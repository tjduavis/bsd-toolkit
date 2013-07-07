#include <iostream>
using namespace std;
#include "timer.h"

/*This function finds and returns x!*/
unsigned int Fact(unsigned int x){
  unsigned int rc;
  if(x<=1){       //BASE CASE.  if x is 0
    rc=1;         //or x is 1, we know the
  }               //result is 1
  else{
    rc=x*Fact(x-1);
  }
  return rc;  
}


/*This function finds and returns x!*/
unsigned int Fact1(unsigned int x){
  unsigned int rc=1;  //base case, if the condition is false, this is
                     //return value
  if(x>1){ 
    rc=x*Fact1(x-1);
  }
  return rc;
  
}

/* This function finds the nth fibonacci value.
   F0 == 0
   F1 ==1
   F2 == F1+F0
....
*/
unsigned int FibR(unsigned int n){
  unsigned int rc;
  if(n==0)
    rc=0;
  else if(n==1)
    rc=1;
  else
    rc=FibR(n-1)+FibR(n-2);
  return rc;
}

/* this function returns x ^ n (x raised to n)*/
unsigned int PowR(unsigned int x, unsigned int n){
  unsigned int rc;
  if(n==0){
    rc=1;
  }
  else{
    rc=x*PowR(x,n-1);
  }
  return rc;
}

/* this function returns x ^ n (x raised to n)*/
unsigned int Pow(unsigned int x, unsigned int n){
  unsigned int rc=1;
  for(int i=0;i<n;i++){
     rc=rc*x;
  }
  return rc;
}

unsigned int Fib(unsigned int x){
  unsigned int result=0;
  if(x==1)
    result=1;
  else if(x > 1){
    int fnless1=1;
    int fnless2=0;
    for(int n=2;n<=x;n++){
      result=fnless2+fnless1;
      fnless2=fnless1;
      fnless1=result;
    }
  }
  return result;

}

int main(int argc,char* argv[]){
  unsigned int v=(unsigned int)atoi(argv[1]);
  unsigned int aa;
  Timer T1, T2;
  T1.start();
  aa=Fib(v);
  T1.stop();
  cout << "Fib ( " << v << " ) == " << aa << endl;
  cout << "It took :  " << T1.currtime() << " seconds " << endl;
  T2.start();
  aa=FibR(v);
  T2.stop();
  cout << "FibR ( " << v << " ) == " << aa << endl;
  cout << "It took :  " << T2.currtime() << " seconds " << endl;
}
