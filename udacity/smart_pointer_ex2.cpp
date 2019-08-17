// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused smart_pointer_ex2.cpp && ./a.out
// cppcheck --enable=all ./smart_pointer_ex2.cpp 

#include <iostream>
#include <memory>

using namespace std;

class MyClass {

public:
    MyClass() {}
    void classMethod() {
        cout << "MyClass::classMethod"<< endl;
    }
};

int main() {

    shared_ptr<MyClass> ptr_1(new MyClass());
    cout << ptr_1.get() << endl;

    shared_ptr<MyClass> ptr_2(ptr_1);
    cout << ptr_1.get() << endl;
    cout << ptr_2.get() << endl;
    
    // Returns the number of shared_ptr objects 
    //referring to the same managed object.
    cout << ptr_1.use_count() << endl;
    cout << ptr_2.use_count() << endl;

    // Relinquishes ownership of ptr_1 on the object
    // and the pointer becomes NULL
    ptr_1.reset();
    cout << ptr_1.get() << endl;
    cout << ptr_2.use_count() << endl;
    cout << ptr_2.get() << endl;

    return 0;
}