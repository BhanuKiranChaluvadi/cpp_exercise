// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_multi_ex1.cpp -pthread && ./a.out

/*
The problem with pushing the thread object into the vector, 
we attempt to make a copy of it. However, thread objects do not have a 
copy constructor and thus can not be duplicated. If this were possible, 
we would create yet another branch in the flow of execution - which is not what we want

Observng the output:
This shows us two important properties of concurrent programs:
1. The order in which threads are executed is non-deterministic.
2. Every time a program is executed, there is a chance for a completely different order of execution.
Threads may get preempted in the middle of execution and another thread may be selected to run.

*/

#include <iostream>
#include <vector>
#include <thread>

void printHello() {
    // perform work
    std::cout << "Hello from Worker thread #" << std::this_thread::get_id() << "\n";
}


int main() {    

    // create threads

    std::vector<std::thread> threads;
    for(size_t i=0; i<5; ++i) {
        // copying thread object cause a compiler error
        /*
        std::thread t(printHello);
        threads.pushback(t);
        */
       // std::thread t(printHello);        // works
       // threads.push_back(std::move(t));  // works
       // moving thread object will work.
       threads.emplace_back(printHello);
    }

    // do something in main()
    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;

    for (auto &t : threads) 
        t.join();

    return 0;
}