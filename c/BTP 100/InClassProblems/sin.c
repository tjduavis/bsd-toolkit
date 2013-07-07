/* sine function
*  Practice Problems
*  sin.c
*  Oct 15 2004
*  BTP100a
*/

#include <stdio.h>
#include <math.h>
double my_sin(double x, int nterms);

int main(void) {
	double x;
	int nterms;

	printf("Enter number of terms : ");
	scanf("%d", &nterms);
	printf("Enter value of x : ");
	scanf("%lf", &x);

	printf("my_sin(x) is about %18.15lf\n", my_sin(x,nterms));
	printf("math.h value is    %18.15lf\n", sin(x));

	return 0;
}

/* my_sin returns the approximate value of sin(x)
*  based on a series expansion of nterms
*/
double my_sin(double x, int nterms) {
	int i, sign;
	double result, term;

	term = x;
	sign = 1;
	i = 1;
	result = 0;
	while (nterms > 0) {
		result += sign * term;
		nterms--;
		/* updates for next term */
		term = term * ( x / (i + 1) ) * ( x  / (i + 2) ); 
		i += 2;
		sign = -sign; 
	}
	return result;
}
