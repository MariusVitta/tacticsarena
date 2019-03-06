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
void initialisation(char matriceJeu[N][N],t_personnage * perso1,t_personnage * perso2){
	//printf("Choix du placement du joueur %i\n",joueur);
	srand(time(NULL));
	int y1 = rand()%3+(N-3), x1 = rand()%(N-4)+2, y2, x2;
	int i,j,choix = 0,numero_j=1;
	int nb = 1;

	// remplissage de la map sans les joueurs positionnés 
	for(i = 0; i < N ; i++){
		for(j = 0;j < N; j++){
			//if(matriceJeu[i][j] != '*' && matriceJeu[i][j] != '*'){
				matriceJeu[i][j] = '.';
			//}
		}
	}


	int obs_x = rand()%10+1 , osb_y = rand()%3+4;

	/* génération des obstacles sur la carte */
<<<<<<< HEAD
	i = 1;/*
	while(i <= 5){
=======
	//i = 1;
	/*while(i <= 5){
>>>>>>> 760b49bb5fbe602751b8be5be13f041e13501c70
		matriceJeu[obs_x][osb_y] = 1;
	}*/



	while(numero_j <=2){
<<<<<<< HEAD
		printf("Choix des cases possibles pour le joueur %i:",numero_j);
		/* choix des positions du premier joueurs*/
		if(numero_j == 1){
			matriceJeu[y][x]='2';
			matriceJeu[y-1][x-2]='1';
			matriceJeu[y -1][x + 2]='3';
			printf(" \n[1]{x=%i y=%i}\n [2]{x=%i y=%i}\n [3]{x=%i y=%i}\n",x-2+1,y-1+1,x+1,y+1,x+2+1,y-1+1);
=======
		printf("Choix des cases possibles pour le jouerez %i:",numero_j);
		/* choix des positions du premier joueurs*/
		if(numero_j == 1){
			matriceJeu[y1][x1]='1';
			matriceJeu[y1-1][x1-2]='2';
			matriceJeu[y1 -1][x1 + 2]='3';
			printf("\n[1]{x=%i y=%i}\n[2]{x=%i y=%i}\n[3]{x=%i y=%i}\n",x1,y1,x1-2,y1-1,x1+2,y1-1);
			affichage_map(matriceJeu);
			do{
				printf("Choix: ");
				scanf("%i", &choix);

			}while((choix < 1)||(choix >3));

			switch(choix){
				case 1: matriceJeu[y1][x1] = '*';
					matriceJeu[y1-1][x1-2]='.';
					matriceJeu[y1 -1][x1 + 2]='.';
					perso1->coord.x = x1; 
					perso1->coord.y = y1; 
				break;
					
				case 2: matriceJeu[y1][x1] = '.';
					matriceJeu[y1-1][x1-2]='*';
					matriceJeu[y1 -1][x1 + 2]='.';
					perso1->coord.x = x1-2; 
					perso1->coord.y = y1-1; 
				break;
				
				case 3: matriceJeu[y1][x1] = '.';
					matriceJeu[y1-1][x1-2]='.';
					matriceJeu[y1 -1][x1 + 2]='*';
					perso1->coord.x = x1+2; 
					perso1->coord.y = y1-1; 
				break;
			}
>>>>>>> 760b49bb5fbe602751b8be5be13f041e13501c70
		}

		else{
			/* choix des positions du deuxième joueur */
<<<<<<< HEAD
			y = rand()%3;
			x = rand()%(N-4)+2;
			matriceJeu[y][x]='5';
			matriceJeu[y+1][x-2]='4';
			matriceJeu[y +1][x + 2]='6';
			printf(" \n[4]{x=%i y=%i}\n [5]{x=%i y=%i}\n [6]{x=%i y=%i}\n",x-2+1,y+1+1,x,y,x+2+1,y+1+1);
		}
		affichage_map(matriceJeu);
		/* gestion erreurs de saisie de l'utilisateur */
		switch(numero_j){
			case 1:do{
						printf("choix:");
						scanf("%i",&choix);
					}
					while(choix<1 || choix>3);break;

			case 2:do{
						printf("choix:");
						scanf("%i",&choix);
					}
					while(choix<4 || choix>6);break;
		}
		//affichage_map(matriceJeu);
		
		switch(choix){
			/* choix de la position du joueur avec le caractère '*' */
			case 1: matriceJeu[y-1][x-2]= '*' ; 
					matriceJeu[y][x] = '.'; 
					matriceJeu[y -1][x + 2] = '.'; 
					perso1->coord.x = x-2 ; 
					perso1->coord.y = y- 1;break;

			case 2: matriceJeu[y][x] = '*'; 
					matriceJeu[y -1][x + 2] = '.'; 
					matriceJeu[y-1][x-2]= '.'; 
					perso1->coord.x = x ; 
					perso1->coord.y = y;break;

			case 3: matriceJeu[y -1][x + 2] = '*'; 
					matriceJeu[y][x] = '.'; 
					matriceJeu[y-1][x-2]= '.'; 
					perso1->coord.x = x+2 ; 
					perso1->coord.y = y- 1;break;

			case 4: matriceJeu[y+1][x-2]= '$'; 
					matriceJeu[y][x] = '.'; 
					matriceJeu[y +1][x + 2] = '.'; 
					perso2->coord.x = x-2; 
					perso2->coord.y = y + 1;break;

			case 5: matriceJeu[y][x] = '$'; 
					matriceJeu[y +1][x + 2] = '.'; 
					matriceJeu[y+1][x-2]= '.'; 
					perso2->coord.x = x ; 
					perso2->coord.y = y ;break;

			case 6: matriceJeu[y +1][x + 2] = '$'; 
					matriceJeu[y][x] = '.'; 
					matriceJeu[y+1][x-2]= '.'; 
					perso2->coord.x = x+2; 
					perso2->coord.y = y + 1;break;
=======
			y2 = rand()%3;
			x2 = rand()%(N-4)+2;
			matriceJeu[y2][x2]='4';
			matriceJeu[y2+1][x2-2]='5';
			matriceJeu[y2 +1][x2 + 2]='6';
			printf("\n[4]{x=%i y=%i}\n[5]{x=%i y=%i}\n[6]{x=%i y=%i}\n",x2 ,y2 ,x2 -2,y2+1,x2+2,y2+1);
			
			affichage_map(matriceJeu);
				do{
				printf("Choix: ");
				scanf("%i", &choix);

				}while((choix < 4)||(choix >6));

				switch(choix){
					case 4: matriceJeu[y2][x2]='$';
						matriceJeu[y2+1][x2-2]='.';
						matriceJeu[y2 +1][x2 + 2]='.';
						perso2->coord.x = x2; 
						perso2->coord.y = y2; 
					break;
						
					case 5: matriceJeu[y2][x2]='.';
						matriceJeu[y2+1][x2-2]='$';
						matriceJeu[y2+1][x2 + 2]='.';
						perso2->coord.x = x2-2; 
						perso2->coord.y = y2+1; 
					break;
					
					case 6: matriceJeu[y2][x2]='.';
						matriceJeu[y2+1][x2-2]='.';
						matriceJeu[y2 +1][x2 + 2]='$';
						perso2->coord.x = x2+2; 
						perso2->coord.y = y2+1; 
					break;
				}
>>>>>>> 760b49bb5fbe602751b8be5be13f041e13501c70
		}

		choix = 0;
		numero_j++;
	}
	affichage_map(matriceJeu);

}
