/* Playing with getchar()
*  getchar.c
*  Oct 8 2004
*  BTP100a
*/

#include <stdio.h>

int main(void) {
	char c;
	int i, quit;
	int value, total;

	total = 0;

	do {
		printf("Enter a value : ");
		scanf("%d", &value);
		total += value;

		printf("More values (y or n) ? ");
		getchar(); /* rid of \n */
		i = getchar();
		c = (char) i;
		if (i == EOF){
			quit = 1;
			putchar('\n');
		} else if (c == 'y' || c== 'Y')
			quit = 0;
		else if (c == 'n' || c == 'N')
			quit = 1;
		else {
			printf("Yes assumed\n");
			quit = 0;
		}
	} while (quit == 0);

	printf("The total is %d\n", total);

	return 0;
}

