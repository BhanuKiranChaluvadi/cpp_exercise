// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_promises_futures_3.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <future>
#include <cmath>

/**/
void divideByNumber (std::promise<double> &&prms, double num, double denom) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // simulate work
    try {
        if (denom == 0)
            throw std::runtime_error("Exception from thread: Division by zero!");
        else 
            prms.set_value(num / denom);
    } catch (...) {
        prms.set_exception(std::current_exception());
    }

}

// Throws an error. 
/* 
void divideByNumber(std::promise<double> &&prms, double num, double denom) {

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work

    if( denom == 0) {
        throw std::runtime_error("Exception from thread: Division by zero!");
    } else 
        prms.set_value(num / denom);
}
*/


int main() {

    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass future as argument
    double num = 42.0, denom = 0.0;
    std::thread t(divideByNumber, std::move(prms), num, denom);

    // retrive result within try-catch-block
    try {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    // thread barrier
    t.join();

    return 0;
}