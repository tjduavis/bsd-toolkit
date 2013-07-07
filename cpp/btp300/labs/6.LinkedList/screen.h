 // Screen Display
// Workshop 6
// screen.h
// BTP300
// November 02, 2005 

#include <iostream>
#include <new>
using namespace std;
extern "C" { 
	#include "dtio.h"
}


class Field {
	char* str;
	int row;
	int col;
	int width;
	
	public:
	Field();
	Field(Field&);
	Field(int, int, int, const char*);
	~Field();
	Field& operator=(Field&);
	void initField(Field&);
	Field* clone();				
	void display();
};	

class fieldNode {
	Field data;
    fieldNode* next;
    
    public:
    fieldNode(Field d, fieldNode* n) : data(d), next(n) { }
    fieldNode* goNext() { return next; }
    Field getData() { return data; }
    void setNext(fieldNode* p) { next = p; }
};


class Screen {
	fieldNode* first;
	fieldNode* last;
	void initScreen(Screen&);
	int count;
	
	public:
	Screen() : first(NULL), last(NULL) { count = 0; }
	Screen(Screen&);
	~Screen();
	Screen& operator=(Screen&);
				
	int add(int, int, int, const char*);
	void display(bool);
};
