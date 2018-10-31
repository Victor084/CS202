/*
   inheritance.cpp
   Victor Heredia
   CS202 - 10/29/18
   this file implements all the prototypes of the header file
 */
#include "inheritance.h"


//###############  ABC  ###########
// default constructor
Rentals::Rentals() : id(0), isAvailable(0), isRented(0), rate(0), intersection(0), hoursRented(0) {}
// parameterized constructor to initialize all the data members
Rentals::Rentals(int newId, bool available, bool rented, float setRate, char address[], int hours) : id(newId), isAvailable(available), isRented(rented), rate(setRate), hoursRented(hours) {

	intersection = new char[strlen(address) + 1];
	strcpy(intersection, address);
}
// copy constructor
Rentals::Rentals(const Rentals& otherRental) : id(otherRental.id), isAvailable(otherRental.isAvailable)
{
	// didnt want the initialization list too long, but they could have gone up there too
	isRented =  otherRental.isRented;
	rate = otherRental.rate;

	intersection = new char[strlen(otherRental.intersection) + 1];
	strcpy(intersection, otherRental.intersection);
	hoursRented = otherRental.hoursRented;
}
Rentals::~Rentals(){
	if(intersection){
		delete [] intersection;
		intersection = NULL;
	}
}
// functions that were not implemented in time
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
// just virtual functions that the derived classes will use
void Rentals::returningScooter(int rentedHours, bool repair, float batteryLevel) { }
void Rentals::returningVehicle(int hours, bool repair, float currentFuel, int rating){ }
void Rentals::earningsSinceLastRepair() { };
void Rentals::printDriversName(){ };
//getter for the list class to use for comparison
int Rentals::getId(){
	return(id);
}
//getter for the list class to use for comparison
bool Rentals::isItAvailable(){
	return(isAvailable);
}
// setters to update when checking in a product
void Rentals::setAvailability(bool state){
	isAvailable = state;
}
// setters to update when checking in a product
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
// scooters copy constructor so it may be passed in as an argument
//call the base class copy constructor's
Scooter::Scooter(const Scooter& newScooter) : Rentals(newScooter){
	batteryLevel = newScooter.batteryLevel;
}
// parameterized constructor to initialized the data members and it kicks it up to the base class for it to do its thing before Scooter gets them.
Scooter::Scooter(int newId, bool available, bool rented, char intersections[]) : Rentals(newId, available, rented, 1.0, intersections) {
	batteryLevel = 100.0;
}

//The Scooter class invokes the base class pure virtual function which we actually implemented
void Scooter::print() const{
	cout << "\nScooter \n";
	// Why implement the same print when I can just call the Base class's print
	Rentals::print();// this was implemented
	cout << "Battery Level: " << batteryLevel << endl;
}

//update the scooter variables once it has been return to the shop, tac on the additional hours since last repair
void Scooter::returningScooter(int hours, bool repair, float currentCharge){
	hoursRented += hours; // this adds on the hours since last repair
	isAvailable = !repair;  // if it needs repairs then it is not available
	batteryLevel = 100.0;   // we charge all baterries before renting to another customer
	//batteryLevel = currentCharge;
}
//calculate the earnings since last repair
void Scooter::earningsSinceLastRepair(){
	cout << "\nThis Scooter has been used for " << hoursRented << " hours since its last repair.\n"
		<< "It has earned the company $" << rate * hoursRented << ".00 in that time." << endl;
}












//    ###########   VEHICLE    ################
// default constructor
Vehicle::Vehicle() : licensePlate(0), gasLevel(0), seats(0)
{ }
// this constructor initialies all the data members including the base class members
Vehicle::Vehicle(int newId, bool available, bool rented, float rate, char address[], char plates[], float gas, int numSeats) : Rentals(newId, available, rented, rate, address) {
	licensePlate = new char[strlen(plates) + 1];
	strcpy(licensePlate, plates);
	gasLevel =  gas;
	seats = numSeats;

}
// the copy constructor for the Vehicle class
// it invokes the base class copy constructor before doing its work
Vehicle::Vehicle(const Vehicle& otherVehicle) : Rentals(otherVehicle) {
	licensePlate = new char[strlen(otherVehicle.licensePlate) + 1];
	strcpy(licensePlate, otherVehicle.licensePlate);
	gasLevel = otherVehicle.gasLevel;
	seats = seats;
}
// desturctor
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

// default constructor
Zip_Car::Zip_Car() 
{ }
// this initialzes all the data members
Zip_Car::Zip_Car(int newId, bool available, bool rented, char intersections[50], char plates[]) : Vehicle(newId, available, rented, 25.0, intersections, plates, 100.00, 4) 
{ }

// the copy constructor for Zip Car  we really dont need it because it doesnt manage any dynamic memory, but it already has so little things as its memebrs :-(
Zip_Car::Zip_Car(const Zip_Car& otherZipCar) : Vehicle(otherZipCar)
{ }


// print the Zip car info and it is const because it wont be modifying anything
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

// earning since last reapir the hours checked out were just tallied together
void Zip_Car::earningsSinceLastRepair(){
	cout << "\nThis Zip Car has been used for " << hoursRented << " hours since its last repair.\n"
		<< "It has earned the company $" << rate * hoursRented << ".00 in that time." << endl;
}







//        ******* LIMO ********
// default constructor
Limo::Limo() : driverName(0), reservedHours(0)
{ }

// copy constructor
Limo::Limo(const Limo& otherLimo) : Vehicle(otherLimo){
	driverName = new char[strlen(otherLimo.driverName) + 1];
	strcpy(driverName, otherLimo.driverName);
	reservedHours = otherLimo.reservedHours;
}

//destructor
Limo::~Limo(){
	if(driverName){
		delete [] driverName;
		driverName = NULL;
	}
}

// initialies every data member and its base class too because it needs it all
Limo::Limo(int newId, bool available, bool rented, char intersections[50], char plates[], char name[], int hours) : Vehicle(newId, available, rented, 25.0, intersections, plates, 100.00, 10) 
{
	driverName = new char[strlen(name) + 1];
	strcpy(driverName, name);
	reservedHours = hours;

}

// const becuase it doesnt modify anything
void Limo::print() const{

	cout << "\nLimo: \n";
	Rentals::print();// we implemented the pure virtual so lets use it!
	cout << "The driver of this limo is: " << driverName << endl
		<< "License plate: " << licensePlate << endl
		<< "Current gas Level: " << gasLevel << endl
		<< "Number of seats: " << seats << endl
		<< "This limo is must be resereved for a minimum of " << reservedHours << " hours.\n";
}
// extractor operator overloaded just to print the name inline
// this was fully implemented operator << overloading but my list class couldnt implement it correctly
ostream& operator<<(ostream& outObj, const Limo& limo){
	outObj << limo.driverName;
	return outObj;
}
//just print the drivers name
void Limo::printDriversName(){
	cout << driverName;
}
// update the data members after bering returned
void Limo::returningVehicle(int hours, bool repair, float currentFuel, int rated){
	// it's parent class takes care of its part and limo takes care of the rating.
	Vehicle::returningVehicle(hours, repair, currentFuel, rating);
	rating = rated; 
}
//calculated the earning since last rent
void Limo::earningsSinceLastRepair(){
	cout << "\nThis Limo has been used for " << hoursRented << " hours since its last repair.\n"
		<< "It has earned the company $" << rate * hoursRented << ".00 in that time." << endl;
}
