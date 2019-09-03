// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_vs_tasks_2.cpp -pthread && ./a.out

/*
int nLoops = 1e7 , nThreads = 5 , std::launch::async (fastest)
int nLoops = 10, nThreads = 5;   -- std::launch::deferred (fastest)

An astounding difference to the asynchronous execution and a stark reminder 
that starting and managing threads takes a significant amount of time. 
It is therefore not a general advantage if computations are performed in parallel: 
It must be carefully weighed with regard to the computational effort 
whether parallelization makes sense.
*/

#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <chrono>


void workerFunction (int n) {
    // print system id of worker thread
    std::cout << "Worker thread id == " << std::this_thread::get_id() << std::endl;

    // perform work
    for (int i = 0; i < n; ++i) {
        sqrt(12345.6789);
    }

}

int main() {

    // print system id of main thread
    std::cout << "Main thread id == " << std::this_thread::get_id()<< std::endl;

    // start time measurement
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // launch various  tasks
    std::vector<std::future<void> > futures;
    int nLoops = 10, nThreads = 5;
    for (int i =0; i < nThreads; ++i) {
        futures.emplace_back (std::async(std::launch::async, workerFunction, nLoops));
    }

    // wait for the task to complete
    for (const auto &ftr : futures) {
        ftr.wait();
    }

    // stop time measurement and print execution time 
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds> ( t2 - t1).count();
    std::cout << "Execution finished after " << duration <<" microseconds" << std::endl;

    return 0;
}
