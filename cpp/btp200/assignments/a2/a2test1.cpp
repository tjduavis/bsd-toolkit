/* BTP200.051 Assignment 2 Test Main
*  Regression Calculator with Outliers
*
*  Author: Chris Szalwinski
*  February 5 2005
*  a2test.cpp
*
*  Version 1.01
*  Last Modified February 5 (CS)
*  Last Modified February 14 (CS) - single value file error now can
*                                   return a[0] or emptyX
*
*  Set DEBUG to 1 for verbose debugging output
*  Set DEBUG to 0 for submission version
*/

#define DEBUG 0                     // Verbosity control
#define SCRATCH  "a1scratchFile"    // Scratch file for this assignment
#define TESTFILE "paleo.dat"        // Test file
#define TESTSLOPE     0.6354829386
#define TESTINTERCPT  2.5098043930
#define TESTCORREL    0.8771592639
#define TESTCHAUVTOL  1.00
#define TESTCHAUVOUT  7
#define TESTCHAUVSLP  0.4188912167
#define TESTCHAUVINT  4.7947409899
#define TESTCHAUVCOR  0.7404404704
#define DOUBLE_TOLERANCE 1.0E-5

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
using namespace std;
#include "DataSet.h"
bool DataPointTests(int& testNumber, int& totalPassed, int& totalTested);
bool DataSetTests(int& testNumber, int& totalPassed, int& totalTested);
void passed(const char* message, int i, int& totalPassed, int& total);
void failed(const char* message, int i, bool& ok, int& total);
bool doubleEqual(double a, double b);

int main() {
	int totalPassed = 0, totalTested = 0, testNumber = 0;

	// DataPoint Tests
	if (DEBUG)
		cout << "DataPoint Tests\n===============\n";
	if(DataPointTests(testNumber, totalPassed, totalTested)) {
		if (DEBUG) cout << '\n';
		cout << "DataPoint Tests passed!\n";
		if (DEBUG) cout << '\n';
	} else {
		cout << "\nDataPoint Tests had errors!\n";
		if (DEBUG) cout << '\n';
	}

	// DataSet Tests
	if (DEBUG)
		cout << "DataSet Tests\n=============\n";
	if(DataSetTests(testNumber, totalPassed, totalTested)) {
		if (DEBUG) cout << '\n';
		cout << "DataSet Tests passed!\n";
		if (DEBUG) cout << '\n';
	} else {
		cout << "\n\nDataSet Tests had errors!\n";
	}

	// Conclusion
	cout << "\nYour DatSet module has passed " << totalPassed <<
		" of " << totalTested << " tests\n";
	if (totalPassed == totalTested)
		cout << "\nCongratulations!!!   "
		"Your DataSet module is ready for submission\n\n";
	else
		cout << "Keep working on your code - good luck!\n";

	return 0;
}

