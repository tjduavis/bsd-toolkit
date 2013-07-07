/*********************************************************/
/*                                                       */
/*   Written by: Timothy Duavis                          */
/*   Student Number: 019-261-049                         */
/*   Section: A/B                                        */ 
/*   Assignment #1 Version 1.0                           */
/*   The program demonstrates a doubly linked list,      */ 
/*   that appends, inserts, gets data, removes nodes,    */
/*   moves current node, and finds a specific item.      */
/*                                                       */
/*   Course: BTP500-Fall 2006                            */
/*   Professor: Catherine Leung                          */
/*                                                       */
/*                                                       */
/*********************************************************/

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
  CList(const CList<T>& src);
  ~CList();
  CList<T>& operator=(const CList<T>& rhs);
  void insert(const T& data);
  void append(const T& data);
  bool remove();
  const T& curr() const;
  bool isempty() const;
  void goFwd();
  void goBack();
  bool get(T passback[], int max) const;
  bool find(const void* key, bool (*match)(const void*,const T&));
};

/**
 * CList constructor
 */
template <class T>
CList<T>::CList() : curr_(NULL) { };

/**
 * CList copy constructor
 */
template <class T>
CList<T>::CList(const CList<T>& src) {
	Node<T>* startNode_ = src.curr_;
	Node<T>* tempNode_ = src.curr_;
	curr_ = NULL;
	insert(startNode_->data_);
	tempNode_ = tempNode_->next_;
	while (tempNode_ != startNode_) {
		insert(tempNode_->data_);
		tempNode_ = tempNode_->next_;
	}
	goFwd();
};

/**
 * CList destructor
 */
template <class T>
CList<T>::~CList(){
	while (remove()) { }
};

/**
 * CList assignment operator
 */
template <class T>
CList<T>& CList<T>::operator=(const CList<T>& rhs) {
	if (this != &rhs) {
		Node<T>* startNode_ = rhs.curr_;
		Node<T>* tempNode_ = rhs.curr_;
		curr_ = NULL;
		insert(startNode_->data_);
		tempNode_ = tempNode_->next_;
		while (tempNode_ != startNode_) {
			insert(tempNode_->data_);
			tempNode_ = tempNode_->next_;
		}
	}
	goFwd();
	return *this;
};

/**
 * The function inserts data into the link list such that 
 * the new node placed between the node before curr_ (curr_'s previous node) and curr_
 * curr_ points at newly added node.
 * NOTE: function discription written by Catherine Leung
 */
template <class T>
void CList<T>::append(const T &data) {
	Node<T>* newNode_= new Node<T>;
	newNode_->data_ = data;
	if (!isempty()) {
		if (curr_ != curr_->next_ && curr_ != curr_->prev_) {
			newNode_->next_ = curr_;
			newNode_->prev_ = curr_->prev_;
			curr_->prev_->next_ = newNode_;
			curr_->prev_ = newNode_;
			curr_= newNode_;
		} else {
			newNode_->next_ = newNode_->prev_ = curr_;
			curr_->next_ = newNode_;
			curr_ = newNode_;
		}
	} else {
		curr_ = newNode_;
		curr_->next_ = curr_->prev_ = newNode_;
	}
};

/**
 * The function inserts data into the link list such that 
 * the new node placed between curr_ and the node after curr_ (curr_'s next node).
 * curr_ points at newly added node.
 * NOTE: function discription written by Catherine Leung
 */
template <class T>
void CList<T>::insert(const T &data) {
	Node<T>* newNode_= new Node<T>;
	newNode_->data_ = data;
	if (!isempty()) {
		if (curr_ != curr_->next_) {
			newNode_->next_ = curr_->next_;
			newNode_->prev_ = curr_;
			curr_->next_->prev_ = newNode_;
			curr_->next_ = newNode_;
			curr_ = newNode_;
		} else {
			newNode_->next_ = curr_;
			newNode_->prev_ = curr_;
			curr_->next_ = curr_->prev_ = newNode_;
			curr_ = newNode_;
		}
	} else {
		curr_= newNode_;
		curr_->next_ = curr_->prev_ = newNode_;
	}
};

