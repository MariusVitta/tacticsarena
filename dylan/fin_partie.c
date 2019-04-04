#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


/*
 * fonction pour tester si un personnage est mort ou pas
 * paramètre joueur: struct joueur
 * paramètre numero_personnage: personnage n du joueur dont on veut tester la mort
 * retourne 1 si le personnage n°numero_personnage du joueur est encore en vie
 */
int est_mort(t_joueur * joueur, int nump){
	int bool = 0;
	/* le personnage est deja mort */
	if(joueur->perso1->pv == -1 && nump == 1){
		return 1;
	}
	if(joueur->perso2->pv == -1 && nump == 2){
		return 1;
	}
	/*sinon s'il vient de mourir */
	switch(nump){
		case 1:
				if(joueur->perso1->pv <= 0 ){
					/* on check qu'il soit mort puis on lui mets un nombre de points de vie suffisament petit
					 * pour pas qu'il soit reconsideré comme mort de nouveau dans les autres fonctions
					 faisant appel est_mort();
					 */
					joueur->nbPersoVivant--;
					joueur->perso1->pv =-1;
                    printf(" Le %s du joueur %i est mort ",joueur->perso1->nom,joueur->numJoueur);
					bool = 1;
				}
				break;
		case 2:
				if(joueur->perso2->pv <= 0){
					joueur->nbPersoVivant--;
					joueur->perso2->pv =-1;
                    printf(" Le %s du joueur %i est mort ",joueur->perso2->nom,joueur->numJoueur);
					bool = 1;
				}
				break;
	}
	return bool;
}


/*
 * Fonction qui vérifie si le joueur joueur possède encore des personnages
 * retourne 1 si le joueur a plus de personnages vivants
 */
int partie_finie(t_joueur * joueur){
	return (joueur->nbPersoVivant);
}
