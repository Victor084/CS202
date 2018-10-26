#ifndef INHERINTANCE_H
#define INHERINTANCE_H

#include <cstring>
#include <iostream>

using namespace std;

//################## Base class ########
// Abstract Base Class
class Rentals {
	public:
		int id;
		bool available;
		bool service;
		float rate;
		char* intersection;

		bool state;  // 1 in operation,  0 in repairshop,  what about READY

		int servicing(Rentals* brokenRentals);  // int returns the numbers of days since last service

		float hoursUsed();
		float totalRevenue();
		float earningsPerServiceOfRentals();


		virtual void print() const = 0;

		Rentals(int, bool);
		Rentals();
		virtual ~Rentals();
		Rentals(const Rentals& otherRentals);


	protected:


};






// ********** DERIVED CLASSES **********
class Scooter : public Rentals {
	public:
		float batteryLevel;

		void print() const;

		Scooter();
		Scooter(const Scooter & otherScooter);
	protected:



};


//#### Sub Base CLass  ########
class Vehicle : public Rentals {
	public:
		char* licensePlate;
		float gasLevel;
		bool returnedFull;
		int seats;

		Vehicle();
	virtual	~Vehicle();
	//virtual	~Vehicle();
		Vehicle(const Vehicle& otherVehicle);

	protected:


};

class Zip_Car : public Vehicle {
	public:
		Zip_Car();
		Zip_Car(const Zip_Car& otherZipCar);

		void print() const;

		// do I need print here
	protected:



};


class Limo : public Vehicle {
	public:
		char* driverName;
		int minimumRentalHours;

		Limo();
		Limo(const Limo& otherLimo);

		void print() const;

		// do I need print here
	protected:


};



#endif
