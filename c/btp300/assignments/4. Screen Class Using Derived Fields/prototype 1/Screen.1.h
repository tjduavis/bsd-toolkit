/*==============================================================================/
 *                                                                             * 
 * Assignment 4 Version 1.0 - Field Class                                      *
 *                                                                             * 
 * FILE           : Field.h                                                    * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : December 05, 2005                                          *
 *                                                                             *
 * Description    : 
 *                                                                             * 
 * Specs created  : Chris S. - Seneca College                                  * 
 *                                                                             *  
/*=============================================================================*/

#include "Field.h"

class Label : virtual public Field {
	int rowL;
	int colL;
	int lenL; 
	const char* initData;
		
	public:
	Label() : rowL(0), colL(0), initData(NULL), lenL(0) { }
	Label(int rL, int cL, const char* iniD, int lL = strlen(iniD)) { }
	: Field(rL,cL,lL,iniD,false) {
		rowSF = rL;
		colSF = cL;
		lenSF = lL;
		initData = new char[strlen(iniD)+1];
		strcpy(initData,iniD);
	}
	Field* clone() const {
		Field* temp = new Field(rowL, colL, lenL, initData, false);
		return  temp ? temp : NULL;
	}
};

class SField : virtual public Field {
	int rowSF;
	int colSF;
	int lenSF;
	const char* initData; 
	
	public:
	SField() : rowSF(0), colSF(0), lenSF(0), initData(NULL) { }
	SField(int rSF, int cSF, int lSF, const char* iniD = NULL)
	: Field(rSF,cSF,lSf,iniD,true) {
		rowSF = rSF;
		colSF = cSF;
		lenSF = lSF;
		initData = new char[strlen(iniD)+1];
		strcpy(initData,iniD);
	}
	Field* clone() const {
		Field* temp = new Field(rowSF, colSF, lenSF, initData, true);
		return  temp ? temp : NULL;
	}
};

class HField : virtual public SField {
	int rowHF;
	int colHF;
	int lenHF;
	const char* initData;
	void (*h)(void*); 
	
	public:
	HField() : rowHF(0), colHF(0), lenHF(0), initData(NULL), h(NULL) { }
	HField(int rHF, int cHF, int lHF, const char* iniD = NULL, void (*iniH)(void*) = NULL )
	: SField(rHF,cHF,lHf,iniD,inH) {
		rowHF = rHF;
		colHF = cHF;
		lenHF = lHF;
		initData = new char[strlen(iniD)+1];
		strcpy(initData,iniD);
		h = iniH;
	}
	Field* clone() const {
		Field* temp = new Field(row, column, width, str, toEdit);
		return  temp ? temp : NULL;
	}
	void edit() {
		char* tempStr = NULL;
		int result = Field::edit();
		if (result == F1 && h) {
			tempStr = new char[strlen(initData)+1];
			strcpy(tempStr,initData);
			h();
			if (strcmp(tempStr,initData)) Field::display();
			delete [] tempStr;
		} else {
			Field::edit();		
		}
		return 0;
	}	
};

class VField : virtual public HField {
	int rowVF;
	int colVF;
	int lenVF;
	const char* initData;
	bool (*v)(char*);
	void (*h)(void*);
	
	public:
	VField() : VField() : rowVF(0), colVF(0), lenVF(0), initData(NULL) {
		h = NULL;
		v = NULL;
	}
	VField(int rVF, int cVF, int lVF, const char* iniD = NULL, void (*iniH)(void*) = NULL, bool (*iniV)(char*) = NULL)
	: HField(rVF,cVF,lVF,iniD,inH) {
		rowVF = rVF;
		colVF = cVF;
		lenVF = lVF;
		initData = new char[strlen(iniD)+1];
		strcpy(initData,iniD);
		h = iniH;
		v = iniV;
	}		
	Field* clone() const {
		Field* temp = new Field(rowVF, colVF, lenVF, initData, true);
		return  temp ? temp : NULL;
	}
	void edit() {
		char* tempStr = NULL;
		int result = Field::edit();
		if (result == ESCAPE && v) {
			do {
				if (tempStr) delete [] tempStr;
				tempStr = new char[strlen(initData)+1];
				strcpy(tempStr,initData);
				bool keepgoing = v();
				if (strcmp(tempStr,initData)) Field::display();
			} while (!keepgoing);
		} else {
			Field::edit();		
		}
		if (tempStr) delete [] tempStr;
		return 0;
	}
};

class IVField : 