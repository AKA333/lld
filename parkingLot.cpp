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
		if(isAvailable)
			return nullptr;
		Vehicle* vehicle = parkedVehicle;
		parkedVehicle = nullptr;
		isAvailable= true;
		return vehicle;
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
	vector<ParkingSpot> spots;
public:
	Floor(int floorId, int small, int mid, int large): floorId(floorId), 
	small(small), ,mid(mid), large(large){
		int total= small+mid+large;
		int i=0;
		for(int i=0; i<total; i++){
			VehicleType type;
			switch(i){
			case i<small:
				type = VehicleType::bike;
			case i<mid and i>=small:
				type = VehicleType::car
			case i<large && i>=mid:
				type = VehicleType::truck;
			default:
				type= VehicleType::car;
			}

			ParkingSpot spot(type, genId(i));
			spots.push_back(spot);
		}
	}

	string genId(int i){
		return "f"+to_string(floorId)+to_string(i);
	}

	ParkingSpot isSpotAvailable(Vehicle vehicle){
		VehicleType type = vehicle.type;
		for(auto spot: spots){
			if(spot.type == type && spot.isAvailable()){
				return spot;
			}
		}
		return nullptr;
	}
};

class ParkingLot{
	vector<Floor>parking;
public:
	void addFloor(Floor floor){
		parking.push_back(floor)
	}

	bool parkVehicle(Vehicle* vehicle){
		if(!vehicle)
			return false;
		for(auto floor:parking){
			ParkingSpot vacantSpot= floor.isSpotAvailable(vehicle);
			if(vacantSpot){
				return vacantSpot.parkVehicle(vehicle);
			}
		}
		cout<<"no spot isAvailable\n";
		return false;

	}

	unparkVehicle(Vehicle vehicle){

	}

	void displayStatus(){

	}
};