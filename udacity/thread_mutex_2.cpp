// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused threads_mutex_2.cpp -pthread && ./a.out

/*

# Deadlock 1:

Using mutexes can significantly reduce the risk of data races as seen in the example above. 
But imagine what would happen if an exception was thrown while executing code in the critical 
section, i.e. between lock and unlock. In such a case, the mutex would remain locked indefinitely 
and no other thread could unlock it - the program would most likely freeze.

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
    // mtx.lock();
    try { 
        // divide num by denom but throw an exception if division by zero is attempted
        if (denom != 0 ) {
            mtx.lock();
            result = num / denom ;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            printResult(denom);
            mtx.unlock();
        } else {
            throw std::invalid_argument("Exception from thread: Division by zero!");
        }
    } catch (const std::invalid_argument &e) {
        // notify the user about the exception and return 
        std::cout << e.what() << std::endl;
        return;
    }
    // mtx.unlock();
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