/*
   inheritance.h
   Victor Heredia
   CS202 - 10/29/18
   this file promises all the functions that will be implemented in the source file
 */
#ifndef INHERINTANCE_H
#define INHERINTANCE_H

#include <cstring>
#include <iostream>

using namespace std;

//################## Base class ###################
// Abstract Base Class
class Rentals {
	public:


		int servicing(Rentals* brokenRentals);  // int returns the numbers of days since last service

		float hoursUsed();// not implemented
		float totalRevenue();// didnt get time to get to this
		float earningsPerServiceOfRentals();// this was to be used
		int getId();// return the id 
		void setAvailability(bool);// update availability
		void setRental(bool state);// update rental status
		bool isItAvailable();// gets the availability


		// every pure virtual my be implemented by the derived classes or they become ABC too
		virtual void print() const = 0;
		virtual void returningScooter(int rentedHours, bool repair, float batteryLevel);
		virtual void returningVehicle(int hours, bool repair, float currentFuel, int rating = 0);// both derived vehicles dont use the rating
		virtual void earningsSinceLastRepair();
		virtual void printDriversName();// gets the name

		Rentals(int, bool);
		Rentals();
		virtual ~Rentals();
		Rentals(const Rentals& otherRentals);
		Rentals(int newId, bool available, bool service, float setRate, char address[], int hours = 0); 


	protected:
		int id;
		bool isAvailable;
		bool isRented;
		float rate;
		char* intersection;
		int hoursRented;
};






// ********** DERIVED CLASSES  FROM RENTALS  **********
class Scooter : public Rentals {
	public:
		Scooter();
		Scooter(const Scooter & otherScooter);
		// this constructor created a complete scooter and allowed me to use the copy constructor when inserting that completed scooter object
		Scooter(int newId, bool available, bool service, char intersections[]); 


		void print() const;
		void returningScooter(int rentedHours, bool repair, float batteryLevel);//checking in
		void earningsSinceLastRepair();// calculate the earnings

	protected:
		float batteryLevel;
};






//#### SUB ABSTRACT CLASS DERIVED FROM RENTALS  ########

// this class will NOT implement the pure virtual function from the ABC making it an ABC too
class Vehicle : public Rentals {
	public:
		Vehicle();
		~Vehicle();
		// the copy constructor
		Vehicle(const Vehicle& otherVehicle);
		//this constructor passes everything up to the Base class
		Vehicle(int newId, bool available, bool service, float rate, char address[], char plates[], float gas, int numSeats); 


		// this class also has its own pure virtual function
		virtual void returningVehicle(int hours, bool repair, float currentFuel, int rating = 0) = 0;
		//virtual void printDriversName();
		bool returnedFull();


	protected:
		char* licensePlate;
		float gasLevel;
		int seats;


};




// ------------ DERIVED CLASSES FROM VEHICLE -------------------------//

// a Zip Car is a Vehicle
class Zip_Car : public Vehicle {
	public:
		Zip_Car();
		Zip_Car(const Zip_Car& otherZipCar);
		// this constructor allows me to construct a complete zip car and use the copy constructor when passing it to the insert function of my data structure
		Zip_Car(int newId, bool available, bool service, char intersections[], char plates[]); 


		void print() const;
		void returningVehicle(int hours, bool repair, float currentFuel, int rating = 0);
		void earningsSinceLastRepair();

	protected:
		// no additional members needed, since it is derived from Vehicle and that has everything


};



// a Limo is a Vehicle
class Limo : public Vehicle {
	friend ostream& operator<<(ostream&, const Limo&);// this was not actually used but will play with it later
	public:
	Limo();
	Limo(const Limo& otherLimo); // copy constructor
	~Limo();//destructor
	// this constructor allows me to construct a complete zip car and use the copy constructor when passing it to the insert function of my data structure
	Limo(int newId, bool available, bool service, char intersections[], char plates[], char name[], int hours); 

	void print() const;
	void returningVehicle(int hours, bool repair, float currentFuel, int rating = 0);//checking in the vehicle and update the data memebrs
	void earningsSinceLastRepair();
	void printDriversName();

	protected:
	char* driverName;
	int reservedHours;
	int rating;
};
#endif
