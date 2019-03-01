#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonc.h"
 
#define N 11

/**
 *\file init.c
 *\brief programme d'initialisation du jeu
 *\author Marius Vitta
 *\version 0.1
 *\date 28/02/2019
*/


/** 
 *\fn void initialisation(char matriceJeu[N][N],int joueur)
 *\brief initialise la position des deux joueurs
 *\param matriceJeu[N][N] matrice qui sert au tour du jeu
 *\param joueur numéro du joueur qui sera placé sur la carte
 *\return void 
 */
void initialisation(char matriceJeu[N][N], int joueur){
	//printf("Choix du placement du joueur %i\n",joueur);
	srand(time(NULL));
	int y = rand()%3+8, x = rand()%7+2;
	int i,j,choix = 0,numero_j=1;
	int nb = 0;
	while(numero_j <=2){
		printf("Choix des cases possibles pour le joueur %i:",numero_j);
		/* choix des positions du premier joueurs*/
		if(numero_j == 1){
			matriceJeu[y][x]='2';
			matriceJeu[y-1][x-2]='1';
			matriceJeu[y -1][x + 2]='3';
		}
		else{
			/* choix des positions du deuxième joueur */
			y = rand()%3;
			x = rand()%7+2;
			matriceJeu[y][x]='5';
			matriceJeu[y+1][x-2]='4';
			matriceJeu[y +1][x + 2]='6';
		}
		printf("\n[%i]{x=%i y=%i}\n [%i]{x=%i y=%i}\n [%i]{x=%i y=%i}\n",++nb,x-2,y+1,++nb,x,y,++nb, x+2,y+1);
		affichage_map(matriceJeu);
		printf("choix:");
		scanf("%i",&choix);

		switch(choix){
			case 1: matriceJeu[y-1][x-2]= '*';matriceJeu[y][x] = ' ';matriceJeu[y -1][x + 2] = ' ';break;
			case 2: matriceJeu[y][x] = '*';matriceJeu[y -1][x + 2] = ' ';matriceJeu[y-1][x-2]= ' ';break;
			case 3: matriceJeu[y -1][x + 2] = '*';matriceJeu[y][x] = ' ';matriceJeu[y-1][x-2]= ' ';break;
			case 4: matriceJeu[y+1][x-2]= '*';matriceJeu[y][x] = ' ';matriceJeu[y +1][x + 2] = ' ';break;
			case 5: matriceJeu[y][x] = '*';matriceJeu[y +1][x + 2] = ' ';matriceJeu[y+1][x-2]= ' ';break;
			case 6: matriceJeu[y +1][x + 2] = '*';matriceJeu[y][x] = ' ';matriceJeu[y+1][x-2]= ' ';break;
			/*default: matriceJeu[y][x]='*';break;*/
		}
		choix = 0;
		numero_j++;
	}
	affichage_map(matriceJeu);
/*
	printf("(*) x joueur 1 = %i y joueur 1 = %i\n",x,y);
	printf("(X) x joueur 2 = %i y joueur 2 = %i\n",N-x,N-y-1);
*/
	for(i = 0; i < N ; i++){
		for(j = 0;j < N; j++){
			if(matriceJeu[i][j] != '*' && matriceJeu[i][j] != '*'){
				matriceJeu[i][j] = '.';
			}
		}

	}

}
