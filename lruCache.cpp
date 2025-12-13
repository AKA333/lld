#include <bits/stdc++.h>
#include <list>
#include <mutex>
#include <string>
#include <unordered_map>
#include "mutex"
#include "condition_variable"
#include "thread"

using namespace std;

class LruCache{
    // Methods: get(key), put(key, value)
    mutex mu;
    int sz;
    list<string> ls;
    unordered_map<string, pair<string, list<string>::iterator> > mp;
    public:
    LruCache(int capacity): sz(capacity){}
    void put(string key, string value){
        lock_guard<mutex> lock(mu);
        if(mp.find(key)!= mp.end()){
            ls.erase(mp[key].second);
            ls.push_front(key);
            mp[key] = {value, ls.begin()};
            return;
        }
        while(ls.size()>=sz){
            string t= ls.back();
            auto it= mp[t];
            mp.erase(t);
            ls.pop_back();
        }
        ls.push_front(key);
        mp[key] = {value, ls.begin()};
    }
    
    string get(string key){
        lock_guard<mutex> lock(mu);
        if(mp.find(key)== mp.end())
            return "null";
        auto t = mp[key];
        ls.erase(t.second);
        ls.push_front(key);
        mp[key] = {value, ls.begin()};
        
        return t.first;
    }  
};
