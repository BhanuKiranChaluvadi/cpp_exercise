// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_conditionVariables.cpp -pthread && ./a.out

/*
std::condition_variable

A std::condition_variable has a method wait(), which blocks, when it is called by a thread. 
The condition variable is kept blocked until it is released by another thread. The release 
works via the method notify_one() or the notify_all method. The key difference between the 
two methods is that notify_one will only wake up a single waiting thread while notify_all 
will wake up all the waiting threads at once.

A condition variable is a low-level building block for more advanced communication protocols. 
It neither has a memory of its own nor does it remember notifications. Imagine that one thread 
calls wait() before another thread calls notify(), the condition variable works as expected and 
the first thread will wake up. Imagine the case however where the call order is reversed such 
that notify() is called before wait(), the notification will be lost and the thread will block 
indefinitely. So in more sophisticated communication protocols a condition variable should always 
be used in conjunction with another shared state that can be checked independently. 
Notifying a condition variable in this case would then only mean to proceed and check this other 
shared state.

*/

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    int getID() { return _id; }

private:
    int _id;
};

class WaitingVehicles
{
public:
    WaitingVehicles() {}

    Vehicle popBack()
    {
        // perform vector modification under the lock
        std::unique_lock<std::mutex> uLock(_mutex);
        _cond.wait(uLock, [this] { return !_vehicles.empty(); }); // pass unique lock to condition variable

        // remove last vector element from queue
        Vehicle v = std::move(_vehicles.back());
        _vehicles.pop_back();

        return v; // will not be copied due to return value optimization (RVO) in C++
    }

    void pushBack(Vehicle &&v)
    {
        // simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // perform vector modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);

        // add vector to queue
        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
        _vehicles.push_back(std::move(v));
        _cond.notify_one(); // notify client after pushing new Vehicle into vector
    }

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
};

int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 10; ++i)
    {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::cout << "Collecting results..." << std::endl;
    while (true)
    {
        // popBack wakes up when a new element is available in the queue
        Vehicle v = queue->popBack();
        std::cout << "   Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
    });

    std::cout << "Finished!" << std::endl;

    return 0;
}