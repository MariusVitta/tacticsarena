#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fonc.h"
#include "define.h"

/**
 *\file ia.c
 *\brief programme de test du bot
 *\author Marius
 *\version 0.1
 *\date 28/02/2019
*/

char map[N][N];
typedef enum {NORD = 1,EST = 2,SUD = 3,OUEST = 4}t_direction;
int tour_ordi_opti(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,int * hors_portee);
int tour_equipe_opti(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,int * hors_portee);
int coup_ordi_opti(char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,int * hors_portee);
int eval_sort(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage, int * hors_portee);
int eval_degat(t_personnage * perso,int indice_sort,int portee,int degat);
int eval_deplacement(t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,t_direction * direction);
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
    return portee;
}

int eval_vie();

int eval_deplacement(t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,t_direction * direction){
    srand(time(NULL));
    int choix = rand()%2;
    int i,carre,plus_proche,distance_x,distance_y;
    int distance[NB_PERSONNAGES];
    t_personnage * temp;
    /* choix du personnage du equipe 1 */
    if(numero_personnage == 1)
        temp = equipe1->perso1;
    else
        temp = equipe1->perso2;
    char * chaine;
    //printf("Attente...");
    //scanf("%s",chaine);

    for(i = 0; i < NB_PERSONNAGES;i++){
        //on cherche à savoir quel est le personnage le plus proche du personnage 'perso'
        if(!i){
            carre = pow((double)(temp->coord.x - equipe2->perso1->coord.x),2) + pow((double)(temp->coord.y - equipe2->perso1->coord.y),2);
            distance[i] = sqrt((double)carre);
            plus_proche = i;

        }
        else{
            carre = pow((double)(temp->coord.x - equipe2->perso2->coord.x),2) + pow((double)(temp->coord.y - equipe2->perso2->coord.y),2);
            distance[i] = sqrt((double)carre);
            if(distance[i] < distance[i - 1])
                plus_proche = i;
        }
    }

    printf("indice du joueur le plus proche : %i\n",plus_proche +1 );
    //on cherche à savoir quel est la coordonées la plus élévée entre les deux personnages le x ou le y
    if(!plus_proche){ //si le personnage le plus éloigné est le 1er personnage
        distance_x = temp->coord.x - equipe2->perso1->coord.x;
        distance_y = temp->coord.y - equipe2->perso1->coord.y;
    }
    else{
        distance_x = temp->coord.x - equipe2->perso2->coord.x;
        distance_y = temp->coord.y - equipe2->perso2->coord.y;
    }

    printf("{ x : %i et y: %i }\n",distance_x,distance_y);
    if(distance_x > distance_y  && distance_x > 0){
        //si l'ennemi le plus proche est situé à gauche ou à droite et que la distance en x est plus grande que la distance en y
        //if(distance_x > 0){
            if(temp->coord.x-1<0 || (map[temp->coord.y][temp->coord.x-1]!='.'))
				printf(" ---- Déplacement impossible 1 ---- \n" );
			else{
				printf(" ---- Déplacement à Gauche ---- \n" );
				*direction = OUEST;
			}
        //}
        //else{

        //}
    }
    else if(distance_x > distance_y  && distance_x < 0){   // si la distance en x est égale à la distance en y
        //on fais avancer le perso soit en x soit en y
        if(temp->coord.x+1>=N || (map[temp->coord.y][temp->coord.x+1]!='.'))
            printf(" ---- Déplacement impossible 2 ---- \n" );
        else{
            printf(" ---- Déplacement à Droite ---- \n" );
            *direction = EST;
        }
        printf("3");

    }
    else if( distance_x < distance_y  && distance_y > 0){ // si la distance en y est supérieur à la distance en x
        //if(distance_y > 0){
            if(temp->coord.y-1<0 || (map[temp->coord.y-1][temp->coord.x]!='.'))
				printf(" ---- Déplacement impossible 3 ---- \n" );
			else{
				printf(" ---- Déplacement en Haut ---- \n" );
				*direction = NORD;
			}

        //}
        //else{

        //}
    }
    else if(distance_x < distance_y  && distance_y < 0){
        if(temp->coord.y+1>=N || (map[temp->coord.y+1][temp->coord.x]!='.'))
            printf(" ---- Déplacement impossible 4 ---- \n" );
        else{
            printf(" ---- Déplacement en Bas ---- \n" );
            *direction = SUD;
        }
    }

    printf("DIR : %i ",*direction);




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
    return 0;
}



/*
 * Fonction d'évalutation pour le MinMax retourne soit un entier supérieur ou égale à  soit un négatif
 * paramètre indice_sort: sort actuel que l'on soit tester
 * return : portee du sort (indice_sort) ou la différence entre la distance entre les deux equipes et la portée du sort
 */
