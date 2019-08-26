// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_callableObject_ex3.cpp -pthread && ./a.out

/*
A Lambda is just an object and, like other objects it may be copied, passed as a parameter, stored in
a container, etc. The Lambda object has its own scope and lifetime which may, in some circumstances, be different
to those objects it has ‘captured’. Programers need to take special care when capturing local objects by reference
because a Lambda’s lifetime may exceed the lifetime of its capture list: It must be ensured that the object to which
the reference points is still in scope when the Lambda is called. This is especially important in multi-threading
programs.
*/

#include <iostream>
#include <thread>

int main() {

    int id = 0; // Define an integer variable

    // starting a first thread by reference
    auto f0 = [&id] () {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "a) ID in Thread (call-by-reference) = " << id << std::endl;
    };

    std::thread t1(f0);

    // start a second thread by value
    std::thread t2([id]() mutable {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "b) ID in Thread (call-by-value) = " << id << std::endl;
    });

    // increment and print id in main
    ++id;
    std::cout << "c) ID in Main (call-by-value) = "<< id  << std::endl;

    // wait for threads before returning
    t1.join();
    t2.join();

    return 0;
}



