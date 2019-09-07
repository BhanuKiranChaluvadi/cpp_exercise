// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_mutex_3.cpp -pthread && ./a.out

/*
# DeadLock 2:
A second type of deadlock is a state in which two or more threads are blocked because 
each thread waits for the resource of the other thread to be released before releasing 
its resource. The result of the deadlock is a complete standstill. The thread and therefore 
usually the whole program is blocked forever.

ThreadA and ThreadB both require access to the console. 
Unfortunately, they request this resource which is protected by two mutexes in different order.

One way to avoid such a deadlock would be to number all resources and require that processes 
request resources only in strictly increasing (or decreasing) order. Please try to manually 
rearrange the locks and unlocks in a way that the deadlock does not occur and the following 
text is printed to the console

*/
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <algorithm>

std::mutex mutex1, mutex2;

void ThreadA() {
    // Creates beadloc problem
    mutex2.lock();
    std::cout << "Thread A"<< std::endl;
    mutex1.lock();
    mutex2.unlock();
    mutex1.unlock();
}

void ThreadB() {
    // Creates beadloc problem
    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    mutex1.lock();
    std::cout << "Thread B"<< std::endl;
    mutex2.lock();
    mutex1.unlock();
    mutex2.unlock();
}

void ExecuteThreads() {

    std::thread t1(ThreadA);
    std::thread t2(ThreadB);

    t1.join();
    t2.join();

    std::cout << "Finished" << std::endl;
}

int main() {

    ExecuteThreads();

    return 0;
}