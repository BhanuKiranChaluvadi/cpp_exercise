// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused pointers_project_lab.cpp 
// cppcheck --enable=all ./pointers_project_lab.cpp

#include <iostream>

using namespace std;

template <class T>
class PtrDetails {
public:
    PtrDetails(T ptr, int size) : memPtr(ptr) {
        if (size > 0) {
            isArray = true;
        }
    }

public:
    int refcount;
    T memPtr;
    bool isArray;
    int arraySize;

};

template<class T>
bool operator == (const PtrDetails<T> &obj1,
                const PtrDetails<T> &obj2) {

}



int main() {
    return 0;
}