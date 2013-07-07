/* Assignment 2 Version 1 - Paint a Screen
*
* FILE:		     dtio.c
* Author:        Timothy Duavis
* Last Modified: Sept 25/2005
*
* Description: Direct terminal I/O library that hides platform dependencies.
*/

#include "dtio.h"

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

	#elif PLATFORM == BCC32
		gettextinfo(&x);
		clrscr();

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
		/*COORD coordScreen = { 0, 0 };    // home for the cursor 
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi; 
		DWORD dwConSize;
		std_out = GetStdHandle(STD_OUTPUT_HANDLE);						/* MUST BE DECLARED inorder to use console */
		
		// Get the number of character cells in the current buffer. 
		//GetConsoleScreenBufferInfo( std_out, &csbi );
		//dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

		// Fill the entire screen with blanks.
		//FillConsoleOutputCharacter( std_out, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten );

		// Get the current text attribute.
		//GetConsoleScreenBufferInfo( std_out, &csbi );

		// Set the buffer's attributes accordingly.
		//FillConsoleOutputAttribute( std_out, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );

		// Put the cursor at its home coordinates.
		//SetConsoleCursorPosition( std_out, coordScreen );*/

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
		/* printf("dtioGetchar: %d",key_char); */
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
		if ( row >= 0 && row <= mRow && column >= 0 && column <= mCol ) {
			winscreen.X = column;
			winscreen.Y = row;
			SetConsoleCursorPosition(std_out, winscreen);
		}

	#elif PLATFORM == BCC32
		if ( row >= 0 && row <= mRow && column >= 0 && column <= mCol )
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

/*=================================================================================================/
 * Function - dtioDisplay	                                                                      *
 * Description    : Displays the string s on the screen specified by length.					  *
 *                  Function does not flush output buffer.
 *                  Undefined results if it does meet specs.
 *
 * Specifications :
 *
 * Arguements     :
 *
 * Return         : VOID
 *=================================================================================================*/

void dtioDisplay(const char *s, int row, int column, int length)  {
	/* Local declaration */
	int i = 0, dtioStrLen = strlen(s);

	if (s) {
		if (dtioStrLen > length && length) {			/* string s is greater than length of space */
			dtioCursor(row,column);
			for(i = 0; i < length; i++)
				dtioPutchar( (int)s[i]);
		} else if (dtioStrLen < length && length) {		/* string s is less than length of space */
			dtioCursor(row,column);
			dtioPuts(s);
			for (i = dtioStrLen + 1; i <= length; i++)
				dtioPutchar(32);
		} else if (length <= 0) {						/* string s fits exactly */
			dtioCursor(row,column);
			dtioPuts(s);
		}

	}
}

/*============================================================================================/
 * Function - dtioEdit
 * Description:
 *
 * Arguements : s - contains string
 *             row - row coordinate
 *			   col - column coordinate
 *			   len - length size
 *			   ppos - index value of string
 *
 * Return     : int value of the exit key
 *
 *==========================================================================================*/
