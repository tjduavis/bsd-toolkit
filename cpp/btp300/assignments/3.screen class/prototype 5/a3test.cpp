/*************************************************************************\
* File: a3test.cpp                                                        *
* Originally written by Evan Weaver                                       *
* 18 Oct 2004                                                             *
* Updated by Chris Szalwinski                                             *
* 30 Oct 2005                                                             *
* Version 2.0                                                             *
*                                                                         *
* This is a test program for the classes in BTP300's third assignment.    *
* Compile this program with your console I/O routines and classes.        *
* For example,                                                            *
*     bcc32  a3main.cpp dtio.c Screen.cpp                     (Borland)   *
*     cl     a3main.cpp dtio.c Screen.cpp                     (VS .net)   *
*     c++ -o a3main a3main.cpp dtio.c Screen.cpp -lcurses     (AIX)       *
*     c++ -o a3main a3main.cpp dtio.c Screen.cpp -lncurses    (Linux)     *
* should probably work for you.                                           *
*                                                                         *
* Note that this program cannot verify that your routines are correct -   *
* you must run the program and observe whether or not it is working       *
* correctly.                                                              *
*                                                                         *
* In particular, there are many little variations that are not tested but *
* for which you are responsible. Just because your program passes this    *
* test does not mean that your program works perfectly.  Your instructor  *
* will look especially closely at the code that isn't tested here.        *                                    *
*                                                                         *
* Be sure to check for updates every day until the due date, just in case *
* there is some problem, er, ah, issue that needs to be addressed.        *
*                                                                         *
* IMPORTANT: if you changed the dtio code at all, you should document the *
* changes, and provide the assignment 1 and 2 test results as well as the *
* assignment 3 executables (i.e. you need to demonstrate that you did not *
* break the assignment 2 code in getting this assignment code to work).   *
\*************************************************************************/

#include <cstdio>
#include <cstring>
using namespace std;
#include "Screen.h" 

// newFie is derived from Field in order to test whether clone() does
// what we shall need it to do in the future.
class newFie: public Field {
	int row;
	int col;
	int len;
	bool edi;
public:
	newFie(int r, int c, int l, const char *s = "", bool ed = true):
		   Field(r, c, l, s, ed) { row = r; col = c; len = l; edi = ed; }
	Field *clone() const { return new newFie(row, col, len,
		   "Derived cloning is ok", edi); }
};

// message displays status messages on line 19
void message(const char *s) {
	dtioDisplay(s, 19, 5, 50);
}

