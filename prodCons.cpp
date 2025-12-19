// Implementation for producer consumer problem
// It can be stuck in a hanging state or starvation when consumer is
// looking to consume without being produced by consumer
// Given a fixed size buffer or queue where producer produces
// And is consumed by the consumer until the end condition
// The producer wait when queue is full and consumer waits or block
// when the queue is empty
//
// What cv.notify_one() Actually Does
// cv.notify_one() only signals that a waiting thread can wake up — it does NOT:

// ✅ Force the other thread to run immediately
// ✅ Preempt the current thread
// ✅ Guarantee the other thread runs next
// The current thread continues running until:

// It releases the mutex (when unique_lock goes out of scope), AND
// The OS scheduler decides to switch to the other thread

#include <bits/stdc++.h>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include "condition_variable"
using namespace std;

class ProducerConsumer {
    queue<int>q;
    int capacity;
    int maxLimit;
    int counter = 1;

    mutex mu;
    condition_variable cv;
    public:
    ProducerConsumer(int cap, int M): capacity(cap), maxLimit(M){}
    void prod(){
        while(true){
            unique_lock<mutex> lock(mu);
            cv.wait(lock, [&](){
                return q.size() < capacity || counter > maxLimit;
            });

            if(counter > maxLimit){
                cv.notify_all();
                break;
            }
            cout<<"prod: "<<counter<<"\n";
            q.push(counter);

            counter++;
            cv.notify_one();
        }
    }

    void cons(){
        while(true){
            unique_lock<mutex>lock(mu);
            cv.wait(lock, [&](){
                return !q.empty() || counter > maxLimit;
            });

            if (q.empty() && counter > maxLimit)
                break;

            if(!q.empty()){
                cout<<"cons: "<<q.front() <<"\n";
                q.pop();
                cv.notify_one();
            }

        }
    }
};

int main(){
    ProducerConsumer obj(3, 10);
    thread t1(&ProducerConsumer::prod, &obj);

    thread t2(&ProducerConsumer::cons, &obj);

    t1.join();
    t2.join();

    return 0;
}

// Output-
// prod: 1
// prod: 2
// prod: 3
// cons: 1
// cons: 2
// cons: 3
// prod: 4
// prod: 5
// prod: 6
// cons: 4
// cons: 5
// cons: 6
// prod: 7
// prod: 8
// prod: 9
// cons: 7
// cons: 8
// cons: 9
// prod: 10
// cons: 10
