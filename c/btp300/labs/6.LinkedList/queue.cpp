 /* Singly Linked Lists - Queue
  * queue.cpp
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
     Node* next() const { return _next;}
     Field data() const { return _data;}
     void setNext(Node* p) { _next = p;}
 };

 class Queue {
     Node* first;
     Node* last;
     Queue (const &) {}
     Queue& operator=(const Queue&) { return *this;} 
 public:
     Queue() : first(NULL), last(NULL) {}
     ~Queue() {
         Node* current;
         while (current = first) {
             first = first->next();
             delete current;
         }
     }
     void push(int d) {
         Node* p = new Node(d, 0);
         if (first) {
             last->setNext(p);
     	} else {
	     	cout << "test" << endl;
             first = p;
         }
         last = p;
     }
     Field pop() {
         Field data;
         if (first) {
             Node* p = first;
             data = first->data();
             first = first->next();
             delete p;
             if (!first) last = NULL;
         }
         return data;
     }
     bool empty() { return first == NULL;}
 };

 int main () {
     Queue q;

     // Push Data Into the Queue
     q.push(3);
     q.push(5);
     //q.push(9);
     //q.push(8);

     // Remove First Node
     //q.pop();

     // Pop Data Off the Queue
     while (!q.empty())
         cout << q.pop().out() << ' ';
     cout << endl;

     return 0;
 }
