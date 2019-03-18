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

int saut(t_joueur j1,t_joueur j2,char map[N][N],int nbj,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g,car=0;
	char choix;

    t_personnage * temp;
    if(numero_perso == 1 ){
        temp = j1.perso1;
    }
    else{
        temp = j1.perso2;
    }
    int dist=temp->s1.portee;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					//verifie si il y a un obstacle ou un joueur à l'emplacement
					if(point[i][j] == '.'){
						point[i][j] = 'A' + car;
						car++;
						if('A' + car == 'o')
							car++;
					}
				}
			}
		}
	}

	dist=temp->s1.portee;
	g = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != temp->coord.y){
								point[g][j] = 'A' + car;
								car ++;
						}
					}
				}
			}
		}
	}

	/* affichage */
	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous sauter : ");
			scanf(" %c", &choix);
	}while((!existe(point, choix, &x, &y)) || (((abs(temp->coord.x-x)+abs(temp->coord.y-y))>3) || (x<0 || x>=N) || (y<0 || y>=N)) || (map[y][x]!='.'));


	temp->coord.x = x;

	temp->coord.y = y;



	if(nbj==1){
		maj(map,j1,j2);
		affichage_map(map);
	}
	else{
		maj(map,j2,j1);
		affichage_map(map);
	}

	return 1;
}

/*avec personnage n le nombre de deplacements qu'il reste et nbj le numero du joueur*/
int deplacement(t_joueur j1,t_joueur j2,char map[N][N],int  n ,int nbj,int numero_perso ){
    t_personnage * temp;
    if(numero_perso == 1 ){
        temp = j1.perso1;
    }
    else{
        temp = j1.perso2;
    }
	char c;

	//while (n > 0) {

		do{
		printf("Choisissez l'initial entre haut, bas, gauche, ou droite pour vous déplacer ou R pour rester sur place\n");

		scanf(" %c",&c);
		}
		while(c != 'h' && c != 'b' && c != 'g' && c != 'd' && c != 'R');



		switch (c) {
			case 'h':

				if(temp->coord.y-1<0 || (map[temp->coord.y-1][temp->coord.x]!='.')){
  				printf(" ---- Déplacement impossible ---- \n" );
					break;
				}
				else{
					(temp->coord.y)--;
  				printf(" ---- Déplacement en Haut ---- \n" );
					n--;
					break;
				}

			case 'b':

				if(temp->coord.y+1>=N || (map[temp->coord.y+1][temp->coord.x]!='.')){
  				printf(" ---- Déplacement impossible ---- \n" );
					break;
				}

				else{
					(temp->coord.y)++;
  				printf(" ---- Déplacement en Bas ---- \n" );
					n--;
					break;
				}

			case 'g':

				if(temp->coord.x-1<0 || (map[temp->coord.y][temp->coord.x-1]!='.')){
  				printf(" ---- Déplacement impossible ---- \n" );
					break;
				}

				else{
					(temp->coord.x)--;
  				printf(" ---- Déplacement à Gauche ---- \n" );
					n--;
					break;
				}

			case 'd':

				if(temp->coord.x+1>=N || (map[temp->coord.y][temp->coord.x+1]!='.')){
  				printf(" ---- Déplacement impossible ---- \n" );
					break;
				}

				else{
					(temp->coord.x)++;
  				printf(" ---- Déplacement à Droite ---- \n" );
					n--;
					break;
				}

			case 'R':

				return n;
		}
		if(nbj==1){
			maj(map,j1,j2);
			affichage_map(map);
		}
		else{
			maj(map,j2,j1);
			affichage_map(map);
		}
	//}

	return n;
}
