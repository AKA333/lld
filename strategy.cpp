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

// ****************************
// #include <iostream>
// #include <bits/stdc++.h>

// using namespace std;

// class Payment{
//     public:
//     virtual void pay(int amount) = 0;
// };

// class CC: public Payment {
//    public: 
//    CC () {}
//    void pay(int amount){
//        cout<<"paid by cc amount:"<<amount<<endl;
//    }
// };

// class Upi: public Payment {
//     public:
//     Upi() {}
//     void pay(int amount) {
//         cout << "paid by upi amount:"<< amount <<endl;
//     }
// };

// class Cart {
//     Payment *mode;
//     public:
//     Cart(){
//         mode = nullptr;
//     }
//     Payment* setStrategy(string method){
//         if(method == "CC")
//             mode = new CC();
//         else if (method == "Upi")
//             mode = new Upi();
//         return mode;
//     }
// };

// int main(){
//     Cart shoppingCart;
//     Payment* payment = shoppingCart.setStrategy("CC");
//     payment->pay(400);
    
//     payment = shoppingCart.setStrategy("Upi");
//     payment->pay(200);
    
//     payment = shoppingCart.setStrategy("CC");
//     payment->pay(1000);
    
//     return 0;
// }