#include <stdio.h>
#include <curses.h>

int main(void) {
	int disp = 0;
	printf("Welcome to the direct terminal IO program.\n");
	printf("To Begin type any characters to see the codes. To QUIT hit the ESC key.\n\n");
	
	initscr();
	disp = getch();
	printf("%d\n",disp);
	getch();
	refresh();
	endwin();
	 	
  	return 0;
}