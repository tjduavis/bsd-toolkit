 /* String Input Function
 *  getstr.c
 *  BTP100
 *  Nov 10 2004
 */

 #define MAX 30
 #include <stdio.h>

 void getstr( char s[], int max);

 int main ( void ) {
     char string[MAX+1];

     do {
	 printf("Enter a string (empty to quit) : ");
	 getstr(string, MAX);
	 printf("You entered ==>%s<==\n", string);
     } while (string[0] != '\n');

     return 0;
 }

 /* getstr accepts a newline terminated string s of up
 *  to max characters, appends a null byte and throws
 *  away the terminating character
 */
 void getstr(char s[], int max) {
     int i, c;

     i = 0;
     while((c= getchar()) != '\n' && c != EOF)
	 if (i < max)
	     s[i++] = (char) c;
     s[i] = '\0';
 }
