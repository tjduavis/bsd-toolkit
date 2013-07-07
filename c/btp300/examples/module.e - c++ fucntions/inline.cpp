 /* Inline Functions
  * inline.cpp
  * BTP300
  * Oct 5 2005
  */

 #include <iostream>
 using namespace std;
 #include "inline.h"

 int main (void) {
     Student s(975975975, "Harry");

     cout << s.number() << " - " << s.name() << endl;

     return 0;
 }
