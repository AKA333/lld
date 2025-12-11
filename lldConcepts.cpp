// Abstraction - hide unnecessary implementation details
// reduces complexity, increases code reusability

// Abstract classes- cannot be instantiated
// Allows defining common behavior that subclasses must implement
// Prevent direct instantiation of base class

// Abstract class
class Vehicle{
protected: 
    string brand;
public:
    Vehicle(string b): brand(b){}
    virtual void start() = 0; // Pure virtual function
    virtual ~Vehicle() = default; // Virtual destructor
    // Vir Des needed when we try to delete base class pointer which has object of derived class
    void displayBrand(){
        cout<<"Brand:"<<brand<<endl;
    }
};

class Car: public Vehicle{
public:
    Car(string b): Vehicle(b){}
    void start(){
        cout<<"Car is starting\n";
    }
};

int main(){
    Vehicle* myCar= new Car("Ford");
    myCar->displayBrand();;
    myCar->start();
    return 0;
}

// Interfaces- contains only pure virtual functions

class Animal{
public:
    virtual ~Animal() = default;
    virtual void makeSound() = 0;
};

class Dog: public Animal{
public:
    void makeSound(){
        cout<<"Dog barks\n";
    }
};

class Cat : public Animal{
public:
    void makeSound(){
        cout<<"Cat meows\n";
    }
};

int main(){
    Animal* myDog= new Dog();
    Animal* myCat= new Cat();
    
    myDog->makeSound();
    myCat->makeSound();
}

// Real World Example: Payment system
class Payment{
    protected:
    double amount;
    public:
    Payment(double x): amount(x){}
    virtual ~Payment()= default; // Virtual destructor
    virtual void pay() =0; // Abstract method
};

class CreditCardPayment: public Payment{
public:
    CreditCardPayment(double x): Payment(x) {}
    void pay(){
        cout<< "paid amount: "<<amount<<"\n";
    }
};

int main(){
    Payment* payment= new CreditCardPayment(20);
    payment->pay(); // call to credit card def
}
