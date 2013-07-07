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
	static bool lastSelect = true;
	static bool keyEnter = false;
	
	if (!fieldNum) { 
		currentNode = initNode;
	} 	
	while (keepgoing) {
		nav = currentNode->getData()->edit();
		if (nav) {
			if (queField) keepgoing = false;
			if (nav == ENTER || nav == TAB || nav == DOWN) {
				bool enterExit = false;
				lastSelect = true;
				currentNode = currentNode->goNext();
				fieldNum + 1 == famt ? fieldNum = 0 : fieldNum++;
				if (!currentNode) {
					currentNode = initNode;
					fieldNum = 0;
					enterExit = true;
				}
				
				if (enterExit)
					keepgoing = false;
				else if (nav == ENTER) {
					nav = DOWN;
					keyEnter = true;
				}
			} else if (nav == UP) {
				lastSelect = false;
				currentNode = currentNode->goPrev();
				fieldNum - 1 < 0 ? fieldNum = famt - 1 : fieldNum--;
				if (!currentNode) { 
					currentNode = lastNode;
				}
			}
		} else {
			if (lastSelect) {
				currentNode = currentNode->goNext();
				fieldNum + 1 == famt ? fieldNum = 0 : fieldNum++;
				if (!currentNode) {
					if (keyEnter) keepgoing = false;
					currentNode = initNode;
				}
			} else {
				currentNode = currentNode->goPrev();
				fieldNum - 1 < 0 ? fieldNum = famt - 1 : fieldNum--;
				if (!currentNode) {
					currentNode = lastNode;
				}
			}		
		}
	}
	*i = fieldNum;
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