/* Assignment 2 Version 1 - Paint a Screen
*
* FILE:		     dtio.h
* Author:        Timothy Duavis
* Last Modified: Sept 25/2005
*
* Description: Direct terminal I/O library that hides platform dependencies.
*/

#include <string.h>
#include <stdlib.h>
#include <malloc.h>

/*** MACROS ***/

#define EMPTY 1

/* different platforms options */
#define VSNET2K3   		1      /* MSDOS - Visual Studio .NET 2003 */
#define GCC        		2      /* LINUX - GCC compiler            */ 
#define BCC32      		3      /* MSDOS - Borland compiler        */
#define AIXC       		4      /* UNIX: AIX   - AIX Compiler      */

/* platform choice */
#define PLATFORM 		VSNET2K3


/*** KEY CODE MACROS ***/
#define KEY_BKSPC   	8
#define KEY_TAB			9
#define KEY_ESCAPE		27
#define KEY_SPACE		32
#define KEY_RIGHT_ARROW 62

/* gcc Key Codes */
#define GCC_KEY_END		385
#define GCC_KEY_HOME	362

/* UNIX-LIKE Key code */
#define IX_KEY_ENTER 	10

#if PLATFORM == VSNET2K3 || PLATFORM == BCC32
#define KEY_ENTER		13
#define KEY_UP    		72
#define KEY_DOWN  		80
#define KEY_LEFT  		75
#define KEY_RIGHT 		77
#define KEY_DEL   		83
#define KEY_HOME		71
#define KEY_END			79
#define KEY_PGDN		81
#define KEY_PGUP		73
#define KEY_INST		82
#define KEY_F1			59
#define KEY_F2			60
#define KEY_F3			61
#define KEY_F4			62
#define KEY_F5			63
#define KEY_F6			64
#define KEY_F7			65
#define KEY_F8			66
#define KEY_F9			67
#define KEY_F10			68
#define KEY_F11			133
#define KEY_F12			134
#endif

/* identifier codes for non-AsCII key */
#define HOME			1001
#define UP				1002
#define DOWN 			1003
#define LEFT 			1004
#define RIGHT 			1005
#define END 			1006
#define PGDN 			1007
#define PGUP 			1008
#define DEL 			1009
#define INSERT 			1010
#define BACKSPACE		1011
#define TAB				1012
#define ESCAPE			1013
#define ENTER			1014
#define F(n)	    	2000 + n
#define UNKNOWN			0

#define DSIZE(x,y) x * y

/*** PROTOTYPES ***/
void dtioStart();
void dtioStop();

void dtioClear();
void dtioFlush();

int  dtioGetchar();

void dtioCursor(int, int);
void dtioPutchar(int);
void dtioPuts(const char *);

int dtioRows();
int dtioColumns();

void dtioDisplay(const char *, int, int, int);
int dtioEdit(char *, int , int , int , int *);
void truncate(int flag, int cpos, int c, char * ts);
void append(int k, int cpos, int c, char * ts);

int dtioMenu(const char *[], int , int , int , const char *);