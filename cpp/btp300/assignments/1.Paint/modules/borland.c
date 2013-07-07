/* Borland Console Functions 
* 
* borland.c
* Author: Timothy Duavis
* Last Updated: Sept 22/2005
*/

#include <stdio.h>
#include <conio.h>

int main(void) {
	int row, col;
	
	clrscr();
	cprintf("Enter x value to move cursor to x coordinate: ");
	cscanf("%d",&row);
	clrscr();
	cprintf("Enter y value to move cursor to y coordinate: ");
	cscanf("%d",&col);
	clrscr();
	getch();
	gotoxy(row + 1,col + 1);
	getch();
	
	return 0;
}