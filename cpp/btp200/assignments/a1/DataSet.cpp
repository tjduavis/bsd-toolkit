/*
* Assignment 2 - v.1.01
* DataSet.cpp
*	 Purpose: - to design, code and test a class for data set objects that
*			    performs a linear regression analyses on those objects.
*			(source: cs/~btp website - Assignment 1 outline)
*    Author: Timothy Duavis
*    Last Modified: Feb 11/05
*/

#include "DataSet.h"

//DataPoint Class Definitions
//-----------------------------------------------//
/*
* loadFromFile - function
* 	Purpose:Reads the abscissa and ordinate from the file pointed
*			to by fp and returns the number of values successfully read
*			from the file.  Your function, if it encounters an end of file
*			mark, returns EOF.
*			(source: cs/~btp website - Assignment 1 outline)
*/
int DataPoint::loadFromFile(FILE* fp){
	int check;

	if(fp!=NULL){
		check=fscanf(fp,"%lf %lf",&abscissa, &ordinate);
	}
	else
		check=EOF;
	return check;
}

/*
* getx - function
* 	Purpose:Is a query that returns the abscissa.
*		    (source: cs/~btp website - Assignment 1 outline)
*/
double DataPoint::getx() const{
	return abscissa;
}

/*
* gety - function
* 	Purpose:Is a query that returns the ordinate.
*		   (source: cs/~btp website - Assignment 1 outline)
*/
double DataPoint::gety() const{
	return ordinate;
}

//DataSet Class
//------------------------------------------------//
//Private Definitions: Modifiers
/*
* calc_slope - function
* 	Purpose:Calculates slope and returns double to private DataSet Class
*/
double DataSet::calc_slope(){
	double numerator=0, denominator=0;
	//Private variables initialized
	meanX=0;
	meanY=0;

	for (j=0; j<numDataPts; j++){
		meanX += Pts[j].getx();
		meanY += Pts[j].gety();
	}
	meanX /= (numDataPts);
	meanY /= (numDataPts);
	for (j=0; j<numDataPts; j++){
		numerator += (Pts[j].getx() - meanX)*(Pts[j].gety()-meanY);
		denominator += pow((Pts[j].getx()-meanX),SQUARE);
	}
	return (slopeValue = numerator / denominator);
}

/*
* calc_intercept - function
* 	Purpose:Calculates intercept and returns double to private DataSet Class
*/
double DataSet::calc_intercept(){
	return ( interceptValue = meanY - (slope() * meanX) );
}

/*
* calc_correlation - function
* 	Purpose:Calculates correlation and returns double to private DataSet Class
*/
double DataSet::calc_correlation(){
	double rootedX, rootedY;
	double numerator=0, denominator=0;

	//Private variables initialized
	sumSqrsX = 0;
	sumSqrsY = 0;

	for (j=0; j<numDataPts; j++){
		sumSqrsX += pow(Pts[j].getx(),SQUARE);
		sumSqrsY += pow(Pts[j].gety(),SQUARE);
	}

	rootedX = (sumSqrsX / numDataPts) - pow(meanX,SQUARE);
	rootedY = (sumSqrsY / numDataPts) - pow(meanY,SQUARE);

	devtnX = sqrt(rootedX);
	devtnY = sqrt(rootedY);

	for (j=0; j<numDataPts; j++)
		numerator += Pts[j].getx()*Pts[j].gety();

	numerator /= numDataPts;
	numerator -= (meanX*meanY);

	return ( correlationValue = numerator / (devtnX*devtnY) );
}
//updated.a2
/*
* chauvenet - function
*   Purpose: screens out statiscally invalid data (assuming data has a Gaussian
*			 error distro) by verifying each point given by the deviance ratio,
*			 compared to a tolerance given.
*/



//Public Definitions: Modifiers
/*
* loadFromFile - function
* 	Purpose:receives the name of a file in a null-terminated C-style string.
*			The file contains the data points in the set, one abscissa and
*			corresponding ordinate per record.  Function attempts to open the
*			file and returns true if successful; false otherwise.
*		   (source: cs/~btp website - Assignment 1 outline)
*/
bool DataSet::loadFromFile(const char* filename){
	bool success = false;
	int numLines = 0, quit=0, check;
	FILE* DataFile = NULL;

	//Private variables initialized
	Pts = NULL;
	numDataPts = 0;

	strcpy(labelFile,filename);

	DataFile = fopen(filename,"r");
	if (DataFile != NULL){
		//Reads Num. of Lines in file for class array
		do{
			check=fgetc(DataFile);
			if(check=='\n')
				numLines+=1;
		}while(check!=EOF);
		//Adds 1,since EOF considering end of sentence as new line
		numLines+=1;
		//reset file to read from begginning
		rewind(DataFile);

		//Creates Instance for DataPoint with numLines amount of space
		Pts = new DataPoint [numLines];
		//number of lines Read successfully
		for(int i=0; quit==0; i++){
			int goodValue = Pts[i].loadFromFile(DataFile);
			if(goodValue==EOF)
				quit=1;
			else if(goodValue==2){
				goodValue/=2;
				numDataPts+=goodValue;
			}
		}

		if(numDataPts!=0){
			//Call private functions that does the calculations
			slopeValue=calc_slope();
			interceptValue=calc_intercept();
			correlationValue=calc_correlation();
			success = true;
		}
		else if(numDataPts==0){
			//Set calculatedValue to 0, if there are no files
			slopeValue=0;
			interceptValue=0;
			correlationValue=0;
		}
		//Close file
		fclose(DataFile);
	}
	return success;
}
//Public Defintions: Queries
/*
* point - function
* 	Purpose:Is a query that returns data point i of the data set.
*		   (source: cs/~btp website - Assignment 1 outline)
*/
DataPoint DataSet::point(int i) const{
	return Pts[i];
}

