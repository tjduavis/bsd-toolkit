/* Assignment 1 Version 1 - Paint a Screen
*
* FILE:		     dtio.c
* Author:        Timothy Duavis
* Last Modified: Sept 23/2005
*
* Description: Direct terminal I/O * library that hides platform dependencies.
*/

#include "dtio.h"

/* Include Platform Specific Library */
#if PLATFORM == VSNET2K3							
    #define DTIO_LIBRARY <conio.h>
    
    /*VSNET2K3 requires windows.h + stdlib.h for addtional functions*/
    #include <Windows.h>						
    #include <stdlib.h>
   	
    /*VSNET Specified console screen structures and handles*/
	HANDLE std_out;                                                  /*standard handle for output*/
    COORD winscreen;                                                 /*standard structure*/
	CONSOLE_SCREEN_BUFFER_INFO winscreen_info;                       /*structure holds additional info*/	
#elif PLATFORM == BCC32
    #define DTIO_LIBRARY <conio.h>	
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
	#if PLATFORM == VSNET2K3
		int maxRows, maxCol;
		/*Sets std_out value*/
		std_out = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(std_out, &winscreen_info);
		
		system("cls");
		
		maxRows = dtioRows();
		maxCol	= dtioColumns();
		
		dtioCursor( (maxRows/8) - 3 , (maxCol/8) - 4);		
		dtioPuts("***Welcome to BTP300 A1 - Paint a Screen***");
		dtioCursor( (maxRows/8) + 3 , (maxCol/8) - 3 );
		dtioPuts("Description:");
		dtioCursor( (maxRows/8) + 3 , (maxCol/8) - 2 );
		dtioPuts("Simple program that prints ascii and");
		dtioCursor( (maxRows/8) + 3 , (maxCol/8) - 1 );
		dtioPuts("non ascii keys on the console screen.");
		dtioCursor( (maxRows/8) - 3 , (maxCol/8) + 5 ); 
		dtioPuts("To exit hit 'ESC' TWICE (IN A ROW). Hit any key to continue...");
			
	#elif PLATFORM == BCC32
		int maxRows;
		int maxCol;
		clrscr();	
		
		maxRows = dtioRows();
		maxCol	= dtioColumns();	
	
		dtioCursor( (maxCol/8) - 4 , (maxRows/8) - 3);		
		dtioPuts("***Welcome to BTP300 A1 - Paint a Screen***");
		dtioCursor( (maxCol/8) - 3 , (maxRows/8) + 3 );
		dtioPuts("Description:");
		dtioCursor( (maxCol/8) - 2 , (maxRows/8) + 3 );
		dtioPuts("Simple program that prints ascii and");
		dtioCursor( (maxCol/8) - 1 , (maxRows/8) + 3 );
		dtioPuts("non ascii keys on the console screen.");
		dtioCursor( (maxCol/8) + 5 , (maxRows/8) - 3 ); 
		dtioPuts("To exit hit 'ESC' TWICE (IN A ROW). Hit any key to continue...");

	#else
	/*LINUX AND UNIX PLATFORM - AIXC AND GCC Compilers*/
		int maxRows;
		int maxCol;	
	
		initscr();										                 /*initialize direct terminal console*/
		noecho();                                                        /*turn off echo of characters when typed*/
		cbreak();                                                        /*program controls revert on each keyboard*/ 
		keypad(stdscr,1);                                                /*non ascii keys are treated as keys*/
		
		maxRows = dtioRows();
		maxCol	= dtioColumns();
		
		dtioCursor( (maxRows/8) - 3 , (maxCol/8) - 4);		
		dtioPuts("***Welcome to BTP300 A1 - Paint a Screen***");
		dtioCursor( (maxRows/8) + 3 , (maxCol/8) - 3 );
		dtioPuts("Description:");
		dtioCursor( (maxRows/8) + 3 , (maxCol/8) - 2 );
		dtioPuts("Simple program that prints ascii and");
		dtioCursor( (maxRows/8) + 3 , (maxCol/8) - 1 );
		dtioPuts("non ascii keys on the console screen.");
		dtioCursor( (maxRows/8) - 3 , (maxCol/8) + 5 ); 
		dtioPuts("To exit hit 'ESC' TWICE (IN A ROW). Hit any key to continue...");
		
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
	#if PLATFORM == GCC || PLATFORM == AIXC
		int key_char;
		key_char = getch();	
		/*printw("%d",key_char);	*/
		switch (key_char) {
			/* KEY_... is dtio.h defined*/
	    	case KEY_UP:    	key_char = UP;      break;
        	case KEY_DOWN:  	key_char = DOWN;    break;
       		case KEY_LEFT:  	key_char = LEFT;    break;
       		case KEY_RIGHT: 	key_char = RIGHT;   break;
       		case KEY_DC:  	 	key_char = DEL;  	break;
       		case KEY_HOME:  	key_char = HOME;  	break;
       		case KEY_END:   	key_char = END;  	break;
      		case KEY_PPAGE:    	key_char = PGDN;  	break;
       		case KEY_NPAGE:    	key_char = PGUP;  	break;
       		case KEY_IC:    	key_char = INSERT;  break;
      
       		case KEY_F(1):		key_char = F1;	break;
       		case KEY_F(2):		key_char = F2;	break;
       		case KEY_F(3):		key_char = F3;	break;
       		case KEY_F(4):		key_char = F4;	break;       		
        	case KEY_F(5):		key_char = F5; 	break;
        	case KEY_F(6):		key_char = F6;	break;
        	case KEY_F(7):		key_char = F7;	break;
        	case KEY_F(8):		key_char = F8;	break;
        	case KEY_F(9):		key_char = F9;	break;
        	case KEY_F(10):		key_char = F10; 	break;
        	case KEY_F(11):		key_char = F11; 	break;
        	case KEY_F(12):		key_char = F12; 	break;
        	default:        	key_char = UNKNOWN;
		}
		return key_char; 
	#elif PLATFORM == BCC32
		int key_char;
		key_char = getch();
		/*cprintf(": %d",key_char);
		getch();*/
		if(key_char == 0) {
			/*cprintf("ESC: %d",key_char);*/
			key_char = getch();
			switch (key_char) {
	    		/*KEY_... is conio.h defined*/
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
		   		case KEY_F1:		key_char = F1;		break;
		   		case KEY_F2:		key_char = F2;		break;
		   		case KEY_F3:	    key_char = F3;		break;
		   		case KEY_F4:		key_char = F4;		break;
		   		case KEY_F5:		key_char = F5;		break;
		   		case KEY_F6:		key_char = F6;		break;
		   		case KEY_F7:        key_char = F7;		break;
		  		case KEY_F8:        key_char = F8;		break;
		   		case KEY_F9:        key_char = F9;		break;
		   		case KEY_F10:       key_char = F10;		break;
		   		case KEY_F11:       key_char = F11;		break;
		   		case KEY_F12:       key_char = F12;		break;
        		default:            key_char = UNKNOWN;
    		}
		}
		
		switch(key_char) {
			case KEY_BKSPC:			key_char = BACKSPACE;	break;
			case KEY_TAB:			key_char = TAB;			break;
			case KEY_ESC:			key_char = ESC;			break;
		}
		
		return key_char;			
	#else 
		int key_char;
    	key_char = getch();
    	/*if (key_char == 27){
    		cprintf("key_char: %d",key_char);
			/*getch();
		/*}*/
    	if (key_char == 224) {
	    	key_char = getch();
	    	/*printf("224: %d",key_char);*/
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
		    	case KEY_F11:			key_char = F11;	break;
		    	case KEY_F12:			key_char = F12;	break;
        		default:        		key_char = UNKNOWN;
      		}
    	} else if (key_char == 0) {
	    	key_char = getch();
	    	/*printf("0:%d",key_char);*/
	    	switch (key_char) {
		    	case KEY_F1:		key_char = F1;		break;
		    	case KEY_F2:		key_char = F2;		break;
		    	case KEY_F3:		key_char = F3;		break;
		    	case KEY_F4:		key_char = F4;		break;
		    	case KEY_F5:		key_char = F5;		break;
		    	case KEY_F6:		key_char = F6;		break;
		    	case KEY_F7:		key_char = F7;		break;
		    	case KEY_F8:		key_char = F8;		break;
		    	case KEY_F9:		key_char = F9;		break;
		    	case KEY_F10:		key_char = F10;		break;
		    	default:        	key_char = UNKNOWN;
	    	}
		} 
		
		/*if (key_char == 8) {
			key_char = 10011;
			cprintf("key_char: %d",key_char);
		} else if (key_char == 9) {
			key_char = 10012;
			cprintf("key_char: %d",key_char);
		}*/
		/*other special keys*/
		/*if (key_char == 27) {
			key_char = ESC;
			cprintf("key_char: %d",key_char);
		}*/
		switch(key_char) {
			case KEY_BKSPC:			key_char = BACKSPACE;	break;
			case KEY_TAB:			key_char = TAB;			break;
			case KEY_ESC:			key_char = ESC;			break;

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
void dtioCursor(int row, int column) {
	#if PLATFORM == VSNET2K3
	int vRow = 0;                 /*validated row value*/
	int vCol = 0;                 /*validated col value*/

	/*validate row and col*/
	/*if invalid row, set coordinates to origin*/
	/*if ( row > dtioRows() || column > dtioColumns() ) {
		vRow = 0;
		vRow = row;
	} else {
		vRow = row;
		vCol = column; 
	}*/
				
		/*assign values to vsnet coord structs*/
		/*and move to desired coord.*/
		winscreen.X = row;
		winscreen.Y = column;				
		SetConsoleCursorPosition(std_out, winscreen);

	#elif PLATFORM == BCC32
		gotoxy(column + 1, row + 1);
	#else 
		move(row, column);
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
		putch(c);	
	#elif PLATFORM == AIXC || PLATFORM == GCC
		addch(c);
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
void dtioPuts(const char *s) {
	#if PLATFORM == VSNET2K3 || PLATFORM == BCC32
		cputs(s);
	#elif PLATFORM == GCC || PLATFORM == AIXC
		addstr(c);
	#endif
} 
    
/* Funcion - dtioRows
*  Description: Returns the number of rows on the screen.
*               
*  Arguements:   VOID
*  RETURN VALUE: INT
*/
int dtioRows(void) {
	#if PLATFORM == VSNET2K3
		return winscreen_info.dwMaximumWindowSize.X;	
	#elif PLATFORM == BCC32
    	struct text_info x;
     	gettextinfo(&x);
     	return x.screenheight;
	#else
		return LINES;
	#endif
}

/* Funcion - dtioColumns
*  Description: Returns the number of cols on the screen.
*               
*  Arguements:   VOID
*  RETURN VALUE: INT
*/
int dtioColumns(void) {
	#if PLATFORM == VSNET2K3
		return winscreen_info.dwMaximumWindowSize.Y;
	#elif PLATFORM == BCC32
    	struct text_info x;
     	gettextinfo(&x);
     	return x.screenwidth;	
	#else
		return COLS;
	#endif
}   