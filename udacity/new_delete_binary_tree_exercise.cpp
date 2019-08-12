// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused new_delete_binary_tree_exercise.cpp && ./a.out
// cppcheck --enable=all ./new_delete_binary_tree_exercise.cpp

#include<iostream>

using namespace std;

class Binary_tree {

    struct Node {
        int data;
        Node *left;
        Node *right;
        Node(int data, Node *left, Node *right): data(data), left(left), right(right) {}
        ~Node() {
            if (left)
                delete left;
            if (right)
                delete right;
        }
    };

    Node *root;

    void add(int val, Node *ptr) {
        // TODO:
    }
    bool search(int item,  Node *ptr) {
        // TODO:
        return true;
    }

public:
    Binary_tree() {}
    ~Binary_tree() {
         delete root;
    }


private:



};


int main() {


    return 0;
}