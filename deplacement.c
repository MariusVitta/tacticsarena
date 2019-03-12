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
	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist=j1->s3.portee,car=0;
	char choix;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}
	i = j1->coord.y;
	j = j1->coord.x - dist ;

	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = j1->coord.x - dist ;
		for( ; (j >= 0 && j < N)  && (j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] != '*' && point[i][j] != 'o'){
						point[i][j] = 'A' + car;
						car++;
						if('A' + car == 'o')
							car++;
					}
				}
			}
		}
	}

	dist=j1->s1.portee;
	g = j1->coord.y;
	j = j1->coord.x - dist ;

	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = j1->coord.x - dist ;
		for( ; (j >= 0 && j < N)  && (j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] != '*' && point[g][j] != 'o'){
						if(g != j1->coord.y){
								point[g][j] = 'A' + car;
								car ++;
						}
					}
				}
			}
		}
	}

	do{
			printf("Où souhaitez vous aller : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));





	while((((abs(j1->coord.x-x)+abs(j1->coord.y-y))>3) || (x<0 || x>=N) || (y<0 || y>=N)) || (map[y][x]!='.'));

	j1->coord.x = x;

	j1->coord.y = y;


	/* affichage */
	affichage_map(point);


	return 1;
}



/*avec personnage n le nombre de deplacements qu'il reste et nbj le numero du joueur*/
int deplacement(t_personnage * j1,t_personnage * j2,char map[N][N],int  n ,int nbj){

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
					(j1->coord.y)--;
					printf("Déplacement en haut \n");
					n--;
					break;
				}

			case 'b':

				if(j1->coord.y+1>=N || (map[j1->coord.y+1][j1->coord.x]!='.')){

					break;
				}

				else{
					(j1->coord.y)++;
					printf("Déplacement en bas \n");
					n--;
					break;
				}

			case 'g':

				if(j1->coord.x-1<0 || (map[j1->coord.y][j1->coord.x-1]!='.')){

					break;
				}

				else{
					(j1->coord.x)--;
					printf("Déplacement à gauche \n");
					n--;
					break;
				}

			case 'd':

				if(j1->coord.x+1>=N || (map[j1->coord.y][j1->coord.x+1]!='.')){

					break;
				}

				else{
					(j1->coord.x)++;
					printf("Déplacement à droite \n");
					n--;
					break;
				}

			case 'R':
				return n;
		}
		if(nbj==1){
			maj(map,*j1,*j2);
			affichage_map(map);
		}
		else{
			maj(map,*j2,*j1);
			affichage_map(map);
		}
	//}

	return n;
}
