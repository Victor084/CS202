#ifndef DLL_H
#define DLL_H

#include "inheritance.h"
#include <typeinfo>

class Node {
	public:
	Node();
	~Node();
	Node(const Node& otherNode);
	Node(Rentals* newData);
	Node(const Scooter & newScooter);
	Node(const Zip_Car & newZipCar);
	Node(const Limo & newLimo);


	Node* &goNext();
	void setNext(Node* newNext);
	Node* &goPrev();
	void setPrev(Node* newPrev);

	Rentals* getData();


	protected:
	Rentals* data;
	Node* prev;
	Node* next;

};


class List {
	public:
	
	void listBuild();
	void insert(Rentals* newRental);
	void displayAll() const;
	void displayAll(Node* head) const;
	void deleteAll(Node* &head);

	void removeNode(Node* &head, int key);
	void rent(int renID);
	void search(Node* head, int key);
	void checkIn(int rentID, int hours, bool isBroken);
	void checkInSearch(Node* &head, int key, int hoursUsed, bool isBroken);
	Rentals* getIdPtr(int requestId);
	Rentals* getDataPtr(Node* head, int key);
	void getType(Rentals* product);
	void checkInScooter(int checkInId, int rentedHours, bool repair, int batteryLevel);
	void checkInVehicle(int id, int hours, bool needsRepairing, float gasLevel, int rating = 0);
	ostream& getDriversName(ostream& outObj, int limoId);
	bool idAlreadyUsed(int id);

	Node* getHead();

	List();
	~List();
	List(const List & otherList);

	protected:
	Node* head;
	Node* tail;

};



#endif
