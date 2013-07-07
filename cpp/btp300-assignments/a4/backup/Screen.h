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
	Box(int rowB, int colB, int widthB, int heightB, const char* border = NULL)
	: Field(rowB, colB, widthBox, NULL, false) {
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
		Field* temp = new Box(*this);
		return temp ? temp : NULL;
	}
	void display() {
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
	public:
	Label(int rL, int cL, const char* iniD, int lL = 0)
	: Field(rL,cL,lL <= 0 ? strlen(iniD) : lL,iniD,false) { }
	Field* clone() const {
		Field* temp = new Label(*this);
		return  temp ? temp : NULL;
	}
};

class SField : public Field {
	public:
	SField(int rSF, int cSF, int lSF, const char* iniD = NULL)
	: Field(rSF,cSF,lSF,iniD,true) { }
	virtual Field* clone() const {
		Field* temp = new SField(*this);
		return  temp ? temp : NULL;
	}
};

class HField : public SField {
	void (*h)(void*); 
	
	public:
	HField(int rHF, int cHF, int lHF, const char* iniD = NULL, void (*iniH)(void*) = NULL )
	: SField(rHF,cHF,lHF,iniD) { h = *iniH; }
	virtual Field* clone() const {
		Field* temp = new HField(*this);
		return temp ? temp : NULL;
	}
	virtual int edit() {
		bool finish = false;
		char* tempStr = NULL;
		int result;

		tempStr = new char[strlen((char *)Field::data())+1];
		strcpy(tempStr,(char *)Field::data());
		do {
			result = Field::edit();
			if (h) {
				if (result == F(1)) {
					h(Field::data());
					Field::display();
				} else {
					finish = true;
					strcpy((char *)Field::data(),tempStr);
				}
			} else
				finish = true;
				
		} while(!finish);
		if (tempStr) delete [] tempStr;
				
		return result;
	}
};

class VField : public HField {
	bool (*v)(char*);
	void (*h)(void*);
	
	public:
	VField(int rVF, int cVF, int lVF, const char* iniD = NULL, bool (*iniV)(char*) = NULL, void (*iniH)(void*) = NULL)
	: HField(rVF,cVF,lVF,iniD,iniH) {
		h = *iniH;
		v = *iniV;
	}
	virtual Field* clone() const {
		Field* temp = new VField(*this);
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
				strcpy((char *)Field::data(),tempStr);
				finish = true;
			} else if (result == F(1) && h) {
				h(Field::data());
				Field::display();
			} else {
				finish = v((char *)Field::data());
				Field::display();
			}
		} while (!finish);
		if (tempStr) delete [] tempStr;
		
		return result;
	}
};

class IVField : public VField {
	int initIVal;
	bool (*v)(int&);
	void (*h)(void*);
	
	public:
	IVField(int rIVF, int cIVF, int lIVF, int initVL = 0, bool (*iniV)(int&) = NULL, void (*iniH)(void*) = NULL)
	: VField(rIVF,cIVF,lIVF,"                            ",NULL,iniH) {
		initIVal = initVL;
		h = *iniH;
		v = *iniV;
	}               
	virtual Field* clone() const {
		Field* temp = new IVField(*this);
		return  temp ? temp : NULL;
	}
	virtual int edit() {
		char* tempStr = NULL;
		char* checkStr = NULL;
		int result = 0;
		bool finish = false;
		bool nonNumTest = true;

		//copy initial data to temp
		tempStr = new char[strlen((char *)Field::data())+1];
		strcpy(tempStr,(char *)Field::data());
		do {
			result = Field::edit();
			if (result == ESCAPE) {
				finish = true;
				strcpy((char *)Field::data(),tempStr);
				Field::display();
			}
			if (!v) {
				finish = true;
			} else if (result == F(1) && h) {
				h(Field::data());
				Field::display();
			} else {
				//copy edited data to checkStr
				if (checkStr) delete [] checkStr;
				checkStr = new char[strlen((char *)Field::data())+1];
				strcpy(checkStr,(char *)Field::data());                         

				//check for non-numeric characters except for '-'
				for (int j = 0; j < strlen(checkStr); j++) {
					switch(checkStr[j]) {
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
						default:
							j = strlen(checkStr);
							nonNumTest = false;
					}
				}
				if (nonNumTest) {
					sscanf((char *)Field::data(),"%d",&initIVal); //convert string into int datatype
					finish = v(initIVal);
					Field::display();
				}
				nonNumTest = true;
			} 
		} while (!finish);
		if (tempStr) delete [] tempStr;
		if (checkStr) delete [] checkStr;
		return result;
	}
	void operator=(int rhs) {
		initIVal = rhs;
		sprintf((char *)Field::data(),"%d", initIVal);  //load string
	}
	operator int() const {
		return initIVal;
	}
	void *initVL() { return &initIVal; }
};

