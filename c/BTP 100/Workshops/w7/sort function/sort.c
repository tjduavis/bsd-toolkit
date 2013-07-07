/*
*  Workshop 7 - Assets	
*  sort function
*	sorts barcode from ascending order.
*/

void sort(barcode[],int x, int j, long holder)
{
	for(j=0; j<x; j++)
	{	
		bufferClear();
		for(i=j+1; i<x; i++)
		{
			bufferClear();
			if(barcode[j]>barcode[i])
			{
				bufferClear();
				/*swap*/
				holder=barcode[j];
				barcode[j]=barcode[i];
				barcode[i]=holder;
			}
		}
	}
}	