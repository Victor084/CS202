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
	data = newData;
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



//############  LIST   (DLL)  #############

List::List() : head(0), tail(0)
{ }

// make HELPER FUNCTION
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
}

void List::displayAll() const {
	displayAll(head);
}

void List::displayAll(Node* head) const {
	if(!head) return;

	head->getData()->print();
	displayAll(head->goNext() );
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

// this will search for the product ID in the Inventory
void List::rent(int rentID){
	search(head, rentID);
}

void List::search(Node* head, int key){
	if(!head) return;


	if(head->getData()->getId() == key){
		head->getData()->setRental(true);
		// we should probably assign a name to tack who checked it out.


		// this is just to hit that exit and keep the control flow tight
		search(tail->goNext(), key); 
	}

	search(head->goNext(), key);
}

void List::checkIn(int rentID, int hours, bool isBroken){
	checkInSearch(head, rentID, hours, isBroken);	

}

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


Node* List::getHead(){
	return(head);
}


Rentals* List::getIdPtr(int requestId){
	return(getDataPtr(head, requestId));
}

Rentals* List::getDataPtr(Node* head, int key){
	Rentals* returnType = NULL;
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

void List::getType(Rentals* productPtr){

	if(typeid(*productPtr) == typeid(Scooter))
		cout << "Scooter";
	if(typeid(*productPtr) == typeid(Zip_Car))
		cout << "Zip Car";
	if(typeid(*productPtr) == typeid(Limo))
		cout << "Limo";
}
void List::checkInScooter(int checkInId, int rentedHours, bool repair, int batteryLevel){

	getDataPtr(head, checkInId)->returningScooter(rentedHours, repair,batteryLevel);

}
void List::checkInVehicle(int id, int hours, bool needsRepairing, float gasLevel, int rating){
	getDataPtr(head, id)->returningVehicle(hours, needsRepairing, gasLevel, rating);
}

// will only be called if the base pointer is pointing to a limo object
ostream& List::getDriversName(ostream& outObj, int limoId){
	
	// searc the list for the limo and get cout the name
	  outObj << (getDataPtr(head, limoId));
	  return outObj;
	//return cout << getDataPtr(head, limoId)->printName();
	//if(head->getData()->getId() == key){
	//	head->getData->printName();
	//	return; 
	//}
	//getDriversName(head->goNext(), limoId);
}
bool List::idAlreadyUsed(int id){
	bool returningValue = 0;
	// if we find a node with that id then it is not Unique
	if(getDataPtr(head, id))
		returningValue = true;
	// initialized to false to begin with 
	return returningValue;
}

