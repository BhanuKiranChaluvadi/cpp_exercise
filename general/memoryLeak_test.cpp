// g++ -std=c++17 memoryLeak_test.cpp -pthread && ./a.out

#include <boost/circular_buffer.hpp>
#include <iostream>

struct MyObject {
    MyObject(int i) : _i(i) { std::cout << __FUNCTION__ << " _i=" << _i << "\n"; }
   ~MyObject()              { std::cout << __FUNCTION__ << " _i=" << _i << "\n"; }
   int _i;
};

int main() {
    using Ptr = std::unique_ptr<MyObject>;
    boost::circular_buffer<Ptr> cBuf(5);
    cBuf.push_back(std::make_unique<MyObject>(0)); // cBuf[0]
    cBuf.push_back(std::make_unique<MyObject>(1)); // cBuf[1]
    cBuf.push_back(std::make_unique<MyObject>(2)); // cBuf[2]
    cBuf.push_back(std::make_unique<MyObject>(3)); // cBuf[3]
    cBuf.push_back(std::make_unique<MyObject>(4)); // cBuf[4]

    std::cout << "Full, pushing extra\n";

    cBuf.push_back(std::make_unique<MyObject>(5)); // this will overwrite position 0

    std::cout << "Done\n";
}
