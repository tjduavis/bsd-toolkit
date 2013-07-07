 /* Macro Efficiency
  * BTP300
  * Sep 7 2005
  * macroEff.cpp
  */

 #include <time.h>
 #include <stdio.h>
 #define PRODUCT(x,y) (x)*(y)
 #define NITER 1000000

 int main (void) {
     double x;
     int i;
     clock_t c0, c1;

     x = 1;
     c0 = clock();
     for (i = 0; i < NITER; i++)
         x = PRODUCT(x, 1.0000000001); 
     c1 = clock();

     printf("Process time is %.3lf secs\n",
            (double)(c1-c0)/CLOCKS_PER_SEC); 
     printf("Value of x is %.10lf\n", x);

     return 0;
 }
