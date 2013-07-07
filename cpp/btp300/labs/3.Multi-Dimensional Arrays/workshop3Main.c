/*Workshop3 - Multi-Dimensional Arrays
 * DESCRIPTION:
 * FILE:          workshop3Main.c
 * AUTHOR:        Timothy Duavis
 * LAST MODIFIED: Sept 29,2005
 */

#include "matrix.h"

int main (void) {
	int selectRow, selectCol;
	int i;
	int display;

	int matrix[MAX][MAX] = {0};
	int vector[MAX] = {0};

	unsigned cont = 1;
	unsigned selectOperation = 0;
		

	while (cont) {
		printf("Number of rows (0 to exit) ? ");
		scanf("%d", &selectRow);
		if (selectRow) {
		/* Run Program */
			
			printf("Number of columns          ? ");
			scanf("%d",&selectCol);

			InputMatrix(matrix, selectCol, selectRow);
			
			printf("Pre (0) or Post (1) Multiply ? ");
			scanf("%d",&selectOperation);
			
			InputVector(vector, selectCol);
			
			if (selectOperation) {
				PostMultiply(matrix, vector, selectCol, selectRow);
				display = selectRow;	
			} else {
				PreMultiply(matrix, vector, selectRow, selectCol);
				display = selectCol;
			}

			DisplayResult(vector, display);				
		} else {
			/* End Program */
			cont = 0;
		}
	}

	return 0;
}

			