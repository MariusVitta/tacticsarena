#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "fonc.h"

#define N 11

/* Fonction permettant de deplacer son personnage et changer ses coordonnées
 * paramètre j1 : joueur que l'on souhaite déplacer
 * paramètre j2 : joueur non déplacer, utilisation de ses coordonnées pour éviter la superposition des joueurs
 * retourne : 1 si le déplacement a bien eu lieu
 */

int deplacement(t_personnage * j1,char mat[N][N]){
	int x,y;

	do{
		printf("saisir les coordonnées de la case ou vous voulez aller\n");

		scanf("%d %d",&x,&y);
	}
	while((((fabs(j1->coord.x-x)+fabs(j1->coord.y-y))>3) || (x<0 || x>=N) || (y<0 || y>=N)) || (mat[x][y]!='.'));


	j1->coord.x = x;

	j1->coord.y = y;

	return 1;
}
