#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Payment{
    public:
    virtual void pay(int) = 0;
    virtual ~Payment() = default;
};

class CreditCard: public Payment{
    int ccNum;
    public:
    CreditCard(int num) : ccNum(num){
        cout<<"registered cc num:"<<num<<"\n";
    }
    void pay(int amt){
        cout<<"Paid by CreditCard amt:"<< amt<<"\n";
    }
};

class Upi: public Payment{
    int upiId;
    public:
    Upi(int id): upiId(id){
        cout<<"registered with upiid:"<< id<<"\n";
    }
    void pay(int amt){
        cout<<"Paid by Upi amt:"<< amt<<"\n";
    }
};

class Cart{
    Payment* paymentStrategy = nullptr;
    public:
    void setStrategy (Payment* method){
        paymentStrategy = method;
    }

    void checkout(int amt){
        if (paymentStrategy){
            paymentStrategy->pay(amt);
        }
        else{
            cout<<"Payment failed"<<"\n";
        }
    }
};

int main(){
    Cart shoppingCart;

    CreditCard* cc= new CreditCard(1234);
    Upi* upi = new Upi(999);

    shoppingCart.setStrategy(upi);
    shoppingCart.checkout(500);

    shoppingCart.setStrategy(cc);
    shoppingCart.checkout(200);

    return 0;
}
