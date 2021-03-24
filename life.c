/* Game of Life in C
 * By Ken Callow
 * 2014 - 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GRIDSIZE 50
#define GRIDMEM GRIDSIZE*GRIDSIZE*sizeof(int)

int* gridPointer(int* S, int i, int j) {
	return S + i*GRIDSIZE + j;
}

void fill(int* S){
	time_t t;
	srand(time(&t));
	// Fill the grid with randomly selected active blocks
	int i, j;
	for (i = 0; i < GRIDSIZE; i++)
		for (j = 0; j < GRIDSIZE; j++)
			*gridPointer(S, i, j) = rand() % 8 / 7;//probablity of 1/8 of starting alive 
}

int getLifePoints(int* S, int i, int j) {
	int p, q, s;
	s = 0;
	// Iterates over all the 8 surounding blocks and adds 1 if active 
	for (p = i - 1; p <= i + 1; p++)
		for (q = j - 1; q <= j + 1; q++)
			if (p >= 0 && p < GRIDSIZE)
				s += *gridPointer(S, p, (q + GRIDSIZE) % GRIDSIZE);
	return s;
}

int* life(int* S){
	int i, j, s;
	int* S2 = (int*) malloc(GRIDMEM);

	for (i = 0; i < GRIDSIZE; i++)
		for (j = 0; j < GRIDSIZE; j++){
			s = getLifePoints(S, i, j);
			// If surrounded by two or three active blocks keep/make active, else kill
			if (s - *gridPointer(S, i, j) == 3 || s == 3)
				*gridPointer(S2, i, j) = 1;
			else
				*gridPointer(S2, i, j) = 0;
		}
	return S2;
}

void print(int* S)
{
	int i, j;
	for (i = 0; i < GRIDSIZE; i++){
		for (j = 0; j < GRIDSIZE; j++){
			// Print all the active blocks with a square, if dead print spaces 
			if (*gridPointer(S, i, j) == 1) printf("██");
			else printf("  ");
		}
		printf("\n");
	}
}

int main(){
	int* S = (int*) malloc(GRIDMEM);
	int* S2;
	fill(S);
	while (1)
	{ 
		S2 = life(S);
		free(S);
		S = S2;
		print(S);
		sleep(0.3);
	}

}

