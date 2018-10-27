#include "inheritance.h"


//###############  ABC  ###########
Rentals::Rentals() : id(0), isAvailable(0), needsService(0), rate(0), intersection(0) {}

Rentals::Rentals(int newId, bool available, bool service, float setRate, char address[]) : id(newId), isAvailable(available), needsService(service), rate(setRate) {

	intersection = new char[strlen(address) + 1];
	strcpy(intersection, address);
}

Rentals::Rentals(const Rentals& otherRental) : id(otherRental.id), isAvailable(otherRental.isAvailable)
{
	// didnt want the initialization list too long, but they could have gone up there too
	needsService =  otherRental.needsService;
	rate = otherRental.rate;

	intersection = new char[strlen(otherRental.intersection) + 1];
	strcpy(intersection, otherRental.intersection);
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

	return(0);
}


float Rentals::totalRevenue(){
return(0);
}

float Rentals::earningsPerServiceOfRentals(){
return(0);
}
void Rentals::print() const{
	cout << "ID: " << id << endl
		 << "Rate: " << rate << endl;
	if(2)
		cout  << "Located at: " << intersection << endl;
	if(1)
		cout << "Currently in unavilable" << endl;
	if(0)
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
Scooter::Scooter(int newId, bool available, bool service, char intersections[50]) : Rentals(newId, available, service, 5.0, intersections) {
	batteryLevel = 100.0;
}
	

void Scooter::print() const{
	// HMMMM if the base class is a pure virtual then this wont work.
	cout << "\nScooter \n";
	Rentals::print();
	cout << "Battery Level: " << batteryLevel << endl;
}








//    ###########   VEHICLE    ################

Vehicle::Vehicle() : licensePlate(0), gasLevel(0), seats(0)
{ }

Vehicle::Vehicle(int newId, bool available, bool service, float rate, char address[], char plates[], float gas, int numSeats) : Rentals(newId, available, service, rate, address) {
	licensePlate = new char[strlen(plates) + 1];
	strcpy(licensePlate, plates);
	gasLevel =  gas;
	seats = numSeats;
	
}

Vehicle::Vehicle(const Vehicle& otherVehicle) : Rentals(otherVehicle) {
	licensePlate = new char[strlen(otherVehicle.licensePlate) + 1];
	strcpy(licensePlate, otherVehicle.licensePlate);
	gasLevel = otherVehicle.gasLevel;
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

Zip_Car::Zip_Car(int newId, bool available, bool service, char intersections[50], char plates[]) : Vehicle(newId, available, service, 25.0, intersections, plates, 100.00, 4) 
{ }

Zip_Car::Zip_Car(const Zip_Car& otherZipCar) : Vehicle(otherZipCar)
{ }

void Zip_Car::print() const{
}





//        ******* LIMO ********
Limo::Limo() : driverName(0), reservedHours(0)
{ }

Limo::Limo(const Limo& otherLimo) : Vehicle(otherLimo){
	driverName = new char[strlen(otherLimo.driverName) + 1];
	strcpy(driverName, otherLimo.driverName);
	reservedHours = otherLimo.reservedHours;
}

Limo::Limo(int newId, bool available, bool service, char intersections[50], char plates[], char name[], int hours) : Vehicle(newId, available, service, 25.0, intersections, plates, 100.00, 10) 
{
	driverName = new char[strlen(name) + 1];
	strcpy(driverName, name);
	reservedHours = hours;
	
}

void Limo::print() const{

}
