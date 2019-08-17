// RUN: g++ -g -std=c++17 -Wall -Wextra -Wpedantic -Wunused scope_2.cpp && ./a.out
// cppcheck --enable=all ./scope_2.cpp

#include <iostream>

using namespace std;

int val = 100;
//this variable val is defined in global namespace
// which means, its scope is global. It exists
// everywhere

namespace _namespace
{
     int val = 200;  
    // it is defined in a local namespace called '_namespace'
    // outside _namespace it doesn't exist.
}

void _func()
{
   int val = 300;  
    // scope is the function itself.
    // outside the function, a doesn't exist.
    cout << val << endl;
    cout << ::val << endl;
    std::cout << _namespace::val << std::endl;
   {
        int val = 400; //the curly braces defines this scope
        cout << ""  << endl;
        cout << val << endl;
        cout << ::val << endl;
        std::cout << _namespace::val << std::endl;
   }
}

class _class
{
   int val;  
    // scope is the class itself.
    // outside class _class, it doesn't exist.
    
};

int main() {

    _func();

    return 0;
}