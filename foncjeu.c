#include <stdio.h>
#include <stdlib.h>
#include "fonc.h" 

int est_mort(t_personnage perso){
	return (perso.pv <= 0);
}

void maj(char map[N][N], t_personnage perso1, t_personnage perso2){
	int i, j;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++)
			map[i][j] = '.';
	
	}	
	/*problème de type x et y == type double */
	map[perso1.coord.y][perso1.coord.x] = '*';
	map[perso2.coord.y][perso2.coord.x] = '$';

	int x1 = perso1.coord.x;
	int y1 = perso1.coord.y;
			
}
