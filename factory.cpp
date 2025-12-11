// Factory design pattern 

enum class VehicleType{
    bike, car, truck
};


class Vehicle{
public:
    string vehicleNo;
    VehicleType type;
    
    Vehicle(VehicleType vt, string no = ""): vehicleNo(no), type(vt){}
    
    string getVehicleNo(){ return vehicleNo; }
    VehicleType getVehicleType() { return type; }
    
    virtual void displayType() {
        cout<<" Vechicle type is: "<< type<<"\n";
    }
};

class Bike: public Vehicle{
public:
    Bike(string no = ""): Vehicle(VehicleType::bike, no){}
    void displayType(){
        cout<<"this is a bike, type:"<<type<<"\n";
    }
};

class Car: public Vehicle{
public:
    Car(string no= ""): Vehicle(VehicleType::car, no){}
    void displayType(){
        cout<<"this is a car, type:"<< type<<"\n";
    }
};

class VehicleFactory{
public:
    static Vehicle* createVehicle(VehicleType vt, string no= ""){
        switch(vt){
            case VehicleType::bike: return new Bike(no);
            case VehicleType::car : return new Car(no);
            default:
                cout<<"invalid vehicle"<<"\n";
                return nullptr;
        }
    }
};

// Type 2 Factory design pattern

class Vehicle{
    public:
    virtual void getVehicleType() =0;
};

class Car: public Vehicle{
    public:
    void getVehicleType(){
        cout<<"Vehicle is car\n";
    }
};

class Bike: public Vehicle{
    public:
    void getVehicleType(){
        cout<<"Vehicle is Bike\n";
    }
};

class VehicleFactory{
    public:
    static Vehicle* createVehicle(string type){
        if(type == "bike")
            return new Bike();
        else if (type == "Car")
            return new Car();
        else 
            return NULL;
    }
}