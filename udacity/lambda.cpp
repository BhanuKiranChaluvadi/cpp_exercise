// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused lambda.cpp -pthread && ./a.out

/*
Lambdas have the properties of being unnamed and capturing variables 
from the surrounding context, but lack the ability to execute and return functions

A Lambda is a function object (a "functor"), so it has a type and can be stored and passed around. 
Its result object is called a "closure", which can be called using the operator ()

A lambda formally consists of three parts: a capture list [] , a parameter list () and a main part {}

By default, variables in the capture block can not be modified within the Lambda. 
Using the keyword "mutable" allows to modify the parameters captured by copy, 
and to call their non-const member functions within the body of the Lambda

Even though we have been using Lambdas in the above example in various ways, 
it is important to note that a Lambda does not exist at runtime. 
The runtime effect of a Lambda is the generation of an object, which is known as closure. 
The difference between a Lambda and the corresponding closure is similar 
to the distinction between a class and an instance of the class.
A class exists only in the source code while the objects created from it exist at runtime.

*/

#include <iostream>

int main() {

    // create lambdas
    int id = 0;     // Define an integer variable

    // auto f0 = [] () { std::cout << "ID = " << id << std::endl; }; // Error: 'id' cannot be accessed.

    id++;

    auto f1 = [id]() {std::cout << "ID = " << id << std::endl;}; // OK, 'id' is captured by value

    auto f2 = [&id]() {std::cout << "ID = " << ++id << std::endl;}; // OK, 'id' is captured by reference

    // auto f3 = [id](){std::cout << "ID = " << ++id << std::endl;};  // Error, 'id' may not be modified.

    auto f4 = [id] () mutable {std::cout << "ID = " << ++id << std::endl;}; // OK, 'id' may be modified

    std::cout << "One ID = " << id << std::endl; 

    // execute lambdas
    f1();
    f2();
    // f3();
    f4();

    std::cout << "Two ID = " << id << std::endl;

    auto f5 = [](const int id) { std::cout << "ID = " << id << std::endl; }; // ID is passed as a parameter

    // execute function object and pass the parameter
    f5(id);

    return 0;
}
