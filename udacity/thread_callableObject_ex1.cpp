
// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_callableObject_ex1.cpp -pthread && ./a.out

/* 
In C++, callable objects are object that can appear as the left-hand operand of the call operator. 
1. Pointers to functions
2. Objects of a class that defines an overloaded function call operator ----> ()
3. lambdas (an anonymous inline function),
with which function objects can be created in a very simple way.

Function object instance, ,which is basically an instance of class that implement the function call operator.

*** std::thread t(Vehicle());
1. a variable definition for variable t of class std::thread, initialized with an anonymous instance of class Vehicle or
2. a function declaration for a function t that returns an object of type std::thread and has a single (unnamed) 
        parameter that is a pointer to function returning an object of type Vehicle
***
TO PASS DATA
pass it in as a constructor argument and store it as a data member:
*/

#include <iostream>
#include <thread>
#include <chrono>

class Vehicle
{
public:
    void operator()()
    {
        std::cout << "Vehicle object has been created" << std::endl;
    }
};


int main()
{
    // create thread 
    // std::thread t{Vehicle()}; // C++'s most vexing parse

    std::thread t1( (Vehicle()) ); // Add an extra pair of parantheses
    std::thread t2 = std::thread( Vehicle() ); // Use copy initialization
    std::thread t3{ Vehicle() };// Use uniform initialization with braces

    // do something in main()
    std::cout << "Finished work in main \n";
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // wait for thread to finish
    t1.join();
    t2.join();
    t3.join();

    return 0;
}