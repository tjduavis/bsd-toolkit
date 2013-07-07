// Screen Display
// Workshop 6
// screenDisplay.cpp
// BTP300
// Oct 11 2005

#include "screen.h"

int main() {
	Screen s, t;
	
 	s.add(2, 4, 11,  "Hello World!");
 	s.add(2, 69, 30, "Off the Edge");
 	s.add(3, 5, 15,  "This is BTP300");
 	s.add(4, 6, 20,  "Good Morning, Canada!");
 	s.add(5, 7, 30,  "Time To Finish Assignment 2!"); 
 	s.add(6, 8, 5,   "");
 	s.display(true);
 	system("pause");

 	t = s;
 	t.add(7, 9, 10,   "One more!");
 	t.display(true);
  	system("pause");

 	Screen u = s;
 	u.display(true);
 	system("pause");
 	return 0;
}