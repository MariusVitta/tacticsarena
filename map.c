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
	printf("Placement du joueur %i\n",joueur);
	srand(time(NULL));
	int y = rand()%2+6,x = rand()%12,i;
	matriceJeu[x][y] = '1';
	matriceJeu[-x][-y] = '2';
	//printf("x = %i y = %i\n",x,y);
	for(i = 0,i < N ,i++){
		for(j = 0,j < N, J++){
			if(matriceJeu[i][j] != '1' || matriceJeu[i][j] != '2'){
				matriceJeu[i][j] = 'x';
			}
		}

	}

}


int main(){  
	char jeu[N][N];
	initialisation(jeu,2);


	return 0;
}