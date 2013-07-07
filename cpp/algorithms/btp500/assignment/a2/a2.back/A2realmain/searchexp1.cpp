/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.1                                         */
/*   NOTE:  DO NOT RUN THIS PROGRAM WITHOUT RUNNING      */
/*   THE INDEXING PROGRAM FIRST!                         */
/*                                                       */
/*   This tests the hash table for searching by          */
/*   randomly choosing one of the words that were        */                            
/*   indexed earlier.  No consideration on their         */
/*   commonality is given (all equally likely)           */
/*                                                       */
/*                                                       */
/*   You must supply a value indicating how many         */
/*   searches you wish to perform.                       */
/*   You can also specify a cache size                   */
/*   If you run it with only one argument no cache will  */
/*   be used.  To use a cache supply the cache           */
/*   percentage in the command line                      */
/*                                                       */
/*   Usage:  searchexp1 <numberofsearch> <cachesize>     */
/*   Note: cachesize is optional but should not be 0     */
/*                                                       */
/*   BTP500-Fall 2006                                    */
/*                                                       */
/*   A reminder that all template code must be placed in */
/*   header file. You will have trouble compiling and    */
/*   linking otherwise.                                  */
/*                                                       */
/*   v1.1                                                */
/*   Fixed some preprocessor statements to match         */
/*   preliminary main and call to max()                  */
/*                                                       */
/*********************************************************/
#define TPERMHASH 1
#define TPCACHEOLD 2
#define TPCACHEUSED 3
#define TPCACHERECENT 4
#define TESTCASE TPERMHASH  //change this to test your cache versions
#if TESTCASE == TPERMHASH
  #include "permhash.h"
#elif TESTCASE == TPCACHEOLD
  #include "pcacheold.h"
#elif TESTCASE == TPCACHEUSED
  #include "pcacheused.h"
#elif TESTCASE == TPCACHERECENT
  #include "pcacherecent.h"
#endif
#include "wordrec.h"
#include "timer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
class WordStat{
  char* word_;
  int count_;
public:
  WordStat(){
    word_=NULL;
    count_=0;
  }
  void Add(const char* w,int count){
      word_=new char[strlen(w)+1];
      strcpy(word_,w);
      count_=count;
  }
  ~WordStat(){
    delete [] word_;
  }
  const char* word()const{return word_;}
  int count()const{return count_;}
};
int main(int argc, char* argv[]){
  int i;
  double cachesz;
  int numsearch;
  bool goodargs=false;
  if((argc==2)&& (sscanf(argv[1],"%d",&numsearch)==1)){
    goodargs=true;
  }
  else if((argc==3)&&(sscanf(argv[1],"%d",&numsearch)==1) 
                              &&(sscanf(argv[2],"%lf",&cachesz)==1) && TESTCASE!=TPERMHASH){
    goodargs=true;
  }

  if(!goodargs){
    cout << "Incorrect usage." << endl;
    cout << "Usage: searchexp1 <numberofsearches> <cachesize>" << endl;
    cout << "<cachesize> is required only if testing cache table." << endl;
    cout << "If you are testing cache table, check your #define statements" << endl;
  }
  else{
    FILE* fs=fopen("worddump.txt","r");

    if(fs){
      WordStat* searchwords;
      searchwords=new WordStat[20000];
      int i;
      char word[60];
      int count;
      int numsearchwords;
      int randval;
      for(i=0;fscanf(fs,"%s %d\n",&word,&count)==2;i++){
         searchwords[i].Add(word,count);
      }
      numsearchwords=i;
      Timer T;
      PermHash<WordRec>* booktable;
      if(argc!=3){
        booktable=new PermHash<WordRec>("books.dat",0,0);
      }
      else{
 #if TESTCASE != TPERMHASH
       booktable=new PCacheHash<WordRec>("books.dat",0,0,cachesz,3);
 #endif
      }
      WordRec holder;
      bool found;
      bool isgood=true;
      for(i=0;i<numsearch && isgood;i++){
        randval=rand()%numsearchwords;
        T.start();
        found=booktable->find(searchwords[randval].word(),holder);
        T.stop();
        if(!found){
          cout << "It appears that your program has a bug.  A word that should" << endl;
          cout << "have been in the table was not found in the table" << endl;
          cout << "the word being searched for was: " << searchwords[randval].word() << endl;
          cout << "find function returned false indicating it was unable to find word" << endl;
          isgood=false;
        }
        else{
          if(strcmp(searchwords[randval].word(),holder.key())){
            cout << "Your function retreived a record but the word in it does not match" << endl;
            cout << "the word being searched for." << endl;
            cout << "word being searched for: " << searchwords[randval].word() << endl;
            cout << "Found record: "<< endl;
            cout << holder << endl;
            isgood=false;
          }
        }
      }//for
      if(!isgood){
        cout << "program is not fully working yet." << endl;
        cout << "words that should have been found were not found" << endl;
      }
      else{
       cout << "Time needed to search " << numsearch << " words ";
       cout << " was " << T.currtime() << " s" << endl;
      }
      delete booktable;
    }//if fs
    else{
      cout << "make sure you have the worddump.txt file in this directory" << endl;
    }
  }
  return 0;
}
