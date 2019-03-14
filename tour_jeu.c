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
    j1->pm=3;
    int choix = 0;
    /* variable qui compte le nombre de points d'actions max du personnage 1 */
    int point_action = j1->pa;
    /* tant que le joueur ne passe pas son tour OU s'il lui reste des points de déplacements et d'actions */
    while(choix != 3 /*|| (j1->pm > 0 && point_action > 0)*/){
        do{
            printf(" ---- Quelle action souhaitez vous effectuer ? ---- \n[1]:Se déplacer ?[nombre de déplacement:%i]\n[2]:Utiliser un sort ? [nombre de points d'actions:%i]\n[3]:Passer son tour\nchoix:",j1->pm,point_action);
            scanf("%i",&choix );
        }
        while(choix < 1 || choix > 3);

        switch(choix){
            case 1:
                if(j1->pm > 0 ){
                    j1->pm = deplacement(j1,j2,map,j1->pm,nb_j);
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points de déplacements ----\n\n");
                }
                break;
            case 2:
                if(point_action > 0){
                    do{
                        /*affichage de la liste des sorts utilisable par le personnage actuel*/
                        sort_uti(*j1);
                        scanf("%i",&choix );
                    }
                    while(choix < 1 || choix > 4);
                    if(!(strcmp("Guerrier",j1->nom))){
                        switch(choix){
                            case 1:
                                if (j1->s1.point_action <= point_action && j1->s1.upt > 0 ) {
                                    saut(j1,j2,map,nb_j);point_action -= j1->s1.point_action ; j1->s1.upt-=1;
                                }
                                else if(j1->s1.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 2:
                                if (j1->s2.point_action <= point_action && j1->s2.upt > 0 ) {
                                    soin(j1);point_action -= j1->s2.point_action ;j1->s2.upt-=1;
                                }
                                else if(j1->s2.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 3:
                                if (j1->s3.point_action <= point_action && j1->s3.upt > 0 ) {
                                    petit_coup(map,j1,j2);point_action -= j1->s3.point_action ;j1->s3.upt-=1;
                                    choix=0;

                                }
                                else if(j1->s3.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 4:
                                if (j1->s4.point_action <= point_action && j1->s4.upt > 0 ) {
                                    grosCoup(map,j1,j2);point_action -= j1->s4.point_action ;j1->s4.upt-=1;

                                }
                                else if(j1->s4.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            }

                    }
                    else if(!(strcmp("Archer",j1->nom))){
                        switch(choix){
                            case 1:
                                if (j1->s1.point_action <= point_action && j1->s1.upt > 0 ) {
                                    diago(map,j1,j2);
                                    point_action -= j1->s1.point_action ;j1->s1.upt-=1;

                                }
                                else if(j1->s1.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 2:
                                if (j1->s2.point_action <=  point_action && j1->s2.upt > 0 ) {
                                    ligne(map,j1,j2);point_action -= j1->s2.point_action ;j1->s2.upt-=1;

                                }
                                else if(j1->s2.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 3:
                                if (j1->s3.point_action <=  point_action && j1->s3.upt > 0 ) {
                                    double_tape(map,j1,j2);point_action -= j1->s3.point_action ;j1->s3.upt-=1;
                                    choix=0;
                                }
                                else if(j1->s3.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 4:
                                if (j1->s4.point_action <= point_action && j1->s4.upt > 0 ) {

                                    coup_zone(map,j1,j2);point_action -= j1->s4.point_action ;j1->s4.upt-=1;
                                }
                                else if(j1->s4.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                        }

                    }
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points d'actions ----\n\n");break;
                }
                break;

            case 3:
                printf("\n ---- Vous avez passé votre tour ---- \n\n");break;

        }
    }
    return 1;
}
