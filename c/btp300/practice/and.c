 /* Bitwise Expressions - Logical and
  * and.c
  * BTP300
  * Sep 28 2005
  */

 #include <stdio.h>
 #include <limits.h>

 int main (void) {
     unsigned u = 27; 
     signed i; 
     unsigned v = 4; 
	 int j = sizeof(unsigned)*CHAR_BIT-1;
	 int x = sizeof(unsigned);
	 printf("sizeof(unsigned) = %u\n",x); 
	 printf("j = %d\n",j); 
     printf("remainder of %u from %u / 2 is %u\n", v,v,v & 1);
	 for ( i = j; i >= 0; i--) 
	 	printf("%u", u >> i & 1); 

	 printf("\n");
	 
	 for ( i = j; i >= 0; i--)
	 	printf("%u '%' %d = %u\n",i,CHAR_BIT,i%CHAR_BIT);
	 
     return 0;
 }

 /* Learning Outcome
  * v & 1 takes the remainder of v / 1+1 in binary format.
  */
  
/* Questions
 * what is the difference between v & n ( where n is any number) from v % n, since they find out the remaider?