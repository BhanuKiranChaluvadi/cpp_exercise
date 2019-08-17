// RUN: g++ -g -std=c++17 -Wall -Wextra -Wpedantic -Wunused smart_pointer.cpp && ./a.out
// cppcheck --enable=all ./smart_pointer.cpp 

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class testUnique {
    unique_ptr<int> ptr;

public:
    testUnique(int val) : ptr(new int(val)) {
        cout << "constructor called !! " << endl;
    }
    testUnique() : ptr(new int(0)) {}
    // copy constructor overloading.
    testUnique(const testUnique& other) : ptr(new int(other.getAttr())) {
        cout << "copy constructor called !! " << endl;
    }
    // getter:
    int getAttr() const {
        return *ptr;
    }

    ~testUnique() {
        cout << "Destructor called !!" << endl;
    }
};

int main() {

    vector<shared_ptr<testUnique> > container;

    container.push_back(make_shared<testUnique> (testUnique(2)));
    container.push_back(make_shared<testUnique> (testUnique(52)));

    make_shared<testUnique> (testUnique(100));

    for(uint i=0; i < container.size(); i++)
        cout << &container[i] <<  " " << container[i] << " " << (*container[i]).getAttr() << endl;

    return 0;
}