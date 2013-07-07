/************************************************/
/* Workshop5                                    */
/* Fraction.cpp                                 */
/*    Purpose: - fraction calculator            */
/*    Author: Timothy Duavis                    */
/************************************************/

#include "Fraction.h"

//Modifiers*********************************************/

/*                                                     */
/* Constructor                                         */
/*      purpose: initialize numerator and denominator  */
/*               to zero.                              */
/*                                                     */
Fraction::Fraction(){
	numerator = 0;
	denominator = 1;
}

/*                                                     */
/* UserInput()                                         */
/*      purpose: Inputs values for numerator and       */
/*               denominator in class Fraction         */
/*                                                     */
void Fraction::UserInput(){
	bool ok;
	do{
		ok=true;
		cout << " Enter numerator : ";
		cin >> numerator;
		if(cin.fail()){
			cerr << " Error Input!!! try again." << endl;
			cin.clear();
			cin.ignore(IGNORE_CHAR, '\n');
			ok = false;
		}else if(char(cin.get()) != '\n'){
			cerr << "Trailing characters.  Try Again." << endl;
		    cin.ignore(2000, '\n');
		    ok = false;
		}
	}while(!ok);
	do{
		ok=true;
		cout << " Enter denominator : ";
		cin >> denominator;
		if(cin.fail()){
			cout << " Error Input!!! try again." << endl;
			cin.clear();
			cin.ignore(IGNORE_CHAR, '\n');
			ok = false;
		}
	}while(!ok);
}

/* toSimplify()										   */
/*		purpose: simplify numerator and denominator	   */
void Fraction::toSimplify(){
	int i, x = 0;
	int holder, holder1;
	for ( i=2; i <= numerator; i++ ){
		do{
			/* holder and holder1: values of remainders */
	    	holder = numerator % i;
	    	holder1 = denominator % i;

			/* divide by i if there is no remainder */
	    	if( holder + holder1 == 0 ){
				numerator /= i;
				denominator /= i;
			}else
				x = 1;
	   }while(x!=1);
	}
}

/*                                                     */
/* operator==(Fraction& Lhs, Fraction& Rhs)            */
/*      purpose: compares two instances of class       */
/*               Fraction for equavalency              */
/*                                                     */
bool operator==(Fraction& Lhs, Fraction& Rhs){
	if(Lhs.numerator==Rhs.numerator && Lhs.denominator==Rhs.denominator)
		return true;
	else
		return false;
}

//Queries***********************************************/

/*                                                     */
/* Display()                                           */
/*      purpose: outputs numerator and denominator in  */
/*               simplified format.                    */
/*                                                     */
void Fraction::Display() const{
	cout << numerator << "/" << denominator;
}

/*******************Global Functions********************
//Modifiers*********************************************/

/*                                                     */
/* operator+(Fraction& Rhs)                            */
/*      purpose: adds numerator and denominator        */
/*                                                     */
Fraction Fraction::operator+(Fraction& Rhs){
	Fraction operation;
	int numtrL, numtrR, denomtr;

	if(*this==Rhs){
		numtrL = numerator;
		numtrR = Rhs.numerator;
		denomtr = denominator;
	}else{
		numtrL = numerator*(Rhs.denominator);
		numtrR = Rhs.numerator*(denominator);
		denomtr = denominator*Rhs.denominator;
	}
	operation.numerator = numtrL + numtrR;
	operation.denominator = denomtr;
	operation.toSimplify();
	return operation;
}


Fraction Fraction::operator-(Fraction& Rhs){
	Fraction operation;
	int numtrL, numtrR, denomtr;

	if(*this==Rhs){
		numtrL = numerator;
		numtrR = Rhs.numerator;
		denomtr = denominator;
	}else{
		numtrL = numerator*(Rhs.denominator);
		numtrR = Rhs.numerator*(denominator);
		denomtr = denominator*Rhs.denominator;
	}
	operation.numerator = numtrL - numtrR;
	operation.denominator = denomtr;
	operation.toSimplify();
	return operation;
}