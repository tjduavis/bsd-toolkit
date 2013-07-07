/* Assignment 1 Version 1 - Paint a Screen
*
* FILE:		     dtio.c
* Author:        Timothy Duavis
* Last Modified: Sept 25/2005
*
* Description: Direct terminal I/O library that hides platform dependencies.
*/

#include "dtio.h"
#include <string.h>

/* Include Platform Specific Library */
#if PLATFORM == VSNET2K3							
    #define DTIO_LIBRARY <conio.h>
    
    /* VSNET2K3 requires windows.h + stdlib.h for addtional functions */
    #include <Windows.h>						
    #include <stdlib.h>
   	
    /* VSNET Specified console screen structures and handles */
	HANDLE std_out;                                                  /* standard handle for output      */
    COORD winscreen;                                                 /* standard structure              */
	CONSOLE_SCREEN_BUFFER_INFO winscreen_info;                    	 /* structure holds additional info */	
#elif PLATFORM == BCC32
    #define DTIO_LIBRARY <conio.h>
    struct text_info x;												/* standard structurs that contains */ 
    																/* console screen info              */
#else 
    #define DTIO_LIBRARY <curses.h>
#endif

#include DTIO_LIBRARY

/* Funcion - dtioStart 
*  Description: Initializes the direct terminal
*               routines (if necessary).
*  Arguements:   VOID
*  RETURN VALUE: VOID
*/
void dtioStart(void) {
	int maxRows, maxCol;
	
	maxRows = dtioRows();
	maxCol	= dtioColumns();
	
	#if PLATFORM == VSNET2K3		
		std_out = GetStdHandle(STD_OUTPUT_HANDLE);						/* MUST BE DECLARED inorder to use console */
		GetConsoleScreenBufferInfo(std_out, &winscreen_info);			/* structure declared in header            */
		
		system("cls");
		
		dtioCursor( (maxCol/8) - 5 , (maxRows/8) + 15);		
		dtioPuts("***Welcome to BTP300 A1 - Paint a Screen***");
		dtioCursor( (maxCol/8) - 3 , (maxRows/8) + 25 );
		dtioPuts("Description:");
		dtioCursor( (maxCol/8) - 1 , (maxRows/8) + 25 );
		dtioPuts("Simple program that prints ascii and");
		dtioCursor( (maxCol/8) , (maxRows/8) + 25 );
		dtioPuts("non ascii keys on the console screen.");
		dtioCursor( (maxCol/8) + 8 , (maxRows/8) + 10 ); 
		dtioPuts("To exit hit 'ESC' TWICE (IN A ROW). Hit any key to continue...");
			
	#elif PLATFORM == BCC32
		gettextinfo(&x);
		clrscr();	
			
		/*dtioCursor( (maxCol/8) - 5 , (maxRows/8) + 15);		
		dtioPuts("***Welcome to BTP300 A1 - Paint a Screen***");
		dtioCursor( (maxCol/8) - 3 , (maxRows/8) + 25 );
		dtioPuts("Description:");
		dtioCursor( (maxCol/8) - 1 , (maxRows/8) + 25 );
		dtioPuts("Simple program that prints ascii and");
		dtioCursor( (maxCol/8) , (maxRows/8) + 25 );
		dtioPuts("non ascii keys on the console screen.");
		dtioCursor( (maxCol/8) + 8 , (maxRows/8) + 10 ); 
		dtioPuts("To exit hit 'ESC' TWICE (IN A ROW). Hit any key to continue...");*/

	#else	
	/* LINUX AND UNIX PLATFORM - AIXC AND GCC Compilers */
		initscr();										                 /* Initialize direct terminal console        */
		noecho();                                                        /* turn off echo of characters when typed    */
		cbreak();                                                        /* program controls revert on each keyboard  */ 
		keypad(stdscr,1);                                                /* non ascii keys are treated as keys.       */
		
	#endif
}

/* Funcion - dtioStop
*  Description: Cleans up direct terminal I/O.
*               
*  Arguements:   VOID
*  RETURN VALUE: VOID
*/
void dtioStop(void) {
    #if PLATFORM == VSNET2K3
  		system("cls");
  	#elif PLATFORM == BCC32
  		clrscr();
 	#else 
    	refresh(); 
    	endwin();
	#endif
}

/* Funcion - dtioClear
*  Description: Clears the screen and leaves the cursor in the 
*				upper left-hand corner.
*               
*  Arguements:   VOID
*  RETURN VALUE: VOID
*/
void dtioClear(void) {
	#if PLATFORM == VSNET2K3
		system("cls");
	
	#elif PLATFORM == BCC32
		clrscr();
	
	#else
		erase();
	#endif
} 

