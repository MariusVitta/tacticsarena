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
int tour(char map[N][N],t_personnage * j1,t_personnage * j2,int nb_j ){
    /* variable qui compte le nombre de déplacement max possible par personnage*/
    int nb_deplacement = 3;
    int choix = 0;
    int point_action = j1.pa;
    while(choix != 3){
        do{
            printf(" ---- Quelle action souhaitez vous effectuer ? ---- \n[1]:Se déplacer ?[nombre de déplacement:%i]\n[2]:Utiliser un sort ?\n[3]:Passer son tour\nchoix:",nb_deplacement);
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
                        printf(" ---- Quel sort souhaitez vous effectuer ? ---- \n[1]:%s\n[2]:%s\n[3]:%s\n[4]:%s",j1.s1.nom,j1.s2.nom,j1.s3.nom,j1.s4.nom);
                        scanf("%i",&choix );
                    }
                    while(choix < 1 || choix > 4);
                    if(j1.nom == "Guerrier"){
                        switch(choix){
                            case 1:saut(j1,map);break;
                            case 2:/*perso.s2=soin;*/break;
                            case 3: petit_coup(map,j1,j2);break;
                            case 4:/*perso.s4=groscoup;*/break;
                        }
                    }
                    else if(j1.nom == "Archer"){
                        switch(choix){
                            case 1:diago(map,j1,j2);break;
                            case 2:/*perso.s2=ligne;*/break;
                            case 3:double_tape(map,j1,j2);break;
                            case 4:/*perso.s4=coupzone;*/break;
                        }
                    }
                }
                else{
                    printf("\n ---- Vous avez utilisé tous vos points d'actions ----\n\n");break;
                }
            case 3: printf("\n ---- Vous avez passé votre tour ---- \n\n");break;
        }
    }
    return 1;
}
