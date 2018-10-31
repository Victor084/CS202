/*
   main.cpp
   Victor Heredia
   CS202 - 10/29/18
   program 2 using dynamic binding

   main.cpp
   This is the driver file of the program. From here we can interact with the use and enter all the necessary information the list class will need.
   This file has several variables that are used to construct objects that will be passed in to the list class.

 */
#include "dll.h"
#include <unistd.h>

// this function is used by three cases so I didnt want to write it three times
void captureInfo(int& id, bool& available, char intersections[50]);//, original parameter list const List currentlist);

int main(){
	// local members that will be passed in as arguments for the class to initialize its data members
	int id;
	bool available;
	char intersections[50];
	char licensePlate[50];
	char name[50];
	int hours;


	List myInventory;   // this is a list object that manages all our data
	int type = 0;
	//menu asking user to enter product details
	cout << "Congratulations in starting your transportation rental service!" << endl;
	cout << "Let's start by entering some inventory" << endl;

	do{
		// I really should had implemented a try and catch to assure only acceptable inputs were accepted and not terminating my program
		cout << endl << endl << "What product would you like to do? " << endl << endl;
		cout << "1) Enter a new Scooter" << endl  // create a new node with a scooter in the list
			<< "2) Enter a new Zip Car" << endl  // create a new node with a zip car in the list
			<< "3) Enter a new Limo and driver" << endl   // create a new node with a Limo in the list
			<< "4) Check out a product to a customer." << endl  // make product unavailable
			<< "5) Check in a product from a customer." << endl // enter number of hours used
			<< "6) Calculate the revenue made from a single product.\n" // amount earned since last service
			<< "7) Display entire inventory" << endl  // This is all one cout statement
			<< "0) To exit" << endl << endl;
		cout << "Please make a selection by entering only one of the numbers listed above: ";
		cin >> type;
		cin.ignore(100, '\n');
		cin.clear();
		if(type < 0 && type > 7)
			cout << "Unrecognized selection. Please try again" << endl;
		else
			switch(type){
				case 1:{
						   captureInfo(id, available, intersections);//, myInventory);
						   // the flase is setting the isRented data member
						   Scooter* sPtr  = new Scooter(id, available, false, intersections);
						   myInventory.insert(sPtr);
					   }
					   break;
				case 2:{
						   captureInfo(id, available, intersections);//, myInventory);
						   cout << "License Plat: ";
						   cin.get(licensePlate, 50, '\n');
						   cin.clear();
						   cin.ignore(100,'\n'); 
						   cin.clear();
						   // the flase is setting the isRented data member
						   Zip_Car* zPtr = new Zip_Car(id, available, false, intersections, licensePlate);
						   myInventory.insert(zPtr);
					   }
					   break;

				case 3:{
						   captureInfo(id, available, intersections);//, myInventory);
						   cout << "License Plat: ";
						   cin.get(licensePlate, 50, '\n');
						   cin.ignore(100, '\n');
						   cin.clear();
						   cout << "Please enter the name of the driver assigned to this Limo: ";
						   cin.get(name, 50, '\n');
						   cin.ignore(100,'\n');
						   cin.clear();
						   cout << "Enter minimum hours this Limo should be reserved for: ";
						   cin >> hours;
						   cin.ignore(100, '\n');
						   cin.clear();
						   // the flase is setting the isRented data member
						   Limo* limoPtr = new Limo(id, available, false, intersections, licensePlate, name, hours);
						   myInventory.insert(limoPtr);
					   }
					   break;
				case 4:{
						   // check out a product
						   cout << "Enter the ID of the product being rented: ";
						   cin >> id;
						   myInventory.rent(id);
					   }
					   break;

				case 5: {
							// this case check in an item and update the data members
							char repair;
							bool needsRepairing = 0;
							Rentals* productPtr = myInventory.getIdPtr(id);
							cout << "Make sure to check out a product before checking it in" << endl;
							// maybe use RTTI here to print the actual product instad of the work product
							// yeah this would be a good place
							cout << "Enter the ID of the product being returned: ";
							cin >> id;
							cout <<"How many hours did the customer have the ";
							myInventory.getType(productPtr);
							cout << "? ";
							cin >> hours;
							cout << "Does the ";
							myInventory.getType(productPtr);
							cout << " need to be serviced? ";
							cin >> repair;
							cin.ignore(100, '\n');
							cin.clear();
							repair = toupper(repair);
							needsRepairing = (repair == 'Y') ? true : false;
							if(typeid(*productPtr) == typeid(Scooter)){
								int battery = 0;
								//cout Scooter info
								cout << "\nWhat is the battery level?";
								cin >> battery;
								myInventory.checkInScooter(id, hours, needsRepairing, battery);
							}


							if(typeid(*productPtr) == typeid(Vehicle)){
								float gasLevel = 0.0;
								//if the product is a VEHICLE type ask about the gas level
								cout << "What is the gas level of the ";
								myInventory.getType(productPtr);
								cout << "?";
								cin >> gasLevel; 

								if(typeid(*productPtr) == typeid(Zip_Car)){
									// can I use default parameter for battery and gas level?
									// rating is a default parameter and Zip Car does not need it.
									myInventory.checkInVehicle(id, hours, needsRepairing, gasLevel);
								}
								if(typeid(*productPtr) == typeid(Limo)){
									int rating = 0;
									//float gasLevel = 0.0;
									//int rating = 0;
									////if the product is a VEHICLE type ask about the gas level
									//cout << "What is the gas level of the " << myInventory.getType(productPtr) << "?";
									//cin >> gasLevel; 
									cout << "Please rate";
									myInventory.getDriversName(id);
									cout << " on a scale of 1 to 5 stars." << endl;
									//cout << "Please rate" << myInventory.getDriversName(id) << " on a scale of 1 to 5 stars." << endl;
									cin >> rating;
									myInventory.checkInVehicle(id, hours, needsRepairing, gasLevel, rating);
								}//end of Limo
							} // end of Vehicle typeid

						}
						break;

				case 6:{
						   // calculate revenue
						   myInventory.calculateRevenue(id);
						   // need to pause for 5 seconds
						   usleep(5000000);// this is just to pause the screen so the user can read the calculation before being prompted again
					   }
					   break;

				case 7:{
						   // print
						   myInventory.displayAll();
					   }
					   break;
				default:{
							cout << "\nInvalid selection" << endl; // don't need a default since the switch is in an if else guarding incorrect entries
						}

						break;

			}
	}while(type != 0); // quick and simple error cheking but great, but it works



	return(0);
}



