// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_multi_ex2.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <vector>
#include <random>

int main() {

    // create thread
    std::vector<std::thread> threads;
    for(size_t i=0; i<10; ++i) {
        // create new thread froom a lambda
        threads.emplace_back([i](){
            // wait for certain amount of time
            std::this_thread::sleep_for(std::chrono::milliseconds( 10 * i));

            // perform work
            std::cout << "Hello from worker thread # " << i << std::endl;
        });
    }

    // do somethign in main()
    std::cout << "Hello from Main thread" <<std::endl;

    for (auto &t : threads) 
        t.join();

    return 0;
}




