#include <condition_variable>
#include <iostream>
#include <bits/stdc++.h>
#include <thread>

using namespace std;

// Simple thread
void func1(string msg, int c){
    c++;
    cout<< msg << " count:"<<c<<"\n";
}

int main(){
    int c=1;
    thread t1(func1,"func1", c);
    thread t2(func1, "func2", c);
    
    t1.join();
    t2.join();
    
    return 0;
}

// Mutex and lock guard
#include <iostream>
#include <bits/stdc++.h>
#include <thread>
#include <mutex>

using namespace std;

mutex mu;

void printMsg(string msg, int t){
    lock_guard<mutex> lock(mu);
    cout<< msg <<" " << t<<"\n"; 
    // this cout is a shared resource between main and thread t1
}

void func1(){
    for(int i=1 ;i<=5; i++)
        printMsg("from func1", i);
}


int main(){
    thread t1 (func1);
    
    for(int i=1; i<=5; i++)
        printMsg("from main", i);
        
    t1.join();
    
    return 0;
}

// lock guard and unique_lock
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class ThreadManager {
private:
    std::mutex mtx;
    int shared_counter = 0;
    
public:
    // Basic thread function with mutex protection
    void incrementCounter(int iterations) {
        for (int i = 0; i < iterations; ++i) {
            // std::lock_guard<std::mutex> lock(mtx);
            // unique_lock<mutex> lock(mtx);
            unique_lock<mutex> lock(mtx, defer_lock);
            
            lock.lock();
            ++shared_counter;
            
            mtx.unlock();
            // lock_guard automatically releases mutex when out of scope
        }
    }
    
    void demonstrateBasicThreads() {
        std::thread t1(&ThreadManager::incrementCounter, this, 1000);
        std::thread t2(&ThreadManager::incrementCounter, this, 1000);
        
        t1.join();
        t2.join();
        
        std::cout << "Final counter value: " << shared_counter << std::endl;
    }
};

// call_once
mutex mu;
std::once_flag flag;

class Singleton{
    static Singleton* obj;
    public:
    static Singleton* getInst(){
        std::call_once(flag, []() {
            obj = new Singleton();
        });
        return obj;
    }
}

class sync{
    mutex mu;
    condition_variable cv;
    queue<int>q;
    int c=1;
    
    void producer(){
        lock_guard<mutex> lock(mu);
        for(int i=1; i<=5; i++){
            q.push(c++);
        }
        cv.notify_all();
    }
    
    void consumer(){
        lock_guard<mutex> lock(mu);
        cv.wait(lock, [](){
            !return q.empty();
        });
        if(!q.empty()){
            int t= q.front();
            q.pop();
            cout<<"pop ele:"<<t<<"\n";
        }
    }
}

// *******************************************
#include <bits/stdc++.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mu;
condition_variable cv;

int c=0;
bool flag= 1;
void func1(){
    // lock_guard<mutex> lock(mu);
    unique_lock<mutex> lock(mu);
    cv.wait(lock, [&](){
        return flag; 
    });
    
    c++;
    cout<<"func1: "<<c<<"\n";
    flag = !flag;
    
    cv.notify_one();
}

void func2(){
    unique_lock<mutex> lock(mu);
    cv.wait(lock, [&](){
        return !flag; 
    });
    c++;
    cout<<"func2: "<<c<<"\n";
    flag = !flag;
    
    cv.notify_one();
}

void printEvenOdd(){
    while(c<=10){
        thread t1(func1);
        thread t2(func2);
    
        t1.join(); t2.join();
    }
}

int main()
{
    printEvenOdd();
    return 0;
}