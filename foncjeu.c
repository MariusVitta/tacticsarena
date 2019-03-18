#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

int est_mort(t_personnage * perso){
	return (perso->pv <= 0);
}

void maj(char map[N][N], t_joueur joueur1, t_joueur joueur2){
	int i, j;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(map[i][j] != 'o')
				map[i][j] = '.';
        }
	}

    /* joueur 1 */
	map[joueur1.perso1->coord.y][joueur1.perso1->coord.x] = '1';
    map[joueur1.perso2->coord.y][joueur1.perso2->coord.x] = '3';
    /* joueur 2*/
	map[joueur2.perso1->coord.y][joueur2.perso1->coord.x] = '2';
    map[joueur2.perso2->coord.y][joueur2.perso2->coord.x] = '4';
    /*
	int x1 = joueur1.perso1->coord.x;
	int y1 = joueur1.perso1->coord.y;
    */
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

void diago(char map[N][N], t_personnage * perso1, t_personnage * perso2){

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
	j = perso1->coord.x + 1;


	int nb = 0;
	int car = 0;
	//printf("%i\n", perso1.s1.portee);

	for(; (i < N && j < N) && nb < perso1->s1.portee && point[i][j] == '.'; i++, j++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x - 1;
	nb = 0;

	for(; (i >= 0  && j >= 0) && nb < perso1->s1.portee && point[i][j] == '.'; i--, j--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; (i >= 0  && j < N) && nb < perso1->s1.portee && point[i][j] == '.'; i--, j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y + 1;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; (i < N  && j >= 0) && nb < perso1->s1.portee && point[i][j] == '.'; i++, j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

	//printf("x = %i y = %i\n", x, y);
	if(map[y][x] == '1' || map[y][x] == '2'){
		perso2->pv -= perso1->s1.degat;
		printf("%s touché.\nPoint de vie : %i\n", perso2->nom, perso2->pv);
	}

}

void ligne(char map[N][N], t_personnage * perso1, t_personnage * perso2){

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

	if(map[y][x] == '1' || map[y][x] == '2'){
		perso2->pv -= perso1->s2.degat;
		printf("%s touché.\nPoint de vie : %i\n", perso2->nom, perso2->pv);
	}
}

void grosCoup(char map[N][N], t_personnage * perso1, t_personnage * perso2){

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
		perso2->pv -= perso1->s4.degat;
		printf("%s touché.\nPoint de vie : %i\n", perso2->nom, perso2->pv);
	}
}
