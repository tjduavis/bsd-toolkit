/*
* BTP100a
* Workshop 4: Table of Primes
*
* -main function
*
* Programmer: Timothy Duavis
* Date Modified: Oct 17/2004
*/

#include<stdio.h>
#define PLUS_ONE 2

int primeNum(int);

int main(void)
{
	int min, max, col, col_limit, row, set_col=0;
	int chk_num,value,reset,holder;

	printf ("Enter the lower limit:");
	scanf ("%d",&min);
	printf ("Enter the upper limit:");
	scanf ("%d",&max);
	printf ("Enter the number of columns:");
	scanf ("%d",&col);
	printf("\n");

	chk_num=min;

	while(chk_num<max)
	{
		while(set_col<col && chk_num<max)
		{
			value=primeNum(chk_num);
			
			if(value>0)
			{
				printf("\t%d",value);
				set_col=set_col+1;
				chk_num=chk_num+1;
			}
			else
			{
				chk_num=chk_num+1;
			}
		}
		set_col=0;
		printf("\n");	
	}

	return 0; 
}

int primeNum(int num)
{
	int count,remainder,test=0;

	if(num<2 && num>=0)
		num=0;
	else
	{
		for(count=(num-(num-PLUS_ONE));count<num;count++)
		{
			remainder=num%count;
			if(remainder==0)
			       test=1;
		}

		if(test==1)
			num=0;
		
	}
	return num;
}

