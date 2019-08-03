// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused std_move.cpp 

#include <iostream>

using namespace std;

class Move {
    size_t size;
    int* dataPtr;
public:
// default construuctor
explicit Move(int size) : size(size), dataPtr(new int[size]){
    cout << "Default constructor called !!" << endl;
}
// Destructor
~Move() {
    cout << "Destructor called !! "<< endl;
    if (dataPtr != nullptr)
        delete [] this->dataPtr;
}
// Copy Constructor
Move (const Move& other) : size(other.size), dataPtr(new int[other.size]) {
    cout << "Copy constructor called !! "<< endl;
    copy(other.dataPtr, other.dataPtr + other.size, dataPtr);   
}
// Copy Assignment
Move& operator = (const Move& other) {
    cout << "Copy Assignment constructor called !! " << endl;
    if(this != &other) {
        // Free the existing resource
        delete [] this->dataPtr;

        // Copy data
        this->size = other.size;
        this->dataPtr = new int[other.size];
        copy(other.dataPtr, other.dataPtr + other.size, this->dataPtr);
    }
    return *this;
}
// std::move constructor
Move(Move&& other): size(0), dataPtr(nullptr) {
    cout << "Move Constructor called !! " << endl;
    // Copy the data pointer and its length from the source object
    this->size = other.size;
    this->dataPtr = other.dataPtr;
    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times. 
    other.size = 0;
    other.dataPtr = nullptr;
}

// std::move assignmment operator
Move& operator = (Move&& other) {
    cout << "Move Assignment constructor called !! "<< endl;
    if(this != &other) {
        // Free the existing resource
        delete [] this->dataPtr;

        // Assign data
        this->size = other.size;
        this->dataPtr = other.dataPtr;

        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.size = 0;
        other.dataPtr = nullptr;
    }
    return *this;
}
// Get number of elements
size_t getSize() const {
    return this->size;
}
};

int main() {
    Move A(10);
    cout << "Size of A: " << A.getSize() << "\n";
    Move B(A);
    cout << "Size of B: " << B.getSize() << "\n";
    Move C = A;
    cout << "Size of C: " << C.getSize() << "\n";
    Move D(20);
    cout << "Size of D: " << D.getSize() << "\n";
    D = A;
    cout << "Size of D changed to : " << D.getSize() << "\n";
    cout << "" << endl;
    // std::move
    Move E(15);
    cout << "Size of E: " << E.getSize() << "\n";
    Move F(std::move(E));
    cout << "Size of F: " << F.getSize() << "\n";
    cout << "Size of E changed to: " << E.getSize() << "\n";
    cout << "" << endl;
    // Assignment
    Move G(5);
    cout << "Size of G: " << G.getSize() << "\n";
    Move H (25);
    cout << "Size of H: " << H.getSize() << "\n";
    H = move(G);
    cout << "Size of G changed to: " << G.getSize() << "\n";
    cout << "Size of H changed to: " << H.getSize() << "\n";

    // Move B(std::move(A));
    // cout << "Size of A: " << A.getSize() << "\n";
    cout << "" << endl;
    return 0;
}
