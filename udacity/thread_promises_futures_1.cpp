// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_promises_futures_1.cpp -pthread && ./a.out


/*
we start listening on the other end of the communication channel by calling the function get() 
on the future. This method will block until data is available - 
which happens as soon as set_value has been called on the promise (from the thread). 
If the result is movable (which is the case for std::string), it will be moved -
otherwise it will be copied instead.


It is also possible that the worker value calls set_value on the promise
before get() is called on the future. In this case, get() returns immediately without any delay. 
After get() has been called once, the future is no longer usable. 
This makes sense as the normal mode of data exchange between promise and future works 
with std::move - and in this case, the data is no longer available in the channel after the 
first call to get(). If get() is called a second time, an exception is thrown.

*/

#include <iostream>
#include <thread>
#include <future>

void modifyMessage(std::promise<std::string> && prms, std::string message) {
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    std::string modifiedMessage = message + " has been modified ";
    prms.set_value(modifiedMessage);
    return;
}

int main() {

    // define message
    std::string messageToThread = "My Message";

    // create promise and future
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as an argument
    std::thread t(modifyMessage, std::move(prms), messageToThread);

    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // retrieve mdified message via future and print to console
    std::string messageFromThread = ftr.get();
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl; 

    // thread barrier
    t.join();

    return 0;
}