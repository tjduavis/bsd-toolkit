#include <fstream>
#include <iostream>
using namespace std;


int main(void){
  fstream fs("binopentest.dat",ios::in|ios::out|ios::binary);
  int size;
  int nodata=false;
  if(!fs.fail()){
    cout << "file opened"  << endl;
    fs.seekg(0,ios::end);
    size=fs.tellg();
    fs.seekg(0,ios::beg);   //move cursor back to be beginning
    if(size==0)
      nodata=true;
  }
  else{
    cout << "file did not open " << endl;
    nodata=true;
    fs.clear();
    fs.open("binopentest.dat",ios::in|ios::out|ios::binary|ios::trunc);
  }
  if(nodata){
     cout << "create the file" << endl;
     fs.write((char*)&size,sizeof(int));
  }
  else{
     cout << "file there, process it" << endl;
  }
  
}
