/*
* BTP100a
* Workshop 4: Table of Primes
*
* -main function
*
* Programmer: Timothy Duavis
* Date Modified: Oct 5/2004
*/

#include<stdio.h>
#define PLUS_ONE 2

int main()
{
	int num=3;
	int count,remainder,test;
	if(num==1)
		return 0;
	else
	{
		for(count=(num-(num-PLUS_ONE));count<num;count++)
		{
			printf("%d",count);
			remainder=num%count;
			
			if(remainder==0)
			       test=1;
			 /*printf("z:%d, a:%d\n",remainder,test);*/
		 }

		 if(test!=1)
			return num;
	}
}