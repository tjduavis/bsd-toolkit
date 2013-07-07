/*==============================================================================/
 *                                                                             * 
 * Assignment 3 Version 1.0 - Field Class                                      *
 *                                                                             * 
 * FILE           : Field.h                                                    * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : November 11, 2005                                          *
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
	
	void initField(Field&);
	void initField(int,int,int,const char*);		
	
	public:
	Field() : str(NULL), toEdit(true) { row = column = width = index = 0; }
	Field(Field&);
	Field(int, int, int);
	Field(int, int, int, const char *);
	Field(int, int, int, const char*, bool);
	~Field();
	
	Field& operator=(Field&);
	
	virtual void display() { /*printf("[%s]",str);*/ dtioDisplay(str,row,column,width); }
	virtual int edit();
	virtual bool editable() const;
	virtual void *data() { return str; }
	virtual Field *clone() const;
};