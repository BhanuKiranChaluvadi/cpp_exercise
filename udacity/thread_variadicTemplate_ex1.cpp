// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_variadicTemplate_ex1.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <string>

void printID(int id) {
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    std::cout << "ID = " << id << std::endl;
}

void printIDAndName(int id, std::string name) {
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    std::cout << "ID = " << id << ", name = " << name << std::endl;
}


int main() {

    int id = 0; // Define an integer variable

    // ++id;
    // starting thread using variadic function
    std::thread t1(printID, id);
    std::thread t2(printIDAndName, ++id, "MyString");
    // std::thread t3(printIDAndName, ++id);   // this produce a compiler error

    // wait for thread before returning
    t1.join();
    t2.join();
    // t3.join();

    return 0;
}
