/*********************************************************/
/*                                                       */
/*   Written by: Timothy Duavis                          */
/*   Version 1.0                                         */
/*   This is program is for question 3 of assignment 1   */
/*   written by Catherine Leung. The program             */ 
/*   demonstrates a function that is written with a run  */ 
/*   time of Big O if N as oppose to a run time of Big O */
/*   of N squared or worse.                              */
/*   This program evaluates a polynomial with the first  */
/*   term having the hightest exponent.                  */
/*                                                       */
/*   Course: BTP500-Fall 2006                            */
/*   Professor: Catherine Leung                          */
/*                                                       */
/*                                                       */
/*********************************************************/

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