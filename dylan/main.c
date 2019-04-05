#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"
#include "define.h"

char map[N][N];

int main(){

	int i,val,j,test=0,nb_tour = 1,mort1 = 0,mort2 = 0;
	int classe[NB_PERSONNAGES+1];
  int indice_joueur = 1,nump = 1;

	t_joueur * joueur1, * joueur2;

	/*Creation de toutes les classes et tous les sorts */
	t_personnage * persos[CLASSES+1];

	t_sort * sorts[SORTS+1];
	for(int i = 1; i <= SORTS;i++)
		sorts[i] = malloc(sizeof(t_sort));

	creation_sorts(sorts);

	for(int i = 1; i <= CLASSES;i++)
		persos[i] = malloc(sizeof(t_personnage));

	creation_classes(persos,sorts);

	joueur1 = malloc(sizeof(t_joueur));
	joueur2 = malloc(sizeof(t_joueur));

	t_joueur * tab[NB_EQUIPES+1];
	tab[1] = joueur1;
	tab[2] = joueur2;

	for(j = 1 ; j <= NB_EQUIPES; j++){

		do{ /* choix personnage du joueur 1 */

			printf("Le Joueur %d choisi ses classes : \n",j);

			for(i = 1; i <= CLASSES; i++){

				printf("[%d] : %s\n",i,persos[i]->nom);

			}

			for (i = 1; i <= NB_PERSONNAGES; i++){
		  printf("Choix personnage %d: ",i);
			scanf("%d",&val);
			classe[i] = val;
			}

			for(i = 1;i <= NB_PERSONNAGES; i++){
				if((classe[i] < 1) || (classe[i] > CLASSES))
					test = 1;
				else
					test = 0;
			}

			if(test)
				printf("Vous devez taper un nombre compris entre 1 ou %i\n",CLASSES);

		}
		while(test);

		/* creation du personnages du joueurs 1 */
		tab[j]->perso1 = copie_perso(persos[classe[1]]);
		tab[j]->perso2 = copie_perso(persos[classe[2]]);
		tab[j]->numJoueur = j;
		tab[j]->nbPersoVivant = NB_PERSONNAGES;

	}


	initialisation(map,joueur1,joueur2);
  printf("===================================================\n\tDEMARRAGE DE LA  PARTIE\n===================================================\n");
	maj(map,joueur1,joueur2);
	affichage_map(map);

  for(nump = 1, indice_joueur = 1;(partie_finie(joueur1) && partie_finie(joueur2));){


			/* si le personnage est mort on ne le fais plus jouer */
			if(indice_joueur == 1){
				printf("[Tour numéro:%i][Tour du joueur %i][personnage :%i]{Caractère : %c}\n\n",nb_tour,indice_joueur,nump,carac_perso(indice_joueur,nump));

				if(nump == 1 && !est_mort(tab[indice_joueur],nump))
					tour(map,joueur1,joueur2,nump);

				else if(nump == 2 && !est_mort(tab[indice_joueur],nump))
					tour(map,joueur1,joueur2,nump);

				indice_joueur++;

				maj(map,joueur1,joueur2);
				affichage_map(map);
			}


			if(indice_joueur == 2){
				printf("[Tour numéro:%i][Tour du joueur %i][personnage :%i]{Caractère : %c}\n\n",nb_tour,indice_joueur,nump,carac_perso(indice_joueur,nump));
				if(nump == 1 && !est_mort(tab[indice_joueur],nump)){
					tour(map,joueur2,joueur1,nump);
					indice_joueur--;
				}
				else if(nump == 2 && !est_mort(tab[indice_joueur],nump))
					tour(map,joueur2,joueur1,nump);



				maj(map,joueur1,joueur2);
				affichage_map(map);
			}



			if((partie_finie(joueur1) || partie_finie(joueur2))&& indice_joueur == 2 && nump == 2){
				printf("===================================================\n\tAFFICHAGE COORDONNEES | FIN DU TOUR\n===================================================\n\n");
				affichage_coord(joueur1);
				affichage_coord(joueur2);
				indice_joueur--;
				nb_tour++;
			}
			if (nump == 2)
				nump --;

			else
				nump ++;
  }

  printf("===================================================\n\tFIN DE LA PARTIE\n===================================================\n\n");

	if(partie_finie(joueur1))
		printf("Le joueur 1 a perdu \n");
	else if(partie_finie(joueur2))
		printf("Le joueur 2 a perdu\n");

	for(i = 1; i < SORTS; i++){
		suppr_sort(&(sorts[i]));
	}

	for(i = 1; i <= CLASSES; i++){
		suppr_perso(&(persos[i]));
	}

	for(i=1; i <= NB_EQUIPES; i++){
		suppr_perso(&(tab[i]->perso1));
		suppr_perso(&(tab[i]->perso2));
		free(tab[i]);
		tab[i] = NULL;
	}


	return 0;
}
