#include "inheritance.h"


//###############  ABC  ###########
Rentals::Rentals() : id(0), available(0), service(0), rate(0), intersection(0), state(0){}
Rentals::Rentals(int num, bool whatever){
	 char repair;
	 cout << "Please enter an ID number: ";
	 cin >> id;
	 cout << "\nDoes it need any repairs? (Y/N)";
	 cin >> repair;
	 repair = toupper(repair);
	 service = (repair == 'Y') ? true : false;
	 cout << "\nHow much will this prodcut be rented for? " ;
	 cin >> rate;
	cout << "\nWhere will this product be located? " ;	
}

Rentals::Rentals(const Rentals& otherRentals) : id(otherRentals.id), available(otherRentals.available)
{
	// didnt want the initialization list too long, but they could have gone up there too
	service =  otherRentals.service;
	rate = otherRentals.rate;

	intersection = new char[strlen(otherRentals.intersection) + 1];
	strcpy(intersection, otherRentals.intersection);
}
Rentals::~Rentals(){
	if(intersection){
		delete [] intersection;
		intersection = NULL;
	}
}

int Rentals::servicing(Rentals* brokenRentals){
	return(0);
}

float Rentals::hoursUsed(){

}


float Rentals::totalRevenue(){
return(0);
}

float Rentals::earningsPerServiceOfRentals(){
return(0);
}
void Rentals::print() const{
	cout << "ID: " << id
		 << "Rate: " << rate;
	if(state == 2)
		cout  << "Located at: " << intersection << endl;
	if(state == 1)
		cout << "Currently in unavilable" << endl;
	if(state == 0)
		cout << "Out of Service" << endl;
}





// ************   DERIVED  CLASSES  *************

//       $$$$    SCOOTER    $$$$
// the base class constructor is not required as it is automatically invoked
Scooter::Scooter() : Rentals() {
	batteryLevel = 0.0;
}
Scooter::Scooter(const Scooter& newScooter) : Rentals(newScooter){
	batteryLevel = newScooter.batteryLevel;
}

void Scooter::print() const{
	// HMMMM if the base class is a pure virtual then this wont work.
	cout << "Scooter \n";
	Rentals::print();
	cout << "Battery Level: " << batteryLevel << endl;
}








//    ###########   VEHICLE    ################

Vehicle::Vehicle() : licensePlate(0), gasLevel(0), returnedFull(0), seats(0)
{ }


Vehicle::Vehicle(const Vehicle& otherVehicle) : Rentals(otherVehicle) {
	licensePlate = new char[strlen(otherVehicle.licensePlate) + 1];
	strcpy(licensePlate, otherVehicle.licensePlate);
	gasLevel = otherVehicle.gasLevel;
	returnedFull = otherVehicle.returnedFull;
	seats = seats;
}

Vehicle::~Vehicle(){
	if(licensePlate){
		delete [] licensePlate;
		licensePlate = NULL;
	}
}

//        ****** ZIP CAR ******* 

Zip_Car::Zip_Car() 
{ }

Zip_Car::Zip_Car(const Zip_Car& otherZipCar) : Vehicle(otherZipCar)
{ }

void Zip_Car::print() const{
}





//        ******* LIMO ********
Limo::Limo() : driverName(0), minimumRentalHours(0)
{ }

Limo::Limo(const Limo& otherLimo) : Vehicle(otherLimo){
	driverName = new char[strlen(otherLimo.driverName) + 1];
	strcpy(driverName, otherLimo.driverName);
	minimumRentalHours = otherLimo.minimumRentalHours;
}
void Limo::print() const{

}
