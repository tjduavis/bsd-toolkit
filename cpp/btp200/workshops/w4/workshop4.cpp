/*
* workshop4 - Atom
* 	workshop4.cpp
*	purpose:
*	author: Timothy Duavis
*	date: Feb 8/05
*/
#include "Atom.h"

int main(void){
	int NumEntry=0,i;
	Atom Input[NUM_ATOM];
	bool exit=false;

	//User enter values
	cout << "Atomic Information" << endl;
	cout << "==================" << endl;
	do{
		exit=Input[NumEntry].accept();
		NumEntry++;
		if(NumEntry==(NUM_ATOM-1))
			cout << "***Error*** Exceeded number of Atoms" << endl;
	}while(exit!=true);

	//Final Display of Entries
	cout << "No " << "Sym " << "Name " << "                     " << "Weight" << endl;
	for(i=0; i<NumEntry; i++){
		Input[i].display();
	}
	return 0;
}