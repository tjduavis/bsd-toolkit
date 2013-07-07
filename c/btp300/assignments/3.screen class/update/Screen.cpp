/*******************************************************************************
 * Assignment 3 Version 1.0                                                    *
 * Screen Class                                                                *
 * File           : Screen.cpp                                                 * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : December 15, 2005                                          *
 * Description    : An object-oriented wrapper, for Direct Terminal Library    *
 *                  This wrapper will be the foundation for typical data       *
 *                  programs, which contains a Field and Screen.               *
 *                  *This program is powered by Chris' dtio                    *
 * Specs created  : Chris S. - Seneca College                                  * 
 *******************************************************************************/

#include "Screen.h"

// controls the navigation for edit
// pointer to 'i' specifies the field number while,
// flag queField specifies if caller has requested a que
// for a field to be edited.
//
int Screen::NavigateEdit(int* i,bool queField) {
	int fieldNum = *i;
	int nav = 0;
	bool keepgoing = true;
	static bool selectUP = false;
	static bool nonNavKeys = false;
	bool selectEnter = false;
	bool uniq_select = false;
	
	if (queField && !fieldNum) { 
		currentNode = initNode;
	} else if (!queField) {
		currentNode = initNode;
	}
	
	while (keepgoing) {
		nav = currentNode->getData()->edit();
		if (nav) {
			uniq_select = true;
			if (queField) keepgoing = false;
			if (nav == ENTER || nav == TAB || nav == DOWN) {
				selectUP = false;
				nonNavKeys = false;
				currentNode = currentNode->goNext();
				fieldNum++;
				if (!currentNode) {
					currentNode = initNode;
					fieldNum = 0;
				}			
				if (nav == ENTER)
					selectEnter = true;
				else
					selectEnter = false;
			} else if (nav == UP) {
				selectEnter = false;
				selectUP = true;
				nonNavKeys = false;
				currentNode = currentNode->goPrev();
				fieldNum--;
				if (!currentNode) {
					currentNode = lastNode;
					fieldNum = famt - 1;
				}				
			} else {
				nonNavKeys = true;
				if (nav == ESCAPE) 
					keepgoing = false;
			}
		} else if (!nonNavKeys) {
			uniq_select = false;
			if (selectUP) {
				fieldNum - 1 <= 0 ? fieldNum = famt - 1 : fieldNum--;
				currentNode = initNode;
				for (int j = 0; j < fieldNum; j++)
					currentNode = currentNode->goNext();
			} else {
				if (fieldNum + 1 == famt) {
					fieldNum = 0;
					if (selectEnter) keepgoing = false;
				} else {
					fieldNum++;
				}
				currentNode = initNode;
				for (int j = 0; j < fieldNum; j++)
					currentNode = currentNode->goNext();
			}
		} else {
			uniq_select = false;
			currentNode = initNode;
			for (int j = 0; j < fieldNum; j++)
				currentNode = currentNode->goNext();
			nonNavKeys = false;
		}
		if (selectEnter && fieldNum >= famt - 1) {
			keepgoing = false;
		} else if (!nonNavKeys) {
			keepgoing = true;
		}
	}
	if (queField) { *i = fieldNum; }
	return nav;
}

// removes field specified by param 'i',
// and moves everything to the beginning by one.
//
int Screen::remove(int i) {
	if (i >= 0) {
		int j;
		currentNode = initNode;
		for (j = 0; j < i && currentNode; j++) {
			currentNode = currentNode->goNext();
		}
		if (j == i) {
			fieldNode* tempNode = currentNode;
			fieldNode* replace = currentNode->goNext();
			if (!replace) {
				//field to delete is the last
				replace = currentNode->goPrev(); 
			} else {
				currentNode = currentNode->goPrev(); 
				if (!currentNode) { 
					currentNode = initNode;
				}
			}
			currentNode->setNext(replace);
			delete tempNode;
			for (fieldNode* setLast = initNode; setLast; setLast = setLast->goNext()) {
				lastNode = setLast;
			}
			famt-=j;
		}
	}
	return famt;
}