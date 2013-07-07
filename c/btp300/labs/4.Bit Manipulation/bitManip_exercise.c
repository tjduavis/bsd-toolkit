/*
 * bitManip_exercise
 */
 
#include <stdio.h>
#include <limits.h>

int main(void) {
	unsigned i;
	
	printf("size of unsigned i 					: %d\n",sizeof(i));
	printf("size of unsigned  					: %d\n",sizeof(unsigned));
	printf("size of signed    					: %d\n",sizeof(signed));
	printf("CHAR_BIT        					: %d\n",CHAR_BIT);
	printf("sizeof(unsigned) * CHAR_BIT         : %d\n",sizeof(unsigned) * CHAR_BIT);
	printf("\n");
	printf("27 << 0 = %d && 27 * 1 = %d\n",27 << 0, 27 * 1);
	printf("27 << 1 = %d && 27 * 2 = %d\n",27 << 1, 27 * 2);
	printf("27 << 2 = %d && 27 * 4 = %d\n",27 << 2, 27 * 4);
	printf("\n");
	printf("27 >> 0 = %d && 27 / 1 = %d\n",27 >> 0, 27 / 1);
	printf("27 >> 1 = %d && 27 / 2 = %d\n",27 >> 1, 27 / 2);
	printf("27 >> 2 = %d && 27 / 4 = %d\n",27 >> 2, 27 / 4);
	return 0;
}
void displayBits(unsigned num) {
        signed i;
        for (i = sizeof(unsigned) * CHAR_BIT - 1; i >= 0; i--) {
                        /* shift over i places and if the last digit is a one, puts a one
                         *  on the screen */
                        if (num>>i  1U& == 1)
                                printf("1");
                        else printf("0");
                /* Puts a space every byte */
                if (!(i%CHAR_BIT))
                        printf(" ");
        }
        printf("\n");