/* binary hexadecimal representations */
/* C:\Documents and Settings\TJ Duavis\My Documents\BSD\sem3\btp300\practice.wordploblems\ */
/* bin_hex.c */

#include <stdio.h>

int main(void) {
	int *p = NULL;
	int x = 32769;
	p = &x;
	
	printf("p + 1 = %d\n", &p);
	
	printf("%x\n",x);
	
	return 0;
}