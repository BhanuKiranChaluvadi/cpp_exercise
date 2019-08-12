// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused reference_exercise.cpp && ./a.out
// cppcheck --enable=all ./reference_exercise.cpp

#include <iostream>

template <class T>
void swap(T &var1, T &var2)
{
    var1 += var2;
    var2 = var1 - var2;
    var1 -= var2;
    return;
}

int main()
{
    float var1 = 23.2;
    float var2 = 14.83;

    std::cout << "Values before swap: " << var1 << " " << var2 << std::endl;
    swap(var1, var2);
    std::cout << "Values after swap: " << var1 << " " << var2 << std::endl;

    return 0;
}