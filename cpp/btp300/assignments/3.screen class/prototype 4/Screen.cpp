/*==============================================================================/
 *                                                                             * 
 * Assignment 3 Version 1.0 - Screen Class                                     *
 *                                                                             * 
 * FILE           : Screen.cpp                                                 * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : November 11, 2005                                          *
 *                                                                             *
 * Description    : 
 *                                                                             * 
 * Specs created  : Chris S. - Seneca College                                  * 
 *                                                                             *  
/*=============================================================================*/

#include "Screen.h"

// Screen
// copy constructor
Screen::Screen(Screen& src) {
	initScreen(src);
}

// Screen
// desctructor
Screen::~Screen() {
	currentNode = initNode;
	fieldNode* tempNode = initNode;
	while(tempNode) {
		delete tempNode;
		currentNode = currentNode->goNext();
		tempNode = currentNode;
	}
}

// InitScreen
void Screen::initScreen(Screen& src) {
	fieldNode *tempNode = src.initNode;
	currentNode = NULL;
	initNode = NULL;
	while (tempNode) {
		fieldNode *link = new fieldNode(*tempNode->getData()->clone(),NULL,currentNode);
		appendLast(link);
		tempNode = tempNode->goNext();
	}
}

// add
// 	   DESCRIPTION : appends field into screen.
//	   PARAMETER   : row, column, width and the string.
//	   RETURN      : number of fields.
int Screen::add(int r, int c, int w) {
	Field* tempData = new Field(r,c,w);
	fieldNode* link = new fieldNode(*tempData,NULL,currentNode);
	
	appendLast(link);
	count++;
	return count;
}

// add
// 	   DESCRIPTION : appends field into screen.
//	   PARAMETER   : row, column, width and the string.
//	   RETURN      : number of fields.
int Screen::add(int r, int c, int w, const char* s) {
	Field* tempData = new Field(r,c,w,s);
	fieldNode* link = new fieldNode(*tempData,NULL,currentNode);
	
	appendLast(link);
	count++;
	return count;
}

// add
// 	   DESCRIPTION : appends field into screen.
//	   PARAMETER   : row, column, width and the string.
//	   RETURN      : number of fields.
int Screen::add(int r, int c, int w, const char* s, bool e) {
	Field* tempData = new Field(r,c,w,s,e);
	fieldNode* link = new fieldNode(*tempData,NULL,currentNode);
	
	appendLast(link);
	count++;
	return count;
}

void Screen::appendLast(fieldNode* lk) {
	if (initNode) {
		fieldNode* oldCurr = currentNode->goNext();
		currentNode->setPrev(oldCurr);
		currentNode->setNext(lk);
	} else {
		initNode = lk;
	}
	currentNode = lastNode = lk;
}

// edit
int Screen::edit() {
	int empty = 0;
	return NavigateEdit(&empty,false);
}

int Screen::edit(bool clear) {
	if (clear) { dtioClear(); }
	return edit();
}

int Screen::edit(int *pfield) {
	return NavigateEdit(pfield,true);
}

int Screen::edit(int *pfield, bool clear) {
	if (clear) { dtioClear(); }
	return edit(pfield);
}
	
int Screen::NavigateEdit(int* i,bool queField) {
	int nav = 0;
	int counter = *i;
	int lastNode_nom = 0;
	bool keepgoing = true;
	bool queExit = false;
	
	fieldNode* countNodes = initNode;
	while ( countNodes = countNodes->goNext() ) {
		lastNode_nom++;
	}
	
	if (queField) {
		currentNode = initNode;
		for (int j = 0; j < counter; j++)
			currentNode = currentNode->goNext();
	}
	
	while ( keepgoing ) {
		nav = currentNode->getData()->edit();
		
		if (nav) {
			keepgoing = false;
			if (nav == ENTER || nav == TAB || nav == DOWN) {
				currentNode = currentNode->goNext();
				counter++;
				if ( !(currentNode) ) {
					currentNode = initNode;
					counter = 0;
				}
			} else if (nav == UP) {
				currentNode = currentNode->goPrev();
				counter--;
				if ( !(currentNode) ) {
					currentNode = lastNode;
					counter = lastNode_nom;
				}
			}			
		} else {
			currentNode = currentNode->goNext();
			counter++;
			if ( !(currentNode) ) {
				currentNode = initNode;
				counter = 0;
			}
		}
	}
	if (queField) {*i = counter;}
	return nav;
}

Field* Screen::getField(int i) {
	currentNode = initNode;
	for (int j = 0; j < i && currentNode; j++)
		currentNode = currentNode->goNext();
	if (j != i)
		currentNode = initNode;
	
	return currentNode->getData();
}

int Screen::remove(int i) {
	int test = 0;
	if (i >= 0) {
		int j;
		currentNode = initNode;
		if (i) {
			for (j = 0; j < i && currentNode; j++) {
				currentNode = currentNode->goNext();
			}
			if (j == i) {
				fieldNode* tempNode = currentNode;
				fieldNode* replace = currentNode->goNext();
				if ( !(replace) ) replace = tempNode->goPrev();
				currentNode = currentNode->goPrev(); if (!(currentNode)) {currentNode = initNode;}
				currentNode->setNext(replace);
				currentNode = replace;
				delete tempNode;
				for (fieldNode* check = initNode; check; check = check->goNext()) {
					lastNode = check;
				}
				count-=j;
			}
		} else {
			delete currentNode;
			delete initNode;
		}
	}
	return count;
}

Screen& Screen::operator+=(Field& rhs) {
	Field* tempData = new Field(rhs);
	fieldNode* link = new fieldNode(*tempData,NULL,currentNode);
	
	appendLast(link);
	count++;
	return *this;
}