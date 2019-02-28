#include <stdio.h>
#include <stdlib.h>

#define N 11

char map[N][N];

void affichage_sort();
	

void affichage_map(char map[N][N]){

	int i, j;

	printf("Plan de jeu \n\n");

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++)
			printf(" %c |", map[i][j]);
		printf("\n");
	}
}



