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
int eval_degat(t_personnage * perso,int indice_sort,int portee,int degat);
int eval_deplacement();
int eval_vie();
/*
 * fonction qui évalue si un sort fais plus de dégat que le sort (indice_sort)
 * paramètre indice_sort: sort que l'on teste
 * paramètre portee : portée du sort indice_sort
 * paramètre degat: degat du sort indice_sort
 * return la portee du sort + les degats;
 */
int eval_degat(t_personnage * perso,int indice_sort,int portee,int degat){
    int j;
    for(j = 1; j <= NB_SORTS; j++ ){
        /* on verifie si un sort avec la meme distance que le sort (indice_sort) n'est pas un nombre de dégat plus important */
        switch (j){
            case 1: if(perso->s1.degat > degat )
                        portee--;
                break;
            case 2: if(perso->s2.degat > degat )
                        portee--;
                break;
            case 3: if(perso->s3.degat > degat)
                        portee--;
                break;
            case 4: if(perso->s4.degat > degat )
                        portee--;
                break;
        }
    }
    return portee;
}

int eval_vie();

int eval_deplacement(){
    /*
    //h
    if(temp->coord.y-1<0 || (map[temp->coord.y-1][temp->coord.x]!='.'))
    //b
    if(temp->coord.y+1>=N || (map[temp->coord.y+1][temp->coord.x]!='.')
    //g
    if(temp->coord.x-1<0 || (map[temp->coord.y][temp->coord.x-1]!='.'))
    //d
    if(temp->coord.x+1>=N || (map[temp->coord.y][temp->coord.x+1]!='.'))
    */
}



/*
 * Fonction d'évalutation pour le MinMax retourne soit un entier supérieur ou égale à  soit un négatif
 * paramètre indice_sort: sort actuel que l'on soit tester
 * return : portee du sort (indice_sort) ou la différence entre la distance entre les deux joueurs et la portée du sort
 */
int fonction_evalution(int indice_sort,char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage){
    int portee = 0,i,degat;
    t_personnage * temp;
    /* choix du personnage du joueur 1 */
    if(numero_personnage == 1)
        temp = joueur1.perso1;
    else
        temp = joueur1.perso2;
    int distance,carre;

    //recupération de la portée et des dégats selon le sort
    switch (indice_sort){
        case 1: portee = temp->s1.portee;degat = temp->s1.degat;break;
        case 2: portee = temp->s2.portee;degat = temp->s2.degat;break;
        case 3: portee = temp->s3.portee;degat = temp->s3.degat;break;
        case 4: portee = temp->s4.portee;degat = temp->s4.degat;break;
    }

    for(i = 1; i <= NB_PERSONNAGES;i++){
        if(i == 1){
            /* test du sort sur le premier perso de l'adversaire */
            carre = pow((double)(temp->coord.x - joueur2.perso1->coord.x),2) + pow((double)(temp->coord.y - joueur2.perso1->coord.y),2);
            distance = sqrt((double)carre);
            if(distance <= portee){
                /* si distance entre les deux personages est plus petites que la portée du sort on retourne la portée du sort*/
                portee = eval_degat(temp,indice_sort,portee,degat);
                return portee;
            }
        }
        else{
            /* test du sort sur le deuxième perso de l'adversaire */
            carre = pow((double)(temp->coord.x - joueur2.perso2->coord.x),2) + pow((double)(temp->coord.y - joueur2.perso2->coord.y),2);
            distance = sqrt((double)carre);
            if(distance <= portee){
                portee = eval_degat(temp,indice_sort,portee,degat);
                return portee;
            }
        }
    }
    printf("SALUT\n" );
    /* si on est hors portée pour tout les personnages */
    portee = eval_degat(temp,indice_sort,portee,degat);
    return (portee);// != 0 ? (distance - portee) :portee);
}

/*
 * fonction recursive qui teste de prévoir le coup optimal que l'ordinateur pourrait effectuer
 * retourne le meilleur coup s'il existe ou le maximum des coups
 */
int tour_ordi_opti(int indice_sort,char map[N][N],t_joueur joueur1,t_joueur joueur2,int numero_personnage){
	int i, score,eval;
	int max = -2;
    eval = fonction_evalution(indice_sort,map,joueur1,joueur2,numero_personnage);
    printf("eval ordi : %i\n",eval );
	if(eval >=0)/* fonction evaluation */
		return eval;
	else{
		for(i=1 ;i < NB_SORTS; i++){
            if(numero_personnage == 1)
                score = tour_joueur_opti(i,map,joueur1,joueur2,numero_personnage);
            else
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
	int i, score,eval;
	int min = 2;
    eval = fonction_evalution(indice_sort,map,joueur1,joueur2,numero_personnage);
    printf("eval joueur :%i\n",eval );
	if(eval >=0) /* fonction evaluation */
		return eval;
    else{
        for(i=1 ;i < NB_SORTS; i++){
            if(numero_personnage == 1)
                score = tour_ordi_opti(i,map,joueur2,joueur1,numero_personnage);
            else
                score = tour_ordi_opti(i,map,joueur2,joueur1,numero_personnage);
            if( score < min){
    			min = score;
    		}
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
        printf("====== SCORE APRES TOUR JOUEUR : %i ===== \n\n",score );
        if( score > max){
			max = score;
            imax = i;
			printf("imax = %i,max = %i\n",imax,max);
		}
	}
	return imax; /* on retourne l'indice du sort */
}


int main() {
    int i = 0;
    t_joueur joueur1,joueur2;
    joueur1.perso1 = creer_perso(3);
	joueur1.perso2 = creer_perso(2);
    joueur1.numJoueur = 1;
    joueur1.nbPersoVivant = NB_PERSONNAGES;
    joueur2.perso1 = creer_perso(2);
	joueur2.perso2 = creer_perso(1);
    joueur2.numJoueur = 2;
    joueur2.nbPersoVivant = NB_PERSONNAGES;

    joueur1.perso1->coord.x = 11;
    joueur1.perso1->coord.y = 5;
    joueur2.perso1->coord.x = 11;
    joueur2.perso1->coord.y = 6;

    printf("meilleur coup : {%i}\n",coup_ordi_opti(map,joueur1,joueur2,1));
    int dist,carre;

    carre = pow((double)(joueur1.perso1->coord.x - joueur2.perso1->coord.x),2) + pow((double)(joueur1.perso1->coord.y - joueur2.perso1->coord.y),2);
    dist = sqrt((double)carre);
    printf("distance = %i\n",dist);
    //affichage_map(map);
}
