#include <stdio.h>
#include "init.h"
#include "fonc.h"

#define N 11

char map[N][N];


int main(int argc, char const *argv[]){
	int i, j;
	char jeu[N][N];

	//affichage_map(map);

	initialisation(map,2);
	affichage_map(map);

	return 0;
}