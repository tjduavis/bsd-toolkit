 /* Singly Linked Lists - Data Fields
  * fields.cpp
  * BTP300
  * Oct 12 2005
  */

 #include <iostream>
 using namespace std;

 class Field {
     int data;
     Field* _next;
 public:
     Field(int d, Field* n) : data(d), _next(n) {} 
     int out() const { return data;}
     Field* next() const { return _next;}
 };

 int main () {
     Field* first = NULL;

     // Add fields to the head of the list
     first = new Field(3, first);
     first = new Field(5, first);
     first = new Field(9, first);
     first = new Field(8, first);

     // Display Fields in Order
     for (Field* p = first; p; p = p->next())
         cout << p->out() << ' ';
     cout << endl;

     // Deallocate Memory Space for each field
     while (Field* p = first) {
         first = first->next();
         delete p;
     }
     return 0;
 }
