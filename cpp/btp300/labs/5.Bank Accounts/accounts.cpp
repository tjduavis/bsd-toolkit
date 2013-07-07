// Workshop 5 - Bank Accounts
//  FILE: Account.cpp
//  DESCRIPTION: Class that tracks banking accounts. 
//               This is the implementation file.
//  AUTHOR: Timothy Duavis
//  LAST MODIFIED: October 12, 2005
//
#include "accounts.h"

int main(void) {
	int days = 0;
	double intRate = 0.0;
	bankAccount cust1, cust2;
		
	days = 30;
	intRate = 2.5;

	cust1.open(123456789);
	cust2.open(123456780);
	
	cust1.transaction(1000);
	cust2.transaction(1000);

	cust1.setRate(intRate);
	cust2.setRate(intRate);
	
	for (int i = 0; i < days; i++) 
		cust1.dailyInterest();
	cust1.compound();
	
	cust1.setRate(intRate + 0.5);
	cust2.setRate(intRate + 0.5);
	
	cust1.transaction(-500);

	for (int i = 0; i < days + 1; i++) {
		cust1.dailyInterest();
		cust2.dailyInterest();
	}
	
	cout << "Cust1.Interest earned: " << cust1.interestEarned() << endl;
	cout << "Cust2.Interest earned: " << cust2.interestEarned() << endl;
	cust1.compound();
	cust2.compound();
	cout << "Cust1.Balance: " << cust1.balance() << endl;
	cout << "Cust2.Balance: " << cust2.balance() << endl;
		
	return 0;
}