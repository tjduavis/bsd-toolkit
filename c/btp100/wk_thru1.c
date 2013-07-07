 /* compu_4.c
    Chris Szalwinski
    Sep 23 2003
 */

 #define C 14
 #define P 10
 #define R 6

 main ( ) {
     long long i = 74724183943651LL;
     int d, j = 1, k = 9;
     double x = 0.0;

     while ( i > 0 ) {
	 d = i % 10;
	 switch ( j ) {
	 case C:
	     printf("The company name is %d\n", k);
	     break;
	 case P:
	     printf("The product number is %d\n", k);
	     k = 0;
	     break;
	 case R:
	     k = 0;
	 }
	 if ( j < 6 )
	     x = 10.0 * x + (double) d;
	 else
	     k = 10 * k + d;
	 i /= 10;
	 j++;
    }
    printf("The price is $%.2lf\n", x / 100 );

}
