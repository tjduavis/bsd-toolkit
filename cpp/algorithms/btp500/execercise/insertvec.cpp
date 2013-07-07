#include <vector>
#include <iostream>
#include <fstream>
#include "timer.h"

using namespace std;

template <class TYPE>
void InsertionSort(vector<TYPE>& arr){
  TYPE curr;
  int i, j;
  for(i=1;i<arr.size();i++){
    curr=arr[i];
    for(j=i;j>0 && arr[j-1] > curr;j--){
      arr[j]=arr[j-1];
    }
    arr[j]=curr;
  }
}

int main(int argc, char* argv[]){
  int size=atoi(argv[1]);
  vector<int> myarr(size);
  ofstream log("sort.log");
  Timer stopwatch;
  for(int i=0;i<myarr.size();i++){
    myarr[i]=rand();
  }
  stopwatch.start();
  InsertionSort(myarr);
  stopwatch.stop();
  cout << stopwatch.currtime() << endl;
  for(int i=0;i<myarr.size();i++){
    log <<myarr[i]<< endl;
  }
  return 0;
}

