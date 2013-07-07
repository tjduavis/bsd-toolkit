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
/*   NOTE:  If you run this program more than twice, all */
/*          the counts will double so you need to remove */
/*          the old data file before running this again  */
/*                                                       */
/*   BTP500-Fall 2006                                    */
/*                                                       */
/*   A reminder that all template code must be placed in */
/*   header file. You will have trouble compiling and    */
/*   linking otherwise.                                  */
/*                                                       */
/*   On the computers in the school labs, the program    */
/*   can take about 2 min to run, IF you find that your  */
/*   this main takes any longer, you probably have a bug */
/*   of some sort                                        */
/*   v1.1 changed code to use cachecap as specified      */
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
#include <fstream>
using namespace std;

const int MAXWORDS = 20000;
const double CACHECAP = 0.05;    //these are used only if you are testing
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
int main(void){  
  ifstream fs;
  char word[80];
  int numunique=0;
  double numsec;
  #if TESTCASE == TPERMHASH
  PermHash<WordRec> booktable("books.dat",MAXWORDS,OVERAMT);
  #else
  PCacheHash<WordRec> booktable("books.dat",MAXWORDS,OVERAMT,CACHECAP,NUMBUCKETS);
  #endif
  WordRec holder;
  cout << "Table created, file processing begins" << endl;
  bool swtch = false;
  for(int i=0;i<numfiles;i++){
    fs.open(filenames[i]);
    cout << "Started Processing: " << filenames[i] << endl;
	int counter = 0;
    while(getnext(fs,word)){
      WordRec tmp(word);

	  /*if (strcmp(word,"aback") == 0) {
		  cout << "Start of Loop " << word << endl;
		  cout << "*********************************************" << endl;
		  cout << "holder = " << endl;
		  cout << holder << endl;
		  cout << "*********************************************" << endl;
		  cout << "temp = " << endl;
		  cout << tmp << endl;
		  cout << "*********************************************" << endl;
		  swtch = true;
	  }*/

	  if(booktable.find(word,holder)){
        holder.increase(i);
        booktable.update(holder);
		// if (strcmp(word,"aback") == 0 || swtch) cout << "\t" << "in a ****************" << endl;
		// getchar();
      }
      else if(numunique < MAXWORDS){
        numunique++;
        tmp.increase(i);
        booktable.update(tmp);
		// if (strcmp(word,"aback") == 0 || swtch) cout << "\t" << "in b ***************" << endl;
      }/*else if*/

	  /*if (strcmp(word,"aback") == 0) {
		  cout << "numunique (" << numunique << ") < " << "(" << MAXWORDS << ") " << "MAXWORDS" << endl;
		  printf("press enter to continue"); getchar();
	  }
	  swtch = false;*/

    }/*while*/
    fs.clear();
    fs.close();
    cout << "Finished Processing: " << filenames[i] << endl;
  }
  cout << endl;
  cout << "********************************************" << endl;

  cout << "Cap (correct value 27011): " << booktable.cap() << endl;
  cout << "Max (correct value 20000): " << booktable.max() << endl;
  cout << "Size (correct value 19704): " << booktable.size() << endl;
  cout << "********************************************" << endl;
  cout << "Removing the words gutenberg and project" << endl;
  booktable.remove("gutenberg");
  booktable.remove("project");
  cout << "Cap (correct value 27011): " << booktable.cap() << endl;
  cout << "Max (correct value 20000): " << booktable.max() << endl;
  cout << "Size (correct value 19702): " << booktable.size() << endl;

}
