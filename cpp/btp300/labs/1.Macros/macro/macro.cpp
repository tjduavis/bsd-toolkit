// macro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>

#define SWAP(a,b,c) a=b; b=c; c=a;
#define NUM_CYCLE 10000000

int main(void)
{
	int x=1, y=2, z=3;
	int i;
	clock_t t0, t1;
	
	t0 = clock();
	for(i=0; i<NUM_CYCLE; i++){
        SWAP(x,y,z);
	}
	t1 = clock();
    
	printf("Process time is %.3lf\n",(double)(t1-t0)/CLOCKS_PER_SEC);

	getchar();
	return 0;
}

