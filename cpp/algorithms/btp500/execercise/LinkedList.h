template <class T>
struct Node {
    T data;
    Node<T>* next;
};

template <class T>
class LinkedList {
    Node<T>* startingNode;
    public:
        LinkedList();
        void insert(const T& theData);
        void append(const T& theData);
        void removeFront();
        void removeLast();
        void print() const;
        ~LinkedList();
};

/*creates an empty linked list*/
template <class T>
LinkedList<T>::LinkedList() {
    startingNode = NULL;
}

/*adds a node to the front of the list*/
template <class T>
void LinkedList<T>::insert(const T& theData) {
    Node<T>* node = new Node<T>;
    node->data = theData;
    node->next = startingNode;
    startingNode = node;
}

/*adds a node to the end of the list*/
template <class T>
void LinkedList<T>::append(const T& theData) {
    Node<T>* node = new Node<T>;
    node->data = theData;
    node->next = NULL;
    
    if (startingNode) {
        Node<T>* current = startingNode;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }
    else {
        startingNode = node;
    }
}

/*removes first node in list*/
template <class T>
void LinkedList<T>::removeFront() {
    if (startingNode) {
        Node<T>* currentNode = startingNode;
        startingNode = startingNode->next;
        delete currentNode;
    }
}

/*removes first node in list*/
template <class T>
void LinkedList<T>::removeLast(){
    if (startingNode) {
        Node<T>* currentNode = startingNode;
        if (currentNode->next) {
            while (currentNode->next) {
                currentNode = currentNode->next;
            }
            delete currentNode->next;
            currentNode->next = NULL;    
        }
        else {
            delete currentNode;
            startingNode = NULL;   
        }
    }
}


/*prints the list from start to end.  Assume T can be outputted using
  << operator and an instance of ostream*/
template <class T>
void LinkedList<T>::print() const {
  for (Node<T>* currentNode = startingNode; currentNode; currentNode = currentNode->next) {
    cout << currentNode->data << endl;
  }
}

/*deallocates all memory for the nodes of the list*/
template <class T>
LinkedList<T>::~LinkedList() {
  Node<T>* currentNode = startingNode;
  Node<T>* nextNode;
  while (currentNode) {
    nextNode = currentNode->next;
    delete currentNode;
    currentNode = nextNode;
  }
}

