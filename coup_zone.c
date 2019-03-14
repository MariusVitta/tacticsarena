#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

enum perso {j1,j2,j3,j4};

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
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					//verifie si il y a un obstacle ou un personnage a l'emplacement
					if(point[i][j] != 'o' && point[i][j] != point[j1->coord.y][j1->coord.x]){
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
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] != 'o'){
						if(g != j1->coord.y){
								point[g][j] = 'A' + car;
								car ++;
								if( ('A' + car )== 'o')
									car++;
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
  //vérifie si il y a des personnages dans la croix de largeur 'l' si oui leurs infliges les dégats
	int l=1;

	if( (i==x && j==y-l || j==y+l) || (j==y && i==x-l || i==x+l) ){
			if( (map[i][j] == '1') || (map[i][j] == '2') || (map[i][j] == '3') || (map[i][j] == '4') ){
				j2->pv -= j1->s4.degat;
				printf("%s touché.\nPoint de vie : %i\n", j2->nom, j2->pv);
			}
	}
}
