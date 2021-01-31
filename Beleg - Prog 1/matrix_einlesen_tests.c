#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define ROWS 20
#define COLS 17
#define GREEN   "\x1b[32m"		// @todo remove
#define RESET   "\x1b[0m"		// @todo remove

char buffer[341];

char matrixCurrGen[ROWS][COLS];

void printMatrix(char matrix[ROWS][COLS]);

int main() {


    FILE* myFile;
    myFile = fopen("matrix2.txt", "r");

    //read file into array
    if (myFile == NULL) {
        printf("Error Reading File\n");
        exit(-1);
    } else printf("File successfully opened!\n");

    char c;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            c = fscanf(myFile, "%c", &buffer[i]);
            matrixCurrGen[i][j] = c;
        }
    }
   

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (buffer[i+j] == 1) matrixCurrGen[i][j] = 1;
            else if (buffer[i + j] == 0) matrixCurrGen[i][j] = 0;
        }
        printf("\n");
    }

    fclose(myFile);

    printMatrix(matrixCurrGen);

	return 0;
}


/*	FUNCTIONS	*/	

// prints matrices of fixed size
void printMatrix(char matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrix[i][j] == 1) printf(GREEN "[%d]"RESET, matrix[i][j]);
            else if (matrix[i][j] == 0) printf("[%d]", matrix[i][j]);
            else printf("Error");
        }
        printf("\n");
    }
}
