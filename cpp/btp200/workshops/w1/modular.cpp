 /* Modular Programs
 *  BTP200 - Workshop 1
 *  Week 1
 *  modular.cpp
 */

 #include <iostream>
 using namespace std;
 #define MAX 25

 int getPosInt(int max);

 int main() {
     int i;

     i = getPosInt(MAX);
     cout << "You entered " << i << endl;

     return 0;
 }

 // getPosInt returns a positive integer not greater than max
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
