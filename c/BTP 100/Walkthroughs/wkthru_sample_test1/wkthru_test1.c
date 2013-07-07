#include <stdio.h>
#define MIN 3
#define MAX 6
int pRbar ( double area, int *size, int *no );

int main(void) {
	int s, n, i;
	double area, cc;

	area = 25.00;
	while ( area <= 115.00) {
		i = pRbar ( area, &s, &n );
		if ( i == 1 )
			printf("To get %.0lf, use %d-#%d\n", area, n, s );
		else
			printf("No match found\n");
		area += 15.00;
	}
	return 0;
}
int pRbar ( double area, int *size, int *no ) {
	int i, j, k;
	double a;

	k = 1;
	for ( j = MIN; j <= MAX && k; j++ ) {
		for ( i = 1; i <= 4 && k; i++ ) {
			switch ( i ) {
			case 1:
				a = 7.50;
				break;
			case 2:
				a = 11.50;
				break;
			case 3:
				a = 15.25;
				break;
			case 4:
				a = 19.05;
				break;
			}
			if (a * j >= area) {
				k = 0;
				*size = i;
				*no = j;
			}
		}
	}
	printf("(%d-#%d %5.2lf)\n", j-1, i-1, a);
	return !k;
}
