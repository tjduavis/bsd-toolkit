void OrdList::OrdInsert(int v){
  Node* nn=new Node;
  nn->data_=v;
  nn->next_=NULL;
  if(!start_){  //start pointer is NULL, list is empty
    start_=nn;
  }
  else{
    Node* curr=start_;  //pointer to node I'm looking at
    Node* prev=NULL;
    while(curr  && v > curr->data_){
      prev=curr;
      curr=curr->next_;
    }
    if(prev){
      nn->next_=curr;
      prev->next_=nn;
    }
    else{
      nn->next_=curr;
      start_=nn;
    }
  }
  
}
#include <ctype.h>
void Reorder(char s[]){
  Stack upper;
  Queue lower;
  Stack nonalpha;
  for(int i=0;s[i]!='\0';i++){
    if(s[i]>='A' && s[i]<='Z'){  //upper case
      upper.push(s[i]);
    }
    else if(s[i]>='a' && s[i]<='z'){ //lower case
      lower.enqueue(s[i]);
    }
    else{  //nonalpha
      nonalpha.push(s[i]);
    }
  }
  int j=0;
  while(!nonalpha.isempty())
    s[j++]=nonalpha.pop();
  while(!lower.isempty())
    s[j++]=lower.dequeue();
  while(!upper.isempty())
    s[j++]=upper.pop();
}

bool isPalindrome(const char* s,int len){
  bool rc;
  if(len<=1)
    rc=true;
  else{
    if(s[0] != s[len-1])
      rc=false;
    else{
      rc=isPalindrome(s+1,len-2);
    //  rc=isPalindrome(&(s[1]),len-2);
    }
  }
}
