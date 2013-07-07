/* assigment 2 test main */

#include "dtio.h"
#include <Windows.h>

void cls( HANDLE hConsole );

int main(void) {
	HANDLE std_out;
	
	/*char str[] = "a2 test";*/
	char str[27] = "abcdefghijklmnopqrstuvwxyz";
	char *choices[] = { "Add", "Change", "Delete", "", "Quit" },
		  box[] = { '_', '_', '_', '|', '+', '-', '+', '|' };
	/*char mock = "";*/
	int r = 0;
	int c = 0;
	int l = 8;
	int index = 0;
	int key;
	
	std_out = GetStdHandle(STD_OUTPUT_HANDLE);	
	
	dtioStart();
	/*dtioDisplay("abcdefghijklmnopqrstuvwxyz", 12, 5, 0);*/
	/*dtioDisplay(const char *, int, int, int);*/
	/*dtioEdit(str, r, c, l, &index); */
	key = dtioEdit(str, 14, 5, 27, &index);
	getch();
	cls(std_out);
	dtioPuts(str);
	printf("\n\n%s length %d\n",str, strlen(str));
	/*cputs("*****Test******\n");*/ 
	getch();
	/*printf("choices[3][0]: %d\n",choices[3][0]);
	if (choices[3][0] == (char)0)*/
		/*dtioMenu(choices, 5, 0, 0, box);*/
	/*else
		printf("find a solution");
	getch();*/
	
	dtioStop();
	
	return 0;
}

void cls( HANDLE hConsole )
{
   COORD coordScreen = { 0, 0 };    // home for the cursor 
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi; 
   DWORD dwConSize;

// Get the number of character cells in the current buffer. 

   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
      return;
   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   // Fill the entire screen with blanks.

   if( !FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
      dwConSize, coordScreen, &cCharsWritten ))
      return;

   // Get the current text attribute.

   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
      return;

   // Set the buffer's attributes accordingly.

   if( !FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten ))
      return;

   // Put the cursor at its home coordinates.

   SetConsoleCursorPosition( hConsole, coordScreen );
}