// didn't want to enter the same code three time, one for each case that creates a new derived object
void captureInfo(int& id, bool& available, char intersections[50]){// this was the original parameter list to check for duplicate IDs const List currentlist){
	char repair;
	//bool isNotUnique = 0;
	cout << "\n\nPlease catalog the product, by entering the following info:\n";
	// should I check to make sure that ID is not already being used?
	//do{
	//	if(isNotUnique)
	//cout << "ID number is already assigned to a product.\n\n";
	cout << "Please enter an ID number: "; // should really should have a function here that checking that the id is unique
	cin >> id;
	// this function call was modifying my list object for whatever reason, tried passing the list as a const argument
	//	isNotUnique = currentlist.idAlreadyUsed(id);
	//}while(isNotUnique );
	cout << "\nDoes it need any repairs? (Y/N) ";  // not really required here, but maybe a product arrived defective or second hand
	cin >> repair;
	cin.ignore(100, '\n');
	cin.clear();
	repair = toupper(repair);  // if it needs repairs then it is not available
	available = (repair == 'Y') ? false : true;
	cout << "\nWhere will this product be deployed? (street intersections) " ;	// each product has a home base where they start, strategic placement
	cin.get(intersections, 50, '\n');	
	cin.ignore(100, '\n');
	cin.clear();
}
