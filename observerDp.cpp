#include <bits/stdc++.h>
#include <list>
#include <string>
using namespace std;

class Observer {
    public:
    virtual void notify() = 0;
    virtual ~Observer() = default;
    virtual string getId() = 0;
};

class Subscribers: public Observer {
    string id;
    public:
    Subscribers(string id): id(id) {}
    string getId(){
        return id;
    }
    void notify(){
        cout<<"notified: "<<id<<"\n";
    }
};

class Publisher {
    list<Observer*> subs;
    public:
    void addSub(Observer* sub){
        subs.push_back(sub);
    }
    
    void notify(){
        for(auto & sub: subs){
            sub->notify();
        }
    }
    
    void removeSub(string id){
        for (auto it= subs.begin(); it != subs.end(); it++){
            if((*it)->getId()==id){
                subs.erase(it);
                return;
            }
        }
    }
};

int main(){
    Publisher pub;
    Subscribers s1("user1"), s2("user2");
    
    pub.addSub(&s1);
    pub.addSub(&s2);
    
    pub.notify();
    
    pub.removeSub("user2");
    pub.notify();
    
    return 0;
}

// output:
// notified: user1
// notified: user2
// notified: user1
