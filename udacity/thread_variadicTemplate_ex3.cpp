// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_variadicTemplate_ex3.cpp -pthread && ./a.out

/*
Even though the code works, we are now sharing mutable data between threads - 
which will be something we discuss in later sections of this course 
as a primary source for concurrency bugs.
*/
#include <iostream>
#include <thread>
#include <string>


void printName(std::string &name, int waitTime) {
    std::this_thread::sleep_for(std::chrono::microseconds(waitTime));
    name += "(from Thread)";
    std::cout << name << std::endl;
}

int main() {

    std::string name("Bhanu Kiran");

    // starting thread
    std::thread t1(printName, std::ref(name), 50);

    // wait for the thread before returning
    t1.join();

    // print name from main
    name += " (from Main)";
    std::cout <<  name << std::endl;

    return 0;
}