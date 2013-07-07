 /* Working with Doubles - Rounding Doubles
 *  BTP100 - Workshop 2
 *  Week 2
 *  rounding.c
 *
 *  test data: 12.3, 12.7, -12.3, -12.7
 */

 main() {

     double value, remainder;
     int truncated, rounded;

     printf("Enter a value : ");
     scanf("%lf", &value);

     truncated = value;
     remainder = value - truncated;
     rounded = value;

     printf("Value     : %10.2lf\n", value);
     printf("Truncated : %7d\n", truncated);
     printf("Remainder : %10.2lf\n", remainder);
     printf("Rounded   : %7d\n", rounded);

     return 0;
 }
