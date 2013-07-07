/*************************************************************************\
* File: a4test.cpp                                                        *
* Originally written by Evan Weaver 23 Nov 2004                           *
* Version 1.2                                                             *
* Updates by Chris Szalwinski                                             *
* Nov 29 2005                                                             *
* Updated 25 Nov 2004 - changed length of 4th field to fit inside the box *
*                       and changed the way the prompt comes out in       *
*                       helppick() to improve appearance.                 *
*                                                                         *
* This is a test program for the classes in BTP300's fourth assignment.   *
* You should compile this program with your dtio routines and classes.    *
* For example,                                                            *
*     bcc32 a4test.cpp dtio.c Screen.cpp                      (Borland)   *
*     c++ -o a4test a4test.cpp dtio.c Screen.cpp -lcurses     (AIX)       *
*     cc -c dtio.c                                            (Linux)     *
*      c++ -o a4test a4test.cpp Screen.cpp dtio.o -lncurses               *
* will probably work for you.                                             *
*                                                                         *
* If you programmed the region class, either put #define DID_REGION in    *
* Screen.h, or else compile with a switch to predefine the name           *
* DID_REGION (e.g. c++ -DDID_REGION ... in AIX).                          *
*                                                                         *
* Note that this program cannot verify that your routines are correct -   *
* you must run the program and observe whether or not it is working       *
* correctly.                                                              *
*                                                                         *
* In particular, there are many little variations that are not tested but *
* for which you are responsible for correctly implementing. Just because  *
* your program passes this test, it doesn't mean you'll get higher than   *
* a C - your instructor will be looking especially closely at the parts   *
* which aren't covered in this test.                                      *
*                                                                         *
* Be sure to check for updates every day until the due date, just in case *
* there is some problem, er, ah, issue that needs to be addressed.        *
*                                                                         *
* IMPORTANT: if you changed the dtio code at all, you should document the *
* changes, and provide the assignment 1 test executables as well as the   *
* assignment 2 and 3 executables (i.e. you must demonstrate that you      *
* didn't break the assignment 1-3 code in getting the assignment 4 code   *
* to work). Similarly, if you changed the Field or Screen classes, you    *
* should document the changes and provide the assignment 3 executables.   *
\*************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "Screen.h"

// the test program uses line 17 for status messages; this function
// writes a string in the message location
//
void message(const char *s)
{
    dtioDisplay(s, 17, 4, 48);
}

// returns a description of key code "key" - this string should
// be used immediately, its address should not be stored for later use
//
const char *keymess(int key)
{
	int keys[] = {UP, DOWN, LEFT, RIGHT, PGUP, PGDN, ENTER, TAB,
				  BACKSPACE, DEL, HOME, END, ESCAPE, INSERT,
				  F(1), F(2), F(3), F(4), F(5), F(6), F(7), F(8),
				  F(9), F(10), F(11), F(12) };
	char *names[] = {"Up Arrow", "Down Arrow", "Left Arrow",
				  "Right Arrow", "Page Up", "Page Down", "Enter",
				  "Tab", "Backspace", "Delete", "Home", "End",
				  "Escape", "Insert", "F1", "F2", "F3", "F4", "F5",
				  "F6", "F7", "F8", "F9", "F10", "F11", "F12"};
	const int nKeys = 26;
	static char s[30];

	if (' ' <= key && key <= '~') {
		// printable ASCII key
		s[0] = key;
		s[1] = '\0';
	}
	else {
		// non-printable or non-ASCII key
		int i = 0;
		while (i < nKeys && key != keys[i])
			i++;
		if (i < nKeys)
			strcpy(s, names[i]);
		else
			sprintf(s, "Unknown key : code %d", key);
	}
	return s;
}

// displays a key description and a message on the "status line".
//
void dispmess(int key, char *s)
{
    char msg[81];
    sprintf(msg, "<%s> %s", keymess(key), s);
    message(msg);
}

// generic help function
//
void help1(void *)
{
    message("Use the arrow keys to move between fields");
}

// another help function
//
void help2(void *)
{
    message("The 3rd vfield must be nonempty");
}

// help function for ivfield that lets user pick a value from 1-3
//
void helppick(void *data)
{
    static bool firsttime = true;

    if (firsttime) {
        srand((unsigned)time(NULL));
        firsttime = false;
    }
    message("Shall I pick a number (y/n)? ");
    Field yorn(17, 33, 1, "y");
    if (ESCAPE != yorn.edit() && 'y' == *(char *)yorn.data())
        *(int *)data = rand()%3 + 1;
}

// validate that a string is not empty
//
bool notempty(char *s)
{
    return s[0] != '\0';
}

// validation function for a string that simply converts it to uppercase
//
bool capit(char *s)
{
    while (*s) {
        if ('a' <= *s && *s <= 'z')
            *s -= 32;
        s++;
    }
    return true;
}

bool zero100(int &n)
{
    bool rc = n < 0 || 100 < n;
    message(rc ? "" : "Number mustn't be between 0 and 100");
    return rc;
}

bool makeitpi(double &d)
{
    d = 3.141592654;
    return true;
}

// result displays the result for the tester in column 55
void result(int row, const char* s) {
	dtioDisplay(s, row, 60, 24);
}

// prompt displays the prompt for the tester on line 23
void prompt(const char* s) {
	dtioDisplay(s, 23, 9, 45);
}

// pause
int pause() {
	prompt("Press any key to continue ... ");
	dtioGetchar();
	prompt("");
	return 0;
}

int main()
{
    dtioStart();
    dtioClear();
    if (dtioRows() < 20 || dtioColumns() < 60) {
        dtioStop();
        printf("Screen is too small - need 20x60\n");
    }
    else {
        Screen s1, s2;
        s1 += Box(1, 1, 58, 19, "/-\\|/-\\|");
	    result(1, "Box added");
        s1 += Label(3, 3, "SFields:");
	    result(2, "SField Label");
        s1 += SField(3, 14, 20);
	    result(3, "SField empty");
        s1 += SField(3, 36, 20, "string");
	    result(4, "SField added");
        s1 += Label(5, 3, "HFields:");
	    result(5, "HField Label");
        s1 += HField(5, 14, 20);
	    result(6, "HField added");
        s1 += HField(5, 36, 20, "press F1", help1);  // basic help
	    result(7, "F1 added");
        s1 += Label(7, 3, "VFields: ");
	    result(8, "VField Label");
        s1 += VField(7, 14, 20);                         // works like a Field
	    result(9, "VField added");
        s1 += VField(7, 36, 4, "big", capit, help1);  // always gets capitalized
	    result(10, "big added");
        s1 += VField(7, 42, 10, "delete me", notempty, help2); // can't empty it
	    result(11, "delete me");
        s1 += Label(9, 3, "IVFields:");
	    result(12, "IVFields Label");
        s1 += IVField(9, 14, 5);                         // must be an int
	    result(13, "IVField added");
        s1 += IVField(9, 20, 5, 999999, zero100, help1); // < 0 or > 100
	    result(14, "999999 added");
        s1 += IVField(9, 26, 4, 0, NULL, help1);     // int with help
	    result(15, "help added");
        s1 += Label(12, 3, "MMIFields:");
	    result(16, "MMIField added");
        s1 += MMIField(12, 14, 3, -1, 0, 100);        // range 0-100
	    result(17, "0-100 added");
        s1 += MMIField(12, 20, 3, 1, 0, 3, helppick); // F1 lets user pick
	    result(18, "F1 picks");
        s1 += Label(15, 3, "DVFields:");
	    result(19, "DVFields added");
        s1 += DVField(15, 14, 10);                    // must be a double
	    result(20, "must be added");
        s1 += DVField(15, 36, 10, 6, 1.1, makeitpi, help1);// always becomes pi
	    result(21, "pi added");
        s1 += Box(16, 3, 54, 3);
	    result(22, "Box added");
        #ifdef DID_REGION
                s1 += Region(10, 40, 15, 4, "test\nregion");
        #endif
		
        s1.display();
		result(23, "ready to test edit");

		pause();
        s1.edit();
		result(23, "ready to test =");

        pause();
        s2 = s1; // just to make sure the pesky = works
	    result(23, "= operator tested");
		pause();
        *(IVField *)s2.getField(14) = 5;    // set 3rd IVField to 5
        *(DVField *)s2.getField(19) = -0.5; // set 1st DVField to -0.5

        int key;
        char msg[121];
        bool done = false;

        do {
            key = s2.edit();
            if (key == ESCAPE)
                done = true;
            else {
                // keys like F2-F10, page up and page down will display
                // the keycode, the 3rd ivfield and the 2nd dvfield
                sprintf(msg, "%s %d %.8lf", keymess(key),
                 int(*(IVField *)s2.getField(14)),
                 double(*(DVField *)s2.getField(20)));
                message(msg);
				pause();
            }
        } while (!done);
        dtioStop();
        #ifdef DID_REGION
            printf("Region:[%s]\n", (char *)s2.getField(22)->data());
        #endif

    }
    return 0;
}