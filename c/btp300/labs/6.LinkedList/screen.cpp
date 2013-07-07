// Screen Display
// Workshop 6
// screen.cpp
// BTP300
// November 02, 2005 

#include "screen.h"

/*--------------------------------------------------------------------*/
/*                           FIELD DEFINITION                         */
/*--------------------------------------------------------------------*/

// Field
// constructor
Field::Field() {
	str = NULL;
	row = 0;
	col = 0;
	width = 0;
}	

// Field
// copy constructor
Field::Field(Field& src) {
	str = NULL;
	str = new char[strlen(src.str)+1];
	initField(src);
}
Field::Field(int r, int c, int w, const char *s) : row(r), col(c), width(w), str(0) {
	//width = col + width > dtioColumns() ? dtioColumns() : width;
	if (s) {
		str = new char[w];
		for (int i = 0; i < w; i++) { str[i] = s[i]; }
		str[i] = '\0';
	}
}

// Field
// desctructor
Field::~Field() {
	if (str) delete [] str;
}

// assignmnet operator
Field& Field::operator=(Field& rhs) {
	if (this != &rhs) {
		if (str) delete [] str;
		str = new char[strlen(rhs.str)+1];
		initField(rhs);
	}
	return *this;
}

// initField
void Field::initField(Field& src) {
	row = src.row;
	col = src.col;
	width = src.width;
	strcpy(str,src.str);
}
	
// display
// 	   DESC       : Displays the field with the given row, col coordinate.
//	   PARAMETER  : NONE
//	   RETURN     : NONE
void Field::display() {
	dtioDisplay(str, row, col, width);
}

// clone
// 	  DESCRIPTION : dynamically allocates a copy of the current object and returns 
//                  the address.
//	  PARAMETERS  : none
//	  RETURN      : address of field.
Field* Field::clone() {
	Field *temp;
	temp = new Field;
	temp = this;
	return temp;
}

/*--------------------------------------------------------------------*/
/*                          SCREEN DEFINITION                         */
/*--------------------------------------------------------------------*/

// Screen
// copy constructor
Screen::Screen(Screen& src) {
	initScreen(src);
}

// Screen
// desctructor
Screen::~Screen() {
	fieldNode* temp = first;
	while(temp) {
		delete temp;
		first = first->goNext();
		temp = first;
	} 
}

// InitScreen
void Screen::initScreen(Screen& src) {
	fieldNode *temp = src.first;
	first = NULL;
	last = NULL;
	while (temp) {
		fieldNode *link = new fieldNode(*temp->getData().clone(),NULL);
		if (first) {
			last->setNext(link);
		} else 
			first = link;
		last = link;
		temp = temp->goNext();
	}
}

// Assignment Operator
Screen& Screen::operator=(Screen& rhs) {
	if (this != &rhs) { initScreen(rhs); }
	return *this;
}

// add
// 	   DESCRIPTION : appends field into screen.
//	   PARAMETER   : row, column, width and the string.
//	   RETURN      : number of fields.
int Screen::add(int r, int c, int w, const char* s) {
	Field* append = new Field(r,c,w,s);
	fieldNode* link = new fieldNode(*append,NULL);
	printf("{%d}",last);
	system("pause");
	if (first) {
		last->setNext(link);
	} else {
		first = link;
	}
	last = link;
	count++;
	return count;
}

// display
//	  DESCRIPTION : clears the buffer specified in the arugement and displays the
//                  fields in queue order.
//	  PARAMETER   : bool flag to flush or not.
//	  RETURN      : void
void Screen::display(bool clear) {
	if (clear) { dtioClear(); }
    for (fieldNode* temp = first; temp; temp = temp->goNext())
    	temp->getData().display();
}