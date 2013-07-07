/* Class Problem
*  raise an integer to a power of an integer
*  BTP100
*  Sept 28 2004
*  raiseToPower.c
*/

 #include <stdio.h>
 #include "raiseToPower.h"
 void clear(void);

 int main () {
     int base, exp, answer;

     base = getInt(-LIMIT,LIMIT);
     exp = getInt(0,LIMIT);
     answer = power ( base, exp );
     printf("%d^%d is %d\n", base, exp, answer);

     return 0;
 }

 /* getInt prompts for and accepts an int
 *  in the range [min, max] from the user
 */
 int getInt(int min, int max) {
     char c;
     int ok, rc, value;

     do {
	 ok = 0;
	 printf("Enter an integer : ");
	 rc = scanf("%d%c", &value, &c);
	 if (rc != 2) {
	     clear();
	     printf("Invalid input!  Try again!\n");
	 } else if (c != '\n') {
	     clear();
	     printf("Trailing characters! Try again!\n");
	 } else if (value < min || value > max) {
	     printf("%d is outside bounds [%d,%d]."
		    "  Try again!\n",
		    value, min, max);
	 } else
	     ok = 1;
     } while (ok == 0);

     return value;
 }                   

 /* clear clears the input stream of all characters */
 void clear(void) {
     char c;

     do {
	 scanf("%c", &c);
     } while(c !='\n');
 }

 /* power returns the value of base raised to
 *  the power of exponent (base^exponent)
 *  no checks are made to ensure that the
 *  exponent is non-negative
 */
 int power ( int base, int exponent ) {
     int result, i;

     result = 1;
     for (i = 1; i <= exponent; i++)
	 result = result * base;

     return result;
 }
