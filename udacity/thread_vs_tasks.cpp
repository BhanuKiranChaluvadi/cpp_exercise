
// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_vs_tasks.cpp -pthread && ./a.out
/*
We are removing the promise from the argument list as well as the try-catch block. 
Also, the return type of the function is changed from void to double as the result 
of the computation will be channeled back to the main thread using a simple return. After these changes, 
the function has no knowledge of threads, nor of futures or promises - it is a simple function that takes two doubles 
as arguments and returns a double as a result. Also, it will throw an exception when a division by zero is attempted.

In the main thread, we need to replace the call to std::thread with std::async. Note that async returns 
a future, which we will use later in the code to retrieve the value that is returned by the function. 
A promise, as with std::thread, is no longer needed, so the code becomes much shorter. In the try-catch block,
nothing has changed - we are still calling get() on the future in the try-block and exception-handling happens 
unaltered in the catch-block. Also, we do not need to call join() any more. With async, 
the thread destructor will be called automatically - which reduces the risk of a concurrency bug.

*/

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
