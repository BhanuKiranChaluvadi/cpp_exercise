/*
** RUN: g++ -std=c++17 -pthread 4_ThreadManagement.cpp && ./a.out

1. Passing a parameter
2. Parameter to a thread is always passed by value although passed by reference
3. Passing through pointer will work.


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
    void operator()(string* msg)  {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // perform some work
        cout << "t1 says: " << *msg << endl;
        *msg = "yes trust yes love";
    }
};

int main() {

    string s = "no trust no love" ; 
  
    std::thread t1((Fctor()), &s);              // most vexing syntax
    t1.join();

    cout << "Main thread says: " << s << endl;

    return 0;
}
