#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


void affichage_sort(t_personnage * perso){
/*affiche les sorts selon le personnage choisi par l'utilisateur*/
	int i;
	printf("Personnage : %s\n\n", perso->nom);
	printf("Listes des sorts: \n");

	/*affichage des quatres sorts*/
	for (i = 0; i < MAX_NB_SORT ; i++)
	printf("- %s : portée [%i] / dégât [%i] / utilisation par tour [%i]\npoint d'action [%i]\n", perso->sorts[i]->nom, perso->sorts[i]->portee, perso->sorts[i]->degat, perso->sorts[i]->upt, perso->sorts[i]->point_action);
}

void sort_uti(t_personnage * perso){
	int i = 1;
	printf(" ---- Quel sort souhaitez vous effectuer ? ---- \n");

	for (i = 0; i < MAX_NB_SORT ; i++)
	printf("[%i] %s : portée [%i] / dégât [%i] / utilisation par tour [%i]\npoint d'action [%i]\n",i+1, perso->sorts[i]->nom, perso->sorts[i]->portee, perso->sorts[i]->degat, perso->sorts[i]->upt, perso->sorts[i]->point_action);
	printf("[%i] Ne pas utiliser de sort\nchoix:",i+1);
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

void affichage_coord(t_equipe * equipe){
	printf("equipe %i : \n", equipe->numEquipe);
	printf("- Coordonnées %s : x = %i et y = %i {Vie actuelle:%i}\n", equipe->perso1->nom, equipe->perso1->coord.x, equipe->perso1->coord.y,equipe->perso1->pv);
    printf("- Coordonnées %s : x = %i et y = %i {Vie actuelle:%i}\n", equipe->perso2->nom, equipe->perso2->coord.x, equipe->perso2->coord.y,equipe->perso2->pv);
	printf("\n");
}

/*
 * Fonction de mise à jour de l'affichage de la map
 *  paramètre equipe1,equipe2 : utilisé afin d'obtenir les coordonnées de tout les persos
 */
void maj(char map[N][N], t_equipe * equipe1, t_equipe * equipe2){
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(map[i][j] != 'o')
				map[i][j] = '.';
        }
	}

    /* equipe 1 */
    if(!est_mort(equipe1,1)){
	    map[equipe1->perso1->coord.y][equipe1->perso1->coord.x] = '1';
    }
    if(!est_mort(equipe1,2)){
        map[equipe1->perso2->coord.y][equipe1->perso2->coord.x] = '3';
    }
    /* equipe 2*/
    if(!est_mort(equipe2,1)){
	   map[equipe2->perso1->coord.y][equipe2->perso1->coord.x] = '2';
    }
    if(!est_mort(equipe2,2)){
        map[equipe2->perso2->coord.y][equipe2->perso2->coord.x] = '4';
    }
}


/*
 * Fonction qui retourne le caractère correspondant au personnage d'indice: numEro_personnage du equipe : indice_equipe
 */
char carac_perso(int numj,int nump){
	char c;
	if(numj == 1){
		if(nump == 1){
			c = '1';
		}
		else{
			c = '3';
		}
	}
	else{
		if(nump == 1){
			c = '2';
		}
		else{
			c = '4';
		}
	}

	return c;
}
