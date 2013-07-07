/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.1                                        */
/*   The preliminary main is written in 2 files.         */
/*   This is the second.  Don't run until you            */
/*   have created the data file with the other program   */
/*                                                       */
/*   This program will allow you to search for a word    */
/*   If found it will print out how many times that      */
/*   word occured.  If not it will print out that it     */
/*   was not found                                       */
/*                                                       */
/*   BTP500-Fall 2006                                   */
/*                                                       */
/*   A reminder that all template code must be placed in */
/*   header file. You will have trouble compiling and    */
/*   linking otherwise.                                  */
/*   V1.1 added code to make it test cache versions      */
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
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
  char word[60];
  int i;
  if(argc!=2){
    cout << "Usage: searcher <word>" << endl;
  }
  else{
    for(i=0;argv[1][i]!='\0';i++){
      word[i]=tolower(argv[1][i]);
    }
    word[i]='\0';
    WordRec holder;
    bool found;
    #if TESTCASE == TPERMHASH
    PermHash<WordRec> booktable("books.dat",0,0);
    #else
    PCacheHash<WordRec> booktable("books.dat",0,0,0.05,3);
    #endif
    found=booktable.find(word,holder);
    if(found){
      cout << holder << endl;
    }
    else{
      cout << word << " was not part of any of the files" << endl;
    }
  }
}
