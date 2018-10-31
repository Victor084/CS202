/*
   Victor Heredia
   CS202 - 10/29/18
   this file make all the promises of the functions that will be implemented by the source file
 */

#ifndef DLL_H
#define DLL_H

#include "inheritance.h"
// this library allows us to use typeid
#include <typeinfo>

class Node {
	public:
		Node();
		~Node();
		Node(const Node& otherNode);// copy constructor
		Node(Rentals* newData);
		// object constructors that made it easier for me.
		Node(const Scooter & newScooter);
		Node(const Zip_Car & newZipCar);
		Node(const Limo & newLimo);

		// getters and setters
		Node* &goNext();
		void setNext(Node* newNext);
		Node* &goPrev();
		void setPrev(Node* newPrev);

		Rentals* getData();
		void setData(Rentals* otherData);


	protected:
		Rentals* data;
		Node* prev;
		Node* next;

};


class List {
	public:

		void insert(Rentals* newRental);// this inserts at the tail of the list
		void displayAll() const;

		void removeNode(Node* &head, int key);// removed a node from the list by sending head by refrence
		void rent(int renID);
		void checkIn(int rentID, int hours, bool isBroken); // checks in the product
		Rentals* getIdPtr(int requestId);// this was awesome, it returned a base pointer that allowed me to use the memeber function from the inheritance hierarchy
		void getType(Rentals* product);// checks to see what type the base pointer is
		bool checkedout(Node* head, int id);// checks out the product
		void checkInScooter(int checkInId, int rentedHours, bool repair, int batteryLevel);// checks in a scooter
		void checkInVehicle(int id, int hours, bool needsRepairing, float gasLevel, int rating = 0);// checks in a Vehicle like a car or limo
		void sendToRepairShop(Node* &head, int key);// this removes a node from the list because it is not available to rent 
		//ostream& getDriversName(int limoId);
		bool idAlreadyUsed(int id);// this was implemented but unfortunately not used. it was to check that ids were unique only
		void calculateRevenue(int id);// calculate the revenue
		void assignCost(Node* &head, int id);
		void getDriversName(int limoId);

		Node* getHead();

		List();
		~List();
		List(const List & otherList);

	protected:
		Node* head;
		Node* tail;
		// all these functions are the helper functions that give access to the head of the list to the wrapper functions.
		void copyList(Node* &head,  Node* otherHead);// copy constructor
		void displayAll(Node* head) const;// this the actual display function but the client doesnt have access
		void deleteAll(Node* &head); // this is for the destuctor only
		void search(Node* head, int key);// the actual search function
		void checkInSearch(Node* &head, int key, int hoursUsed, bool isBroken);
		Rentals* getDataPtr(Node* head, int key);

};



#endif
