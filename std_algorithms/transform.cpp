/*
** RUN: g++ -std=c++17 transform.cpp && ./a.out

** Simple std::algorithm illustration

*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

// only for vector
template<class T>
void print (const T &container) {
    for (auto element: container)
        cout << ' ' << element;
    cout << "\n";
    return;
}

int main() {

    string s("hello");
    // std::transform(s.begin(), s.end(), s.begin(), 
    //                 [](unsigned char c) -> unsigned char {return std::toupper(c);});
    
    std::transform(s.begin(), s.end(), s.begin(), 
                    [](unsigned char c) {return std::toupper(c);});

    cout << "Transformed string: "<< s << "\n";

    vector<size_t> ordinals;
    // std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
    //         [] (unsigned char c) -> size_t { return c; });

    std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
            [] (unsigned char c) { return c; });

    cout << s << ":";
    // print<std::vector<size_t>>(ordinals);
    print(ordinals);


    // second version
    vector<int> vec1{1, 2, 3, 4, 5};
    vector<int> vec2{9, 8, 7, 6, 5};
    vector<double> sum;

    std::transform(vec1.begin(), vec1.end(), vec2.begin(), std::back_inserter(sum) , 
                    [](int a, int b) { return a+b; });

    cout << "SUM: ";
    print(sum);

    return 0;
}