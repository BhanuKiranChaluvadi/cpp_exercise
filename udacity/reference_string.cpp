// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused reference_string.cpp && ./a.out
// cppcheck --enable=all ./reference_string.cpp 

#include<iostream>
#include<string>

using namespace std;

void addSpaces(const char * &str1) {
    // Make a string with double the size
    char *temp = new char(sizeof(str1)*2);
    char *start = temp;  // to remember the start address
    // cout << "First value: " << *str1 << endl;
    // cout << "Second value: " << *str1++ << endl;
    // cout << "Third value: " << *str1 << endl;
    while(*str1 != '\0') {
        // *temp++ = *str1++;
        // *temp++  = ' ';

        *temp++ = *str1++;
        cout << "temp: " << temp << endl;
        *temp++ = ' ';
        // temp++;
        // str1++;
    }
    cout << start << endl;
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
