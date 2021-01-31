#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#pragma warning(disable : 4996)

/* constant definitions; matrix format	*/
#define ROWS 24
#define COLS 19
#define GREEN   "\x1b[32m"		// @todo remove
#define RESET   "\x1b[0m"		// @todo remove

/*	function declarations	*/	
void printMatrix(char matrix[ROWS][COLS]);
char isValidCell(int m, int n);
void fillInitialMatrixRandomly(int likelihood);
void updateCell(char livingNeighbors, int m, int n);
char countLivingNeighbors(int i, int j);
void gotoXY(int x, int y);

void eraseScreen();
void menuHeader();
void menuHeader_chooseMode();
void menuHeader_choosePercentage();
void menuHeader_chooseSpeed();
void menuHeader_chooseMatrix();


/*	global variables	*/
char matrixCurrGen[ROWS][COLS];
char matrixNextGen[ROWS][COLS];
int rebirthTime;
/*	FILE-Pointer	*/
FILE* fp;

int main() {
	char userInput;

	//standard value: around 50% of all cells will be initialized as living cells
	char likelihood = 50;

	char livingNeighbors;
	
	while (1)
	{
		menuHeader();

		scanf_s("%d", &userInput);

		switch (userInput) {

		/*	MENU OPTION 1: CONWAY'S BASED ON RANDOM MATRIX	*/
		case 1:

			eraseScreen();
			gotoXY(0, 0);
			menuHeader_choosePercentage();

			scanf("%d", &likelihood);

			fillInitialMatrixRandomly(likelihood);

			eraseScreen();
			gotoXY(0, 0);
			menuHeader_chooseSpeed();

			scanf_s("%d", &rebirthTime);

			eraseScreen();
			gotoXY(0, 0);
			menuHeader_chooseMode();

			scanf_s("%d", &userInput);

			char selectStepByStepMode;
			if (userInput == 2) selectStepByStepMode = 1;

			do {

				gotoXY(8, 5);

				printMatrix(matrixCurrGen);

				if (selectStepByStepMode == 1) {
					scanf("%c", &userInput);
				}

				Sleep(rebirthTime);
				gotoXY(8, 5);

				// for every cell, determine next state
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						livingNeighbors = countLivingNeighbors(i, j);
						updateCell(livingNeighbors, i, j);
					}
				}

				memcpy(matrixCurrGen, matrixNextGen, sizeof matrixCurrGen);

				printMatrix(matrixCurrGen);


			} while (userInput);

			break;




		/*	MENU OPTION 2: CONWAY'S BASED ON PRESET MATRICES	*/

		case 2:
			eraseScreen();
			gotoXY(0, 0);
			menuHeader_chooseMatrix();

			/* MENU TO CHOOSE MATRIX */
			scanf_s("%d", &userInput);

			switch (userInput) {
			case 1:
				fp = fopen("matrix1.txt", "r");
				break;
			case 2:
				fp = fopen("matrix2.txt", "r");
				break;
			case 3:
				fp = fopen("matrix3.txt", "r");
				break;
			case 4:
				fp = fopen("matrix4.txt", "r");
				break;
			}


			if (fp == NULL) {
				printf("Error: opening the file.");
				return -1;
			}


			eraseScreen();
			gotoXY(0, 0);
			menuHeader_chooseSpeed();

			scanf_s("%d", &rebirthTime);


			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS+1; j++) {
					char s[] = "0";
					fscanf(fp, "%c", &s[0]);
					if (atoi(s) == 1) {
						matrixCurrGen[i][j] = 1;
					}
					else if (atoi(s) == 0) {
						matrixCurrGen[i][j] = 0;
					}
				}
			}

			while (1) {
				eraseScreen();
				gotoXY(0, 0);
				menuHeader_chooseMatrix();

				gotoXY(8, 5);
				printMatrix(matrixCurrGen);
				Sleep(rebirthTime);
				gotoXY(8, 5);

				// for every cell, determine next state
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						livingNeighbors = countLivingNeighbors(i, j);
						updateCell(livingNeighbors, i, j);
					}
				}

				memcpy(matrixCurrGen, matrixNextGen, sizeof matrixCurrGen);

				printMatrix(matrixCurrGen);
			}

			fclose(fp);

			break;
		/*	Exit 3	*/
		case 3:
			return 0;
		

		default:
			eraseScreen();
			gotoXY(30, 25);
			printf("[ In Memory of John Horton Conway ]");
			break;



			}

			gotoXY(0, 0);

		}


	return 0;
}


// prints matrices of fixed size
void printMatrix(char matrix[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (matrix[i][j] == 1) printf(GREEN "[%d]" RESET, matrix[i][j]);
			else if (matrix[i][j] == 0) printf("[%d]", matrix[i][j]);
			else printf("E");
		}
		printf("\n\t");
	}
}

// checks if coordinates are within matrix bounds
char isValidCell(int m, int n) {
	if ((m >= 0) && (m < ROWS) && (n >= 0) && (n < COLS))
		return 1;
	else
		return 0;
}

//	sets random initial matrix state with values 1 or 0
void fillInitialMatrixRandomly(int likelihood) {
	srand(time(NULL));

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			int r = rand() % 100;
			if (r < likelihood) matrixCurrGen[i][j] = 1;
			else matrixCurrGen[i][j] = 0;
		}
	}
}

