#include <vector>
#include <iostream>
#include <fstream>
#include "timer.h"
using namespace std;
template <class TYPE>
void HeapSort(vector<TYPE>& arr){
  int i;
  int parent;  //index of parrent of node i;
  int left;    //index of left child
  int right;   //index of right child
  int empty;   //location of empty spot
  int curr;    //item that we are dealing with
  bool found;  //correct spot for curr's placement has been found or not
  int last;    //last element in the heap;
  //Build the heap (max heap)
  for(i=1;i<arr.size();i++){
    curr=arr[i];
    empty=i;
    found=false;
    while(empty!=0 && !found){
      parent=(empty-1)/2;
      if(arr[parent] < curr){
        arr[empty]=arr[parent];
        empty=parent;
      }
      else
        found=true;
    }
    arr[empty]=curr;
  }//for each element in array
  last=arr.size()-1;
  for(int i=0;i<arr.size();i++){
    curr=arr[last];
    arr[last]=arr[0];
    empty=0;
    found=false;
    last--;
    left=empty*2+1;
    while(!found && left <= last){
      right=left+1;
      if(right > last){   //only a left child
        if(curr >= arr[left])
          found=true;
        else{
          arr[empty]=arr[left];
          empty=left;
          left=empty*2+1;         
        }       
      } //if only left child
      else{
        if(curr >= arr[left] && curr >=arr[right]){
          found=true;
        }//if curr is bigger than children
        else{
          if(arr[left] > arr[right]){
            arr[empty]=arr[left];
            empty=left;
            left=empty*2+1;
          }
          else{
            arr[empty]=arr[right];
            empty=right;
            left=empty*2+1;            
          }
        }//else (2 children)
      }//while
    } 
      arr[empty]=curr;
  }    
  //Destroy the heap


}

int main(int argc, char* argv[]){
  int size=atoi(argv[1]);
  vector<int> myarr(size);
  Timer stopwatch;
  fstream log("sort.log");
  for(int i=0;i<myarr.size();i++){
    myarr[i]=rand();
  }
  stopwatch.start();
  HeapSort(myarr);
  stopwatch.stop();
  for(int i=0;i<myarr.size();i++){
    log <<myarr[i]<< endl;
  }
  cout<< "Time: "  << stopwatch.currtime() << endl;
  HeapSort(myarr);

  return 0;
}
