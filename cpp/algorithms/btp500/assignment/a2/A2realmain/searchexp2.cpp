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
/*   Usage:  searchexp2 <numberofsearch> <cachesize>     */
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
#include <stdio.h>
#include <ctype.h>
#include <iostream>
using namespace std;
class WordStat{
  char* word_;
  int count_;
  double relfreq_;
public:
  WordStat(){
    word_=NULL;
    count_=0;
  }
  void Add(const char* w,int count){
      word_=new char[strlen(w)+1];
      strcpy(word_,w);
      count_=count;
      relfreq_=0;
  }
  ~WordStat(){
    delete [] word_;
  }
  double setpercent(int total,double percenttotal){
    relfreq_=((double)count_/(double)total)+percenttotal;
    return relfreq_;
  }
  const char* word()const{return word_;}
  int count()const{return count_;}
  double relfreq() const{return relfreq_;}
};

/*The following is the code for a random number generator that will 
  generate a number between 0 and max int.  Code for this is adapted
  from the random number generator found in [Law and Kelton, 1991].  
  it is based on Marse and Robert's portable Fortran generator.

  [Law and Kelton, 1991] Averill M. Law and W. David Kelton, 
  "Simulation Modeling & Analysis, Second Edition", McGraw Hill 1991, pg 455
*/


#define MODLUS 2147483647
#define MULT1       24112
#define MULT2       26143
/*note don't use stream 0.*/
static long zrng[] = { 0,
 1973272912, 281629770,  20006270,1280689831,2096730329,1933576050,
 913566091, 246780520,1363774876, 604901985,1511192140,1259851944,
 824064364, 150493284, 242708531,  75253171,1964472944,1202299975,
 233217322,1911216000, 726370533, 403498145, 993232223,1103205531,
 762430696,1922803170,1385516923,  76271663, 413682397, 726466604,
 336157058,1432650381,1120463904, 595778810, 877722890,1046574445,
  68911991,2088367019, 748545416, 622401386,2122378830, 640690903,
1774806513,2132545692,2079249579,  78130110, 852776735,1187867272,
1351423507,1645973084,1997049139, 922510944,2045512870, 898585771,
 243649545,1004818771, 773686062, 403188473, 372279877,1901633463,
 498067494,2087759558, 493157915, 597104727,1530940798,1814496276,
 536444882,1663153658, 855503735,  67784357,1432404475, 619691088,
 119025595, 880802310, 176192644,1116780070, 277854671,1366580350,
1142483975,2026948561,1053920743, 786262391,1792203830,1494667770,
1923011392,1433700034,1244184613,1147297105, 539712780,1545929719,
 190641742,1645390429, 264907697, 620389253,1502074852, 927711160,
 364849192,2049576050, 638580085, 547070247
};

double lkrand(int stream){
  long zi, lowprd, hi31;
  zi = zrng[stream];
  lowprd = (zi & 65535) * MULT1;
  hi31 = (zi >> 16) * MULT1 + (lowprd >> 16);
  zi = ((lowprd & 65535)-MODLUS)+((hi31 & 32767) << 16)+(hi31 >> 15);
  if (zi < 0) {    zi += MODLUS;  }
  lowprd = (zi & 65535) * MULT2;
  hi31 = (zi >> 16) * MULT2 + (lowprd >> 16);
  zi = ((lowprd & 65535)-MODLUS)+((hi31 & 32767) << 16)+(hi31 >> 15);
  if (zi < 0) {    zi += MODLUS;  }
  zrng[stream] = zi;
  return ((zi >> 7 | 1) + 1)/16777216.0;
}
void randst(long zset, int stream){
  zrng[stream] = zset;
}
long randgt(int stream){
  return zrng[stream];
}
/*code above from [Law and Kelton, 1991] see above code for reference*/

/*this function chooses a word based on its relative frequency
/*the more often a word occurs, the more likely it is chosen*/
int GetRand(const WordStat searchwords[],int numsearchwords){
  double rv=lkrand(1);   //get a random number 1 means from first stream
  int idx=-1;
  for(int i=0;i<numsearchwords && idx==-1;i++){
    if(rv<searchwords[i].relfreq())
      idx=i;
  }
  if(idx==-1)
    idx=0;
  return idx;
}

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
    cout << "Usage: searchexp2 <numberofsearches> <cachesize>" << endl;
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
      unsigned int totalwords=0;
      for(i=0;fscanf(fs,"%s %d\n",&word,&count)==2;i++){
         searchwords[i].Add(word,count);
         totalwords+=count;
      }
      numsearchwords=i;
      double runningpercent=0;
      /*calculate a running relative fequency of words and store it in the object*/
      for(i=0;i<numsearchwords;i++){
        runningpercent=searchwords[i].setpercent(totalwords,runningpercent);
      }
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
        randval=GetRand(searchwords,numsearchwords);
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
