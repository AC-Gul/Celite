#include<windows.h>

// Initialize the CMD buffer
void initScreen (HANDLE *hConsole, int sw, int sh) 
{
     // Create screen buffer
    *hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(*hConsole);
}