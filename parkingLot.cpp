// parking lot design

enum class VehicleType{
	bike, car, truck
};

class Vehicle{
public:
	VehicleType type;
	string regNo;
	Vehicle (VehicleType t, string reg): type(t), regNo(reg) {}
};

class ParkingSpot{
	VehicleType type;
	string spotId;
	bool isAvailable;
	Vehicle* parkedVehicle;
public:
	ParkingSpot(VehicleType type, string id)
		: type(type), spotId(id), isAvailable(true), parkedVehicle(nullptr) {}
	
	bool isAvailable(){
		return isAvailable;
	}
	VehicleType getSpotType(){
		return type;
	}
	bool parkVehicle(Vehicle* vehicle){
		if(!isAvailable || !canFit(vehicle))
				return false;
		parkedVehicle = vehicle;
		isAvailable = false;
		return true;
	}
	Vehicle unparkVehicle(){
		Vehicle* temp = vehicle;
		
	}

private:
	bool canFit(Vehicle* vehicle){
		if(!vehicle)
				return false;
		VehicleType type= vehicle->type();
		switch(type){
			case Vehicle::bike:
				return type == Vehicle::bike;
			case Vehicle::car:
				return type == Vehicle::car || type == Vehicle::truck;
			case Vehicle::truck:
				return type == Vehicle::truck;
			default:
				return false;
		}
	}
};

class Floor{
	int small, mid, large;
	int floorId;
public:
	Floor(id, small, mid, large){floorId: id, small: small, mid: mid, large:large}
	int getFloorId(){
		return floorId;
	}
};

class ParkingLot{
	vector<Floor>parking;
public:
	bool isParkingSpotAvailable(Vehicle veh){

	}

};