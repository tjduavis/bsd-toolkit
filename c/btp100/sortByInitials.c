/* Sort
*  sortByInitials.c
*  BTP100
*  Dec 7 2004
*/
#include <stdio.h>
#include <string.h>
void sort(char s[][81], int n);

int main(void) {
	char str[500][81], temp1[81];
	FILE *fp = NULL;
	short n;
	int counter, i;

	fp = fopen("/home/cszalwin/btp100a/text.dat","r");
	if(fp != NULL){
		counter = 0;
		while(!feof(fp))
			fscanf(fp,"%[^\n]%*c", str[counter++]);
		sort(str, counter);
		for (i = 0; i < counter; i++)
			printf("%-80s\n", str[i]);
		fclose(fp);
	} else
		printf("File failed to open\n");
	return 0;
}

void sort(char str[][81], int n) {
	int i, j;
	char temp[81];

	for (i = n - 2; i >= 0; i--)
		for (j = 0; j < i; j++) {
			if(str[j][1]>str[j+1][1] || str[j][1]==str[j+1][1] && 
				str[j][0]>str[j+1][0] ) {
				strcpy(temp,str[j]);
				strcpy(str[j],str[j+1]);
				strcpy(str[j+1],temp);
			}
		}
     
}


