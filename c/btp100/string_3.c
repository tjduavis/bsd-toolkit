 /* string_3.c
    Danny Abesdris
    November 22 2002
 */

 #include <stdio.h>
 #include <string.h>

 void readln(FILE *, char [ ]);
 void extract(char [ ], char [ ], int);
 void change(char [ ]);

 int main( ) {
    char buf[51], temp[10], fname[11] = "data.txt";
    FILE *fp;
    int i, j=0, line[5] = {2,3,4,5,8}, pos[5] = {16,9,8,26,1};

    fp = fopen(fname, "r"); /* assume file opened successfully! */
    for(i=0; i<10; i++) {
      readln(fp, buf);
      if(j<5 && i == line[j]) {
	extract(temp, buf, pos[j]);
	j++;
	if(i>3 && i<6) {
	  change(temp);
	}
      }
    }
    fclose(fp);
    return 0;
 }

 void readln(FILE *fp, char buf[ ]) {
    fgets(buf, 51, fp);  /* reads an entire line from the file */
 }                       /* and stores it in array 'buf'       */

 void extract(char temp[ ], char buf[ ], int x) {
    int i, j=0;
    for(i=x; buf[i] != ' '; i++) {
      temp[j] = buf[i];
      printf("%c", temp[j]);
      j++;
    }
    temp[j] = '\0';
    printf("\n");
 }

 void change(char s[ ]) {
    s[0] -= 32;          /* recall what -32 does to a character */
    printf("%s\n", s);
 }
