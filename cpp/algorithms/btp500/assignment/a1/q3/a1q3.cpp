/*********************************************************/
/*                                                       */
/*   Written by: Timothy Duavis                          */
/*   Student Number: 019-261-049                         */
/*   Section: A/B                                        */ 
/*   Assignment #1 Version 1.0                           */
/*   The program demonstrates a function that is         */
/*   written with a run time of Big O if N as oppose to  */
/*   a run time of Big O of N squared or worse.          */
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
	double powerOf; //the value that will be squared with val
	double *expVal; //dynamic array that holds the expVal 
	                //where the the element is the exp #

	if (poly[HIGHEST_EXP].exp_ == 0) {
		expVal = new double [1];
		expVal[0] = 1;
	} else if (poly[HIGHEST_EXP].exp_ == 1){
		expVal = new double [2];
		expVal[0] = 1;
		expVal[1] = val;
	} else {
		expVal = new double [poly[HIGHEST_EXP].exp_ + 1];
		expVal[0] = 1;
		expVal[1] = powerOf = val;
		int expNum;
		for (int i = 1, expNum = 2; i < poly[HIGHEST_EXP].exp_; i++, expNum++) {
			powerOf *= val;
			expVal[expNum] = powerOf;
		}
	}
	for (int i = 0; i < numterms; i++) {
		result += poly[i].coeff_ * expVal[poly[i].exp_];
	}
	if (expVal) delete expVal;
	return result;
}