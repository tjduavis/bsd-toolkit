/* Virtual Direct Terminal Library - dtio
 *
 * Header File for Direct Terminal I/O Functions
 * dtio.h
 * Oct 30 2005
 * Chris Szalwinski
 */

#ifndef _DTIO_H_
#define _DTIO_H_

/* Platforms Implemented */
#define AIXC     1
#define GCC      2
#define BORLANDC 3
#define VSNETC   4

/* Select Platform Here */
#define PLATFORM VSNETC

/* Platform Specific Key Codes */
#if PLATFORM == BORLANDC || PLATFORM == VSNETC
	#define KEY_HOME   71
	#define KEY_UP     72
	#define KEY_DOWN   80
	#define KEY_LEFT   75
	#define KEY_RIGHT  77
	#define KEY_END    79
	#define KEY_NPAGE  81
	#define KEY_PPAGE  73
	#define KEY_DC     83
	#define KEY_IC     82
	#define KEY_F0     58
	#define KEY_F(n)   (KEY_F0+(((n)<=10)?(n):((n) + 64)))
	#define KEY_ENTER  13
#elif PLATFORM == AIXC
	#define HOME_KEY   KEY_HOME
	#define END_KEY    KEY_END
#elif PLATFORM == GCC
	#define HOME_KEY   362
	#define END_KEY    385
#endif

/* Virtual Key Codes */
#define TAB       '\t'
#define BACKSPACE '\b'
#define ALARM     '\a'
#define ESCAPE    27
#define ENTER     '\n'
#define HOME      1000
#define UP        1001
#define DOWN      1002
#define LEFT      1003
#define RIGHT     1004
#define END       1005
#define PGDN      1006
#define PGUP      1007
#define DEL       1008
#define INSERT    1009
#define F(n)      (1009+(n))
#define UNKNOWN   9999

void dtioStart(void);                   /* start the terminal routines */
void dtioClear(void);                   /* clear the screen */
void dtioFlush(void);                   /* flush output */
void dtioStop(void);                    /* clean up   */
int  dtioRows(void);                    /* number of rows on screen */
int  dtioColumns(void);                 /* number of columns on screen */
int  dtioGetchar(void);                 /* get a key press */
void dtioCursor(int row, int column);   /* move cursor to row,column */
void dtioPutchar(int c);                /* display character c */
void dtioPuts(const char* s);           /* display string s */
void dtioDisplay(const char *s, int row, int column, int length);
                                        /* display string s for length */
int  dtioEdit(char *s, int row, int column, int len, int *ppos);
                                        /* edit s at row, column */
int dtioMenu(const char *s[], unsigned int choices, int row, int column,
             const char *box);          /* display menu of choices at
                                           row, column with box outline */
void *dtioBackup(int row, int column, int depth, int width);
                                        /* backup screen contents */
void dtioRestore(int row, int column, int depth, int width, void *buffer);
                                        /* restore screen contents */
#endif /*_DTIO_H_*/
