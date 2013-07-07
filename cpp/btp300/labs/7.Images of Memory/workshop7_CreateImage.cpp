/* Images of Memory
 * Workshop 7
 * CreateImage.cpp
 */

#include<iostream>
#include<fstream>
using namespace std;
#include "Accounts.h";

int main(int argc, char* argv[]) {
	Account a;
	
	int   counter = 0;
	bool  quit = false;

	ofstream fileOut(argv[1], ios::in|ios::out|ios::app);
	cout << "** Storing Account Records **" << endl;
	do 
	{
		cin >> a;
		if (a)
		{
			fileOut << a << endl;
			counter++;
		} 
		else
			quit = true;
	} while (!(quit));
	
	//Destructor closes fileOut
	
	cout << "** " << counter << " Records Appended **" << endl;

	return 0;
}	