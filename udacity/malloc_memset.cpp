// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused malloc_memset.cpp && ./a.out
// cppcheck --enable=all ./malloc_memset.cpp 

#include <iostream>
// Include library for memset
#include <cstring>
// Include library for malloc
#include <cstdlib>

using namespace std;

int main() {

    int *ptr = nullptr;

    // Notice how pointer is allocated to single int memory space 
    // but later is redicerted to show to memory block
    ptr = new(std::nothrow) int;
    //  We can initialize memory block using malloc
    //  declaring memory space for array of 4 integers
    ptr = (int*) std::malloc(4*sizeof(int));
    for (int i=0; i< 4; i++) {
        cout << "Address: " << &ptr[i] << " Value: "<< ptr[i] << std::endl;
    }

    char *testPtr = (char*) std::malloc(4*sizeof(char));
    for (int i=0; i< 5; i++) {
        cout << "Address: " << &testPtr[i] << " Value: "<< testPtr[i] << std::endl;
    }

    // every memory place is used for initialization of specific value
    // here we are using letters for values, but casted to ints
    for( int i=0; i<4; i++){
        // sending address by reference
        std::memset(&ptr[i],('A' + i), sizeof(int));
    }

    // Printing state of our array
    // we are converting int values to char to see what is happening with our values
    for (int i=0; i<4; i++){
        std::cout << "Address: " << &ptr[i]
        << " Value: "<< char(ptr[i])
        << std::endl;
    }

    delete [] ptr;
    delete [] testPtr;
    
    return 0;
}