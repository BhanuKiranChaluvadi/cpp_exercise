// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused pointer_resizeArray.cpp 
// cppcheck --enable=all ./pointer_resizeArray.cpp 


#include <iostream>

using namespace std;

int* createArr(size_t size) {
    return new int[size];
}

int* resizeArr(int* arrPtr, int resize, int size) {
    // create an array
    int* resizeArrPtr = new int[resize];
    // copy the values
    for(int i=0; i<size; i++)
        *(resizeArrPtr+i) = *(arrPtr+i);
    // free up memory
    delete [] arrPtr;
    return resizeArrPtr;
}

int main() {
    int size;
    cout << "Enter the array size: " << endl;
    cin >> size;
    
    int* arrPtr = createArr(1000);
    resizeArr(arrPtr, 20, 10);
    return 0;
}