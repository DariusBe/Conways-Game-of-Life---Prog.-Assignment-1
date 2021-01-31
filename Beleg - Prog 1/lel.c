#include <stdio.h>

void invArr(char* array);


int main(void) {

	char array[7] = { 1,2,3,4,5,6,7 };

	printf("\n\nAnzahl d. Schritte: %lu\n\n", (sizeof(array) / 2));


	invArr(array);

	for (int i = 0; i < 7; i++) printf("[%i]", array[i]);

	return 0;

}

void invArr(char* array) {
	char h;
	int opCount = 3;

	for (int i = 0; i < opCount; i++) {

		printf("%d\n", i);
		h = array[i];
		array[i] = array[opCount - i];
		array[opCount - i] = h;
	}
}

/*

		a[0] --> a[-1]

		a[1] --> a[-2]

*/