#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "fonc.h"

#define N 11

/* Fonction permettant de deplacer son personnage et changer ses coordonnées
 * paramètre j1 : joueur que l'on souhaite déplacer
 * paramètre map
 * retourne : 1 si le déplacement a bien eu lieu
 */

int saut(t_personnage * j1,char map[N][N]){
	int x,y;

	do{
		printf("Saisir les coordonnées de la case où vous voulez aller\n");

		scanf("%d %d",&x,&y);
	}

	while((((fabs(j1->coord.x-x)+fabs(j1->coord.y-y))>3) || (x<0 || x>=N) || (y<0 || y>=N)) || (map[y][x]!='.'));

	j1->coord.x = x;

	j1->coord.y = y;

	return 1;
}



int deplacement(t_personnage * j1,t_personnage j2,char map[N][N],int  n ){

	char c;

	//while (n > 0) {

		do{
		printf("Choisissez l'initial entre haut, bas, gauche, ou droite pour vous déplacer ou R pour rester sur place\n");

		scanf(" %c",&c);
		}
		while(c != 'h' && c != 'b' && c != 'g' && c != 'd' && c != 'R');



		switch (c) {
			case 'h':

				if(j1->coord.y-1<0 || (map[j1->coord.y-1][j1->coord.x]!='.')){

					break;
				}
				else{
					j1->coord.y--;
					printf("Haut\n");
					n--;
					break;
				}

			case 'b':

				if(j1->coord.y+1>=N || (map[j1->coord.y+1][j1->coord.x]!='.')){

					break;
				}

				else{
					j1->coord.y++;
					printf("Bas\n");
					n--;
					break;
				}

			case 'g':

				if(j1->coord.x-1<0 || (map[j1->coord.y][j1->coord.x-1]!='.')){

					break;
				}

				else{
					j1->coord.x--;
					printf("Gauche\n");
					n--;
					break;
				}

			case 'd':

				if(j1->coord.x+1>=N || (map[j1->coord.y][j1->coord.x+1]!='.')){

					break;
				}

				else{
					j1->coord.x++;
					printf("Droite\n");
					n--;
					break;
				}

			case 'R':
				return n;
		}
		maj(map,*j1,j2);
		affichage_map(map);

	//}

	return n;
}
