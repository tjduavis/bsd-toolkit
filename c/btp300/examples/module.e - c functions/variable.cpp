/* Variable Parameter Lists - Handout
 * variable.cpp
 * BTP300
 * Oct 3 2005
 */

#include <stdio.h>
#include <stdarg.h>

void printi(int &, ...);

int main (void) {
    int n;
    n = 6;
	
    printf("n in main: %d\n",&n);
    printi(n, 1, 2, 3, 4, 5, 6); 
    
    n = 3;
    printf("n in main: %d\n",&n);
    printi(n, 7, 8, 9); 

    return 0;
}

void printi (int &n, ...) {
	int i = 0;
	int parameter;
	int retrieve = 1;
	
	/*va_list nptr;
	va_start(nptr,n);*/
	
	printf("%d\n",&n);
	printf("%d\n",n);
	//printf("%d\n",*n);
	
	/*printf("List of Values:\n");
	for (i = 0; i < *n; i++) {
		parameter = va_arg(nptr,int);
		printf("%d: %d\n",i+1,parameter);
	}
	
	va_end(nptr);*/
}