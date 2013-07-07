/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.0                                         */
/*   This is the official test main for Question 3       */
/*   of Assignment 1                                     */
/*   BTP500-Fall 2006                                    */
/*                                                       */
/*   To compile this program on phobos:                  */
/*       c++ a1q3main.cpp -qstaticinline                 */
/*   To compile this program on the PC :                 */
/*       bcc32 a1q3main.cpp                              */
/*                                                       */
/*********************************************************/
#include <iostream>
using namespace std;
struct Term{
  int coeff_;      //the coefficient of the term
  int exp_;        //the exponent x is raised to
};
const int maxterms=7;
const int numeq=4;
double Evaluate(double val, Term poly[],int numterms);
void Print(Term poly[],int numterms);
int main(void){
  Term poly[maxterms];
  int coef[numeq][maxterms]={{1,1,1,1,1,1,1},{1,1,1,1},
                                {2,-3,6,4},{2,-4,3,-1}};
  int exp[numeq][maxterms]={{6,5,4,3,2,1,0},{6,4,2,0},
                                {6,4,2,1},{8,7,2,0}};
  int numterms[numeq]={7,4,4,4};
  double correct[numeq][3]={{127,1093,5461},{85,820,4369},
                              {112,1281,7536},{11,4400,65583}};
  bool pass=true;
  for(int i=0;i<numeq && pass;i++){
    for(int j=0;j<numterms[i];j++){
      poly[j].coeff_=coef[i][j];
      poly[j].exp_=exp[i][j];
    }
    for(int j=0;j<3 && pass;j++){
      double rc=Evaluate(2+j,poly,numterms[i]);
      if(rc!=correct[i][j]){
        pass=false;
        cout << "Evaluate function return value is incorrect." << endl;
        cout << "P(x)= ";
        Print(poly,numterms[i]);
        cout << endl;
        cout << "x is: " << 2+j << endl;
        cout << "Function should return: " << correct[i][j] << endl;
        cout << "Your function returned: " << rc << endl;
      }
    }
  }
  if(pass){
      cout << "Testing for Q3 complted.  All tests passed" << endl;
  }
}
int ABS(int val){
  return (val>0)?val:-val;
}
void Print(Term poly[],int numterms){
  if(poly[0].coeff_ != 1 || poly[0].exp_==0)
    cout << poly[0].coeff_;
  if(poly[0].exp_!=0) 
    cout << "x^" << poly[0].exp_;
  for(int i=1;i<numterms;i++){
    if(poly[i].coeff_>0){
      cout << " + ";
    }
    else{
      cout << " - ";
    }
    if(ABS(poly[i].coeff_) != 1 || poly[i].exp_==0)
      cout << ABS(poly[i].coeff_);
    if(poly[i].exp_!=0) 
      cout << "x^" << poly[i].exp_;
  }
}
