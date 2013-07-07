/*
* Workshop 6: Objects with Depth
* Staff List
*   Employee.cpp
*   Purpose: Stores variables and memberfunction for each staff in
*                staff list program.
*   Author: Timothy Duavis
*/

#include "Employee.h"

Employee::Employee(){
	Emp_num = 0;
	payrate = 0.0;
	sur_name = '\0';
	given_name = '\0';
}

Employee::Employee(const Employee& cpySource){
	copyClone(cpySource);
}

Employee::~Employee(){
	delete [] sur_name;
	delete [] given_name;
}

void Employee::copyClone(const Employee& cpySource){
	sur_name = new char [strlen(cpySource.sur_name)+1];
	given_name = new char [strlen(cpySource.given_name)+1];

	strcpy(sur_name,cpySource.sur_name);
	strcpy(given_name,cpySource.sur_name);
	Emp_num = cpySource.Emp_num;
	payrate = cpySource.payrate;
}

bool Employee::operator>(const Employee& rhs){
	bool ok;
	if(sur_name[0]>rhs.sur_name[0])
		ok=true;
	else
		ok=false;
	return ok;
}

Employee Employee::operator=(Employee& source){
	if(this != &source){
		if (sur_name) delete [] sur_name;
		if (given_name) delete [] given_name;
		copyClone(source);
	}
	return *this;
}

istream& operator>>(istream& UserInput, Employee& Firstcpy){
	bool success;
	int optor_num;
	double optor_rate;
	char* optor_sname;
	char* optor_gname;

	optor_sname = new char;
	optor_gname = new char;

	do{
		cout << "Enter surname : ";
		UserInput >> optor_sname;
		int length = strlen(optor_sname);
		success=true;
		for(int i=0; i<length; i++){
			bool NumDigits=isdigit(optor_sname[i]);
			if(NumDigits){
				cerr << "Invalid Entry. Numeric Value" << endl;
				success=false;
			}
		}
		if(char(UserInput.get()) != '\n'){
			cerr << "Trailing characters.  Try Again." << endl;
			UserInput.ignore(IGNORE_CHAR, '\n');
			success=false;
		}
	}while(success!=true);

	do{
		cout << "Enter given name : ";
		UserInput >> optor_gname;
		success=true;
		int length = strlen(optor_gname);
		for(int i=0; i<length; i++){
			bool NumDigits=isdigit(optor_gname[i]);
			if(NumDigits){
				cerr << "Invalid Entry. Numeric Value" << endl;
				success=false;
			}
		}
		if(char(UserInput.get()) != '\n'){
			cerr << "Trailing characters.  Try Again." << endl;
			UserInput.ignore(IGNORE_CHAR, '\n');
			success=false;
		}
	}while(success!=true);
	do{
		cout << "Enter number : ";
		UserInput >> optor_num;
		success=true;
		if(UserInput.fail()){
			cerr << "Invalid Entry." << endl;
			UserInput.clear();
			UserInput.ignore(IGNORE_CHAR, '\n');
			success=false;
		}else if(optor_num < 0){
			cerr << "Invalid Entry: negative value!" << endl;
			UserInput.clear();
			UserInput.ignore(IGNORE_CHAR, '\n');
			success=false;
		}else if(char(cin.get()) != '\n'){
			cerr <<"Trailing characters. Try Again." << endl;
			UserInput.ignore(IGNORE_CHAR, '\n');
			success=false;
		}
	}while(success!=true);

	do{
		cout << "Enter pay rate : ";
		UserInput >> optor_rate;
		success=true;
		if(UserInput.fail()){
			cerr << "Invalid Entry." << endl;
			UserInput.clear();
			UserInput.ignore(IGNORE_CHAR, '\n');
			success=false;
		}else if(optor_rate < 0){
			cerr << "Invalid Entry: negative value!" << endl;
			UserInput.clear();
			UserInput.ignore(IGNORE_CHAR, '\n');
			success=false;
		}else if(char(cin.get()) != '\n'){
			cerr <<"Trailing characters. Try Again." << endl;
			UserInput.ignore(IGNORE_CHAR, '\n');
			success=false;
		}
	}while(success!=true);

	Firstcpy.sur_name = new char [strlen(optor_sname)];
	Firstcpy.given_name = new char [strlen(optor_gname)];

	strcpy(Firstcpy.sur_name,optor_sname);
	strcpy(Firstcpy.given_name,optor_gname);
	Firstcpy.Emp_num = optor_num;
	Firstcpy.payrate = optor_rate;

	delete optor_sname;
	delete optor_gname;

	return UserInput;
}

ostream& operator<<(ostream& Output, const Employee& Display){
	Output << Display.Emp_num << Display.payrate << Display.sur_name << Display.given_name << endl;
	return Output;
}