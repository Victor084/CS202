#include "dll.h"

void captureInfo(int& id, bool& available, char intersections[50]);

int main(){
	int id;
	bool available;
	char intersections[50];
	char licensePlate[50];
	char name[50];
	int hours;


	List myInventory;
	int type = 0;
	//menu asking user to enter product details
	cout << "Congratulations in starting your transportation rental service!" << endl;
	cout << "Let's start by entering some inventory" << endl;

	do{
		cout << endl << endl << "What product would you like to do? " << endl << endl;
		cout << "1) Enter a new Scooter" << endl
			<< "2) Enter a new Zip Car" << endl
			<< "3) Enter a new Limo and driver" << endl
			<< "4) Check out a product to a customer." << endl
			<< "5) Check in a product from a customer." << endl // enter number of hours used
			<< "6) Calculate the revenue made from a single product.\n" // amount earned since last service
			<< "7) Display entire inventory" << endl;
		cin >> type;
		cin.ignore(100, '\n');
		cin.clear();
		if(type < 1 && type > 7)
			cout << "Unrecognized selection. Please try again" << endl;
		else
			switch(type){
				case 1:{
						   captureInfo(id, available, intersections);
						   // the flase is setting the isRented data member
						   Scooter* sPtr  = new Scooter(id, available, false, intersections);
						   myInventory.insert(sPtr);
					   }
					   break;
				case 2:{
						   captureInfo(id, available, intersections);
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
						   captureInfo(id, available, intersections);
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
							char repair;
							bool needsRepairing = 0;
							Rentals* productPtr = myInventory.getIdPtr(id);
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
						//cout << "Please rate" << myInventory.getDriversName(id) << " on a scale of 1 to 5 stars." << endl;
									cin >> rating;
									myInventory.checkInVehicle(id, hours, needsRepairing, gasLevel, rating);
								}//end of Limo
							} // end of Vehicle typeid

						}
						break;

				case 6:{
						// calculate revenue
						cout << "This is case 6\n";
				}
						break;

				case 7:{

						   // print
						   myInventory.displayAll();
					   }
					   break;
				default:{
							cout << "Invalid selection" << endl;
						}

						break;

			}
	}while(type > 0 && type < 8);



	return(0);
}

void captureInfo(int& id, bool& available, char intersections[50]){
	char repair;

	cout << "Please catalog the product, by entering the following info:\n";
	// should I check to make sure that ID is not already being used?
	cout << "Please enter an ID number: ";
	cin >> id;

	cout << "\nDoes it need any repairs? (Y/N) ";
	cin >> repair;
	cin.ignore(100, '\n');
	cin.clear();
	repair = toupper(repair);
	available = (repair == 'Y') ? false : true;
	// dont forget to include this in the constructor
	//cout << "\nHow much will this prodcut be rented for? " ;
	//cin >> rate;
	cout << "\nWhere will this product be deployed? (street intersections) " ;	
	cin.get(intersections, 50, '\n');	
	cin.ignore(100, '\n');
	cin.clear();


}



