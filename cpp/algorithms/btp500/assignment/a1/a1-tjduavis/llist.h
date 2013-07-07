template <class T>
struct Node{
  T data_;
  Node<T>* next_;
};

template <class T>
class LList{
  Node<T>* start_;
public:
  LList();
  void Insert(const T& data);
  void Append(const T& data);
  void RMFront();
  void Print() const;
  ~LList();
};

/*creates an empty linked list*/
template <class T>
LList<T>::LList(){
  start_=NULL;
}

/*adds a node to the front of the list*/
template <class T>
void LList<T>::Insert(const T& data){
  Node<T>* nn=new Node<T>;
  nn->data_=data;
  nn->next_=start_;
  start_=nn;
}

/*adds a node to the end of the list*/
template <class T>
void LList<T>::Append(const T& data){
  Node<T>* nn=new Node<T>;
  nn->data_=data;
  nn->next_=NULL;
  if(start_){
    Node<T>* curr=start_;
    while(curr->next_){
      curr=curr->next_;
    }
    curr->next_=nn;
  }
  else{
    start_=nn;
  }
}

/*removes first node in list*/
template <class T>
void LList<T>::RMFront(){
  if(start_){
    Node<T>* curr=start_;
    start_=start_->next_;
    delete curr;
  }
}

/*removes first node in list*/
template <class T>
void LList<T>::RMLast(){
  if(start_){
    Node<T>* curr=start_;
    if(curr->next_){
      while(curr->next_->next_){
        curr=curr->next_;
      }
      delete curr->next_;
      curr->next_=NULL;    
    }
    else{
      delete curr;
      start_=NULL;   
    }
  }
}


/*prints the list from start to end.  Assume T can be outputted using
  << operator and an instance of ostream*/
template <class T>
void LList<T>::Print() const{
  for(Node<T>* curr=start_;curr;curr=curr->next_){
    cout << curr->data_ << endl;
  }
}

/*deallocates all memory for the nodes of the list*/
template <class T>
LList<T>::~LList(){
  Node<T>* curr=start_;
  Node<T>* next;
  while(curr){
    next=curr->next_;
    delete curr;
    curr=next;
  }
  
}

