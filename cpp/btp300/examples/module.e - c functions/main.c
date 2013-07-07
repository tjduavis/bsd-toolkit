 /* main Function Parameters
  * main.c
  * BTP300
  * Oct 3 2005
  */

 #include <stdio.h>

 int main (int argc, char *argv[]) {
     int i;

     printf("Course : %s\n", argv[0]);
     for (i = 1; i < argc; i++)
         printf("- %s\n", argv[i]);

     return 0;
 }
