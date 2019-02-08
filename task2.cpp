//				task 2 Software Engineering Coursework 18WSB014
//								 By Joseph Stone
//							  	    B526838
//							LOUGHBOROUGH UNIVERSITY
//								  08/02/2019
//
//		    A program used to manage a small database of OpAmp objects
//
//    The purpose of this program is to outline the benefits of using object
//		 				oriented programming techniques
//
//		  					  General description
//
// The program  consists of an array of OpAmp objects known as DatabaseOpAmps, with a limit of DATABASE_MAX OpAmp objects. Each
// OpAmp object contains the operation amplifier name, the number of pins in the package and stores the slew rate of the device.
//
// New OpAmp objects are added by the user 
// New elements can be added into the database by the user. The database can be saved
// to disk or loaded from disk. The database elements can be sorted either by name or
// by slew rate. There is also the facility to display the elements.
//
// Only a single database is required and the file name is fixed in the code as 
// DATABASE_FILENAME. This means that each time the database is saved to disk,
// any previous data in the file is overwritten. Also, when a database is loaded
// from a file it should overwrite any data already in memory.

#include <iostream>
#include <fstream>
#include <string> // to allow variable type 'string'
#include <algorithm> // Used to enable C++ sort function

using namespace std;

// OpAmp Class consists of three private members, Name, PinCount, and SlewRate
// these are the main variables that make up the object's data
// A public accessor function DisplayOpAmps outputs the data to cout
// A 'mutator' function GetNewOpAmp allows the user to enter a new OpAmp
class OpAmps { 

protected:
	string Name; // the name of the op-amp (e.g. "741")
	unsigned int PinCount; // the number of pins in the package
	double SlewRate; // the slew rate in volts per microsecond
public:
	OpAmps(); // OpAmps contructor
	void GetNewOpAmp(); // Enter new OpAmp member function
	void DisplayOpAmps(); // Display list of OpAmps member function
	friend ostream & operator<<(ostream &OutStream, const OpAmps &ObOpAmps); // Overload << operator to work with object ObOpAmps
	friend ifstream & operator>>(ifstream & Instream, OpAmps & ObOpAmps); // Overload >> operator to work with object ObOpAmps
	friend bool SortName(const OpAmps &First, const OpAmps &Second);	 //
	friend bool SortSlewRate(const OpAmps &First, const OpAmps &Second); // friend functions called to access private member data for comparison when sorting
	~OpAmps(); // destructor
};

OpAmps::OpAmps() { // constructor initalisation
	Name = "";
	PinCount = 0;
	SlewRate = 0;
}

OpAmps::~OpAmps() { // destructor

}

// Class DatabaseOpAmps contains member functions for managing a database of OpAmp Objects
// Such as entering a new OpAmp, Saving the current database, Loading from a pre-existing file,
// displaying the array of OpAmp objects and sorting the OpAmps into a preferred arrangement
class DatabaseOpAmps {
public:
	DatabaseOpAmps(OpAmps*); // passes a point to an array of OpAmp objects
	friend class OpAmps;
	void Enter();
	void Save();
	void Load();
	void Sort(OpAmps *); // passes a point to an array of OpAmp objects
	void Display();
	~DatabaseOpAmps();
private:
	unsigned long database_length; // length of database
	OpAmps *ObOpAmps; // Create object of an array of OpAmp objects
};

DatabaseOpAmps::DatabaseOpAmps(OpAmps* Data) { // constructor
	ObOpAmps = Data; // initialises array od OpAmp objects
	database_length = 0; //initialise database length value
}

DatabaseOpAmps::~DatabaseOpAmps() { // destructor for closing database
	cout << "Database has been closed. Goodbye\n";
}

// the length of the fixed array to be used for database
#define DATABASE_MAX 10

// file used for the database
#define DATABASE_FILENAME "database.txt"

//Menu class that produces code for the generic main function
class Menu {
public:
	Menu() { MenuCreate(); } // Menu constructor
	int MenuCreate();
	~Menu();
private:
	char UserInput;
};

Menu::~Menu() { // destructor closing menu
	cout << "Menu has been closed. Goodbye.\n";
}

// Control the entering, saving, loading, sorting and displaying using member objects in 
// the DatabaseOpAmps class with the Menu class
// Arguments: None
// Returns: 0 on completion
int Menu::MenuCreate()
{
	OpAmps OpAmp[DATABASE_MAX];   // the OpAmp object array
	DatabaseOpAmps Main(OpAmp); // creation of Object OpAmp array database
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
			Main.Enter();
			break;

		case '2':
			Main.Save();
			break;

		case '3':
			Main.Load();
			break;

		case '4':
			Main.Sort(OpAmp);
			break;

		case '5':
			Main.Display();
			break;

		case '6':
			return 0;

		default:
			cout << "Invalid entry" << endl << endl;
			break;
		}
	}
}

ostream & operator<<(ostream &OutStream, const OpAmps &ObOpAmps) { // Overloading the << operator


	OutStream << ObOpAmps.Name << endl;
	OutStream << ObOpAmps.PinCount << endl;
	OutStream << ObOpAmps.SlewRate << endl << endl;

	return OutStream;

}

