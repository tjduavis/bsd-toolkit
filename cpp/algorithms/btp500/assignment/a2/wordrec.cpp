#include "wordrec.h"
WordRec::WordRec(){
  strcpy(word_,"");
  for(int i=0;i<numfiles;i++){
    numoccur_[i]=0;
    strcpy(file_[i],filenames[i]);
  }
}
WordRec::WordRec(char* word){
  strcpy(word_,word);
  for(int i=0;i<numfiles;i++){
    numoccur_[i]=0;
    strcpy(file_[i],filenames[i]);
  }
}
ostream& operator << (ostream& os, WordRec& wr){
  os << "Word: " << wr.word_ << endl;
  for(int i=0;i<numfiles;i++){
    if(wr.numoccur_!=0)
      os <<  wr.file_[i] << " --> " << wr.numoccur_[i] << endl;    
  }
  os << endl;
  return os;
}
