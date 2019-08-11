// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused std_move.cpp 

#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

class Move {
    size_t size;
    int* dataPtr;
public:
// default construuctor
explicit Move(int size) : size(size), dataPtr(new int[size]){
    cout << "Default constructor called of size: !!"  << this->size  << endl;
}
// Destructor
~Move() {
    cout << "Destructor called of size: !! " << this->size << endl;
    if (dataPtr != nullptr)
        delete [] this->dataPtr;
}
// Copy Constructor
Move (const Move& other) : size(other.size), dataPtr(new int[other.size]) {
    cout << "Copy constructor called of other size !! "  << other.size  << endl;
    copy(other.dataPtr, other.dataPtr + other.size, dataPtr);   
}
// Copy Assignment
Move& operator = (const Move& other) {
    cout << "Copy Assignment constructor called of other size !! " << other.size  << endl;
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
    cout << "Move Constructor called of other size !! " << other.size  << endl;
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
    cout << "Move Assignment constructor called of other size !! " << other.size << endl;
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
    Move D(15);
    cout << "Size of D: " << D.getSize() << "\n";
    D = A;
    cout << "Size of D changed to : " << D.getSize() << "\n";
    cout << "" << endl;
    // std::move
    Move E(20);
    cout << "Size of E: " << E.getSize() << "\n";
    Move F(std::move(E));
    cout << "Size of F: " << F.getSize() << "\n";
    cout << "Size of E changed to: " << E.getSize() << "\n";
    cout << "" << endl;
    // Assignment
    Move G(25);
    cout << "Size of G: " << G.getSize() << "\n";
    Move H (50);
    cout << "Size of H: " << H.getSize() << "\n";
    H = move(G);
    cout << "Size of G changed to: " << G.getSize() << "\n";
    cout << "Size of H changed to: " << H.getSize() << "\n";
    Move I = Move(99); // -------------> check
    cout << "Size of I: " << I.getSize() << "\n";
    cout << "" << endl;

    // vector
    cout << " XXXXXXXXXXXXXXXXXXX  Start of a vector !! XXXXXXXXXXXXXXXXXX" << endl;
    vector<Move> vec;
    vec.push_back(Move(100));
    cout << "" << endl;
    vec.push_back(Move(1000));
    cout << "  " << endl;
    vec.push_back(Move(10000));
    cout << "" << endl;
    // Insert a new element into the second position of the vector.
    // vec.insert(begin(vec)+1, Move(500));
    cout << " XXXXXXXXXXXXXXXXXXX  Second Start of a vector !! XXXXXXXXXXXXXXXXXX" << endl;
    vector<Move> vec2;
    vec2.emplace_back(111);
    cout << "  " << endl;
    vec2.emplace_back(1111);
    cout << "  " << endl;
    cout << "" << endl;
    return 0;
}
