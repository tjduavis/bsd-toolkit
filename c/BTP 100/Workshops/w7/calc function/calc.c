/*
*  Workshop 7 - Assets	
*  calc function
*	calculates the price and quantity and totals the value.
*/

void calc(value[], price[], quantity[],float total, int x, int j)
{
	for(j=0; j<x; j++)
	{
		printf("chk1\n");
		value[j]=price[j]*quantity[j];	
	}	

	for(j=0; j<x; j++)
	{
		printf("chk2\n");
		total+=value[j];
	}		
}