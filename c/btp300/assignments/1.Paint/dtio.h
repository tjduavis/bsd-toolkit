/* Assignment 1 Version 1 - Paint a Screen
*
* FILE:		     dtio.c
* Author:        Timothy Duavis
* Last Modified: Sept 22/2005
*
* Description: Direct terminal I/O * library that hides platform dependencies.
*/

/***MACROS***/

/*different platforms options*/
#define VSNET2K3   1      /*MSDOS - Visual Studio .NET 2003*/
#define GCC        2      /*LINUX - GCC compiler*/ 
#define BCC32      3      /*MSDOS - Borland compiler*/
#define AIXC       4      /*UNIX: AIX   - AIX Compiler*/

/*platform choice*/
#define PLATFORM BCC32 

/*.net and bcc32 Key Codes */
#define KEY_BKSPC   8
#define KEY_TAB		9
#define KEY_ESC		27
#define KEY_UP    	72
#define KEY_DOWN  	80
#define KEY_LEFT  	75
#define KEY_RIGHT 	77
#define KEY_DEL   	83
#define KEY_HOME	71
#define KEY_END		79
#define KEY_PGDN	81
#define KEY_PGUP	73
#define KEY_INST	82
#define KEY_F1		59
#define KEY_F2		60
#define KEY_F3		61
#define KEY_F4		62
#define KEY_F5		63
#define KEY_F6		64
#define KEY_F7		65
#define KEY_F8		66
#define KEY_F9		67
#define KEY_F10		68
#define KEY_F11		133
#define KEY_F12		134

/*identifier codes for non-AsCII key*/
#define HOME		1001
#define UP			1002
#define DOWN 		1003
#define LEFT 		1004
#define RIGHT 		1005
#define END 		1006
#define PGDN 		1007
#define PGUP 		1008
#define DEL 		1009
#define INSERT 		1010
#define BACKSPACE	1011
#define TAB			1012
#define ESC			1013
#define F1		    2001
#define F2			2002
#define F3		    2003
#define F4		    2004
#define F5		    2005
#define F6		    2006
#define F7		    2007
#define F8		    2008
#define F9		    2009
#define F10		    2010
#define F11		    2011
#define F12		    2012
#define UNKNOWN		0

/***PROTOTYPES***/
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