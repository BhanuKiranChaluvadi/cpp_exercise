/*
** RUN: g++ -std=c++17 -pthread 1_Introduction.cpp  && ./a.out
** If two threads are sharing resource , in this case COUT
** then the thread owning the resource (main thread)
** should live as long as other thread accessing the resource
*/

#include <iostream>
#include <thread>
using namespace std;

void function_1 ()  {
    cout << "Child thread ID: " << std::this_thread::get_id() << endl;
    cout << "Beauty is only skin-deep" << endl;
}

int main() {
    cout << "Hardware Concurrency: " << std::thread::hardware_concurrency() << endl;
    cout << "Main thread ID: " << std::this_thread::get_id() << endl;
    std::thread t1(function_1);   // t1 starts runnning
    cout << "From Main Child Thead ID: " << t1.get_id() << endl;
    // t1.join();                 // main thread waits until t1 finishes.

    t1.detach();        // t1 will be freely on its own -- deamon process
    if(t1.joinable()) 
        t1.join();      // once detached - can't be joined.

    return 0;
}