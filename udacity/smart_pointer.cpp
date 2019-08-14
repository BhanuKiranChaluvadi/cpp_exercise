// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused smart_pointer.cpp && ./a.out
// cppcheck --enable=all ./smart_pointer.cpp 

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class testUnique {
    unique_ptr<int> ptr;

public:
    testUnique(int val) : ptr(new int(val)) {}
    testUnique() : ptr(new int(0)) {}
    // getter:
    int getAttr() const {
        return *ptr;
    }
    // ~testUnique() {
    //     cout << "Destructed !!" << endl;
    // }
};

int main() {

    vector<shared_ptr<testUnique> > container;

    container.push_back(make_shared<testUnique> (testUnique(2)));
    container.push_back(make_shared<testUnique> (testUnique(52)));

    for(uint i=0; i < container.size(); i++)
        cout << &container[i] << " " << (*container[i]).getAttr() << endl;

    return 0;
}