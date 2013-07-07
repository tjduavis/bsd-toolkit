 /* funct_5.c
 *  Chris Szalwinski
 *  Feb 24 2004
 *  BTP100
 */

 #define TIMES 3
 #define SETS  4
 #define COLOR 1

 #include <stdio.h>
 int control(int color, int times, int nsets);

 int main() {
     int color;

     color = COLOR;
     printf("%d\n", control(color, TIMES, SETS));
     printf("%d\n", color);

     return 0;
 }

 int control(int color, int times, int nsets) {
     int sec, set;

     if (color < 0 || color > 2)
         color = 0;
     sec = 0;
     set = 0;
     printf("%d,%d,%d\n", color, times, nsets);
     while ( set < nsets ) {
         switch ( color ) {
         case 0:
             printf("G ");
             sec = sec + 1;
             break;
         case 1:
             printf("Y ");
             sec = sec + times;
             break;
         case 2:
             printf("R ");
             sec = sec + 1;
             break;
         default:
             printf("O ");
             sec = sec + 1;
         }
         if (color != 0 || sec % times == 0)
             printf("Wt ");
         else
             printf("Wk ");
         if (sec % times == 0) {
             printf("(%d,%d)\n", sec, set);
             set = set + 1;
             if (color == 2) {
                 sec = 0;
                 color = 0;
             } else
                 color = color + 1;
         }
     }

     return color;
 }
