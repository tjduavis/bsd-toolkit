/* screen.cpp
 * Cesar Oliveira
 * BTP300a
 * November 01, 2005 */

#include "cesar.h"

Field::Field(int _row, int _col, int _width, const char* s) : row(_row), column(_col), str(NULL) {
        // Checks if width stays within the screen limits
        width = column + _width > dtioColumns() ? dtioColumns() : _width;
        // allocates memory the c-style way.
        str = (char*)malloc(strlen(s) + 1);
        strcpy(str, s);
}

void Field::display(void) {
        dtioDisplay(str, row, column, width);
}

Field* Field::clone(void) {
        Field *copy = (Field*)malloc(sizeof(Field)); // creates area in memory for this copy
        *copy = *this;   // calls copy constructor
        return copy;
}

Field::~Field() {
        free(str);
        str = NULL;
}

Field& Field::operator=(const Field& source) {
        if (&source != this) {
                width = source.width;
                column = source.column;
                row = source.row;
                str = (char*)malloc(strlen(source.str) + 1);
                strcpy(str, source.str);
        }
        return *this;
}

Field::Field(const Field& source) {
        // copy and pasted from the assignment operator
        width = source.width;
        column = source.column;
        row = source.row;
        str = (char*)malloc(strlen(source.str) + 1);
        strcpy(str, source.str);
}

int Screen::add(int r, int c, int w, const char* s) {
        /* To add a new link list, we must do the following :
         * Create new space in memory
         * Go to the last link list item and have it point it our link list (through the node)
         * Have the class know that we are the last item in the list
         */
        Field *item = new Field(r,c,w,s);      // Create a new field object and its node
        Node *pointer = new Node(*item, NULL); // The last node in the link list should ALWAYS point to NULL
        // checks if this is the first item on the linklist
        if (first)
                last->set(pointer);  // sets the last node to point to the new item
        else
                first = pointer;     // sets the first link list element
        last = pointer;         // Tells the class we are the last item in the list
        ++num;
        return num;
}

void Screen::display(bool clear) {
        Node* p;
        if (clear) dtioClear();
        for (p = first; p; p = p->next())
                p->data().display();
}

Screen::Screen(const Screen& source) {
        Node *p = source.first;    // Go through each Node and field untill you hit NULL
        first = NULL;
        last = NULL;
        while (p) {
                // Create a new node and copy over a copy of the field
                Node *newnode = new Node(*p->data().clone(), NULL);
                if (first)
                        last->set(newnode);
                else
                        first = newnode;
                last = newnode;
                p = p->next(); // Goto the next node, if there is one.
        }
}

Screen::~Screen(void) {
        Node *p = first;
        while (p) {
                first = first->next();
                delete(p);
                p = first;
        }
}

void Screen::operator=(const Screen& source) {
        if (this != &source) {
                Node *p = source.first;
                first = NULL;
                last = NULL;
                while (p) {
                        Node *newnode = new Node(*p->data().clone(), NULL);
                        if (first)
                                last->set(newnode);
                        else
                                first = newnode;
                        last = newnode;
                        p = p->next();
                }
        }
}
