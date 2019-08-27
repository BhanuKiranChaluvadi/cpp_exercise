// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_memberFunction_ex2.cpp -pthread && ./a.out

/*
Instead passing value by reference and making sure its scope.
An alternative is to use a heap-allocated object and a reference-counted pointer such as 
std::shared_ptr<Vehicle> to ensure that the object lives as long as it takes the thread 
to finish its work.
*/

#include <iostream>
#include <thread>

class Vehicle {
    int _id;
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void printID() {
        std::cout << "Vehicle ID="<< _id << std::endl;
    }
};

int main() {

    // create thread
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t1(&Vehicle::addID, v, 1);   // call member function on object v

    // wait for thread to finish
    t1.join();
    
    // print vehcle id's
    v->printID();

    return 0;
}
