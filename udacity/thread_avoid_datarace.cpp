// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_avoid_datarace.cpp -pthread && ./a.out

/*
An instance of the proprietary class Vehicle is created and passed 
to a thread by value, thus making a copy of it.

Note that v0 is passed by value to a Lambda, 
which serves as the thread function for std::async
*/

#include <iostream>
#include <thread>
#include <future>

class Vehicle {
public:
    Vehicle() : _id(0) {
        std::cout << "Vechicle # " << _id << "Default constructor called" << std::endl;
    }

    // Initializing the constrcutor
    Vehicle(int id) : _id(id) {
        std::cout << "Vechicle # " << _id << "Initializing constructor called" << std::endl;
    }

    // setters and getters
    void setID(int id) {_id = id; }
    int getID() { return _id; }

private:
    int _id;
};

int main () {

    // create instance of class Vehicle
    Vehicle v0;     // default constructor
    Vehicle v1(1);  // initializing constructor

    // read and write name in different threads 
    std::future<void> ftr = std::async(std::launch::async, [](Vehicle v) {
        std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));    // simulate work
        v.setID(2);
    }, v0);

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));   
    v0.setID(3);
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    ftr.wait();
    std::cout << "Vehicle #" << v0.getID() << std::endl;

    return 0;
}
