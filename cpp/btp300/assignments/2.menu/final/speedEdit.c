/*======================================================/
 *                                                     *
 * Speed Edit                                          *  
 *	Description : Randomnizes a string using           * 
 *                using alphaphetical characters. User *
 *                tries to copy the string and records *
 *                the duration.                        *
 *                Speed Edit demontrates the           *
 *                dtio library.                        *
 *                                                     *
 *	author      : Timothy Duavis                       *
 *  file        : speedEdit.c                          *
 *  modified    : October 26, 2005                     *
 *                                                     *  
/*====================================================*/

#include <stdio.h>
#include <time.h>
#include "dtio.h"

/************* MACROS ********************************/
#define A          97
#define Z          122
#define ORIGIN     0
#define LIMIT      26
#define CENTER_ROW 10
#define CENTER_COL 10

int main(void) {
	
	float _diff;
	int i;
	int complete = 1;
	int cursor = 0;
	time_t c0, c1;
	
	char str[LIMIT + 1];
	char sortstr[27] = "--------------------------";
	
	const char *choice[] = {"Retry","Quit"};
	const char box[] = { '_', '_', '_', '|', '+', '-', '+', '|' };
	char keepgoing = 'y';
	int exit = 0;
	
	/******************* WELCOME HEADER *************************/
	dtioStart();
	dtioCursor(CENTER_ROW,CENTER_COL);
	dtioPuts("Welcome to SpeedEdit");
	dtioCursor(CENTER_ROW + 5,CENTER_COL + 5);
	dtioPuts("Match the string above and see how fast you can type it out!!!");
	dtioCursor(CENTER_ROW + 6,CENTER_COL + 5);
	dtioPuts("Goodluck and Enjoy (hint: type INSERT KEY first)");
	dtioCursor(CENTER_ROW + 7,CENTER_COL + 5);
	dtioPuts("Press any key to continue...");
	getch();
	dtioClear();
	
	/******************* RANDOMNIZE STR ************************/
	srand(time(NULL));
	for(i = 0; i < LIMIT; i++) 
		str[i] = A + rand() % (Z + 1 - A);
	str[i] = '\0';
	
	/************************ START ***************************/	
	do {
		
		time(&c0);
		do {
			
			dtioCursor(CENTER_ROW,CENTER_COL);
			dtioPuts(str);
					
			dtioCursor(CENTER_ROW + 2,CENTER_COL - 1);
			dtioPutchar( (int)'|' );
			dtioCursor(CENTER_ROW + 2,CENTER_COL + LIMIT);
			dtioPutchar( (int)'|' );
			
			dtioEdit(sortstr,CENTER_ROW + 2,CENTER_COL,LIMIT,&cursor);
			
			if ( !(strcmp(sortstr, str)) )
				keepgoing = 'n';		
			else {
							
				dtioCursor(CENTER_ROW + 4,CENTER_COL);
				dtioPuts("Incorrect Keep going ? Y/N ");
				keepgoing = dtioGetchar();
				dtioPutchar(keepgoing);
				complete = 0;		
			}
				
			dtioClear();
			
		} while( keepgoing != 'n' && keepgoing != 'n' );
		time(&c1);
		
		if (complete)  {
			_diff = difftime (c1,c0);
			dtioCursor(CENTER_ROW,CENTER_COL);
			#if PLATFORM == VSNET2K3 || PLATFORM == BCC32
			
				printf("Time is: %.2lf s\n",_diff);
			
			#else
			
				printw("Time is: %.2lf s\n",_diff);
			
			#endif
		}
		dtioCursor(CENTER_ROW + 1,CENTER_COL);
		dtioPuts("Play again ? ");
		exit = dtioMenu(choice,2,ORIGIN,ORIGIN,box);
		
		dtioClear();
	} while ( exit != 2);
	
	dtioStop();
	
	return 0;
} 	