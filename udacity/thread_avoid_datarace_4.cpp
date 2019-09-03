// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_avoid_datarace_4.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <future>
#include <string>

class Vehicle {
public:
    Vehicle() : _id(0), _name(new std::string("Default Name")) {
        std::cout << "Vechicle # " << _id << " Default constructor called" << std::endl;
    }

    ~Vehicle() {
        delete _name;
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

    // move copy constructor
    Vehicle(Vehicle && other) {
        _id = other._id;
        _name = other._name;
        // _name = new std::string(other.getName());
        // Release the data in other
        other.setID(0);
        other.setName("Default Name");

        std::cout << "Vehicle #" << _id << " move constructor called" << std::endl;
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

    // launch a thread that modifies the Vehicle name
    std::future<void> ftr = std::async([](Vehicle v) {
        v.setName("Vehicle 2");
    }, std::move(v0));

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}

