// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_memberFunction_ex1.cpp -pthread && ./a.out
/*
we have to ensure that the existence of v2 outlives the completion of the thread t2 -
otherwise there will be an attempt to access an invalidated memory address
*/
#include <iostream>
#include <thread>

class Vehicle {
    int _id ;
public:
    Vehicle() : _id(0) {}  
    void addID(int id) { _id = id; }
    void printID() {
        std::cout << "Vehice ID= " << _id << std::endl;
    }
};


int main() {

    // creata a thread
    Vehicle v1, v2;
    std::thread t1 = std::thread(&Vehicle::addID, v1, 1);   // call member function on object v
    std::thread t2 = std::thread(&Vehicle::addID, &v2, 2);  // call member function on object v

    // wait for the thread to finish
    t1.join();
    t2.join();

    // print Vehicle id
    v1.printID();
    v2.printID();

    return 0;
}
