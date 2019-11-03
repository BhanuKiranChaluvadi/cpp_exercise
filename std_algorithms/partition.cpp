// RUN: g++ -std=c++17 partition.cpp && ./a.out

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <forward_list>

using namespace std;

template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last) 
{
    if(first == last) return;
    auto pivot = *std::next(first, std::distance(first, last)/2);   // value: 6
    // cout << "pivot: " << pivot << endl;
    ForwardIt middle1 = std::partition(first, last, 
                                        [pivot](const auto& em){ return em < pivot; });
    // cout << "\nmiddle1 vector: ";
    // std::copy(first, middle1, std::ostream_iterator<int>(std::cout, " "));
    // std::cout << " * ";
    // std::copy(middle1, last, std::ostream_iterator<int>(std::cout, " "));

    ForwardIt middle2 = std::partition(middle1, last, 
                                        [pivot](const auto& em){ return !(pivot < em); });
    
    // cout << "\nmiddle2 vector: ";
    // std::copy(first, middle2, std::ostream_iterator<int>(std::cout, " "));
    // std::cout << " * ";
    // std::copy(middle2, last, std::ostream_iterator<int>(std::cout, " "));
    // // Debug                                    
    // cout << "\nFinal vector: ";
    // std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));

    quicksort(first, middle1);
    quicksort(middle2, last);
}

int main() {

    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "Original vector:\n    ";
    for(int elem : v) std::cout << elem << ' ';

    auto itr = std::partition(begin(v), end(v), [](int i){ return i % 2 == 0 ; });
    cout << "\nPartitioned vector:\n    ";
    std::copy(begin(v), itr, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " * ";
    std::copy(itr, end(v), std::ostream_iterator<int>(std::cout, " "));

    cout << "\nPartitioned vector: ";
    for(int elem : v) std::cout << elem << ' ';

    std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
    std::cout << "\nUnsorted list:\n    ";
    for(int n : fl) std::cout << n << ' ';
    std::cout << '\n'; 

    quicksort(begin(fl), end(fl));
    std::cout << "Sorted using quicksort:\n    ";
    for(int fi : fl) std::cout << fi << ' ';
    std::cout << '\n';

    return 0; 
}