// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_promises_futures_2.cpp -pthread && ./a.out


#include <iostream>
#include <thread>
#include <future>

void modifyMessage(std::promise<std::string> &&prms, std::string message) {
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    std::string modifiedMessage = message + " has been modified";
    prms.set_value(modifiedMessage);
}

int main() {

    // define input data
    std::string message = "My Message";

    // create promise and future
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(modifyMessage, std::move(prms), message);

    std::cout << "Original message from main(): " << message << std::endl;
    
    // wait for the results to become available
    // ftr.wait();
    auto status = ftr.wait_for(std::chrono::milliseconds(10000));
    if (status == std::future_status::ready) {
        std::cout << "Modified message from thread(): " << ftr.get() << std::endl;
    } else if (status == std::future_status::timeout || status == std::future_status::deferred) {
        std::cout << "Modified message unavailable !! " << std::endl;
    }
    
    // thread barrier
    t.join();
    
    return 0;
}