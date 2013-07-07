// Regression Analysis Calculator
// Assignment 1
// regression.cpp
// BTP200
// Jan 20 2005
// Jan 28 2005 - Data => DataSet

#include <iostream>
#include <iomanip>
using namespace std;
#include "DataSet.h"
#include "regression.h"

int main ( ) {
	bool keepgoing;
	int choice, noDataSets;
	DataSet data[MAX_DATA_SETS];

	noDataSets = 0;
	keepgoing = true;
	cout << "Regression analysis (x on y)\n"
		 << "============================\n";
	do {
		choice = menu();
		switch (choice) {
			case LOAD:
				loadDataSet(data, &noDataSets);
				break;
			case STATS:
				displayStats(data, noDataSets);
				break;
			case QUIT:
				keepgoing = false;
				break;
			default:
				cout << "Choice not implemented!" << endl;
		}
	} while (keepgoing);

	for (int i = 0; i < noDataSets; i++)
		data[i].closeUp();
	cout << "Have a nice day!" << endl;
	return 0;
}

// menu return user selection
int menu(void) {
	int choice;
	bool keepgoing;

	cout << endl;
	cout << "Choose one of the following options:" << endl;
	cout << ' ' << LOAD    << " Load a data set from file" << endl;
	cout << ' ' << STATS   << " Display statistics for all data sets" << endl;
	cout << ' ' << QUIT    << " Quit" << endl;
	do {
		keepgoing = true;
		cout << "Your selection : ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(2000,'\n');
		} else if (cin.get() != '\n') {
			cout << "**Trailing characters.  Try again.**" << endl;
			cin.ignore(2000,'\n');
		} else if (choice <  0 || choice >= NOPTIONS) {
			cout << "**Invalid choice.  Try again.**" << endl;
		} else {
			keepgoing = false;
		}
	} while (keepgoing);

	cout << endl;
	return choice;
}

// returns a positive double
double getPosDouble() {
    double value;
    bool ok;

    ok = false;
    do {
		cout << "Enter a positive value : ";
        cin  >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
            cout << "Invalid character.  Try Again." << endl;
        } else if (value <= 0.0) {
            cout << value << " is not positive.  Try Again." << endl;
            cin.ignore(2000, '\n');
        } else if (char(cin.get()) != '\n') {
            cout << "Trailing characters.  Try Again." << endl;
            cin.ignore(2000, '\n');
        } else
			ok = true;
    } while(!ok);

    return value;
}

// gets a filename from the user and returns the index of the
// filename in the array of files
int findFile(const char* message, const DataSet* data, int noDataSets) {
	char filename[MAX_FILENAME];
	int j = -1;

	cout << message;
	cin >> filename;
	j = -1;
	for (int i = 0; i < noDataSets; i++)
		if (!strcmp(filename, data[i].label()))
			j = i;
	if (j == -1)
		cout << "Filename " << filename << " not found" << endl;

	return j;
}

// loadDataSet loads a Data Set from a user specified file
void loadDataSet(DataSet* data, int* noDataSets) {
	char filename[MAX_FILENAME];

	if (*noDataSets < MAX_DATA_SETS) {
		cout << "Enter filename : ";
		cin >> filename;
		if (data[*noDataSets].loadFromFile(filename))
			++*noDataSets;
		else
			cout << "Filename " << filename << " not found" << endl;
	} else
		cout << "Data Set Limit Reached" << endl;
}

// displayStats display regression stats for all Data Sets
void displayStats(const DataSet* data, int noDataSets) {

	cout << setw(MAX_FILENAME-1) << left << "Data Set Label" << right;
	cout << "     Slope Intercept Correlation" << endl;
	cout.setf(ios::fixed);
	cout.precision(2);
	for (int i = 0; i < noDataSets; i++) {
		cout << setw(MAX_FILENAME-1) << left << data[i].label() << right;
		cout << setw(10) << data[i].slope() <<
				setw(10) << data[i].intercept() <<
				setw(10) << data[i].correlation() <<
				endl;
	}
	cout.unsetf(ios::fixed);
	cout.precision(6);
}


