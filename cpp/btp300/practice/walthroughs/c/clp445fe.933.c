	     #include <stdio.h>
	     #include <string.h>
	     void init(char s[][10])
	     {
		 strcpy(s[0], "aXYasZab!");
		 strcpy(s[1], "CnIps?Mye");
	     }
	     int foo1(char s[][10], int row, int col)
	     {
		 char c;
		 c = s[row][col];
		 putchar( ((c >= 'X') && (c <= 'Z')) ? ' ' : c);
	     }
	     main()
	     {
		 char data[2][10];
		 int i;
		 init(data);
		 for (i = 0; i < 10; i++) {
		     foo1(data, 1, i);
		     foo1(data, 0, i);
		 }
	     }