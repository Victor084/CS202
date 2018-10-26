// for typeid
//#include <typeinfo>
#include "dll.h"

//***********  NODE    **************

Node::Node() : data(0), prev(0), next(0)
{ }

Node::Node(const Node& otherNode){
	data = otherNode.data;
	prev = otherNode.prev;
	next = otherNode.next;
}

Node::~Node(){
	if(data){
		delete data;
		data = nullptr;
	}
	// but we will need to invoked the destuctor for data is there is something there.
	// this was the tricky part for me. I had to use the keyword virtual in the destuctor for it to hold off and actually call the vehicle or crosswalk destructor depending on what the node actualy had. This took care of my memory leaks. The tutors had to fix that for me.
	next = nullptr;
	prev = nullptr;
}
Node::Node(Rentals* newData){
/*
	if(typeid(newData) == typeid(Scooter))
		data = new Scooter(ID name, batteryLevel );
	if(typeid == Vehicle)
	if(typeid == Zip_Car)
		data = new Zip_Car(Zip_Car);
	if(typeid == Limo)
		data = new Limo(Limo);
*/	
}

Node::Node(const Scooter & newScooter){
	data = new Scooter(newScooter);
}
Node::Node(const Zip_Car & newZipCar){
	data = new Zip_Car(newZipCar);
}
Node::Node(const Limo & newLimo){
	data = new Limo(newLimo);
}


Node* Node::goNext(){
	return(next);
}
void Node::setNext(Node* newNext){
	next = newNext;
}
Node* Node::goPrev(){
	return(prev);
}
void Node::setPrev(Node* newPrev){
	prev = newPrev;
}




//############  LIST   (DLL)  #############

List::List() : head(0), tail(0)
{ }

List::List(const List& otherList) : head(otherList.head), tail(otherList.tail)
{  }

List::~List(){
	deleteAll(head);	
}
// the helper function for the destructor so we can do it recursively
void List::deleteAll(Node* &head){
	Node* temp = nullptr;
	if(head){
		temp = head->goNext();
		delete head;
		head = temp;
		// we already updated head
		deleteAll(head);
	}
}

void List::listBuild(){
	int type = 0;
	//menu asking user to enter product details
	cout << "Congratulations in starting your transportation rental servivce!" << endl;
	cout << "Let's start by entering some inventory" << endl;

	do{
		cout << endl << endl << "What product would you like to do? " << endl << endl;
		cout << "1) Enter a new Scooter" << endl
			 << "2) Enter a new Zip Car" << endl
			 << "3) Enter a new Limo and driver" << endl
			 << "4) Exit the inventory manager" << endl;
		cin >> type;
		if(type < 1 && type > 4)
			cout << "Unrecognized selection. Please try again" << endl;
		else
			switch(type){
				case 1:{
						   Scooter* sPtr  = new Scooter;
						   insert(sPtr);
					   }
					   break;
				case 2:{
						   Zip_Car* zPtr = new Zip_Car;
						   insert(zPtr);
					   }
					   break;

				case 3:{
						   Limo* limoPtr = new Limo;
						   insert(limoPtr);
					   }
					   break;
			}
	}while(type > 0 && type < 4);
}



 // insert with recursion for traversal of LLL  so obj is in correct node position
void List::insert(Rentals* newRental){
	Node* temp = new Node(newRental);
	
	if(!head)
		// insert the first Node
		head = tail = temp;
	else {
		// the node contructor sets next and prev to nullptr already
		//update prev
		temp->setPrev(tail);
		// update Tail's next then move tail
		tail->setNext(temp);
		tail = temp;
	}


}

