/* Menu Driven Line Editor - Test Main
 * Assignment 2 - BTP300
 * a2test.c
 *
 * Chris Szalwinski
 * Oct 12 2005
 *
 * uses dtio.h library in current directory
 */

#include <string.h>
#include "dtio.h"
#define ROW_ERRORS 22
#define FORGET -1
#define ADD     1
#define CHANGE  2
#define ERASE   3
#define QUIT    5

int dtioRequestKey(int request);
int dtioReportBadKey(int request, int key, const char *);
void dtioLabel(int key);

int main(void) {
	int i, j, key, rows, cols, errors = 0, index = 0;
	char str[27] = "abcdefghijklmnopqrstuvwxyz";
	char  in[27] = "AbcdefghiJKLmnopqrstuvwxyZ";
	char out[27] = "AbcdefghiJKLmnopqrstuvwxyZ";
	char  ed[27] = "AbCdefghiJKLmnopqrstuv12";
	char end[27] = "AbCdefg12JKLmnopqrstuv12";
	char del[27] = "AbCdef7892JKLmnopqrstuv12";
	const char *s[10] = {"Add", "Edit", "Delete", "", "Quit"};
	const char box[] = { '_', '_', '_', '|', '+', '-', '+', '|' };

	dtioStart();
	rows = dtioRows();
	cols = dtioColumns();
	dtioClear();
	dtioCursor(0,0);
	j = (int) '0';
	for (i = 0; i < cols; i++) {
		dtioPutchar(j);
		if (j == (int)'9')
			j = (int)'0';
		else
			j++;
	}
	j = (int) '0';
	for (i = 0; i < rows; i++) {
		dtioCursor(i, 0);
		dtioPutchar(j);
		if (j == (int)'9')
			j = (int)'0';
		else
			j++;
	}

	dtioDisplay("abcdefghijklmnopqrstuvwxyz", 12, 5, 0);
	dtioDisplay("Perform the following instructions in turn", 1, 1, 0);
	dtioDisplay("Press Right Arrow Twice, Down Arrow Twice, Insert Once", 3, 3, 0);
	dtioDisplay("Using Arrow and ASCII keys, change \"jkl\" to \"JKL\"", 4, 3, 0);
	dtioDisplay("Press Home, A, End, Left Arrow, Z, Enter", 5, 3, 0);
	dtioDisplay("Press Insert, Home, a, End, Left Arrow, z, Escape", 6, 3, 0);
	dtioDisplay("Press Insert, C, End, Backspace 4 times, Insert, 1, 2, Enter", 7, 3, 0);
	dtioDisplay("Press End, Backspace Twice, 1, 2, 3, Enter", 8, 3, 0);
	dtioDisplay("Press Delete Twice, 7, 8, 9, Enter", 9, 3, 0);
	dtioDisplay("Press Down Arrow twice, Up Arrow once, Enter", 10, 3, 0);
	dtioDisplay("Press Down Arrow once, Escape", 11, 3, 0);
	dtioDisplay("Press Down Arrow 3 times, Enter", 12, 3, 0);
	dtioCursor(3, 3);
	errors += dtioRequestKey(RIGHT);
	if (!errors)dtioCursor(3, 4);
	errors += dtioRequestKey(RIGHT);
	if (!errors)dtioCursor(3, 5);
	errors += dtioRequestKey(DOWN);
	if (!errors)dtioCursor(4, 5);
	errors += dtioRequestKey(DOWN);
	if (!errors)dtioCursor(5, 5);
	key = dtioEdit(str, 14, 5, 27, &index);
	if (key != ENTER) errors += dtioReportBadKey(ENTER, key, NULL);
	if (strcmp(str, out)) errors += dtioReportBadKey(ENTER, 0, "Incorrect string result");
	key = dtioEdit(str, 15, 5, 27, &index);
	if (key != ESCAPE) errors += dtioReportBadKey(ESCAPE, key, NULL);
	if (strcmp(str, in)) errors += dtioReportBadKey(ESCAPE, 0, "Incorrect string result");
	index = 2;
	key = dtioEdit(str, 16, 5, 27, &index);
	if (key != ENTER) errors += dtioReportBadKey(ENTER, key, NULL);
	if (strcmp(str, ed)) errors += dtioReportBadKey(ENTER, 0, "Incorrect string result");
	index = 2;
	key = dtioEdit(str, 14, cols - 10, strlen(str), &index);
	if (key != ENTER) errors += dtioReportBadKey(ENTER, key, NULL);
	if (strcmp(str,end)) errors += dtioReportBadKey(ENTER, 0, "Incorrect string result");
	index = 6;
	key = dtioEdit(str, 17, 5, 27, &index);
	if (key != ENTER) errors += dtioReportBadKey(ENTER, key, NULL);
	if (strcmp(str,del)) errors += dtioReportBadKey(ENTER, 0, "Incorrect string result");
	key = dtioMenu(s, 5, 0, 0, box);
	if (key != CHANGE) errors += dtioReportBadKey(CHANGE, key, NULL);
	key = dtioMenu(s, 5, 1, 1, box);
	if (key != FORGET) errors += dtioReportBadKey(FORGET, key, NULL);
	key = dtioMenu(s, 5, 2, 2, box);
	if (key != QUIT) errors += dtioReportBadKey(QUIT, key, NULL);

	dtioCursor(ROW_ERRORS - 3,3);
	if (errors) {
		dtioPuts("Continue working! ");
	} else {
		dtioPuts("If no errors, prepare screen shot (include top row of numbers) ... ");
	}
	dtioCursor(ROW_ERRORS - 2, 3);
	dtioPuts("Press any key to exit!");
	dtioGetchar();
	dtioStop();

	return 0;
}

