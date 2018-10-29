#include "inheritance.h"


//###############  ABC  ###########
Rentals::Rentals() : id(0), isAvailable(0), isRented(0), rate(0), intersection(0) {}

Rentals::Rentals(int newId, bool available, bool rented, float setRate, char address[]) : id(newId), isAvailable(available), isRented(rented), rate(setRate) {

	intersection = new char[strlen(address) + 1];
	strcpy(intersection, address);
}

Rentals::Rentals(const Rentals& otherRental) : id(otherRental.id), isAvailable(otherRental.isAvailable)
{
	// didnt want the initialization list too long, but they could have gone up there too
	isRented =  otherRental.isRented;
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
int Rentals::getId(){
	return(id);
}

void Rentals::setAvailability(bool state){
	isAvailable = state;
}

void Rentals::setRental(bool state){
	isRented = state;
}


// here is the "PURE VIRTUAL FUNCTION"
// making it a pure virtual function  requires the derived classes to implement them
// the ABC class is not required to implement it, but I wanted to use it from my derived classes so I did
//no client would be able to call this though
void Rentals::print() const{
	cout << "ID: " << id << endl
		 << "Rate: $" << rate << ".00 per hour" <<  endl
		 << "Located at: " << intersection << endl;
	if(isAvailable)
		if(!isRented)
			cout << "Ready to be rented" << endl;
		else 
			cout << "It is currently rented" << endl;
	else 
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
Scooter::Scooter(int newId, bool available, bool rented, char intersections[50]) : Rentals(newId, available, rented, 1.0, intersections) {
	batteryLevel = 100.0;
}
	

void Scooter::print() const{
	cout << "\nScooter \n";
	// Why implement the same print when I can just call the Base class's print
	Rentals::print();
	cout << "Battery Level: " << batteryLevel << endl;
}

void Scooter::returningScooter(int hours, bool repair, float currentCharge){
	hoursRented = hours;
	isAvailable = !repair;  // if it needs repairs then it is not available
	batteryLevel = currentCharge;
}











//    ###########   VEHICLE    ################

Vehicle::Vehicle() : licensePlate(0), gasLevel(0), seats(0)
{ }

Vehicle::Vehicle(int newId, bool available, bool rented, float rate, char address[], char plates[], float gas, int numSeats) : Rentals(newId, available, rented, rate, address) {
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

// again implementation not require but makes it easier if I do.
void Vehicle::returningVehicle(int hours, bool repair, float currentFuel, int rating){
	// since it doesn't have some of these it will look in its parent class for them
	hoursRented = hours;
	isAvailable = !repair;  // if it needs repairs then it is not available
	gasLevel = currentFuel;
}






//        ****** ZIP CAR ******* 

Zip_Car::Zip_Car() 
{ }

Zip_Car::Zip_Car(int newId, bool available, bool rented, char intersections[50], char plates[]) : Vehicle(newId, available, rented, 25.0, intersections, plates, 100.00, 4) 
{ }

Zip_Car::Zip_Car(const Zip_Car& otherZipCar) : Vehicle(otherZipCar)
{ }


void Zip_Car::print() const{
	cout << "\nZip Car: \n";
	Rentals::print();
	cout << "License plate: " << licensePlate << endl
		 << "Current gas Level: " << gasLevel << endl
		 << "Number of seats: " << seats << endl;

}

// Zip Car has no additional member so instead of listing all of its inherited members one by one 
// and updating their value, it is easier if its parent class just does it for it since the other 
// derived class will also need to do the same.
void Zip_Car::returningVehicle(int hours, bool repair, float currentFuel, int rating){
	Vehicle::returningVehicle(hours, repair, currentFuel, rating);
}




//        ******* LIMO ********
Limo::Limo() : driverName(0), reservedHours(0)
{ }

Limo::Limo(const Limo& otherLimo) : Vehicle(otherLimo){
	driverName = new char[strlen(otherLimo.driverName) + 1];
	strcpy(driverName, otherLimo.driverName);
	reservedHours = otherLimo.reservedHours;
}

Limo::Limo(int newId, bool available, bool rented, char intersections[50], char plates[], char name[], int hours) : Vehicle(newId, available, rented, 25.0, intersections, plates, 100.00, 10) 
{
	driverName = new char[strlen(name) + 1];
	strcpy(driverName, name);
	reservedHours = hours;
	
}

void Limo::print() const{

	cout << "\nLimo: \n";
	Rentals::print();
	cout << "The driver of this limo is: " << driverName << endl
		 << "License plate: " << licensePlate << endl
		 << "Current gas Level: " << gasLevel << endl
		 << "Number of seats: " << seats << endl
		 << "This limo is must be resereved for a minimum of " << reservedHours << " hours.\n";
}
// extractor operator overloaded just to print the name inline
ostream& operator<<(ostream& outObj, const Limo& limo){
	outObj << limo.driverName;
	return outObj;
}
void Limo::returningVehicle(int hours, bool repair, float currentFuel, int rated){
	// it's parent class takes care of its part and limo takes care of the rating.
	Vehicle::returningVehicle(hours, repair, currentFuel, rating);
	rating = rated; 
}
