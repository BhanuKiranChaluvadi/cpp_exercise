// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_mutex_1.cpp -pthread && ./a.out

/*
Assuming we have a piece of memory (e.g. a shared variable) that we want to protect from 
simultaneous access, we can assign a mutex to be the guardian of this particular memory. 
It is important to understand that a mutex is bound to the memory it protects.

In order to protect the access to _vehicles from being manipulated by several threads at 
sonce, a mutex has been added to the class as a private data member.
*/

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <mutex>


class Vehicle {
public:
    Vehicle(int id) : _id(id) {}
    int getID() {return _id;}

private:
    int _id;
};

class WaitingVehicles {
public:
    WaitingVehicles() {}
    
    // getters / setters
    void printSize() {
        
        _mtx.lock();
        std::cout << "#vehicles = " << _vehicles.size() << std::endl;
        _mtx.unlock();
    }


    // typical behavious method
    void pushBack (Vehicle &&v) {

        for (size_t i=0; i<3; ++i) {
            if(_mtx.try_lock_for(std::chrono::milliseconds(1000))) {
                _vehicles.emplace_back(std::move(v)); // data race would cause an exception
                _mtx.unlock();
                break;
            } else {
                std::cout << "Error! Vehicle #" << v.getID() << " could not be added to the vector" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }


private:
    std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
    std::timed_mutex _mtx;
    // std::recursive_mutex
    // std::recursive_timed_mutex
};

int main() {
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
    std::vector<std::future<void> > futures;
    for (int i = 0; i < 1000; ++i) {
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::for_each(futures.begin(), futures.end(), [](auto &ftr){
        ftr.wait();
    });

    queue->printSize();

    return 0;
}