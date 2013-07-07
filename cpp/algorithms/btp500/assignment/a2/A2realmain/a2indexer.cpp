/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.1                                         */
/*   The main is written in 2 files.  This is the first  */
/*   Compile and run this program.  Once it finishes,    */
/*   compile and run the other program.                  */
/*                                                       */
/*   This program goes through 8 files and creates an    */
/*   index of the words found in them.  It keeps track   */
/*   of how many times each word appears in each of the  */
/*   files.  This program may take a while to run as     */
/*   the files are not small so have patience            */
/*                                                       */
/*   Once the indexing is done, run the searcher program.*/
/*   that program will allow you to search for that word.*/
/*   If found it will print out how many times each word */
/*   appeared in the files it was found in.  If not      */
/*   It will print out that it was not found             */
/*                                                       */
/*   NOTE:  If you run this program more than once, all  */
/*          the counts will double so you need to remove */
/*          the old data file before running this again  */
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
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
const int MAXWORDS = 20000;
const int NUMBUCKETS = 3;     //the cache, feel free to change them for test
const double OVERAMT = 0.35;  //unless you want to really wait, don't change it
                              //to less than .3

int myisalpha(int c){
  int rc=0;
  if ((c >='a' && c <= 'z') || (c >='A' && c<='Z')){
    rc=1;
  }/*if*/
  return rc;
}

int getnext(ifstream& fs,char word[]){
  char c;
  int i=0;
  int rc=1;
  fs.get(c);
  while(fs && !myisalpha(c)){
    fs.get(c);
  }
  while(fs && myisalpha(c)){
    word[i++]=tolower(c);
    fs.get(c);
  }
  if(!fs)
    rc=0;
  else
    word[i]='\0';
  return rc;
}
int main(int argc,char* argv[])
{  
  Timer T;
  ifstream fs;
  char word[80];
  int numunique=0;
  double numsec;
	PermHash<WordRec>* booktable;
  double cachesz;
  bool goodargs=false;
  if(argc==1){
    T.start();
    booktable=new PermHash<WordRec>("books.dat",MAXWORDS,OVERAMT);
    T.stop();
    goodargs=true;
  }
  else if((argc==2)&&(sscanf(argv[1],"%lf",&cachesz)==1)){
#if TESTCASE != TPERMHASH
    T.start();
    booktable=new PCacheHash<WordRec>("books.dat",MAXWORDS,OVERAMT,cachesz,NUMBUCKETS);
    T.stop();
#else
    cout << "#defines in main not set to test cache.  Please adjust as"<< endl;
    cout << "necessary if you wish to test cache. Continuing without a cache" << endl;
    cout << "without cache" << endl;
    T.start();
    booktable=new PermHash<WordRec>("books.dat",MAXWORDS,OVERAMT);
    T.stop();
#endif
    goodargs=true;
  }
  if(goodargs){
    if(booktable->max()==20000 && booktable->cap()==27011 && booktable->size()==0){
      WordRec holder;
      for(int i=0;i<numfiles;i++){
        fs.open(filenames[i]);
        cout << "Started Processing: " << filenames[i] << endl;
        while(getnext(fs,word)){
          WordRec tmp(word);
          T.start();
          if(booktable->find(word,holder)){
            holder.increase(i);
            booktable->update(holder);
          }
          else if(numunique < MAXWORDS){
			numunique++;
            tmp.increase(i);
            booktable->update(tmp);
          }/*else if*/
          T.stop();
        }/*while*/
        fs.clear();
        fs.close();
        cout << "Finished Processing: " << filenames[i] << endl;
      }
      numsec=T.currtime();
      cout << "Number of unique words added: " << numunique << endl;
      cout << "Time used to index files: " << numsec << " seconds" << endl;

      if(booktable->max()==20000 && booktable->cap()==27011 && booktable->size()==19704){
        /*removing 5 words that are in the table*/
        booktable->remove("gutenberg");
        booktable->remove("project");
        booktable->remove("bungalow");
        booktable->remove("archaeologist");
        booktable->remove("tours");

        /*removing 5 word that isn't in the table because it was already removed earlier*/
        booktable->remove("gutenberg");
        booktable->remove("project");
        booktable->remove("bungalow");
        booktable->remove("archaeologist");
        booktable->remove("tours");
        if(booktable->max()!=20000 || booktable->cap()!=27011 || booktable->size()!=19699){
          cout << "After removing some records: " << endl;
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
      }
      else{
        cout << "After completing record creation: " << endl;
        cout << "either your capacity, max or number of items in your table is incorrectly" << endl;
        cout << "calculated or stored. Please check your values" << endl;
        cout << "The Correct values are: " << endl;
        cout << "capacity = 27011" << endl;
        cout << "max = 20000"<< endl;
        cout << "size = 19704" << endl;
        cout << "Your table returns the following:" << endl;
        cout << "capacity = " << booktable->cap() << endl;
        cout << "max = " << booktable->max() << endl;
        cout << "size = " << booktable->size() << endl;
      }
    }
    else{
        cout << "either your capacity, max or number of items in your table is incorrectly" << endl;
        cout <<"calculated or stored. Please check your values" << endl;
        cout <<"The Correct values are: " << endl;
        cout <<"capacity = 27011" << endl;
        cout <<"max = 20000"<< endl;
        cout <<"size = 0 (initial size)" << endl;
        cout << "Your table returns the following:" << endl;
        cout << "capacity = " << booktable->cap() << endl;
        cout << "max = " << booktable->max() << endl;
        cout << "size = " << booktable->size() << endl;
    }
    delete booktable;
  }
  else{
    cout << "Incorrect usage." << endl;
    cout << "Usage: a2indexer <cachesize>" << endl;
    cout << "<cachesize> is optional" << endl;
  }
  return 0;
}