// keyMessage returns a description of key code "key" that should be
// used immediately: its address should not be stored for later use
const char *keyMessage(int key) {
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

// prompt displays the prompt for the tester on line 23
void prompt(const char* s) {
	dtioDisplay(s, 23, 9, 45);
}

// pause
void pause() {
	prompt("Press any key to continue ... ");
	dtioGetchar();
	prompt("");
}

// displays on the "status line" a description of key followed by a message.
void dispMessage(int key, char *s) {
	char msg[81];
	sprintf(msg, "Key pressed <%s> %s", keyMessage(key), s);
	message(msg);
}

// result displays the result for the tester in column 55
void result(int row, const char* s) {
	dtioDisplay(s, row, 55, 24);
}

// check checks whether a field works correctly by letting the user edit it
// and then displaying the key used to exit editing and the edited contents
// on the "status line".
void check(Field &f) {
	int key = f.edit();
	dispMessage(key, (char *)f.data());
}

// fieldTest tests the field class
void fieldTest() {
	dtioDisplay("PERFORMING FIELD TESTS", 1, 29, 22);
	Field one(-10, -15, 17, "Upper Left CornerXXXX", false); // at (0, 0)
	result(4, "1 constructed");
	Field two(2, 4000, 300, "Help!", false);                 // length 1!
	result(5, "2 constructed");
	Field three(10, 10, 12, "Edit this : ", false);       // normal label
	result(6, "3 constructed");
	Field four(10, 22, 15, "This is a test of a Field");// This is a test
	result(7, "4 constructed");
	Field five(four);                         // initially a copy of four
	result(8, "5 constructed");
	Field six(13, 5, 4);                               // initially empty
	result(9, "6 constructed");
	Field seven(17, 5, 6, "Done ?", false);               // normal label
	result(10, "7 constructed");
	Field eight(17, 12, 1, "n", true);          // used to exit test loop
	result(11, "8 constructed");
	newFie nine(5, 30, 25, "Derived Field", false); // test derived field
	result(12, "9 constructed");
	Field *pten;                                          // test clone()

	if (NULL == (pten = nine.clone()))                 // testing clone()
		message("Clone failed");
	else {
		if (strcmp((char *)pten->data(), "Derived cloning is ok"))
			message("Clone incorrect");
		else
			result(13, "cloning tested");

		// see if editable() is doing the right thing
		if (one.editable() || two.editable() || !four.editable() ||
			!eight.editable() || pten->editable())
			message("editable() is incorrect");
		else
			result(14, "editable() tested");

		// make sure field two that doesn't fit was correctly placed -
		// "two" should start at the end of row 3, hence is 1 char long
		dtioDisplay("Should be an H here->", 2, dtioColumns() - 22, 21);

		// make sure non-editable fields can't be edited
		if (0 != one.edit() || 0 != two.edit() || 0 != three.edit())
			message("Incorrect return value from non-edit edit()");
		else
			result(15, "non-editable tested");

		// show all ten fields
		one.display();
		two.display();
		three.display();
		four.display();
		five.display();  // overwrites four
		six.display();
		seven.display();
		eight.display();
		nine.display();
		pten->display(); // overwrites nine

		// edit each editable field in turn.
		bool first = true;
		dtioDisplay("^Field 1", 1, 0, 8);
		dtioDisplay("Field 2^", 3, dtioColumns() - 8, 8);
		dtioDisplay("^Field 3", 11, 10, 8);
		dtioDisplay("Field^7", 18, 0, 7);
		dtioDisplay("^Field 8", 18, 12, 8);
		do {
			// change four so it contains different data than five
			strcpy((char *)four.data(), "edit this!");
			dtioDisplay("^Field 4", 11, 22, 8);
			prompt("Change the contents of Field 4 above");
			check(four);
			dtioDisplay("", 11, 20, 25);

			dtioDisplay("^Field 5", first ? 11 : 14, first ? 22 : 5, 25);
			prompt("Change the contents of Field 5 above");
			check(five);
			dtioDisplay("", first ? 11 : 14, first ? 20 : 5, 25);

			five = six; // next time five will be a copy of previous six

			if (first) dtioDisplay("^Field 6", 14, 5, 8);
			prompt("Enter something into Field 6 above");
			check(six);

			prompt("Enter \'y\' into Field 8 to exit");
			check(eight);
			prompt("");

			first = false; // no longer the first time through this loop
		} while (*(char *)eight.data() != 'y');
		delete pten;
		dtioDisplay("", 1, 0, 8);
		dtioDisplay("", 4, dtioColumns() - 8, 8);
		dtioDisplay("", 11, 10, 8);
		dtioDisplay("", 14, 5, 8);
		dtioDisplay("", 18, 0, 7);
		dtioDisplay("", 18, 12, 8);
	}
	result(16, "Field Tests Completed");
	dtioDisplay("", 1, 29, 21);
}

// screenTest tests the Screen class
void screenTest() {
	dtioDisplay("PERFORMING SCREEN TESTS", 1, 29, 23);
	Screen s1;
	int keyPressed;

	if (1 != s1.add(10, 30, 25, "Test Screen", false))
		message("first add() has a problem");
	else if (2 != s1.add(13, 10, 5, "Name:XXX", false))
		message("second add() has a problem");
	else if (3 != s1.add(13, 18, 30))
		message("third add() has a problem");
	else if (3 != s1.remove(-1))
		message("first remove() has a problem");
	else {
		s1.display(false);
		result(18, "three fields displayed");
		pause();
		// ensure that screens are copied OK
		Screen s2 = s1;
		result(19,"screen copied");

		prompt("Enter something into the Name field above");
		keyPressed = s1.edit(false);
		//dtioClear(); printf("test"); system("pause");
		dispMessage(keyPressed, (char *)s1.getField(2)->data());
		prompt("");

		// change contents of field for next time
		strcpy((char *)s1.getField(2)->data(), "<-Name: should be gone");
		result(20, "last field altered");

		// remove the Name: label (field number 1) - the editable
		// field should now become field 1
		if (2 == s1.remove(1)) {
			dtioDisplay("", 13, 10, 5);
			prompt("Edit the \'<-Name ...\' field above");
			keyPressed = s1.edit(false);
			dispMessage(keyPressed, (char *)s1.getField(1)->data());
			prompt("");
		} else
			message("remove() has a problem");
		result(21, "remove & edit tested");
	}

	// lets make another screen, using += instead of add()
	Screen s3;

	// make sure that += returns a reference to the screen
	(s3 += Field(3, 20, 20, "Last Test", false)) +=
	Field(5, 5, 4, "URL:", false);

	s3 += Field(5, 15, 40);
	s3 += Field(8, 5, 10, "IP Addr:", false);
	s3 += Field(8, 15, 40);
	s3 += Field(15, 5, 50, "", false);

	int field = 0;
	bool keepon = true;
	// const char *menu[] = {"Exit the program", "Continue editing"};

	// do a data entry screen where only Enter (on the last editable
	// field) or Escape will stop the program, asking for user
	// confirmation before exiting.

	s3.display(false);
	prompt("Enter URL and IP Addr Fields, F1 for help");
	do {
		switch (keyPressed = s3.edit(&field, false)) {
		case F(1): // used as a "help" key
			strcpy((char *)s3.getField(5)->data(),
				field == 2 ? "e.g. http://www.hahaha.com" :
				field == 4 ? "e.g. 123.123.123.2" :
						  "Something is wrong!");
			break;
		case ENTER:
		case ESCAPE: // exit
			keepon = false;
			break;
		default: // otherwise, just show the last key press and edit value
			strcpy((char *)s3.getField(5)->data(), keyMessage(keyPressed));
		}
	} while (keepon);
	prompt("");
	pause();

	dtioDisplay("", 1, 29, 23);
	dtioDisplay("Screen Tests Completed", 22, 55, 22);
	message("Prepare a screen shot if the results look correct");
	pause();
	// done - let's get out and show the edited data on standard output.
	dtioStop();
	printf("Host %s is %s\n", (char *)s3.getField(2)->data(),
		(char *)s3.getField(4)->data());
}

int main() {
	dtioStart();
	dtioClear();
	if (dtioRows() < 20 || dtioColumns() < 60) {
		dtioStop();
		printf("Screen is too small - need 20x60\n");
	} else {
		dtioDisplay("Prompt : ", 23, 0, 9);
		fieldTest();
		screenTest(); // dtioStop() is called here
	}
	return 0;
}

