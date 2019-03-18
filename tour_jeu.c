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
int tour(char map[N][N],t_joueur joueur1,t_joueur joueur2,int nb_j,int numero_perso ){
    /* variable qui compte le nombre de déplacement max possible par personnage*/
    int pm=joueur1.perso1->pm;
    int choix = 0;
    joueur1.perso1->s1.upt=joueur1.perso1->s1.uptm;
    joueur1.perso1->s2.upt=joueur1.perso1->s2.uptm;
    joueur1.perso1->s3.upt=joueur1.perso1->s3.uptm;
    joueur1.perso1->s4.upt=joueur1.perso1->s4.uptm;
    /* variable qui compte le nombre de points d'actions max du personnage 1 */
    int point_action = joueur1.perso1->pa;
    /* tant que le joueur ne passe pas son tour OU s'il lui reste des points de déplacements et d'actions */
    while(choix != 3 /*|| (pm > 0 && point_action > 0)*/){
        do{
            printf(" ---- Quelle action souhaitez vous effectuer ? ---- \n[1]:Se déplacer ?[nombre de déplacement:%i]\n[2]:Utiliser un sort ? [nombre de points d'actions:%i]\n[3]:Passer son tour\nchoix:",pm,point_action);
            scanf("%i",&choix );
        }
        while(choix < 1 || choix > 3);

        switch(choix){
            case 1:
                if(pm > 0 ){
                    pm = deplacement(joueur1,joueur2,map,pm,nb_j,numero_perso);
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points de déplacements ----\n\n");
                }
                break;
            case 2:
                if(point_action > 0){
                    do{
                        /*affichage de la liste des sorts utilisable par le personnage actuel*/
                        sort_uti(*(joueur1.perso1));
                        scanf("%i",&choix );
                    }
                    while(choix < 1 || choix > 4);
                    if(!(strcmp("Guerrier",joueur1.perso1->nom))){
                        switch(choix){
                            case 1:

                                if (joueur1.perso1->s1.point_action <= point_action && joueur1.perso1->s1.upt > 0 ) {
                                    saut(joueur1,joueur2,map,nb_j,numero_perso);point_action -= joueur1.perso1->s1.point_action ; joueur1.perso1->s1.upt-=1;
                                }
                                else if(joueur1.perso1->s1.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 2:
                                if (joueur1.perso1->s2.point_action <= point_action && joueur1.perso1->s2.upt > 0 ) {
                                    soin(joueur1.perso1);point_action -= joueur1.perso1->s2.point_action ;joueur1.perso1->s2.upt-=1;
                                }
                                else if(joueur1.perso1->s2.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 3:
                                if (joueur1.perso1->s3.point_action <= point_action && joueur1.perso1->s3.upt > 0 ) {
                                    petit_coup(map,joueur1.perso1,joueur2.perso1);point_action -= joueur1.perso1->s3.point_action ;joueur1.perso1->s3.upt-=1;
                                    choix=0;

                                }
                                else if(joueur1.perso1->s3.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 4:
                                if (joueur1.perso1->s4.point_action <= point_action && joueur1.perso1->s4.upt > 0 ) {
                                    grosCoup(map,joueur1.perso1,joueur2.perso1);point_action -= joueur1.perso1->s4.point_action ;joueur1.perso1->s4.upt-=1;

                                }
                                else if(joueur1.perso1->s4.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            }

                    }
                    else if(!(strcmp("Archer",joueur1.perso1->nom))){
                        switch(choix){
                            case 1:
                                if (joueur1.perso1->s1.point_action <= point_action && joueur1.perso1->s1.upt > 0 ) {
                                    diago(map,joueur1.perso1,joueur2.perso1);
                                    point_action -= joueur1.perso1->s1.point_action ;joueur1.perso1->s1.upt-=1;

                                }
                                else if(joueur1.perso1->s1.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 2:
                                if (joueur1.perso1->s2.point_action <=  point_action && joueur1.perso1->s2.upt > 0 ) {
                                    ligne(map,joueur1.perso1,joueur2.perso1);point_action -= joueur1.perso1->s2.point_action ;joueur1.perso1->s2.upt-=1;

                                }
                                else if(joueur1.perso1->s2.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 3:
                                if (joueur1.perso1->s3.point_action <=  point_action && joueur1.perso1->s3.upt > 0 ) {
                                    double_tape(map,joueur1.perso1,joueur2.perso1);point_action -= joueur1.perso1->s3.point_action ;joueur1.perso1->s3.upt-=1;
                                    choix=0;
                                }
                                else if(joueur1.perso1->s3.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 4:
                                if (joueur1.perso1->s4.point_action <= point_action && joueur1.perso1->s4.upt > 0 ) {

                                    coup_zone(map,joueur1.perso1,joueur2.perso1);point_action -= joueur1.perso1->s4.point_action ;joueur1.perso1->s4.upt-=1;
                                }
                                else if(joueur1.perso1->s4.upt == 0){
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
