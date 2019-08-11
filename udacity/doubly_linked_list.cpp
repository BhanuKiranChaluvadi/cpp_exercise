// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused doubly_linked_list.cpp 
// cppcheck --enable=all ./doubly_linked_list.cpp 

/*
------------------------------------------------
|  Node  |  Node  |  Node  |                   
------------------------------------------------
List

-------------------------------------------
| previos Node ptr | T  | next Node ptr   |
-------------------------------------------

 */

#include<iostream>
#include <assert.h>

using namespace std;


template<class T> class List {
public:
    List() :  head_(nullptr), tail_(nullptr) {}
    ~List() ;
    void PushFront(T);
    void PushBack(T);
    T PopBack();
    T PopFront();

    bool Empty() const {return (head_ == nullptr);}
    int Size() const;

private:
    struct Node
    {   
        T value;
        Node *previous;
        Node *next;
        Node(T val, Node *previous, Node *next)
            : value(val), previous(previous), next(next) {}
    };

    Node *head_;
    Node *tail_;
};

// Destructor
template<class T> List<T>::~List() {
    while(this->head_) {
        Node *temp(this->head_);      // use copy constructor -- can use std::move in future
        this->head_ = this->head_->next;    // update head
        delete temp;           // delete the Node that is no longer in List.
    }
}

template<class T> void List<T>::PushFront(T val) {
    this->head_ = new Node(val, nullptr, this->head_);
    // Handle first element insertion or not
    if(this->tail_ == nullptr){
        this->tail_ = this->head_;
    } else {
        this->head_->next->previous = this->head_;
    }
}

template<class T> void List<T>::PushBack(T val) {
    this->tail_ = new Node(val, this->tail_, nullptr);
    
    if (this->head_ == nullptr) {       // First element insertion
        this->head_ = this->tail_;
    } else {                            // already has elements
        this->tail_->previous->next = this->tail_;    
    }
}

template<class T> T List<T>::PopFront() {
    if(List::Empty()){
        throw("Cannot List::PopBack() when List::Empty()");
    }
    Node *temp(this->head_);
    T value = (this->head_->value);
    this->head_ = this->head_->next;
    if(this->head_ == nullptr) {
        this->tail_ = nullptr;
    } else {
        this->head_->previous = nullptr;
    }
    delete temp;
    return value;
}

template <class T> T List<T>::PopBack() {
    if(List::Empty()){
        throw("Cannot List::PopBack() when List::Empty()");
    }
    Node *temp(this->tail_);
    T value = (this->tail_->value);
    this->tail_ = this->tail_->previous;
    if(this->tail_ == nullptr) {
        this->head_ = nullptr;
    } else {
        this->tail_->next = nullptr;
    }
    delete temp;
    return value;  
}

template<class T> int List<T>::Size() const {
    int size = 0;
    Node *temp(this->head_);
    if(temp != nullptr) {
        size++;
        temp = temp->next;
    }
    return size;
}

int main() {
    // Sanity test
    List<int> list1;
    list1.PushBack(9);
    assert(list1.Size() == 1);

    // Deeper test
    List<int> list2;
    list2.PushFront(9);
    list2.PushBack(10);
    assert(list2.Size() == 2);
    assert(list2.PopBack() == 10);
    assert(list2.PopFront() == 9);
    assert(list2.Size() == 0);

    return 0;
}




