 /* Failing to swap with a function
 *  swap_1.c  (first attempt - faulty code)
 *  BTP100
 *  Chris Szalwinski
 *  Oct 5 2004
 */

 #include<stdio.h>
 void swap ( int *a, int *b );

 int main ( ) {
     int booksInLeftHand;
     int booksInRightHand;

     printf("Enter booksInLeftHand  : ");
     scanf("%d", &booksInLeftHand);
     printf("Enter booksInRightHand : ");
     scanf("%d", &booksInRightHand);
     printf("booksInLeftHand is at Address %p\n", &booksInLeftHand);
     swap( &booksInLeftHand, &booksInRightHand );

     printf("After swap:\n"
	    "booksInLeftHand  are %d\n"
	    "booksInRightHand are %d\n",
	    booksInLeftHand, booksInRightHand);

     return 0;
 }

 void swap ( int *a, int *b ) { /* DOESN'T WORK */
     int c;

     printf("a holds the address %p\n", a);
     printf("In swap a is %d, b is %d\n", *a, *b);

     c = *a;
     *a = *b;
     *b = c;

     printf("In swap a is %d, b is %d\n", *a, *b);
}
