/* BTP500 Assignment 1 */
/* Question 3 */

#include "eval.h"
#include <stdio.h>

double Evaluate(double val, Term poly[],int numterms) {
	double result = 0.0;
	for (int i = 0; i < numterms; i++) {
		if (poly[i].exp_ == 0) result += poly[i].coeff_ * 1;
		else if (poly[i].exp_ == 1) result += poly[i].coeff_ * val;
		else {
			double powerOf = val;
			for (int i = 0; i < poly[i].exp_ + 1; i++)
				powerOf *= val;
			result += poly[i].coeff_ * powerOf;
		}
	}
	return result;
}