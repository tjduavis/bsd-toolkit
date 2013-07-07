#include <iostream>
using namespace std;
struct Node{
  int data_;
  Node* right_;
  Node* left_;
  Node(){right_=left_=NULL;}
  Node(int v){
   data_=v;
   right_=left_=NULL;
  }
};

class BST{
  Node* root_;
  void InsertR(int v,Node*& subtreeroot);
  Node* InsertR2(int v,Node* subtreeroot);
  void Print(const Node* subtreeroot)const;
  const Node* SearchR(int v,const Node* subtreeroot);
  void Remove(int v, Node*& subtreeroot);
  void DestroyTree(Node*& subtreeroot);
public:
  ~BST();
  BST(){root_=NULL;}
  const Node* SearchR(int v);
  void InsertR(int v){InsertR(v,root_);}
  void InsertR2(int v){
     Node* from=InsertR2(v,root_);
     if(from)
       root_=from;
  }
  void Insert(int v);

  const Node* Search(int v);
  void Print()const;
  void Remove(int v){
    Remove(v,root_);
  }
};
/*returns root of subtree where v goes*/
Node* BST::InsertR2(int v,Node* subtreeroot){
  Node* rc=NULL;
  if(subtreeroot==NULL){
    rc=new Node(v);
  }
  else{
    Node* from;
    if(v < subtreeroot->left_->data_){
      from=InsertR2(v,subtreeroot->left_);
      if(from)
        subtreeroot->left_=from;
    }
    else{
      from=InsertR2(v,subtreeroot->right_);
      if(from)
        subtreeroot->right_=from;
    }
  }
  return rc;
}



/*function inserts v into the subtree who's root node is stored in 
subtreeroot*/
void BST::InsertR(int v,Node*& subtreeroot){
  if(subtreeroot == NULL){
    subtreeroot=new Node(v);
  }
  else{
    if(v < subtreeroot->left_->data_)
      InsertR(v,subtreeroot->left_);
    else
      InsertR(v,subtreeroot->right_);
  }
}

void BST::Insert(int v){
  if(!root_)
    root_=new Node(v);
  else{
    bool found=false;  //this flag is set to true after we do an insertion
    Node* curr=root_;
    while(!found){
      if(v < curr->data_){
        if(curr->left_)
          curr=curr->left_;
        else{
          found=true;
          curr->left_=new Node(v);
        }
      }
      else{
        if(curr->right_)
          curr=curr->right_;
        else{
          found=true;
          curr->right_=new Node(v);
        }
      }

    }
  }
}


const Node* BST::Search(int v){
  Node* rc=root_;
  while(rc  && rc->data_!=v){
    if(v<rc->data_ )
      rc=rc->left_;
    else
      rc=rc->right_;
  }
  return rc;
}

const Node* BST::SearchR(int v){
  return SearchR(v,root_);
}

const Node* BST::SearchR(int v,const Node* subtreeroot){
  const Node* rc;
  if(!subtreeroot || subtreeroot->data_==v)
    rc=subtreeroot;
  else
    if(v<subtreeroot->data_)
      rc=SearchR(v,subtreeroot->left_);
    else
      rc=SearchR(v,subtreeroot->right_);
  return rc;
}
void BST::Print()const{
  Print(root_);
}
/*function prints the data (inorder) in the tree with root subtreeroot*/
void BST::Print(const Node* subtreeroot)const{
  if(subtreeroot){
    Print(subtreeroot->left_);
    cout << subtreeroot->data_ << endl;
    Print(subtreeroot->right_);
  }
}

/* this function removes the value v from the tree with root
   subtreeroot*/
void BST::Remove(int v, Node*& subtreeroot){
  if(subtreeroot){
    if(v==subtreeroot->data_){
      Node* rm=subtreeroot;
      if(rm->left_ && rm->right_){
          //two children
          Node* is=rm->right_;      //inorder successor;
          Node* isparent=NULL;      //inorder successor's parent
          while(is->left_){
            isparent=is;
            is=is->left_;
          }
          if(isparent){
            isparent->left_=is->right_;  //note if is->right_ is NULL
                                         //then the pointer will just 
                                         //become NULL
            is->right_=rm->right_;
          }
          is->left_=rm->left_;
          subtreeroot=is;
          
      }
      else{
         if(!rm->left_ && !rm->right_){
           subtreeroot=NULL;   //no children
         }
         else if(rm->left_){
           subtreeroot=rm->left_;//only left child
         
         }
         else{
            subtreeroot=rm->right_;//only right child
         }
      }
      delete rm;
    }
    else if(v < subtreeroot->data_){
      Remove(v,subtreeroot->left_);
    }
    else{
      Remove(v,subtreeroot->right_);
    }
  }
}
BST::~BST(){
  DestroyTree(root_);
}

/*destroys the subtree at subtreeroot*/
void BST::DestroyTree(Node*& subtreeroot){
  if(subtreeroot){
    DestroyTree(subtreeroot->left_);
    DestroyTree(subtreeroot->right_);
    delete subtreeroot;
    subtreeroot=NULL;
  }
}


int main(void){
  BST T;
  T.Insert(10);
  T.Insert(3);
  T.Insert(9);
  T.Insert(12);
  T.Insert(18);
  T.Insert(11);
  T.Insert(7);
  T.Insert(2);
  T.Insert(6);
  T.Insert(8);
  T.Print();
  cout << "************" << endl;
  T.Remove(10);
  T.Print();
}