/* Funcion - dtioFlush
*  Description: Displays the characters still in the 
*               output buffer (if any).
*  Arguements:   VOID
*  RETURN VALUE: VOID
*/
void dtioFlush(void) {
	#if PLATFORM == GCC || PLATFORM == AIXC
		refresh();
	
	#endif
}    

/* Funcion - dtioGetchar
*  Description: Returns the universal key code that
*				identifies the key pressed.
*
*  Arguements:   VOID
*  RETURN VALUE: INT
*/
int dtioGetchar(void) {
	int key_char;
	
	#if PLATFORM == GCC
		key_char = getch();
		
		/* KEYPAD keys: the following keys have a 27   */
    	/* key code, which then is followed by 79 and  */
    	/* a key code specified to the unknown key     */
    	/* code sequence.							   */ 
		if (key_char == 27 && getch() == 79 && getch() > 0) {
		 		key_char = UNKNOWN;
		} else {
			switch (key_char) {
			case KEY_UP:    	key_char = UP;      	break;
        	case KEY_DOWN:  	key_char = DOWN;    	break;
       		case KEY_LEFT:  	key_char = LEFT;    	break;
       		case KEY_RIGHT: 	key_char = RIGHT;   	break;
       		case KEY_DC:  	 	key_char = DEL;  		break;
       		
       		/* KEY_... is dtio.h defined */
       		case GCC_KEY_HOME:  key_char = HOME;  		break;
       		case GCC_KEY_END:   key_char = END;  		break;
       		case IX_KEY_ENTER:	key_char = ENTER;		break;      		
       		case KEY_NPAGE:    	key_char = PGDN;  		break;
       		case KEY_PPAGE:    	key_char = PGUP;  		break;
       		case KEY_IC:    	key_char = INSERT;  	break;
       		case KEY_BKSPC:    	key_char = BACKSPACE;  	break;
       		case KEY_TAB:    	key_char = TAB;			break;
       		case KEY_ESCAPE:   	key_char = ESCAPE;		break;  
       		case KEY_F(1):		key_char = F(1);		break;
       		case KEY_F(2):		key_char = F(2);		break;
       		case KEY_F(3):		key_char = F(3);		break;
       		case KEY_F(4):		key_char = F(4);		break;       		
        	case KEY_F(5):		key_char = F(5);		break;
        	case KEY_F(6):		key_char = F(6);		break;
        	case KEY_F(7):		key_char = F(7);		break;
        	case KEY_F(8):		key_char = F(8);		break;
        	case KEY_F(9):		key_char = F(9);		break;
        	case KEY_F(10):		key_char = F(10); 		break;
        	case KEY_F(11):		key_char = F(11); 		break;
        	case KEY_F(12):		key_char = F(12); 		break;
			}
		}
		return key_char;
	
	#elif PLATFORM == AIXC
		key_char = getch();

		/* KEYPAD keys: the following keys have a 27   */
    	/* key code, which then is followed by 79 and  */
    	/* a key code specified to the unknown key     */
    	/* code sequence.							   */	 
		if (key_char == 27 && getch() == 79 && getch() > 0) {
		 		key_char = UNKNOWN;
		} else {		
			switch (key_char) {
	    		case KEY_UP:    	key_char = UP;      	break;
        		case KEY_DOWN:  	key_char = DOWN;    	break;
       			case KEY_LEFT:  	key_char = LEFT;    	break;
       			case KEY_RIGHT: 	key_char = RIGHT;   	break;
       			case KEY_DC:  	 	key_char = DEL;  		break;
       			case KEY_HOME:  	key_char = HOME;  		break;
       			case KEY_END:   	key_char = END;  		break;
      			case KEY_NPAGE:    	key_char = PGDN;  		break;
       			case KEY_PPAGE:    	key_char = PGUP;  		break;
       			case KEY_IC:    	key_char = INSERT;  	break;
       			case KEY_BKSPC:    	key_char = BACKSPACE;  	break;
       			case KEY_TAB:    	key_char = TAB;			break;
       			case KEY_ESCAPE:   	key_char = ESCAPE;		break;
       			case IX_KEY_ENTER:	key_char = ENTER;		break;   
       			case KEY_F(1):		key_char = F(1);		break;
       			case KEY_F(2):		key_char = F(2);		break;
       			case KEY_F(3):		key_char = F(3);		break;
       			case KEY_F(4):		key_char = F(4);		break;       		
        		case KEY_F(5):		key_char = F(5);		break;
        		case KEY_F(6):		key_char = F(6);		break;
        		case KEY_F(7):		key_char = F(7);		break;
        		case KEY_F(8):		key_char = F(8);		break;
        		case KEY_F(9):		key_char = F(9);		break;
        		case KEY_F(10):		key_char = F(10); 		break;
        		case KEY_F(11):		key_char = F(11); 		break;
        		case KEY_F(12):		key_char = F(12); 		break;
			}
		}
		return key_char;
	
	#elif PLATFORM == BCC32
		key_char = getch();
      	
		/* The following keys have a 0 key code,              */
    	/* which then is followed by another set of key codes */
		if(key_char == 0) {
			key_char = getch();
			switch (key_char) {
				
	    		/* KEY_... is conio.h defined */
				case KEY_UP:    	key_char = UP;      break;
        		case KEY_DOWN:  	key_char = DOWN;    break;
        		case KEY_LEFT:  	key_char = LEFT;    break;
        		case KEY_RIGHT: 	key_char = RIGHT;   break;
        		case KEY_DEL:    	key_char = DEL;  	break;
        		case KEY_HOME:    	key_char = HOME;  	break;
        		case KEY_END:    	key_char = END;  	break;
        		case KEY_PGDN:    	key_char = PGDN;  	break;
        		case KEY_PGUP:    	key_char = PGUP;  	break;
        		case KEY_INST:    	key_char = INSERT;  break;
		   		case KEY_F1:		key_char = F(1);	break;
		   		case KEY_F2:		key_char = F(2);	break;
		   		case KEY_F3:	    key_char = F(3);	break;
		   		case KEY_F4:		key_char = F(4);	break;
		   		case KEY_F5:		key_char = F(5);	break;
		   		case KEY_F6:		key_char = F(6);	break;
		   		case KEY_F7:        key_char = F(7);	break;
		  		case KEY_F8:        key_char = F(8);	break;
		   		case KEY_F9:        key_char = F(9);	break;
		   		case KEY_F10:       key_char = F(10);	break;
		   		case KEY_F11:       key_char = F(11);	break;
		   		case KEY_F12:       key_char = F(12);	break;
        		default:            key_char = UNKNOWN;
    		}
		}
		
		/* Other ascii key codes that are specified to 	*/ 
		/* implement universal codes 					*/		
		switch(key_char) {
			case KEY_BKSPC:			key_char = BACKSPACE;	break;
			case KEY_TAB:			key_char = TAB;			break;
			case KEY_ESCAPE:		key_char = ESCAPE;		break;
			case KEY_ENTER:			key_char = ENTER;		break;
		}
		
		return key_char;			

	#else 
    	key_char = getch();
    	
    	/* The following keys have a 224 key code,            */
    	/* which then is followed by another set of key codes */
    	if (key_char == 224) {
	    	key_char = getch();
	    	switch (key_char) {
	    		case KEY_UP:    		key_char = UP;      break;
        		case KEY_DOWN:  		key_char = DOWN;    break;
        		case KEY_LEFT:  		key_char = LEFT;    break;
        		case KEY_RIGHT: 		key_char = RIGHT;   break;
        		case KEY_DEL:    		key_char = DEL;  	break;
        		case KEY_HOME:    		key_char = HOME;  	break;
        		case KEY_END:    		key_char = END;  	break;
        		case KEY_PGDN:    		key_char = PGDN;  	break;
        		case KEY_PGUP:    		key_char = PGUP;  	break;
        		case KEY_INST:    		key_char = INSERT;  break;
		    	case KEY_F11:			key_char = F(11);	break;
		    	case KEY_F12:			key_char = F(12);	break;
        		default:        		key_char = UNKNOWN;
      		}
      	
      	/* The following keys have a 0 key code,              */
    	/* which then is followed by another set of key codes */
    	} else if (key_char == 0) {
	    	key_char = getch();
	    	switch (key_char) {
		    	case KEY_F1:		key_char = F(1);		break;
		    	case KEY_F2:		key_char = F(2);		break;
		    	case KEY_F3:		key_char = F(3);		break;
		    	case KEY_F4:		key_char = F(4);		break;
		    	case KEY_F5:		key_char = F(5);		break;
		    	case KEY_F6:		key_char = F(6);		break;
		    	case KEY_F7:		key_char = F(7);		break;
		    	case KEY_F8:		key_char = F(8);		break;
		    	case KEY_F9:		key_char = F(9);		break;
		    	case KEY_F10:		key_char = F(10);		break;
		    	default:        	key_char = UNKNOWN;
	    	}
		} 
		
		/* Other ascii key codes that are specified to 	*/ 
		/* implement universal codes 					*/
		switch(key_char) {
			case KEY_BKSPC:			key_char = BACKSPACE;	break;
			case KEY_TAB:			key_char = TAB;			break;
			case KEY_ESCAPE:		key_char = ESCAPE;		break;
			case KEY_ENTER:			key_char = ENTER; 		break;

		}
		return key_char;
  	#endif
}

