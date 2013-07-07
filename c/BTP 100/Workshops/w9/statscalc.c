/*
* Workshop 8
*  Statistics Calculator
*  statsCalc.c
*
* Last Modified: Nov 21,2004
* Programmer: Timothy Duavis
*/

#include<stdio.h>
#include<math.h>

#define MAX 100
#define FILEMAX 31

int main(void)
{
	FILE *fp=NULL;
	float value[MAX];		/*float array holder for values reading from source file*/
	char filename[FILEMAX];		/*user defines file to open*/
	int endChk;
	int i=0;	
	int j=0;
	float mean=0;
	float sum_Squares=0;
	double deviation=0;			

	printf("Statistics Calculator\n");
	printf("=====================\n");
	printf("Enter the name of the data file : ");
	scanf("%30[^\n]",filename);

	printf("%s\n",filename);
	getchar();

	fp=fopen(filename,"r");
	if(fp!=NULL)
	{
		do
		{
			endChk=fscanf(fp,"%f\n",value[i]);
			i++;
		}while(endChk!=EOF);
		
		for(j=0; j<i; j++)
		{
			mean+=value[j]/(i-1);
			
			sum_Squares+=(value[j] * value[j]);
		}

		deviation=(sum_Squares/(i-1))- (mean * mean);
		deviation=sqrt(deviation);

		printf("The number of data values read from this file was %d\n",i-1);
		printf("Their statistical mean is %f\n",mean);
		printf("Their standard deviation is %lf\n",deviation);
	}
	else
		printf("ERROR Encountered in I/O of file\n");

	fclose(fp);

	return 0;
}								
