/* Workshop 2 - Multi-Dimensional Arrays
*  FILE: matrix.h
*  DESCRIPTION:
*  LAST MODIFIED: Sept 28,2005
*/

#define MAX 9

void 	InputMatrix(int[][MAX], int, int);
void 	InputVector(int[], int);
void 	PreMultiply(int[][MAX], int[], int, int);
void 	PostMultiply(int[][MAX], int[], int, int);
void    DisplayResult(int [], int);