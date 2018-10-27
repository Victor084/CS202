#include "dll.h"

void captureInfo(int& id, bool& available, bool& service, char intersections[50]);

int main(){
	int id;
	bool available;
	bool service;
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
			 << "4) Exit the inventory manager" << endl
			 << "5) Display entire inventory" << endl;
		cin >> type;
		cin.ignore(100, '\n');
		cin.clear();
		if(type < 1 && type > 4)
			cout << "Unrecognized selection. Please try again" << endl;
		else
			switch(type){
				case 1:{
						   captureInfo(id, available, service, intersections);
						   Scooter* sPtr  = new Scooter(id, available, service, intersections);
						   myInventory.insert(sPtr);
					   }
					   break;
				case 2:{
						   captureInfo(id, available, service, intersections);
						   cout << "License Plat: ";
						   cin.get(licensePlate, 50, '\n');
						   cin.clear();
						   cin.ignore(100,'\n'); 
						   cin.clear();
						   Zip_Car* zPtr = new Zip_Car(id, available, service, intersections, licensePlate);
						   myInventory.insert(zPtr);
					   }
					   break;

				case 3:{
						   captureInfo(id, available, service, intersections);
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
						   Limo* limoPtr = new Limo(id, available, service, intersections, licensePlate, name, hours);
						   myInventory.insert(limoPtr);
					   }
					   break;
				case 4:
						// calculate revenue
						break;
				case 5:
						// print
						myInventory.displayAll();

					break;

			}
	}while(type > 0 && type < 4);
	


	return(0);
}

void captureInfo(int& id, bool& available, bool& service, char intersections[50]){
	char repair;

	cout << "Please catalog the product, by entering the following info:\n";
	cout << "Please enter an ID number: ";
	cin >> id;

	cout << "\nDoes it need any repairs? (Y/N)";
	cin >> repair;
	cin.ignore(100, '\n');
	cin.clear();
	repair = toupper(repair);
	service = (repair == 'Y') ? true : false;
	if(service)
		available = false;
	// dont forget to include this in the constructor
	//cout << "\nHow much will this prodcut be rented for? " ;
	//cin >> rate;
	cout << "\nWhere will this product be deployed? (street intersections) " ;	
	cin.get(intersections, 50, '\n');	
	cin.ignore(100, '\n');
	cin.clear();


}



