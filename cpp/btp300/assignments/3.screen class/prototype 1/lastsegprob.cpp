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

int main(void) {
// lets make another screen, using += instead of add()
	Screen s3;
	int keyPressed;

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
		printf("%d",field);
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
		
	return 0;
}