int eval_sort(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,int * hors_portee){
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

    /* pour tout les personnages possibles de l'adversaire */
    for(i = 0; i < NB_PERSONNAGES;i++){
        if(!i){
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
    (*hors_portee)++;
    /* si on est hors portée pour tout les personnages */
    //portee = eval_degat(temp,indice_sort,portee,degat);
    return (portee);// != 0 ? (distance - portee) :portee);
}

/*
 * fonction recursive qui teste de prévoir le coup optimal que l'ordinateur pourrait effectuer
 * retourne le meilleur coup s'il existe ou le maximum des coups
 */
int tour_ordi_opti(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,int * hors_portee){
	int i, score,eval;
	int max = -30;
    //
    eval = eval_sort(indice_sort,map,equipe1,equipe2,numero_personnage,hors_portee);
    printf("eval ordi : %i\n",eval );
    //si ce meilleur coup de l'ordi existe on retourne l'indice du meilleur coup
	if(eval >=0)/* fonction evaluation */
		return eval;
	else{
		for(i=0 ;i < MAX_NB_SORT; i++){
            if(numero_personnage == 1)
                score = tour_equipe_opti(i,map,equipe1,equipe2,numero_personnage,hors_portee);
            else
                score = tour_equipe_opti(i,map,equipe1,equipe2,numero_personnage,hors_portee);
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
int tour_equipe_opti(int indice_sort,char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,int * hors_portee){
	int i, score,eval;
	int min = 10;
    //on va chercher à savoir si on trouve un meilleur coup
    eval = eval_sort(indice_sort,map,equipe1,equipe2,numero_personnage,hors_portee);printf("eval equipe :%i\n",eval );
    //si ce meilleur coup existe on retourne l'indice du meilleur coup
	if(eval >=0) /* fonction evaluation */
		return eval;
    else{
        for(i=0 ;i < MAX_NB_SORT; i++){
            if(numero_personnage == 1)
                score = tour_ordi_opti(i,map,equipe2,equipe1,numero_personnage,hors_portee);
            else
                score = tour_ordi_opti(i,map,equipe2,equipe1,numero_personnage,hors_portee);
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
int coup_ordi_opti(char map[N][N],t_equipe * equipe1,t_equipe * equipe2,int numero_personnage,int * hors_portee){
	int i = 0,score;
    int max = -30, imax=-1;

	/* pour tout les sorts on va tester de savoir qu'elle est le meilleur sort possible pour ce tour */
	for(i = 0; i < MAX_NB_SORT; i++){
        // on joue le coup
        score = tour_equipe_opti(i,map,equipe1,equipe2,numero_personnage,hors_portee);
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
    int i = 0,hors_portee = 0;
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

    t_equipe * tab[NB_EQUIPES+1];
	tab[1] = equipe1;
	tab[2] = equipe2;

    for(int i = 1; i < N;i++)
		for(int j = 1; j < N;j++)
			map[i][j] = '.';

    equipe1->perso1 = copie_perso(persos[1]);
	equipe1->perso2 = copie_perso(persos[2]);
    equipe1->numEquipe = 1;
    equipe1->nbPersoVivant = NB_PERSONNAGES;
    equipe2->perso1 = copie_perso(persos[3]);
	equipe2->perso2 = copie_perso(persos[4]);
    equipe2->numEquipe = 2;
    equipe2->nbPersoVivant = NB_PERSONNAGES;

    equipe1->perso1->coord.x = 5;
    equipe1->perso1->coord.y = 4;
    equipe2->perso1->coord.x = 5;
    equipe2->perso1->coord.y = 6;
    map[4][5] = '1';
    map[6][5] = '2';

    equipe2->perso2->coord.x = 1;
    equipe2->perso2->coord.y = 1;

    printf("meilleur coup : {%i}\n",coup_ordi_opti(map,equipe1,equipe2,1,&hors_portee) + 1);
    printf("nombre de sorts hors portée : %i\n",hors_portee );
    t_direction direction = NORD;
    eval_deplacement(equipe1,equipe2,1,&direction);
    printf("{ Direction : %d }\n",direction );
    int dist,carre,j;
    //for(j = 0;j < NB_PERSONNAGES; j++){
        carre = pow((double)(equipe1->perso1->coord.x - equipe2->perso1->coord.x),2) + pow((double)(equipe1->perso1->coord.y - equipe2->perso1->coord.y),2);
        dist = sqrt((double)carre);
        printf("{ distance = %i }\n",dist);
    //}
    affichage_map(map);



    /*suppression de tous les mallocs*/
	for(i = 1; i < SORTS; i++){
		suppr_sort(&(sorts[i]));
	}
    printf("1er free\n" );

	for(i = 1; i <= CLASSES; i++){
		suppr_perso(&(persos[i]));
	}
    printf("2eme free\n" );

	for(i=1; i <= NB_EQUIPES; i++){
		suppr_perso(&(tab[i]->perso1));
		suppr_perso(&(tab[i]->perso2));
		free(tab[i]);
		tab[i] = NULL;
	}
    printf("3eme free\n" );
    return 0;
}
