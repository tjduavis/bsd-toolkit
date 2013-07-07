/* Simple Validation
*  valid.c
*  Oct 12 2004
*  BTP100
*/

#include <stdio.h>
int get(int min, int max);
#define MIN 0
#define MAX 999

int main(void) {
	int value;

/*        scanf("%d", &value);*/
	value = get(MIN,MAX);
	printf("The value is : %d\n", value);

	return 0;
}

int get(int min, int max) {
	char after;
	int ok, value;

	do {
	   ok = 0;
	   scanf("%d%c", &value, &after);
	   if (after != '\n')
		printf("Trailing characters\n");
	   else if (value < min)
		printf("Value must be >= %d\n", min);
	   else if (value > max)
		printf("Value must be <= %d\n", max);
	   else
		ok = 1;
	} while (ok == 0);

	return value;
}
