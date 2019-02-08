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
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//class OpAmps {
//
//private:
//	string Name; // the name of the op-amp (e.g. "741")
//	unsigned int PinCount; // the number of pins in the package
//	double SlewRate; // the slew rate in volts per microsecond
//public:
//	OpAmps();
//	//string Na, unsigned int Pin, double Slew
//	void GetNewOpAmp();
//	void DisplayOpAmps();
//	string GetName(string);
//	int GetPinCount(unsigned int);
//	double GetSlewRate(double);
//	//friend ostream & operator<<(ostream &, const DatabaseOpAmps & Main);
//	//friend ifstream & operator>>(ifstream &, const DatabaseOpAmps &);
//	~OpAmps();
//};



//class SortOpAmps : OpAmps {
//	
//	public:
//	void Sort(OpAmps*, unsigned long);
//	bool SortName(const OpAmps &First, const OpAmps &Second);
//	bool SortSlewRate(const OpAmps &First, const OpAmps &Second);
//
//
//};

class OpAmps { // OpAmp Class

private:
	string Name; // the name of the op-amp (e.g. "741")
	unsigned int PinCount; // the number of pins in the package
	double SlewRate; // the slew rate in volts per microsecond
public:
	OpAmps();
	//string Na, unsigned int Pin, double Slew
	void GetNewOpAmp();
	void DisplayOpAmps();
	string GetName();
	int GetPinCount();
	double GetSlewRate();
	friend ostream & operator<<(ostream &OutStream, const OpAmps &ObOpAmps);
	friend ifstream & operator>>(ifstream & Instream, OpAmps & ObOpAmps);
	//friend bool SortName(OpAmps &First, OpAmps &Second);
	//friend bool SortSlewRate(OpAmps &First, OpAmps &Second);
	~OpAmps();
};

class DatabaseOpAmps {
public:
	DatabaseOpAmps(OpAmps*);
	void Enter();
	void Save();
	void Load();
	void Sort(OpAmps *);
	void Display();

	~DatabaseOpAmps();
private:

	bool SortName(const DatabaseOpAmps &First,const DatabaseOpAmps &Second);
	bool SortSlewRate(const DatabaseOpAmps &First,const DatabaseOpAmps &Second);
	unsigned long database_length; // length of database
	OpAmps *ObOpAmps; // Create object of an array of OpAmp objects

};

OpAmps::OpAmps() { // constructor
	//string Name;
	//unsigned int PinCount;
	//double SlewRate;
}

OpAmps::~OpAmps() { // destructor

	cout << "Close OpAmps object";

}


DatabaseOpAmps::DatabaseOpAmps(OpAmps* Data) { // constructor
	ObOpAmps = Data;
	database_length = 0;
}

DatabaseOpAmps::~DatabaseOpAmps() { // destructor

	cout << "Database has been closed";
}

// the length of the fixed array to be used for database - must be at least one
// and no greater the maximum value allowed in an unsigned long (see the file 
// limits.h)
#define DATABASE_MAX 10

// file used for the database
#define DATABASE_FILENAME "database.txt"



