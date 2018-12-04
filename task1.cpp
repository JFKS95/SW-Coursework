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

//#include "stdafx.h"
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
void Enter(OpAmps &EnterElement, unsigned long &database_length);

void Save(OpAmps *SaveElement, unsigned long &database_length);

void Load(OpAmps *LoadElement, unsigned long &database_length);

int Sort(OpAmps *SortDatabase, unsigned long &database_length);

void Display(OpAmps *DisplayDatabase, unsigned long &database_length);

void qsort(void* OpAmps, size_t &database_length, size_t size_of_elements, int(*compare)(const void*, const void*));

int compare(const void* a, const void* b);

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
			Save(OpAmp, database_length);
			break;

		case '3':
			Load(OpAmp, database_length);
			break;

		case '4':
			Sort(OpAmp, database_length);
			break;

		case '5':
			Display(OpAmp, database_length);
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
void Enter(OpAmps &EnterElement, unsigned long &database_length)
{

	//DATABASE_FILENAME;

	// if the database is full, inform the user

	if (database_length == DATABASE_MAX) {
		cout << "The database is full" << "\n";
	}
	else
	{

		//OpAmps AddOpAmp;
		//OpAmps *pOpAmps;
		//pOpAmps = &AddOpAmp;

		/*OpAmps OpAmp;*/
		OpAmps *pOpAmps;
		pOpAmps = &EnterElement;

		cout << "Enter OpAmp name: ";
		cin >> pOpAmps->Name;
		cout << "Enter Pin count: ";
		cin >> pOpAmps->PinCount;
		cout << "Enter Slew Rate: ";
		cin >> pOpAmps->SlewRate;

		database_length++;

		cout << "\nYou have entered:\n";
		cout << pOpAmps->Name << "\n";
		cout << pOpAmps->PinCount << "\n";
		cout << pOpAmps->SlewRate << "\n";
		cout << "Value in database: " << database_length << "\n";

		return;

	}

}
// Save the database to the file specified by DATABASE_FILENAME. If the file 
// exists it is simply overwritten without asking the user.
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void Save(OpAmps *SaveElement, unsigned long &database_length)
{
	fstream output_file;  // file stream for output
	/*OpAmps AddOpAmp;
	OpAmps *pOpAmps;
	pOpAmps = &AddOpAmp;*/
	// open the file
	output_file.open(DATABASE_FILENAME, ios::out);


	if (output_file.is_open() == true) {
		// write length information to file
		output_file << database_length << "\n";
		// write data to file
		for (int i = 0; i < database_length; i++)
		{
			output_file << "\n" << (SaveElement + i)->Name << "\n";
			output_file << (SaveElement + i)->PinCount << "\n";
			output_file << (SaveElement + i)->SlewRate << "\n";

		}

	}
	else
	{
		cout << "Unable to open file" << "\n";
		return;
	}
	cout << "Save completed" << "\n";
	// close the file
	output_file.close();
}


// Load the database from the file specified by DATABASE_FILENAME. If the file
// exists it simply overwrites the data currently in memory without asking
// the user.
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void Load(OpAmps *LoadElement, unsigned long &database_length) {

	fstream input_file;  // file stream for input
	// open the file
	input_file.open(DATABASE_FILENAME, ios::in);


	if (input_file.is_open() == true) {
		// load database length information from file
		input_file >> database_length;
		input_file << "\n";
		// load data from file
		for (int i = 0; i < database_length; i++)
		{
			input_file << "\n";
			input_file >> (LoadElement + i)->Name;
			input_file << "\n";
			input_file >> (LoadElement + i)->PinCount;
			input_file << "\n";
			input_file >> (LoadElement + i)->SlewRate;
			input_file << "\n";
			//input_file >> "\n" << (LoadElement + i)->Name >> "\n";
			//input_file >> (LoadElement + i)->PinCount >> "\n";
			//input_file >> (LoadElement + i)->SlewRate >> "\n";

		}
		cout << "Load Successful" << "\n";
	}
	else
	{
		cout << "Unable to open file" << "\n";
		return;
	}
	// close the file
	input_file.close();
}


// Sort the database either using the name of the op-amps or using the slew 
// rate values.
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
int Sort(OpAmps *SortDatabase, unsigned long &database_length) {

	char UserInput;
	//
	//	// show the menu of options
	cout << endl;
	cout << "Sorting options" << endl;
	cout << "---------------" << endl;
	cout << "1. To sort by name" << endl;
	cout << "2. To sort by slew rate" << endl;
	cout << "3. No sorting" << endl << endl;
	//
	//	// get the user's choice of sorting operation required
	cout << "Enter your option: ";
	cin >> UserInput;
	cout << endl;
	//
	//	// act on the user's input
	switch (UserInput) {
	case '1':
		//AlphabetqSort(&SortDatabase, database_length);
		break;

	case '2':
		//SlewRateqSort(SortDatabase, database_length);
		break;

	case '3':
		return 0;
		break;

		//	<enter code here>
	}

}
// Compare function for qsort, to help sort the elements by the Name member of
// OpAmps.
// Items should be sorted into alphabetical order.
// Arguments:
//   (1) a database item
//   (2) a database item
// Returns: result of the comparison
void AlphabetqSort(OpAmps &SortDatabase, unsigned long &database_length) {

	//qsort(Name, database_length, sizeof(char), compare);
	//qsort(SortDatabase.Name, database_length, sizeof(int), a - b);

	//for (SortDatabase.Name == 0; SortDatabase.Name <= 9; SortDatabase.Name++) {



	//}

}



// Compare function for qsort, to help sort the elements by the SlewRate member of 
// OpAmps.
// Items should be sorted in increasing value of slew rate.
// Arguments:
//   (1) a database item
//   (2) a database item
// Returns: result of the comparison
void SlewRateqSort(OpAmps *Name, unsigned long &database_length) {

	//qsort(SortDatabase.Name, database_length, sizeof(int), a - b);



}



// Display all of the messages in the database.
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void Display(OpAmps *DisplayDatabase, unsigned long &database_length)
{
	fstream input_file;
	//fstream output_file;
	// if the database is empty, inform the user
	input_file.open(DATABASE_FILENAME, ios::in);
	//output_file.open(DATABASE_FILENAME, ios::out);

	if (input_file.is_open() == true) {
		input_file << database_length << "\n";
		if (database_length == 0)
		{
			cout << "Database is empty" << "\n";
			return;
		}
	// if the database is not empty, display all the elements in the database
		else
		{

			for (int i = 0; i < database_length; i++)
		{
			cout << "\n" << (DisplayDatabase + i)->Name << "\n";
			cout << (DisplayDatabase + i)->PinCount << "\n";
			cout << (DisplayDatabase + i)->SlewRate << "\n";

		}

	}
	}
	else
	{
		cout << "Unable to open file" << "\n";
		return;
	}

}
