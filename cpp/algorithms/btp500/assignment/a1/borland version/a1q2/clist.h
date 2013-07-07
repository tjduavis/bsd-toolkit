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
 * constructor
 */
template <class T>
CList<T>::CList() : curr_(NULL) { };

/**
 * copy constructor
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
 * destructor
 */
template <class T>
CList<T>::~CList(){
	while (remove()) { }
};

/**
 * assignment operator
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
 * function inserts data into the link list such that 
 * the new node placed between the node before curr_ (curr_'s previous node) and curr_
 * curr_ points at newly added node.
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
 * function inserts data into the link list such that 
 * the new node placed between curr_ and the node after curr_ (curr_'s next node).
 * curr_ points at newly added node.
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
 * removes the node curr_ is pointing at. curr_ points at
 * the node after curr_ (or NULL if curr_ was last node in list).  
 * Function returns true if node was successfully removed, 
 * false otherwise (when list is empty for example)
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
 * return the data at the node curr_ is pointing at.
 * If curr is NULL, function returns a default instance of the unknown data type
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
 * returns true if list is empty, false otherwise
 */
template <class T>
bool CList<T>::isempty() const {
	if (curr_) 
		return false;
	else {
		//printf("NULL == %d",curr_); getchar();
		return true;
	}
};

/**
 * advances curr_ to point at the node after 
 * the one it is currently pointing at.
 */
template <class T>
void CList<T>::goFwd() {
	curr_ = curr_->next_;
};

/**
 * changes curr_ to point at the node before 
 * the one it is currently pointing at.
 */
template <class T>
void CList<T>::goBack() {
	curr_ = curr_->prev_;
};

/**
 * function copies the data in the nodes starting at curr_
 * to passback at most, 
 * Only copy max nodes at most.  
 * Thus if there are 10 nodes and max is 9, only the first 9 nodes will be copied.  
 * curr_ does not change during this process, 
 * it still points at the node it use to point at.
 */
template <class T>
bool CList<T>::get(T passback[], int max) const {
	int i = 0;
	bool succ = false;
	Node<T>* tempNode_ = curr_;
	for (i = 0; i < max; i++) {
		passback[i] = tempNode_->data_;
		tempNode_ = tempNode_->next_;
	}
	if (i == max) 
		succ = true;
	return succ;
};

/**
 * key is the address of the thing that we are searching
 * match is the address of a function that will return true if its second argument "matches" the first and false otherwise.
 * You may assume that at most one node will "match" the key.
 * (YOU DO NOT WRITE THIS FUNCTION, just call it to compare key against a value in the node)
 * function assigns curr_ to point at the node with the matching key if it is found.
 * If no match is found, curr_ does not change positions.
 * return true if match is found, false otherwise.
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