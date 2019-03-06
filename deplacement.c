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

int deplacement(t_personnage * j1,t_personnage j2){
	int x,y,dep_reste=3,x2,y2;

	//affiche_coordonnee();

	//demande la saisie de la nouvelle coordonnee
	do{
		printf("saisir les coordonnées de la case ou vous voulez aller\n");
		scanf("%d %d",&x,&y);

	//Vérifie que le personnage ne se déplace pas de plus de 3 cases & que le perso ne sorte pas de la matrice & qu'il ne va pas sur une case occupée
		x2=fabs(j1->coord.x-x);
		y2=fabs(j1->coord.y-y);
	}while( (x2+y2)<=3) && (x>=0 && x<N) && (y>=0 && y<N) && (x!=j2.coord.x || y!=j2.coord.y) ) ;       
	// need rajouter la verif qu'il n'y a pas d'obstacle

	j1->coord.x = x;

	j1->coord.y = y;

	dep_reste -= x2+y2;

	return dep_reste;
}

