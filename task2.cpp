// Title
//
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

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

class OpAmps {

	private:
		char Name[20]; // the name of the op-amp (e.g. "741")
		unsigned int PinCount; // the number of pins in the package
		double SlewRate; // the slew rate in volts per microsecond
	public:
		void Enter(OpAmps&, unsigned long&);
		void Save(const OpAmps*, unsigned long);
		void Load(OpAmps*, unsigned long&);
		void Sort(OpAmps*, unsigned long);
		void Display(const OpAmps*, unsigned long);

		friend bool SortName(const OpAmps &First, const OpAmps &Second);
		friend bool SortSlewRate(const OpAmps &First, const OpAmps &Second);
	/*	friend bool SortName(const void*, const void*);
		friend bool SortSlewRate(const void*, const void*);*/
	//friend int SortName(const OpAmps&, const OpAmps&);
	//friend int SortSlewRate(const OpAmps&, const OpAmps&);
};



// the length of the fixed array to be used for database - must be at least one
// and no greater the maximum value allowed in an unsigned long (see the file 
// limits.h)
#define DATABASE_MAX 10

// file used for the database
#define DATABASE_FILENAME "database.txt"

// function prototypes
//void Enter(OpAmps&, unsigned long&);
//void Save(const OpAmps*, unsigned long);
//void Load(OpAmps*, unsigned long&);
//void Sort(OpAmps*, unsigned long);
//int SortName(const void*, const void*);
//int SortSlewRate(const void*, const void*);
//void Display(const OpAmps*, unsigned long);

// Control the entering, saving, loading, sorting and displaying of elements in 
// the database
// Arguments: None
// Returns: 0 on completion
int main()
{
	OpAmps OpAmp[DATABASE_MAX];   // the database
	OpAmps Main;
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
			Main.Enter(OpAmp[database_length], database_length);
			break;

		case '2':
			Main.Save(OpAmp, database_length);
			break;

		case '3':
			Main.Load(OpAmp, database_length);
			break;

		case '4':
			Main.Sort(OpAmp, database_length);
			break;

		case '5':
			Main.Display(OpAmp, database_length);
			break;

		case '6':
			return 0;

		default:
			cout << "Invalid entry" << endl << endl;
			break;
		}
	}
}


// Allow the user to enter a new element into the database. Note that the data 
// is simply added to the end the database (if not full) and no sorting is
// carried out.
// Arguments:
//   (1) the element in the database to be entered
//   (2) the position of the element in the database
// Returns: void
void OpAmps::Enter(OpAmps& Op, unsigned long& length)
{
	// if the database is full, inform the user
	if (length == DATABASE_MAX) {
		cout << "The database is full" << endl;
	}

	// if the database is not full, get the data from the user and alter the database
	// length
	else {
		cout << "Add new data" << endl;
		cout << "------------" << endl;
		cout << "Enter op-amp name: ";
		cin >> Op.Name;
		cout << "Enter number of pins: ";
		cin >> Op.PinCount;
		cout << "Enter slew rate: ";
		cin >> Op.SlewRate;
		cout << endl;
		length++;
	}
}


// Save the database to the file specified by DATABASE_FILENAME. If the file
// exists it is simply overwritten without asking the user
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void OpAmps::Save(const OpAmps* Op, unsigned long length)
{
	fstream output_file;  // file stream for output

						  // open the file
	output_file.open(DATABASE_FILENAME, ios::out);

	// access file if opened
	if (output_file.good()) {

		// write length information to file
		output_file << length << endl << endl;

		// write database to file
		for (unsigned long i = 0; i<length; i++) {
			output_file << Op[i].Name << endl;
			output_file << Op[i].PinCount << endl;
			output_file << Op[i].SlewRate << endl << endl;
		}
	}

	// close the file
	output_file.close();
}


// Load the database from the file specified by DATABASE_FILENAME. If the file
// exists it simply overwrites the data currently in memory without asking
// the user
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void OpAmps::Load(OpAmps* Op, unsigned long& length)
{
	fstream input_file;  // file stream for input

						 // open the file
	input_file.open(DATABASE_FILENAME, ios::in);

	// access file if opened
	if (input_file.good()) {

		// load length information from file
		input_file >> length;

		// load data from file
		for (unsigned long i = 0; i<length; i++) {
			input_file >> Op[i].Name;
			input_file >> Op[i].PinCount;
			input_file >> Op[i].SlewRate;
		}
	}

	// close the file
	input_file.close();
}


// Sort the database either using the name of the op-amps or using the slew rate
// values
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void OpAmps::Sort(OpAmps* Op, unsigned long length)
{
	char UserInput;

	// show the menu of options
	cout << endl;
	cout << "Sorting options" << endl;
	cout << "---------------" << endl;
	cout << "1. To sort by name" << endl;
	cout << "2. To sort by slew rate" << endl;
	cout << "3. No sorting" << endl << endl;

	// get the user's choice of sorting operation required
	cout << "Enter your option: ";
	cin >> UserInput;
	cout << endl;

	// act on the user's input
	switch (UserInput) {
	case '1':
		// sort according to name (in alphabetical order)
		//sort(Op, length, sizeof(OpAmps), SortName);
		sort(Op, Op + sizeof(OpAmps), SortName);
		break;

	case '2':
		// sort according to slew rate (in increasing slew rate order)
		//qsort(Op, length, sizeof(OpAmps), SortSlewRate);
		sort(Op, Op + sizeof(OpAmps), SortSlewRate);
		break;

	case '3':
		return;

	default:
		cout << "Invalid entry" << endl << endl;
		break;
	}
}


// Compare function for qsort, to help sort the elements by the Name member of 
// OpAmps.
// Items should be sorted in alphabetical order.
// Arguments:
//   (1) a database item
//   (2) a database item
// Returns: result of the comparison
bool SortName(const OpAmps &First, const OpAmps &Second)
{
	//return strcmp(((OpAmps *)First)->Name, ((OpAmps *)Second)->Name);
	return strcmp(First.Name, Second.Name) < 0;
}


// Compare function for qsort, to help sort the elements by the SlewRate member 
// of OpAmps.
// Items should be sorted in increasing value of slew rate.
// Arguments:
//   (1) a database item
//   (2) a database item
// Returns: result of the comparison
bool SortSlewRate(const OpAmps &First, const OpAmps &Second)
{
	//return (int)((((OpAmps *)First)->SlewRate > ((OpAmps *)Second)->SlewRate) ? 1 : -1);

	return First.SlewRate < Second.SlewRate;
}

// Display all of the messages in the database.
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void OpAmps::Display(const OpAmps* Op, unsigned long length)
{
	// if the database is empty, display an error statement
	if (length == 0) {
		cout << "No elements in the database" << endl;
	}

	// if the database is not empty, display all the elements in the database
	else {

		// display a title
		cout << endl;
		cout << "Name     Number of pins    Slew rate" << endl;

		// display the elements
		for (unsigned long i = 0; i<length; i++) {
			cout << Op[i].Name << "   ";
			cout << Op[i].PinCount << "   ";
			cout << Op[i].SlewRate << "   ";
			cout << endl;
		}
	}
}

