/************************************************/
/* Workshop5                                    */
/* workshop5.cpp                                */
/*    Purpose: - fraction calculator            */
/*    Author: Timothy Duavis                    */
/************************************************/

#include "Fraction.h"

int main(void){
	bool exit;
	int operation;
	char sign;
	Fraction calculator[SUM+1];

	cout << "Fraction Calculator" << endl;
	cout << "==================="<< endl;
	cout << endl;

	cout << "Left Operand :" << endl;
	calculator[LEFT].UserInput();

	cout << endl;
	cout << endl;
	do{
		cout << "Operator : ";
		cin >> sign;
		if(cin.get() != '\n'){
			cerr << "Trailing characters.  Try Again." << endl;
			cin.clear();
			cin.ignore(2000, '\n');
			exit=false;
		}
		else{
			switch(sign){
				case '+':
					operation = ADD;
					exit = true;
					break;
				case '-':
					operation = SUBTRACT;
					exit = true;
					break;
				default:
					cerr << "Invalid Operator. Try Again" << endl;
		    		exit=false;
		 	}
		}
	}while(!exit);
	cout << endl;
	cout << endl;

	cout << "Right Operand :" << endl;
	calculator[RIGHT].UserInput();

	if(operation==ADD)
		calculator[SUM] = calculator[LEFT] + calculator[RIGHT];
	else if(operation==SUBTRACT)
		calculator[SUM] = calculator[0] - calculator[1];

	cout << endl;
	cout << endl;
	calculator[LEFT].Display();
	cout << " " << sign << " ";
	calculator[RIGHT].Display();
	cout << " = ";
	calculator[SUM].Display();
	cout << endl;
	return 0;
}