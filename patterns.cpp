// Singleton pattern

class Singleton{
    Singleton() = default;
    public:
    static Singleton& getInstance(){
        static Singleton obj;
        return obj;
    }
    Singleton (Singleton&) = delete ;
    Singleton& operator = (Singleton& ) = delete;
};

int main(){
    Singleton& logger = Singleton::getInstance();
}

// Factory pattern
// 
class Vehicle{
    protected:
    string type;
    public:
    Vehicle(string type= "na"):type(type) {}
    virtual void setWheels() = 0;
    virtual ~Vehicle() = default;
};

class Car: public Vehicle{
    public:
    Car(string tp): Vehicle(tp) {}
    void setWheels(){
        cout<<"for "<<type<<" we have 4 wheels"<<"\n";
    }
};

class Truck: public Vehicle{
    public:
    Truck(string type): Vehicle(type){}
    void setWheels(){
        cout<<"for "<<type<<" we have 10 wheels"<<"\n";
    }
};

class VehicleFactory{
    public:
    static Vehicle* getVehicle(string type){
        Vehicle* obj;
        if (type == "Car")
            obj= new Car(type);
        else if (type == "Truck")
            obj = new Truck(type);
        else 
            obj = NULL;
        return obj;
    }
};

int main(){
    Vehicle* myCar = VehicleFactory::getVehicle("Car");
    if (myCar)
        myCar->setWheels();
    
    Vehicle* myTruck= VehicleFactory::getVehicle("Truck");
    if(myTruck)
        myTruck->setWheels();
    
    return 0;
}

// Observer Design Pattern

class Event{
    virtual void notify(string )= 0;
};

class Sub: public Event{
    int id;
    public:
    sub(int user_id): id(user_id){}
    void notify(string msg){
        cout<<"for userId "<< id << " msg:" <<msg<<"\n";
    }
};

class Pub{
    list<Sub*> subs;
    public:
    void registerUser(Sub* user){
        subs.push_back(user);
    }
    
    void unregisterUser(Sub* user){
        subs.remove(user);
    }
    
    void notify(string msg){
        for(sub: subs){
            sub->notify(msg);
        }
    }
};

// Strategy design pattern
//
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
    
    return 0;
}