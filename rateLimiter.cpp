// to design a rate limiter which can be extended with differnt rules
// will once load configs at start

// Entities:
// rateLimiter
// request


#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

class Request {
    string clientId;
public:
    Request(string id): clientId(id) {}
    string getClientId() { return clientId; }
};

class RateLimiter {
    public:
    virtual bool checkRequest(Request* req)= 0;
};

class Bucket{
    double currToken;
    time_t lastRefill;
    double capacity;
    double refillRate;
    void refill() {
        auto now = chrono::steady_clock::now();
        double diff = chrono::steady_clock::duration<double>(now - lastRefill).count() * refillRate;

        currToken = min(capacity, currToken + diff);
        lastRefill = chrono::system_clock::now();
    }
public:
    Bucket(double capacity, double rate){
        currToken = capacity;
        lastRefill = chrono::steady_clock::now();
        refillRate = rate;
    }
    bool consume(){
        if(currToken >= 1.0){
            currToken -= 1.0;
            return true;
        }
        return false;
    }
};

class TokenBucket: public RateLimiter {
    map<string, Bucket*> clientBukcetRecord;

    double capacity;
    double refillRate;
public:
    TokenBucket(double capacity, double rate): capacity(capacity), refillRate(rate) {}
    bool checkRequest(Request* req){
        Bucket* bucket = nullptr;
        string clientId = req->getClientId();
        if(clientBukcetRecord.find(clientId) == clientBukcetRecord.end()){
            Bucket* bucket = new Bucket(capacity, refillRate);
            clientBukcetRecord[clientId] = bucket;
        }

        bucket = clientBukcetRecord[clientId];
        return bucket->consume();
    }
};

int main(){
    
}