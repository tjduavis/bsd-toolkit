/*==============================================================================/
 *                                                                             * 
 * Assignment 3 Version 1.0 - Field Class                                      *
 *                                                                             * 
 * FILE           : Field.cpp                                                  * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : November 11, 2005                                          *
 *                                                                             *
 * Description    : 
 *                                                                             * 
 * Specs created  : Chris S. - Seneca College                                  * 
 *                                                                             *  
/*=============================================================================*/

#include "Field.h"
Field::Field(int r, int c, int w, const char *s, bool e) {
	initField(r,c,w,s);
	index = 0;
	toEdit = e;
}

Field::Field(int r, int c, int w, const char *s) {
	initField(r,c,w,s);
	index = 0;
	toEdit = true;
}

Field::Field(int r, int c, int w) {
	initField(r,c,w,NULL);
	index = 0;
	toEdit = true;
}

Field::Field(Field& src) {
	initField(src);
}

Field::~Field() {
	if (str)
		delete [] str;
}

/*=============================================================================*/
// Assignment Operator
//                                                                             *
//  Description  : 
//                                                                             * 
//  Arguements   : void                                                        *  
//  RETURN VALUE : void                                                        *
Field& Field::operator=(Field& rhs) {
	if (this != &rhs) {
		if (str) delete [] str;
		initField(rhs);
	}
	return *this;	
}

/*=============================================================================*/
// Init Field
//                                                                             *
//  Description  : 
//                                                                             * 
//  Arguements   : void                                                        *  
//  RETURN VALUE : void                                                        *
void Field::initField(Field& src) {
	initField(src.row,src.column,src.width,src.str);
	index = src.index;
	toEdit = src.toEdit;
}

void Field::initField(int rChk,int cChk, int wChk, const char* sChk) {
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

	if (sChk) {
		if (wChk > strlen(sChk))
			width = strlen(sChk);
		else if (wChk <= strlen(sChk) && wChk > 0)
			width = wChk;
		else
			width = 1;
		str = new char[width+1];
		for (i = 0; i < width && width != 1; i++) { str[i] = sChk[i]; }
		str[i] = '\0';
	} else {
		if (wChk > dtioColumns()) width = dtioColumns() - 1;
		width = wChk;
		str = new char[width+1];
		//for (i = 0; i < width && width != 1; i++) { str[i] = ' '; }
		//str[0] = ' ';
		str[i] = '\0';
	}
}

/*=============================================================================*/
// Edit
//                                                                             *
//  Description  : 
//                                                                             * 
//  Arguements   : void                                                        *  
//  RETURN VALUE : void                                                        *
int Field::edit() {
	int exit = 0;
	dtioCursor(row,index);
	if (toEdit) {
		exit = dtioEdit(str, row, column, width, &index);
		index++;
	} else {
		dtioDisplay(str, row, column, width);
	}
	return exit;
}

/*=============================================================================*/
// Editable
//                                                                             *
//  Description  : 
//                                                                             * 
//  Arguements   : void                                                        *  
//  RETURN VALUE : void                                                        *
bool Field::editable() const {
	bool editField = false;
	if (toEdit) { editField = true; }
	return editField;
}

/*=============================================================================*/
// Data
//                                                                             *
//  Description  : 
//                                                                             * 
//  Arguements   : void                                                        *  
//  RETURN VALUE : void                                                        *
Field* Field::clone() const {
	Field* temp = new Field(row, column, width, str, toEdit);
	return  temp ? temp : NULL;
}