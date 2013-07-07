/* Paint A Screen - Test main
 * Assignment 1 - BTP300
 * a1test.c
 *
 * Chris Szalwinski
 * Sep 22 2005
 *
 * uses dtio.h library in current directory
 */

#include "dtio.h"
int dtioRequestKey(int request);
void dtioLabel(int key);

int main(void) {
	int i, j, key, rows, cols, errors = 0;

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

	dtioCursor(3,3);
	dtioPuts("Press the key displayed in the same row and to the left of the cursor : ");
	dtioCursor(5,3);
	errors += dtioRequestKey(F(1));
	dtioCursor(5,18);
	errors += dtioRequestKey(F(2));
	dtioCursor(5,33);
	errors += dtioRequestKey(F(3));
	dtioCursor(5,48);
	errors += dtioRequestKey(F(4));
	dtioCursor(5,63);
	errors += dtioRequestKey(F(5));
	dtioCursor(6,3);
	errors += dtioRequestKey(F(6));
	dtioCursor(6,18);
	errors += dtioRequestKey(F(7));
	dtioCursor(6,33);
	errors += dtioRequestKey(F(8));
	dtioCursor(6,48);
	errors += dtioRequestKey(F(9));
	dtioCursor(6,63);
	errors += dtioRequestKey(F(10));
	dtioCursor(7,3);
	errors += dtioRequestKey(F(11));
	dtioCursor(7,18);
	errors += dtioRequestKey(F(12));
	dtioCursor(8,3);
	errors += dtioRequestKey(ESCAPE);
	dtioCursor(9,3);
	errors += dtioRequestKey(TAB);
	dtioCursor(8,33);
	errors += dtioRequestKey(BACKSPACE);
	dtioCursor(8,48);
	errors += dtioRequestKey(HOME);
	dtioCursor(8,63);
	errors += dtioRequestKey(PGUP);
	dtioCursor(9,48);
	errors += dtioRequestKey(END);
	dtioCursor(9,63);
	errors += dtioRequestKey(PGDN);
	dtioCursor(10,33);
	errors += dtioRequestKey(ENTER);
	dtioCursor(10,48);
	errors += dtioRequestKey(DEL);
	dtioCursor(10,63);
	errors += dtioRequestKey(INSERT);
	dtioCursor(11,48);
	errors += dtioRequestKey(UP);
	dtioCursor(12,33);
	errors += dtioRequestKey(LEFT);
	dtioCursor(12,48);
	errors += dtioRequestKey(DOWN);
	dtioCursor(12,63);
	errors += dtioRequestKey(RIGHT);

	dtioCursor(3,3);
	dtioPuts("                                                                        ");
	dtioCursor(14,3);
	if (errors) {
		dtioPuts("Continue working! ");
	} else {
		dtioPuts("Prepare a screen shot (include the top row of numbers) ... ");
	}
	dtioCursor(15,3);
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
	static int row = 18;

	dtioLabel(request);
	key = dtioGetchar();
	if (key != request) {
		rc = 1;
		if (row != 18) {
			dtioCursor(17,18);
			dtioPuts("s!");
		} else {
			dtioCursor(17,3);
			dtioPuts("Key press error!");
		}
		dtioCursor(row++,3);
		dtioPuts("Key requested : ");
		dtioLabel(request);
		dtioCursor(row++,3);
		dtioPuts("You pressed   : ");
		dtioLabel(key);
	}
	return rc;
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
		default:        dtioPuts("non-ASCII key");
		}
	}
}


