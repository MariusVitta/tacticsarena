#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include "fonc.h"

char map[N][N];

int main(){

	int i, j, classe;

	t_personnage personnage;
	printf("choisir classe\n");
	scanf("%d",&classe);

	personnage=creer_perso(classe,personnage);
	initialisation(map,classe);
	affichage_sort(personnage);
	affichage_map(map);

	if(est_mort(personnage))
		printf("Le personnage '%s' est mort\n", personnage.nom);
	else
		printf("Le personnage '%s' est vivant\n", personnage.nom);

	return 0;
}
