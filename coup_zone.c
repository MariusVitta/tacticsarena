#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

char map[N][N];

void coup_zone(char map[N][N],t_personnage j1,t_personnage j2){


    //affichage_map(map);
}

int main(){
    int i, j, classe1, classe2;
    int num_j = 1;
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

		if((classe2 != 1)&&(classe2 != 2))
			printf("Vous devez taper 1 ou 2\n");

	}while((classe2 != 1)&&(classe2 != 2));

	personnage1 = creer_perso(classe1,personnage1);
	personnage2 = creer_perso(classe2,personnage2);

	initialisation(map,&personnage1,&personnage2);


    coup_zone(map,personnage1,personnage2);
    return 0;
}
