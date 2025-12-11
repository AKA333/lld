// Singleton design pattern implementation
#include <cstddef>
#include <locale>
class singleton{
    static singleton *obj;
    singleton(){} 
    singleton(singleton&) = delete;
    singleton& operator = (const singleton&) = delete;
public:
    static singleton* getObj(){
        if(obj== nullptr)
            obj= new singleton();
        return obj;
    }
};

singleton* singleton::obj = nullptr;

// Or thread safe version
class singleton{
  singleton obj;
public:
static singleton& getObj(){
    // after c++11 this ensures there is only one thread assiging this static obj
    static singleton obj; 
    return obj;
}
singleton (const singleton&)= delete;
singleton operator= (const singleton&) = delete;
};

// Factory design pattern
// Multiple objects from a single factory

class Vehicle{
    protected:
    string type;
    public:
    Vehicle(string type= "na"):type(type) {}
    virtual void setWheels() = 0;
    virtual ~Vehicle() = default; // must when we are using virtual method
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
        if (type == "car")
            obj= new Car("Car");
        else if (type == "Truck")
            obj = new Truck("Truck");
        else 
            obj = new Car("Car");
        return obj;
    }
};

int main(){
    Vehicle* myCar = VehicleFactory::getVehicle("Car");
    myCar->setWheels();
    
    Vehicle* myTruck= VehicleFactory::getVehicle("Truck");
    myTruck->setWheels();
    
    return 0;
}