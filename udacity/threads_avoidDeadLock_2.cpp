// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused threads_avoidDeadLock_2.cpp -pthread && ./a.out

/*

std::lock_guard --> std::unique_lock

we can only lock the mutex once and the only way to control lock and unlock is by invalidating 
the scope of the std::lock_guard object. But what if we wanted (or needed) a finer control of the 
locking mechanism?

A more flexible alternative to std::lock_guard is unique_lock, that also provides support 
for more advanced mechanisms, such as deferred locking, time locking, recursive locking, 
transfer of lock ownership and use of condition variables (which we will discuss later). 
It behaves similar to lock_guard but provides much more flexibility, especially with regard 
to the timing behavior of the locking mechanism.

Advantages:
1. …construct an instance without an associated mutex using the default constructor 
2. …construct an instance with an associated mutex while leaving the mutex unlocked at first using the deferred-
locking constructor
3. …construct an instance that tries to lock a mutex, but leaves it unlocked if the lock failed using 
the try-lock constructor
4. …construct an instance that tries to acquire a lock for either a specified time period or until 
a specified point in time
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
    std::unique_lock<std::mutex> lck(mtx);
    try { 
        // divide num by denom but throw an exception if division by zero is attempted
        if (denom != 0 ) {
            result = num / denom ;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            printResult(denom);
            lck.unlock();

            // do something outside of the lock
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            lck.lock();
            // do something else under the lock
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
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