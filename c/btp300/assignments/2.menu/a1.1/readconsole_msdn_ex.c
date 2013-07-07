#include <windows.h> 
#include <stdio.h>
 
int main(void) 
{ 
    HANDLE hStdout, hNewScreenBuffer; 
    SMALL_RECT srctReadRect; 
    SMALL_RECT srctWriteRect; 
    CHAR_INFO chiBuffer[160]; // [2][80]; 
    COORD coordBufSize; 
    COORD coordBufCoord; 
    BOOL fSuccess; 
 
    // Get a handle to the STDOUT screen buffer to copy from and 
    // create a new screen buffer to copy to. 
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    hNewScreenBuffer = CreateConsoleScreenBuffer( 
       GENERIC_READ |           // read/write access 
       GENERIC_WRITE, 
       0,                       // not shared 
       NULL,                    // default security attributes 
       CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
       NULL);                   // reserved; must be NULL 
    if (hStdout == INVALID_HANDLE_VALUE || 
            hNewScreenBuffer == INVALID_HANDLE_VALUE) 
    {
        printf("CreateConsoleScreenBuffer (%d)\n", GetLastError()); 
        return;
    }
 
    // Make the new screen buffer the active screen buffer. 
 	   cputs("******test********\n");
    getch();
    if (! SetConsoleActiveScreenBuffer(hNewScreenBuffer) ) 
    {
        printf("SetConsoleActiveScreenBuffer (%d)\n", GetLastError()); 
        return;
    }
 
    // Set the source rectangle. 
 
    srctReadRect.Top = 0;    // top left: row 0, col 0 
    srctReadRect.Left = 0; 
    srctReadRect.Bottom = 1; // bot. right: row 1, col 79 
    srctReadRect.Right = 60; 
 
    // The temporary buffer size is 2 rows x 80 columns. 
 
    coordBufSize.Y = 2; 
    coordBufSize.X = 60; 
 
    // The top left destination cell of the temporary buffer is 
    // row 0, col 0. 
 
    coordBufCoord.X = 0; 
    coordBufCoord.Y = 0; 
    
   	
    
    // Copy the block from the screen buffer to the temp. buffer. 
 
    fSuccess = ReadConsoleOutput( 
       hStdout,        // screen buffer to read from 
       chiBuffer,      // buffer to copy into 
       coordBufSize,   // col-row size of chiBuffer 
       coordBufCoord,  // top left dest. cell in chiBuffer 
       &srctReadRect); // screen buffer source rectangle 
    if (! fSuccess) 
    {
        printf("ReadConsoleOutput (%d)\n", GetLastError()); 
        return;
    } 
 
    // Set the destination rectangle. 
 
    srctWriteRect.Top = 10;    // top lt: row 10, col 0 
    srctWriteRect.Left = 0; 
    srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79 
    srctWriteRect.Right = 60; 
 
    // Copy from the temporary buffer to the new screen buffer. 
 	getchar();
    fSuccess = WriteConsoleOutput( 
        hNewScreenBuffer, // screen buffer to write to 
        chiBuffer,        // buffer to copy from 
        coordBufSize,     // col-row size of chiBuffer 
        coordBufCoord,    // top left src cell in chiBuffer 
        &srctWriteRect);  // dest. screen buffer rectangle 
    if (! fSuccess) 
    {
        printf("WriteConsoleOutput (%d)\n", GetLastError()); 
        return;
    }
    Sleep(10000); 
    // getchar();
 
    // Restore the original active screen buffer. 
 
    if (! SetConsoleActiveScreenBuffer(hStdout)) 
    {
        printf("SetConsoleActiveScreenBuffer (%d)\n", GetLastError()); 
        return;
    }
    return 0;
}
