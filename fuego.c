#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

void fuego(char map[N][N],t_personnage * perso1, t_joueur j2,int numj){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist=perso1->s3.portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] == '.'){
						point[i][j] = 'A' + car;
						car++;
					}
				}
			}
		}
	}

	dist=perso1->s3.portee;
	g = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != perso1->coord.y){
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

	if(numj==2){
		switch (map[y][x]){

			case '1' :
					perso1->perso1->pv -= perso1->s3.degat;
					printf("%s touché.\nPoint de vie : %i\n", perso1->perso1->nom, perso1->perso1->pv);
				break;

			case '3' :
					perso1->perso2->pv -= perso1->s3.degat;
					printf("%s touché.\nPoint de vie : %i\n", perso1->perso2->nom, perso1->perso2->pv);
				break;
		}
	}

	else if(numj==1){
		switch (map[y][x]){

			case '2' :
					j2->perso1->pv -= perso1->s3.degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

			case '4' :
					j2->perso2->pv -= perso1->s3.degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
				break;
		}
	}
}
