
// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_vs_tasks.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <future>

double divideByNumber(double num, double denom) {

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work

    if( denom == 0) {
        throw std::runtime_error("Exception from thread: Division by zero!");
    }

    return num / denom ;
}

int main() {

    // use asyn
    double num = 42.0, denom = 0.0;
    // divideByNumber(num, denom);
    std::future<double> ftr = std::async(divideByNumber, num, denom);

    // retrieve result within try-cathc-block
    // ftr.wait();
    try {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    } 

    return 0;
}
