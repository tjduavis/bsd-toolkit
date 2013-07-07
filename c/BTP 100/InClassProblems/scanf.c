/* Working with Input
*  scanf.c
*  Oct 6 2004
*  BTP100A
*/

#include <stdio.h>
void clear(void);

int main(void) {
	short hours, minutes;
	int i;
	char c;
	int rc;

	i = getchar();
	if (i == EOF){
		/* code for special case */
	} else {
		c = (char) i;
	printf("Enter the time in HH:mm format : ");
	rc = scanf("%hd:%hd", &hours, &minutes);
	if (rc == 2)
		printf("You input %hd:%hd\n", hours, minutes);
	else if (rc == 1) {
		clear();
		printf("Enter the minutes : ");
		scanf("%hd", &minutes);
	} else if (rc == 0) {
		clear();
		printf("Enter the time in HH:mm format : ");
		rc = scanf("%hd:%hd", &hours, &minutes);
	} else
		printf("End of data\n");

	printf("You input %hd:%hd\n", hours, minutes);
	}
	return 0;
}

/* clears the input buffer */
void clear(void) {
	while(getchar() != '\n')
		;
}
