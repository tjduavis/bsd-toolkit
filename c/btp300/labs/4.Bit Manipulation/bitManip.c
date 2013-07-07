/* Workshop 3 - Bit Manipulation
 *  FILE: bitManip.c
 *  DESCRIPTION:
 *  AUTHOR:
 *  LAST MODIFIED:
 */

#include <stdio.h>
#include <limits.h>

void displayBits(unsigned);

int main(void) {
	unsigned x = 12;
    signed i;
    printf("x = %d\n",x);
	for (i = sizeof(unsigned) * CHAR_BIT - 1; i >= 0; i--) {
		/*printf("i = %d || ",i);
		printf("%d >> %d = %d || ",x,i, x >> i);
		printf("%d >> %d = %d & 1U %d || ",x,i, x >> i,x >> i & 1U);*/
		if (x >> i & 1U == 1)
			printf("1");
		else 
			printf("0");
			
		if (!(i % CHAR_BIT))
			printf(" ");
	}
	/* for (i = sizeof(unsigned) * CHAR_BIT - 1; i >= 0; i--) */
		
	
    /*displayBits(0);
    displayBits(1);
    displayBits(-1);
    displayBits(2000000000);
    displayBits(-2000000000);*/

    return 0;
}

/*void displayBits(unsigned x) {

}*/
