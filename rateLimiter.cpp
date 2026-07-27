// to design a rate limiter which can be extended with differnt rules
// will once load configs at start

// Entities:
// rateLimiter
// request


#include <chrono>
#include <ctime>
#include <ios>
#include <iostream>
#include <mutex>
#include <random>
#include <ratio>

using namespace std;

// lld design rate limiter

class Request {
    string reqId;
    string userId;
public:
    string getReqId() { return reqId; }
    string getUserId() { return userId; }
};

class RateLimiter{
public:
    virtual bool checkRequest(Request* req) = 0;
    virtual ~RateLimiter() = default;
};

class Bucket {
    double capacity;
    double refillRate;
    time_t lastRefillTime;
    double availableTokens;
    mutex bucketMutex;
public:
    Bucket(double size, double rate){
        capacity = size;
        refillRate= rate;
        lastRefillTime = chrono::steady_clock::now();
        availableTokens = capacity;
    }
    void refillTokens(){
        double elapsedSeconds = chrono::duration<double>(chrono::steady_clock::now() - lastRefillTime).count() * 1000.0
        double diff = elapsedSeconds * refillRate / 1000.0
        availableTokens = min(capacity, availableTokens + diff);
        lastRefillTime = chrono::steady_clock::now();
    }
    bool consumeToken(){
        unique_lock<mutex>lock(bucketMutex);
        refillTokens();
        if(availableTokens >= 1.0){
            availableTokens -= 1.0;
            return true;
        }
        return false;
    }

};

class TokenBucket: public RateLimiter {
    map<string, Bucket*> bukcetMap;
    double refillRate;
    double bucketCapacity;
    mutex mapMutex;
public:
    TokenBucket(double rate, double capacity): refillRate(rate), bucketCapacity(capacity) {}

    bool checkRequest(Request* req){
        Bucket* curr;
        string userId = req->getUserId();
        unique_lock<mutex>lock(mapMutex);
        auto it = bukcetMap.find(userId);
        if(it==bukcetMap.end()){
            curr = new Bucket(bucketCapacity, refillRate);
            bukcetMap[userId] =curr;
        }
        else{
            curr = it->second;
        }
        return curr->consumeToken();
    }
};

int main(){
    
}



// #include <bits/stdc++.h>
// #include <chrono>
// #include <ctime>
// #include <string>

// using namespace std;

// class Request {
//     string clientId;
// public:
//     Request(string id): clientId(id) {}
//     string getClientId() { return clientId; }
// };

// class RateLimiter {
//     public:
//     virtual bool checkRequest(Request* req)= 0;
// };

// class Bucket{
//     double currToken;
//     time_t lastRefill;
//     double capacity;
//     double refillRate;
//     void refill() {
//         auto now = chrono::steady_clock::now();
//         double diff = chrono::steady_clock::duration<double>(now - lastRefill).count() * refillRate;

//         currToken = min(capacity, currToken + diff);
//         lastRefill = chrono::system_clock::now();
//     }
// public:
//     Bucket(double capacity, double rate){
//         currToken = capacity;
//         lastRefill = chrono::steady_clock::now();
//         refillRate = rate;
//     }
//     bool consume(){
//         if(currToken >= 1.0){
//             currToken -= 1.0;
//             return true;
//         }
//         return false;
//     }
// };

// class TokenBucket: public RateLimiter {
//     map<string, Bucket*> clientBukcetRecord;

//     double capacity;
//     double refillRate;
// public:
//     TokenBucket(double capacity, double rate): capacity(capacity), refillRate(rate) {}
//     bool checkRequest(Request* req){
//         Bucket* bucket = nullptr;
//         string clientId = req->getClientId();
//         if(clientBukcetRecord.find(clientId) == clientBukcetRecord.end()){
//             Bucket* bucket = new Bucket(capacity, refillRate);
//             clientBukcetRecord[clientId] = bucket;
//         }

//         bucket = clientBukcetRecord[clientId];
//         return bucket->consume();
//     }
// };

// int main(){
    
// }


