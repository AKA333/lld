// Multithreadded program to alternatively print odd even upto a range
#include <bits/stdc++.h>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "mutex"
#include "condition_variable"

using namespace std;

class PrintOddEven{
    int range;
    std::mutex mu;
    std::condition_variable cv;
    bool flag= 1;
    int curr = 1;

    public:
    PrintOddEven(int n): range(n) {}

    void printOdd(){
        while(true){
            std::unique_lock<std::mutex> lock(mu);
            cv.wait(lock, [&](){
                return flag || curr > range;
            });
            if(curr > range)
                break;
            cout<<"odd: "<<curr<<"\n";
            curr++;

            flag = !flag;
            cv.notify_one();
        }
    }

    void printEven(){
        while(true){
            std::unique_lock<std::mutex> lock(mu);
            cv.wait(lock, [&](){
                return !flag || curr > range;
            });
            if(curr > range)
                break;
            cout<<"even: "<<curr<<"\n";
            curr++;

            flag = !flag;
            cv.notify_one();
        }
    }

};

int main(){
    PrintOddEven obj(10);
    thread t1 (&PrintOddEven::printOdd, &obj);
    thread t2 (&PrintOddEven::printEven, &obj);

    t1.join();
    t2.join();

    return 0;
}

// Output-
// odd: 1
// even: 2
// odd: 3
// even: 4
// odd: 5
// even: 6
// odd: 7
// even: 8
// odd: 9
// even: 10
