/*
* Difference between && statements
* Timothy Duavis
* andexpressions.c
* Oct, 13/04
*/

#include<stdio.h>

int main(void)
{
	int x=2, k=1;
	if(x>=4&&k)
		printf("option 1\n");
	else 
		printf("option 2\n");
	
	return 0;	
}
