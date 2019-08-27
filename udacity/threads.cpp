// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused threads.cpp -pthread && ./a.out

/*
Initialiing a thread
    1. Passing a function object directly (like below). But arguments can't be passed / only global varibles are used.

    # passing arguments to threads -->  function pointer
                                        operator overloading 
                                        lambda function
    2. Using operator () overloading
    3. Using lambda functions
    4. Using thread constructor - varidic functions -- call independent functions / class member functions.
    5. Using member functons 
*/

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>

void thread_function() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // simulate work
    std::cout << "Finished work in thread\n"; 
}

int main() {

    std::cout << "Hello concurrent world from main! Thread id = " << std::this_thread::get_id() << std::endl;
    unsigned int nCores = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nCores << " cores available" << std::endl; 

    std::thread t(thread_function);  
    // do something in the main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50));     // simulate work
    std::cout << "Finished work in main\n";


    // detach thread and continue with main
    // t.detach();
    
    // wait for the thread to finish
    t.join();



    return 0;
}




