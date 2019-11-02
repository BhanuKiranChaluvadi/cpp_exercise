/*
** RUN: g++ -std=c++17 -pthread 6_ThreadManagement.cpp && ./a.out

1. Passing a parameter by reference should use : std::move
2. How many thread should i create a tough problem : 
        Ideally as many threads as  possible
        We don't want to run more threads than hardware can support -- over subscription
        More threads than available cpu cores It creates a lot of contact switching 
        And too many of contact switcing will degrade my performance.

*/

#include <iostream>
#include <thread>
#include <string>

using namespace std;

void function_1 ()  {
    cout << "Beauty is only skin-deep" << endl;
}

// Functor - function pointer
class Fctor {
public:
    void operator()(string msg)  {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // perform some work
        cout << "t1 says: " << msg << endl;
    }
};

int main() {

    string s = "no trust no love" ; 

    std::thread t1((Fctor()), std::move(s)); 

    std::thread t2 = std::move(t1);
    t2.join();
    cout << "Main thread says: " << s << endl;

    return 0;
}
