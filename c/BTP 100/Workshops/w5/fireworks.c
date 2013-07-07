/*
* Workshop 5: Multiple Solutions
* Fireworks
* fireworks.c
*
* Programmer: TJ Duavis
* Date Modified: Oct 17/04
*/

#include<stdio.h>
#include<math.h>
#define G -9.8

int root(double h,double h_v, double *t1, double *t2);
double sigdig(double value);

int main(void)
{
	double height, h_velocity;
	int result;
	double time1, time2;			/*times 1 and 2*/

	printf("Initial horizontal velocity (m/sec):\t");
	scanf("%lf",&h_velocity);
	printf("Desired Height (m):\t");
	scanf("%lf",&height);

	result=root(height,h_velocity, &time1, &time2);

	printf("\n");

	switch(result)
	{
		case 1:
			printf("Your firework will reach the desired height a time of:\n");
			printf("%10.2lfs\n",time1);
			break;
		case 2:
			printf("Your firework will reach the desired height at times:\n");
			printf("%10.2lfs\n",time1);
			printf("%10.2lfs\n",time2);
			break;
		case 0:
			printf("There are no time(s) for the given height:\n");
			break;	
	}	
	return 0;
}

int root(double h,double h_v, double *t1, double *t2)
{
	double d;	/*d is the discriminant of the quadratic equation*/
	int realroot;

	d=(h_v)*(h_v)-(4)*(-(G/2))*(h);
	d=sqrt(d);	/*square root*/
	d=sigdig(d);
	*t1=-(h_v+d)/G;	/*root 1*/
	*t2=-(h_v-d)/G;	/*root 2*/
	
	if(d==0)
		realroot=1;
	else if(d>0)
		realroot=2;
	else
		realroot=0;

	return realroot;
}

double sigdig(double value)
{
	int truncated, remainder;
	double decimal;

	remainder=value;               	/*convert value into whole value*/
	decimal=value-remainder;       	/*get the decimal*/
	decimal*=1000000;		/*turn decimal into whole value*/
	truncated=decimal;		/*turn decimal value into integer value*/
	truncated/=1000;		/*truncate the decimal value by 3 decimal places*/
	decimal=(double)truncated/1000;	/*convert back into decimal*/
	value=remainder+decimal; 	/*new value to 3 decimal places*/

	return value;
}