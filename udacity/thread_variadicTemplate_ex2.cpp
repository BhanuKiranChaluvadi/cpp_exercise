// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_variadicTemplate_ex2.cpp -pthread && ./a.out

/*
Calling a function directly and passing it to a thread
1. Calling a function directly :
    arguments may be passed by value, by reference or by using move semantics -
     depending on the signature of the function.
2. Calling a function using a variadic template :
    the arguments are by default either moved or copied - 
    depending on wether they are rvalues or lvalues.
    If you want to move an lvalue for example, we can call std::move.

*/

#include <iostream>
#include <thread>
#include <string>

void printName(std::string name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    std::cout << "Name (from Thread) = " << name << std::endl;
}

int main()
{
    std::string name1 = "MyThread1";
    std::string name2 = "MyThread2";

    // starting threads using value-copy and move semantics 
    std::thread t1(printName, name1, 50);
    std::thread t2(printName, std::move(name2), 100);

    // wait for threads before returning
    t1.join();
    t2.join();

    // print name from main
    std::cout << "Name (from Main) = " << name1 << std::endl;
    std::cout << "Name (from Main) = " << name2 << std::endl;

    return 0;
}

