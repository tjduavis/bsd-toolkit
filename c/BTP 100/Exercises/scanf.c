/*
* Scanf Exercise
* scanf.c
* TJ Duavis
* Oct 8,2004
*/

#include<stdio.h>

int main(void)
{
	double input; 

	printf("Enter a input value:");
	scanf("%*lf%lf",&input);
	printf("Input value is: %lf\n",input);

	return 0;
}