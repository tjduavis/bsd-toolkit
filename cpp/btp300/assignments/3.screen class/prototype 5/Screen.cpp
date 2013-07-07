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
Screen::Screen(const Screen& src) {
	initScreen(src);
}

// Screen
// desctructor
Screen::~Screen() {
	while(currentNode = initNode) {
		initNode = currentNode->goNext();
		delete currentNode;
	}
}

// InitScreen
void Screen::initScreen(const Screen& src) {
	fieldNode* tempNode = src.initNode;
	currentNode = NULL;
	initNode = NULL;
	while (tempNode) {
		fieldNode* link = new fieldNode(*tempNode->getData(),NULL,currentNode);
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
	famt++;
	return famt;
}

// add
// 	   DESCRIPTION : appends field into screen.
//	   PARAMETER   : row, column, width and the string.
//	   RETURN      : number of fields.
int Screen::add(int r, int c, int w, const char* s) {
	Field* tempData = new Field(r,c,w,s);
	fieldNode* link = new fieldNode(*tempData,NULL,currentNode);
	
	appendLast(link);
	famt++;
	return famt;
}

// add
// 	   DESCRIPTION : appends field into screen.
//	   PARAMETER   : row, column, width and the string.
//	   RETURN      : number of fields.
int Screen::add(int r, int c, int w, const char* s, bool e) {
	Field* tempData = new Field(r,c,w,s,e);
	fieldNode* link = new fieldNode(*tempData,NULL,currentNode);
	
	appendLast(link);
	famt++;
	return famt;
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
	int fieldNum = *i;
	bool keepgoing = true;
	static bool selectUP = true;
	static bool nonNavKeys = false;
	
	if (queField && !fieldNum) { 
		currentNode = initNode;
	} 	
	while (keepgoing) {
		nav = currentNode->getData()->edit();
		if (nav) {
			keepgoing = false;
			if (nav == ENTER || nav == TAB || nav == DOWN) {
				selectUP = false;
				nonNavKeys = false;
				currentNode = currentNode->goNext();
				fieldNum++;
				if (!currentNode) {
					currentNode = initNode;
					fieldNum = 0;
				}			
				if (nav == ENTER && fieldNum < famt - 1)
					nav = DOWN;
			} else if (nav == UP) {
				selectUP = true;
				nonNavKeys = false;
				currentNode = currentNode->goPrev();
				if (!currentNode) { currentNode = lastNode;	}	
				fieldNum - 1 < 0 ? famt - 1 : fieldNum--;				
			} else {
				nonNavKeys = true;
			}
		} else if (!nonNavKeys) {
			if (selectUP) {
				fieldNum - 1 == 0 ? fieldNum = famt - 1 : fieldNum--;
				currentNode = initNode;
				for (int j = 0; j < fieldNum; j++)
					currentNode = currentNode->goNext();
			} else {
				fieldNum + 1 == famt ? fieldNum = 0 : fieldNum++;
				currentNode = initNode;
				for (int j = 0; j < fieldNum; j++)
					currentNode = currentNode->goNext();
			}
		} else {
			currentNode = initNode;
			for (int j = 0; j < fieldNum; j++)
				currentNode = currentNode->goNext();
			nonNavKeys = false;
		}
	}
	if (queField) { *i = fieldNum; }
	return nav;
}

Field* Screen::getField(int i) {
	int j;
	currentNode = initNode;
	for (j = 0; j < i && currentNode; j++)
		currentNode = currentNode->goNext();
	if (j != i)
		currentNode = initNode;
	
	return currentNode->getData();
}

int Screen::remove(int i) {
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
				famt-=j;
			}
		} else {
			delete currentNode;
			delete initNode;
		}
	}
	return famt;
}

Screen& Screen::operator+=(const Field& rhs) {
	Field* tempData = new Field(rhs);
	fieldNode* link = new fieldNode(*tempData,NULL,currentNode);
	
	appendLast(link);
	famt++;
	
	return *this;
}