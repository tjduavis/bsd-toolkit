/* 5.  Write a function

		int bitoff(int value, int bitnumber)

		that returns the contents of  "value"  with  bit  number
		"bitnumber" turned off (i.e. set  to  zero),  where  bit
		number 0 is the lowest order (i.e. rightmost)  bit.  For
		example, bitoff(7,0) returns 6, bitoff(7,1)  returns  5,
		and bitoff(7, 5) returns 7.

		Hint: One way to do this is  to  slide  1  to  the  left
		"bitnumber" bits, and then flip all the bits to create a
		mask for a bitwise and. */

#include <stdio.h>

int bitoff(int , int );

int main(void) {

	printf("%d\n",bitoff(7,0));
	printf("%d\n",bitoff(7,1));
	printf("%d\n",bitoff(7,5));
		
	return 0;
}

int bitoff(int value, int bitnumber) {
	int answer;
	answer = bitnumber + 1;
	
	return value & ~answer);
}