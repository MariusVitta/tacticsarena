#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


int tour_ordi_opti(int nb);
int tour_joueur_opti(int nb);
int coup_ordi_opti(int nb,char c);


int coup_gagnant(t_personnage *j1,t_personnage *j2){

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
int tour_ordi_opti(int nb,t_personnage perso){
	int i, score;
	int max = -2;
	if((nb + M) >= N){
		return 1;
	}
	else{
		for(i=1 ;i < M && nb +i <= N; i++){
			score = tour_joueur_opti(nb+i);
			if( score > max){
				max = score;
			}
		}
	}
    return max;
}
/*
 * fonction recursive qui teste de prévoir le coup optimal que le joueur pourrait effectuer
 * paramètre nb: sort n°1
 * paramètre joueur:
 */
int tour_joueur_opti(int nb,t_personnage perso){
	int i, score;
	int min = 2;
	if((nb + M) >= N){
		return -1;
	}
    for(i=1 ;i < M && nb +i <= N ; i++){
        score = tour_ordi_opti(nb+i);
        if( score < min){
			min = score;
		}
	}
    return min;
}
/*
 * Fonction qui effectue le meilleur coup de l'ordi
 */
int coup_ordi_opti(int nb,char c){
	int i = 0,coups[M],score;
    int max = -2, imax=-1;
	if((nb + M) >= N){
		printf("%c joue %d\ttotal:%d\n",c,N-nb,N);
		return N-nb;
	}
	else{
		for(i = 1; i <= M &&  nb +i <= N; i++){
            // on joue le coup
            // renvoyer le max des scores
            score = tour_joueur_opti(nb+i);
            if( score > max){
				max = score;
                imax = i;
			}
		}
		return imax;
	}
}






}
