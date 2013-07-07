/*
* Workshop 6: Simple Games
* Ball Lottery
* ball_lottery.c
*
* Programmer: TJ Duavis
* Date Modified: Oct 17/04
*/

#include<stdio.h>
#define LIMIT 10

int ball_Lottery(int sought);
int verifier(int chk);

int main(void)
{       int userinput,total;

	userinput=verifier(userinput);

	total=ball_Lottery(userinput);
	printf("You got your total in %d picks!\n",total);

	return 0;
}

int ball_Lottery(int sought)
{
	int p_1, p_2, result;
	int counter=1;

	srand(time(NULL));
	srand(time(NULL));
	do
	{
		p_1=rand()%LIMIT+1;
		p_2=rand()%LIMIT+1;

		result=p_1+p_2;
		printf("Result of %d and %d:%d + %d\n",counter, counter+1, p_1, p_2);
		counter++;

	}while(result!=sought);

	return counter;
}

int verifier(int chk)
{
	int valid,flag=0;
	char endChk;

	do
	{
		printf("Total sought:");
		valid=scanf("%d%c",&chk,&endChk);

		/*trailing character detected*/
		if(endChk!='\n')
		{
			printf("Trailing characters encountered.  Try again.\n");

			/*clears input buffer*/
			while(getchar()!='\n')
			{
				;/*null statement*/
			}
		}

		else if(chk>20)
			printf("Choice must be less than 20\n");
		else if(chk<0)
			printf("Must be non-negative.  Try again.\n");
		else if(valid==2)
			flag=1;

	}while(flag!=1);

	return chk;
}
