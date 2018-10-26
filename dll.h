#ifndef DLL_H
#define DLL_H

#include "inheritance.h"

class Node {
	public:
	Node();
	~Node();
	Node(const Node& otherNode);
	Node(Rentals* newData);
	Node(const Scooter & newScooter);
	Node(const Zip_Car & newZipCar);
	Node(const Limo & newLimo);


	Node* goNext();
	void setNext(Node* newNext);
	Node* goPrev();
	void setPrev(Node* newPrev);


	protected:
	Rentals* data;
	Node* prev;
	Node* next;

};


class List {
	public:
	List();
	~List();
	List(const List & otherList);
	
	void listBuild();
	void insert(Rentals* newRental);
	void deleteAll(Node* &head);



	protected:
	Node* head;
	Node* tail;


};



#endif