// changes state of current cell depending on number of living neighbor cells
void updateCell(char livingNeighbors, int m, int n) {
	if (matrixCurrGen[m][n] == 1) {
		if ((livingNeighbors < 2) || (livingNeighbors > 3))
			matrixNextGen[m][n] = 0;
		else
			matrixNextGen[m][n] = 1;
	}
	else {
		if (livingNeighbors == 3)
			matrixNextGen[m][n] = 1;
		else
			matrixNextGen[m][n] = 0;
	}
}

// counts living neighbors for a given cell
char countLivingNeighbors(int i, int j) {
	char livingNeighbors = 0;

	// top left
	if (isValidCell(i - 1, j - 1))
		livingNeighbors += matrixCurrGen[i - 1][j - 1];

	// top mid
	if (isValidCell(i - 1, j))
		livingNeighbors += matrixCurrGen[i - 1][j];

	// top right
	if (isValidCell(i - 1, j + 1))
		livingNeighbors += matrixCurrGen[i - 1][j + 1];

	// left
	if (isValidCell(i, j - 1))
		livingNeighbors += matrixCurrGen[i][j - 1];

	// right
	if (isValidCell(i, j + 1))
		livingNeighbors += matrixCurrGen[i][j + 1];

	// bottom left
	if (isValidCell(i + 1, j - 1))
		livingNeighbors += matrixCurrGen[i + 1][j - 1];

	// bottom mid
	if (isValidCell(i + 1, j))
		livingNeighbors += matrixCurrGen[i + 1][j];

	// bottom right
	if (isValidCell(i + 1, j + 1))
		livingNeighbors += matrixCurrGen[i + 1][j + 1];

	return livingNeighbors;
}

void gotoXY(int x, int y) {
	HANDLE  hConsoleOutput; COORD koords;
	koords.X = x; koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}

/*	MENU HEADER FUNCTIONS	*/

void eraseScreen() {
	gotoXY(5,1);
	for (int i=0; i<40; i++) {
		printf("                                                         \n");
	}
}

void menuHeader() {
	printf("\n\t\t\tCONWAY's GAME OF LIFE\n");
	printf("\t=========================================================\n\t|");
	printf("[1 - Random Matrix ] [2 - Load Startup-File] [3 - Exit]");
	printf("|\n\t=========================================================\n\t>>>>\t");
}

void menuHeader_choosePercentage() {
	printf("\n\t\t\tCONWAY's GAME OF LIFE\n");
	printf("\t=========================================================\n\t|");
	printf("[  By what percentage shall the matrix be poulated?   ]");
	printf("|\n\t=========================================================\n\t>>>>\t");
}

void menuHeader_chooseSpeed() {
	printf("\n\t\t\tCONWAY's GAME OF LIFE\n");
	printf("\t=========================================================\n\t|");
	printf("[ Please select Animation Speed in ms per generation. ]");
	printf("|\n\t=========================================================\n\t>>>>\t");
}

void menuHeader_chooseMode() {
	printf("\n\t\t\tCONWAY's GAME OF LIFE\n");
	printf("\t=========================================================\n\t|");
	printf("[GAME MODES]	 [ 1 - Animated ]    [2 - Step by Step ]");
	printf("|\n\t=========================================================\n\t>>>>\t");
}


void menuHeader_chooseMatrix() {
	printf("\n\t\t\tCONWAY's GAME OF LIFE\n");
	printf("\t=========================================================\n\t|");
	printf("[ MATRIX 1 ]  [ MATRIX 2 ]  [ MATRIX 3 ]  [ MATRIX 4 ]");
	printf("|\n\t=========================================================\n\twhich file? >>");
}



/*	NOTES	*/
/*
[i-1][j-1]	||	  [i-1][j]	||		[i-1][j+1]
==================================================
[i][j-1]		||		[  *  ]		||		[ i][j+1]
==================================================
[i+1][j-1]	||		[i+1][j]	||		[i+1][j+1]



REGELN:
1. Besitzt eine lebende Zelle 0, 1 oder mehr als 3 lebende
Nachbarzellen, stirbt sie an Vereinsamung oder Übervölkerung.

2. Besitzt eine lebende Zelle 2 oder 3 lebende Nachbarzellen, dann
existiert sie in der nächsten Generation weiter.

3. Ist eine tote Zelle von genau 3 lebenden Zellen umgeben, dann
entsteht aus ihr eine neue lebende Zelle.

betrachtete Zelle arr[i][j]

Vorab Prüfung: Lebt Zelle arr[i][j]?
Lebt Zelle:
Verrechnung aller Nachbarn miteinander: Addition der einzelnen Elemente sodass >3 --> Zelle ist in Folgegeneration tot
int summe = arr[i-1][j-1] + arr[i][j-1] +  arr[i-1][j+1] + arr[i-1][j] + arr[i+1][j] + arr[i+1][j-1] + arr[i+1][j] + arr[i+1][j+1]


if (summe < 2 && summe > 3) arr[i][j] --> in Folgegeneration TOT
else arr[i][j] bleibt am Leben;

Ist Zelle tot:
if (summe >= 3) arr[i][j] --> in Folgegeneration LEBEND

*/


/*	TO
-DO's	*/
/*
	- check Exit function
	- validation checks for all Inputs: mapping of "likelihood" input to fit percentage format
	- default switch case implementation (what mode?)
*/