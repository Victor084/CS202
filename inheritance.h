#ifndef INHERINTANCE_H
#define INHERINTANCE_H

#include <cstring>
#include <iostream>

using namespace std;

//################## Base class ########
// Abstract Base Class
class Rentals {
	public:


		int servicing(Rentals* brokenRentals);  // int returns the numbers of days since last service

		float hoursUsed();
		float totalRevenue();
		float earningsPerServiceOfRentals();


		virtual void print() const = 0;

		Rentals(int, bool);
		Rentals();
		virtual ~Rentals();
		Rentals(const Rentals& otherRentals);
		Rentals(int newId, bool available, bool service, float setRate, char address[]); 


	protected:
		int id;
		bool isAvailable;
		bool needsService;
		float rate;
		char* intersection;


};






// ********** DERIVED CLASSES **********
class Scooter : public Rentals {
	public:
		float batteryLevel;

		void print() const;

		Scooter();
		Scooter(const Scooter & otherScooter);
		Scooter(int newId, bool available, bool service, char intersections[50]); 
	protected:



};


//#### Sub Base CLass  ########
class Vehicle : public Rentals {
	public:
		char* licensePlate;
		float gasLevel;
		int seats;

		bool returnedFull();
		Vehicle();
		~Vehicle();
		Vehicle(const Vehicle& otherVehicle);
		Vehicle(int newId, bool available, bool service, float rate, char address[], char plates[], float gas, int numSeats); 


	protected:


};

class Zip_Car : public Vehicle {
	public:
		Zip_Car();
		Zip_Car(const Zip_Car& otherZipCar);
		Zip_Car(int newId, bool available, bool service, char intersections[50], char plates[]); 


		void print() const;

	protected:



};


class Limo : public Vehicle {
	public:
		char* driverName;
		int reservedHours;

		Limo();
		Limo(const Limo& otherLimo);
		Limo(int newId, bool available, bool service, char intersections[50], char plates[], char name[], int hours); 

		void print() const;

	protected:


};



#endif
