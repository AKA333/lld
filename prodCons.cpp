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
#include <mutex>
#include <thread>
#include "mutex"
#include "condition_variable"

using namespace std;

class ProdCons{
    mutex mu;
    condition_variable cv;
    int size;
    queue<int>q;
    int curr=1;
    int range;
    public:
    ProdCons(int sz, int range): size(sz), range(range){}
    void producer(){
        while(true){
            unique_lock<mutex>lock(mu);
            cv.wait(lock, [&](){
                return q.size() < size || curr > range;
            });
            
            if(curr>range)
                break;
            cout<<"Producer curr:"<<curr<<"\n";
            q.push(curr);
            curr++;
            
            cv.notify_one();
        }
    }
    
    void consumer(){
        while(true){
            unique_lock<mutex>lock(mu);
            cv.wait(lock, [&](){
                return !q.empty() || curr>range;
            });
            
            if(curr > range && q.empty())
                break;
            if(!q.empty()){
                cout<<"Consumer curr:"<<q.front()<<"\n";
                q.pop();
                
                cv.notify_one();
            }
        }
    }
};

int main(){
    ProdCons obj(3, 10);
    thread t1(&ProdCons::producer, &obj);
    thread t2(&ProdCons::consumer, &obj);
    
    t1.join(); t2.join();
    
    return 0;
}

// Output- 
// Producer curr:1
// Producer curr:2
// Producer curr:3
// Consumer curr:1
// Consumer curr:2
// Consumer curr:3
// Producer curr:4
// Producer curr:5
// Producer curr:6
// Consumer curr:4
// Consumer curr:5
// Consumer curr:6
// Producer curr:7
// Producer curr:8
// Producer curr:9
// Consumer curr:7
// Consumer curr:8
// Consumer curr:9
// Producer curr:10
// Consumer curr:10