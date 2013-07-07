void OrdList::OrdInsert(int v){
  Node* nn=new Node;
  nn->data_=v;
  nn->next_=NULL;
  if(!start_){   //if list is empty
    start_=nn;
  }
  else{
    Node* curr=start_;  //a pointer to node that will be just in front of nn
    Node* prev=NULL;  //a pointer to node that will be just behind nn
    bool found=false;
    while(curr && !found){
      if(v < curr->data_)
        found=true;
      else{
        prev=curr;
        curr=curr->next_;
      }
    }
    if(prev==NULL){
      nn->next_=start_;
      start_=nn;
    }
    else{
      nn->next_=curr;
      prev->next_=nn;
    }
  }
}
#include <ctype.h>
void Reorder(char s[]){
  Queue upper;
  Stack nonalpha, lower;
  for(int i=0;s[i]!='\0';i++){
    if(s[i]>='A' && s[i]<='Z'){//upper case
      upper.enqueue(s[i]);
    }
    else if(s[i]>='a' && s[i]<='z'){
      lower.push(s[i]);
    }
    else{
      nonalpha.push(s[i]);
    }
  }
  int j=0;
  while(!upper.isempty())
    s[j++]=upper.dequeue();
  while(!nonalpha.isempty())
    s[j++]=nonalpha.pop();
  while(!lower.isempty())
    s[j++]=lower.pop();
}

bool isPalindrome(const char* s,int len){
  bool rc;
  if(len<=1){
    rc=true;
  }
  else{
    if(s[0]!=s[len-1])
      rc=false;
    else{
      rc=isPalindrome(s+1 ,len-2);
     // rc=isPalindrome(&(s[1]) ,len-2);
    }
  }
  return rc;
}
