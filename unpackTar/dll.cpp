/*
   dll.cpp
   Victor Heredia
   CS202 - 10/29/18

   this file implements all the function prototypes of the dll.h

 */

// for typeid
//#include <typeinfo>
#include "dll.h"


//***********  NODE    **************
// default copy constructor
Node::Node() : data(0), prev(0), next(0)
{ }
// copy constructor to take case of passing by value and making copies of other Nodes
Node::Node(const Node& otherNode){
	data = otherNode.data;// copy the data
	prev = otherNode.prev;// and copy the pointers[
	next = otherNode.next;
}
// the node derturctors to invoke the inheritance heirachy's destuctors
Node::~Node(){
	if(data){
		delete data;
		data = nullptr;
	}
	// but we will need to invoked the destuctor for data is there is something there.
	// this was the tricky part for me. I had to use the keyword virtual in the destuctor for it to hold off and actually call the vehicle or crosswalk destructor depending on what the node actualy had. This took care of my memory leaks. The tutors had to fix that for me.
	next = nullptr; // set the pointers to null 
	prev = nullptr;
}
// we already made the object and data so lets just set the data there
Node::Node(Rentals* newData){
	data = newData;
	next = nullptr;
	prev = nullptr;
	// my first attemp was using typeid to construct the appropiate object in the node but Karla said not to do it here.
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

// constructo the node with the correct object
Node::Node(const Scooter & newScooter){
	data = new Scooter(newScooter);
}
Node::Node(const Zip_Car & newZipCar){
	data = new Zip_Car(newZipCar);
}
Node::Node(const Limo & newLimo){
	data = new Limo(newLimo);
}


// the famous getters and setter that come with Node classes
Node*& Node::goNext(){
	return(next);
}
void Node::setNext(Node* newNext){
	next = newNext;
}
Node* &Node::goPrev(){
	return(prev);
}
void Node::setPrev(Node* newPrev){
	prev = newPrev;
}
Rentals* Node::getData(){
	return(data);
}
void Node::setData(Rentals* otherData){
	data = otherData;
}






//############  LIST   (DLL)  #############

// default constructor
List::List() : head(0), tail(0)
{ }

// make HELPER FUNCTION
List::List(const List& otherList) : head(NULL), tail(NULL){  
	copyList(head, otherList.head);	
}
// here is the hepler function for the copy constructor
void List::copyList(Node* &head,  Node* otherHead){
	if(!otherHead) return;

	head = new Node;
	head->setData(otherHead->getData() );
	head->setPrev(otherHead->goPrev() );
	head->setNext(otherHead->goNext() );

	copyList(head->goNext(), otherHead->goNext());

	// on our way back we can set the  head and tail
	// we could do it in the wrapper fucntion but that would require creating the nodes and then updating head and tail, we already have those nodes here.
	if(!head->goNext() )
		this->tail = head;
	if(!head->goPrev())
		this->head = head;

}

// the destuctor has its helper function
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

// wrapper to get access to the head
void List::displayAll() const {
	displayAll(head);
}
// is the recursive function to display the content of the list
void List::displayAll(Node* head) const {
	if(!head) return;
	head->getData()->print();  // in order printing, if we have a node then print it.
	displayAll(head->goNext() ); // then move on to the next node
}


// insert with recursion for traversal of LLL  so obj is in correct node position
void List::insert(Rentals* newRental){
	Node* temp = new Node(newRental);  // create the node then assign it later

	if(!head)
		head = tail = temp; // insert the first Node
	else {
		// the node contructor sets next and prev to nullptr already
		// always add at the tail
		//update prev
		temp->setPrev(tail);
		// update Tail's next then move tail
		tail->setNext(temp);
		tail = temp; // make sure to update thet tail
	}
}


// head is passed by reference to update the actual list
// id are assumed to be unique so it may return as soon as it find the first and only instance with that id
void List::removeNode(Node* &head, int key){
	if(!head) return;

	// only one node
	if(!head->goPrev() && !head->goNext()){
		delete head;
		head = tail = nullptr;
	}

	//remove tail
	if(tail->getData()->getId() == key){
		Node* toRemove = tail;
		tail = tail->goPrev();
		delete toRemove;
	}

	//remove head
	if(head->getData()->getId() == key){
		Node* toRemove = head;
		head = head->goNext();
		// if we are at the head of the list
		if(!head->goPrev()){
			delete toRemove;
		} else {
			head->setPrev(toRemove->goPrev());
			toRemove->goPrev()->setNext(head);
		}

	}
}

// this only call the real search function
void List::rent(int rentID){
	search(head, rentID);
}

// this will search for the product ID in the Inventory
void List::search(Node* head, int key){
	if(!head) return;


	if(head->getData()->getId() == key){  // this block is when we actually find it.
		head->getData()->setRental(true);
		// we should probably assign a name to tack who checked it out.

		// this is just to hit that exit and keep the control flow tight
		search(tail->goNext(), key); 
	}


	// keep looking on the following nodes
	search(head->goNext(), key);
}
// return the product and update the data members
void List::checkIn(int rentID, int hours, bool isBroken){
	checkInSearch(head, rentID, hours, isBroken);	
}
//we search for the node with the id that matches and update the data memebrs
void List::checkInSearch(Node* &head, int key, int hoursUsed, bool isBroken){
	if(!head) return;

	if(head->getData()->getId() == key){
		Node* toRemove = head;
		head = head->goNext();
		//if head we need to set prev to NULL
		if(!toRemove->goPrev() )
			head->setPrev(NULL);

		removeNode(toRemove, key);

		// check to make sure we are not removing at the tail
		checkInSearch(tail->goNext(), key, hoursUsed, isBroken);
	} else {

		checkInSearch(head->goNext(), key, hoursUsed, isBroken);
	}
}


// get the head
Node* List::getHead(){
	return(head);
}

// lets return the base class pointer so we can call member functinos from that derived class
Rentals* List::getIdPtr(int requestId){
	return(getDataPtr(head, requestId));
}
// this guy does it recursively
Rentals* List::getDataPtr(Node* head, int key){
	Rentals* returnType = NULL;
	//only do things when we actually have a head otherwise return that Rental* returnType which is already null
	if(head) {
		if(head->getData()->getId() == key){
			returnType = head->getData();
		} else {
			getDataPtr(head->goNext(), key);
		}	
	}
	// only one return for better flow control
	return returnType;
}

// this my first draft but scrapped, it helps me to keep it here to avoid doing it again.
void List::getType(Rentals* productPtr){

	if(typeid(*productPtr) == typeid(Scooter))
		cout << "Scooter";
	if(typeid(*productPtr) == typeid(Zip_Car))
		cout << "Zip Car";
	if(typeid(*productPtr) == typeid(Limo))
		cout << "Limo";
}
// change the availability status to checked out
bool List::checkedout(Node* head, int id){
	return getDataPtr(head, id)->isItAvailable();
}

// return a scooter and update the data memebers
void List::checkInScooter(int id, int rentedHours, bool needsRepairing, int batteryLevel){
	// if it has not been checked out then it should not be able to be checked in
	bool checkedOut = !checkedout(head, id);
	if(checkedOut)
		cout << "Product was never rented so it can not be checked in" << endl;
	else{
		// if it is checked out then check it in
		getDataPtr(head, id)->returningScooter(rentedHours, needsRepairing, batteryLevel);
		// if it needs repairs then send it to the shop
		if(needsRepairing)
			sendToRepairShop(head, id);
	}
}
//check in the vehicle and update the data members
void List::checkInVehicle(int id, int hours, bool needsRepairing, float gasLevel, int rating){
	// checking to make sure it is not already checked out didn't work as beaitufuly as it did yesterday so I am no implementing it on the Vehicle classes
	getDataPtr(head, id)->returningVehicle(hours, needsRepairing, gasLevel, rating);
	// if it needs repairs then send it to the shop
	if(needsRepairing)
		sendToRepairShop(head, id);
}

// this removes the node from the list becaus it is not ready to be checked out
void List::sendToRepairShop(Node* &head, int key){
	if(!head) return;


	// we found the node of interest
	if(head->getData()->getId() == key){

		// hold on top node that will be removed
		Node* toRemove = head;


		//if only one node
		if(!head->goPrev() && !head->goNext()){
			head = tail = nullptr;
		}

		// remove at head 
		if(!head->goPrev()){
			//advance head and cut ties
			this->head = head = head->goNext();
			head->setPrev(nullptr);
		}
		// remove at tail
		if(!head->goNext()){

			this->tail = head = head->goPrev();
			head->setNext(nullptr);
		} else {
			// if not one node, and not head or tail then it is in the middle of the list


			// remove from the middle

			//if we are at head this wont work
			Node* previousNode = head->goPrev();

			// advance head
			head = head->goNext();
			head->setPrev(previousNode);
			previousNode->setNext(head);
		}
		delete toRemove; // finally remove the node of interest
		return; // nothing else to do here since every id is unique
	}
	// current node doesn't have the droids we are looking for
	// move on
	sendToRepairShop(head->goNext(), key);
}

// we just get the name
void List::getDriversName(int limoId){
	getDataPtr(head, limoId)->printDriversName();
}

// this was a failed expirement 

// will only be called if the base pointer is pointing to a limo object
//ostream& List::getDriversName(int limoId){
//ostream& outObj;
// searc the list for the limo and get cout the name
//outObj << (getDataPtr(head, limoId));
//return outObj;
//return cout << getDataPtr(head, limoId)->printName();
//if(head->getData()->getId() == key){
//	head->getData->printName();
//	return; 
//}
//getDriversName(head->goNext(), limoId);
//}



// this was used in the driver file to check that the entered id was original, however it would modify the existing list, tutors and I couldnt figure out why or how so I just didnt use it.
bool List::idAlreadyUsed(int id){
	bool returningValue = 0;
	// if we find a node with that id then it is not Unique
	if(getDataPtr(head, id))
		returningValue = true;
	// initialized to false to begin with 
	return returningValue;
}
// find out how much the product has made since the last repair
void List::calculateRevenue(int id){
	assignCost(head, id);
}

// this functino calls the getDataPtr who searches the list and returns a base pointer to we can just use an arrow right after the call since it returns an base pointer
void List::assignCost(Node* &head, int id){
	// basePtr->calculate earningns
	getDataPtr(head, id)->earningsSinceLastRepair();

}
