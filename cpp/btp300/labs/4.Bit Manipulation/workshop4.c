/* Workshop 4 - Bit Manipulation
 *  FILE: workshop4.c
 *  DESCRIPTION: Converts decimal to binary using bit manipulations
 *  AUTHOR: Timothy Duavis
 *  LAST MODIFIED: October 12, 2005
 */

#include <stdio.h>
#include <limits.h>

void displayBits(unsigned);

int main(void) {
	
	displayBits(0);
    displayBits(1);
    displayBits(-1);
    displayBits(2000000000);
    displayBits(-2000000000);

    return 0;
}

void displayBits(unsigned x) {
	signed i;
	
	for (i = sizeof(unsigned) * CHAR_BIT - 1; i >= 0; i--) {
		if (x >> i & 1U == 1)
			printf("1");
		else
			printf("0");
		
		if (!(i % CHAR_BIT))
			printf(" ");
	}
	printf("\n");
}		