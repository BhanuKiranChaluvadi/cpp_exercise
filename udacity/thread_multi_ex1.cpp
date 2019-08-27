// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_multi_ex1.cpp -pthread && ./a.out

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
       
       // moving thread object will work.
       threads.emplace_back(printHello);
    }

    // do something in main()
    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;

    for (auto &t : threads) 
        t.join();

    return 0;
}