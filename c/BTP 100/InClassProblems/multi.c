/* Multiplication Table
*  multi.c
*  BTP100a
*  Sep 21 2004
*/

main() {
	int column, row, nrows;

	printf("Enter the number of rows : ");
	scanf("%d", &nrows);

	printf("    ");
	for (column = 1; column <= nrows; column++)
		printf("%4d", column);
	printf("\n");

	for (row = 1; row <= nrows; row ++){
		printf("%4d", row);
		for (column = 1; column <= nrows; column++) {
			printf("%4d", column * row);
		}
		printf("\n");
	}

}
