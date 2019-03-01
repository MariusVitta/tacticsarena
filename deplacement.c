#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <fonc.h>

#define N 11

/*Fonction permettant de deplacer son personnage et changer ses coordonnées*/

int deplacement(t_coordonnees coordj1,t_coordonnees coordj2){

	int x,y;

	do{
		printf("saisir les coordonnées de la case ou vous voulez aller\n");

		scanf("%d %d",&x,&y);
	}
	while(((fabs(coordj1.x-x)+fabs(coordj1.y-y))<=3) && (x<0 || x>=N) && (y<0 || y>=N) && (coordj1.x!=coordj2.x || coordj1.y!=coordj2;y));

	coordj1.x = x;

	coordj1.y = y;

	return(coordj1);
}

int main(){



	return 0;
}