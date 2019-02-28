#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 
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
 *\brief renvoie le chiffre correspondant au caractère entre '0' et '9' recu en paramètre
 *\param matriceJeu[N][N] matrice qui sert au tour du jeu
 *\param joueur numéro du joueur qui sera placé sur la carte
 *\return void 
 */
void initialisation(char matriceJeu[N][N], int joueur){
	//printf("Placement du joueur %i\n",joueur);
	srand(time(NULL));
	int y = rand()%3+8, x = rand()%11+1;

	int i,j;


	matriceJeu[y-1][x-1] = '*';
	matriceJeu[N-y-1][N-x] = 'x';

	printf("(*) x joueur 1 = %i y joueur 1 = %i\n",x,y);
	printf("(X) x joueur 2 = %i y joueur 2 = %i\n",N-x,N-y-1);

	for(i = 0; i < N ; i++){
		for(j = 0;j < N; j++){
			if(matriceJeu[i][j] != 'x' && matriceJeu[i][j] != '*'){
				matriceJeu[i][j] = '.';
			}
		}

	}

}
