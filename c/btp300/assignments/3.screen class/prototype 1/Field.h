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
#include <cstdio>
#include <cstring>
#include <new>
using namespace std;
extern "C" {
	#include "dtio.h"
}

class Field {
	int row;
	int column;
	int width;
	char* str;
	bool toEdit;
	int index;
	
	void initField(Field& src) {
		initField(src.row,src.column,src.width,src.str);
		index = src.index;
		toEdit = src.toEdit;
	}
	void initField(int rChk,int cChk, int wChk, const char* sChk) {
		int i = 0;
		if (rChk > dtioRows())
			row = dtioRows() - 1;
		else if (rChk > 0) 
			row = rChk;
		else
			row = 0;
		
		if (cChk > dtioColumns())
			column = dtioColumns() - 1;
		else if (cChk > 0) 
			column = cChk;
		else
			column = 0;
	
		if (wChk > dtioColumns()) 
			width = dtioColumns() - 1;
		else
			width = wChk;
		str = new char[width+1];
		if (sChk) {
			for (i = 0; i < width && width != 1; i++) { str[i] = sChk[i]; }
			str[i] = '\0';
		} else {
			str[0] = 32;
			str[i] = '\0';
		}
	}		
	
	public:
	Field() : str(NULL), toEdit(true) { row = column = width = index = 0; }
	Field(Field& src) {
		initField(src);
	}
	Field(int r, int c, int w) {
		initField(r,c,w,NULL);
		index = 0;
		toEdit = true;
	}
	Field(int r, int c, int w, const char* s) {
		initField(r,c,w,s);
		index = 0;
		toEdit = true;
	}	
	Field(int r, int c, int w, const char* s, bool e) {
		initField(r,c,w,s);
		index = 0;
		toEdit = e;
	}	
	~Field() { if (str) delete [] str; }
	
	Field& operator=(Field& rhs) {
		if (this != &rhs) {
			if (str) delete [] str;
			initField(rhs);
		}
		return *this;	
	}
	
	virtual void display() { 
		dtioDisplay(str,row,column,width);
	}
	virtual int edit() {
		int exit = 0;
		dtioCursor(row,index);
		if (toEdit) {
			exit = dtioEdit(str, row, column, width, &index);
		} else {
			dtioDisplay(str, row, column, width);
		}
		return exit;
	}
	virtual bool editable() const {
		bool editField = false;
		if (toEdit) { editField = true; }
		return editField;
	}
	virtual void *data() { return str; }
	virtual Field *clone() const {
		Field* temp = new Field(row, column, width, str, toEdit);
		return  temp ? temp : NULL;
	}
};
