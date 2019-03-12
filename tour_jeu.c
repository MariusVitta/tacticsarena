#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"
#include <string.h>

/* fonction de gestion d'un tour de jeu
 * paramètre map : carte de jeu
 * paramètre j1: personnage actif pendant le tour jeu
 * paramètre j2: personnage passif durant le tour de jeu
 * la fonction demande au personne s'il souhaite effectuer un déplacement/utiliser un ou des sort(s)/passer son tour et ne rien faire
 * renvoie vrai lors que le tour de jeu du personnage est finie ou lorsqu'il passe son tour
 */
int tour(char map[N][N],t_personnage * j1,t_personnage * j2,int nb_j ){
    /* variable qui compte le nombre de déplacement max possible par personnage*/
    int nb_deplacement = 3;
    int choix = 0;
    int point_action = j1->pa;
    while(choix != 3){
        do{
            printf(" ---- Quelle action souhaitez vous effectuer ? ---- \n[1]:Se déplacer ?[nombre de déplacement:%i]\n[2]:Utiliser un sort ? [nombre de points d'actions:%i]\n[3]:Passer son tour\nchoix:",nb_deplacement,point_action);
            scanf("%i",&choix );
        }
        while(choix < 1 || choix > 3);

        switch(choix){
            case 1:
                if(nb_deplacement > 0 ){
                    nb_deplacement = deplacement(j1,j2,map,nb_deplacement,nb_j);break;
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points de déplacements ----\n\n");break;
                }
            case 2:
                if(point_action > 0){
                    printf("\n ---- fonctions sort ---- \n\n");
                    do{

                        sort_uti(*j1);
                        scanf("%i",&choix );
                    }
                    while(choix < 1 || choix > 4);
                    if(!(strcmp("Guerrier",j1->nom))){
                        switch(choix){
                            case 1:
                                if (j1->s1.point_action <= point_action  ) {
                                    saut(j1,j2,map,nb_j);point_action--;
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }break;
                            case 2:
                                if (j1->s1.point_action <= point_action ) {
                                    soin(j1);point_action--;
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }break;
                            case 3:
                                if ( j1->s1.point_action <= point_action  ) {
                                    petit_coup(map,j1,j2);point_action--;
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }break;
                            case 4:
                                if (j1->s1.point_action <= point_action  ) {
                                    grosCoup(map,j1,j2);point_action--;
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }break;
                            }
                            break;
                    }
                    else if(!(strcmp("Archer",j1->nom))){
                        switch(choix){
                            case 1:
                                if (j1->s1.point_action <= point_action  ) {
                                    diago(map,j1,j2);point_action--;
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }break;
                            case 2:
                                if (j1->s1.point_action <=  point_action) {
                                    ligne(map,j1,j2);point_action--;
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }break;
                            case 3:
                                if (j1->s1.point_action <=  point_action) {
                                    double_tape(map,j1,j2);point_action--;
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }break;
                            case 4:
                                if (j1->s1.point_action <= point_action) {
                                    /*perso.s4=coupzone;*/
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }break;
                        }
                        break;
                    }
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points d'actions ----\n\n");break;
                }
            case 3:printf("\n ---- Vous avez passé votre tour ---- \n\n");break;
        }
    }
    return 1;
}