class MMIField : public IVField {
	int minVal;
	int maxVal;
	void (*h)(void*);
	
	public:
	MMIField(int rMMI, int cMMI, int lMMI, int iniMMIVl = 0, int minVl = 0, int maxVl = 0, void (*iniH)(void*) = NULL)
	: IVField(rMMI,cMMI,lMMI,iniMMIVl,NULL,iniH) {
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
			} else if(result == F(1) && h) {
				h(IVField::initVL());
				sprintf((char *)Field::data(),"%d",(int *)IVField::initVL()); dtioGetchar();
				//sprintf((char *)Field::data(),"%d", (int)Field::data());
				//sscanf((char *)Field::data(),"%d",(int *)IVField::initVL()); //convert string into int datatype
			} else {
				//checks if data is in specified range
				sscanf((char *)Field::data(),"%d",(int *)IVField::initVL()); //convert string into int datatype
				if ((int)IVField::initVL() >= minVal || (int)IVField::initVL() <= maxVal) {
					finish = true;
				}
			}
		} while (!finish);
		if (tempStr) delete [] tempStr;
		return result;
	}
	Field* clone() const {
		Field* temp = new MMIField(*this);
		return  temp ? temp : NULL;
	}
};
		

class DVField : public VField {
	int decDV;
	double initDVal;
	bool (*v)(double&);
	void (*h)(void*);
	
	public:
	DVField(int rDV, int cDV, int lDV, int dDV = 2, double initDL = 0.0, bool (*iniV)(double&) = NULL, void (*iniH)(void*) = NULL)
	: VField(rDV,cDV,lDV,"                            ",NULL,iniH) {
		decDV = dDV;
		initDVal = initDL;
		h = *iniH;
		v = *iniV;
	}               
	virtual Field* clone() const {
		Field* temp = new DVField(*this);
		return  temp ? temp : NULL;
	}
	virtual int edit() {
		char* tempStr = NULL;
		char* checkStr = NULL;          
		int result = 0;
		bool finish = false;
		bool nonNumTest = true;

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
			} else if (result == F(1) && h) {
				h(Field::data());
				Field::display();
			} else {
				//copy edited data to checkStr
				if (checkStr) delete [] checkStr;
				checkStr = new char[strlen((char *)Field::data())+1];
				strcpy(checkStr,(char *)Field::data());
								
				//check for non-numeric characters except for '-' and '.'
				for (int j = 0; j < strlen(checkStr); j++) {
					switch(checkStr[j]) {
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
						case '.':
						case ' ':
							break;
						default:
							j = strlen(checkStr);
							nonNumTest = false;
					}
				}
				if (nonNumTest) {
					sscanf((char *)Field::data(),"%lf",&initDVal); //convert string into double datatype
					finish = v(initDVal);
					sprintf((char *)Field::data(),"%lf", initDVal,decDV);
					Field::display();       
				}
				nonNumTest = true; //reset
			}
		} while (!finish);
		if (tempStr) delete [] tempStr;
		if (checkStr) delete [] checkStr;
		return result;
	}
	void operator=(double rhs) {
		initDVal = rhs;
		sprintf((char *)Field::data(),"%.2lf", initDVal,decDV); //load string
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
