#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


char map[N][N];

int main(){

	int i, j, classe1, classe2;

	t_personnage personnage1,personnage2;
	
	do{
		printf("Joueur 1: choisir une classe\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\n");
		scanf("%d",&classe1);
		
		if((classe1 != 1)&&(classe1 != 2))
			printf("Vous devez taper 1 ou 2\n");
		
	}while((classe1 != 1)&&(classe1 != 2));

	do{
		printf("Joueur 2: choisir une classe\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\n");
		scanf("%d",&classe2);
		
		if((classe2 != 1)||(classe2 != 2))
			printf("Vous devez taper 1 ou 2\n");
		
	}while((classe2 != 1)&&(classe2 != 2));

	personnage1 = creer_perso(classe1,personnage1);
	personnage2 = creer_perso(classe2,personnage2);

	initialisation(map,&personnage1,&personnage2);

	affichage_sort(personnage1);
	affichage_map(map);

	printf("vos coords : {%0.0f;%0.0f}\n",personnage1.coord.x,personnage1.coord.y);
	deplacement(&personnage1,personnage2);
	/*printf("x perso 1:%i - y perso 1:%i\n",personnage1.coord.x,personnage1.coord.y);
	printf("x perso 2:%i - y perso 2:%i\n",personnage2.coord.x,personnage2.coord.y);*/
	printf("après deplacement\n");
	affichage_map(map);

	maj(map,personnage1,personnage2);
	affichage_map(map);


	printf("x perso 1:%0.0f - y perso 1:%0.0f\n",personnage1.coord.x,personnage1.coord.y);
	printf("x perso 2:%0.0f - y perso 2:%0.0f\n",personnage2.coord.x,personnage2.coord.y);

	/*if(est_mort(personnage1))
		printf("Le personnage '%s' est mort\n", personnage1.nom);
	else
		printf("Le personnage '%s' est vivant\n", personnage1.nom);*/
	

	return 0;
}
