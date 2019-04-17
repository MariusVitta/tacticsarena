#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


char map[N][N];

int main(){

	int i, j, classe1, classe2,nb_tour = 1,mort1 = 0,mort2 = 0;
    int num_j = 1,choix;
	t_joueur joueur1,joueur2;

	do{
		printf("Joueur 1: choisir une classe personnage 1 et classe personnage 2\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\nChoix personnage 1: ");
		scanf("%d",&classe1);
        printf("Choix personnage 2: ");
        scanf("%d",&classe2);

		if((classe1 != 1)&&(classe1 != 2) || (classe2 != 1)&&(classe2 != 2) )
			printf("Vous devez taper 1 ou 2\n");

	}while((classe1 != 1)&&(classe1 != 2) || (classe2 != 1)&&(classe2 != 2));
    joueur1.perso1 = malloc(sizeof(t_personnage));
    joueur1.perso2 = malloc(sizeof(t_personnage));
    creer_perso(classe1,joueur1.perso1);
	creer_perso(classe2,joueur1.perso2);
    joueur1.numJoueur = 1;
    joueur1.nbPVivant = 2;



    do{
		printf("Joueur 2: choisir une classe personnage 1 et classe personnage 2\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\nChoix personnage 1: ");
		scanf("%d",&classe1);
        printf("Choix personnage 2: ");
        scanf("%d",&classe2);

		if((classe1 != 1)&&(classe1 != 2) || (classe2 != 1)&&(classe2 != 2) )
			printf("Vous devez taper 1 ou 2\n");

	}while((classe1 != 1)&&(classe1 != 2) || (classe2 != 1)&&(classe2 != 2));

    joueur2.perso1 = malloc(sizeof(t_personnage));
    joueur2.perso2 = malloc(sizeof(t_personnage));
	creer_perso(classe1,joueur2.perso1 );
	creer_perso(classe2,joueur2.perso2);
    joueur2.numJoueur = 1;
    joueur2.nbPVivant = 2;


    /*joueur1.pv = 10;
    joueur2.pv = 5;
    */
	initialisation(map,&joueur1,&joueur2);
    printf("===================================================\n\tDEMARRAGE DE LA  PARTIE\n===================================================\n");
    affichage_map(map);
    while(joueur1.nbPVivant > 0 && joueur2.nbPVivant > 0){
        printf("[Tour numéro:%i][Tour du joueur %i]\n\n",nb_tour,num_j);
        printf(" ---- Quel personnage voulez vous utiliser pour ce tour ---- \nChoix[1][3]: ");
        scanf("%i",&choix);
        tour(map,joueur1.perso1,joueur2.perso1,1);
        affichage_map(map);
        num_j++;
				//verifie si les personnages sont vivant au ( refaire a chaque fin de tour )
        /*mort1 = est_mort(personnage1);
				mort2= est_mort(personnage2);
        // si le personnage 1 est mort on effectue pas le tour du joueur
        if(!mort1 && !mort2){
            printf("[Tour numéro:%i][Tour du joueur %i]\n\n",nb_tour,num_j);
            printf(" ---- Quel personnage voulez vous utiliser pour ce tour ---- \nChoix[2][4]: ");
            scanf("%i",&choix);
            tour(map,&personnage2,&personnage1,2);
            affichage_map(map);
        }*/
    }

    affichage_coord(joueur1);
    affichage_coord(joueur2);
    free(joueur1.perso1);
    free(joueur1.perso2);
    free(joueur2.perso1);
    free(joueur2.perso2);
/*
	if(est_mort(joueur1))
		printf("Le personnage '%s' est mort\n", joueur1.nom);
	else if(est_mort(joueur2))
		printf("Le personnage '%s' est mort\n", joueur1.nom);
*/
	return 0;
}
