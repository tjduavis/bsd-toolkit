// Regression Analysis Calculator
// Assignments 2
// outliers.cpp
// BTP200
// Chris Szalwinski
// Feb 5 2005
// modified (CS) Feb 7 2005 - name() => label()

#include <iostream>
#include <iomanip>
using namespace std;
#include "DataSet.h"
#include "outliner.h"

int main ( ) {
	DataSet data[MAX_DATA_SETS];
	int choice, noDataSets;
	bool keepgoing;

	cout << "Regression Analysis (x on y)\n"
		 << "============================" << endl;
	noDataSets = 0;
	keepgoing = true;
	do {
		choice = menu();
		switch (choice) {
			case LOAD:
				loadDataSet(data, &noDataSets);
				break;
			case DISPLAY:
				displayDataSet(data, noDataSets);
				break;
			case COMPARE:
				compareDataSets(data, noDataSets);
				break;
			case CHAUV:
				setOutliers(data, noDataSets);
				break;
			case ALLGOOD:
				clearOutliers(data, noDataSets);
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

	cout << "\nHave a Nice Day!" << endl;
	return 0;
}

int menu(void) {
	int choice;
	bool keepgoing;

	cout << "\nChoose one of the following options:" << endl;
	cout << LOAD    << " Load a data set from file" << endl;
	cout << CHAUV   << " Exclude outlier points in a data set" << endl;
	cout << ALLGOOD << " Include outlier points in the calculations" << endl;
	cout << DISPLAY << " Display the values for a data set" << endl;
	cout << COMPARE << " Compare two data sets" << endl;
	cout << STATS   << " Display statistics for all data sets" << endl;
	cout << QUIT    << " Quit" << endl;
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

	return choice;
}

// returns a positive value
double getPosDouble(const char* message) {
    double value;
    bool ok;

    ok = false;
    do {
		cout << message;
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

// load a Data Set
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

// display a data set
void displayDataSet(const DataSet* data, int noDataSets) {
	int j;

	j = findFile("Enter filename to be displayed : ", data, noDataSets);
	if (j != -1)
		data[j].display();
}

// compares a Data Set to another Data set
void compareDataSets(const DataSet* data, int noDataSets) {
	int j, k;

	j = findFile("Enter first filename  : ", data, noDataSets);
	if (j != -1) {
		k = findFile("Enter second filename : ", data, noDataSets);
		if (k != -1) {
			if (data[j] == data[k])
				cout << "Data Sets Match" << endl;
			else
				cout << "Data Sets Do Not Match" << endl;
		}
	}
}

// set outliers for a Data Set
void setOutliers(DataSet* data, int noDataSets) {
	int j;

	j = findFile("Enter filename : ", data, noDataSets);
	if (j != -1)
		data[j].include(getPosDouble("Positive tolerance : "));
}

// clear Outliers for a Data Set
void clearOutliers(DataSet* data, int noDataSets) {
	int j;

	j = findFile("Enter filename : ", data, noDataSets);
	if (j != -1)
		data[j].include();
}

// display stats for all Data Sets
void displayStats(const DataSet* data, int noDataSets) {

	cout << setw(MAX_FILENAME-1) << left << "Filename" << right;
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