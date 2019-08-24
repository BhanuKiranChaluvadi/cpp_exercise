// RUN: g++ -pthread -std=c++17 -Wall -Wextra -Wpedantic -Wunused test_threads.cpp && ./a.out

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>

int main() {

    std::vector <std::thread> threads;

    // startup n threads
    int nThreads = 4;
    for (int i =0; i< nThreads; ++i) {
        threads.emplace_back(std::thread([]() {
            while (true) {
                // std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }));
    }

    // wait for the threads to finish before leaving main
    std::for_each(std::begin(threads), std::end(threads), [](std::thread &t){
        t.join();
    });

    return 0;
}




