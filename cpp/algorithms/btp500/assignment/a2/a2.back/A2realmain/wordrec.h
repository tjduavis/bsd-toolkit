#ifndef WORDREC_H
#define WORDREC_H
#include <iostream>
using namespace std;
const int numfiles=8;
const char filenames[numfiles][20]={"advsh12.txt","bskrv11.txt",
    "lcrfx10.txt","lostw10.txt","memho11.txt","rholm10.txt",
    "totam10.txt","ttmgd10.txt"
};
class WordRec{
  friend ostream& operator<< (ostream& os, const WordRec& wr);
  char word_[60];
  char file_[numfiles][20];
  int numoccur_[numfiles];
public:
  WordRec();
  WordRec(char* word);
  const char* key() const{return word_;}
  void increase(int index){
    numoccur_[index]++;
  }
  int total() const;
};
ostream& operator << (ostream& os, const WordRec& wr);
#endif
