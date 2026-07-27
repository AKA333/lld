#include <chrono>
#include <ctime>
#include <ios>
#include <iostream>
#include <mutex>
#include <random>
#include <ratio>
#include <string>

using namespace std;

// Builder Pattern

class Pizza {
    string crust;
    string sauce;
    vector<string>toppings;
public:
    void setCrust(string _crust) { crust = _crust; }
    void setSauce(string _sauce) { sauce = _sauce; }
    void addToppings(string _topping) { toppings.push_back(_topping); }

    void printPizza(){
        cout<<crust<<" "<<sauce<<"\n";
        for(auto &c: toppings){
            cout<<c<<" ";
        }
        cout<<"\n";
    }
};

class PizzaBuilder {
    Pizza* pizza= nullptr;
public:
    PizzaBuilder(){
        pizza = new Pizza();
    }
    PizzaBuilder* addCrust(string _crust){
        pizza->setCrust(_crust);
        return this;
    }
    PizzaBuilder* addSauce(string _sauce){
        pizza->setSauce(_sauce);
        return this;
    }

    PizzaBuilder* build(){
        Pizza* builtPizza = pizza;
        pizza = new Pizza();

        return builtPizza;
    }

    ~PizzaBuilder(){
        delete pizza;
    }
    
};

int main(){
    PizzaBuilder* builder = new PizzaBuilder();
    Pizza* myPizza = builder->addCrust("thin")->addSauce("tomato")->build();

    myPizza->printPizza();

    return 0;
}