#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <fonc.h>

#define N 11

/*Fonction permettant de deplacer son personnage et changer ses coordonnées*/

int deplacement(t_personnage j1,t_personnage j2){

	int x,y;

	do{
		printf("saisir les coordonnées de la case ou vous voulez aller\n");

		scanf("%d %d",&x,&y);
	}

	while(((fabs(j1.coord.x-x)+fabs(j1.coord.y-y))<=3) && (x<0 || x>=N) && (y<0 || y>=N) && (j1.coord.x!=j2.coord.x || j1.coord.y!=j2.coord.y));


	j1.coord.x = x;

	j1.coord.y = y;

	return(j1);
}

