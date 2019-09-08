// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused threads_avoidDeadLock.cpp -pthread && ./a.out

/*
we have directly called the lock() and unlock() functions of a mutex. The idea of 
"working under the lock" is to block unwanted access by other threads to the same resource. 
Only the thread which acquired the lock can unlock the mutex and give all remaining threads 
the chance to acquire the lock. In practice however, direct calls to lock() should be avoided 
at all cost! Imagine that while working under the lock, a thread would throw an exception 
and exit the critical section without calling the unlock function on the mutex. In such a 
situation, the program would most likely freeze as no other thread could acquire the mutex any more.

We can avoid this problem by creating a std::lock_guard object, which keeps an associated mutex 
locked during the entire object life time. The lock is acquired on construction and released 
automatically on destruction. 

Also, std::lock_guard guarantees exception safety because any critical section is 
automatically unlocked when an exception is thrown.

*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <algorithm>

double result;
std::mutex mtx;

void printResult(int denom) {
    std::cout << "for denom = " << denom << ", the result is " << result << std::endl;
}

void divideByNumber(double num, double denom) {
    // std::lock_guard<std::mutex> lck(mtx);
    try { 
        // divide num by denom but throw an exception if division by zero is attempted
        if (denom != 0 ) {
            // mtx.lock();
            std::lock_guard<std::mutex> lck(mtx);
            result = num / denom ;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            printResult(denom);
            // mtx.unlock();
        } else {
            throw std::invalid_argument("Exception from thread: Division by zero!");
        }
    } catch (const std::invalid_argument &e) {
        // notify the user about the exception and return 
        std::cout << e.what() << std::endl;
        return;
    }
}


int main() {

    // create a number of threads which execute the function "divideByNumber" with varying parameters
    std::vector<std::future <void> > futures;
    for (double i = -5; i<= +5; ++i) {
        futures.emplace_back(std::async(std::launch::async, divideByNumber, 50, i));
    }

    // wait for the results
    std::for_each(futures.begin(), futures.end(), [](auto &ftr){
        ftr.wait();
    });

    return 0;
}