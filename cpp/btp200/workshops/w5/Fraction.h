/************************************************/
/* Workshop5									*/
/* Fraction.h									*/
/*    Purpose: - fraction calculator			*/
/*    Author: Timothy Duavis					*/
/************************************************/

#include<iostream>
using namespace std;

#define LEFT 0
#define RIGHT 1
#define SUM 2

#define ADD 1
#define SUBTRACT 2

#define IGNORE_CHAR 2000

class Fraction{
	int numerator;
	int denominator;
	friend bool Fraction::operator==(Fraction&, Fraction&);
	void toSimplify();
	public:
		//Modifiers
		Fraction::Fraction();
		void Fraction::UserInput();
		Fraction Fraction::operator+(Fraction&);
		Fraction Fraction::operator-(Fraction&);

		//Queries
		void Display() const;
};


