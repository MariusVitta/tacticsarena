#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

char map[N][N];


void coup_zone(char map[N][N],t_personnage * j1,t_personnage  * j2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist=j1->s4.portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = j1->coord.y;
	j = j1->coord.x - dist ;

	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] != '*' && point[i][j] != 'o'){
						point[i][j] = 'A' + car;
						car++;
					}
				}
			}
		}
	}

	dist=j1->s4.portee;
	g = j1->coord.y;
	j = j1->coord.x - dist ;

	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] != '*' && point[g][j] != 'o'){
						if(g != j1->coord.y){
								point[g][j] = 'A' + car;
								car ++;
						}
					}
				}
			}
		}
	}
	/* affichage */
	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

	//printf("x = %i y = %i\n", x, y);
  //vérifie si il y a un ennemie si oui lui inflige les dégats
	if(map[y][x] == map[i][j]){
    if ((map[y-1][x] == map[i][j]) || (map[y+1][x] == map[i][j]) || (map[y][x-1] == map[i][j]) || (map[y][x+1] == map[i][j]))
    		j2->pv -= j1->s4.degat;
	}
}