/* DataPointTests tests the DataPoint class and returns true
   for success, false for one or more failed tests
   testNumber  - number of last test completed
   totalPassed - total number of tests passed
   totalTested - total number of tests attempted
*/
#define NP 4
bool DataPointTests(int& testNumber, int& totalPassed, int& totalTested) {
	bool ok;
	DataPoint point;
	FILE* fp = NULL;
	char message[61];
	double a[] = {12.3, 23.4, 5.46, 7.89}, emptyX = point.getx();
	double o[] = {12.3, 23.4, 5.46, 7.89}, emptyY = point.gety();

	// empty point tests
	DataPoint point2;
	if(point.getx() != emptyX) {
		sprintf(message, "getx() did not return %10.2lf", emptyX);
		failed(message, ++testNumber, ok, totalTested);
	} else
		passed("getx()", ++testNumber, totalPassed, totalTested);
	if(point.gety() != emptyY) {
		sprintf(message, "gety() did not return %10.2lf", emptyY);
		failed(message, ++testNumber, ok, totalTested);
	} else
		passed("gety()", ++testNumber, totalPassed, totalTested);

	// prepare scratch file
	fp = fopen(SCRATCH, "w+");
	if (fp) {
		ok = true;
		sprintf(message, "Load Scratch File (%s)", SCRATCH);
		passed(message, ++testNumber, totalPassed, totalTested);
		for (int i = 0; i < NP; i++)
			fprintf(fp, "%10.2lf%10.2lf\n", a[i], o[i]);
		fprintf(fp, "%10.2lf\n", a[0]);
		fprintf(fp, "a\n");
		rewind(fp);

		// check for NULL pointer
		if(point.loadFromFile(NULL) != EOF) {
			failed("loadFromFile(NULL) did not return EOF", ++testNumber, ok, totalTested);
		} else
			passed("loadFromFile(NULL)", ++testNumber, totalPassed, totalTested);
		if(point.getx() != emptyX) {
			sprintf(message, "getx() did not return %10.2lf", emptyX);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("getx()", ++testNumber, totalPassed, totalTested);
		if(point.gety() != emptyY) {
			sprintf(message, "gety() did not return %10.2lf", emptyY);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("gety()", ++testNumber, totalPassed, totalTested);

		// check for array of pairs
		for (int i = 0; i < NP; i++) {
			if(point.loadFromFile(fp) != 2) {
				failed("loadFromFile(fp) did not return 2", ++testNumber, ok, totalTested);
			} else
				passed("loadFromFile(fp)", ++testNumber, totalPassed, totalTested);
			if(point.getx() != a[i]) {
				sprintf(message, "getx() did not return %10.2lf", a[i]);
				failed(message, ++testNumber, ok, totalTested);
			} else
				passed("getx()", ++testNumber, totalPassed, totalTested);
			if(point.gety() != o[i]) {
				sprintf(message, "gety() did not return %10.2lf", o[i]);
				failed(message, ++testNumber, ok, totalTested);
			} else
				passed("gety()", ++testNumber, totalPassed, totalTested);
		}

		// check for single value
		if(point.loadFromFile(fp) != 1) {
			failed("loadFromFile(fp) did not return 1", ++testNumber, ok, totalTested);
		} else
			passed("loadFromFile(fp)", ++testNumber, totalPassed, totalTested);
		if(point.getx() != a[0] && point.getx() != emptyX) {
			sprintf(message, "getx() did not return %10.2lf or %10.2lf", a[0], emptyX);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("getx()", ++testNumber, totalPassed, totalTested);
		if(point.gety() != emptyY) {
			sprintf(message, "gety() did not return %10.2lf", emptyY);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("gety()", ++testNumber, totalPassed, totalTested);

		// check for no values
		if(point.loadFromFile(fp) != 0) {
			failed("loadFromFile(fp) did not return 0", ++testNumber, ok, totalTested);
		} else
			passed("loadFromFile(fp)", ++testNumber, totalPassed, totalTested);
		if(point.getx() != emptyX) {
			sprintf(message, "getx() did not return %10.2lf", emptyX);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("getx()", ++testNumber, totalPassed, totalTested);
		if(point.gety() != emptyY) {
			sprintf(message, "gety() did not return %10.2lf", emptyY);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("gety()", ++testNumber, totalPassed, totalTested);

		// remove alpha character
		fscanf(fp,"%*c\n");

		// check for end of file mark
		if(point.loadFromFile(fp) != EOF) {
			failed("loadFromFile(fp) did not return EOF", ++testNumber, ok, totalTested);
		} else
			passed("loadFromFile(fp)", ++testNumber, totalPassed, totalTested);
		if(point.getx() != emptyX) {
			sprintf(message, "getx() did not return empty value %10.2lf", emptyX);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("getx()", ++testNumber, totalPassed, totalTested);
		if(point.gety() != emptyY) {
			sprintf(message, "gety() did not return empty value %10.2lf", emptyY);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("gety()", ++testNumber, totalPassed, totalTested);

		fclose(fp);
	} else {
		sprintf(message, "Load Scratch File (%s)", SCRATCH);
		failed(message, ++testNumber, ok, totalTested);
	}

	return ok;
}

/* DataSetTests performs tests on the DataSet class and
   returns true if successful, false if one or more tests
   failed
   testNumber  - number of the last test completed
   totalPassed - total number of tests passed
   totalTested - total number of tests attempted
*/
bool DataSetTests(int& testNumber, int& totalPassed, int& totalTested) {
	FILE* fp;
	bool ok;
	char message[61];

	// gather the data from TESTFILE
	fp = fopen(TESTFILE, "r");
	if (fp) {
		int nr, c;
		double* a;
		double* o;
		DataSet set;
		DataPoint point;
		double emptyX = point.getx(), emptyY = point.gety();
		ok = true;
		passed("Preload test file", ++testNumber, totalPassed, totalTested);
		nr = 0;
		while ((c = fgetc(fp)) != EOF)
			if ((char)c == '\n') nr++;
		rewind(fp);
		a = new (nothrow) double[nr];
		o = new (nothrow) double[nr];
		for (int i = 0; i < nr; i++)
			fscanf(fp, "%lf%lf", &a[i], &o[i]);
		fclose(fp);

		// check for no file
		if(set.loadFromFile("")) {
			failed("loadFromFile(\"\") did not return false", ++testNumber, ok, totalTested);
		} else
			passed("loadFromFile(\"\")", ++testNumber, totalPassed, totalTested);
		if(set.nPoints() != 0) {
			failed("nPoints() did not return 0", ++testNumber, ok, totalTested);
		} else {
			passed("nPoints()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.slope(), 0)) {
			failed("slope() did not return 0", ++testNumber, ok, totalTested);
		} else {
			passed("slope()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.intercept(), 0)) {
			failed("intercept() did not return 0", ++testNumber, ok, totalTested);
		} else {
			passed("intercept()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.correlation(), 0)) {
			failed("correlation() did not return 0", ++testNumber, ok, totalTested);
		} else {
			passed("correlation()", ++testNumber, totalPassed, totalTested);
		}

		// check for TESTFILE
		if(!set.loadFromFile(TESTFILE)) {
			sprintf(message, "loadFromFile(%s) did not return true", TESTFILE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			sprintf(message, "loadFromFile(%s)", TESTFILE);
			passed(message, ++testNumber, totalPassed, totalTested);
		}
		if(set.nPoints() != nr) {
			sprintf(message, "nPoints() did not return %d", nr);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("nPoints()", ++testNumber, totalPassed, totalTested);
		}
		if(set.point(-1).getx() != emptyX) {
			sprintf(message, "getx() did not return %10.2lf", emptyX);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("getx()", ++testNumber, totalPassed, totalTested);
		if(set.point(-1).gety() != emptyY) {
			sprintf(message, "gety() did not return %10.2lf", emptyY);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("gety()", ++testNumber, totalPassed, totalTested);
		if(set.point(nr).getx() != emptyX) {
			sprintf(message, "getx() did not return %10.2lf", emptyX);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("getx()", ++testNumber, totalPassed, totalTested);
		if(set.point(nr).gety() != emptyY) {
			sprintf(message, "gety() did not return %10.2lf", emptyY);
			failed(message, ++testNumber, ok, totalTested);
		} else
			passed("gety()", ++testNumber, totalPassed, totalTested);
		for (int i = 0; i < nr; i++) {
			if(set.point(i).getx() != a[i]) {
				sprintf(message, "getx() did not return %10.2lf", a[i]);
				failed(message, ++testNumber, ok, totalTested);
			} else
				passed("getx()", ++testNumber, totalPassed, totalTested);
			if(set.point(i).gety() != o[i]) {
				sprintf(message, "gety() did not return %10.2lf", o[i]);
				failed(message, ++testNumber, ok, totalTested);
			} else
				passed("gety()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.slope(), TESTSLOPE)) {
			sprintf(message, "slope() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("slope()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.intercept(), TESTINTERCPT)) {
			sprintf(message, "intercept() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("intercept()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.correlation(), TESTCORREL)) {
			sprintf(message, "correlation() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("correlation()", ++testNumber, totalPassed, totalTested);
		}
		if(!(set == set)) {
			failed("operator==(,) did not return true", ++testNumber, ok, totalTested);
		} else {
			passed("operator==(,)", ++testNumber, totalPassed, totalTested);
		}
		DataSet nullSet;
		nullSet.loadFromFile("");
		if((set == nullSet)) {
			failed("operator==(,) did not return false", ++testNumber, ok, totalTested);
		} else {
			passed("operator==(,)", ++testNumber, totalPassed, totalTested);
		}

		// Chauvenet Algorithm on the TESTFILE
		set.include(TESTCHAUVTOL);
		if(set.outlier() != TESTCHAUVOUT) {
			sprintf(message, "outlier() did not return %d", TESTCHAUVOUT);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("outlier()", ++testNumber, totalPassed, totalTested);
		}
		if(!set.outlier(-1)) {
			failed("outlier(-1) did not return true", ++testNumber, ok, totalTested);
		} else
			passed("outlier(-1)", ++testNumber, totalPassed, totalTested);
		if(!set.outlier(nr)) {
			sprintf(message, "outlier(%d) did not return true", nr);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			sprintf(message, "outlier(%d)", nr);
			passed(message, ++testNumber, totalPassed, totalTested);
		}
		for (int i = 0; i < nr; i++) {
			if(!set.outlier(i)) {
				if(set.point(i).getx() != a[i]) {
					sprintf(message, "point(%d).getx() did not return %10.2lf", i, a[i]);
					failed(message, ++testNumber, ok, totalTested);
				} else
					passed("getx()", ++testNumber, totalPassed, totalTested);
				if(set.point(i).gety() != o[i]) {
					sprintf(message, "point(%d).gety() did not return %10.2lf", i, o[i]);
					failed(message, ++testNumber, ok, totalTested);
				} else
					passed("gety()", ++testNumber, totalPassed, totalTested);
			} else {
				if(set.point(i).getx() != emptyX) {
					sprintf(message, "point(%d).getx() did not return %10.2lf", i, emptyX);
					failed(message, ++testNumber, ok, totalTested);
				} else
					passed("getx()", ++testNumber, totalPassed, totalTested);
				if(set.point(i).gety() != emptyY) {
					sprintf(message, "point(%d).gety() did not return %10.2lf", i, emptyY);
					failed(message, ++testNumber, ok, totalTested);
				} else
					passed("gety()", ++testNumber, totalPassed, totalTested);
			}
		}
		if(!doubleEqual(set.slope(), TESTCHAUVSLP)) {
			sprintf(message, "slope() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("slope()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.intercept(), TESTCHAUVINT)) {
			sprintf(message, "intercept() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("intercept()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.correlation(), TESTCHAUVCOR)) {
			sprintf(message, "correlation() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("correlation()", ++testNumber, totalPassed, totalTested);
		}

		// Back to Normal
		set.include();
		for (int i = 0; i < nr; i++) {
			if(set.outlier(i)) {
				sprintf(message, "outlier(%d) did not return false", i);
				failed(message, ++testNumber, ok, totalTested);
			} else {
				sprintf(message, "outlier(%d)", i);
				passed(message, ++testNumber, totalPassed, totalTested);
			}
		}
		if(!doubleEqual(set.slope(), TESTSLOPE)) {
			sprintf(message, "slope() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("slope()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.intercept(), TESTINTERCPT)) {
			sprintf(message, "intercept() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("intercept()", ++testNumber, totalPassed, totalTested);
		}
		if(!doubleEqual(set.correlation(), TESTCORREL)) {
			sprintf(message, "correlation() did not return %.2lf", TESTSLOPE);
			failed(message, ++testNumber, ok, totalTested);
		} else {
			passed("correlation()", ++testNumber, totalPassed, totalTested);
		}
		delete [] a;
		delete [] o;
	} else {
		sprintf(message, "Preload Test File (%s)", TESTFILE);
		failed(message, ++testNumber, ok, totalTested);
	}

	return ok;
}

/* passed displays testNumber (message), increments totalPassed
   and totalTests
*/
void passed(const char* message, int testNumber, int& totalPassed, int& totalTests) {
	if (DEBUG && message[0] != '\0')
		cout << "Passed test " << setw(4) << testNumber << " ("
		<< message << ")\n";
	++totalPassed;
	++totalTests;
}

/* failed displays testNumber (message), resets ok to false,
   increments totalTests
*/
void failed(const char* message, int testNumber, bool& ok, int& totalTests) {
	cout << "Failed test " << setw(4) << testNumber << " ("
		<< message << ")\n";
	ok = false;
	++totalTests;
}

/* doubleEqual returns true if a and b are approximately ==
*  false otherwise
*/
bool doubleEqual(double a, double b) {
	return fabs(a-b) < DOUBLE_TOLERANCE;
}

