/*==============================================================================/
 *                                                                             * 
 * Assignment 2 Version 1.0 - Menu Driven Line Editor                          *
 *                                                                             * 
 * FILE           : dtio_v2.c                                                  * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : October 26, 2005                                           *
 *                                                                             *
 * Description    : Direct terminal I/O library that                           *
 *                  hides platform dependencies.                               *
 *                  A2.1 includes menu driven line editor.                     *
 *                                                                             * 
 * Specs created  : Chris S. - Seneca College                                  * 
 *                                                                             *  
/*=============================================================================*/

#include "dtio.h"

/****************** Include Platform Specific Libraries ************************/
#if PLATFORM == VSNET2K3
 /************************** VS.Net Env ******************************/
    
	#define DTIO_LIBRARY <conio.h>
    #include <Windows.h>

    /********* VS.NET Specified console screen structures and handles ****************/
    
	HANDLE std_out;                               /* standard handle for output      */
    COORD winscreen;                              /* standard structure              */
	CONSOLE_SCREEN_BUFFER_INFO winscreen_info;    /* structure holds additional info */
	
#elif PLATFORM == BCC32
/************************** Borland Env ******************************/
    
	#define DTIO_LIBRARY <conio.h>
	
	 /**************** standard structure - console screen info *********************/

	struct text_info x;				  

#else
/************************* AIX + GCC Env ****************************/

    #define DTIO_LIBRARY <curses.h>

#endif

#include DTIO_LIBRARY

/*==============================================================================/
 * Funcion - dtioStart                                                         *
 *                                                                             *
 *  Description  : Initializes the direct terminal routines (if necessary).    *
 *                                                                             * 
 *  Arguements   : void                                                        *  
 *  RETURN VALUE : void                                                        * 
 *                                                                             *
/*=============================================================================*/

void dtioStart(void) {

	#if PLATFORM == VSNET2K3
	/************************** VS.Net Env ******************************/
	
		std_out = GetStdHandle(STD_OUTPUT_HANDLE);
		
		/* MUST BE DECLARED inorder to use console */
		/* and structures */						
		GetConsoleScreenBufferInfo(   
			std_out, 						
			&winscreen_info
		);			
		dtioClear();

	#elif PLATFORM == BCC32
	/************************** Borland Env ******************************/
		gettextinfo(&x);
		clrscr();

	#else
	/************************* AIX + GCC Env ****************************/
	
		initscr();         /* Initialize direct terminal console        */
		noecho();          /* turn off echo of characters when typed    */
		cbreak();          /* program controls revert on each keyboard  */
		keypad(stdscr,1);  /* non ascii keys are treated as keys.       */

	#endif

}

/*==============================================================================/
 * Funcion - dtioStop                                                          *
 *                                                                             *
 *  Description: Cleans up direct terminal I/O.                                *
 *                                                                             *
 *  Arguements:   VOID                                                         *
 *  RETURN VALUE: VOID                                                         *
 *                                                                             *
 *=============================================================================*/
 
void dtioStop(void) {

    dtioClear();
  		
 	#if PLATFORM == AIXC || PLATFORM == GCC
    /************************* AIX + GCC Env ****************************/
    	
 		refresh();
    	endwin();
    	
	#endif
	
}

/*==============================================================================/
 *                                                                             * 
 * Funcion - dtioClear                                                         *
 *  Description: Clears the screen and leaves the cursor in the                *
 *				upper left-hand corner.                                        *
 *                                                                             *
 *  Arguements:   VOID                                                         *
 *  RETURN VALUE: VOID                                                         *
 *                                                                             *
 *=============================================================================*/
 
void dtioClear(void) {
	#if PLATFORM == VSNET2K3
	/************************** VS.Net Env ******************************/
	
		system("cls");

	#elif PLATFORM == BCC32
	/************************** Borland Env ******************************/
		
		clrscr();

	#else
	/************************* AIX + GCC Env ****************************/
	
		erase();
	
	#endif
}

/*==============================================================================/
 * Funcion - dtioFlush                                                         *
 *  Description: Displays the characters still in the                          *
 *               output buffer (if any).                                       *
 *                                                                             *
 *  Arguements:   VOID                                                         *
 *  RETURN VALUE: VOID                                                         *
 *                                                                             *
 *=============================================================================*/

void dtioFlush(void) {
	#if PLATFORM == GCC || PLATFORM == AIXC
	/************************* AIX + GCC Env ****************************/
	
		refresh();

	#endif
}

