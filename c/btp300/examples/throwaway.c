/* throwing away in scanf */
/* throwaway.c */
/* C:\Documents and Settings\TJ Duavis\My Documents\BSD\sem3\btp300\examples\ */

#include <stdio.h>

int main(void) {
	int x;
	int status;
	char newline;

	status = scanf("%d%c",&x,&newline);
	if (newline == '\n')
		printf("|%d|\n",x);
	printf("status %d\n",status);
	
	return 0;
}