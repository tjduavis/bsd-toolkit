/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.1                                         */
/*   This is the official test main for Question 2       */
/*   of Assignment 1                                     */
/*   BTP500-Fall 2006                                    */
/*                                                       */
/*   To compile this program on phobos:                  */
/*       c++ a1q2.cpp-qstaticinline                      */
/*   To compile this program on the PC :                 */
/*       bcc32 a1q2.cpp                                  */
/*                                                       */
/*   You will also need to have the file a1q2data.txt    */
/*   V1.1 changes: took out debugging output, fixed      */
/*   comment about what file is needed                   */
/*                                                       */
/*********************************************************/
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "clist.h"
using namespace std;
const int NUMELEM=100;
struct Book{
  int id_;
  char author_[31];
  char title_[41];
  Book(){
    id_=100;
    strcpy(author_,"someone");
    strcpy(title_,"ABC");
  }
};
ostream& operator<<(ostream& os,const Book& b);
template <class T>
void Adjust(int idx,T arr[],int sz);
bool CheckInts(const int correctlist[],const int checklist[],int sz);
bool CheckBooks(const Book correctlist[],const Book checklist[],int sz);
bool SameBook(const Book& b1,const Book& b2);
bool checkID(const void* idptr,const Book& B);
bool checkTitle(const void* ptr,const Book& B);
bool checkInt(const void* numptr,const int& val);
int main(void){
  int numbooks;
  Book* bookrecs;
  Book* bookorig;
  Book* bookcheck;
  Book passback;
  int intrecs[NUMELEM],intcheck[NUMELEM],intorig[NUMELEM];
  FILE* fs=fopen("a1q2data.txt","r");
  bool passtest=true;
  int pick;
  Book Nomatch;
  int ipassback;
  if(fs){
    CList<int> ilist;
    CList<Book> blist;
    if(!ilist.isempty() || !blist.isempty()){
      passtest=false;
      cout << "Default constructor error or isempty() function error." << endl;
      cout << "lists should be empty but isempty() function is returning false" << endl;
    }
    if(passtest){
      fscanf(fs,"%d\n",&numbooks);
      bookrecs=new Book[numbooks];
      bookorig=new Book[numbooks];
      bookcheck=new Book[numbooks];
      for(int i=0;i<numbooks;i++){
        fscanf(fs,"%d;%[^;];%[^\n]\n",&(bookrecs[i].id_),
          bookrecs[i].author_,bookrecs[i].title_);
        bookorig[i]=bookrecs[i];
      }//for
	  printf("step1"); getchar();
      for(int i=0;i<NUMELEM;i++){
        ilist.append(i);
        intrecs[NUMELEM-1-i]=i;
        intorig[NUMELEM-1-i]=i;
      }//for
	  printf("step2"); getchar();
      for(int i=1;i<numbooks;i++){
        blist.insert(bookrecs[i]);
      }//for
	  printf("step3"); getchar();
      blist.insert(bookrecs[0]);
      if(ilist.isempty() || blist.isempty()){
        passtest=false;
        cout << "Either your insert()/append() functions didn't work" << endl;
        cout << "or your isempty() function does not work.  lists are not" << endl;
        cout << "not empty, but your isempty() function returns true" << endl;
      }//if ilist.isempty() || blist.isempty(
    }//if passtest
	printf("step4"); getchar();
	
    if(passtest && 
      ((!blist.get(bookcheck,numbooks))||(!CheckBooks(bookcheck,bookrecs,numbooks)))){
      passtest=false;
      cout << "Failed either default constructor/insert() function test"<< endl;
    }
	CheckBooks(bookcheck,bookrecs,numbooks); getchar();
	printf("step5"); getchar();
    if (passtest){
      ilist.get(intcheck,NUMELEM);
      if(!CheckInts(intcheck,intrecs,NUMELEM)){
        passtest=false;
        cout << "Failed either default constructor/append() function test" << endl;
      }
    }
	printf("step6"); getchar();
    CList<int> ilistcopy=ilist;
    CList<Book> blistcopy=blist;
	printf("step7"); getchar();
    if(passtest){
      ilistcopy.get(intcheck,NUMELEM);
      blistcopy.get(bookcheck,numbooks);
	  CheckBooks(bookcheck,bookorig,numbooks); getchar();
      if(!CheckInts(intcheck,intorig,NUMELEM) || !CheckBooks(bookcheck,bookorig,numbooks)){
        passtest=false;
        cout << "Failed copy constructor test" << endl;
      }
    }
	printf("step8"); getchar();
    if(passtest){
      blist.goFwd();
      Adjust(1,bookrecs,numbooks);
      blist.get(bookcheck,numbooks);
      if(!CheckBooks(bookcheck,bookrecs,numbooks)){
        cout << "Your goFwd() is not working properly" << endl;
      }
    }
	printf("step9"); getchar();
    if(passtest){
      blist.goBack();
	  //blist.goBack();
	  //blist.goBack();
      Adjust(numbooks-1,bookrecs,numbooks);
      blist.get(bookcheck,numbooks);
      if(!CheckBooks(bookcheck,bookrecs,numbooks)){
        cout << "Your goBack() is not working properly" << endl;
      }
    }
	printf("step10"); getchar();
    if(passtest){
      if(blist.find(Nomatch.title_,checkTitle)){
        passtest=false;
        cout << "Failed Find() test." << endl;
        cout << "Find() function return true."<< endl;
        cout << "It should have returned false" << endl;
      }
      if(passtest){
        blist.get(bookcheck,numbooks);
        if(!CheckBooks(bookcheck,bookrecs,numbooks)){
          passtest=false;
          cout << "Find() test failed.  curr_ points at different node when find() failed"<< endl;
        }
      }

    }
	printf("step11"); getchar();
    if(passtest){
      if(blist.find(&(Nomatch.id_),checkID)){
        passtest=false;
        cout << "Failed Find() test." << endl;
        cout << "Find() function return true."<< endl;
        cout << "It should have returned false" << endl;
      }
      if(passtest){
        blist.get(bookcheck,numbooks);
        if(!CheckBooks(bookcheck,bookrecs,numbooks)){
          passtest=false;
          cout << "Find() test failed.  curr_ points at different node when find() failed"<< endl;
        }
      }

    }
	printf("step12 -FIND RETURNS TRUE"); getchar();
    if(passtest){
		printf("step12a\n"); getchar();
      for(int i=0;i<200 && passtest;i++){
        if(i==0)
          pick=0;
        else
          pick=rand()%numbooks;
        if(!blist.find(bookrecs[pick].title_,checkTitle)){
          passtest=false;
          cout << "Failed Find() test." << endl;
          cout << "Find() function returned false" << endl;
          cout << "It should have returned true" << endl;
        }
        else{
          passback=blist.curr();
        }
        if(passtest && !SameBook(passback,bookrecs[pick])){
          passtest=false;
          cout << "Failed Find() test." << endl;
          cout << "Find() function return value was correct but curr was not" << endl;
          cout << "pointing at the node with the correct book" << endl;
        }
        if(passtest){
          Adjust(pick,bookrecs,numbooks);
          blist.get(bookcheck,numbooks);
          if(!CheckBooks(bookcheck,bookrecs,numbooks)){
            passtest=false;
            cout << "Test failed List was not properly adjusted after search"<< endl;
          }
        }
      }//for
	  printf("step12d\n"); getchar();
      for(int i=0;i<200 && passtest;i++){
        if(i==100)
          pick=0;
        else
          pick=rand()%numbooks;
        if(!blist.find(&(bookrecs[pick].id_),checkID)){
          passtest=false;
          cout << "Failed Find() test." << endl;
          cout << "Find() function returned false, when it should have returned true" << endl;
        }
        else{
          passback=blist.curr();
        }
        if(passtest && !SameBook(passback,bookrecs[pick])){
          passtest=false;
          cout << "Failed Find() test." << endl;
          cout << "Find() function return value was correct but book passed back was not" << endl;
          cout << "The one searched for" << endl;
        }
        if(passtest){
          Adjust(pick,bookrecs,numbooks);
          blist.get(bookcheck,numbooks);
          if(!CheckBooks(bookcheck,bookrecs,numbooks)){
            passtest=false;
            cout << "Test failed List was not properly adjusted after search"<< endl;
          }
        }
      }//for
 
      for(int i=0;i<500 && passtest;i++){
        if(i==100)
          pick=0;
        else
          pick=rand()%NUMELEM;
        if(!ilist.find(&intrecs[pick],checkInt)){
          passtest=false;
          cout << "Failed Find() test." << endl;
          cout << "Find() function returned false, when it should have returned true" << endl;
        }
        else{
          ipassback=ilist.curr();
        }
        if(passtest && ipassback!=intrecs[pick]){
          passtest=false;
          cout << "Failed Find() test." << endl;
          cout << "Find() function return value was correct but book passed back was not" << endl;
          cout << "The one searched for" << endl;
        }
        if(passtest){
          Adjust(pick,intrecs,NUMELEM);
          ilist.get(intcheck,NUMELEM);
          if(!CheckInts(intcheck,intrecs,NUMELEM)){
            passtest=false;
            cout << "Test failed List was not properly adjusted after search"<< endl;
          }
        }
      }//for
    }
	printf("step13"); getchar();
    if(passtest){
      if(!ilist.remove() || !blist.remove()){
        passtest=false;
        cout << "Failed remove() test.  Return value incorrect" << endl;
      }
      else{
        ilist.get(intcheck,NUMELEM);
        blist.get(bookcheck,numbooks);
        if(!CheckInts(intcheck,intrecs+1,NUMELEM-1) || !CheckBooks(bookcheck,bookrecs+1,numbooks-1)){
          passtest=false;
          cout << "Failed remove test. Linked list incorrect after remove" << endl;
        }
      }//else
    }//ifpasstest
	printf("step14"); getchar();
    if(passtest){
      ilistcopy.get(intcheck,NUMELEM);
      blistcopy.get(bookcheck,numbooks);
      if(!CheckInts(intcheck,intorig,NUMELEM) || !CheckBooks(bookcheck,bookorig,numbooks)){
        passtest=false;
        cout << "Failed copy constructor test. Link list was not properly deep copied over" << endl;
      }
    }
	printf("step15"); getchar();
    if(passtest){
      ilistcopy=ilist;
      blistcopy=blist;
      ilistcopy.get(intcheck,NUMELEM);
      blistcopy.get(bookcheck,numbooks);
      if(!CheckInts(intcheck,intrecs+1,NUMELEM-1) || !CheckBooks(bookcheck,bookrecs+1,numbooks-1)){
        passtest=false;
        cout << "Failed assignment operator test" << endl;
      }
      ilist.remove();
      blist.remove();
      if(!CheckInts(intcheck,intrecs+1,NUMELEM-1) || !CheckBooks(bookcheck,bookrecs+1,numbooks-1)){
        passtest=false;
        cout << "Failed assignment operator test, deep copy not made" << endl;
      }

    }
	printf("step16"); getchar();
    if(passtest){
      for(int i=0;i<NUMELEM-1 && passtest;i++){
        if(!ilistcopy.remove())
          passtest=false;
      }
      if(!passtest)
        cout << "Failed remove() function test.  function returned false when list was not empty" << endl;
    }
	printf("step17"); getchar();
    if(passtest){
      if(ilistcopy.remove())
        passtest=false;
      if(!passtest)
        cout << "Failed remove() function test.  Function returned true, even though list was empty" << endl;
    }
	printf("step18"); getchar();
    if(passtest){
      cout << "Testing for Q2 complted.  All tests passed" << endl;
    }
	printf("step-FINISH"); getchar();
	for (int i = 0; i < numbooks-1; i++) {
		printf("%d\n",bookrecs[i].id_);
	}
    delete [] bookrecs;
    delete [] bookorig;
    delete [] bookcheck;
  }
  else{
    cout << "You need to have the file a1q2data.txt to run this main" << endl;
  }
}


