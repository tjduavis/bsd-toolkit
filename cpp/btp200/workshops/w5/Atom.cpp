/*
* workshop 4 - Atom
*	workshop4.cpp
*	purpose: validations and formatted output
*	author: Timothy Duavis
*	date: Feb 8/05
*/

#include "Atom.h"

//Constructor
//default values
Atom::Atom(){
	atomNum = 0;
	symbol[0] = '-';
	name[0] = '-';
	aWeight = 0.000;
}
//accept - function
//menu for data inputs
//validated inputs using iostream objects
bool Atom::accept(){
	bool getOut=false;
	bool success;
	int test;
	for(test=0; test<NUM_QUERIES; test++){
		switch(test){
			case ENTER_NUM:
				do{
					success=true;
					cout << "Enter atomic number : ";
					cin >> atomNum;
					if(cin.fail()){
						cin.clear();
					    cin.ignore(IGNORE_CHAR, '\n');
					    success=false;
					}
				}while(success!=true);
				if(atomNum==0){
					getOut=true;
					test=NUM_QUERIES;
				}
				break;
			case ENTER_SYMBOL:
				do{
					success=true;
					cout << "Enter symbol : ";
					cin >> setw(SYMBOL_LENGTH) >> symbol;
					if(cin.fail()){
						cin.clear();
				        cin.ignore(IGNORE_CHAR, '\n');
				        success=false;
					}
				}while(success!=true);
				break;
			case ENTER_NAME:
				do{
					success=true;
					cout << "Enter full name : ";
					cin >> setw(FULL_LENGTH) >> name;
					if(cin.fail()){
            			cin.clear();
             			cin.ignore(IGNORE_CHAR,'\n');
             			success=false;
					}
				}while(success!=true);
				break;
			case ENTER_WEIGHT:
				do{
					success=true;
					cout << "Enter weight : ";
					cin >> aWeight;
					if(cin.fail()){
						cin.clear();
				        cin.ignore(IGNORE_CHAR,'\n');
				        success=false;
					}
				}while(success!=true);
				break;
		}
	}
	cout << endl << endl;
	return getOut;
}

void Atom::display() const{
	cout << atomNum << symbol << name << aWeight << endl;
}