/*==============================================================================/ 
 * Funcion - dtioGetchar                                                       *
 *  Description: Returns the universal key code that                           *  
 *				identifies the key pressed.                                    * 
 *                                                                             *
 *  Arguements:   VOID                                                         *
 *  RETURN VALUE: Int                                                          *
 *                                                                             *
 *=============================================================================*/

int dtioGetchar(void) {
	int key_char;

	#if PLATFORM == GCC
	/************************* GCC Env ************************************/
		
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
	/************************* AIX Env *********************************/
		
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
	/************************** Borland Env ******************************/
	
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
	/************************** VS.Net Env ******************************/
	
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

/*==============================================================================/
 * Funcion - dtioCursor                                                        *
 *  Description  : Positions the cursor at the row and col specified.          * 
 *				   Row 0 is top row and Col 0 is lefmost.                      *
 *                 This function has undefined results if either parameter     * 
 *                 is invalid.                                                 *   
 *			       This function does not flush the output buffer.             *
 *                                                                             *
 *  Arguements   :  void                                                       *
 *  Return value :  void                                                       *
 *                                                                             *
 *=============================================================================*/

void dtioCursor( int row , int column ) {
	
	/* max columns and max rows */
	int mRow = dtioRows();					
	int mCol = dtioColumns();

	#if PLATFORM == VSNET2K3
	/************************** VS.Net Env ******************************/
	
		if ( row >= 0 && row <= mRow && column >= 0 && column <= mCol ) {
			
			winscreen.X = column;
			winscreen.Y = row;
			
			SetConsoleCursorPosition(std_out, winscreen);
			
		}

	#elif PLATFORM == BCC32
	/************************** Borland Env ******************************/
	
		if ( row >= 0 && row <= mRow && column >= 0 && column <= mCol )
				gotoxy( column + 1, row + 1 );
				
	#else
	/************************* AIX + GCC Env ****************************/
	
		if ( row >= 0 && row <= mRow && column >= 0 && column <= mCol )
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
	/********************** VS.Net + Borland Env *************************/
		putch( c );

	#else
	/************************* AIX + GCC Env ****************************/
		addch( c );

	#endif
}

/*==============================================================================/
 * Funcion - dtioPuts                                                          *
 *  Description  : Displays the null-terminated string pointed to by s         *
 *                 starting at the current cursor position.                    *
 *				   The function leaves the cursor just after the last          * 
 *                 character displayed. If the string exceeds in length the    *
 *                 available space on the current line of output, this         * 
 *                 function has undefined results. This function does not      *
 *                 flush the output buffer.                                    *
 *                                                                             *
 *  Arguements   : void                                                        *
 *  Retnrn value : void                                                        *
 *                                                                             *
 *=============================================================================*/
 
void dtioPuts( const char *s ) {
		
	int c_ptn;		/* cursor position     */
	int diff;		/* difference in space */
	int y;

	#if PLATFORM == VSNET2K3
	/************************** VS.Net Env ******************************/
	
		std_out = GetStdHandle( STD_OUTPUT_HANDLE );					/* MUST BE DECLARED inorder to use console */
		GetConsoleScreenBufferInfo( std_out, &winscreen_info );			/* structure declared in header            */

		c_ptn = winscreen_info.dwCursorPosition.X;
		diff = dtioColumns() - c_ptn;
		if ( strlen( s ) <= diff )
			cputs( s );

	#elif PLATFORM == BCC32
	/************************** Borland Env ******************************/
	
     	c_ptn = wherex();
     	diff = dtioColumns() - c_ptn;

     	if ( strlen( s ) <= diff)
			cputs( s );

	#else
	/************************* AIX + GCC Env ****************************/
	    
	    /* function that gets current position on std console screen */  
		getyx(stdscr, y, c_ptn);
		diff = dtioColumns() - c_ptn;

		if ( strlen( s ) <= diff )
			addstr( s );

	#endif
}

/*==============================================================================/
 * Funcion - dtioRows                                                          *
 *  Description : Returns the number of rows on the screen.                    *
 *				  Rows are the screen height.                                  *
 *                                                                             *
 *  Arguements  : void                                                         *
 *  Return Value: int - max row value                                          *
 *                                                                             *
 *=============================================================================*/
 
int dtioRows( void ) {
	#if PLATFORM == VSNET2K3
	/************************** VS.Net Env ******************************/
	
		return winscreen_info.dwMaximumWindowSize.Y;

	#elif PLATFORM == BCC32
    /************************** Borland Env ******************************/
    
	 	return x.screenheight;

    #else
    /************************* AIX + GCC Env ****************************/
    
		return LINES;
		
	#endif
}

/*==============================================================================/
 * Funcion - dtioColumns                                                       *
 *  Description  : Returns the number of cols on the screen.                   * 
 *				   Cols are the screen width.                                  *                      
 *                                                                             *
 *  Arguements   : void                                                        *
 *  RETURN VALUE : int - max column                                            *
 *                                                                             *
 *=============================================================================*/
int dtioColumns( void ) {
	#if PLATFORM == VSNET2K3
	/************************** VS.Net Env ******************************/
	
		return winscreen_info.dwMaximumWindowSize.X;

	#elif PLATFORM == BCC32
	/************************** Borland Env ******************************/
	
	 	return x.screenwidth;
	
	#else
	/************************* AIX + GCC Env ****************************/
	
		return COLS;
		
	#endif
}

/*=================================================================================================/
 * Function - dtioDisplay	                                                                      *
 * Description    : Displays the string s on the screen specified                                 * 
 *                  by length. Function does not flush output buffer.                             *                   
 *                  Undefined results if it does meet specs.                                      *
 *                                                                                                *
 * Arguements     : s - constant string                                                           *
 *                  row - initial row                                                             *
 *                  column - initial column                                                       *
 *                  length - length of space                                                      *
 *                                                                                                *
 * Return         : VOID                                                                          *
 *================================================================================================*/

void dtioDisplay(const char *s, int row, int column, int length)  {
	
/********************************************************/
/*					Local Variables						*/
/********************************************************/	

	int i = 0, j;
	int dtioStrLen = strlen(s);
	int screenLimit = dtioColumns();

	if (s) {
		if (dtioStrLen == length) {
			
			dtioCursor(row,column);
			dtioPuts(s);			
			
		} else if (dtioStrLen > length && length) {
						
			dtioCursor(row,column);
			for(i = 0, j = column; i < dtioStrLen && j; i++) {
				
				if ( j == screenLimit )
					j = 0;
				else {
					dtioPutchar( (int)s[i] );
					j++;
				}
				
			}
				
		} else if (dtioStrLen < length && length) {
			
			dtioCursor(row,column);
			dtioPuts(s);
			
			for (i = dtioStrLen + 1; i <= length; i++)
				dtioPutchar(KEY_SPACE);
				
		} else if (length <= 0) {
			
			dtioCursor(row,column);
			dtioPuts(s);
			
		}

	}
}

/*=======================================================================/
 * Function - dtioEdit                                                  *
 * Description   : Controls full editing  of string, where ever cursor  *
 *                 is placed with len defining editable field.          *
 *                                                                      *
 * Functionality : LEFT      - move left one character, limit len       * 
 *                 RIGHT     - move right one character, limit len      *
 *                 HOME      - go to beggining of string                *
 *                 END       - go to end of character in string,        * 
 *                             limit len.                               *
 *                 INSERT                                               * 
 *                    OVR    - replaces character at cursor position or *
 *                             appends, if possible.                    * 
 *                    INS    - default, adds character, moves string    * 
 *                             one to left or appends, if possible.     *
 *                 DEL       - Discards character at currernt cursor    *
 *                             position and moves remaining characters  *
 *                             to the left, if possible.                *
 *                 BACKSPACE - discards character to left of cursor and *
 *                             moves remaining characters to the left.  *
 *                                                                      * 
 *                                                                      *
 * Arguements    : s    - contains string                               *
 *                 row  - row coordinate                                *
 *			       col  - column coordinate                             *
 *			       len  - length size                                   * 
 *			       ppos - index value of string                         *
 *                                                                      *
 * Return        : int value of the exit key                            *
 *                                                                      *
 *======================================================================*/
 
int dtioEdit(char *s, int row, int col, int len, int *ppos) {

/********************************************************/
/*					Local Variables						*/
/********************************************************/

	int 	i = 0,j = 0;					/* Loop flags */
	int 	key;							/* keyboard key flag */
	int 	screenLimit = dtioColumns();
	int 	ovr  = 0;						/* ovride mode flag: not default */
	int 	exit = 0;						/* exit flag: loop of dtioEdit */
	int 	index;							/* cursor location value */
	char 	*tempS = NULL;					/* holds temporary edited string */

	/* copy s to temporary string for manipulation */

	tempS = (char *) malloc(strlen(s)+1);
	strcpy(tempS,s);

	/* set temporary cursor variable */
	if (*ppos)
		index = *ppos + col;
	else
		index = col;
	
	/*********************************** START ***********************************/
	dtioDisplay(s,row,col,len);		
	dtioCursor(row,index);	

	do {
	/********************************* USER INPUT ***********************************/
	
		key = dtioGetchar();

		if (key == INSERT) {
		/******************************** INSERT **********************************/
			
			if (ovr) ovr = 0; 	
			else 	 ovr = 1;	

		} else if (key == HOME) {
		/******************************** HOME **********************************/	

			dtioCursor(row,col);	
			index = col;		

		} else if (key == END) {
		/******************************** END **********************************/
			
			if ( strlen(tempS) + col <= dtioColumns() ) {
			/* length of string, not including the first + col location of string */
				
				index = (strlen(tempS) - 1) + col;	
				
				if (index + 1 < len + col) 
					index++;
				
			} else  index = dtioColumns() - 1;
			
			dtioCursor(row,index);

		} else if (key == RIGHT) {
		/******************************** RIGHT **********************************/
		
			if ( index + 1 < (len + col) )			
				dtioCursor(row,++index);

		} else if (key == LEFT) {
		/******************************** LEFT **********************************/
		
			if (index - 1 >= col)					
				dtioCursor(row,--index);

		} else if (key == DEL) {
		/******************************** Delete Algorithm **********************************/
		
		/* delete current character and moves character to the left one position, */
		/* limit begin position                                                   */
		
			if (index <= strlen(tempS) + col) {		
																				
				truncate(DEL, index, col, tempS);

				/* output string from index (minus starting position) */				
				dtioCursor(row,index);
				for (i = index - col, j = index; i < strlen(tempS); i++,j++) {
					
					if (j == screenLimit)
						i = strlen(tempS);
					else
						dtioPutchar(tempS[i]);
						
				}
				
				if (strlen(tempS) + col < screenLimit) dtioPutchar(KEY_SPACE);
				dtioCursor(row,index);

			}

		} else if (key == BACKSPACE) {
		/******************************** Backspace Algorithm **********************************/

			/* move one cursor position to the right, limit begin position */
			
			if (index > col && index <= strlen(tempS) + col) {
				
				truncate(BACKSPACE, index, col, tempS);

				/* output string from index (minus starting position) */
				dtioCursor(row,--index);
				for (i = index - col, j = index; i < strlen(tempS); i++,j++) {
					
					if (j == screenLimit)
						i = strlen(tempS);
					else
						dtioPutchar( (int)tempS[i] );
						
				}
				
				if (strlen(tempS) + col < screenLimit) dtioPutchar(KEY_SPACE);
				dtioCursor(row,index);

			}

		} else if (key < 1000 && key > 0) {
		/******************************** CHARACTER INPUTS **********************************/
			if (ovr) {
			/***************************** Overstrike Mode *****************************/
                
				if (index <= (strlen(tempS) - 1) + col) {
				/* index is still within string */
				
					tempS[index - col] = key;
					dtioPutchar(key);
				
				} else if (strlen(tempS) + 1 <= len) {
				
					append(key, index, col, tempS);
					dtioPutchar(key);
					
				}
                
				if (index + 1 <= (len + col) - 1 && index + col <= screenLimit - 1)
					++index;

				dtioCursor(row,index);

			}else {
			/***************************** Insert Mode *****************************/

				if (strlen(tempS) + 1 <= len) {

					append(key, index, col, tempS);
					
					/*** ouput string from current cursor position ***/
					
					dtioCursor(row,index);
					dtioPutchar(key);
					if (index < strlen(tempS) + col) {
						
						for(i = ++index - col, j = index - 1; i < strlen(tempS); i++,j++) {
							
							if (j == screenLimit - 1)
								i = strlen(tempS);
							else 
								dtioPutchar( (int)tempS[i] );
								
						}
						
					}						
					
					/* do not move cursor if cursor is within screen limit or len */
					
					if ( index + col == screenLimit - 1 || index == len + col ) 
						dtioCursor(row,--index);
					else 
						dtioCursor(row,index);
				}
			}

		} else {
		/**************************** Terminate Editing Mode ********************/

			if (key != ESCAPE) 
				strcpy(s,tempS);

			exit = 1;

		}
		
	} while (!exit) ;

	if (tempS) free(tempS);

	return key;
}

/*========================================================================/
 * Function - truncate()                                                 *
 * 	Description: Delete or backspace algorithm                           *
 *                                                                       *
 *	Parameter  : int flag - backspace or delete key                      *
 *               char* s  - source string                                *
 *                                                                       *
 *  Return     : void                                                    *
 *                                                                       *
 *=======================================================================*/

void truncate(int flag, int cpos, int c, char * ts) {
	/*********************************************************************/
	/*                          Local Variables                          */
	/*********************************************************************/
	
	int i = 0, j = 0;	
	char *swap;
	
	/*** allocate 1 less the size of tempS ***/
    swap = (char *) malloc(strlen(ts));
	
	for (i = j = 0; i < strlen(ts); i++) {
		
		if (flag == DEL) {
			
			if (i != cpos - c)
				swap[j++] = ts[i];
				
		} else {
			
			if (i != (cpos - c) - 1)
				swap[j++] = ts[i];
				
		}
			
	}
	swap[j]='\0';

	/* copy swap into ts */
    strcpy(ts,swap);
    free(swap);	
	
}

/*========================================================================/
 * Function - append                                                     *
 * 	Description: append character to string                              *
 *                                                                       *
 *	Parameter  : int k - ascii nummber of character                      *   
 *               char* s  - source string                                *
 *                                                                       *
 *  Return     : void                                                    *
 *                                                                       *
 *=======================================================================*/

void append(int k, int cpos, int c, char * ts) {
	/*********************************************************************/
	/*                          Local Variables                          */
	/*********************************************************************/

	int i = 0, j = 0;	
	char *swap;

	swap = (char *) malloc(strlen(ts)+2);
	for (i = 0,j = 0; j < strlen(ts); i++) {
		if (i == cpos - c)
			swap[i] = k;
        else
            swap[i] = ts[j++];
	}
	if (cpos - c == i) {
		swap[i] = k;
		swap[i+1] = '\0';
	} else
		swap[i] = '\0';

	/* copy swap into ts */										
	strcpy(ts,swap);
	free(swap);			
	
}

/*========================================================================/
 * Function - dtioMenu
 * Description:
 *
 * Arguements:
 *
 * Return    :
 *=======================================================================*/

int dtioMenu(const char *s[], int count, int row, int column, const char *box) {
	/*********************************************************************/
	/*                          Local Variables                          */
	/*********************************************************************/

	int a, i, j = 0, exit = 0;				                        /* loop and help flags */
	char defMenu[] = {'+', '-', '+', '|', '+', '-', '+', '|'};		/* default menux box */
	
	int maxLen;								/* max length of string */
	
	/* helpers for building menu */
	int cRow = row + 1, cCol = column + 1;	/* current cursor position in box menu */
	int cRow_Home = row + 1;				/* top cursor position in box menu */
	int buildRow = row;						/* top cursor position */
	
	int cursorMove;							/* user current cursor */
	
	/* settings for reading and writing console oututs */
	int depth = dtioRows();
	int width = dtioColumns();
	int x1,y1,x2,y2;
	
	#if PLATFORM == VSNET2K3

		SMALL_RECT screenRec;
		CHAR_INFO* dimension;
		COORD dimensionSize;
		COORD dimensionOrigin;
		
	#elif PLATFORM == BCC32
	
		void *buffer = NULL; 
	
	#elif PLATFORM == GCC || PLATFORM == AIXC

		chtype* screen;	

	#endif

	/* find longest character in string s array */
	for (i = 0; i < (count - 1); i++) {         
		if ( strlen(s[i]) > strlen(s[i + 1]) ) {
			maxLen = strlen(s[i]);
		}
	}	
	
	/**********************************************************************/
	/*                     remember console screen                        */
	/**********************************************************************/

	#if PLATFORM == BCC32
	/************************** Borland Env ******************************/	
		
		x1 = row + 1;
		y1 = column + 1;
		x2 = row + maxLen + 4;
		y2 = column + count + 3;

		buffer = (void *) malloc(depth * width * 3);
		gettext(x1, y1, x2, y2, buffer);
		
	#elif PLATFORM == VSNET2K3
	/************************** VS.Net Env ******************************/

		dimension = (CHAR_INFO *) malloc(sizeof(CHAR_INFO) * depth * width);

		screenRec.Top = row;
		screenRec.Left = column;
		screenRec.Bottom = row + depth;
		screenRec.Right = column + width;

		dimensionSize.Y = depth;
		dimensionSize.X = width;

		dimensionOrigin.Y = row;
		dimensionOrigin.X = column;

		std_out = GetStdHandle(STD_OUTPUT_HANDLE);			

		ReadConsoleOutput(std_out, dimension, dimensionSize, dimensionOrigin, &screenRec);
		
	#else
	/************************* AIX + GCC Env ****************************/
	
		x1 = y1 = 0;

		screen = (chtype *) malloc(sizeof(chtype) * depth * width);    /* chtype screen */
		
		i = 0;
		for (x1 = 0; x1 < depth; x1++) {
			for (y1 = 0; y1 < width; y1++)
				screen[i++] = mvinch(x1,y1);
		}
		
	#endif

	/******************************************************************/
	/*                        Construct Menu                          */
	/******************************************************************/

	/************************ Print Top Border ************************/

	dtioCursor(buildRow,column);
	dtioPutchar(box[j++]);
	for (i = 0; i <= maxLen; i++)
		dtioPutchar(box[j]);
	j++;
	dtioPutchar(box[j++]);
	dtioCursor(++buildRow,column);

	/*********************** Print Menu *******************************/

	for (i = 0; i < count; i++) {
		
		dtioPutchar((int)box[j]);
		dtioPutchar(KEY_SPACE);
		dtioPuts(s[i]);
		
		if (strlen(s[i]) < maxLen) {
			
			for (a = 1; a < (maxLen - strlen(s[i])) + 1; a++)
				dtioPutchar(KEY_SPACE);
				
		}
		
		dtioPutchar(box[8 - 1]);
		dtioCursor(++buildRow,column);
	}
	j++;

	/******************* Print Bottom Border **************************/

	dtioPutchar(box[j++]);
		for (i = 0; i <= maxLen; i++)
		dtioPutchar(box[j]);
	j++;
	dtioPutchar(box[j]);

	dtioCursor(column + 1,buildRow + 1);

	/******************* Menu Functionality **************************/
	
	dtioCursor(cRow,cCol);
	dtioPutchar(KEY_RIGHT_ARROW);
	dtioCursor(cRow,cCol);

	do {
		
		cursorMove = dtioGetchar();
		
		if ((cRow - 1) > row && cursorMove == UP) {
			
			dtioPutchar(KEY_SPACE);
			if (!(s[ (cRow - cRow_Home) - 1 ][0])) {
				do {
					--cRow;
				} while(!(s[ (cRow - cRow_Home) ][0]));
			} else
				--cRow;

			dtioCursor(cRow,cCol);
			dtioPutchar(KEY_RIGHT_ARROW);
			dtioCursor(cRow,cCol);
			
		} else if ((cRow + 1) < (cRow_Home + count) && cursorMove == DOWN) {
			
			dtioPutchar(KEY_SPACE);
			if (!(s[ (cRow - cRow_Home) + 1 ][0])) {
				do {
					++cRow;
				} while(!(s[ (cRow - cRow_Home) ][0]));
			} else 
				++cRow;

			dtioCursor(cRow,cCol);
			dtioPutchar(KEY_RIGHT_ARROW);
			dtioCursor(cRow,cCol);
			
		} else if (cursorMove == ENTER || cursorMove == ESCAPE) {

		/************************************************************/
		/*					write console screen                    */
		/************************************************************/

			#if PLATFORM == BCC32
			/******************** BCC32 *****************************/
				
				puttext(x1, y1, x2, y2, buffer);
				free(buffer);

			#elif PLATFORM == VSNET2K3
			/****************** VSNET2K3 ****************************/
				
				WriteConsoleOutput(std_out, dimension, dimensionSize, dimensionOrigin, &screenRec);
				free(dimension);

			#else
			/************ AIX and GCC LINUX *************************/

				i = 0;
				for (x1 = 0; x1 < depth; x1++) 
					for (y1 = 0; y1 < width; y1++) {
						move(x1,y1);
						addch(screen[i++]);
					}
				free(screen);		

			#endif

			exit = 1;
			if (cursorMove == ESCAPE)
				cRow = -1;

		}
	} while (!exit);

	return (cursorMove != ESCAPE) ? (cRow - row) : cRow;
}