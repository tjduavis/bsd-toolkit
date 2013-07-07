// Account Class Header File
// Account.h
// Workshop 7
// BTP300
// Nov 1 2005

#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <iostream>
#include <iomanip>
using namespace std;

class Account {
	int accountNo;
	double bal;
public:
	Account() : accountNo(0), bal(0.0) {}
	double balance() const { return bal; }
	operator bool() { return accountNo; }
	friend ostream& operator<<(ostream& os, const Account& a) {
		return os << setw(10) << a.accountNo << setw(10) <<
		             setprecision(2) << fixed << a.bal;
	}
	friend istream& operator>>(istream& is, Account& a) {
		int no;
		cout << "Account No (or 0 to quit) : ";
		cin >> no;
		if (no) {
			a.accountNo = no;
			cout << "Balance : ";
			cin >> a.bal;
		} else
			a = Account();
		return is;
	}
};
#endif /* _ACCOUNT_H */
