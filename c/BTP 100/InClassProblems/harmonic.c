/* Harmonic Numbers
*  Practice Problems
*  harmonic.c
*  Oct 12 2004
*  BTP100a
*/

#include <stdio.h>

int main(void) {
	int i, nterms;
	double h;

	printf("Enter the number of terms : ");
	scanf("%d", &nterms);

	h = 0;                            /* initialize h */
	for (i = 1; i <= nterms; i++) {
		h = h + 1/(double)i;      /* or use 1.0/i */
	}

	printf("The value of h for %d terms is %lf\n", nterms, h);

	return 0;
}
