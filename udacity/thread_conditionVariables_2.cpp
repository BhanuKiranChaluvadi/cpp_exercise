// RUN: g++ -std=c++17 -Wall -Wextra -Wpedantic -Wunused thread_conditionVariables_2.cpp -pthread && ./a.out

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <queue>

template<class T>
class MessageQueue {
public:
    T receive() {
        // perform queue modification under the lock
        std::unique_lock<std::mutex> uLock(_mutex);
        // pass unique lock to condition variable
        _cond.wait(uLock, [this]{ return !_messages.empty(); });

        // remove the last vector element from the queue
        T msg = std::move(_messages.back());
        _messages.pop_back();

        return msg; // will not be copied due to return value optimization (RVO) in C++
    }

    void send (T &&msg) {
        // simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // perform vector modification under the lock.
        std::lock_guard<std::mutex> uLock(_mutex);
        std::cout << "   Message #" << msg << " will be added to the queue" << std::endl;
        _messages.push_back(std::move(msg));

        // notify client after pushing new Vehicle into vector
        _cond.notify_one();
    }

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _messages;
};

int main() {

    // create a monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<MessageQueue<int> > queue(new MessageQueue<int>);

    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void> > futures;
    for(int i = 0; i < 10; ++i) {
        int message = i;
        futures.emplace_back(std::async(std::launch::async, &MessageQueue<int>::send, queue, std::move(message)));
    }

    std::cout << "Collecting results..." << std::endl;
    while (true)
    {
       int message = queue->receive();
       std::cout << "   Message #" << message << " has been removed from the queue" << std::endl;
        
    }
    

    for(auto &ftr : futures)
        ftr.wait();

    return 0;
}
