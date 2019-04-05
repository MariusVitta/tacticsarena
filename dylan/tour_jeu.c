#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"
#include <string.h>

/* fonction de gestion d'un tour de jeu
 * paramètre map : carte de jeu
 * paramètre equipe1: personnage actif pendant le tour jeu
 * paramètre equipe2: personnage passif durant le tour de jeu
 * paramètre numj: numéro du equipe qui joue actuellement
 * paramètre nump: numéro du %numj actuellement
 * la fonction demande au personne s'il souhaite effectuer un déplacement/utiliser un ou des sort(s)/passer son tour et ne rien faire
 * renvoie vrai lors que le tour de jeu du personnage est finie ou lorsqu'il passe son tour
 */
void tour(char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int nump ){

		t_personnage * temp;

		if(nump == 1 ){
        temp = equipe1->perso1;
    }
    else{
        temp = equipe1->perso2;
    }

    /* variable qui compte le nombre de déplacement max possible par personnage*/
    int pm=temp->pm;
    int choix_action = 0,choix_sort =0;
    temp->sorts[0]->upt=temp->sorts[0]->uptm;
    temp->sorts[1]->upt=temp->sorts[1]->uptm;
    temp->sorts[2]->upt=temp->sorts[2]->uptm;
    temp->sorts[3]->upt=temp->sorts[3]->uptm;

    /* variable qui compte le nombre de points d'actions max du personnage 1 */
    int point_action = temp->pa;

    /* tant que le equipe ne passe pas son tour OU s'il lui reste des points de déplacements et d'actions */
    while(choix_action != 3 /*|| (pm > 0 && point_action > 0)*/){
        do{
            printf(" ---- Quelle action souhaitez vous effectuer ? ---- \n[1]:Se déplacer ?[nombre de déplacement:%i]\n[2]:Utiliser un sort ? [nombre de points d'actions:%i]\n[3]:Passer son tour\nchoix:",pm,point_action);
            scanf("%i",&choix_action );
        }
        while(choix_action < 1 || choix_action > 3);

        switch(choix_action){
            case 1:

                if(pm > 0 ){
                    pm = deplacement(equipe1,equipe2,map,pm,nump);
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points de déplacements ----\n\n");
                }
                break;

            case 2:

                if(point_action > 0){
                    do{
                        /*affichage de la liste des sorts utilisable par le personnage actuel*/
                        sort_uti(temp);
                        scanf("%i",&choix_sort );
                    }
                    while(choix_sort < 1 || choix_sort > MAX_NB_SORT+1);

                    switch(choix_sort){

											  case 1:

                            if (temp->sorts[0]->point_action <= point_action && temp->sorts[0]->upt > 0 ) {
																temp->sorts[0]->sort(map,temp,equipe2,equipe1,nump,temp->sorts[0]->degat,temp->sorts[0]->portee,equipe1->numEquipe);
																point_action -= temp->sorts[0]->point_action ;
																temp->sorts[0]->upt-=1;
                            }
                            else if(temp->sorts[0]->upt == 0){
                                printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                            }
                            else{
                                printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                            }
                            break;

                        case 2:

                          	if (temp->sorts[1]->point_action <= point_action && temp->sorts[1]->upt > 0 ) {
                                temp->sorts[1]->sort(map,temp,equipe2,equipe1,nump,temp->sorts[1]->degat,temp->sorts[1]->portee,equipe1->numEquipe);
																point_action -= temp->sorts[1]->point_action ;
																temp->sorts[1]->upt-=1;
                            }
                            else if(temp->sorts[1]->upt == 0){
                                printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                            }
                            else{
                                printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                            }
                            break;

                        case 3:

                            if (temp->sorts[2]->point_action <= point_action && temp->sorts[2]->upt > 0 ) {
																temp->sorts[2]->sort(map,temp,equipe2,equipe1,nump,temp->sorts[2]->degat,temp->sorts[2]->portee,equipe1->numEquipe);
																point_action -= temp->sorts[2]->point_action ;
																temp->sorts[2]->upt-=1;

                            }
                            else if(temp->sorts[2]->upt == 0){
                                printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                            }
                            else{
                                printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                            }
                            break;

                        case 4:

														if (temp->sorts[3]->point_action <= point_action && temp->sorts[3]->upt > 0 ) {
														temp->sorts[3]->sort(map,temp,equipe2,equipe1,nump,temp->sorts[3]->degat,temp->sorts[3]->portee,equipe1->numEquipe);
														point_action -= temp->sorts[3]->point_action ;
														temp->sorts[3]->upt-=1;

                            }
                            else if(temp->sorts[3]->upt == 0){
                                printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                            }
                            else{
                                printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                            }
                            break;

                        case 5: printf(" ---- Vous n'avez utilisé aucun sort,vous ne perdez aucun point d'action ----\n\n");
														break;
                    }

                }

								else{
										printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
									break;

								}
								break;

						case 3:
								printf("\n ---- Vous avez passé votre tour ---- \n\n");
									break;
        }
        maj(map,equipe1,equipe2);
    }
}
