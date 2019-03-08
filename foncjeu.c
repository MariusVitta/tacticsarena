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
			if(map[i][j] != 'o')
				map[i][j] = '.';
		}

	}

	map[perso1.coord.y][perso1.coord.x] = '*';
	map[perso2.coord.y][perso2.coord.x] = '$';

	int x1 = perso1.coord.x;
	int y1 = perso1.coord.y;

}

static int existe(char mat[N][N], char choix, int * x, int * y){

	int i, j;

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

void diago(char map[N][N], t_personnage perso1, t_personnage * perso2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;
/*copie plan jeu dans la matrice point*/

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = perso1.coord.y + 1;
	j = perso1.coord.x + 1;


	int nb = 0;

	printf("%i\n", perso1.s1.portee);

	for(; (i < N && j < N) && nb < perso1.s1.portee && point[i][j] != 'o'; i++, j++, nb++)
		point[i][j] = 'A' + nb;

	i = perso1.coord.y - 1;
	j = perso1.coord.x - 1;
	nb = 0;

	for(; (i >= 0  && j >= 0) && nb < perso1.s1.portee && point[i][j] != 'o'; i--, j--, nb++)
		point[i][j] = 'G' + nb;

	i = perso1.coord.y - 1;
	j = perso1.coord.x + 1;
	nb = 0;

	for(; (i >= 0  && j < N) && nb < perso1.s1.portee && point[i][j] != 'o'; i--, j++, nb++)
		point[i][j] = 'M' + nb;

		i = perso1.coord.y + 1;
		j = perso1.coord.x - 1;
		nb = 0;

	for(; (i < N  && j >= 0) && nb < perso1.s1.portee && point[i][j] != 'o'; i++, j--, nb++)
		point[i][j] = 'S' + nb;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

	//printf("x = %i y = %i\n", x, y);
	if(map[y][x] == map[i][j])
		perso2->pv -= perso1.s1.degat;


}
