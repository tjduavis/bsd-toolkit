/* Natural logarithm of 2
*  Practice Problems
*  ln2.c
*  Oct 12 2004
*  BTP100a
*/

#include <stdio.h>

int main(void) {
	int i, nterms, sign;
	double ln2;

	printf("Enter the number of terms : ");
	scanf("%d", &nterms);

	ln2 = 0;
	sign = 1;
	for (i = 1; i <= nterms; i++) {
		ln2 = ln2 + sign/(double)i;      /* or use 1.0/i */
		sign = -sign;
	}

	printf("The approximate value of ln2 using %d terms is %lf\n", 
		nterms, ln2);

	return 0;
}
