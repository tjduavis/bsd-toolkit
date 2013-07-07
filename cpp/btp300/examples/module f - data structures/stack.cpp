 /* Singly Linked Lists - Stack
  * stack.cpp
  * BTP300
  * Oct 12 2005
  */

 #include <iostream>
 using namespace std;

 class Field {
     int data;
 public:
     Field(int d = 0) : data(d) {}
     int out() const { return data;}
 };

 class Node {
     Field _data;
     Node* _next;
 public:
     Node(int d, Node* n) : _data(d), _next(n) {}
     Node* next() const { printf(":next %d:\n",_next); return _next;}
     Field data() const { return _data;}
 };

 class Stack {
     Node* first;
     Stack (const &) {}
     Stack& operator=(const Stack&) { return *this;}
 public:
     Stack() : first(NULL) {}
     ~Stack() {
         while (Node* p = first) {
             first = first->next();
             delete p;
         }
     }
     void push(int d) { first = new Node (d, first);} 
     Field pop() {
         Field data;
         if (first) {
             Node* p = first;
             data = first->data();
             first = first->next();
             delete p;
         }
         return data;
     }
     bool empty() { return first == NULL;}
 };

 int main () {
     Stack s;

     // Push Data Onto Stack
     s.push(3);
     s.push(5);
     s.push(9);
     s.push(8);

     // Remove first Node
     s.pop();

     // Pop Data Off Stack
     while (!s.empty())
         cout << s.pop().out() << ' ';
     cout << endl;

     return 0;
 }
