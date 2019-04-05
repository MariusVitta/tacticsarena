#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonc.h"
#include "define.h"

char map[N][N];

int tour_ordi_opti(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage);
int tour_equipe_opti(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage);
int coup_ordi_opti(char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage);
int fonction_evalution(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage);
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
    for(j = 1; j <= MAX_NB_SORT; j++ ){
        /* on verifie si un sort avec la meme distance que le sort (indice_sort) n'est pas un nombre de dégat plus important */
        if(perso->sorts[indice_sort]->degat > degat )
                    return portee--;
    }
    //return portee;
}

int eval_vie();

int eval_deplacement(t_personnage * perso,int indice_sort,int portee,int distance){
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
 * return : portee du sort (indice_sort) ou la différence entre la distance entre les deux equipes et la portée du sort
 */
int fonction_evalution(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage){
    int portee = 0,i,degat;
    t_personnage * temp;
    /* choix du personnage du equipe 1 */
    if(numero_personnage == 1)
        temp = equipe1->perso1;
    else
        temp = equipe1->perso2;
    int distance,carre;

    //recupération de la portée et des dégats selon le sort

    portee = temp->sorts[indice_sort]->portee;
    degat = temp->sorts[indice_sort]->degat;


    for(i = 1; i <= NB_PERSONNAGES;i++){
        if(i == 1){
            /* test du sort sur le premier perso de l'adversaire */
            carre = pow((double)(temp->coord.x - equipe2->perso1->coord.x),2) + pow((double)(temp->coord.y - equipe2->perso1->coord.y),2);
            distance = sqrt((double)carre);
            if(distance <= portee){
                /* si distance entre les deux personages est plus petites que la portée du sort on retourne la portée du sort*/
                portee = eval_degat(temp,indice_sort,portee,degat);
                return portee;
            }
        }
        else{
            /* test du sort sur le deuxième perso de l'adversaire */
            carre = pow((double)(temp->coord.x - equipe2->perso2->coord.x),2) + pow((double)(temp->coord.y - equipe2->perso2->coord.y),2);
            distance = sqrt((double)carre);
            if(distance <= portee){
                portee = eval_degat(temp,indice_sort,portee,degat);
                return portee;
            }
        }
    }
    printf("SALUT \n" );
    /* si on est hors portée pour tout les personnages */
    //portee = eval_degat(temp,indice_sort,portee,degat);
    return (portee--);// != 0 ? (distance - portee) :portee);
}

/*
 * fonction recursive qui teste de prévoir le coup optimal que l'ordinateur pourrait effectuer
 * retourne le meilleur coup s'il existe ou le maximum des coups
 */
int tour_ordi_opti(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage){
	int i, score,eval;
	int max = -10;
    eval = fonction_evalution(indice_sort,map,equipe1,equipe2,numero_personnage);
    printf("eval ordi : %i\n",eval );
	if(eval >=0)/* fonction evaluation */
		return eval;
	else{
		for(i=1 ;i < MAX_NB_SORT; i++){
            if(numero_personnage == 1)
                score = tour_equipe_opti(i,map,equipe1,equipe2,numero_personnage);
            else
                score = tour_equipe_opti(i,map,equipe1,equipe2,numero_personnage);
			if( score > max){
				max = score;
			}
		}
	}
    return max;
}

/*
 * fonction recursive qui teste de prévoir le coup optimal que le equipe pourrait effectuer
 * paramètre nb: sort n°
 * paramètre equipe:
 */
int tour_equipe_opti(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage){
	int i, score,eval;
	int min = 10;
    eval = fonction_evalution(indice_sort,map,equipe1,equipe2,numero_personnage);
    printf("eval equipe :%i\n",eval );
	if(eval >=0) /* fonction evaluation */
		return eval;
    else{
        for(i=1 ;i < MAX_NB_SORT; i++){
            if(numero_personnage == 1)
                score = tour_ordi_opti(i,map,equipe2,equipe1,numero_personnage);
            else
                score = tour_ordi_opti(i,map,equipe2,equipe1,numero_personnage);
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
int coup_ordi_opti(char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage){
	int i = 0,score;
    int max = -10, imax=-1;

	/* pour tout les sorts on va tester de savoir qu'elle est le meilleur sort possible pour ce tour */
	for(i = 1; i <= MAX_NB_SORT; i++){
        // on joue le coup
        // renvoyer le max des scores
        score = tour_equipe_opti(i,map,equipe1,equipe2,numero_personnage);
        printf("====== SCORE APRES TOUR equipe : %i ===== \n\n",score );
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
    int classe[NB_PERSONNAGES+1];
    t_equipe * equipe1,*equipe2;
    /*Creation de toutes les classes et tous les sorts */
	t_personnage * persos[CLASSES+1];
	t_sort * sorts[SORTS+1];
	for(int i = 1; i <= SORTS;i++)
		sorts[i] = malloc(sizeof(t_sort));

	creation_sorts(sorts);

	for(int i = 1; i <= CLASSES;i++)
		persos[i] = malloc(sizeof(t_personnage));

	creation_classes(persos,sorts);
	/*fin de création des sorts et classes*/

    /*création des équipes et personnages par équipe*/
	equipe1 = malloc(sizeof(t_equipe));
	equipe2 = malloc(sizeof(t_equipe));


    equipe1->perso1 =copie_perso(persos[classe[1]]);
	equipe1->perso2 = copie_perso(persos[classe[1]]);
    equipe1->numEquipe = 1;
    equipe1->nbPersoVivant = NB_PERSONNAGES;
    equipe2->perso1 = copie_perso(persos[classe[1]]);
	equipe2->perso2 = copie_perso(persos[classe[1]]);
    equipe2->numEquipe = 2;
    equipe2->nbPersoVivant = NB_PERSONNAGES;

    equipe1->perso1->coord.x = 11;
    equipe1->perso1->coord.y = 5;
    equipe2->perso1->coord.x = 1;
    equipe2->perso1->coord.y = 6;

    printf("meilleur coup : {%i}\n",coup_ordi_opti(map,equipe1,equipe2,1));
    int dist,carre;

    carre = pow((double)(equipe1->perso1->coord.x - equipe2->perso1->coord.x),2) + pow((double)(equipe1->perso1->coord.y - equipe2->perso1->coord.y),2);
    dist = sqrt((double)carre);
    printf("distance = %i\n",dist);
    //affichage_map(map);
}
