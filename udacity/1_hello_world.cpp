// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused 1_hello_world.cpp 
// cppcheck --enable=all ./1_hello_world.cpp 

// gcc/clang compiler Warnings: -Wall -Wextra -Wpedantic -Wunused 
// Static anlyers: plugins(Eclipse & VS code)/Cppcheck/Clang/Coverity/IKOS

#include <iostream>

using namespace std;

int main() {
    int a;
    cout << "Hello World!! \n";
    return 0;
} 