/*
RUN: g++ -std=c++17 booleanalpha.cpp && ./a.out
*/

#include <sstream>
#include <locale>
#include <iostream>
int main()
{
    // boolalpha output
    std::cout << std::boolalpha
              << "boolalpha true: " << true << '\n'
              << "boolalpha false: " << false << '\n';
    std::cout << std::noboolalpha 
              << "noboolalpha true: " << true << '\n'
              << "noboolalpha false: " << false << '\n';
    // boolalpha parse
    bool b1, b2, b3;
    // b3 = true;
    std::istringstream is("falsetrue");

    // is >> std::boolalpha >> b1 >> b2;
    // std::cout << '\"' << is.str() << "\" parsed as " << b1 << ' ' << b2 << '\n';

    is >> std::boolalpha >> b1 >> b2 >> b3;
    std::cout << '\"' << is.str() << "\" parsed as " << b1 << ' ' << b2 << ' ' << b3 << '\n';
}
