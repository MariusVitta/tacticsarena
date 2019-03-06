#include <stdio.h>
#include <stdlib.h>
#include "fonc.h" 

int est_mort(t_personnage perso){
	return (perso.pv <= 0);
}

void maj(char map[N][N], t_personnage perso1, t_personnage perso2){
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(j == perso1.coord.x && i == perso1.coord.y)
				map[i][j] = '*';
			if(j == perso2.coord.x && i == perso2.coord.y)
				map[i][j] = '$';
			else
				map[i][j] = '.';
		}
	} 			
}
