/* Workshop 2 - Multi-Dimensional Arrays
 *  FILE: matrix.c
 *  DESCRIPTION:
 *  LAST MODIFIED: Sept 28,2005
 */

#include "matrix.h"
#include <stdio.h>

/* InputMatrix
 *  DESCRIPTION: Creates matrix, using multi dimensional array.
 *  PARAMTERS: INT value for the number of 
 *             columns and INT array for the matrix.
 *  RETURN: VOID.
 */
void InputMatrix( int m[][MAX], int col, int row) {
	int i, j;
		
	for ( i = 0; i < row; i++ ) {
		printf("Row %d ? ",i + 1);
		for ( j = 0; j < col; j++ ) {
			scanf("%d",&m[i][j]);
		}
	} 	
		
	return 0;
}

/* InputVector
 *  DESCRIPTION: Creates a vector, using an array.
 *  PARAMTERS: INT values for number of columns
 *             and INT array for the matrix. 
 *  RETURN: VOID.
 */
void InputVector( int v[], int col) {
	int j;
	
	printf("Vector? \n");
	for ( j = 0; j < col; j++ )
		scanf("%d", &v[j]); 
		
	return 0;
}	
	
/* Pre-Multiply 
 *  DESCRIPTION: Performs pre-multiplicaiton with a matrix and a vector.
 *  PARAMTERS: INT values for number of columns. 
 *  RETURN: VOID.
 */
void PreMultiply( int m[][MAX], int v[], int Row, int Col) {
	int product[MAX] = {0};
	int i,j;
	for ( i = 0; i < Col; i++ ) {
		for ( j = 0; j < Row; j++ ) {
			product[i] += v[i] * m[j][i];
		}
	}
	
	for ( i = 0; i < Col; i++ ) 
		v[i] = product[i];
}

/* Post-Multiply 
 *  DESCRIPTION: Performs post-multiplicaiton with a matrix and a vector.
 *  PARAMTERS: INT values for number of columns. 
 *  RETURN: VOID.
 */
void PostMultiply( int m[][MAX], int v[], int Col, int Row) {
	int product[MAX] = {0};
	int i,j;
	for ( i = 0; i < Row; i++ ) {
		for ( j = 0; j < Col; j++ ) {
			if (!v[i]) v[i] = v[0];
			product[i] += v[i] * m[i][j];
		}
	}
	
	for ( i = 0; i < Row; i++ ) 
		v[i] = product[i];
}

/* DisplayResult
 *  DESCRIPTION: Displays product of pre/post multiplication of matrix and vector.
 *  PARAMETERS:  INT array.
 *  RETURN:      VOID. 
 */
void DisplayResult( int final[], int col ) {
	int i;
	printf("Result: ");
	for (i = 0; i < col; i++) 
		printf("%d ",final[i]);

	printf("\n");

	return 0;
}