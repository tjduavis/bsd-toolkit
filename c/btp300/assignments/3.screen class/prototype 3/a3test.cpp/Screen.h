/*==============================================================================/
 *                                                                             * 
 * Assignment 3 Version 1.0 - Screen Class                                     *
 *                                                                             * 
 * FILE           : Screen.h                                                   * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : November 11, 2005                                          *
 *                                                                             *
 * Description    : 
 *                                                                             * 
 * Specs created  : Chris S. - Seneca College                                  * 
 *                                                                             *  
/*=============================================================================*/

#include "Field.h"

class fieldNode {
	Field data;
    fieldNode* next;
    fieldNode* prev;
	
    public:
    fieldNode(Field d, fieldNode* n, fieldNode* p) : data(d), next(n), prev(p) { }
    fieldNode* goNext() { return next; }
    fieldNode* goPrev() { return prev; }
    Field getData() { return data; }
    void setNext(fieldNode* n) { next = n; }
    void setPrev(fieldNode* p) { prev = p; }
};

class Screen {
	int count;
	fieldNode* currentNode;
	fieldNode* initNode;
	fieldNode* lastNode;
	
	void initScreen(Screen&);
	void appendLast(fieldNode*);
	int NavigateEdit(int *,bool);
	
	public:
	Screen() : currentNode(NULL), initNode(NULL) { count = 0; };
	Screen(Screen&);
	~Screen();
	
	Screen& operator+=(Field&);
	Screen& operator=(Screen& rhs) { if (this != &rhs) { initScreen(rhs); } return *this; }

	int add(int, int, int);
	int add(int, int, int, const char*);
	int add(int, int, int, const char *, bool);
	
	void display() { 
		for (fieldNode* tempData = initNode; tempData; tempData = tempData->goNext())
    		tempData->getData().display();
	}
	void display(bool clear) {
		if (clear) { dtioClear(); }
			display();
	}
	
	int edit();
	int edit(bool);
	int edit(int*);
	int edit(int*, bool);
	
	Field *getField(int);
	int remove(int);
};