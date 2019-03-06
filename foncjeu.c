#include <stdio.h>
#include <stdlib.h>
#include "fonc.h" 

int est_mort(t_personnage perso){
	return (perso.pv <= 0);
}

void maj(char map[N][N], t_personnage perso){
<<<<<<< HEAD
	int i,j;
=======
	int i, j;
>>>>>>> dc67b1808d6f35874fb6c8d4afbcd1ce32185a95
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(j == perso.coord.x && i == perso.coord.y)
				map[i][j] = '*';
			else
				map[i][j] = '.';
		}
	} 			
}