bool CheckInts(const int checklist[],const int correctlist[],int sz){
  bool rc=true;
  for(int i=0;i<sz && rc;i++){
    if(correctlist[i]!=checklist[i])
      rc=false;
  }
  return rc;
}

bool CheckBooks(const Book correctlist[],const Book checklist[],int sz){
  bool rc=true;
  for(int i=0;i<sz && rc;i++){
    if(!SameBook(correctlist[i],checklist[i]))
      rc=false;
  }
  for (int i=0; i < sz; i++)
	  printf("correctlist is : %s || checklist is : %s\n",correctlist[i],checklist[i]);
  return rc;
}
bool SameBook(const Book& b1,const Book& b2){
  bool rc=true;
  if((b1.id_!=b2.id_) ||
      strcmp(b1.author_,b2.author_)!=0 ||
      strcmp(b1.title_,b2.title_)!=0 ){
      rc=false;
  }
  return rc;
}

bool checkID(const void* idptr,const Book& B){
  int id=*((int*)idptr);
  bool rc=false;
  if(id==B.id_){
    rc=true;
  }
  return rc;
}
bool checkTitle(const void* ptr,const Book& B){
  char* title=((char*)(ptr));
  bool rc=false;
  if(strcmp(title,B.title_)==0){
    rc=true;
  }
  return rc;
}
bool checkInt(const void* numptr,const int& val){
  int num=*((int*)numptr);
  bool rc=false;
  if(num==val){
    rc=true;
  }
  return rc;
}
ostream& operator<<(ostream& os,const Book& b){
  os << "ID: " << b.id_ << endl;
  os << "Author: " << b.author_ << endl;
  os << "Title: " << b.title_ << endl;
  return os;
}
template <class T>
void Adjust(int idx,T arr[],int sz){
  T* temp=new T[sz];
  int endchunk=sz-idx;
  for(int i=0;i<idx;i++){
    temp[i]=arr[i];
  }
  for (int i=0;i<endchunk ;i++){
    arr[i]=arr[i+idx];
  }/*for*/
  for(int i=0;i<idx;i++){
    arr[i+endchunk]=temp[i];
  }
}
