#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

void affichage_sort(t_personnage perso){
/*affiche les sorts selon le personnage choisi par l'utilisateur*/

	printf("Personnage : %s\n\n", perso.nom);
	printf("Listes des sorts: \n");

	/*affichage des quatres sorts*/

	printf("- %s : ", perso.s1.nom);
	printf("portée [%i] / ", perso.s1.portee);
	printf("dégât [%i] / ", perso.s1.degat);
	printf("utilisation par tour [%i]\n", perso.s1.upt);
	printf("point d'action [%i]\n", perso.s1.point_action);


	printf("- %s : ", perso.s2.nom);
	printf("portée [%i] / ", perso.s2.portee);
	printf("dégât [%i] / ", perso.s2.degat);
	printf("utilisation par tour [%i]\n", perso.s2.upt);
	printf("point d'action [%i]\n", perso.s2.point_action);


	printf("- %s : ", perso.s3.nom);
	printf("portée [%i] / ", perso.s3.portee);
	printf("dégât [%i] / ", perso.s3.degat);
	printf("utilisation par tour [%i]\n", perso.s3.upt);
	printf("point d'action [%i]\n", perso.s3.point_action);


	printf("- %s : ", perso.s4.nom);
	printf("portée [%i] / ", perso.s4.portee);
	printf("dégât [%i] / ", perso.s4.degat);
	printf("utilisation par tour [%i]\n", perso.s4.upt);
	printf("point d'action [%i]\n\n", perso.s4.point_action);


}

void sort_uti(t_personnage perso){
	int i = 1;
	printf(" ---- Quel sort souhaitez vous effectuer ? ---- \n");

	printf("[%i] %s : ", i++, perso.s1.nom);
	printf("portée [%i] / ", perso.s1.portee);
	printf("dégât [%i] / ", perso.s1.degat);
	printf("utilisation par tour [%i]\n", perso.s1.upt);
	printf("point d'action [%i]\n", perso.s1.point_action);


	printf("[%i] %s : ", i++, perso.s2.nom);
	printf("portée [%i] / ", perso.s2.portee);
	printf("dégât [%i] / ", perso.s2.degat);
	printf("utilisation par tour [%i]\n", perso.s2.upt);
	printf("point d'action [%i]\n", perso.s2.point_action);


	printf("[%i] %s : ", i++, perso.s3.nom);
	printf("portée [%i] / ", perso.s3.portee);
	printf("dégât [%i] / ", perso.s3.degat);
	printf("utilisation par tour [%i]\n", perso.s3.upt);
	printf("point d'action [%i]\n", perso.s3.point_action);

	printf("[%i] %s : ", i++, perso.s4.nom);
	printf("portée [%i] / ", perso.s4.portee);
	printf("dégât [%i] / ", perso.s4.degat);
	printf("utilisation par tour [%i]\n", perso.s4.upt);
	printf("point d'action [%i]\n", perso.s4.point_action);

	printf("[%i] Ne pas utiliser de sort\nchoix:",i++);
}

void affichage_map(char map[N][N]){
/*affiche le plan de jeu*/

	int i, j;

	printf(" ---- [Plan de jeu] ---- \n\n");

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++)
			printf(" %c |", map[i][j]);
		printf("\n");
	}
	printf("\n");
}

void affichage_coord(t_joueur joueur){
	printf("Joueur %i : \n", joueur.numJoueur);
	printf("- Coordonnées %s : x = %i et y = %i {Vie actuelle:%i}\n", joueur.perso1->nom, joueur.perso1->coord.x, joueur.perso1->coord.y,joueur.perso1->pv);
    printf("- Coordonnées %s : x = %i et y = %i {Vie actuelle:%i}\n", joueur.perso2->nom, joueur.perso2->coord.x, joueur.perso2->coord.y,joueur.perso2->pv);
	printf("\n");
}
/*
 * Fonction qui retourne le caractère correspondant au personnage d'indice: numero_personnage du joueur : indice_joueur
 */
char carac_perso(int indice_joueur,int numero_personnage){
	char c;
	if(indice_joueur == 1){
		if(numero_personnage == 1){
			c = '1';
		}
		else{
			c = '3';
		}
	}
	else{
		if(numero_personnage == 1){
			c = '2';
		}
		else{
			c = '4';
		}
	}

	return c;
}