/* Funcion - dtioCursor
*  Description: Positions the cursor at the row and col specified. 
*				Row 0 is top row and Col 0 is lefmost.
*               This function has undefined results if either parameter is invalid.
*			    This function does not flush the output buffer.
*               
*  Arguements:   INT, INT
*  RETURN VALUE: VOID
*/
void dtioCursor( int row , int column ) {
	int mRow, mCol;					/* max columns and max rows */
	mRow = dtioRows();
	mCol = dtioColumns();
	
	#if PLATFORM == VSNET2K3
		if ( row > 0 && row <= mRow && column > 0 && column <= mCol ) {
			winscreen.X = column;
			winscreen.Y = row;				
			SetConsoleCursorPosition(std_out, winscreen);
		}		
		
	#elif PLATFORM == BCC32
		if ( row > 0 && row <= mRow && column > 0 && column <= mCol )
				gotoxy( column + 1, row + 1 );
	#else
		if ( row > 0 && row <= mRow && column > 0 && column <= mCol )
				move( row, column );
	#endif
}  

/* Funcion - dtioPutchar
*  Description: Displays the character c at the current cursor position, 
*				and advances the cursor by one position to the right.
*               If the cursor is already at the rightmost column of the screen, 
*               the advance is system dependent.
*			    This function does not flush the output buffer.
*               
*  Arguements:   INT
*  RETURN VALUE: VOID
*/
void dtioPutchar(int c) {
	#if PLATFORM == VSNET2K3 || PLATFORM == BCC32
		putch( c );	
	
	#else
		addch( c );
	
	#endif
}

