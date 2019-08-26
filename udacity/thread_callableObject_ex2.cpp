// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_callableObject_ex2.cpp -pthread && ./a.out

#include <iostream>
#include <thread>

class Vehicle 
{
    int _id;
public:
    Vehicle(int id) : _id(id) {}
    void operator() () {
        std::cout << "Vehicle #" << _id << " has been created" << std::endl;
    }
};

int main() {
    
    // create thread
    std::thread t(Vehicle(5));
    
    // do something in main
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t.join();
    return 0;
}
