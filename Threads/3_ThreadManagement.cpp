/*
** RUN: g++ -std=c++17 -pthread 3_ThreadManagement.cpp && ./a.out

1. Thread object can also be constructe not only with regular function but also with any callable object.
    eg: functor or lambda functions
*/

#include <iostream>
#include <thread>
using namespace std;

void function_1 ()  {
    cout << "Beauty is only skin-deep" << endl;
}

// Functor - function pointer
class Fctor {
public:
    void operator()()  {
         std::this_thread::sleep_for(std::chrono::milliseconds(100));  // perform some work
         cout << "Fctor: Beauty is only skin-deep" << endl;
    }
};

int main() {
    // std::thread t1(function_1);   // t1 starts runnning

    Fctor fct;
    std::thread t1(fct);  
    std::thread t2((Fctor()));              // most vexing syntax
    std::thread t3{Fctor()};                // most vexing syntax
    std::thread t4 = std::thread(Fctor());  // most vexing syntax
    cout << "From Main Thead ID: " << std::this_thread::get_id() << endl;

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
