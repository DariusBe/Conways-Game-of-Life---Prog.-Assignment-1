#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>    
#include <conio.h>
#pragma warning(disable : 4996)

// falls nötig später mit IF DEF zu anderen OS portieren

/*	Matrix definieren	*/
#define ROWS 17
#define COLS 20

/*	Funktionsinitialisierung	*/
void MenuHeader();
void gotoXY(int x, int y);
char printField(char r, char arr[COLS][ROWS]);
//Menü
int sel = 1;
int userInput;

/*	Funktionsdeklaration:	*/

void MenuHeader() {
	printf("\n\n\t\t\tCONWAY's GAME OF LIFE\n");
	printf("\t===================================================\n\t|");
	printf("[1 - START]	[2 - LOAD STARTUP-FILE]	[3 - EXIT]");
	printf("|\n\t===================================================\n\t>>>>");
}

void gotoXY(int x, int y) {
	HANDLE  hConsoleOutput; COORD koords;
	koords.X = x; koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}

/*
char printField(char r, char arr[COLS][ROWS]) {
	int i, j;
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			r = rand() % 2;
			arr[i][j] = r;
			if (r == 0) printf("[*]");
			else printf("[ ]");
		}
		printf("\n\t");
	}
	return arr;
}*/


char printField(char r, char arr[COLS][ROWS]) {
	int i, j;
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			r = rand() % 2;
			if (r == 0) arr[i][j] = 0;		//LEBEND
			else arr[i][j] = 1;				//TOT
		}
		printf("\n\t");
	}
	return arr;
}



int main(int argc, char *argv[]) {
	

	//RANDOMIZER
	srand(time(NULL));			// Initialization, should only be called once.
	//ZUSTANDSVARIABLEN
	int z = 1;
	//ARRAY
	char r = ' ';
	char arr[ROWS][COLS];

	/* BEGINN PROGRAMMABLAUF */

	//printField(r, arr);

	//printf("%s", arr[1]);

	//CASE-Set
	
	while (1 == 1)
	{	
		
		MenuHeader();

		scanf_s("%d", &userInput);

		switch (userInput) {

		case 1:
			while (1 == 1) {
				gotoXY(8, 8);
				Sleep(500);
				printField(r, *arr);
				gotoXY(8, 8);

				
				for (int m = 0; m < COLS; m++) {
					for (int n = 0; n < ROWS; n++) {
						if (arr[m][n] == 0) printf("[*]");
						else printf("[ ]");
					}
					printf("\n\t");
				}
				
			}	//https://stackoverflow.com/questions/13390541/correct-way-to-return-two-dimensional-array-from-a-function-c
			break;
		case 2:
			printf("Menü 2");
			break;

		case 3:
			return 0;

		case 0:
			break;
		}

		gotoXY(0, 0);

	}
	


	return 0;
}


//Notizablage
/*
//Beispiel für randomisiertes Feld

	for (i = 0; i < 25; i++) {
		r = rand() % 2;
		printf("\n%d", r);
	}


[i-1][j-1]	||		[i][j-1]	||		[i-1][j+1]
==================================================
[ i-1][j ]	||		[  *  ]		||		[ i+1][j]
==================================================
[i+1][j-1]	||		[i+1][j]	||		[i+1][j+1]

1. Besitzt eine lebende Zelle 0, 1 oder mehr als 3 lebende
Nachbarzellen, stirbt sie an Vereinsamung oder Übervölkerung. -->
2. Besitzt eine lebende Zelle 2 oder 3 lebende Nachbarzellen, dann
existiert sie in der nächsten Generation weiter.
3. Ist eine tote Zelle von genau 3 lebenden Zellen umgeben, dann
entsteht aus ihr eine neue lebende Zelle.

betrachtete Zelle arr[i][j]

Vorab Prüfung: Lebt Zelle arr[i][j]?
Lebt Zelle:
Verrechnung aller Nachbarn miteinander: Addition der einzelnen Elemente sodass >2 --> Zelle ist in Folgegeneration tot
int summe = arr[i-1][j-1] + arr[i][j-1] +  arr[i-1][j+1] + arr[i-1][j] + arr[i+1][j] + arr[i+1][j-1] + arr[i+1][j] + arr[i+1][j+1]


if (summe < 2 && summe > 3) arr[i][j] --> in Folgegeneration TOT
else arr[i][j] bleibt am Leben;

Ist Zelle tot:
if (summe >= 3) arr[i][j] --> in Folgegeneration LEBEND

*/