// stdafx.cpp : source file that includes just the standard includes
// task1.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information


// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

// A program to demonstrate the management of a small database of operational 
// amplifiers.
//
// General description
//
// The database contains up to DATABASE_MAX operational amplifier elements. Each 
// element contains the operation amplifier name, the number of pins in the package
// and stores the slew rate of the device.
//
// New elements can be added into the database by the user. The database can be saved
// to disk or loaded from disk. The database elements can be sorted either by name or
// by slew rate. There is also the facility to display the elements.
//
// Only a single database is required and the file name is fixed in the code (as 
// DATABASE_FILENAME). This means that each time the database is saved to disk,
// any previous data in the file is overwritten. Also, when a database is loaded
// from a file it should overwrite any data already in memory.

#include "stdafx.h"
//#include "pch.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

// the format of each of the elements in the database
struct OpAmps {
	char Name[20];  // the name of the op-amp (e.g. "741")
	unsigned int PinCount;  // the number of pins in the package
	double SlewRate;  // the slew rate in volts per microsecond
};

// the length of the fixed array to be used for database - must be at least one
// and no greater the maximum value allowed in an unsigned long (see the file
// limits.h).
#define DATABASE_MAX 10

// file used for the database
#define DATABASE_FILENAME "database.txt"

// function prototypes
//<enter code here>
void Enter(OpAmps ByVal, unsigned long);

void Save(OpAmps *SaveElement, unsigned long);

void Load(OpAmps *LoadElement, unsigned long);

void Sort(OpAmps *SortDatabase, unsigned long);

void Display(OpAmps *DisplayDatabase, unsigned long);

// Control the entering, saving, loading, sorting and displaying of elements in the 
// database.
// Arguments: None
// Returns: 0 on completion
int main()
{
	OpAmps OpAmp[DATABASE_MAX];   // the database
	unsigned long database_length = 0;  // the number of elements in the database
	char UserInput;

	// loop until the user wishes to exit
	while (1) {

		// show the menu of options
		cout << endl;
		cout << "Op-amp database menu" << endl;
		cout << "--------------------" << endl;
		cout << "1. Enter a new op-amp into the database" << endl;
		cout << "2. Save the database to disk" << endl;
		cout << "3. Load the database from disk" << endl;
		cout << "4. Sort the database" << endl;
		cout << "5. Display the database" << endl;
		cout << "6. Exit from the program" << endl << endl;

		// get the user's choice
		cout << "Enter your option: ";
		cin >> UserInput;
		cout << endl;

		// act on the user's input
		switch (UserInput) {
		case '1':
			Enter(OpAmp[database_length], database_length);
			break;

		case '2':
			//Save(OpAmp, database_length);
			break;

		case '3':
			//Load(OpAmp, database_length);
			break;

		case '4':
			//Sort(OpAmp, database_length);
			break;

		case '5':
			//Display(OpAmp, database_length);
			break;

		case '6':
			return 0;

		default:
			cout << "Invalid entry" << endl << endl;
			break;
		}
	}
}


// Allow the user to enter a new element into the database. Note that the data is
// simply added to the end the database (if not full) and no sorting is carried
// out.
// Arguments:
//   (1) the element in the database to be entered
//   (2) the position of the element in the database
// Returns: void
//<enter code here>
//
void Enter(OpAmps ByVal, unsigned long)
{

	DATABASE_FILENAME;
	//strcat(location);

	while (1)
	{
		OpAmps AddOpAmp;
		OpAmps *pOpAmps;
		pOpAmps = &AddOpAmp;

		cout << "Enter OpAmp name";
		cin >> pOpAmps->Name;
		cout << "Enter Pin count";
		cin >> pOpAmps->PinCount;
		cout << "Enter Slew Rate";
		cin >> pOpAmps->SlewRate;

		cout << "\nYou have entered:\n";
		cout << pOpAmps->Name << "\n";
		cout << pOpAmps->PinCount << "\n";
		cout << pOpAmps->SlewRate << "\n";

		return;
	}
}
