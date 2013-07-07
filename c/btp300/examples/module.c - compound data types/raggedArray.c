 /* Ragged Arrays
  * raggedArray.c
  * BTP300
  * Sep 21 2005
  */

 #include <stdio.h>

 int main (void) {
     int i;
     char *name[] = {"Marg", "Jeremy", "Christopher", "Homer"}; 
     char name2[] = {"Marg2"};
     int id[] = {1456,2346,56789,432};
     int *id2[] = {1456,2346,56789,432};
     
     for (i = 0; i < 4; i++)
         printf("%p %p %s\n", &name[i], &name[i][0], name[i]);
     putchar('\n');
     
     printf("%p %p %s\n", &name[0], &name[0][0], name[0]);
     putchar('\n');
     putchar('\n');
     
     printf("sizeof id[] = %d\n",sizeof(id));
     printf("size of int = %d\n\n",sizeof(int));
     printf("therefore there are %d elements in id array of ints\n\n",sizeof(id) / sizeof(int));
     
     printf("id[0] = %d\n",id[0]);
     printf("id[1] = %d\n",id[1]);
     printf("id[2] = %d\n",id[2]);
     
     putchar('\n');
     putchar('\n');

     printf("id2[0][0] = %d\n",&id2[0][1]);
     printf("id2[1][0] = %d\n",&id2[1][1]);
     printf("id2[2][0] = %d\n",&id2[2][1]);     
     
     return 0;
 }