ifstream & operator>>(ifstream & InStream, OpAmps & ObOpAmps) { // Overloading the >> operator


	InStream >> ObOpAmps.Name;
	InStream >> ObOpAmps.PinCount;
	InStream >> ObOpAmps.SlewRate;

	return InStream;

}

void OpAmps::GetNewOpAmp() { // Get data for new OpAmp

	cout << "Add new data" << endl;
	cout << "------------" << endl;
	cout << "Enter op-amp name: ";
	cin >> Name;
	cout << "Enter number of pins: ";
	cin >> PinCount;
	cout << "Enter slew rate: ";
	cin >> SlewRate;
	cout << endl;
}

void OpAmps::DisplayOpAmps() { // Display OpAmps

	cout << Name << "\t";
	cout << PinCount << "\t\t";
	cout << SlewRate;
	cout << endl;
}

// Allow the user to enter a new element into the database. Note that the data 
// is simply added to the end the database (if not full) and no sorting is
// carried out.
// Arguments: none
// Returns: void
void DatabaseOpAmps::Enter()
{
	// if the database is full, inform the user
	if (database_length == DATABASE_MAX) {
		cout << "The database is full" << endl;
	}

	// if the database is not full, get the data from the user and alter the database
	else {
		ObOpAmps[database_length].GetNewOpAmp(); // Get data for new OpAmp
		database_length++; // increment by one
	}
}

// Save the database to the file specified by DATABASE_FILENAME. If the file
// exists it is simply overwritten without asking the user
// Arguments: none
// Returns: void
void DatabaseOpAmps::Save()
{
	fstream Outstream; // file stream for saving data to local location

	Outstream.open(DATABASE_FILENAME, ios::out);  // open the file database.txt and set Outstream as output

	Outstream << database_length << endl << endl; // add database length to file

	for (unsigned long i = 0; i < database_length; i++)
	{
		Outstream << ObOpAmps[i]; // Overloading << function to pass database object array
	}

	cout << "Saved!" << endl;
	Outstream.close();

}


// Load the database from the file specified by DATABASE_FILENAME. If the file
// exists it simply overwrites the data currently in memory without asking
// the user
// Arguments: none
// Returns: void
void DatabaseOpAmps::Load()
{
	ifstream Instream;  // file stream for input


	Instream.open(DATABASE_FILENAME, ios::in); // open the file database.txt and set Instream as input

	// access file if opened
	if (Instream.good()) {
		// load data from file
		Instream >> database_length; // Load database length
		
		for (unsigned long i = 0; i < database_length; i++) {
			Instream >> ObOpAmps[i]; // Overloaded >> operator to pass database object
		}
	}
	cout << "Loaded!" << endl;

	//close the file
	Instream.close();
}

// friend comparator functions to get/return value names and slew rates
bool SortName(const OpAmps &First, const OpAmps &Second)
{
	return First.Name < Second.Name; // returns boolean value based on difference to sort function
}

bool SortSlewRate(const OpAmps &First, const OpAmps &Second)
{
	return First.SlewRate < Second.SlewRate;
}
// I was unable to implement these functions into the DatabaseOpAmps class
// due to errors when passing them into the sort function.
// (I would be interested to find out the appropriate set up for this)

//This member function of DatabaseOpamps arranges the database either using the name of the OpAmps or using the slew rate
// It achieves this by using the friend functions SortSlewRate and SortName to compare private member values from type OpAmp
// The C++ function sort passes the arguments for first object and the last object in the array and sorts them accordingly.
//Arguments:
//  (1) Pointer to the Opamp object array
//Returns: void
void DatabaseOpAmps::Sort(OpAmps * SortAmps)
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
		sort(SortAmps, (SortAmps + database_length), SortName); // sort(First object in array,
		break;													//  Last array object in array, Sort by function/comparator)
	case '2':
		sort(SortAmps, (SortAmps + database_length), SortSlewRate);
		break;
	case '3':
		return;
	default:
		cout << "Invalid entry" << endl << endl;
		break;
	}
}
		
// Display all of the messages in the database.
// First the code gets the private member database_length value to check if the database if empty
// If it is not empty, it will print out all OpAmps within the database using the DisplayOpamps member function.
// Returns: void
void DatabaseOpAmps::Display()
{
	// if the database is empty, display an error statement
	if (database_length == 0) {
		cout << "No OpAmps in the database" << endl;
	}

	// if the database is not empty, display all the elements in the database
	else {

		// display a title
		cout << endl;
		cout << "Name\tNumber of pins\tSlew rate" << endl;

		// display the elements
		for (unsigned long i = 0; i < database_length; i++) {

			ObOpAmps[i].DisplayOpAmps(); // Display all OpAmps in database 
		}
	}
}

// the main function
// Arguments: None
// Returns: 0 on completion
int main() {
	Menu objectMainMenu; //Creation of object of type Menu
return 0;

}
