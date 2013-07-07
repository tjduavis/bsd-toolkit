struct Node{
  int data_;
  Node* left_;
  Node* right_;
  Node(int v){
    data_=v;
    left_=right_=NULL;
  }
};

class BST{
  Node* root_;
  void InsertR(int v,Node*& subtreeroot);
public:
  BST(){root_=NULL;}
  void Insert(int v);
  void InsertR(int v){
    InsertR(v,root_);
  }
  const Node* Search(int v);
};
/*this function inserts a new node with v into the BST*/
void BST::Insert(int v){
  if(!root_)
    root_=new Node(v);
  else{
    Node* curr=root_;  //this variable points to the node I'm comparing v to
    bool found=false;  //set to true when I find the node where data will go
    while(!found){
      if(v < curr->data_){  //v goes into left subtree
        if(curr->left_){  //left subtree is not empty so compare that
                          //value to v;
          curr=curr->left_;
        }
        else{
          found=true;
          curr->left_=new Node(v);
        }
      }
      else{
        if(curr->right_){  //left subtree is not empty so compare that
                          //value to v;
          curr=curr->right_;
        }
        else{
          found=true;
          curr->right_=new Node(v);
        }
      }

    }
  }
}

/*this function inserts v into the subtree at the root
  subtreeroot*/
void BST::InsertR(int v,Node*& subtreeroot){
  if(!subtreeroot){   //subtree is empty
    subtreeroot=new Node(v);
  }
  else{
    if(v < subtreeroot->data_)
      InsertR(v,subtreeroot->left_);
    else
      InsertR(v,subtreeroot->right_);
  }
}
/*function returns address of node with v or NULL if not found*/
const Node* Search(int v){
  Node* curr=root_;
  while(curr && v!=curr->data_){
    if(v<curr->data_)
      curr=curr->left_;
    else
      curr=curr->right_;
  }
  return curr;
}

const Node* BST::SearchR(int v){

}

const Node* BST::SearchR(int v,const Node* subtreeroot){
  Node* rc;
  if(subtreeroot==NULL){
    rc=NULL;
  }
  else{
    if(v==subtreeroot->data_)
      rc=subtreeroot;
    else if(v < subtreeroot->data_)
      rc=SearchR(v,subtreeroot->left_);
    else
      rc=SearchR(v,subtreeroot->right_);
  }
  return rc;
}

