// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_monitorObjectPattern_1.cpp -pthread && ./a.out

/*
# Monitor Object - Concurrent message queue

which is a design pattern that synchronizes concurrent method execution to ensure that only 
one method at a time runs within an object. It also allows an object's methods to cooperatively 
schedule their execution sequences. The problem solved by this pattern is based on the 
observation that many applications contain objects whose methods are invoked concurrently by 
multiple client threads. These methods often modify the state of their objects, for example by 
adding data to an internal vector. For such concurrent programs to execute correctly, it is 
necessary to synchronize and schedule access to the objects very carefully. The idea of a monitor 
object is to synchronize the access to an object's methods so that only one method can execute at 
any one time.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <algorithm>

class Vehicle {
public:
    Vehicle (int id) : _id(id) {}
    int getID() { return _id; }
private:
    int _id;
};

class WaitingVehicles {
public:
    WaitingVehicles() {}

    void printIDs() {
        std::lock_guard<std::mutex> myLock(_mtx); // lock is released when myLock goes out of scope
        for (auto &v : _vehicles) {
            std::cout << "   Vehicle #" << v.getID() << " is now waiting in the queue" << std::endl;
        }

    }

    void pushBack(Vehicle &&v) {
        // perform vector modification under the lock
        std::lock_guard<std::mutex> uLock(_mtx);
        std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
        _vehicles.emplace_back(std::move(v));

        // simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
private:
    std::vector<Vehicle> _vehicles;
    std::mutex _mtx;
};

int main() {

    // create monitor object as a shared pointer to enable access by mutiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void> > futures;
    for (int i = 0; i < 10; ++i) {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }
    std::for_each(futures.begin(), futures.end(), [](auto &ftr){
        ftr.wait();
    });

    std::cout << "Collecting results..." << std::endl;
    queue->printIDs();

    return 0;
}