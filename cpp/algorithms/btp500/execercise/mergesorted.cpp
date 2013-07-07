#include <vector>
#include <iostream>
#include <fstream>
#include "timer.h"
using namespace std;
template <class TYPE>
void MergeSort(vector<TYPE>& arr, vector<TYPE>& tmp, int start, int end){
  if (start<end){
    int mid=(start+end)/2;
    MergeSort(arr,tmp,start,mid);
    MergeSort(arr,tmp,mid+1,end);
    Merge(arr,tmp,start,mid+1,end);
  }
}

template <class TYPE>
void Merge(vector<TYPE>& arr, vector<TYPE>& tmp, int start,
                                         int start2, int end){
  int aptr=start;
  int bptr=start2;
  int i=start;
  while(aptr<start2 && bptr <= end){
    if(arr[aptr]<arr[bptr])
      tmp[i++]=arr[aptr++];
    else
      tmp[i++]=arr[bptr++];
  }
  while(aptr<start2){
    tmp[i++]=arr[aptr++];
  }
  while(bptr<=end){
    tmp[i++]=arr[bptr++];
  }
  for(i=start;i<=end;i++){
    arr[i]=tmp[i];
  }
}
template <class TYPE>
void MergeSort(vector<TYPE>& arr){
  vector<TYPE> tmp(arr.size());
  MergeSort(arr,tmp,0,arr.size()-1);
}

int main(int argc, char* argv[]){
  int size=atoi(argv[1]);
  vector<int> myarr(size);
  Timer stopwatch;
  fstream log("sort.log");
  for(int i=0;i<myarr.size()-1;i++){
    myarr[i]=i+1;
  }
  myarr[size-1]=0;
  stopwatch.start();
  MergeSort(myarr);
  stopwatch.stop();
  for(int i=0;i<myarr.size();i++){
    log <<myarr[i]<< endl;
  }
  cout<< "Time: "  << stopwatch.currtime() << endl;
  return 0;
}
