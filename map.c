#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonc.h"
 
#define N 11
char map[N][N];
/**
 *\file map.c
 *\brief programme d'initialisation du jeu
 *\author Marius Vitta
 *\version 0.1
 *\date 28/02/2019
*/


/** 
 *\fn void initialisation(char matriceJeu[N][N],int joueur)
 *\brief renvoie le chiffre correspondant au caractère entre '0' et '9' recu en paramètre
 *\param matriceJeu[N][N] matrice qui sert au tour du jeu
 *\param joueur numéro du joueur qui sera placé sur la carte
 *\return void 
 */
void initialisation(char matriceJeu[N][N], int joueur){
	printf("Placement du joueur %i",joueur);
	srand(time(NULL));
	int x = rand(),y = rand()%8;

	printf("x = %i y = %i\n",x,y );


}


int main(){  
	int i, j;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++)
			map[i][j] = 'a' + i + j;
	}

	affichage_map(map);
	char jeu[N][N];
	initialisation(jeu[N][N],2);


	return 0;
}