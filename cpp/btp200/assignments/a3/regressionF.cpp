// Regression Analysis Calculator
// Assignment 3
// regressionF.cpp
// BTP200
// Feb 16 2005

#include <iostream>
#include <iomanip>
using namespace std;
#include "DataSet.h"
#include "regressionF.h"

int main ( ) {
	DataSet data[MAX_DATA_SETS];
	int choice, noDataSets;
	bool keepgoing;

	noDataSets = 0;
	keepgoing = true;
	cout << "Regression Analysis (x on y)\n"
		    "============================" << endl;
	do {
		choice = menu();
		switch (choice) {
			case LOAD:
				loadDataSet(data, noDataSets);
				break;
			case DISPLAY:
				displayDataSet(data, noDataSets);
				break;
			case ADD:
				addDataSets(data, noDataSets);
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
			case REMOVE:
				removeDataSet(data, noDataSets);
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

	return 0;
}

int menu(void) {
	int choice;
	bool keepgoing;

	cout << endl;
	cout << "Choose one of the following options:" << endl;
	cout << LOAD    << " Load a data set from file" << endl;
	cout << CHAUV   << " Exclude outlier points in a data set" << endl;
	cout << ALLGOOD << " Include outlier points in calculations" << endl;
	cout << DISPLAY << " Display the data points for a data set" << endl;
	cout << ADD     << " Combine two data sets" << endl;
	cout << COMPARE << " Compare two data sets" << endl;
	cout << STATS   << " Display statistics for all data sets" << endl;
	cout << REMOVE  << " Remove a data set from the list" << endl;
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
			cin.ignore(2000,'\n');
		} else {
			keepgoing = false;
		}
	} while (keepgoing);

	cout << endl;
	return choice;
}

// returns a positive value
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

// load a Data Set
void loadDataSet(DataSet* data, int& noDataSets) {
	char filename[MAX_FILENAME];

	if (noDataSets < MAX_DATA_SETS) {
		cout << "Enter filename : ";
		cin >> filename;
		if (data[noDataSets].loadFromFile(filename))
			++noDataSets;
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

// add one Data Set to another Data Set
void addDataSets(DataSet* data, int& noDataSets) {
	int a, b;
	bool keeptrying;
	char filename[MAX_FILENAME];

	a = findFile("Enter filename a : ", data, noDataSets);
	if (a != -1) {
		b = findFile("Enter filename b : ", data, noDataSets);
		if (b != -1) {
			DataSet concatenatedData = data[a] + data[b];
			keeptrying = true;
			do {
				cout << "Enter filename for a + b : ";
				cin >> filename;
				if (concatenatedData.saveToFile(filename)) {
					if (noDataSets < MAX_DATA_SETS)
						data[noDataSets++] = concatenatedData;
					keeptrying = false;
				} else 
					cout << "File " << filename << " not available" << endl;
			} while (keeptrying);
		}
	}
}

// compares a Data Set to another Data set
void compareDataSets(const DataSet* data, int noDataSets) {
	int j, k;

	j = findFile("Enter first filename : ", data, noDataSets);
	if (j != -1) {
		k = findFile("Enter second filename : ", data, noDataSets);
		if (k != -1) {
			if (data[j] == data[k])
				cout << "\nData sets match" << endl;
			else
				cout << "\nData sets do not match" << endl;
		}
	}
}

// set outliers for a Data Set
void setOutliers(DataSet* data, int noDataSets) {
	int j;

	j = findFile("Enter filename : ", data, noDataSets);
	if (j != -1)
		data[j].include(getPosDouble());
}

// clear Outliers for a Data Set
void clearOutliers(DataSet* data, int noDataSets) {
	int j;

	j = findFile("Enter filename : ", data, noDataSets);
	if (j != -1)
		data[j].include();
}

// remove a Data Set from the array of Data Sets
void removeDataSet(DataSet* data, int& noDataSets) {
	int j;

	j = findFile("Enter filename  to be removed : ", data, noDataSets);
	if (j != -1) {
		for (int i = j; i < noDataSets - 1; i++)
			data[i] = data[i+1];
		--noDataSets;
	}
}

// set display width for filename
void displayStats(const DataSet* data, int noDataSets) {
	cout << "     Slope Intercept Correlation Filename" << endl;
	for (int i = 0; i < noDataSets; i++) {
		cout << data[i] << endl;
	}
}
