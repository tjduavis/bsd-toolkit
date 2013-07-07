/* Assignment 1 Version 1 - Paint a Screen
*
* FILE:		     a1.c - Main Program
* Author:        Timothy Duavis
* Last Modified: Sept 23/2005
*
* Description: Direct terminal I/O * library that hides platform dependencies.
*/

#include "dtio.h"
int counter = 0;
int origin = 0;
/*DEBUGER: 		cprintf("c = %d\n",c);*/
/*DEBUGER:			
	cprintf("maxRows %d\n",maxRows);
	cprintf("maxCol %d\n",maxCol);*/

int main(void) {
	/*local variable declaration*/
	int display = 0;
	int maxRows, maxCol;
	int esc = 0;
	
	int cRow, cCol;
	
	/*Welcome Header - set Header to middle of screen*/
	dtioStart();	
	/*dtioClear();*/
/*	
	
	cprintf("maxRows %d\n",maxRows);
	cprintf("maxCol %d\n",maxCol);*/
	
	dtioFlush();
	
	getch();
	dtioFlush();
	dtioClear();
		
	/*Main Program*/
	dtioCursor(0,0);
	while ( esc != 2 ) {
		/*printw("cM: %d",origin++);*/
		display = dtioGetchar();
		/*printw("display: %d\n",display);*/
		if (display == ESCAPE) esc++;
		else esc = 0;					/*reset*/

		if (display > 1000) {
			switch(display) {
				case HOME: 		dtioPuts("HOME"); 	 	break;
				case UP: 		dtioPuts("UP"); 	 	break;
				case DOWN: 		dtioPuts("DOWN"); 	 	break;
				case LEFT: 		dtioPuts("LEFT"); 	 	break;
				case RIGHT:		dtioPuts("RIGHT"); 	 	break;
				case END: 		dtioPuts("END"); 	 	break;
				case PGDN: 		dtioPuts("PGDN"); 	 	break;
				case PGUP: 		dtioPuts("PGUP"); 	 	break;
				case DEL: 		dtioPuts("DEL"); 	 	break;
				case INSERT: 	dtioPuts("INSERT");  	break;
				case BACKSPACE: dtioPuts("BACKSPACE");  break;
				case TAB:		dtioPuts("TAB");		break;
				case ESCAPE:	dtioPuts("ESCAPE");		break;
				case ENTER: 	dtioPuts("ENTER");		break;
				case F(1):		dtioPuts("F1"); 	 	break;
				case F(2):		dtioPuts("F2"); 	 	break;
				case F(3):		dtioPuts("F3"); 	 	break;
				case F(4):		dtioPuts("F4"); 		break;
				case F(5):		dtioPuts("F5"); 	 	break;
				case F(6):		dtioPuts("F6"); 	 	break;
				case F(7):		dtioPuts("F7"); 	 	break;
				case F(8):		dtioPuts("F8"); 	 	break;
				case F(9):		dtioPuts("F9"); 	 	break;
				case F(10):		dtioPuts("F10"); 	 	break;
				case F(11):		dtioPuts("F11"); 	 	break;
				case F(12):		dtioPuts("F12"); 	 	break;
			}
		} else if (display == UNKNOWN)
			dtioPuts("UNKNOWN");
		else dtioPutchar(display);		
			dtioFlush();
			
	   /*printw("|");*/
	}
		
	/*Close Program*/
		dtioStop();
				
	return 0;
}