#include <vector>
#include <iostream>
#include <fstream>
#include "timer.h"

using namespace std;

void InsertionSort(int arr[],int size){
  int curr;
  int i, j;
  for(i=1;i<size;i++){
    curr=arr[i];
    for(j=i;j>0 && arr[j-1] > curr;j--){
      arr[j]=arr[j-1];
    }
    arr[j]=curr;
  }
}

int main(int argc, char* argv[]){
  int size=atoi(argv[1]);
  int* myarr=new int[size];
  ofstream log("sort.log");
  Timer stopwatch;
  for(int i=0;i<size;i++){
    myarr[i]=i+1;
  }
  stopwatch.start();
  InsertionSort(myarr,size);
  stopwatch.stop();
  cout << stopwatch.currtime() << endl;
  for(int i=0;i<size;i++){
    log <<myarr[i]<< endl;
  }
  return 0;
}

