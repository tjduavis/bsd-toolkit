/* Assignment 1 Version 1 - Paint a Screen
*
* FILE:		     dtio.c
* Author:        Timothy Duavis
* Last Modified: Sept 22/2005
*
* Description: Direct terminal I/O * library that hides platform dependencies.
*/

#include "dtio.h"

/* Include Platform Specific Library */
#if PLATFORM == VSNET2K3							
    #define DTIO_LIBRARY <conio.h>
    #include <Windows.h>						/*VSNET2K3 requires windows.h + stdlib.h*/
    #include <stdlib.h>							
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
	#if PLATFORM == GCC
	/*gcc platform functions*/
		initscr();
		noecho();
		keypad(stdscr,1);
		printw("Welcome to the direct terminal IO program.\n");
		printw("To Begin type any characters to see the codes. To QUIT hit the ESC key.\n\n");		
	#else
		system("cls");
		cputs("Welcome to the direct terminal IO program.\n");
		cputs("To Begin type any characters to see the codes. To QUIT hit the ESC key.\n\n");
	#endif
}

/* Funcion - dtioFlush
*  Description: Displays the characters still in the 
*               output buffer (if any).
*  Arguements:   VOID
*  RETURN VALUE: VOID
*/
void dtioFlush(void) {
	#if PLATFORM == GCC
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
	#if PLATFORM == GCC
		int key_char;
		int fkey;
		int count = 0;
		int i;
		key_char = getch();	
		printw("%d",key_char);	
		switch (key_char) {
	    	case KEY_UP:    	key_char = UP;      break;
        	case KEY_DOWN:  	key_char = DOWN;    break;
       		case KEY_LEFT:  	key_char = LEFT;    break;
       		case KEY_RIGHT: 	key_char = RIGHT;   break;
       		case KEY_DC:  	 	key_char = DEL;  	break;
       		case GCC_KEY_HOME:  key_char = HOME;  	break;
       		case GCC_KEY_END:   key_char = END;  	break;
      		case KEY_PPAGE:    	key_char = PGDN;  	break;
       		case KEY_NPAGE:    	key_char = PGUP;  	break;
       		case KEY_IC:    	key_char = INSERT;  break;
      
       		case KEY_F(1):		key_char = F(1);	break;
       		case KEY_F(2):		key_char = F(2);	break;
       		case KEY_F(3):		key_char = F(3);	break;
       		case KEY_F(4):		key_char = F(4);	break;
       		
        	case KEY_F(5):		key_char = F(5); 	break;
        	case KEY_F(6):		key_char = F(6);	break;
        	case KEY_F(7):		key_char = F(7);	break;
        	case KEY_F(8):		key_char = F(8);	break;
        	case KEY_F(9):		key_char = F(9);	break;
        	case KEY_F(10):		key_char = F(10); 	break;
        	case KEY_F(11):		key_char = F(11); 	break;
        	case KEY_F(12):		key_char = F(12); 	break;
		}
		return key_char;
    #else 
		int key_char;
    	key_char = getch();
    	if (key_char == 224) {
	    	key_char = getch();
	    	printf("%d",key_char);
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
    	} else if (key_char == 0) {
	    	key_char = getch();
	    	printf("%d",key_char);
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
		} else printf("%d",key_char); 
    	return key_char;
  	#endif
}

/* Funcion - dtioStop
*  Description: Cleans up direct terminal I/O.
*               
*  Arguements:   VOID
*  RETURN VALUE: VOID
*/
void dtioStop(void) {
	#if PLATFORM == GCC
    	refresh(); 
    	endwin();
    #else
  		system("cls");
  #endif
}     