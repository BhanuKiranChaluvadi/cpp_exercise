/*
** RUN: g++ -std=c++17 -pthread 5_ThreadManagement.cpp && ./a.out

1. Passing a parameter by reference should use : std::ref
                                                std::move

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
        msg = "yes trust yes love";
    }
};

int main() {

    string s = "no trust no love" ; 
  
    // std::thread t1((Fctor()), std::ref(s));              // most vexing syntax
    std::thread t2((Fctor()), std::move(s));  
    // t1.join();
    t2.join();
    cout << "Main thread says: " << s << endl;

    return 0;
}
