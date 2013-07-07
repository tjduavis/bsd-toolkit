/*
*Macro - Workshop1
*September 10,2005
*Author: Timothy Duavis
*functionSwap.c
*/

#include <stdio.h>
#include <time.h>

void swapF(int a,int b,int c) {a=b; b=c; c=a;}
void swapF2(double d, double e, double f) {d=e; e=f; f=d;}

#define NUM_CYCLE 10000000

int main(void)
{
	int x=1, y=2, z=3;
	int i;
	double xd=1.463257, yd=2.34652, zd=3.734621;
	clock_t t0, t1;
	
	printf("File functionSwap.c\n");

	t0 = clock();
	for(i=0; i<NUM_CYCLE; i++){
        	swapF(x,y,z);
	}
	t1 = clock();

	printf("Process time is %.3lf\n",(double)(t1-t0)/CLOCKS_PER_SEC);
	
	t0 =  clock();
	for(i=0; i<NUM_CYCLE; i++){
		swapF2(xd, yd, zd);
	}
	t1 = clock();
    
	printf("Process time is %.3lf\n",(double)(t1-t0)/CLOCKS_PER_SEC);
		
	return 0;
}
