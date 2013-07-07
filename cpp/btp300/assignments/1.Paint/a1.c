/* Assignment 1 Version 1 - Paint a Screen
*
* FILE:		     a1.c - Main Program
* Author:        Timothy Duavis
* Last Modified: Sept 23/2005
*
* Description: Direct terminal I/O * library that hides platform dependencies.
*/

#include "dtio.h"

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
		display = dtioGetchar();
		if (display == ESC) esc++;
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
				case ESC:		dtioPuts("ESC");		break;
				case F1:		dtioPuts("F1"); 	 	break;
				case F2:		dtioPuts("F2"); 	 	break;
				case F3:		dtioPuts("F3"); 	 	break;
				case F4:		dtioPuts("F4"); 		break;
				case F5:		dtioPuts("F5"); 	 	break;
				case F6:		dtioPuts("F6"); 	 	break;
				case F7:		dtioPuts("F7"); 	 	break;
				case F8:		dtioPuts("F8"); 	 	break;
				case F9:		dtioPuts("F9"); 	 	break;
				case F10:		dtioPuts("F10"); 	 	break;
				case F11:		dtioPuts("F11"); 	 	break;
				case F12:		dtioPuts("F12"); 	 	break;
			}
		} else if (display == UNKNOWN)
			dtioPuts("UNKNOWN");
		else dtioPutchar(display);		
			dtioFlush();
	}
		
	/*Close Program*/
		dtioStop();
				
	return 0;
}