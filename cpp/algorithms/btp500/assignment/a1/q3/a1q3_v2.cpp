/* BTP500 Assignment 1 */
/* Question 3 */
#define HIGHEST_EXP 0
struct Term{
  int coeff_;      //the coefficient of the term
  int exp_;        //the exponent x is raised to
};
double Evaluate(double val, Term poly[],int numterms) {
	double result = 0.0;
	double *buff;

	if (poly[HIGHEST_EXP].exp_ == 0) {
		buff = new double [1];
		buff[0] = 1;
	} else if (poly[HIGHEST_EXP].exp_ == 1){
		buff = new double [2];
		buff[0] = 1;
		buff[1] = val;
	} else {
		double powerOf;
		buff = new double [poly[HIGHEST_EXP].exp_ + 1];
		buff[0] = 1;
		buff[1] = powerOf = val;
		int i,j;
		for (i = 1, j = 2; i < poly[HIGHEST_EXP].exp_; i++, j++) {
			powerOf *= val;
			buff[j] = powerOf;
		}
	}
	for (int i = 0; i < numterms; i++) {
		result += poly[i].coeff_ * buff[poly[i].exp_];
	}
	if (buff) delete buff;
	return result;
}