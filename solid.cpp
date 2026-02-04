 SOLID principles:
 s- Single responsibility
 o- open close relationship
 l- liskov substitution
 i- interface segregation principle
 d- dependency inversion


// Single responsibility:
// class Order {
//     int amount;
//     PaymentGateway* gatway;
//     public:
//     int getOrderValue(){ return amount; }
//     void processPayment() {
//         gatway->process(amount);
//     }
// };

// Always better to separate concerns
// class Order {
//     int amount;
//     public:
//     int getAmount(){ return amount; }
// };

// class Payment {
//     PaymentGateway* gateway;
//     public:
//     void process (Order* order) {
//         order->getAmount();
//     }
// };

// here we separated two different entities order and payment rather than having payment gateway in the order itself we separated this in a separate class handling payments


// Open closed relationship:
// open to extension but closed for modification as a tool box we can add more tools but restrict from modifying existing ones

// class Payment {
//     public:
//     virtual void pay(int amount ) = 0;
// };

// class Upi: public Payment {
//     public:

// };

// class CreditCard: public Payment {
//     public:

// };

// Liskov substitution: child and parent class obj should be replaceable or child class should implement parent class methods
// or derived classes must be replaceable with base class without breaking behavior

// class Bird {
//     public:
//     virtual void fly() = 0;
// };

// class Penguin: public Bird {
//     public:
//     void fly(){
//         // Error but penguins dont fly so these are not interchangable
//     }
// };

// class Bird {
//     public:
//     virtual void move() =0;
// };

// class Penguin : public Bird {
//     public:
//     void move (){

//     }
// };

// Interface segregation: should have separate interfaces for actions

// class Vehicle {
//     public:
//     virtual void setWheels() =0;
//     virtual void engine() = 0;
// };

// class Vehiclexterior {
//     public:
//     virtual void setWheels() =0;
// };

// class VehicleEngine {
//     public:
//     virtual void engine() =0;
// };

// class Car: public Vehiclexterior, public VehicleEngine {

// };
//
// Dependency invesion- higher level classed should not be dependent on lower level modules
// rather than should be calling interface
//

// class messageSender {
//     public:
//     virtual void sendMessage(string)  =0;
// };

// class email: public messageSender {
//     public:
//     void sendMessage(string message) {
//         cout<<"Message from email\n";
//     }
// };

// class text: public messageSender {
//     public:
//     void sendMessage(string message) {
//         cout<<"Message from test\n";
//     }
// };

// class Notification {
//     messageSender* message;
//     public:
//     Notification(messageSender* sender) : message(sender) {}
//     void notify(string msg){
//         message->sendMessage(msg);
//     }
// };