int dtioEdit(char *s, int row, int col, int len, int *ppos) {

/********************************************************/
/*					Local Variables						*/
/********************************************************/

	int 	i = 0,j = 0;					/* Loop flags */
	int 	key;							/* keyboard key flag */
	int 	ovr  = 0;						/* ovride mode flag: not default */
	int 	exit = 0;						/* exit flag: loop of dtioEdit */
	int 	index;							/* cursor location value */
	char    *revert = NULL;
	char 	*tempS = NULL;					/* holds temporary edited string */
	char 	*swap  = NULL;					/* holder for tempS */

	if (s) {
		tempS = (char *) malloc(strlen(s)+1);
		strcpy(tempS,s);
	} else {
		tempS = (char *) malloc(1);
		tempS[0] = '\0';
	}

	if (*ppos != NULL)		index = *ppos + col;
	else 					index = col;

	dtioCursor(row,col);
	dtioPuts(tempS);
	dtioCursor(row,index);

	do {

		key = dtioGetchar();

		if (key == INSERT) {
			if (ovr)
				ovr = 0; 	/* toggle back to inv mode */
			else
				ovr = 1;	/* toggle back to ovr mode */

		} else if (key == HOME) {

			dtioCursor(row,col);	/* move cursor to the first character */
			index = col;			/* set cursor to home column 		  */

		} else if (key == END) {

			index = (strlen(tempS) - 1) + col;	/* length of string, not including the first + col location of string */
			if (index < len + col) index++;
			dtioCursor(row,index);

		} else if (key == RIGHT) {

			if (index+1 < (len + col))			/* move one cursor position to the right, limit end position */
				dtioCursor(row,++index);

		} else if (key == LEFT) {

			if (index-1 >= 0 )					/* move one cursor position to the left, limit begin position */
				dtioCursor(row,--index);

		} else if (key == DEL) {
		/******************************** Delete Algorithm **********************************/

			if (index <= strlen(tempS) + col && index >= 0) {		/* delete current character and moves character to the left one position, */
																	/* limit begin position */
				if (swap) free(swap);
				swap = (char *) malloc(strlen(tempS));				/* allocate 1 less the size of tempS */

				for (i = j = 0; i <= strlen(tempS); i++) {
					if (i != (index - col))
						swap[j++] = tempS[i];
				}
				swap[i-1]='\0';

				if (tempS) free(tempS);
				tempS = (char *) malloc(strlen(swap)+1);
				strcpy(tempS,swap);

				dtioCursor(row,col);
				dtioPuts(tempS);
				dtioPutchar(32);
				dtioCursor(row,col);

				/*dtioCursor(row+3,col);
				printf("size of tempS is %d: i = %d\n",strlen(tempS),i);*/
			}

		} else if (key == BACKSPACE) {
		/******************************** Backspace Algorithm **********************************/

			/* move one cursor position to the right, limit begin position */
			if (index > col && index <= strlen(tempS) + col) {

				if (swap) free(swap);
				swap = (char *) malloc(strlen(tempS));

				for (i = 0, j = 0; i <= strlen(tempS); i++)
					if (i != (index - col) - 1)
						swap[j++] = tempS[i];
				swap[i - 1] = '\0';

				if (tempS) free(tempS);
				tempS = (char *) malloc(strlen(swap)+1);
				strcpy(tempS,swap);

				/*dtioClear();
				dtioPuts(tempS);
				getch();*/

				dtioCursor(row,--index);
				for (i = (index - col); i < strlen(tempS); i++)
					dtioPutchar( (int)tempS[i] );
				dtioPutchar(32);
				dtioCursor(row,index);

			}

		} else if (key < 1000 && key > 0) {
			if (ovr) {
			/***************************** Ovride Mode *********************************/

				if (index < col + len) {
					if (index <= (strlen(s) + col) + 1)
						tempS[index - col] = key;

					++index;

					dtioPutchar(key);
				}

			}else {
			/***************************** Invert Mode *********************************/
			
			if (strlen(tempS) + 1 <= len + col) {
					if (swap) free(swap);
					swap = (char *) malloc(strlen(tempS)+2);

					for (i = 0,j = 0; j < strlen(tempS); i++) {
						if (i == index - col)
							swap[i] = key;
						else
							swap[i] = tempS[j++];
					}
					swap[i] = '\0';

					if (tempS) free(tempS);
					tempS = (char *) malloc(strlen(swap)+1);									
					strcpy(tempS,swap);
					
					dtioCursor(row,++index);
					dtioPutchar(key);
					if (index < strlen(tempS) + col)
						for(i = index - col; i < strlen(tempS); i++)
							dtioPutchar( (int)tempS[i] );
					dtioCursor(row,index);
				}
			}

		} else {
		/**************************** Terminate Editing Mode ******************************/

			if (key != ESCAPE) {
				/*if (s) free(s);
				s = (char *) malloc(strlen(tempS) + 1);*/
				strcpy(s,tempS);
			}

			exit = 1;
			
			/*dtioCursor(row+5,col);
			printf("goodbye %s",s);
			getch();*/

		}
		
	} while (!exit) ;

	if (tempS) free(tempS);
	if (swap) free(swap);


	return key;
}

/*==========================================================================================================/
 * Function - dtioMenu
 * Description:
 *
 * Arguements:
 *
 * Return    :
 *=========================================================================================================*/

