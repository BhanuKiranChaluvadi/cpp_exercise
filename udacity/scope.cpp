// RUN: g++ -g -std=c++17 -Wall -Wextra -Wpedantic -Wunused scope.cpp && ./a.out
// cppcheck --enable=all ./scope.cpp 

// Gobal variables
// Local variables
// Namespaces variables

#include<iostream>

using namespace std;

// Variable created inside namespace
namespace myNamespace {
    int val = 123;
}

// Gobal variable
int val = 100;


int main() {
    // Local variable
    int val = 200;

    // These variables can be accessed from
    // outside the namespace by using the scope
    // operator :: -> also known as scope resolution operator

    // namespace variable value
    std::cout << myNamespace::val << std::endl;
    // global variable value
    std::cout << ::val << std::endl;
    // local variable value
    std::cout << val << std::endl;

    return 0;
}