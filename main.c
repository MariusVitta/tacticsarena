#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


char map[N][N];

int main(){

	int i, j, classe;

	t_personnage personnage1,personnage2;
	printf("choisir classe\n");
	scanf("%d",&classe);

	personnage1 = creer_perso(classe,personnage1);
	personnage2 = creer_perso(classe,personnage2);

	initialisation(map,&personnage1,&personnage2);

	affichage_sort(personnage1);
	affichage_map(map);


	printf("x perso 1:%i - y perso 1:%i\n",personnage1.coord.x,personnage1.coord.y);
	printf("x perso 2:%i - y perso 2:%i\n",personnage2.coord.x,personnage2.coord.y);

	if(est_mort(personnage1))
		printf("Le personnage '%s' est mort\n", personnage1.nom);
	else
		printf("Le personnage '%s' est vivant\n", personnage1.nom);

	return 0;
}
