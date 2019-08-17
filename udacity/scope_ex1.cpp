// RUN: g++ -g -std=c++17 -Wall -Wextra -Wpedantic -Wunused scope_ex1.cpp && ./a.out
// cppcheck --enable=all ./scope_ex1.cpp 

#include <iostream>

namespace math
{
    const double pi = 3.141592653;
    const double euler =  2.718281828;
    const double sqrt2 = 1.414213562;
    const double ln2 = 0.6931471;

} // namespace math

int main() {

    std::cout << math::pi << std::endl;
    std::cout << math::euler << std::endl;
    std::cout << math::sqrt2 << std::endl;
    std::cout << math::ln2 << std::endl;

    return 0;
}
