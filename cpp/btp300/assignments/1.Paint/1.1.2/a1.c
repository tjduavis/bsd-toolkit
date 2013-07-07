/* Assignment 1 Version 1 - Paint a Screen
*
* FILE:		     a1.c - Main Program.
* Author:        Timothy Duavis
* Last Modified: Sept 25/2005
*
* Description: Program that places key characters on the console screen. This program uses
*              custom direct terminal I/O library that hides platform dependencies.
*/

#include "dtio.h"

int main(void) {
	/* local variable declaration */
	int display = 0;
	int maxRows, maxCol;
	int esc = 0;

	dtioStart();	
	maxRows = dtioRows();
	maxCol	= dtioColumns();
	
	/* WELCOME HEADER */
	dtioCursor( maxRows/2 - 5, maxCol/2 - 25);		
	dtioPuts("***Welcome to BTP300 A1 - Paint a Screen***");
	dtioCursor( maxRows/2 - 3, maxCol/2 - 15);
	dtioPuts("Description:");
	dtioCursor( maxRows/2 - 2, maxCol/2 - 15);
	dtioPuts("Simple program that prints ascii and");
	dtioCursor( maxRows/2 - 1, maxCol/2 - 15);
	dtioPuts("non ascii keys on the console screen.");
	dtioCursor( maxRows/2 + 5, maxCol/2 - 30);  
	dtioPuts("To exit hit 'ESC' TWICE (IN A ROW). Hit any key to continue...");
	dtioFlush();
	
	getch();
	
	dtioFlush();
	dtioClear();
		
	/* Main Program */
	dtioCursor(0,0);
	while ( esc != 2 ) {
		display = dtioGetchar();
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
			
	}
	
	dtioStop();
				
	return 0;
}