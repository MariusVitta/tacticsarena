#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


/*
 * fonction pour tester si un personnage est mort ou pas
 * paramètre equipe: struct equipe
 * paramètre numero_personnage: personnage n du equipe dont on veut tester la mort
 * retourne 1 si le personnage n°numEro_personnage du equipe est encore en vie
 */
int est_mort(t_equipe * equipe, int nump){
	int bool = 0;
	/* le personnage est deja mort */
	if(equipe->perso1->pv == -1 && nump == 1){
		return 1;
	}
	if(equipe->perso2->pv == -1 && nump == 2){
		return 1;
	}
	/*sinon s'il vient de mourir */
	switch(nump){
		case 1:
				if(equipe->perso1->pv <= 0 ){
					/* on check qu'il soit mort puis on lui mets un nombre de points de vie suffisament petit
					 * pour pas qu'il soit reconsideré comme mort de nouveau dans les autres fonctions
					 faisant appel est_mort();
					 */
					equipe->nbPersoVivant--;
					equipe->perso1->pv =-1;
                    printf(" Le %s du equipe %i est mort ",equipe->perso1->nom,equipe->numEquipe);
					bool = 1;
				}
				break;
		case 2:
				if(equipe->perso2->pv <= 0){
					equipe->nbPersoVivant--;
					equipe->perso2->pv =-1;
                    printf(" Le %s du equipe %i est mort ",equipe->perso2->nom,equipe->numEquipe);
					bool = 1;
				}
				break;
	}
	return bool;
}


/*
 * Fonction qui vérifie si le equipe equipe possède encore des personnages
 * retourne 1 si le equipe a plus de personnages vivants
 */
int partie_finie(t_equipe * equipe){
	return (equipe->nbPersoVivant);
}
