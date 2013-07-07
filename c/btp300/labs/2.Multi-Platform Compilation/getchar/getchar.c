/* getchar program
* 
* FILE:    		 getchar.c
* AUTHOR:  		 Timothy Duavis
* LAST MODIFIED: Sept 15/2005 
* 
* DESCRIPTION: Program that tests the getchar function.
*/

#include <conio.h>
#include <stdio.h>

int main(void) {
	int x;
	int y;
	x = getch();
	/*while (getchar() != '\n'){
		
		;
	}*/
	y = getch();
	putch(getch());
	printf("\n%d::%d\n",x,y);
	/*printf("%s",stdout);*/
	/*flush(stdin);*/

	
	return 0;
}