int dtioMenu(const char *s[], int count, int row, int column, const char *box) {
	/******************************************************************************************************/
	/*                                        Local Variables                                             */
	/******************************************************************************************************/

	char defMenu[] = {'+', '-', '+', '|', '+', '-', '+', '|'};		/* default menux box */
	int len;
	int cRow = row + 1, cCol = column + 1, topRow = row;
	int exit = 0;
	int endSkip = 0;
	char *buffer = NULL;
	int i,j = 0;
	int a;
	int cursor;
	int depth = dtioRows();
	int width = dtioColumns();
	
	/******************************************************************************************************/
	/*                                   remember console screen                                          */
	/******************************************************************************************************/

	#if PLATFORM == BCC32
		
		int x1 = 1, y1 = 1;
		int x2 = dtioRows(), y2 = dtioColumns();
		
		buffer = (char *) malloc(depth * width * 3);
		gettext(x1, y1, x2, y2, buffer);
		dtioClear();
		
	#elif PLATFORM == VSNET2K3
		HANDLE ScreenBuffer;
		SMALL_RECT Read_screenRec, Write_screenRec;
		CHAR_INFO* dimension;
		COORD dimensionSize;
		COORD dimensionOrigin;

		dimension = (CHAR_INFO *) malloc(sizeof(CHAR_INFO) * depth * width);

		Read_screenRec.Top = dtioRows();
		Read_screenRec.Left = dtioColumns();
		Read_screenRec.Bottom = dtioRows() + depth;
		Read_screenRec.Right = dtioColumns() + width;

		Write_screenRec.Top = dtioRows();
		Write_screenRec.Left = dtioColumns();
		Write_screenRec.Bottom = dtioRows() + depth;
		Write_screenRec.Right = dtioColumns() + width;

		dimensionSize.Y = depth + 1;
		dimensionSize.X = width + 1;

		dimensionOrigin.Y = 0;
		dimensionOrigin.X = 0;

		std_out = GetStdHandle(STD_OUTPUT_HANDLE);						/* MUST BE DECLARED inorder to use console */
		ScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ |           // read/write access
			GENERIC_WRITE,
			0,                       // not shared
			NULL,                    // default security attributes
			CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
			NULL					 // reserved; must be NULL
		);

		ReadConsoleOutput(std_out, dimension, dimensionSize, dimensionOrigin, &Read_screenRec);
	#else
		/* aix and gcc */
		int x1 = 0, y1 = 0;
		chtype* screen;
		screen = (chtype *) malloc(sizeof(chtype) * depth * width);    /* chtype screen */
		
		i = 0;
		for (x1 = 0; x1 < depth; x1++) {
			for (y1 = 0; y1 < width; y1++)
				screen[i++] = mvinch(x1,y1);
		}
		dtioClear();
		
	#endif

	for (i = 0; i < (count - 1); i++) {         /* find longest character in string s array */
		if ( strlen(s[i]) > strlen(s[i + 1]) ) {
			len = strlen(s[i]);
		}
	}

	/******************************************************************************************************/
	/*                                           Construct Menu                                           */
	/******************************************************************************************************/

	/******************************** Print Top Border ****************************/

	dtioCursor(row,column);
	dtioPutchar(box[j++]);
	for (i = 0; i <= len; i++)
		dtioPutchar(box[j]);
	j++;
	dtioPutchar(box[j++]);
	dtioCursor(++row,column);

	/********************************* Print Menu **********************************/

	for (i = 0; i < count; i++) {
		dtioPutchar((int)box[j]);
		dtioPutchar(32);
		dtioPuts(s[i]);
		if (strlen(s[i]) < len) {
			for (a = 1; a < (len - strlen(s[i])) + 1; a++)
				dtioPutchar(32);
		}
		dtioPutchar(box[8 - 1]);
		dtioCursor(++row,column);
	}
	j++;

	/****************************** Print Bottom Border ***************************/

	dtioPutchar(box[j++]);
	for (i = 0; i <= len; i++)
		dtioPutchar(box[j]);
	j++;
	dtioPutchar(box[j]);

	dtioCursor(column + 1,row + 1);

	/*************************** Menu Functionality *******************************/
	
	dtioCursor(cRow,cCol);
	dtioPutchar(62);
	dtioCursor(cRow,cCol);

	do {
		cursor = dtioGetchar();
		if ((cRow - 1) > topRow && cursor == UP) {
			dtioPutchar(32);
			if (s[cRow-2][0] == NULL) {
				do {
					--cRow;
				} while(s[cRow][0] == NULL);
			}

			dtioCursor(--cRow,cCol);

			dtioPutchar(62);
			dtioCursor(cRow,cCol);
		} else if ((cRow + 1) < count && cursor == DOWN) {
			dtioPutchar(32);
			if (s[cRow][0] == NULL) {
				do {
					++cRow;
				} while(s[cRow][0] == NULL);
			}

			dtioCursor(++cRow,cCol);

			dtioPutchar(62);
			dtioCursor(cRow,cCol);
		} else if (cursor == ENTER || cursor == ESCAPE) {

		/******************************************************************************************************/
		/*										write console screen										  */
		/******************************************************************************************************/

			#if PLATFORM == BCC32
			/******************************************** BCC32 **********************************************/

				puttext(x1, y1, x2, y2, buffer);
				free(buffer);

			#elif PLATFORM == VSNET2K3
			/******************************************** VSNET2K3 *******************************************/

				WriteConsoleOutput(ScreenBuffer, dimension, dimensionSize, dimensionOrigin, &Write_screenRec);
				free(dimension);

			#else
			/************************************** AIX and GCC LINUX *****************************************/

				i = 0;
				for (x1 = 0; x1 < depth; x1++) 
					for (y1 = 0; y1 < width; y1++) {
						move(x1,y1);
						addch(screen[i++]);
					}		

			#endif

			exit = 1;
			if (cursor == ESCAPE)
				cRow = -1;

		}
	} while (!exit);
	
	/*printf("*** %d ***\n",cRow);
	getch();*/
	return cRow;
}