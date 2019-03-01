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
	printf("point d'action [%i]\n", perso.s1.point_action);

	printf("- %s : ", perso.s2.nom);
	printf("portée [%i] / ", perso.s2.portee);
	printf("dégât [%i] / ", perso.s2.degat);
	printf("point d'action [%i]\n", perso.s2.point_action);

	printf("- %s : ", perso.s3.nom);
	printf("portée [%i] / ", perso.s3.portee);
	printf("dégât [%i] / ", perso.s3.degat);
	printf("point d'action [%i]\n", perso.s3.point_action);

	printf("- %s : ", perso.s4.nom);
	printf("portée [%i] / ", perso.s4.portee);
	printf("dégât [%i] / ", perso.s4.degat);
	printf("point d'action [%i]\n\n", perso.s4.point_action);

}

void affichage_map(char map[N][N]){
/*affiche le plan de jeu*/

	int i, j;

	printf("Plan de jeu \n\n");

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++)
			printf(" %c |", map[i][j]);
		printf("\n");			
	}
}

