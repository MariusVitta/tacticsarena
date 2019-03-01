#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonc.h"
 
#define N 11

/**
 *\file map.c
 *\brief programme d'initialisation du jeu
 *\author Marius Vitta
 *\version 0.1
 *\date 28/02/2019
*/


/** 
 *\fn void initialisation(char matriceJeu[N][N],int joueur)
 *\brief initialise le jeu
 *\param matriceJeu[N][N] matrice qui sert au tour du jeu
 *\param joueur numéro du joueur qui sera placé sur la carte
 *\return void 
 */
void initialisation(char matriceJeu[N][N], int joueur){
	//printf("Choix du placement du joueur %i\n",joueur);
	srand(time(NULL));
	int y = rand()%3+8, x = rand()%7+2;
	int i,j,choix = 0,numero_j=1;
	while(numero_j <=2){
		printf("Choix des cases possibles pour le joueur %i:",numero_j);
		matriceJeu[y][x]='+';
		matriceJeu[y-1][x-2]='+';
		matriceJeu[y -1][x + 2]='+';
		printf("\n[1]{x=%i y=%i}\n [2]{x=%i y=%i}\n [3]{x=%i y=%i}\n",x-2,y-1,x,y,x+2,y-1);
		affichage_map(matriceJeu);
		printf("choix:");
		scanf("%i",&choix);
		switch(choix){
			case 1: matriceJeu[y-1][x-2]= '*';break;
			case 2: matriceJeu[y][x] = '*';break;
			case 3: matriceJeu[y -1][x + 2] = '*';break;
			default: matriceJeu[y][x]='*';break;
		}
		choix = 0;
		numero_j++;
	}
	affichage_map(matriceJeu);
	/*
	matriceJeu[y-1][x-1] = '1';
	matriceJeu[N-y-1][N-x] = '2';
	*/
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
