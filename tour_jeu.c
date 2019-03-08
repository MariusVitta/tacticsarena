#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


/* fonction de gestion d'un tour de jeu
 * paramètre map : carte de jeu
 * paramètre j1: personnage actif pendant le tour jeu
 * paramètre j2: personnage passif durant le tour de jeu
 * la fonction demande au personne s'il souhaite effectuer un déplacement/utiliser un ou des sort(s)/passer son tour et ne rien faire
 * renvoie vrai lors que le tour de jeu du personnage est finie ou lorsqu'il passe son tour
 */
int tour(char map[N][N],t_personnage j1,t_personnage j2 ){
    /* variable qui compte le nombre de déplacement max possible par personnage*/
    int nb_deplacement = 3;
    int choix = 0;
    int point_action = j1.pa;
    while(choix != 3){
        do{
            printf(" ---- Quel action souhaitez vous effectuer ? ---- \n[1]:Se déplacer ?\n[2]:Utiliser un sort ?\n[3]:Passer son tour\nchoix:");
            scanf("%i",&choix );
        }
        while(choix < 1 || choix > 3);

        switch(choix){
            case 1:
                if(nb_deplacement > 0 ){
                    nb_deplacement = deplacement(&j1,j2,map,nb_deplacement);break;
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points de déplacements ----\n\n");break;
                }
            case 2:
                if(point_action > 0){
                    printf("\n ---- fonction sort ---- \n\n");break;
                    /*point_action = */
                }
            case 3: printf("\n ---- vous avez passé votre tour ---- \n\n");break;
        }
    }
    return 1;
}
