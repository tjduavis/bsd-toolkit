/*
*  Workshop 8
*  Last Modified: Nov 17,04
*  Programmer: Timothy Duavis
*/

#include<stdio.h>

#define MAX 31

int WordCount(char word[],int x);

int main(void)
{
char text[MAX];
int i;

printf("Word Counter\n");
printf("============\n");
printf("String to be counted : ");
scanf("%[^\n]",text);

i=WordCount(text,MAX);

printf("Number of words in the string : %d\n",i);

return 0;
}

/*
*  Workshop 8 - WordCount
*  WordCount
*  wordcount.c
*       Function that receives a null terminated string of text and
*       returns the number of words contained in the string.  Consider
*       a word to be any sequence of non-whitespace characters.
*       (cited from btp100 website)
*
*  Last Modified: Nov 15,04
*  Programmer: Timothy Duavis
*/

int WordCount(char word[], int x)
{
	int num_words=0;
	int i,j;
	int whitespace,character,chk;

/*searches entire array*/
	for(i=0; i<x; i++)
	{
		chk=(int)word[i];
		whitespace=(int)word[i+1];         /*converts into ascii collating sequence*/
		character=(int)word[i];

/*ignoring #127 in ascii collating sequence*/
		if(chk!=127)
		{
			if(character>=33 && whitespace<33)
			num_words++;
		}

	}

	return num_words;
}
