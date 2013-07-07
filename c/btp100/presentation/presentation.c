#include<stdio.h>

#define DECK 13

int generator(int, int, int []);

 int main (void) 
 {
	 int i, n, choice, a = 1, b = 13;
	 int dealer_mask[DECK]={0,0,0,0,0,0,0,0,0,0,0,0,0};

	 do
	 {
		 printf("Enter 1 to generate a random number or -1 to exit : ");
		 scanf("%d",&choice);
		 switch(choice)
		 {
		 case 1:
             n = generator(a,b,dealer_mask);
			 printf("Random number is : %d\n",n);
			 break;
		 case -1:
			 choice = -1;
			 break;
		 default:
			 printf("Error\n");
		 }
	 }while(choice != -1);
	 
	 return 0;
 }

 int generator(int x, int y, int dealer_mask[])
 {
     int z, repeat=0;

     do
	 {
		 z = x + rand() % (y + 1 - x);
		 
		 /* adds ups to 5 */
		 dealer_mask[z]+=1;
		 
		 /* if it adds up to 5, then card has been taken */
		 /* repeat random generator to find different card */
		 if(dealer_mask[z]>=5)
			 repeat=1;
		 else 
			 repeat=0;

		 printf("dealer_mask[%d] = %d\n", z, dealer_mask[z]);

	 }while(repeat != 0);

	 return z;
 }