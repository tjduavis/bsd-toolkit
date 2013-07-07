/*
* Assignment 1 - v.1.01
* DataSet.h
*	 Purpose: - to design, code and test a class for data set objects that
*			    performs a linear regression analyses on those objects.
*			  - header file, for DataSet.cpp: including prototypes,libraries
*			    and macros.
*    Author: Timothy Duavis
*    Last Modified: Feb 06/05
*/

#include <new>
#include <math.h>
#include <cstdio>
#include <string.h>

#define SQUARE 2		//exponent 2, for getting the square of numbers

//holds information for single data point
class DataPoint{
	int outliner;
	double abscissa;
	double ordinate;

	public:
		//updated.a2
		DataPoint();

		//modifiers
		int loadFromFile(FILE* fp);
		double getx() const;
		double gety() const;

		//updated.a2 - type helper
		friend bool operator==(const DataPoint&, const DataPoint&);
};

//objects holds the info for set of data points
class DataSet{
	int numDataPts;
	char labelFile[40];
	DataPoint* Pts;
	//variables for graphical functional relationships
	int j;
	double slopeValue;
	double interceptValue;
	double meanX, meanY;
	double sumSqrsX, sumSqrsY;
	double devtnX, devtnY;
	double correlationValue;
	//updated.a2
	double devRatio;

	//calc modifiers
	double calc_slope();
	double calc_intercept();
	double calc_correlation();
	//updated.a2

	public:
		//updated.a2
		DataSet();
		~DataSet();

		//modifiers
		bool loadFromFile(const char* filename);
		//updated.a2 - type modifier
		void include();
		void include(double tolerance);
		//updated.a2 - type helper
		friend bool operator==(const DataSet&, const DataSet&);

		//queries
		const char* label() const;
		double slope() const;
		double intercept() const;
		double correlation() const;
		int nPoints() const;
		DataPoint point(int i) const;
		//updated.a2 - type queries
		bool outliner(int) const;
		int outliner() const;
		void display() const;
};
