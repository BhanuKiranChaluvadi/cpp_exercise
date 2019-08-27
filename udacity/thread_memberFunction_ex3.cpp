// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_memberFunction_ex3.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <string>

class Vehicle {
    int _id;
    std::string _name;
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void setName (std::string name) {
        _name = name;
    }
    void printID() {
        std::cout << "Vehicle ID= " << _id << std::endl;
    }
    void printName() {
        std::cout << "Vehicle Name= " << _name << std::endl;
    }
};

int main() {

    // start thread
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t = std::thread(&Vehicle::setName, v, "nth");

    // wait for thread to finish
    t.join();

    // print vehicle name
    v->printName();

    return 0;
}