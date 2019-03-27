#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

#define NB_SORTS 4
char map[N][N];

int tour_ordi_opti(int indice_sort,char map[N][N],t_personnage perso1,t_personnage perso2,int numero_personnage);
int tour_joueur_opti(int indice_sort,char map[N][N],t_personnage perso1,t_personnage perso2,int numero_personnage);
int coup_ordi_opti(map[N][N],t_personnage perso1,t_personnage perso2,int numero_personnage);
int fonction_evalution(int indice_sort,char map[N][N],t_personnage perso1,t_personnage perso2,int numero_personnage);

int fonction_evalution(int indice_sort,char map[N][N],t_personnage perso1,t_personnage perso2,int numero_personnage){

  if(!(strcmp("Guerrier",j1->nom))){

    if(j2->pv - j1->s3.degat <= 0)
      if(j1->s3.portee + j1->pm <= (abs(j1->coord.x-j2->coord.x)+abs(j1->coord.y-j2->coord.y)))
        return 3;

    else if(j2->pv - j1->s4.degat <= 0)
      if(j1->s4.portee + j1->pm <= (abs(j1->coord.x-j2->coord.x)+abs(j1->coord.y-j2->coord.y)))
        return 4;

    else
      return 0;

  }
}

/*
 * fonction recursive qui teste de prévoir le coup optimal que l'ordinateur pourrait effectuer
 * retourne le meilleur coup s'il existe ou le maximum des coups
 */
int tour_ordi_opti(int indice_sort,char map[N][N],t_personnage perso1,t_personnage perso2,int numero_personnage){
	int i, score;
	int max = -2;
	if((nb + M) >= N){/* fonction evaluation */
		return 1;
	}
	else{
		for(i=1 ;i < NB_SORTS && nb +i <= N; i++){
			score = tour_joueur_opti(i);
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
int tour_joueur_opti(int indice_sort,char map[N][N],t_personnage perso1,t_personnage perso2,int numero_personnage){
	int i, score;
	int min = 2;
	if((nb + M) >= N){/* fonction evaluation */
		return -1;
	}
    for(i=1 ;i < NB_SORTS && nb +i <= N ; i++){
        score = tour_ordi_opti(i);
        if( score < min){
			min = score;
		}
	}
    return min;
}
/*
 * Fonction qui effectue le meilleur coup de l'ordi
 */
int coup_ordi_opti(char map[N][N],t_personnage perso1,t_personnage perso2,int numero_personnage){
	int i = 0,score;
    int max = -2, imax=-1;
	/*if((nb + M) >= N){
		printf("%c joue %d\ttotal:%d\n",c,N-nb,N);
		return N-nb;
	}
	else{*/
		/* pour tout les sorts on va tester de savoir qu'elle est le meilleur sort possible pour ce tour */
		for(i = 1; i <= NB_SORTS &&  nb +i <= N; i++){
            // on joue le coup
            // renvoyer le max des scores
            score = tour_joueur_opti(i,map,perso1,perso2,numero_personnage);
            if( score > max){
				max = score;
                imax = i;
			}
		}
		return imax; /* on retourne l'indice du sort */
	}
}


int int main() {

	coup_ordi_opti(map,perso1,perso2,1)

	return 0;
}



}
