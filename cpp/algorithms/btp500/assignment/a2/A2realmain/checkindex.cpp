/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.2                                         */
/*   NOTE:  DO NOT RUN THIS PROGRAM WITHOUT RUNNING      */
/*   THE INDEXING PROGRAM FIRST!                         */
/*                                                       */
/*   This tests the hash table for searching by          */
/*   randomly choosing one of the words that were        */                            
/*   indexed earlier.  No consideration on their         */
/*   commonality is given (all equally likely)           */
/*                                                       */
/*                                                       */
/*   You can specify a cache size                        */
/*   If you run it with no aguments no cache will        */
/*   be used.  To use a cache supply the cache           */
/*   percentage in the command line                      */
/*                                                       */
/*   Usage:  checkindex <cachesize>                      */
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
/*   v1.2                                                */
/*   fixed command line argument to test cache           */
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
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
#define A2DEBUG 0  //set to #define A2DEBUG 1 if you are trying to debug your program
                   //it will create a file showing you what words were searched for
                   //and what was retrieved.  debug output will be written to debuglog.txt
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
  if( (argc==1) || ((argc==2) &&(sscanf(argv[1],"%lf",&cachesz)==1) && TESTCASE != TPERMHASH)){
    goodargs=true;
  }

  if(!goodargs){
    cout << "Incorrect Usage." << endl;
    cout << "Usage: checkindex <cachesize>" << endl;
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
#if A2DEBUG==1
      ofstream debug("debuglog.txt",ios::in);
#endif
      for(i=0;fscanf(fs,"%s %d\n",&word,&count)==2;i++){
         searchwords[i].Add(word,count);
      }
      numsearchwords=i;
      PermHash<WordRec>* booktable;
      if(argc==1){
        booktable=new PermHash<WordRec>("books.dat",0,0);
      }
      else{
#if TESTCASE!= TPERMHASH
        booktable=new PCacheHash<WordRec>("books.dat",0,0,cachesz,3);
#endif
      }
      if(booktable->max()==20000 && booktable->cap()==27011 && booktable->size()==19699){
        WordRec holder;
        bool found;
        bool isgood=true;
        for(i=0;i<numsearchwords && isgood;i++){
          found=booktable->find(searchwords[i].word(),holder);
          if(!found){
           cout << "It appears that your program has a bug.  A word that should" << endl;
           cout << "have been in the table was not found in the table" << endl;
           cout << "the word being searched for was: " << searchwords[i].word() << endl;
           cout << "find function returned false indicating it was unable to find word" << endl;
           isgood=false;
         }
         else{
           if(strcmp(searchwords[i].word(),holder.key())){
             cout << "Your function retreived a record but the word in it does not match" << endl;
             cout << "the word being searched for." << endl;
             cout << "word being searched for: " << searchwords[i].word() << endl;
             cout << "Found record: "<< endl;
             cout << holder << endl;
             isgood=false;
           }
           else if(searchwords[i].count()!=holder.total()){
             cout << "Your function found a matching record according to the key but" << endl;
             cout << "The rest of the data in the record (ie the word counts) was not" << endl;
             cout << "correct." << endl;
             cout << "Word: " << searchwords[i].word() << endl;
             cout << "Correct Total count: " << searchwords[i].count()<< endl << endl;
              cout << "Here is your record: " << endl;
              cout << holder << endl;
              isgood=false;
            }
          }
#if A2DEBUG == 1
          debug << "word being searched for: " << searchwords[i].word() << endl;
          debug << "total count (in all files): " << searchwords[i].count() << endl;
          debug << "Found record: "<< endl;
          debug << holder;
#endif
        }//for
        if(!isgood){
          cout << "program is not fully working yet. either words" << endl;
          cout << "that should have been found were not found or" << endl;
          cout << "their associated data was incorrect" << endl;
        }
        else{
          WordStat notthere[5];
          notthere[0].Add("gutenberg",0);
          notthere[1].Add("project",0);
          notthere[2].Add("bungalow",0);
          notthere[3].Add("archaeologist",0);
          notthere[4].Add("tours",0);
          for(int i=0;i<5 && isgood;i++){
            found=booktable->find(notthere[i].word(),holder);
            if(found){
              cout << "It appears that your program has a bug.  A word that should NOT" << endl;
              cout << "have been in the table was found in the table" << endl;
              cout << "the word being searched for was: " << notthere[i].word() << endl;
              cout << "find function returned true indicating it found the word" << endl;
              cout << "This is the record that your program found: "<< endl;
              cout << holder << endl;
              isgood=false;
            }
          }//for
          if(isgood){
            cout << "Your table was properly built and it seems that your" << endl;
            cout << "functions for your hash table works" << endl;
          }
        }//else
      }//if counts are correct
      else{
        cout << "either your capacity, max or number of items in your table is incorrectly" << endl;
        cout <<"calculated or stored. Please check your values" << endl;
        cout <<"The Correct values are: " << endl;
        cout <<"capacity = 27011" << endl;
        cout <<"max = 20000"<< endl;
        cout <<"size = 19699" << endl;
        cout << "Your table returns the following:" << endl;
        cout << "capacity = " << booktable->cap() << endl;
        cout << "max = " << booktable->max() << endl;
        cout << "size = " << booktable->size() << endl;
      }
      delete booktable;
    }//if fs
    else{
      cout << "make sure you have the worddump.txt file in this directory" << endl;
    }
  }
  return 0;
}
