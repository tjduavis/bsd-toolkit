/* Visual Studio Console Functions 
* 
* vnetconsole.c
* Author: Timothy Duavis
* Last Updated: Sept 22/2005
*/

#include<stdio.h>
#include<conio.h>
#include<windows.h>

/*HANDLE GetStdHandle(DWORD);
BOOL SetConsoleCursorPosition(HANDLE,COORD);*/
	


int main(void) {
	HANDLE std_out;
	COORD winscreen;
	CONSOLE_SCREEN_BUFFER_INFO winscreen_info;
	/*SMALL_RECT win;*/
	int success = 2;
	std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(std_out, &winscreen_info);

	
	cprintf("dwSize coordinate x = %d\n",(int)winscreen_info.dwSize.X);
	cprintf("dwSize coordinate y = %d\n",(int)winscreen_info.dwSize.Y);
	
	cprintf("dwMaximumWindowSize coordinate x = %d\n",(int)winscreen_info.dwMaximumWindowSize.X);
	cprintf("dwMaximumWindowSize coordinate y = %d\n",(int)winscreen_info.dwMaximumWindowSize.Y);

	/*cprintf("upper left x coordinate = %d\n",win.srWindow.Left);
	cprintf("upper left y coordinate = %d\n",win.srWindow.Top);
	cprintf("lower right x coordinate = %d\n",win.srWindow.Right);
	cprintf("lower right y coordinate = %d\n",win.srWindow.Bottom);*/
		
	winscreen.X = 99;
	winscreen.Y = 56;
	getch();
	system("cls");
	
	success = SetConsoleCursorPosition(std_out, winscreen);
	cprintf("cursor position success %d\n",success);
	getch();
	
	return 0;
}