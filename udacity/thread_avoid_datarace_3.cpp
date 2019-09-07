// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_avoid_datarace_3.cpp -pthread && ./a.out


#include <iostream>
#include <thread>
#include <future>
#include <string>

class Vehicle {
public:
    Vehicle() : _id(0), _name(new std::string("Default Name")) {
        std::cout << "Vechicle # " << _id << " Default constructor called" << std::endl;
    }

    // Initializing the constrcutor
    Vehicle(int id, std::string name) : _id(id),  _name(new std::string(name)){
        std::cout << "Vechicle # " << _id << " Initializing constructor called" << std::endl;
    }

    // copy constructor
    Vehicle(const Vehicle &other) {
        _id = other._id;
        if (other._name != nullptr) {
            _name = new std::string;
            *_name = *other._name;
        }
        // std::cout << << std::endl;
        std::cout << "Vechicle # " << _id << " Copy constructor called" << std::endl;
    }

    // copy assignment
    Vehicle& operator = (const Vehicle& other) {
        std::cout << "Vechicle # " << other._id << " Copy assignment called" << std::endl;
        if(this != &other) {
            delete _name;
        }
        _id = other._id;
        _name = new std::string(*(other._name)) ;

        return *this;
    }

    // setters and getters
    void setID(int id) {_id = id; }
    int getID() { return _id; }
    void setName(std::string name) {*_name = name ; }
    std::string getName() { return *_name; } 

private:
    int _id;
    std::string *_name;
};

int main () {

    // create instance of class Vehicle
    Vehicle v0;     // default constructor
    Vehicle v1(1, "Vehicle 1");  // initializing constructor

    // read and write name in different threads 
    std::future<void> ftr = std::async([](Vehicle v) {
        std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));    // simulate work
        v.setName("Vehicle 2");
    }, v0);

    // std::this_thread::sleep_for(std::chrono::milliseconds(100));   
    v0.setName("Vehicle 3");
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}

