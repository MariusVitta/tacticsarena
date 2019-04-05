#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonc.h"
#include "define.h"

void suppr_sort(t_sort ** sort){

		free((*sort)->nom);
		free(*sort);
		*sort = NULL;
}

void suppr_perso(t_personnage ** perso){
	int i;

	for(i = MAX_NB_SORT-1; i > 0; i--){
//fprintf(stderr,"suppression sort %d\n",i);
	suppr_sort(&((*perso)->sorts[i]));
	}
	fprintf(stderr,"1\n");
	free((*perso)->nom);
	fprintf(stderr,"2\n");
	free(*perso);
	fprintf(stderr,"3\n");
	*perso = NULL;
	fprintf(stderr,"4\n");

}


void (*creer_sort(int id_sort))(char [N][N], t_personnage * , t_joueur* ,t_joueur* ,int,int ,int){

	void (*fonc )(char [N][N], t_personnage * ,  t_joueur* ,t_joueur* ,int, int,int);


	switch (id_sort) {
		case 1:

			fonc = saut;
			break;
		case 2:
			fonc = soin;
			break;
		case 3:
			fonc = petit_coup;
			break;
		case 4:
			fonc = grosCoup;
			break;
		case 5:
			fonc = diago;
			break;
		case 6:
			fonc = ligne;
			break;
		case 7:
			fonc = double_tape;
			break;
		case 8:
			fonc = coup_zone;
			break;
		case 9:
			fonc = armure;
			break;
		case 10:
			fonc = attire;
			break;
		case 11:
			fonc = chenchen;
			break;
		case 12:
			fonc = bigshaq;
			break;
		case 13:
			fonc = felin;
			break;
		case 14:
			fonc = chouette;
			break;
		case 15:
			fonc = fuego;
			break;
		case 16:
			fonc = revitalisation;
			break;
		default : fonc = NULL;
	}
	return fonc;
}


void creation_sorts(t_sort * sorts[]){

	FILE * s = NULL;
	s = fopen("sorts.txt","r");

	int verif,id,portee,degat,cd,uptm,point_action;


	if(s != NULL){
		char * nom = malloc(sizeof(char)* TAILLE_MAX);
		while((verif = fscanf(s,"%d %s %d %d %d %d %d",&id,nom,&portee,&degat,&cd,&uptm,&point_action)) != EOF){

			sorts[id]->id = id;
			sorts[id]->nom = nom;
			sorts[id]->portee = portee;
			sorts[id]->degat = degat;
			sorts[id]->cd = cd;
			sorts[id]->uptm = uptm;
			sorts[id]->point_action = point_action;
			sorts[id]->sort = creer_sort(id);


		//	printf("%d %s %d %d %d %d %d",id,nom,portee,degat,cd,uptm,point_action);
			nom = malloc(sizeof(char)*TAILLE_MAX);
		}
		free(nom);
		fclose(s);
	}
	else{
		printf("Pas dans le fichier\n" );

	}

}


/*création de la classe choisie par l'utilisateur*/
void creation_classes(t_personnage * persos[],t_sort * sorts[]){

	FILE * c = NULL;
	c = fopen("classe.txt","r");



	int verif;
	int id,point_action,pv,pv_max,pa,pm,s1,s2,s3,s4;



	if(c != NULL){
		char * nom2 = malloc(sizeof(char)*TAILLE_MAX);
		while((verif = fscanf(c,"%d %s %d %d %d %d %d %d %d %d",&id,nom2,&pv,&pv_max,&pa,&pm,&s1,&s2,&s3,&s4)) != EOF){

			persos[id]->id = id;
			persos[id]->nom = nom2;
			persos[id]->pv = pv;
			persos[id]->pv_max = pv_max;
			persos[id]->pa = pa;
			persos[id]->pm = pm;
			persos[id]->sorts[0] = sorts[s1];
			persos[id]->sorts[1] = sorts[s2];
			persos[id]->sorts[2] = sorts[s3];
			persos[id]->sorts[3] = sorts[s4];


			nom2 = malloc(sizeof(char)*TAILLE_MAX);
		}

		free(nom2);
		fclose(c);
	}
	else{
		printf("Pas dans le fichier\n" );
	}
}

t_sort * copie_sort(t_sort * sort){

	t_sort * nv_sort = malloc(sizeof(t_sort));
	nv_sort->nom = malloc(sizeof(char)* TAILLE_MAX);

	nv_sort->id = sort->id;
	strcpy(nv_sort->nom,sort->nom);
	nv_sort->portee = sort->portee;
	nv_sort->degat = sort->degat;
	nv_sort->cd = sort->cd;
	nv_sort->uptm = sort->uptm;
	nv_sort->point_action = sort->point_action;
	nv_sort->sort = sort->sort;

	return nv_sort;
}


t_personnage * copie_perso(t_personnage * perso){

		t_personnage * nv_perso = malloc(sizeof(t_personnage));
		nv_perso->nom = malloc(sizeof(char)* TAILLE_MAX);

		nv_perso->id = perso->id ;
		strcpy(nv_perso->nom,perso->nom);
		nv_perso->pv = perso->pv ;
		nv_perso->pv_max = perso->pv_max;
		nv_perso->pa = perso->pa ;
		nv_perso->pm = perso->pm ;
		nv_perso->sorts[0] = copie_sort(perso->sorts[0]);
		nv_perso->sorts[1] = copie_sort(perso->sorts[1]);
		nv_perso->sorts[2] = copie_sort(perso->sorts[2]);
		nv_perso->sorts[3] = copie_sort(perso->sorts[3]);

		return nv_perso;
}


/*
int main (){

	int i, j,test=0,nb_tour = 1,mort1 = 0,mort2 = 0;
	int classe[NB_PERSONNAGES+1];
  int indice_joueur = 1,numero_personnage = 1;

	t_joueur * joueur1, * joueur2;

	/*Creation de toutes les classes et tous les sorts */
	/*	t_personnage * persos[CLASSES+1];

	t_sort * sorts[SORTS+1];
	for(int i = 1; i <= SORTS;i++)
		sorts[i] = malloc(sizeof(t_sort));

	creation_sorts(sorts);

	for(int i = 1; i <= CLASSES;i++)
		persos[i] = malloc(sizeof(t_personnage));

	creation_classes(persos,sorts);

	joueur1 = malloc(sizeof(t_joueur));
	joueur2 = malloc(sizeof(t_joueur));

	t_joueur * tab[NB_JOUEURS+1];
	tab[1] = joueur1;
	tab[2] = joueur2;




	for(i = 1; i < SORTS; i++){
		printf("suppression %s\n",sorts[i]->nom);
		suppr_sort(&(sorts[i]));
		printf("suppression sort\n\n");
	}

	for(i = 1; i <= CLASSES; i++){
		printf("suppression %s\n",persos[i]->nom);
		suppr_perso(&(persos[i]));
		printf("suppression perso\n\n");
	}


		return 0;
}*/
