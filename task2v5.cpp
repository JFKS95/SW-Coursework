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


class DatabaseOpAmps {
public:
	class OpAmps { // Nested OpAmp Class

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
		//friend ostream & operator<<(ostream &, const DatabaseOpAmps & Main);
		//friend ifstream & operator>>(ifstream &, const DatabaseOpAmps &);
		~OpAmps();
	};
	DatabaseOpAmps(OpAmps*);
	void Enter();
	void Save();
	void Load();
	void Sort();
	void Display();
	friend ostream & operator<<(ostream & OutStream, const DatabaseOpAmps &ObOpAmps);
	friend ifstream & operator>>(ifstream &, const DatabaseOpAmps &ObOpAmps); // For overloading for load function

	~DatabaseOpAmps();
private:


	unsigned long database_length; // length of database
	OpAmps *ObOpAmps; // Create object of an array of OpAmp objects

};

//class File {
//public:
//	File();
//
//
//};

DatabaseOpAmps::OpAmps::OpAmps() { // constructor
	string Name;
	unsigned int PinCount;
	double SlewRate;
}

DatabaseOpAmps::OpAmps::~OpAmps() { // destructor

	cout << "Close OpAmps object";

}


DatabaseOpAmps::DatabaseOpAmps(OpAmps* Data) { // constructor
	ObOpAmps = Data;
	database_length = 0;
}

DatabaseOpAmps::~DatabaseOpAmps() { // destructor

	cout << "Database has been closed";
}

//File::File() {
//	
//
//
//}

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
	DatabaseOpAmps::OpAmps OpAmp[DATABASE_MAX];   // the database
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
			cout << Main;
			break;

		case '3':
			//Main.Load("database.txt");
			break;

		case '4':
			//Main.Sort(OpAmp, database_length);
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

string DatabaseOpAmps::OpAmps::GetName() {

	return Name;
}

int DatabaseOpAmps::OpAmps::GetPinCount() {

	return PinCount;
}

double DatabaseOpAmps::OpAmps::GetSlewRate() {

	return SlewRate;
}

ostream & operator<<(ostream &OutStream, const DatabaseOpAmps &ObOpAmps) { // Overloading the << operator

	//ofstream output_file;
	//output_file.open(DATABASE_FILENAME, ios::out);
	//OutStream << ObOpAmps.database_length << endl << endl;

	//if (OutStream.good())
	//{
		OutStream << ObOpAmps.database_length << endl << endl;

		for (unsigned long i = 0; i < ObOpAmps.database_length; i++)
		{
			OutStream << ObOpAmps.ObOpAmps[i].GetName() << endl;
			OutStream << ObOpAmps.ObOpAmps[i].GetPinCount() << endl;
			OutStream << ObOpAmps.ObOpAmps[i].GetSlewRate() << endl << endl;

		}

	//}

	return OutStream;

	//if (output_file.good())
	//{
	//	output_file << Main.database_length << endl << endl;

	//	for (unsigned long i = 0; i < Main.database_length; i++)
	//	{
	//		output_file << Main.ObOpAmps[i].GetName() << endl;
	//		output_file << Main.ObOpAmps[i].GetPinCount() << endl;
	//		output_file << Main.ObOpAmps[i].GetSlewRate() << endl << endl;
	//		//OutStream <<  << endl;
	//		//OutStream << Main.ObOpAmps. << endl << endl;

	//	}

	//}

	//return output_file;

}

ifstream & operator>>(ifstream & InStream, const DatabaseOpAmps & ObOpAmps) { // or this bit

	//InStream >> ObOpAmps.database_length >> endl >> endl;

	if (InStream.good())
	{
		//InStream >> OpAmps.database_length;

		for (unsigned long i = 0; i < ObOpAmps.database_length; i++)
		{
			//InStream >> ObOpAmps.ObOpAmps[i].GetName() >> endl;
			//InStream >> ObOpAmps.ObOpAmps[i].GetPinCount() >> endl;
			//InStream >> ObOpAmps.ObOpAmps[i].GetSlewRate() >> endl >> endl;

		}


	}

	return InStream;

}

