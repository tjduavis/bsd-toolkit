/* Multi-Platform Compilation - Workshop2
*
* FILE: 		 dtio.h
* Author: 		 Timothy Duavis
* Last Modified: Sept 17/2005
*
* Description: design a direct terminal I/O * library that hides platform dependencies.
*/

/***MACROS***/

/*different platforms options*/
#define VSNET2K3   1      /*MSDOS - Visual Studio .NET 2003*/
#define GCC        2      /*LINUX - GCC compiler*/ 

/*platform choice*/
#define PLATFORM 1

/*.net and bcc32 Key Codes */
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

/*gcc Key Codes*/
#define GCC_KEY_END		385
#define GCC_KEY_HOME	362

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
#define F(n)		n + 2000
#define UNKNOWN		0

/***PROTOTYPES***/
void dtioStart();
void dtioFlush();
void dtioStop();
int  dtioGetchar();