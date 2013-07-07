#include <iostream>
using namespace std;

extern "C" {
        #include "dtio.h"
}

class Field {
        char* str;
        int row;
        int column;
        int width;
public :
        Field(int, int, int, const char* = NULL);  // Constructor
        ~Field();  // Destructor
        void display(void);
        Field* clone(void);
        // Copy constructors
        Field(const Field&);
        Field& operator=(const Field&);
};

class Node {
        Field _data;
        Node *_next;
public :
        Node(Field dat, Node* nx):_data(dat),_next(nx) { }
        inline Node* next(void) const { return _next; }
        inline Field data() const { return _data; }
        void set(Node *pointer) { _next = pointer; }    //link list points to a new value
};

class Screen {
        int num;       // number of link lists in the class
        Node *first;      // pointer to first link list
        Node *last;       // pointer to last link list
public :
        Screen(void):first(NULL), last(NULL), num(0) { };
        int add(int, int, int, const char*);
        void display(bool = false);
        Screen(const Screen&);
        ~Screen();
        void operator=(const Screen&);
};
