 /* Modular Programs
 *  BTP200 - Workshop 1
 *  Week 1
 *  getPosInt - Function
 *  getPosInt.cpp
 */

 // getPosInt returns a positive integer not greater than max 
 #include <iostream>
 #include "getPosInt.h"
 using namespace std;

 int getPosInt(int max) {
     int i;
     bool keepgoing;

     keepgoing = true;
     do {
	 cout << "Enter a positive integer not greater than "
	      << max << " : ";
	 cin >> i;
	 if ( i < 0 || i > max)
	     cout << "Invalid entry.  Try again." << endl;
	 else   
	     keepgoing = false;
     } while ( keepgoing );

     return i;
 }
