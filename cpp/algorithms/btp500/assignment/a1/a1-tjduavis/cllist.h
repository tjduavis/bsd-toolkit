/* BTP500 Q2 */

template <class T>
struct Node{
  T data_;
  Node<T>* next_;
  Node<T>* prev_;
};

template <class T>
class CList{
  Node<T>* curr_;
  public:
  CList();
  ~CList();
  void insert(const T& data);
  void append(const T& data);
  bool remove();
  const T& curr() const;
  
  //returns true if list is empty, false otherwise
  bool isempty() const;
  
  //advances curr_ to point at the node after 
  //the one it is currently pointing at.
  void goFwd();
  
  //changes curr_ to point at the node before 
  //the one it is currently pointing at.
  void goBack();
  
  //function copies the data in the nodes starting at curr_ 
  //to passback at most, 
  //Only copy max nodes at most.  
  //Thus if there are 10 nodes and max is 9, only the first 9 nodes will be copied.  
  //curr_ does not change during this process, 
  //it still points at the node it use to point at.
  bool get(T passback[], int max) const;

  //key is the address of the thing that we are searching
  //match is the address of a function that will return true if its second argument "matches" the first and false otherwise.   
  //You may assume that at most one node will "match" the key.  
  //(YOU DO NOT WRITE THIS FUNCTION, just call it to compare key against a value in the node)
  //function assigns curr_ to point at the node with the matching key if it is found.  
  //If no match is found, curr_ does not change positions.
  //return true if match is found, false otherwise.  
  bool find(const void* key, bool (*match)(const void*,const T&));

};

/**
 * constructor
 */
CList<class T>::CList() {
};

/**
 * destructor
 */
CList<class T>::~CList(){
};

/**
 * function inserts data into the link list such that 
 * the new node placed between the node before curr_ (curr_'s previous node) and curr_ 
 */
CList<class T>::append(const T &data) {
};

/**
 * function inserts data into the link list such that 
 * the new node placed between curr_ and the node after curr_ (curr_'s next node) 
 */
CList<class T>::insert(const T &data) {
};

/**
 * removes the node curr_ is pointing at. curr_ points at
 * the node after curr_ (or NULL if curr_ was last node in list).  
 * Function returns true if node was successfully removed, 
 * false otherwise (when list is empty for example)
 */
CList<class T>::bool remove(){
};

/**
 * return the data at the node curr_ is pointing at.
 * If curr is NULL, function returns a default instance of the unknown data type
 */
CList<class T>::const T& curr() const {
};