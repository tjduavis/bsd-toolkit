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
int WordRec::total()const{
  int total=0;
  for(int i=0;i<numfiles;i++){
      total+=numoccur_[i];
  }
  return total; 
}
ostream& operator << (ostream& os,const WordRec& wr){
  os << "Word: " << wr.word_ << endl;
  for(int i=0;i<numfiles;i++){
    os << "  " <<  wr.file_[i] << " --> " << wr.numoccur_[i] << endl;    
  }
  os << "Total: " << wr.total() << endl;
  return os;
}
