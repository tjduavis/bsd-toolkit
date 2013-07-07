/*
* BTP100a
* Workshop 4: Table of Primes
*
* -Prime number verifier function
*
* Programmer: Timothy Duavis
* Date Modified: Oct 5/2004
*/

#include<stdio.h>
#define PLUS_ONE 2

int main(void)
{
        int count,num,checker,test,initial=0;

        printf("prime number verifier function\n");
        scanf("%d",&num);

	if(num<3)
		printf("%d is not a prime number\n",num);
	else
	{

        	initial=num-(num-PLUS_ONE);

        	for(count=initial;count<num;count++)
        	{
                	printf("%d",count);
                	checker=num%count;
                	if(checker==0)
                       		test=1;
               		printf("z:%d, a:%d\n",checker,test);  
       		}

        	if(test==1)
                	printf("%d is not a prime number\n",num);
        	else
                	printf("%d is a prime number\n",num);

	}
        return 0;
}


