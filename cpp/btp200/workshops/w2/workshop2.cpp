/*
* Workshop 2
*   Title: Fraction Simplifier
*   filename: fraction.cpp
*   purpose:
*       A simple program, using a struct that holds int variables
*       of numerator and denominator of a fraction, and simplifies
*       the fraction to the lowest common denominator.
*   last modified date: Jan 23/05
*   author: Timothy Duavis
*/

struct Fraction 
{
	int numtr;              //numerator
	int denomtr;            //denominator
};

#include <cstdio>
#include <iostream>
using namespace std;

struct simplify(Fraction toSimplify);

int main(void)
{
	struct Fraction get;

	/* heading */
	printf("Fraction Simplifier\n");
	printf("===================\n");

	/* user input */
	printf("Numerator:\t");
	scanf("%d",&get.numtr);
	printf("Denominator:\t");
	scanf("%d",&get.denomtr);

	/* user input display */
	printf("%d / %d = ",get.numtr, get.denomtr);

	/* load into simplify function */
	get = simplify(get);

	/* simplified display */
	printf("%d / %d\n",get.numtr, get.denomtr);

	return 0;
}

/*
* Simplify
*   purpose: Simplifies numerator and denominator.
*   date: Jan 21/05
*   author: Timothy Duavis
*/

struct simplify(Fraction toSimplify)
{                 
	int simple;
	int holder;     //holder variable for numerator or denominator
	int j,i;        //function flags

	/* loops twice for each variable in stuct */
	for(j=0; j<2; j++)
	{
		switch(j)
		{
			case 0:
				holder = toSimplify.numtr;
				break;
			case 1:
				holder = toSimplify.denomtr;
				break;
		}

		/* do-while loop for simplifying */
		do
		{
			simple = holder % 2;
			if ( simple == 0 )
			{
				i = 1;
				holder = holder / 2;
			}
			else
			/* value cannot be simplified */
				i = 0;
		}while(i!=1);

		/* returning holder to correct fraction position */
		if(j==0)
			toSimplify.numtr = holder;
		else
			toSimplify.denomtr = holder;
	}

	return toSimplify;
}
