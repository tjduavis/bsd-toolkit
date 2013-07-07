#include <vector>
#include <iostream>
#include <fstream>
#include "timer.h"

using namespace std;

template <class TYPE>
void InsertionSort(vector<TYPE>& arr,int left,int right){
  TYPE curr;
  int i, j;
  for(i=left+1;i<=right;i++){
    curr=arr[i];
    for(j=i;j>0 && arr[j-1] > curr;j--){
      arr[j]=arr[j-1];
    }
    arr[j]=curr;
  }
}


template <class TYPE>
void QuickSort(vector<TYPE>& arr, int left, int right){
  if(right-left <=3){
    InsertionSort(arr,left,right);
  }
  else{
    int pivotpt=right;
    int i=left;
    int j=right-1;
    TYPE pivot=arr[pivotpt];
    while(i<j){
      while(arr[i]<pivot) i++;
      while(arr[j]>pivot) j--;
      if(i<j)
        swap(arr[i++],arr[j--]);
    }
    if(i==j && arr[i] < arr[pivotpt])
      i++;
    swap(arr[i],arr[pivotpt]);
    QuickSort(arr,left,i-1);
    QuickSort(arr,i+1,right);
  }
}

template <class TYPE>
void QuickSort(vector<TYPE>& arr){
  QuickSort(arr,0,arr.size()-1);
}

int main(int argc, char* argv[]){
  int size=atoi(argv[1]);
  vector<int> myarr(size);
  Timer stopwatch;
  ofstream log("sort.log");
  for(int i=0;i<myarr.size();i++){
    myarr[i]=rand();
  }
  stopwatch.start();
  QuickSort(myarr);
  stopwatch.stop();
  cout << stopwatch.currtime() << endl;
  for(int i=0;i<myarr.size();i++){
    log <<myarr[i]<< endl;
  }
  return 0;
}

