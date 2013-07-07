/*
* Workshop 6: Objects with Depth
*   Employee.h
*   Purpose: library containing class and important libraries
*            for Employee.cpp and workshop6.cpp
*   Author: Timothy Duavis
*/

#include<new>
#include<string.h>
#include<iomanip>
#include<iostream>
using namespace std;

#define LIMIT 10
#define IGNORE_CHAR 2000

class Employee{
	int Emp_num;
	char* sur_name;
	char* given_name;
	double payrate;
	void copyClone(const Employee&);
	public:
		Employee();
		Employee(const Employee&);
		~Employee();
		Employee operator=(Employee&);
		bool operator>(const Employee&);
		friend istream& operator>>(istream&, Employee&);
		friend ostream& operator<<(ostream&, const Employee&);
};

void sort(Employee [], int);
