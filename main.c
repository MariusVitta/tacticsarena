#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


char map[N][N];

int main(){

	int i, j, classe1, classe2,nb_tour = 1,mort1 = 0,mort2 = 0;
    int num_j = 1;
	t_personnage personnage1,personnage2;

	do{
		printf("Joueur 1: choisir une classe\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\nChoix:");
		scanf("%d",&classe1);

		if((classe1 != 1)&&(classe1 != 2))
			printf("Vous devez taper 1 ou 2\n");

	}while((classe1 != 1)&&(classe1 != 2));

	do{
		printf("Joueur 2: choisir une classe\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\nChoix:");


		scanf("%d",&classe2);

		if((classe2 != 1)&&(classe2 != 2))
			printf("Vous devez taper 1 ou 2\n");

	}while((classe2 != 1)&&(classe2 != 2));

	personnage1 = creer_perso(classe1,&personnage1);
	personnage2 = creer_perso(classe2,&personnage2);
    personnage1.pv = 10;
    personnage2.pv = 5;

	initialisation(map,&personnage1,&personnage2);
    printf("===================================================\n\tDEMARRAGE DE LA  PARTIE\n===================================================\n");
    affichage_map(map);

    /* boucle principale du jeu */
    while(!est_mort(personnage1) && !est_mort(personnage2)){
        printf("[Tour numéro:%i][Tour du joueur %i]\n\n",nb_tour,num_j);
        tour(map,&personnage1,&personnage2,1);
        affichage_map(map);
        num_j++;
        mort1 = est_mort(personnage1);
				  mort2= est_mort(personnage2);
        /* si le personnage 1 est mort on effectue pas le tour du joueur */
        if(!mort1 && !mort2){
            printf("[Tour numéro:%i][Tour du joueur %i]\n\n",nb_tour,num_j);
            tour(map,&personnage2,&personnage1,2);
            affichage_map(map);
        }
        if( !mort1 && !mort2 ){
		          printf("===================================================\n\tAFFICHAGE COORDONNEES\n===================================================\n");
		          affichage_coord(personnage2);
		          affichage_coord(personnage1);
        }
        num_j--;
        nb_tour++;
   }
   printf("===================================================\n\tFIN DE LA PARTIE\n===================================================\n");

	if(est_mort(personnage1))
		printf("Le personnage '%s' est mort\n", personnage1.nom);
	else if(est_mort(personnage2))
		printf("Le personnage '%s' est mort\n", personnage1.nom);

	return 0;
}
