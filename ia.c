#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonc.h"

#define N 11
#define NB_PERSONNAGES 2
#define NB_CLASSE 4
char map[N][N];

int tour_ordi_opti(int indice_sort,char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage);
int tour_joueur_opti(int indice_sort,char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage);
int coup_ordi_opti(char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage);
int fonction_evalution(int indice_sort,char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage);

int fonction_evalution(int indice_sort,char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage){
    int portee = 0,i;
    t_personnage * temp;
    if(numero_personnage == 1)
        temp = joueur1.perso1;
    else
        temp = joueur1.perso2;
    int distance,carre;



    switch (indice_sort){
        case 1: portee = temp.s1.portee;break;
        case 2: portee = temp.s2.portee;break;
        case 3: portee = temp.s3.portee;break;
        case 4: portee = temp.s4.portee;break;
    }
    for(i = 1; i <= NB_PERSONNAGES;i++){
        if(i == 1){
            carre = pow((double)(temp->x - joueur2.perso1->x),2) + pow((double)(temp->y - joueur2.perso1->y),2);
            distance = sqrt((double)carre);
            if(distance == portee){
                return 1;
            }
        }
        else{
            carre = pow((double)(temp->x - joueur2.perso2->x),2) + pow((double)(temp->y - joueur2.perso2->y),2);
            distance = sqrt((double)carre);
            if(distance == portee){
                return 1;
            }
        }
    }
}

/*
 * fonction recursive qui teste de prévoir le coup optimal que l'ordinateur pourrait effectuer
 * retourne le meilleur coup s'il existe ou le maximum des coups
 */
int tour_ordi_opti(int indice_sort,char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage){
	int i, score;
	int max = -2;
	if(fonction_evalution(indice_sort,map,joueur1,joueur2,numero_personnage)){/* fonction evaluation */
		return 1;
	}
	else{
		for(i=1 ;i < NB_SORTS; i++){
			score = tour_joueur_opti(i,map,joueur1,joueur2,numero_personnage);
			if( score > max){
				max = score;
			}
		}
	}
    return max;
}
/*
 * fonction recursive qui teste de prévoir le coup optimal que le joueur pourrait effectuer
 * paramètre nb: sort n°
 * paramètre joueur:
 */
int tour_joueur_opti(int indice_sort,char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage){
	int i, score;
	int min = 2;
	if(fonction_evalution(indice_sort,map,joueur1,joueur2,numero_personnage)){/* fonction evaluation */
		return -1;
	}
    for(i=1 ;i < NB_SORTS; i++){
        if(numero_personnage == 1)
            score = tour_ordi_opti(i,map,joueur2,joueur1,numero_personnage);
        else
            score = tour_ordi_opti(i,map,joueur2,joueur1,numero_personnage);
        if( score < min){
			min = score;
		}
	}
    return min;
}
/*
 * Fonction qui effectue le meilleur coup de l'ordi
 */
int coup_ordi_opti(char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage){
	int i = 0,score;
    int max = -2, imax=-1;

	/* pour tout les sorts on va tester de savoir qu'elle est le meilleur sort possible pour ce tour */
	for(i = 1; i <= NB_SORTS; i++){
        // on joue le coup
        // renvoyer le max des scores
        score = tour_joueur_opti(i,map,joueur1,joueur2,numero_personnage);
        if( score > max){
			max = score;
            imax = i;
		}
	}
	return imax; /* on retourne l'indice du sort */
}


int main() {
    int i = 0;
    t_joueur joueur1,joueur2;
    joueur1.perso1 = creer_perso(classe1);
	joueur1.perso2 = creer_perso(classe2);
    joueur1.numJoueur = 1;
    joueur1.nbPersoVivant = NB_PERSONNAGES;
    joueur2.perso1 = creer_perso(classe1);
	joueur2.perso2 = creer_perso(classe2);
    joueur2.numJoueur = 2;
    joueur2.nbPersoVivant = NB_PERSONNAGES;

    joueur1.perso1->x = 11;
    joueur1.perso1->y = 5;
    joueur2.perso1->x = 11;
    joueur2.perso1->y = 6;


	i = coup_ordi_opti(map,joueur1,joueur2,1)
    printf("%i\n",i);
    int x1,x2,y1,y2,dist,carre;
    x1 = 11;
    y1 = 5;
    x2 = 11;
    y2 = 6;
    carre = pow((double)(x1 - x2),2) + pow((double)(y1 - y2),2);
    dist = sqrt((double)carre);
    printf("distance = %i\n",dist);
}
