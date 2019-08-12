// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused new_operator.cpp && ./a.out
// cppcheck --enable=all ./new_operator.cpp

#include <iostream>

int main() {

    double *ptr = new double(23);
    double *arr_ptr = new double[4];

    for (int i = 0; i < 3; i++) {
        *ptr = ++ *ptr;
        std::cout << "Address: " << ptr << " Value: " << *ptr << std::endl;
        std::cout << "Address array: " << arr_ptr << " Value array: " << arr_ptr[i] << std::endl;
    }

    delete ptr;
    delete [] arr_ptr;
    
    return 0;
}