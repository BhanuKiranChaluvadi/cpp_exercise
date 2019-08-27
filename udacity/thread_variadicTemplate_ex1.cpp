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

    
    // starting thread using variadic function
    std::thread t1(printID, id); 

    std::thread t2(printID, std::ref(id));  // Not ideal. By default thread copies its arguments
                                            // As reference to local data tends to be unlikely 
                                            // to last the entire thread's life time.                     
    std::thread t3(printIDAndName, ++id, "MyString");
    // std::thread t3(printIDAndName, ++id);   // this produce a compiler error


    ++id;

    // wait for thread before returning
    // t1.join();
    t2.join();
    t3.join();
    // t3.join();

    return 0;
}
