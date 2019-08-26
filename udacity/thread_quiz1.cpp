
// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_quiz1.cpp -pthread && ./a.out

#include<iostream>
#include <thread>
#include <chrono>

void threadFunctionEven() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "Even thread\n";
}

void threadFunctionOdd() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "Odd thread\n";
}

int main() {

    for (int i=0; i < 6; i++) {
        if(i % 2 == 0) {
            std::thread t(threadFunctionEven);
            t.detach();
        } else {
            std::thread t(threadFunctionOdd);
            t.detach();
        }
    }

    // ensure that main does not return before the threads are finished
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // detached -- joinable is set to false.s

    std::cout << "End of main is reached" << std::endl;
    return 0;
}
