#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


char map[N][N];

int main(){

	int i, j, classe1, classe2,nb_tour = 1,mort1 = 0,mort2 = 0;
    int num_j = 1,num_p = 1;
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
    joueur1.perso1 = malloc(sizeof(t_personnage));
    joueur1.perso2 = malloc(sizeof(t_personnage));
    creer_perso(classe1,joueur1.perso1);
	creer_perso(classe2,joueur1.perso2);
    joueur1.numJoueur = 1;
    joueur1.nbPVivant = 2;

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

    joueur2.perso1 = malloc(sizeof(t_personnage));
    joueur2.perso2 = malloc(sizeof(t_personnage));
	creer_perso(classe1,joueur2.perso1 );
	creer_perso(classe2,joueur2.perso2);
    joueur2.numJoueur = 2;
    joueur2.nbPVivant = 2;


	initialisation(map,&joueur1,&joueur2);
    printf("===================================================\n\tDEMARRAGE DE LA  PARTIE\n===================================================\n");
    affichage_map(map);

    /* boucle principale du jeu */
    while(!est_mort(joueur1.perso1) && !est_mort(joueur2.perso1)){
        for(num_p = 1 ; num_p <= 2; num_p++){
            printf("[Tour numéro:%i][Tour du joueur %i][personnage :%i]\n\n",nb_tour,num_j,num_p);
            if(num_p == 1){
                tour(map,joueur1,joueur2,1,num_p); /* tour du personnage 1 du joueur 1 */
            }
            else{
                tour(map,joueur1,joueur2,1,num_p); /* tour du personnage 1 du joueur 1 */
                printf("personne 2 joueur 1\n");
            }
            affichage_map(map);
        }
        num_j++;

        //verifie si les personnages sont vivant au ( refaire a chaque fin de tour )
        mort1 = est_mort(joueur1.perso1);
		mort2= est_mort(joueur2.perso1);
        /* si le personnage 1 est mort on effectue pas le tour du joueur */
        if(!mort1 && !mort2){
            for(num_p = 1 ; num_p <= 2; num_p++){
                printf("[Tour numéro:%i][Tour du joueur %i][personnage :%i]\n\n",nb_tour,num_j,num_p);
                if(num_p == 1){
                    tour(map,joueur2,joueur1,2,num_p); /* tour du personnage 1 du joueur 1 */
                }
                else{
                    tour(map,joueur2,joueur1,2,num_p); /* tour du personnage 2 du joueur 2 */
                }
                affichage_map(map);
            }
        }
				//verifie si les personnages sont vivant
                mort1 = est_mort(joueur1.perso1);
        		mort2= est_mort(joueur2.perso1);
        if( !mort1 && !mort2 ){
		          printf("===================================================\n\tAFFICHAGE COORDONNEES\n===================================================\n");
		          affichage_coord(joueur1);
		          affichage_coord(joueur2);
        }
        num_j--;
        nb_tour++;
   }
   printf("===================================================\n\tFIN DE LA PARTIE\n===================================================\n");

	if(est_mort(joueur1.perso1))
		printf("Le personnage '%s' est mort\n", joueur1.perso1->nom);
	else if(est_mort(joueur2.perso1))
		printf("Le personnage '%s' est mort\n", joueur2.perso1->nom);

	return 0;
}
