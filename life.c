#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GRIDSIZE 50

void fill(int* S){
	time_t t;
	srand(time(&t));
	
	int i, j;
	for(i = 0; i<GRIDSIZE; i++)
		for(j = 0; j<GRIDSIZE; j++)
			*(S + i*GRIDSIZE + j) = rand()%8/7;//probablity of 1/8 of starting alive 
}

int * life(int* S){
	int i,j,p,q,s;
	int* S2 = (int*) malloc(GRIDSIZE*GRIDSIZE*sizeof(int));

	for(i = 0; i<GRIDSIZE; i++)
		for(j = 0; j<GRIDSIZE; j++){
			s = 0;
		
			for(p = i-1; p<=i+1; p++)
				for(q = j-1; q<=j+1; q++)
					if(p >= 0 && p<GRIDSIZE)
						s += *(S + p*GRIDSIZE + (q+GRIDSIZE)%GRIDSIZE);

			if(s - *(S + i*GRIDSIZE + j) == 3 || s == 3)
				*(S2 + i*GRIDSIZE + j) = 1;
			else
				*(S2 + i*GRIDSIZE + j) = 0;
		}
	return S2;
}

void print(int* S)
{
	int i, j;
	for(i = 0; i<GRIDSIZE; i++){
		for(j = 0; j<GRIDSIZE; j++){
			if(*(S + i*GRIDSIZE + j) == 1) printf("██");
			else printf("  ");
		}
		printf("\n");
	}
}

int main(){
	int* S = (int*) malloc(GRIDSIZE*GRIDSIZE*sizeof(int));
	int* S2;
	fill(S);
	while(1)
	{ 
		S2 = life(S);
		free(S);
		S = S2;
		print(S);
		sleep(1);
	}

}