/**
 * The function removes the node curr_ is pointing at. curr_ points at
 * the node after curr_ (or NULL if curr_ was last node in list).  
 * Function returns true if node was successfully removed, 
 * false otherwise (when list is empty for example)
 * NOTE: function discription written by Catherine Leung
 */
template <class T>
bool CList<T>::remove(){
	if (curr_) {
		Node<T>* tempNode_ = curr_;
		if (curr_->next_ != curr_) {
			curr_->next_->prev_ = curr_->prev_;
			curr_->prev_->next_ = curr_->next_;
			curr_ = curr_->next_;
		} else {
			curr_ = NULL;
		}
		delete tempNode_;
		return true;
	} else
		return false;
};

/**
 * The function return the data at the node curr_ is pointing at.
 * If curr is NULL, function returns a default instance of the unknown data type
 * NOTE: function discription written by Catherine Leung
 */
template <class T>
const T& CList<T>::curr() const {
	if (!isempty())
		return curr_->data_;
	else {
		Node<T>* defaultNode_ = NULL;
		return defaultNode_->data_;
	}
};

/**
 * This function returns true if the list is empty, false otherwise; therefor
 * the CList is empty when curr_ node file is NULL.
 * NOTE: function discription written by Catherine Leung, modified by Timothy Duavis
 */
template <class T>
bool CList<T>::isempty() const {
	if (curr_) 
		return false;
	else
		return true;
};

/**
 * This function advances curr_ to point at the node after 
 * the one it is currently pointing at which is the address of
 * the curr_'s next_ pointer member file.
 * NOTE: function discription written by Catherine Leung, modified by Timothy Duavis
 */
template <class T>
void CList<T>::goFwd() {
	curr_ = curr_->next_;
};

/**
 * This function changes curr_ to point at the node before 
 * the one it is currently pointing at, which is the address of
 * the curr_'s prev_ pointer member file.
 * NOTE: function discription written by Catherine Leung, modified by Timothy Duavis
 */
template <class T>
void CList<T>::goBack() {
	curr_ = curr_->prev_;
};

/**
 * The function copies the data in the nodes starting at curr_
 * to passback at most, 
 * Only copy max nodes at most.  
 * Thus if there are 10 nodes and max is 9, only the first 9 nodes will be copied.  
 * curr_ does not change during this process, 
 * it still points at the node it use to point at.
 * NOTE: function discription written by Catherine Leung
 */
template <class T>
bool CList<T>::get(T passback[], int max) const {
	int counter = 0;
	bool succ = false;
	Node<T>* tempNode_ = curr_;
	for (counter = 0; counter < max; counter++) {
		passback[counter] = tempNode_->data_;
		tempNode_ = tempNode_->next_;
	}
	if (counter == max) 
		succ = true;
	return succ;
};

/**
 * The function finds key, which is the address of the thing that we are searching
 * match is the address of a function that will return true if its second argument "matches" the first and false otherwise.
 * You may assume that at most one node will "match" the key.
 * (YOU DO NOT WRITE THIS FUNCTION, just call it to compare key against a value in the node)
 * function assigns curr_ to point at the node with the matching key if it is found.
 * If no match is found, curr_ does not change positions.
 * return true if match is found, false otherwise.
 * NOTE: function discription written by Catherine Leung, modified by Timothy Duavis
 */
template <class T>
bool CList<T>::find(const void* key, bool (*match)(const void*,const T&)) {
	bool found = false;
	Node<T>* startNode_ = curr_;
	Node<T>* tempNode_ = curr_;
	if (match(key,curr_->data_)) 
		found = true;
	else {
		tempNode_ = tempNode_->next_;
		while (tempNode_ != startNode_) {
			if (match(key,tempNode_->data_)) {
				found = true;
				curr_ = tempNode_;
			}
			tempNode_ = tempNode_->next_;
		}
	}
	return found;
};