// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused threads_randomness_ofEvents.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;

void thread_function() {
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work 1 in thread\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work 2 in thread\n";

}

int main() {

    // create a thread
    std::thread t(thread_function);

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work 1 in main\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work 2 in main\n";

    // wait thread to finish
    t.join();

    return 0;
}
