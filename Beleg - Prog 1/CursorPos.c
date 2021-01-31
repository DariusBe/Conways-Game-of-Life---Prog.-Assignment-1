#include <windows.h>
#include <stdio.h>

void gotoXY(int x, int y) {
   HANDLE  hConsoleOutput; COORD koords;
   koords.X=x; koords.Y=y;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleCursorPosition(hConsoleOutput,koords);
}

void main() {
   
   gotoXY(10,10); printf("Hello World!");
}