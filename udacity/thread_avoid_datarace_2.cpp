// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_avoid_datarace_2.cpp -pthread && ./a.out
/*
When passing a complex data structure however, there are sometimes pointer variables 
hidden within, that point to a (potentially) shared data buffer - which might cause 
a data race even though the programmer believes that the copied data will effectively preempt this.

This time however, even though a copy has been made, the original object v0 is modified, 
when the thread function sets the new name. This happens because the member _name is a 
pointer to a string and after copying, even though the pointer variable has been duplicated, 
it still points to the same location as its value (i.e. the memory location) has not changed.

Classes from the standard template library usually implement a deep copy behavior by default (such as std::vector).
When dealing with proprietary data types, this is not guaranteed. The only safe way to tell 
whether a data structure can be safely passed is by looking at its implementation: 
Does it contain only atomic data types or are there pointers somewhere? If this is 
the case, does the data structure implement the copy constructor (and the assignment operator) 
correctly? Also, if the data structure under scrutiny contains sub-objects, their respective 
implementation has to be analyzed as well to ensure that deep copies are made everywhere.

Unfortunately, one of the primary concepts of object-oriented programming - information hiding - 
often prevents us from looking at the implementation details of a class - we can only see the 
interface, which does not tell us what we need to know to make sure that an object of the 
class may be safely passed by value.
*/

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

    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));   
    v0.setName("Vehicle 3");
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}

