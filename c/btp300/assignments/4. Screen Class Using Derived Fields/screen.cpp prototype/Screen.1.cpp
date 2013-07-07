/*==============================================================================/
 *                                                                             * 
 * Assignment 3 Version 1.0 - Screen Class                                     *
 *                                                                             * 
 * FILE           : Screen.cpp                                                 * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : December 14, 2005                                          *
 *                                                                             *
 * Description    : Object-oriented wrapper, for typical data entry programs,  *
 *                  using the dtio Library created in A2.                      *
 *                  This program is powered by Chris S' dtio object file       *
 *                                                                             * 
 * Specs created  : Chris S. - Seneca College                                  * 
 *                                                                             *  
/*=============================================================================*/

#include "Screen.h"
	
int Screen::NavigateEdit(int* fieldNum,bool queField) {
	static int counter = 0;
	
	int nav = 0;
	bool keepgoing = true;
	static bool lastSelect = true;
	static bool keyEnter = false;
	
	if (*fieldNum == 0) { 
		currentNode = initNode;
	}
	
	while (keepgoing) {
		nav = currentNode->getData()->edit();
		if (nav == ENTER || nav == TAB || nav == DOWN) {
			queField ? keepgoing = false : keepgoing = true;
			currentNode = currentNode->goNext();
			*fieldNum + 1 == famt ? *fieldNum = 0 : *fieldNum++;
			if (!currentNode) {
				currentNode = initNode;
				*fieldNum = 0;
			}
			
			//field, other than last field, is next and key 'ENTER' is hit
			if (nav == ENTER && *fieldNum != 0) {
				nav = DOWN;
			}
			
			//flag everytime key 'ENTER' is hit
			if (nav == ENTER)
				keyEnter = true;
			lastSelect = true; //flag current direction for noneditable fields
		} else if (nav == UP) {
			queField ? keepgoing = false : keepgoing = true;
			currentNode = currentNode->goPrev();
			*fieldNum - 1 < 0 ? *fieldNum = famt - 1 : *fieldNum--;
			if (!currentNode) { 
				currentNode = lastNode;
			}
			
			lastSelect = false; //flag current direction for noneditable fields
		} else if (nav) {
			queField ? keepgoing = false : keepgoing = true;
		} else {
			//printf("%d",++counter);
			if (lastSelect) {
				currentNode = currentNode->goNext();
				*fieldNum + 1 == famt ? *fieldNum = 0 : *fieldNum++;
				if (!currentNode) {
					if (keyEnter) keepgoing = false;
					currentNode = initNode;
				}
			} else {
				currentNode = currentNode->goPrev();
				*fieldNum - 1 < 0 ? *fieldNum = famt - 1 : *fieldNum--;
				if (!currentNode) {
					currentNode = lastNode;
				}
			}	
		}
	}
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

bool numericStr(char* str, bool flPt = true) {
	bool success = true;
	for (int j = 0; j < strlen(str); j++) {
		switch(str[j]) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '-':
			case ' ':
				break;
			case '.':
				if (flPt)
					success = true;
				else
					success = false;
				break;
			default:
				j = strlen(str);
				success = false;
		}
	}
	return success;
}