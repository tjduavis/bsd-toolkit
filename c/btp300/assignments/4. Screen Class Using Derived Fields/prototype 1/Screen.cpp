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