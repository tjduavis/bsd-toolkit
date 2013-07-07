/*
* Validation Exercise
* validation.c
* TJ Duavis
* Oct 9,2004
*
* -solve EOF input (valid=-1)
* -solve implentation of loop
*/

#include<stdio.h>

int main(void)
{
	double input; 
	int valid, flag=0; 
	char endChk;	

	do{
	
		printf("Enter a input value:");
		valid=scanf("%lf%c",&input,&endChk);
		
		if(valid==0)
		{
			printf("Error\n");
			while(getchar()!='\n')
			{
				;
			}
		}
		else if(endChk!='\n')
		{
			printf("Trailing characters\n");
			while(getchar()!='\n')
			{
				;
			}
		}
		else if(input<0)
		{
			printf("Input value must be non-negative\n");
		}
		else if(valid==2)
		{
			printf("Input value is: %lf\n",input);
			flag=1;
		}		
		/*else if(valid==(-1))
			printf("End of FIle");*/

	}while(flag!=1);
	printf("valid: %d\n",valid);
	printf("End\n");

	return 0;
}