/*
* label - function
* 	Purpose:Is a query that returns the label of the data set.
*		   (source: cs/~btp website - Assignment 1 outline)
*/
const char* DataSet::label() const{
	return labelFile;
}

/*
* nPoint - function
* 	Purpose:Is a query that returns the number of data points in the data set.
*		   (source: cs/~btp website - Assignment 1 outline)
*/
int DataSet::nPoints() const{
	return numDataPts;
}

/*
* slope - function
* 	Purpose:Is a query that returns the slope of the least-squares line
*			that fits the data points; 0 if there are no data points
*			in the data set.
*		   (source: cs/~btp website - Assignment 1 outline)
*/
double DataSet::slope() const{
	return slopeValue;
}

/*
* intercept - function
* 	Purpose:Is a query that returns the intercept of the least-squares line
*			that fits the data points; 0 if there are no data points
*			in the data set.
*		   (source: cs/~btp website - Assignment 1 outline)
*/
double DataSet::intercept() const{
	return interceptValue;
}

/*
* correlation - function
* 	Purpose:Is a query that returns the coefficient that describes the correlation
*			between the abscissas and the ordinates of the data set; 0 if there are
*			no data points in the data set.
*		   (source: cs/~btp website - Assignment 1 outline)
*/
double DataSet::correlation() const{
	return correlationValue;
}

/******************************************************************************/
/*
* DataPoint() - Constructor
*	purpose: Initialize private variables to provide a safe empty state
*/
DataPoint::DataPoint(){
	outliner = 1;
	abscissa = 0.0;
	ordinate = 0.0;
	devRatio = 0.0;
}

/*
* == - Operator
*	purpose: Define operator function for two pairs of DataPoint class
*/
bool operator==(const DataPoint& PtA, const DataPoint& PtB){
	int equal = 0;
	if (PtA.abscissa == PtB.abscissa && PtA.ordinate == PtB.ordinate)
		equal = 1;
	return (equal);
}

/*
* DataSet() - Constructor
*	purpose:
*/
DataSet::DataSet(){
	numDataPts = 0;
	j = 0;
	slopeValue = 0.0;
	interceptValue = 0.0;
	meanX = 0.0;
	meanY = 0.0;
	sumSqrsX = 0.0;
	sumSqrsY = 0.0;
	devtnX = 0.0;
	devtnY = 0.0;
	correlationValue = 0.0;
	labelFile[0] = '\0';
}

/*
* ~DataSet() - Deconstructor
*	purpose:
*/
void DataSet::~DataSet(){
	delete [] Pts;
}

/*
* chauvenet(int i) - function
* 	purpose: to identify the
*/
double DataSet::chauvenet(int i){
	final = (Pts[i].ordinate - meanY) / devtnY;
	if (final < 0)
		final -=;
	return final;
}

/*
* include() - function
* 	purpose: accepts all outliners points as valid data points
*   		 (source: cs/~btp website - Assignment 2 outline)
*/
void DatSet::include(){
	for(j=0; j<numDataPts; j++)
		Pts[j].outliner = 1;
}

/*
* include(double) - function
* 	purpose: accepts all outliners points as valid data points
*   		 (source: cs/~btp website - Assignment 2 outline)
*	recieves: type double, name tolerance
*/
void DataSet::include(double tolerance){
	for(j=0; j<numDataPts; j++){
		devRatio = chauvenet(j);
		if (devRatio > tolerance)
			Pts[j].outliner = 0;
	}
}

/*
* outliner(int) - function
* 	purpose:
*/
bool DataSet::outliner(int xy) const{
	bool good=false;
	if (Pts[xy].outliner==1)
		good=true;
	return good;
}

/*
* outliner() - function
*	purpose:
*/
int DataSet::outliner() const{
	for(j=0; j<numDataPts; j++){
		if(Pts[j].outliner==1)
			++numOutliner;
	}
	return numOutliner;
}

/*
* operator== - helper
* 	purpose:
*/
bool operator==(const DataSet& SetA, const DataSet& SetB){
	bool good=true;
	for(int j=0; j<numDataPts || good==false; j++){
		if(SetA.Pts[j].abscissa != SetB.Pts[j].abscissa && SetA.Pts[j].ordinate != SetB.Pts[j].ordinate)
			good = false;
	}
	return good;
}