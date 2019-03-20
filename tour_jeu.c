#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"
#include <string.h>

/* fonction de gestion d'un tour de jeu
 * paramètre map : carte de jeu
 * paramètre joueur1: personnage actif pendant le tour jeu
 * paramètre joueur2: personnage passif durant le tour de jeu
 * paramètre numero_joueur: numéro du joueur qui joue actuellement
 * paramètre numero_perso: numéro du %numero_joueur actuellement
 * la fonction demande au personne s'il souhaite effectuer un déplacement/utiliser un ou des sort(s)/passer son tour et ne rien faire
 * renvoie vrai lors que le tour de jeu du personnage est finie ou lorsqu'il passe son tour
 */
int tour(char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_joueur,int numero_perso ){
	t_personnage * temp;
    if(numero_perso == 1 ){
        temp = joueur1.perso1;
    }
    else{
        temp = joueur1.perso2;
    }
            
    /* variable qui compte le nombre de déplacement max possible par personnage*/
    int pm=temp->pm;
    int choix = 0;
    temp->s1.upt=temp->s1.uptm;
    temp->s2.upt=temp->s2.uptm;
    temp->s3.upt=temp->s3.uptm;
    temp->s4.upt=temp->s4.uptm;
    /* variable qui compte le nombre de points d'actions max du personnage 1 */
    int point_action = temp->pa;
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
                    pm = deplacement(joueur1,joueur2,map,pm,numero_joueur,numero_perso);
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points de déplacements ----\n\n");
                }
                break;
            case 2:
                if(point_action > 0){
                    do{
                        /*affichage de la liste des sorts utilisable par le personnage actuel*/
                        sort_uti(*(temp));
                        scanf("%i",&choix );
                    }
                    while(choix < 1 || choix > 4);
                    if(!(strcmp("Guerrier",temp->nom))){
                        switch(choix){
                            case 1:

                                if (temp->s1.point_action <= point_action && temp->s1.upt > 0 ) {
                                    saut(joueur1,joueur2,map,numero_joueur,numero_perso);point_action -= temp->s1.point_action ; temp->s1.upt-=1;
                                }
                                else if(temp->s1.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 2:
                                if (temp->s2.point_action <= point_action && temp->s2.upt > 0 ) {
                                    soin(temp);point_action -= temp->s2.point_action ;temp->s2.upt-=1;
                                }
                                else if(temp->s2.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 3:
                                if (temp->s3.point_action <= point_action && temp->s3.upt > 0 ) {
                                    petit_coup(map,temp,joueur2);point_action -= temp->s3.point_action ;temp->s3.upt-=1;
                                    choix=0;

                                }
                                else if(temp->s3.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 4:
                                if (temp->s4.point_action <= point_action && temp->s4.upt > 0 ) {
                                    grosCoup(map,temp,joueur2);point_action -= temp->s4.point_action ;temp->s4.upt-=1;

                                }
                                else if(temp->s4.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            }

                    }
                    else if(!(strcmp("Archer",temp->nom))){
                        switch(choix){
                            case 1:
                                if (temp->s1.point_action <= point_action && temp->s1.upt > 0 ) {
                                    diago(map,temp,joueur2);
                                    point_action -= temp->s1.point_action ;temp->s1.upt-=1;

                                }
                                else if(temp->s1.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 2:
                                if (temp->s2.point_action <=  point_action && temp->s2.upt > 0 ) {
                                    ligne(map,temp,joueur2);point_action -= temp->s2.point_action ;temp->s2.upt-=1;

                                }
                                else if(temp->s2.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 3:
                                if (temp->s3.point_action <=  point_action && temp->s3.upt > 0 ) {
                                    double_tape(map,temp,joueur2);point_action -= temp->s3.point_action ;temp->s3.upt-=1;
                                    choix=0;
                                }
                                else if(temp->s3.upt == 0){
                                    printf(" ---- Vous ne pouvez plus utiliser ce sort ce tour ci ----\n\n");
                                }
                                else{
                                    printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
                                }
                                break;
                            case 4:
                                if (temp->s4.point_action <= point_action && temp->s4.upt > 0 ) {

                                    coup_zone(map,temp,joueur2);point_action -= temp->s4.point_action ;temp->s4.upt-=1;
                                }
                                else if(temp->s4.upt == 0){
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
