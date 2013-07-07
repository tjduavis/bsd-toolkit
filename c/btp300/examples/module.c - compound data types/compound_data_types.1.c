/* Module C - Data Types 
 * Compound Data Types 
 *
 * Examples
 */
 
#include <stdio.h>

int main(void) {
	int a[10];	
	int *p;
	int *r;
	
	int b[2][10];
	int **q;
	
	int c[2][10][6];
	int ***s;
	
	/***One dimensional derivations***/
	a[5] = 1;
	a[6] = 2;
 	
	/* address of element 6 */
 	p = &a[4] + 1;
 	p = &a[6] - 1;
 	
 	/* pointer to the value in element 6 */
 	r = *(a + 5);
 	
 	/* Outputs to prove equivalancy */
 	printf("&a[4] + 1 = %d\n",&a[4] + 1);
 	printf("address of a[5] = %d\n",&a[5]);
 	printf("a + 5 = %d\n",a + 5);
 	printf("a[5] = %d\n",a[5]);
 	printf("*(a + 5) = %d\n",*(a + 5));
 	printf("*r = %d\n",r);
 	
 	/***Two dimensional derivations***/
 	b[0][0] = 5;
 	
 	/* address of element 1 */
 	p = &b[0][0] + 0 * 10 + 0; 	
 	/* pointer syntax:
 	 * &b[0][0] + i * 10 + j
 	 * The address of first element of a plus an integer value i 
 	 * times the number of columns plus an integer value j  
 	 * where i == row
 	 *       j == col
 	 */
 	
    /* value of element 1 */   
 	q = *(*(b + 0) + 0);
 	/* pointer syntax:
 	 * *(*(b + i) + j)
 	 * where i == row
 	 *       j == col
 	 */
 	
 	/***Outputs to prove equivalancy***/
 	/* address of element 1 */
 	printf("address of element 1 - &b[0][0] = %d\n",&b[0][0]);
 	printf("address of element 1 - *p = %d\n",p);
 	printf("address of element 1 - &b[0][0] + 0 * 10 + 0 = %d\n",&b[0][0] + 0 * 10 + 0);
 	printf("address of element 1 - b[0][0] + 0 * 10 + 0 = %d\n",b[0][0] + 0 * 10 + 0);
 	r = &b[0][0] + 0 * 10 + 0;
 	printf("address of element 1 - *r = %d\n",r);
 	
 	printf("\n\n");
 	
 	/* pointer for value of element 1 */
 	printf("value of element 1 - b[0][0] = %d\n",b[0][0]);
 	printf("value of element 1 - **q = %d\n",q);
 	printf("value of element 1 - *(*(b + 0) + 0) = %d\n",*(*(b + 0) + 0));
 	
 	printf("\n\n");
 	
 	/***Three dimensional derivations***/
 	c[0][0][0] = 7;
 	
 	/* address of page 1, row 1 col 1 */
 	/* pointer syntax
 	 * &c[0][0][0] + i * 10 * 6 + j * 6 + k
 	 * The address of first element of c plus an integer value i times the number of elements per page plus 
 	 * an integer value j times the number of columns per row plus an integer value k 
 	 * where i = page
 	 *       j = row
 	 *       k = col
 	 */
 	
 	p = &c[0][0][0] + 0 * 10 * 6 + 0 * 6 + 0;
 	
 	/* address of element 1 */
 	printf("address of element 1 - &c[0][0][0] = %d\n",&c[0][0][0]);
 	printf("address of element 1 - *p = %d\n",p);
 	printf("address of element 1 - &c[0][0][0] + 0 * 10 * 6 + 0 + 0 = %d\n",&c[0][0][0] + 0 * 10 * 6 + 0 + 0);
 	
 	printf("\n\n");
 	
 	/* pointer for value of element 1 */
 	/* pointer syntax
 	 * s = *(*(*(c + i) + j) + k) 
 	 * where i = page
 	 *       j = row
 	 *       k = col
 	 */
 	
 	s = *(*(*c + 0) + 0 ) + 0;
 	
 	/***Outputs to prove equivalancy***/
 	/* pointer for value of element 1 */
 	printf("value of element 1 - c[0][0][0] = %d\n",c[0][0][0]);
 	printf("value of element 1 - ***s = %d\n",s);
 	printf("value of element 1 - *(*(*(c + 0) + 0 ) + 0) = %d\n", *(*(*(c + 0) + 0 ) + 0) );
 	
 		
 	return 0;
}
/* compound_data_types.1.c */