void DatabaseOpAmps::OpAmps::GetNewOpAmp() { // Get data for new OpAmp

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

void DatabaseOpAmps::OpAmps::DisplayOpAmps() { // Display OpAmps

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
//void DatabaseOpAmps::Save()
//{
//	fstream output_file;  // file stream for output
//
//						  // open the file
//	output_file.open(DATABASE_FILENAME, ios::out);
//
//	// access file if opened
//	if (output_file.good()) {
//
//		// write length information to file
//		output_file << database_length << endl << endl;
//
//		// write database to fil
//		for (unsigned long i = 0; i < database_length; i++) {
//			output_file << Op[i].Name << endl;
//			output_file << Op[i].PinCount << endl;
//			output_file << Op[i].SlewRate << endl << endl;
//		}
//	}
//
//	 //close the file
//	output_file.close();
//}

 void DatabaseOpAmps::Save()
{
	
	 std::ofstream Outstream;  // file stream for output

						  // open the file
	Outstream.open(DATABASE_FILENAME, ios::out);


	Outstream << ObOpAmps;
	//output_file << database_length << endl << endl;
	
	// access file if opened
	// << ObOpAmps;
	//output_file << ObOpAmps->GetName() << endl; // it is only showing the register and does not run overloaded operator <<
	//output_file << ObOpAmps->GetPinCount() << endl;
	//output_file << ObOpAmps->GetSlewRate() << endl << endl;
	//close the file
	Outstream.close();

}


// Load the database from the file specified by DATABASE_FILENAME. If the file
// exists it simply overwrites the data currently in memory without asking
// the user
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
//void DatabaseOpAmps::Load()
//{
//	fstream input_file;  // file stream for input
//
//						 // open the file
//	input_file.open(DATABASE_FILENAME, ios::in);
//
//	// access file if opened
//	if (input_file.good()) {
//
//		// load length information from file
//		input_file >> database_length;
//		input_file << endl;
//
//		// load data from file
//		for (unsigned long i = 0; i < database_length; i++) {
//			input_file >> ObOpAmps->GetName() << endl; // it is only showing the register and does not run overloaded operator <<
//			input_file >> ObOpAmps->GetPinCount() << endl;
//			input_file >> ObOpAmps->GetSlewRate() << endl << endl;
//		}
//	}
//
//
//	 //close the file
//	input_file.close();
//}


//char SortOpAmps::GetName() const {
//
//
//	return
//
//}
//
//int	 SortOpAmps::GetSlewRate() const {
//
//	return 
//
//}




// Sort the database either using the name of the op-amps or using the slew rate
// values
// Arguments:
//   (1) the database
//   (2) the length of the database
// Returns: void
//void DatabaseOpAmps::Sort(OpAmps* Op, unsigned long length)
//{
//	char UserInput;
//
//	// show the menu of options
//	cout << endl;
//	cout << "Sorting options" << endl;
//	cout << "---------------" << endl;
//	cout << "1. To sort by name" << endl;
//	cout << "2. To sort by slew rate" << endl;
//	cout << "3. No sorting" << endl << endl;
//
//	// get the user's choice of sorting operation required
//	cout << "Enter your option: ";
//	cin >> UserInput;
//	cout << endl;
//
//	// act on the user's input
//	switch (UserInput) {
//	case '1':
//		// sort according to name (in alphabetical order)
//		//sort(Op, length, sizeof(OpAmps), SortName);
//		sort(Op, Op + sizeof(OpAmps), SortName);
//		break;
//
//	case '2':
//		// sort according to slew rate (in increasing slew rate order)
//		//qsort(Op, length, sizeof(OpAmps), SortSlewRate);
//		sort(Op, Op + sizeof(OpAmps), SortSlewRate);
//		break;
//
//	case '3':
//		return;
//
//	default:
//		cout << "Invalid entry" << endl << endl;
//		break;
//	}
//}


// Compare function for qsort, to help sort the elements by the Name member of 
// OpAmps.
// Items should be sorted in alphabetical order.
// Arguments:
//   (1) a database item
//   (2) a database item
// Returns: result of the comparison
//bool SortOpAmps::SortName(const OpAmps &First, const OpAmps &Second)
//bool SortOpAmps::SortName(const OpAmps &First, const OpAmps &Second)
//{
//	//return strcmp(((OpAmps *)First)->Name, ((OpAmps *)Second)->Name);
//	//return strcmp(First.Name, Second.Name) < 0;
//	return First.Name < Second.Name;
//}


// Compare function for qsort, to help sort the elements by the SlewRate member 
// of OpAmps.
// Items should be sorted in increasing value of slew rate.
// Arguments:
//   (1) a database item
//   (2) a database item
// Returns: result of the comparison
//bool SortOpAmps::SortSlewRate(const OpAmps &First, const OpAmps &Second)
//{
//	//return (int)((((OpAmps *)First)->SlewRate > ((OpAmps *)Second)->SlewRate) ? 1 : -1);
//
//	return First.SlewRate < Second.SlewRate;
//}

// Display all of the messages in the database.
// Arguments:
//   (1) the database
//   (2) the length of the database
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
