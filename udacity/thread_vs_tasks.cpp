
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

std::thread and std::async is that with the latter, the system decides wether the associated function 
should be run asynchronously or synchronously. By adjusting the launch parameters of std::async 
manually, we can directly influence wether the associated thread function will be executed 
synchronously or asynchronously.

If we were to use the launch option "async" instead of "deferred", we would enforce an asynchronous 
execution whereas the option "any" would leave it to the system to decide - which is the default


Internally, std::async creates a promise, gets a future from it and runs a template function that 
takes the promise, calls our function and then either sets the value or the exception of that 
promise - depending on function behavior. The code used internally by std::async is more or less 
identical to the code we used in the previous example.

Also, std::async makes it possible to control the amount of concurrency by passing an optional 
launch parameter, which enforces either synchronous or asynchronous behavior. 
*/

#include <iostream>
#include <thread>
#include <future>

double divideByNumber(double num, double denom) {

    std::cout << "Worker thread id = "<< std::this_thread::get_id() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work

    if( denom == 0) {
        throw std::runtime_error("Exception from thread: Division by zero!");
    }

    return num / denom ;
}

int main() {

    // print system id of main thread
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    // use asyn
    double num = 42.0, denom = 0.0;
    // divideByNumber(num, denom);
    // std::future<double> ftr = std::async(divideByNumber, num, denom);
    std::future<double> ftr = std::async(std::launch::deferred, divideByNumber, num, denom);
    // std::future<double> ftr = std::async(std::launch::async, divideByNumber, num, denom);

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
