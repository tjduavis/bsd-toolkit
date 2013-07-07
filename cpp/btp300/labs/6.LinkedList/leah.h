/* A Linked List for Screen Displays
 * By: Leah Spontaneo
 * Screen.h
 * Oct 12 2005
 */

 extern "C"
 {
     #include "dtio.h"
 }

class Field {
	int row;
	int col;
	int width;
	char* st;
	void init(const Field&);
	 
	public:
    Field();
    Field(int, int, int, const char*);
    Field(const Field&);
    ~Field();
    Field& operator=(const Field&);
    void display();
    Field* clone();
};

class Node {
	Field _data;
    Node* _next;
    
    public:
    Node(Field d, Node* n) : _data(d), _next(n) {}
    Node* next() const { return _next;}
    Field data() const { return _data;}
    void setNext(Node* p) { _next = p;}
};

class Screen {
	Node* first;
	Node* last;
	int length;
	void init(const Screen&);
	
	public:
	Screen();
	Screen(const Screen&);
	~Screen();
	Screen& operator=(const Screen&);
	int add(int r, int c, int w, const char* s);
	void display(bool clear);
};