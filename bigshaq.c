#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

void bigshaq(char map[N][N], t_personnage * perso1, t_personnage * perso2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;
	int degat[4]={8,16,32,128}
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

	for(; i < N && nb < perso1->s4.portee && point[i][j] != 'o'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x;
	nb = 0;

	for(; i >= 0  && nb < perso1->s4.portee && point[i][j] != 'o'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; j < N && nb < perso1->s4.portee && point[i][j] != 'o'; j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < perso1->s4.portee && point[i][j] != 'o'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

	if(map[y][x] == '1' || map[y][x] == '2'){
		if(perso1->pv > 50)
			perso2->pv -= degat[0];
		if((perso1->pv > 25) && (perso1->pv <= 50))
			perso2->pv -= degat[1];
		if((perso1->pv > 2) && (perso1->pv <=25))
			perso2->pv -= degat[2];
		if(perso1->pv == 1)
			perso2->pv -= degat[3];
		printf("%s touché.\nPoint de vie : %i\n", perso2->nom, perso2->pv);
	}
}