/* Funcion - dtioPuts
*  Description: Displays the null-terminated string pointed to by s starting at
*               the current cursor position.
*				The function leaves the cursor just after the last character displayed.
*               If the string exceeds in length the available space on the current 
*               line of output, this function has undefined results.
*               This function does not flush the output buffer.   
*               
*  Arguements:   VOID
*  RETURN VALUE: VOID
*/
void dtioPuts( const char *s ) {
	int c_ptn;					/* cursor position     */
	int diff;					/* difference in space */
	int y;
	
	#if PLATFORM == VSNET2K3
		std_out = GetStdHandle( STD_OUTPUT_HANDLE );					/* MUST BE DECLARED inorder to use console */
		GetConsoleScreenBufferInfo( std_out, &winscreen_info );			/* structure declared in header            */
	
		c_ptn = winscreen_info.dwCursorPosition.X;
		diff = dtioColumns() - c_ptn;
		if ( strlen( s ) <= diff )
			cputs( s );

	#elif PLATFORM == BCC32
     	c_ptn = wherex();
     	diff = dtioColumns() - c_ptn;
     	
     	if ( strlen( s ) <= diff)	
			cputs( s );
	
	#else
		getyx(stdscr, y, c_ptn);				/* function that gets current position on std console screen */
		diff = dtioColumns() - c_ptn;
		
		if ( strlen( s ) <= diff )
			addstr( s );
	
	#endif
} 
    
/* Funcion - dtioRows
*  Description: Returns the number of rows on the screen.
*				Rows are the screen height.
*               
*  Arguements:   VOID
*  RETURN VALUE: INT
*/
int dtioRows( void ) {
	#if PLATFORM == VSNET2K3
		return winscreen_info.dwMaximumWindowSize.Y;
	
	#elif PLATFORM == BCC32
     	return x.screenheight;	
	
    #else
		return LINES;
	#endif
}

/* Funcion - dtioColumns
*  Description: Returns the number of cols on the screen.
*				Cols are the screen width.
*               
*  Arguements:   VOID
*  RETURN VALUE: INT
*/
int dtioColumns( void ) {
	#if PLATFORM == VSNET2K3
		return winscreen_info.dwMaximumWindowSize.X;	
	
	#elif PLATFORM == BCC32
    
	 	return x.screenwidth;	
	#else	
		return COLS;
	#endif
}   