// Control the entering, saving, loading, sorting and displaying of elements in 
// the database
// Arguments: None
// Returns: 0 on completion
int main()
{
	OpAmps OpAmp[DATABASE_MAX];   // the OpAmp object
	DatabaseOpAmps Main(OpAmp); // Object OpAmp array database
	//SortOpAmps MainSort;
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

string OpAmps::GetName() {

	return Name;
}

int OpAmps::GetPinCount() {

	return PinCount;
}

double OpAmps::GetSlewRate() {

	return SlewRate;
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

	cout << Name << " \t";
	cout << PinCount << "\t ";
	cout << SlewRate << "\t";
	cout << endl;
}

// Allow the user to enter a new element into the database. Note that the data 
// is simply added to the end the database (if not full) and no sorting is
// carried out.
// Arguments:
//   (1) the element in the database to be entered
//   (2) the position of the element in the database
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
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
 void DatabaseOpAmps::Save()
{
	 fstream Outstream;
						 
	Outstream.open(DATABASE_FILENAME, ios::out);  // open the file

		
		Outstream << database_length << endl << endl; // add database length to file

		for (unsigned long i = 0; i < database_length; i++)
		{
			Outstream << ObOpAmps[i]; // Overloading << function to pass database object

		}

		cout << "Saved!" << database_length << endl;
	Outstream.close();

}


// Load the database from the file specified by DATABASE_FILENAME. If the file
// exists it simply overwrites the data currently in memory without asking
// the user
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
void DatabaseOpAmps::Load()
{
	ifstream Instream;  // file stream for input

						 
	Instream.open(DATABASE_FILENAME, ios::in); // open the file

	// access file if opened
	if (Instream.good()) {

		// load length information from file
		Instream >> database_length; // Load database length
		//Instream << endl;

		// load data from file
		for (unsigned long i = 0; i < database_length; i++) {
			Instream >> ObOpAmps[i]; // Overloaded >> operator to pass database object
			

		}
		
	}
	cout << "Loaded!" << endl;

	 //close the file
	Instream.close();
}


 //Sort the database either using the name of the op-amps or using the slew rate
 //values
 //Arguments:
 //  (1) the database
 //  (2) the length of the database
 //Returns: void
void DatabaseOpAmps::Sort(OpAmps *)
{
	char UserInput;
	size_t size = sizeof(ObOpAmps) / sizeof(ObOpAmps[0]);
	//vector<string> stringvector;
	//vector<double> doublevector;
	vector<string> Obvector;
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
		//stringvector.assign(ObOpAmps, ObOpAmps+database_length);

		//stable_sort(stringvector.begin, stringvector.end, SortSlewRate);
		// sort according to name (in alphabetical order)
		//sort(Op, length, sizeof(OpAmps), SortName);
		//sort(ObOpAmps, ObOpAmps + sizeof(ObOpAmps), SortName);
		//sort(ObOpAmps[0].GetName(), ObOpAmps[database_length - 1].GetName());
		//sort(&ObOpAmps[0], &ObOpAmps[database_length - 1]);
		//stable_sort(ObOpAmps, ObOpAmps +  size, SortName);
		//sort(begin(ObOpAmps->GetName), end(ObOpAmps->GetName));
		break;

	case '2':
		// sort according to slew rate (in increasing slew rate order)
		//qsort(ObOpAmps, database_length, sizeof(OpAmps), SortSlewRate);
		//sort(ObOpAmps, SortSlewRate);
		//cout << ObOpAmps[0];
		//cout << ObOpAmps[1];
		//cout << ObOpAmps[2];
		cout << size;
		cout << endl;
		cout << sizeof(ObOpAmps);
		cout << endl;
		cout << ObOpAmps + database_length;
		//sort(ObOpAmps[0].GetName(), ObOpAmps[database_length].GetName());
		break;

	case '3':
		return;

	default:
		cout << "Invalid entry" << endl << endl;
		break;
	}
}


// Compare function for sort, to help sort the elements by the Name member of 
// OpAmps.
// Items should be sorted in alphabetical order.
// Arguments:
//   (1) a database item
//   (2) a database item
// Returns: result of the comparison
//bool SortOpAmps::SortName(const OpAmps &First, const OpAmps &Second)
bool DatabaseOpAmps::SortName(const DatabaseOpAmps &First,const DatabaseOpAmps &Second)
{
//	//return strcmp(((OpAmps *)First)->Name, ((OpAmps *)Second)->Name);
//	//return strcmp(First.Name, Second.Name) < 0;
//	//return First.GetName() < Second.GetName();
	return First.ObOpAmps->GetName() < Second.ObOpAmps->GetName();
//
}


// Compare function for sort, to help sort the elements by the SlewRate member 
// of OpAmps.
// Items should be sorted in increasing value of slew rate.
// Arguments:
//   (1) a database item
//   (2) a database item
// Returns: result of the comparison
bool DatabaseOpAmps::SortSlewRate(const DatabaseOpAmps &First, const DatabaseOpAmps &Second)
{
	//return (int)((((OpAmps *)First)->SlewRate > ((OpAmps *)Second)->SlewRate) ? 1 : -1);

	return First.ObOpAmps->GetSlewRate() < Second.ObOpAmps->GetSlewRate() ;
}

// Display all of the messages in the database.
// Returns: void
void DatabaseOpAmps::Display()
{
	// if the database is empty, display an error statement
	if (database_length == 0) {
		cout << "No elements in the database" << endl;
	}

	// if the database is not empty, display all the elements in the database
	else {

		// display a title
		cout << endl;
		cout << "Name\t Number of pins\t Slew rate" << endl;

		// display the elements
		for (unsigned long i = 0; i < database_length; i++) {

			ObOpAmps[i].DisplayOpAmps(); // Display all OpAmps in database
		}
	}
}
