/*
** RUN: g++ -std=c++17 -pthread 2_ThreadManagement.cpp && ./a.out

1. What will happen if thread is neither joined nor detached ? program will terminate.
    Make sure t1 is not destroyed before join or detach - before t1 goes out of scope..
2. While parent thread is doing its job for some reason if its throws out exception
    Then again thread object t1 destroyed / goes out of scope before joined. 
3. Altenatively we can use RAII.. Wrapping t1 and joining it in its destructor.
   So, when ever w goes out of scope ..it will join thread automatically.

*/

#include <iostream>
#include <thread>
using namespace std;

void function_1 ()  {
    cout << "Beauty is only skin-deep" << endl;
    
}

int main() {
    std::thread t1(function_1);   // t1 starts runnning
    // using RAII
    // wrapper w(t1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // do some work

    try {   
        // do some work
    } catch (...) {
        t1.join();      // t1 will be joined with or with out exception.
        throw;
    }


    t1.join();
    return 0;
}
