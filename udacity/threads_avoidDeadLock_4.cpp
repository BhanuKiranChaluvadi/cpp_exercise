// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused threads_avoidDeadLock_4.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1, mutex2;

void ThreadA() {
    // Ensure that locks are always exeuted in the same order.
    std::lock(mutex1, mutex2);  // Just locks them ...but will not unlock and hence lock_guard
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
    std::cout << "Thread A"<< std::endl;
}

void ThreadB() {
    std::lock(mutex1, mutex2);  // Just locks them ...but will not unlock and hence lock_guard
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
    std::cout << "Thread B"<< std::endl;
}

void ExecuteThreads() {

    std::thread t1(ThreadA);
    std::thread t2(ThreadB);

    t1.join();
    t2.join();

    std::cout << "Finished" << std::endl;
}

int main() {

    ExecuteThreads();

    return 0;
}