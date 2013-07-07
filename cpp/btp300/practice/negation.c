 /* Bitwise Expressions - Logical and
  * and.c
  * BTP300
  * Sep 28 2005
  */

 #include <stdio.h>

 int main (void) {
     unsigned u = 27u;  /* 0...00011011 */
     unsigned v = 14u;  /* 0...00001110 */

     printf("%u & %u = %u\n", u, v, u & v); 

     return 0;
 }
