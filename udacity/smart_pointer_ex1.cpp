
// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused smart_pointer_ex1.cpp && ./a.out
// cppcheck --enable=all ./smart_pointer_ex1.cpp 


#include <iostream>
#include <memory>

using namespace std;


class MyClass {

public:
    MyClass() {}
    void classMethod() {
        cout << "MyClass::classMethod"<< endl;
    }
    // ~MyClass() {
    //     cout << "Destructor called. " << endl;
    // }
};


int main() {

    unique_ptr<MyClass>  ptr_1(new MyClass());
    ptr_1->classMethod();

    // return the memory address of ptr_1
    cout << ptr_1.get() << endl;

    // transfer ownership to ptr_2
    unique_ptr<MyClass> ptr_2(move(ptr_1));
    // unique_ptr<MyClass> ptr_2 = move(ptr_1);
    ptr_2->classMethod();
    cout << ptr_1.get() << endl;
    cout << ptr_2.get() << endl;

    // transfers ownership to ptr_3
    unique_ptr<MyClass> ptr_3 = move (ptr_2);
    ptr_3->classMethod();
    cout << ptr_1.get() << endl;
    cout << ptr_2.get() << endl;
    cout << ptr_3.get() << endl;

    return 0;
}