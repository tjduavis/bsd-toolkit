/* A Linked List for Screen Displays
 * By: Leah Spontaneo
 * Screen.cpp
 * Oct 12 2005
 */

 #include "leah.h"
 #include <new>
 #include <iostream>
 using namespace std;

 Field::Field()
 {
  row = 0;
  col = 0;
  width = 0;
  st = NULL;
 }

 Field::Field(int r, int c, int w, const char* s)
 {
  int i = 0, len = strlen(s);

  row = r;
  col = c;
  
  if (col + w <= dtioColumns())
   width = w;
  else
   width = dtioColumns() - col;
  
  st = new (nothrow) char[width + 1];

  for (int j = 0; j < len && i < width; j++)
  {
   st[j] = s[j];
   i++;
  }
  st[j] = '\0';
 }

 Field::Field(const Field& source)
 {
  init(source);
 }

 void Field::init(const Field& source)
 {
  row = source.row;
  col = source.col;
  width = source.width;
  st = new (nothrow) char[strlen(source.st) + 1];
  strcpy(st, source.st);
 }

 Field::~Field()
 {
  if (st)
   delete [] st;
 }

 Field& Field::operator=(const Field& source)
 {
  if (this != &source)
  {
   if (st) 
    delete [] st;
   init(source);
  }

  return *this;
 }

 void Field::display()
 {
  dtioDisplay(st, row, col, width);
 }

 Field* Field::clone()
 {
  return new Field(row, col, width, st);
 }

 Screen::Screen()
 {
  first = NULL;
  last = NULL;
  length = 0;
 }

 void Screen::init(const Screen& source)
 {
  first = NULL;
  last = NULL;
  length = source.length;
  Node* current = source.first;
  while (current)
  {
   Node *temp = new Node(*current->data().clone(), NULL);
   
   if (first)
    last->setNext(temp);
         else
             first = temp;
         last = temp;

   current = current->next();
  }
 }

 Screen::Screen(const Screen& source)
 {
  init(source);
 }

 Screen::~Screen()
 {
 Node* current;
    while (current = first) 
 {
  first = first->next();
  delete current;
 }
 }

 Screen& Screen::operator=(const Screen& source)
 {
  if (this != &source)
  {
   if (first) 
    delete first;
   if (last)
    delete last;
   init(source);
  }

  return *this;
 }

 int Screen::add(int r, int c, int w, const char* s)
 {
  Field f = Field(r, c, w, s);

  Node* p = new Node(f, 0);
  if (first)
   last->setNext(p);
     else
   first = p;
  last = p;

  length++;
  return length;
 }

 void Screen::display(bool clear)
 {
  Node* p;
     if (clear) 
   dtioClear();
     for (p = first; p; p = p->next())
   p->data().display();
 }