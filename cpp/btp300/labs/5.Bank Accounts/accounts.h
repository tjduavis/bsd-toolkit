// Workshop 5 - Bank Accounts
//  FILE: Account.h
//  DESCRIPTION: Class that tracks banking accounts. 
//               This is where the class definition is stored. 
//  AUTHOR: Timothy Duavis
//  LAST MODIFIED: October 12, 2005
//

#include <math.h>
#include <iostream>
using namespace std;

#define MAX 5 		//max no. of customers


// bankAccount
// DESCRIPTION: holds customer's account
//              object assumes a safe empty state
class bankAccount {
	double amount;
	double intEarned;
	double intPayable;
	double _rate;
	long acctNo;
	
	public:
		bankAccount();
		void transaction(double);		
		void dailyInterest();
		void compound();
		void open(long);
		void setRate(double); 				
		double balance() const;				//that returns the current balance in the account.		
		double interestEarned() const;		//that returns the interest earned in the account.	
		double rate();						//returns the interest rate payable to any customer.
};

inline double bankAccount::balance() const {return amount;}
inline double bankAccount::interestEarned() const {return intEarned; }
inline double bankAccount::rate() {return _rate;}

//constructor that sets bank accounts to safe empty state.
bankAccount::bankAccount() {
	amount     = 0;
	intEarned  = 0;
	intPayable = 0;
	acctNo     = 0;
	
}

//that receives a customer number and 
//opens an account for that customer.
void bankAccount::open(long num) {
	if (num < 0)
		num = 0;
	else  
		acctNo = num; 
}

//that receives an amount - positive valued for a deposit
//and negative valued for a withdrawal - and adjusts 
//the account balance.
void bankAccount::transaction(double a) {
	if (a < 0 && !amount)
		amount = 0;
	else
		amount += a;
}

//calculates the interest earned in a single day and adds
//that interest to the interest earned since the most 
//recent compounding.
void bankAccount::dailyInterest() {
	intEarned += amount * (_rate / 100);
}


//compounds the interest earned to date with the current
//balance and reset the interest earned to date to 0. 
void bankAccount::compound() {
	amount += intEarned;
	intEarned = 0;	 
}

//receives an interest rate and sets the interest rate 
//payable to all customers to that rate.	
void bankAccount::setRate(double r) { _rate = r; };
 	