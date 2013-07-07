/*
* Workshop 6: Objects with Depth
* Staff List
*   Workshop6.cpp
*   Purpose: Implementation file for objects, for Staff List
*            program.
*   Author: Timothy Duavis
*/

#include "Employee.h"

int main(void){
	Employee Process[LIMIT];
	int i=0, counter=0;
	char ok;

	//start menu counter from 1-10 entries
	for(i=0; i<LIMIT; i++){
		cin >> Process[i];
		cout << "Do you wish to continue? (y or n) : ";
		cin >> ok;
		if(ok=='n')
			i=LIMIT;
		counter++;
	}
	//sort list;
	sort(Process, counter);

	cout << "Staff List" << endl;
	cout << endl;
	for(i=0; i<counter; i++)
		cout << Process[i];

	return 0;
}

void sort(Employee sorted[], int numEntry){
	Employee holder;
	for(int j=0; j<numEntry; j++){
		for(int i=0; i<(numEntry-j); i++){
			if(sorted[j]>sorted[i]){
				cout << "higher then last entry" << endl;
				holder = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = holder;
			}
		}
	}
}
