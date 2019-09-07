// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_avoid_datarace_5.cpp -pthread && ./a.out

/*
As with the above-mentioned copy constructor, passing by value is usually safe - provided that 
a deep copy is made of all the data structures within the object that is to be passed. 

With move semantics , we can additionally use the notion of uniqueness to prevent data 
races by default. In the following example, a unique_pointer instead of a raw pointer 
is used for the string member in the Vehicle class.

As can be seen, the std::string has now been changed to a unique pointer, which 
means that only a single reference to the memory location it points to is allowed. 
Accordingly, the move constructor transfers the unique pointer to the worker by using 
std::move and thus invalidates the pointer in the main thread. When calling 
v0.getName(), an exception is thrown, making it clear to the programmer that 
accessing the data at this point is not permissible - which is the whole point of using a 
unique pointer here as a data race will now be effectively prevented.

The point of this example has been to illustrate that move semantics on its own is not 
enough to avoid data races. The key to thread safety is to use move semantics 
in conjunction with uniqueness. It is the responsibility of the programmer to ensure that 
pointers to objects that are moved between threads are unique.

*/


#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <memory>


class Vehicle {
public:
    Vehicle() : _id(0), _name(new std::string("Default Name")) {
        std::cout << "Vechicle # " << _id << " Default constructor called" << std::endl;
    }

    // Initializing the constrcutor
    Vehicle(int id, std::string name) : _id(id),  _name(new std::string(name)) {
        std::cout << "Vechicle # " << _id << " Initializing constructor called" << std::endl;
    }

    // move constructor with unique pointer
    Vehicle(Vehicle && other) : _name(std::move(other._name)){
        _id = other.getID();
        other.setID(0);

        std::cout << "Vehicle #" << _id << " move constructor called" << std::endl;
    }

    // setters and getters
    void setID(int id) {_id = id; }
    int getID() { return _id; }
    void setName(std::string name) { *_name = name; }
    std::string getName() { return *_name; }


private:
    int _id;
    std::unique_ptr<std::string> _name;
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
    // std::cout << v0.getName() << std::endl; // this will now cause an exception

    return 0;
}

