#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

void maj(char map[N][N], t_personnage perso1, t_personnage perso2){
	int i, j;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(map[i][j] != 'o')
				map[i][j] = '.';
		}

	}

	map[perso1.coord.y][perso1.coord.x] = '1';
	map[perso2.coord.y][perso2.coord.x] = '2';

	int x1 = perso1.coord.x;
	int y1 = perso1.coord.y;

}

int existe(char mat[N][N], char choix, int * x, int * y){

	int i, j;

	if(choix == 'o')
		return 0;

		/*if(choix == '1' || choix == '2')
			return 0;*/

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(mat[i][j] == choix){
				*x = j;
				*y = i;
				return 1;
			}
		}
	}
	return 0;
}

void attire(char map[N][N], t_personnage * perso1, t_personnage * perso2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;
/*copie plan jeu dans la matrice point*/

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = perso1->coord.y + 1;
	j = perso1->coord.x ;

	int nb = 0;
	int car = 0;

	for(; i < N && nb < perso1->s2.portee && point[i][j] == '.'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x;
	nb = 0;

	for(; i >= 0  && nb < perso1->s2.portee && point[i][j] == '.'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; j < N && nb < perso1->s2.portee && point[i][j] == '.'; j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < perso1->s2.portee && point[i][j] == '.'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

	/* Verifie si il y a un perso à cette emplacement */
	if(map[y][x] == '1' || map[y][x] == '2'){
		/* Si sur la même ligne */
		if(perso2->coord.y == perso1->coord.y ){
			/* Si l'écart entre les 2 joueurs est de plus de 3 cases */
			if((perso1->coord.x - perso2->coord.x >= 3) || (perso1->coord.x - perso2->coord.x <= -3)){
		 		if(perso1->coord.x < perso2->coord.x )
						perso2->coord.x -= 3;
				else if(perso1->coord.x > perso2->coord.x )
					perso2->coord.x += 3;
			}
			/* Sinon l'attire a son corps à corps du nb de cases d'écart*/
			else{
				if(perso1->coord.x < perso2->coord.x )
					perso2->coord.x = perso1->coord.x + 1;
				else if(perso1->coord.x > perso2->coord.x )
					perso2->coord.x = perso1->coord.x - 1;
			}
		}

		/* Si sur la même colonne*/
		else if(perso2->coord.x == perso1->coord.x ){
			/* Si l'écart entre les 2 joueurs est de plus de 3 cases */
			if((perso1->coord.y - perso2->coord.y >= 3) || (perso1->coord.y - perso2->coord.y <= -3)){
				if(perso1->coord.y < perso2->coord.y )
					perso2->coord.y -= 3;
				else if(perso1->coord.y > perso2->coord.y )
					perso2->coord.y += 3;
			}
			/* Sinon l'attire a son corps à corps du nb de cases d'écart*/
			else{
				if(perso1->coord.y < perso2->coord.y )
					perso2->coord.y = perso1->coord.y + 1;
				else if(perso1->coord.y > perso2->coord.y )
					perso2->coord.y = perso1->coord.y - 1;
			}
		}
	}
}
