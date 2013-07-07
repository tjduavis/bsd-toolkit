/***************************************************************************/
/* Assignment 2 - v.1.01                                                   */
/* DataSet.h                                                               */
/*	 Purpose: - to design, code and test a class for data set objects that */
/*			    performs a linear regression analyses on those objects.    */
/*			  - header file, for DataSet.cpp: including prototypes,        */
/*              libraries and macros.                                      */
/*            - upgrade version includes
/*                                                                         */
/*    Author: Timothy Duavis                                               */
/*    Last Modified: Feb 15/05                                             */
/***************************************************************************/

//Library*******************************************************************/
#include <new>
#include <cmath>
#include <cstring>
#include<iostream>
#include <iomanip>
using namespace std;

#define SQUARE 2		//exponent 2, for getting the square of numbers
#define INCLUDED 1		//include all pts (even outliners) in calc
#define EXCLUDED 2      //exclude outliners pts in calc

//Class DataPoint***********************************************************/
class DataPoint{
	double abscissa;
	double ordinate;
	int outliner;

	public:
		//modifiers**********************************/
		DataPoint();
		int loadFromFile(FILE* fp);
		int SetOutliner(int);
		friend bool operator==(const DataPoint&, const DataPoint&);
		//queries************************************/
		double getx() const;
		double gety() const;
		int DisplayOutliner() const;
};

//Class DataSet*************************************************************/
class DataSet{
	int numDataPts;
	char labelFile[40];
	DataPoint* Pts;
	int j;
	double slopeValue;
	double interceptValue;
	double meanX, meanY;
	double sumSqrsX, sumSqrsY;
	double devtnX, devtnY;
	double correlationValue;
	double devRatio;
	int numOutliner;

	//modifiers**********************************/
	double calc_slope();
	double calc_intercept();
	double calc_correlation();
	double chauvenet(int);

	public:
		//modifiers**********************************/
		DataSet();
		~DataSet();
		bool loadFromFile(const char* filename);
		void include();
		void include(double tolerance);
		friend bool operator==(const DataSet&, const DataSet&);

		//queries************************************/
		const char* label() const;
		double slope() const;
		double intercept() const;
		double correlation() const;
		int nPoints() const;
		DataPoint point(int i) const;
		bool outlier(int) const;
		int outlier() const;
		void display() const;
};