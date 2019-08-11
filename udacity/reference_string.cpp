// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused reference_string.cpp && ./a.out
// cppcheck --enable=all ./reference_string.cpp 

#include<iostream>
#include<string>

using namespace std;

void addSpaces(const char * &str1) {
    // Make a string with double the size
    char *temp = new char(sizeof(str1)*2);
    char *start = temp;  // to remember the start address
    while(*str1 != '\0') {
        *temp++ = *str1++;
        *temp++  = ' ';
    }
    // resetting our original pointer to start address
    str1 = start;
}

int main() {
    std::string str = "HELLO WORLD !";
    const char* ptr=  str.c_str();
    cout << "String is: "<<  ptr << endl;
    addSpaces(ptr);
    cout<<"string is: "<< ptr << endl;
    return 0;
}
