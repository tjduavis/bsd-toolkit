#include <stdio.h>
#include "eval.h"

int main(void) {
	Term poly[3];
	poly[0].coeff_ = 6;
	poly[0].exp_ = 3;
	poly[1].coeff_ = -3;
	poly[1].exp_ = 1;
	poly[2].coeff_ = 1;
	poly[2].exp_ = 0;

	printf("result is: %f\n",Evaluate(5,poly,3));
	getchar();
	return 0;
}