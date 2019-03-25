#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

#define NB_PERSONNAGES 2

char map[N][N];

int main(){

	int i, j, classe1, classe2,nb_tour = 1,mort1 = 0,mort2 = 0;
    int indice_joueur = 1,numero_personnage = 1;
    t_joueur joueur1,joueur2;

	do{ /* choix personnage du joueur 1 */
		printf("Joueur 1: choisir une classe personnage 1 et classe personnage 2\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\nChoix personnage 1: ");
		scanf("%d",&classe1);
        printf("Choix personnage 2: ");
        scanf("%d",&classe2);

		if((classe1 != 1)&&(classe1 != 2) || (classe2 != 1)&&(classe2 != 2) )
			printf("Vous devez taper 1 ou 2\n");

	}while((classe1 != 1)&&(classe1 != 2) || (classe2 != 1)&&(classe2 != 2));

		joueur1.perso1 = creer_perso(classe1);
		joueur1.perso2 = creer_perso(classe2);
    joueur1.numJoueur = 1;
    joueur1.nbPersoVivant = NB_PERSONNAGES;

    /* choix des personnages du joueur 2 */
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

		joueur2.perso1 = creer_perso(classe1);
		joueur2.perso2 = creer_perso(classe2);
    joueur2.numJoueur = 2;
    joueur2.nbPersoVivant = NB_PERSONNAGES;


	initialisation(map,&joueur1,&joueur2);
    printf("===================================================\n\tDEMARRAGE DE LA  PARTIE\n===================================================\n");
	joueur1.perso1->coord.x = joueur1.perso1->coord.y = 5;
	joueur1.perso2->coord.x = joueur1.perso2->coord.y = 4;
	joueur2.perso1->coord.x = joueur2.perso1->coord.y = 6;
	joueur2.perso2->coord.x = 5;
	joueur2.perso2->coord.y = 4;
	maj(map,&joueur1,&joueur2);
	affichage_map(map);

	joueur1.perso1->pv = 1;
	joueur1.perso2->pv = 1;
	joueur2.perso1->pv = 1;
	joueur2.perso2->pv = 1;


    /* boucle principale du jeu */
    while(!partie_finie(joueur1) && !partie_finie(joueur2)){
        for(numero_personnage = 1 ; numero_personnage <= NB_PERSONNAGES; numero_personnage++){
            printf("[Tour numéro:%i][Tour du joueur %i][personnage :%i]{%c}\n\n",nb_tour,indice_joueur,numero_personnage,carac_perso(indice_joueur,numero_personnage));
			/* si le personnage est mort on ne le fais plus jouer */
			if(numero_personnage == 1 && !est_mort(&joueur1,numero_personnage)){
                tour(map,&joueur1,&joueur2,1,numero_personnage); /* tour du personnage 1 du joueur 1 */
            }
            else if(!est_mort(&joueur1,numero_personnage) && !partie_finie(joueur2)){
                tour(map,&joueur1,&joueur2,1,numero_personnage); /* tour du personnage 2 du joueur 1 */
            }
			maj(map,&joueur1,&joueur2);
            affichage_map(map);
        }
        indice_joueur++;

		printf("perso 1 : %i\n",joueur1.nbPersoVivant);
		printf("perso 2 : %i\n",joueur2.nbPersoVivant);

        /* on effectue pas le tour du joueur 2 si le joueur 2 à plus de personnages ou si joueur 2 a plus de personnage */
		if(!partie_finie(joueur1) && (!est_mort(&joueur2,1)|| !est_mort(&joueur2,2)) ){
            for(numero_personnage = 1 ; numero_personnage <= NB_PERSONNAGES; numero_personnage++){
                printf("[Tour numéro:%i][Tour du joueur %i][personnage :%i]{%c}\n\n",nb_tour,indice_joueur,numero_personnage,carac_perso(indice_joueur,numero_personnage));
				/* si le personnage est mort on ne le fais plus jouer */
				if(numero_personnage == 1 && !est_mort(&joueur2,numero_personnage)){
                    tour(map,&joueur2,&joueur1,2,numero_personnage); /* tour du personnage 1 du joueur 2 */
                }
                else if(!est_mort(&joueur2,numero_personnage)&& !partie_finie(joueur1)){
                    tour(map,&joueur2,&joueur1,2,numero_personnage); /* tour du personnage 2 du joueur 2 */
                }
				maj(map,&joueur1,&joueur2);
                affichage_map(map);
            }
        }

        if(!partie_finie(joueur1) || !partie_finie(joueur2)){
			printf("===================================================\n\tAFFICHAGE COORDONNEES | FIN DU TOUR\n===================================================\n\n");
			affichage_coord(joueur1);
			affichage_coord(joueur2);
        }
        indice_joueur--;
        nb_tour++;
   }
   printf("===================================================\n\tFIN DE LA PARTIE\n===================================================\n\n");

	if(partie_finie(joueur1))
		printf("Le joueur 1 a perdu \n");
	else if(partie_finie(joueur2))
		printf("Le joueur 2 a perdu\n");

	return 0;
}
