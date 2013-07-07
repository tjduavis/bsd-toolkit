/*******************************************************************************
 * Assignment 4 Version 1.0                                                    *
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

#define BOXBORDER 8

class Box : public Field {
	int rowBox;
	int colBox;
	int widthBox;
	int heightBox;
	char borderBox[BOXBORDER];
	
	public:
	Box(int rowB, int colB, int widthB, int heightB, const char* border = "+-+|+-+|")
	: Field(rowB, colB, widthBox, border, false) {
		rowBox = rowB;
		colBox = colB;
		widthBox = widthB;
		heightBox = heightB;
		if (!border || strlen(border) < BOXBORDER)
			strcpy(borderBox,"+-+|+-+|");
		else
			strcpy(borderBox,border);
	}
	Field* clone() const {
		Field* temp = new Field(rowBox,colBox,widthBox,borderBox,false);
		return temp ? temp : NULL;
	}
	void display() {
		dtioClear();
		//left top corner, first character	
		dtioCursor(rowBox,colBox++);
		dtioPutchar(borderBox[0]);
		//top bar, second character
		for (int j = 1; j < widthBox; j++) {
			dtioPutchar(borderBox[1]);
			dtioCursor(rowBox,colBox++);
		}
		//right top corner, third character
		dtioPutchar(borderBox[2]);
		dtioCursor(++rowBox,--colBox);
		//right bar, fourth character
		for (int j = 1; j < heightBox; j++) {
			dtioPutchar(borderBox[3]);
			dtioCursor(rowBox++,colBox);
		}
		//right bottom corner, fifth character
		dtioPutchar(borderBox[4]);
		dtioCursor(--rowBox,--colBox);
		
		//bottom bar, sixth character
		for (int j = 1; j < widthBox; j++) {
			dtioPutchar(borderBox[5]);
			dtioCursor(rowBox,colBox--);
		}
		//left bottom corner, seventh character
		dtioPutchar(borderBox[6]);
		dtioCursor(--rowBox,++colBox);
		//left bar, eighth character
		for (int j = 1; j < heightBox; j++) {
			dtioPutchar(borderBox[7]);
			dtioCursor(rowBox--,colBox);
		}
	}
};

class Label : public Field {
	int rowL;
	int colL;
	int lenL; 
	char* initData;
		
	public:
	Label() : rowL(0), colL(0), initData(NULL), lenL(0) { }
	Label(int rL, int cL, const char* iniD, int lL = 0)
	: Field(rL,cL,lL <= 0 ? strlen(iniD) : lL,iniD,false) {
		rowL = rL;
		colL = cL;
		if (lL <= 0) {
			lenL = strlen(iniD);
		} else {
			lenL = lL;
		}
		initData = new char[strlen(iniD)+1];
		strcpy(initData,iniD);
	}
	Field* clone() const {
		Field* temp = new Field(rowL, colL, lenL, initData, false);
		return  temp ? temp : NULL;
	}
};

class SField : public Field {
	int rowSF;
	int colSF;
	int lenSF;
	char* initData; 
	
	public:
	SField() : rowSF(0), colSF(0), lenSF(0), initData(NULL) { }
	SField(int rSF, int cSF, int lSF, const char* iniD = NULL)
	: Field(rSF,cSF,lSF,iniD,true) {
		rowSF = rSF;
		colSF = cSF;
		lenSF = lSF;
		if (iniD) {
			initData = new char[strlen(iniD)+1];
			strcpy(initData,iniD);
		}
	}
	Field* clone() const {
		Field* temp = new Field(rowSF, colSF, lenSF, initData, true);
		return  temp ? temp : NULL;
	}
};

class HField : public SField {
	int rowHF;
	int colHF;
	int lenHF;
	char* initData;
	void (*h)(void*); 
	
	public:
	HField() : rowHF(0), colHF(0), lenHF(0), initData(NULL), h(NULL) { }
	HField(int rHF, int cHF, int lHF, const char* iniD = NULL, void (*iniH)(void*) = NULL )
	: SField(rHF,cHF,lHF,iniD) {
		rowHF = rHF;
		colHF = cHF;
		lenHF = lHF;
		if (iniD) {
			initData = new char[strlen(iniD)+1];
			strcpy(initData,iniD);
		}
		h = *iniH;
	}
	Field* clone() const {
		Field* temp = new Field(rowHF, colHF, lenHF, initData, true);
		return  temp ? temp : NULL;
	}
	virtual int edit() {
		bool finish = false;
		char* tempStr = NULL;
		int result;

		tempStr = new char[strlen((char *)Field::data())+1];
		strcpy(tempStr,(char *)Field::data());
		do {
			result = Field::edit();
			if (result == F(1)) {
				if (h) {
					h(Field::data());
					Field::display();
				} else {
					finish = true;			
				}
			} else if (result == ESCAPE) {
				finish = true;
				strcpy((char *)Field::data(),tempStr);
			}
		} while(!finish);
		
		//update initData
		if (initData) delete initData;
		initData = new char[strlen((char *)Field::data())+1];
		strcpy(initData,(char *)Field::data());
		
		return result;
	}
};

class VField : public HField {
	int rowVF;
	int colVF;
	int lenVF;
	char* initData;
	bool (*v)(char*);
	void (*h)(void*);
	
	public:
	VField() : rowVF(0), colVF(0), lenVF(0), initData(NULL) {
		h = NULL;
		v = NULL;
	}
	VField(int rVF, int cVF, int lVF, const char* iniD = NULL, bool (*iniV)(char*) = NULL, void (*iniH)(void*) = NULL)
	: HField(rVF,cVF,lVF,iniD,iniH) {
		rowVF = rVF;
		colVF = cVF;
		lenVF = lVF;
		if (iniD) {
			initData = new char[strlen(iniD)+1];
			strcpy(initData,iniD);
		}
		h = *iniH;
		v = *iniV;
	}
	Field* clone() const {
		Field* temp = new Field(rowVF, colVF, lenVF, initData, true);
		return  temp ? temp : NULL;
	}
	virtual int edit() {
		bool finish = false;
		char* tempStr = NULL;
		int result;
		
		tempStr = new char[strlen((char *)Field::data())+1];
		strcpy(tempStr,(char *)Field::data());	
		do {
			result = Field::edit();
			if (!v) {
				finish = true;
			} else if (result == ESCAPE) {				
				finish = v((char *)Field::data());
				Field::display();
				strcpy((char *)Field::data(),tempStr);
			} else if (result == F(1) && h) {
				h(Field::data());
				Field::display();
			}
		} while (!finish);
		if (tempStr) delete [] tempStr;
		
		//update initData
		if (initData) delete initData;
		initData = new char[strlen((char *)Field::data())+1];
		strcpy(initData,(char *)Field::data());		
		
		return result;
	}
};

class IVField : public VField {
	int rowIVF;
	int colIVF;
	int lenIVF;
	int initIVal;
	bool (*v)(int&);
	void (*h)(void*);
	
	public:
	IVField() : rowIVF(0), colIVF(0), lenIVF(0), initIVal(0) {
		h = NULL;
		v = NULL;
	}
	IVField(int rIVF, int cIVF, int lIVF, int initVL = 0, bool (*iniV)(int&) = NULL, void (*iniH)(void*) = NULL)
	: VField(rIVF,cIVF,lIVF,"                            ",NULL,iniH) {
		rowIVF = rIVF;
		colIVF = cIVF;
		lenIVF = lIVF;
		initIVal = initVL;
		h = *iniH;
		v = *iniV;
	}		
	Field* clone() const {
		Field* temp = VField::clone();
		return  temp ? temp : NULL;
	}
	virtual int edit() {
		char* tempStr = NULL;
		char* checkStr = NULL;
		int result = 0;
		bool finish = false;
		bool nonNumTest = false;

		//copy initial data to temp
		tempStr = new char[strlen((char *)Field::data())+1];
		strcpy(tempStr,(char *)Field::data());
		do {
			result = Field::edit();
			if (result == ESCAPE) {
				finish = true;
				strcpy((char *)Field::data(),tempStr);
			}
			if (!v) {
				finish = true;
			} else if (result != ESCAPE) {
				//copy edited data to checkStr
				if (checkStr) delete [] checkStr;
				checkStr = new char[strlen((char *)Field::data())+1];
				strcpy(checkStr,(char *)Field::data());				

				//check for non-numeric characters except for '-'
				for (int j = 0; j < strlen(checkStr) + 1; j++) {
					switch(checkStr[j]) {
						case (char)0:
						case (char)1:
						case (char)2:
						case (char)3:
						case (char)4:
						case (char)5:
						case (char)6:
						case (char)7:
						case (char)8:
						case (char)9:
						case '-':
							nonNumTest = false;
							break;
						default:
							j = strlen(checkStr);
							nonNumTest = true;
					}
				}
				if (!nonNumTest) {
					sscanf((char *)Field::data(),"%d",&initIVal); //convert string into int datatype
					finish = v(initIVal);
					Field::display();
				}
			}
		} while (!finish);
		if (tempStr) delete [] tempStr;
		if (checkStr) delete [] checkStr;
		return result;
	}
	void operator=(int rhs) {
		initIVal = rhs;
		sprintf((char *)Field::data(),"%d", initIVal);	//load string
	}
	operator int() const {
		return initIVal;
	}
};

class MMIField : public IVField {
	int rowMMI;
	int colMMI;
	int lenMMI;
	int initMMIVal;
	int minVal;
	int maxVal;
	void (*h)(void*);
	
	public:
	MMIField() : rowMMI(0), colMMI(0), lenMMI(0), initMMIVal(0), minVal(0), maxVal(0) {
		h = NULL;
	}
	MMIField(int rMMI, int cMMI, int lMMI, int iniMMIVl = 0, int minVl = 0, int maxVl = 0, void (*iniH)(void*) = NULL)
	: IVField(rMMI,cMMI,lMMI,iniMMIVl,NULL,iniH) {
		rowMMI = rMMI;
		colMMI = cMMI;
		lenMMI = lMMI;
		initMMIVal = iniMMIVl;
		minVal = minVl;
		maxVal = maxVl;
		h = *iniH;
	}
	int edit() {
		char* tempStr = NULL;
		int result = 0;
		bool finish = false;

		//copy initial data to temp
		tempStr = new char[strlen((char *)Field::data())+1];
		strcpy(tempStr,(char *)Field::data());
		do {
			result = Field::edit();
			if (result == ESCAPE) {
				finish = true;
				strcpy((char *)Field::data(),tempStr);
			} else {
				//checks if data is in specified range
				sscanf((char *)Field::data(),"%d",&initMMIVal); //convert string into int datatype
				if (initMMIVal >= minVal || initMMIVal <= maxVal) {
					finish = true;
				}
			}
		} while (!finish);
		if (tempStr) delete [] tempStr;
		return result;
	}
	Field* clone() const {
		return  IVField::clone();
	}
};
		

class DVField : public VField {
	int rowDV;
	int colDV;
	int lenDV;
	int decDV;
	double initDVal;
	bool (*v)(double&);
	void (*h)(void*);
	
	public:
	DVField() : rowDV(0), colDV(0), lenDV(0), decDV(0), initDVal(0.0) {
		h = NULL;
		v = NULL;
	}
	DVField(int rDV, int cDV, int lDV, int decDV = 2, double initDL = 0.0, bool (*iniV)(double&) = NULL, void (*iniH)(void*) = NULL)
	: VField(rDV,cDV,lDV,"                            ",NULL,iniH) {
		rowDV = rDV;
		colDV = cDV;
		lenDV = lDV;
		initDVal = initDL;
		h = *iniH;
		v = *iniV;
	}		
	Field* clone() const {
		Field* temp = VField::clone();
		return  temp ? temp : NULL;
	}
	int edit() {
		char* tempStr = NULL;
		char* checkStr = NULL;		
		int result = 0;
		bool finish = false;
		bool nonNumTest = false;

		//copy initial data to temp
		tempStr = new char[strlen((char *)Field::data())+1];
		strcpy(tempStr,(char *)Field::data());
		do {
			result = Field::edit();
			if (result == ESCAPE) {
				finish = true;
				strcpy((char *)Field::data(),tempStr);
			}
			if (!v) {
				finish = true;
			} else if (result != ESCAPE) {
				//copy edited data to checkStr
				if (checkStr) delete [] checkStr;
				checkStr = new char[strlen((char *)Field::data())+1];
				strcpy(checkStr,(char *)Field::data());		
								
				//check for non-numeric characters except for '-' and '.'
				for (int j = 0; j < strlen(checkStr) + 1; j++) {
					switch(checkStr[j]) {
						case (char)0:
						case (char)1:
						case (char)2:
						case (char)3:
						case (char)4:
						case (char)5:
						case (char)6:
						case (char)7:
						case (char)8:
						case (char)9:
						case '-':
						case '.':
							nonNumTest = false;
							break;
						default:
							j = strlen(checkStr);
							nonNumTest = true;
					}
				}
				if (!nonNumTest) {
					sscanf((char *)Field::data(),"%f",&initDVal); //convert string into double datatype
					finish = v(initDVal);
					Field::display(); 	
				}
			}
		} while (!finish);
		if (tempStr) delete [] tempStr;
		if (checkStr) delete [] checkStr;
		return result;
	}
	void operator=(double rhs) {
		initDVal = rhs;
		sprintf((char *)Field::data(),"%f", initDVal);	//load string
	}
	operator double() const {
		return initDVal;
	}
};

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
			fieldNode* link = new fieldNode(tempNode->getData(),NULL,currentNode);
			appendLast(link);
			tempNode = tempNode->goNext();
		}
	}
	void appendLast(fieldNode* lk) {
		if (initNode) {
			fieldNode* oldCurr = currentNode->goNext();
			currentNode->setPrev(oldCurr);
			currentNode->setNext(lk);
		} else {
			initNode = lk;
		}
		currentNode = lastNode = lk;
	}
	int NavigateEdit(int *);
	
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
		//Field* tempData = rhs.clone();
		Field* tempData = new Field(rhs);
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
		return NavigateEdit(&empty);
	}
	int edit(bool clear) {
		if (clear) { dtioClear(); }
		return edit();
	}
	int edit(int *pfield) {
		return NavigateEdit(pfield);
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