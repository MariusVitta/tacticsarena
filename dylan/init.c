#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonc.h"


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
void initialisation(char matriceJeu[N][N],t_joueur * joueur1,t_joueur * joueur2){
	srand(time(NULL));
	int y1 = rand()%3+(N-3), x1 = rand()%(N-4)+2, y2, x2;
	int i,j,choix1 = 0,choix2 = 0,numero_j=1;
	int nb_persos = 1;
	int nb_obs = 10; /* nb d'obstacles max sur la carte*/
    /* remplissage de la map sans les joueurs positionnés */
	for(i = 0; i < N ; i++){
		for(j = 0;j < N; j++){
				matriceJeu[i][j] = '.';
		}
	}

	while(numero_j <=2){
		printf("\n ---- Choix des cases possibles pour le joueur %i ---- \n",numero_j);
		/* choix des positions du premier joueurs*/
		if(numero_j == 1){
			matriceJeu[y1][x1]='1';
			matriceJeu[y1-1][x1-2]='2';
			matriceJeu[y1 -1][x1 + 2]='3';
			printf("\n[1]{x=%i y=%i}\n[2]{x=%i y=%i}\n[3]{x=%i y=%i}\n",x1,y1,x1-2,y1-1,x1+2,y1-1);
			affichage_map(matriceJeu);
			do{
				printf("Choix pour le perso 1 du joueur %i: ",numero_j);
				scanf("%i", &choix1);
                printf("Choix pour le perso 2 du joueur %i: ",numero_j);
				scanf("%i", &choix2);

			}while( ((choix1 < 1)||(choix1 >3)) || ((choix2 < 1)||(choix2 >3)) || (choix1 == choix2) );

			switch(choix1){
				case 1: matriceJeu[y1][x1] = '1';
					matriceJeu[y1-1][x1-2]='.';
					matriceJeu[y1 -1][x1 + 2]='.';
					joueur1->perso1->coord.x = x1;
					joueur1->perso1->coord.y = y1;
				break;

				case 2:
                    matriceJeu[y1][x1] = '.';
					matriceJeu[y1-1][x1-2]='1';
					matriceJeu[y1 -1][x1 + 2]='.';
					joueur1->perso1->coord.x = x1-2;
					joueur1->perso1->coord.y = y1-1;
				break;

				case 3:
                    matriceJeu[y1][x1] = '.';
					matriceJeu[y1-1][x1-2]='.';
					matriceJeu[y1 -1][x1 + 2]='1';
					joueur1->perso1->coord.x = x1+2;
					joueur1->perso1->coord.y = y1-1;
				break;
			}
            switch(choix2){ /* choix case du perso 2 du joueur 1 */
				case 1: matriceJeu[y1][x1] = '3';
					matriceJeu[y1-1][x1-2]='.';
					matriceJeu[y1 -1][x1 + 2]='.';
                    matriceJeu[joueur1->perso1->coord.y][joueur1->perso1->coord.x] = '1';
					joueur1->perso2->coord.x = x1;
					joueur1->perso2->coord.y = y1;

				break;

				case 2: matriceJeu[y1][x1] = '.';
					matriceJeu[y1-1][x1-2]='3';
				    matriceJeu[y1 -1][x1 + 2]='.';
                    matriceJeu[joueur1->perso1->coord.y][joueur1->perso1->coord.x] = '1';
					joueur1->perso2->coord.x = x1-2;
					joueur1->perso2->coord.y = y1-1;
				break;

				case 3:matriceJeu[y1][x1] = '.';
					matriceJeu[y1-1][x1-2]='.';
					matriceJeu[y1 -1][x1 + 2]='3';
                    matriceJeu[joueur1->perso1->coord.y][joueur1->perso1->coord.x] = '1';
					joueur1->perso2->coord.x = x1+2;
					joueur1->perso2->coord.y = y1-1;
				break;
			}
		}
		else{
			/* choix des positions du deuxième joueur */
			y2 = rand()%3;
			x2 = rand()%(N-4)+2;
			matriceJeu[y2][x2]='4';
			matriceJeu[y2+1][x2-2]='5';
			matriceJeu[y2 +1][x2 + 2]='6';
			printf("\n[4]{x=%i y=%i}\n[5]{x=%i y=%i}\n[6]{x=%i y=%i}\n",x2 ,y2 ,x2 -2,y2+1,x2+2,y2+1);

			affichage_map(matriceJeu);
				do{
                    printf("Choix pour le perso 1 du joueur %i: ",numero_j);
    				scanf("%i", &choix1);
                    printf("Choix pour le perso 2 du joueur %i: ",numero_j);
    				scanf("%i", &choix2);
                }
                while(((choix1 < 4)||(choix1 >6)) || ((choix2 < 4)||(choix2 >6)) || (choix1 == choix2));

				switch(choix1){
					case 4: matriceJeu[y2][x2]='2';
						matriceJeu[y2+1][x2-2]='.';
						matriceJeu[y2 +1][x2 + 2]='.';
						joueur2->perso1->coord.x = x2;
						joueur2->perso1->coord.y = y2;
					break;

					case 5: matriceJeu[y2][x2]='.';
						matriceJeu[y2+1][x2-2]='2';
						matriceJeu[y2+1][x2 + 2]='.';
						joueur2->perso1->coord.x = x2-2;
						joueur2->perso1->coord.y = y2+1;
					break;

					case 6: matriceJeu[y2][x2]='.';
						matriceJeu[y2+1][x2-2]='.';
						matriceJeu[y2 +1][x2 + 2]='2';
						joueur2->perso1->coord.x = x2+2;
						joueur2->perso1->coord.y = y2+1;
					break;
				}
                switch(choix2){ /* perso 2 joueur 2 */
					case 4: matriceJeu[y2][x2]='4';
						matriceJeu[y2+1][x2-2]='.';
						matriceJeu[y2 +1][x2 + 2]='.';
                        matriceJeu[joueur2->perso1->coord.y][joueur2->perso1->coord.x] = '2';
						joueur2->perso2->coord.x = x2;
						joueur2->perso2->coord.y = y2;
					break;

					case 5: matriceJeu[y2][x2]='.';
						matriceJeu[y2+1][x2-2]='4';
						matriceJeu[y2+1][x2 + 2]='.';
                        matriceJeu[joueur2->perso1->coord.y][joueur2->perso1->coord.x] = '2';
						joueur2->perso2->coord.x = x2-2;
						joueur2->perso2->coord.y = y2+1;
					break;

					case 6: matriceJeu[y2][x2]='.';
						matriceJeu[y2+1][x2-2]='.';
						matriceJeu[y2 +1][x2 + 2]='4';
                        matriceJeu[joueur2->perso1->coord.y][joueur2->perso1->coord.x] = '2';
						joueur2->perso2->coord.x = x2+2;
						joueur2->perso2->coord.y = y2+1;
					break;
				}
		}

		choix1 = 0;
        choix2 = 0;
		numero_j++;
	}
    /* obstacles générés sur toutes la carte sauf les bords */
	int obs_x = rand()%(N-2)+1 , obs_y = rand()%(N-2)+1;

	/* génération des obstacles sur la carte */
	i = 1;
	while(i <= nb_obs){
		if(matriceJeu[obs_y][obs_x] == '.'){
			matriceJeu[obs_y][obs_x] = 'o';
			i++;
		}
		obs_x = rand()%(N-2)+1 , obs_y = rand()%(N-2)+1;
	}
	//affichage_map(matriceJeu);
}
