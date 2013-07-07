/*******************************************************************************
 * Assignment 3 Version 1.0                                                    *
 *                                                                             * 
 * FILE           : Field.h                                                    * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : December 05, 2005                                          *
 *                                                                             *
 * Description    : 
 *                                                                             * 
 * Specs created  : Chris S. - Seneca College                                  * 
 *******************************************************************************/

#include "Field.h"

class fieldNode {
    Field* data;
    fieldNode* next;
    fieldNode* prev;
	
    public:
    fieldNode(const fieldNode& cpy) {
	    next = cpy.next;
	    prev = cpy.prev;
	    data = cpy.data->clone();
    }
    fieldNode(Field* d, fieldNode* n, fieldNode* p) : data(d), next(n), prev(p) { }
    fieldNode* goNext() { return next; }
    fieldNode* goPrev() { return prev; }
    Field* getData() { return data; }
    void setNext(fieldNode* n) { next = n; }
    void setPrev(fieldNode* p) { prev = p; }
    fieldNode& operator=(const fieldNode& rhs) {
	    if (this != &rhs) {
		    next = rhs.next;
		    prev = rhs.prev;
		    data = rhs.data->clone();
	    }
	    return *this;
    }
};

class Screen {
	int famt;
	fieldNode* currentNode;
	fieldNode* initNode;
	fieldNode* lastNode;
	
	void initScreen(const Screen& src) {
		fieldNode* tempNode = src.initNode;
		currentNode = NULL;
		initNode = NULL;
		while (tempNode) {
			fieldNode* link = new fieldNode(tempNode->getData()->clone(),NULL,currentNode);
			appendLast(link);
			tempNode = tempNode->goNext();
		}
	}
	void appendLast(fieldNode* lk) {
		if (initNode) {
			//fieldNode* oldCurr = currentNode->goNext();
			//currentNode->setPrev(oldCurr);
			currentNode->setNext(lk);
		} else {
			initNode = lk;
		}
		currentNode = lastNode = lk;
	}
	int NavigateEdit(int *,bool);
	
	public:
	Screen() : currentNode(NULL), initNode(NULL), lastNode(NULL) { famt = 0; };
	Screen(const Screen& src) { initScreen(src); }
	~Screen() {
		while(currentNode = initNode) {
			initNode = currentNode->goNext();
			delete currentNode;
		}
	}
	
	Screen& operator+=(const Field& rhs) {
		Field* tempData = rhs.clone();
		//Field* tempData = new Field(rhs);
		fieldNode* link = new fieldNode(tempData,NULL,currentNode);
	
		appendLast(link);
		famt++;
	
		return *this;
	}
	Screen& operator=(const Screen& rhs) { if (this != &rhs) { initScreen(rhs); } return *this; }

	int add(int r, int c, int w) {
		Field* tempData = new Field(r,c,w);
		fieldNode* link = new fieldNode(tempData,NULL,currentNode);
	
		appendLast(link);
		famt++;
		return famt;
	}
	int add(int r, int c, int w, const char* s) {
		Field* tempData = new Field(r,c,w,s);
		fieldNode* link = new fieldNode(tempData,NULL,currentNode);
	
		appendLast(link);
		famt++;
		return famt;
	}
	int add(int r, int c, int w, const char* s, bool e) {
		Field* tempData = new Field(r,c,w,s,e);
		fieldNode* link = new fieldNode(tempData,NULL,currentNode);
	
		appendLast(link);
		famt++;
		return famt;
	}
	void display() {
		fieldNode* tempData = initNode;
		if (tempData = tempData->goNext()) {
			for (tempData = initNode; tempData; tempData = tempData->goNext()) {
				tempData->getData()->display();
			}
		} else {
			tempData = initNode;
			tempData->getData()->display();
		}
	}
	void display(bool clear) {
		if (clear) { dtioClear(); }
			display();
	}
	int edit() {
		static int empty = 0;
		return NavigateEdit(&empty,false);
	}
	int edit(bool clear) {
		if (clear) { dtioClear(); }
		return edit();
	}
	int edit(int *pfield) {
		return NavigateEdit(pfield,true);
	}
	int edit(int *pfield, bool clear) {
		if (clear) { dtioClear(); }
		return edit(pfield);
	}
	Field* getField(int i) {
		int j;
		currentNode = initNode;
		for (j = 0; j < i && currentNode; j++)
			currentNode = currentNode->goNext();
		if (j != i) { currentNode = initNode; }
	
		return currentNode->getData();
	}
	int remove(int);
};