/* Request a key press, accept the key code and
 * report the difference if any
 */
int dtioRequestKey(int request) {
	int key, rc = 0;

	key = dtioGetchar();
	if (key != request) {
	    rc = dtioReportBadKey(request, key, NULL);
	}
	return rc;
}

/* Report a faulty key press */
int dtioReportBadKey(int request, int key, const char *msg) {
	static int row = ROW_ERRORS;

	if (row != ROW_ERRORS) {
		dtioCursor(ROW_ERRORS - 1, 8);
		dtioPuts("s!");
	} else {
		dtioCursor(ROW_ERRORS - 1, 3);
		dtioPuts("Error!");
	}
	dtioCursor(row++, 3);
	if (key != 0) {
		dtioPuts("Key requested : ");
		dtioLabel(request);
		dtioCursor(row++, 3);
		dtioPuts("You pressed   : ");
		dtioLabel(key);
	} else
		dtioPuts(msg);
	return 1;
}

/* Displays key label at current cursor position */
void dtioLabel(int key) {
	if (key >= ' ' && key <= '~') {
		dtioPutchar(key);
		dtioPuts("            ");
	} else {
		switch (key) {
		case LEFT:      dtioPuts("Left Arrow   "); break;
		case RIGHT:     dtioPuts("Right Arrow  "); break;
		case HOME:      dtioPuts("Home         "); break;
		case END:       dtioPuts("End          "); break;
		case INSERT:    dtioPuts("Insert       "); break;
		case DEL:       dtioPuts("Delete       "); break;
		case BACKSPACE: dtioPuts("Backspace    "); break;
		case ESCAPE:    dtioPuts("Escape       "); break;
		case ENTER:     dtioPuts("Enter        "); break;
		case TAB:       dtioPuts("Tab          "); break;
		case UP:        dtioPuts("Up Arrow     "); break;
		case DOWN:      dtioPuts("Down Arrow   "); break;
		case PGUP:      dtioPuts("Page Up      "); break;
		case PGDN:      dtioPuts("Page Down    "); break;
		case F(1):      dtioPuts("F1           "); break;
		case F(2):      dtioPuts("F2           "); break;
		case F(3):      dtioPuts("F3           "); break;
		case F(4):      dtioPuts("F4           "); break;
		case F(5):      dtioPuts("F5           "); break;
		case F(6):      dtioPuts("F6           "); break;
		case F(7):      dtioPuts("F7           "); break;
		case F(8):      dtioPuts("F8           "); break;
		case F(9):      dtioPuts("F9           "); break;
		case F(10):     dtioPuts("F10          "); break;
		case F(11):     dtioPuts("F11          "); break;
		case F(12):     dtioPuts("F12          "); break;
		case UNKNOWN:   dtioPuts("Unknown Key  "); break;
		case FORGET:    dtioPuts("Menu: Escape "); break;
		case ADD:       dtioPuts("Menu: Add    "); break;
		case CHANGE:    dtioPuts("Menu: Change "); break;
		case ERASE:     dtioPuts("Menu: Delete "); break;
		case QUIT:      dtioPuts("Menu: Quit   "); break;
		default:        dtioPuts("non-ASCII key");
		}
	}
}


