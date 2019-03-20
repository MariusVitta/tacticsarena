#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

/*
 * fonction pour tester si un personnage est mort ou pas
 * return  0 ou 1
 */
int est_mort(t_personnage * perso){
	return (perso->pv <= 0);
}

/*
 * Fonction de mise à jour de l'affichage de la map
 *  paramètre joueur1,joueur2 : utilisé afin d'obtenir les coordonnées de tout les persos
 */
void maj(char map[N][N], t_joueur joueur1, t_joueur joueur2){
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(map[i][j] != 'o')
				map[i][j] = '.';
        }
	}

    /* joueur 1 */
    if(!est_mort(joueur1.perso1)){
	       map[joueur1.perso1->coord.y][joueur1.perso1->coord.x] = '1';
    }
    if(!est_mort(joueur1.perso2)){
        map[joueur1.perso2->coord.y][joueur1.perso2->coord.x] = '3';
    }
    /* joueur 2*/
    if(!est_mort(joueur2.perso1)){
	   map[joueur2.perso1->coord.y][joueur2.perso1->coord.x] = '2';
    }
    if(!est_mort(joueur2.perso2)){
        map[joueur2.perso2->coord.y][joueur2.perso2->coord.x] = '4';
    }
}


/*************************************************************
*										Sorts du guerrier												 *
*************************************************************/


/*
 * Fonction qui regarde la vie au personnage j1
 * paramètre j1: personnage1 que l'on souhaite soigner
 */
void soin(t_personnage * j1) {
  printf("Le guerrier a %d points de vie\n",j1->pv);
  if(j1->pv+j1->s2.degat<=j1->pv_max)
    j1->pv+=j1->s2.degat;
  else
    j1->pv=j1->pv_max;

  printf("Le guerrier se soigne de %d et a maintenant %d points de vie sur %d\n",j1->s2.degat,j1->pv,j1->pv_max);
}

int existe(char mat[N][N], char choix, int * x, int * y){
	int i, j;

	if(choix == 'o')
		return 0;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(mat[i][j] == choix){
				*x = j;
				*y = i;
				return 1;
			}
		}
	}
	return 0;
}

/*
 * Fonction qui effectue un coup une case autour du personnage
 * sur une distance "portee"
 * paramètre t_personnage * perso1: personnage qui attaque
 * paramètre t_joueur j2: personnage qui subit les dégats
 */
void grosCoup(char map[N][N], t_personnage * perso1, t_joueur j2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;

    /*copie plan jeu dans la matrice point*/
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = perso1->coord.y + 1;
	j = perso1->coord.x ;


	int nb = 0;
	int car = 0;

	for(; i < N && nb < perso1->s4.portee && point[i][j] != 'o'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x;
	nb = 0;

	for(; i >= 0  && nb < perso1->s4.portee && point[i][j] != 'o'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; j < N && nb < perso1->s4.portee && point[i][j] != 'o'; j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < perso1->s4.portee && point[i][j] != 'o'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
    if((map[y][x] == '4') || (map[y][x] == '3')){ /* si ce sont les personnages 2 des joueurs 1 ou 2* qui sont touchés */
        j2.perso2->pv -= perso1->s3.degat;
		printf("%s touché.\nPoint de vie : %i\n", j2.perso2->nom, j2.perso2->pv);
	}
    else if((map[y][x] == '2') || (map[y][x] == '1')){
        j2.perso1->pv -= perso1->s3.degat;
        printf("%s touché.\nPoint de vie : %i\n", j2.perso1->nom, j2.perso1->pv);
    }
}

/*
 * Fonction qui effectue un sort d'un rayon "portee" autour du personnage
 * paramètre t_personnage * j1: personnage qui attaque
 * paramètre t_joueur j2: personnage qui subit les dégats
 */
void petit_coup(char map[N][N],t_personnage * j1,t_joueur j2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist=j1->s3.portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = j1->coord.y;
	j = j1->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					//verifie si il y a un obstacle ou un joueur à l'emplacement
					if(point[i][j] == '.'){
						point[i][j] = 'A' + car;
						car++;
					}
				}
			}
		}
	}

	dist=j1->s3.portee;
	g = j1->coord.y;
	j = j1->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != j1->coord.y){
								point[g][j] = 'A' + car;
								car ++;
						}
					}
				}
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage j1*/
	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
	if((map[y][x] == '4') || (map[y][x] == '3')){ /* si ce sont les personnages 2 des joueurs 1 ou 2* qui sont touchés */
        j2.perso2->pv -= j1->s3.degat;
		printf("%s touché.\nPoint de vie : %i\n", j2.perso2->nom, j2.perso2->pv);
	}
    else if((map[y][x] == '2') || (map[y][x] == '1')){
        j2.perso1->pv -= j1->s3.degat;
        printf("%s touché.\nPoint de vie : %i\n", j2.perso1->nom, j2.perso1->pv);
    }
}


/*************************************************************
*										Sorts de l'archer												 *
*************************************************************/


/*
 * Fonction qui effectue une coup en diagonale dans les 4 directions par rapport à la position actuel du perso1
 * sur une distance "portee"
 * paramètre t_personnage * j1: personnage qui attaque
 * paramètre t_joueur j2: personnage qui subit les dégats
 */

void diago(char map[N][N], t_personnage * perso1, t_joueur j2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;
/*copie plan jeu dans la matrice point*/

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = perso1->coord.y + 1;
	j = perso1->coord.x + 1;


	int nb = 0;
	int car = 0;
	//printf("%i\n", perso1.s1.portee);

	for(; (i < N && j < N) && nb < perso1->s1.portee && point[i][j] == '.'; i++, j++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x - 1;
	nb = 0;

	for(; (i >= 0  && j >= 0) && nb < perso1->s1.portee && point[i][j] == '.'; i--, j--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; (i >= 0  && j < N) && nb < perso1->s1.portee && point[i][j] == '.'; i--, j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y + 1;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; (i < N  && j >= 0) && nb < perso1->s1.portee && point[i][j] == '.'; i++, j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
    if((map[y][x] == '4') || (map[y][x] == '3')){ /* si ce sont les personnages 2 des joueurs 1 ou 2* qui sont touchés */
        j2.perso2->pv -= perso1->s3.degat;
		printf("%s touché.\nPoint de vie : %i\n", j2.perso2->nom, j2.perso2->pv);
	}
    else if((map[y][x] == '2') || (map[y][x] == '1')){
        j2.perso1->pv -= perso1->s3.degat;
        printf("%s touché.\nPoint de vie : %i\n", j2.perso1->nom, j2.perso1->pv);
    }
}

 /*
  * Fonction qui effectue une coup en ligne dans les 4 directions par rapport à la position actuel du perso1
  * sur une distance "portee"
  * paramètre t_personnage * j1: personnage qui attaque
  * paramètre t_joueur j2: personnage qui subit les dégats
  */
void ligne(char map[N][N], t_personnage * perso1, t_joueur j2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;
    /*copie plan jeu dans la matrice point*/

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = perso1->coord.y + 1;
	j = perso1->coord.x ;


	int nb = 0;
	int car = 0;

	for(; i < N && nb < perso1->s2.portee && point[i][j] == '.'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x;
	nb = 0;

	for(; i >= 0  && nb < perso1->s2.portee && point[i][j] == '.'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; j < N && nb < perso1->s2.portee && point[i][j] == '.'; j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < perso1->s2.portee && point[i][j] == '.'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
    if((map[y][x] == '4') || (map[y][x] == '3')){ /* si ce sont les personnages 2 des joueurs 1 ou 2* qui sont touchés */
        j2.perso2->pv -= perso1->s3.degat;
		printf("%s touché.\nPoint de vie : %i\n", j2.perso2->nom, j2.perso2->pv);
	}
    else if((map[y][x] == '2') || (map[y][x] == '1')){
        j2.perso1->pv -= perso1->s3.degat;
        printf("%s touché.\nPoint de vie : %i\n", j2.perso1->nom, j2.perso1->pv);
    }
}

/*
 * Fonction qui effectue un sort d'un rayon "portee" autour du personnage
 * paramètre t_personnage * j1: personnage qui attaque
 * paramètre t_joueur j2: personnage qui subit les dégats
 */
void double_tape(char map[N][N],t_personnage * j1, t_joueur j2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist=j1->s3.portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = j1->coord.y;
	j = j1->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] == '.'){
						point[i][j] = 'A' + car;
						car++;
					}
				}
			}
		}
	}

	dist=j1->s3.portee;
	g = j1->coord.y;
	j = j1->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != j1->coord.y){
								point[g][j] = 'A' + car;
								car ++;
								if( ('A' + car )== 'o')
									car++;
						}
					}
				}
			}
		}
	}

	/* affichage */
	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
	if((map[y][x] == '4') || (map[y][x] == '3')){ /* si ce sont les personnages 2 des joueurs 1 ou 2* qui sont touchés */
        j2.perso2->pv -= j1->s3.degat;
		printf("%s touché.\nPoint de vie : %i\n", j2.perso2->nom, j2.perso2->pv);
	}
    else if((map[y][x] == '2') || (map[y][x] == '1')){
        j2.perso1->pv -= j1->s3.degat;
        printf("%s touché.\nPoint de vie : %i\n", j2.perso1->nom, j2.perso1->pv);
    }
}


void coup_zone(char map[N][N],t_personnage * j1, t_joueur j2){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist=j1->s4.portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = j1->coord.y;
	j = j1->coord.x - dist ;
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					//verifie si il y a un obstacle ou un joueur à l'emplacement
					if(point[i][j] == '.' ){
							point[i][j] = 'A' + car;
							car++;
						}
					}
				}
			}
		}

	dist=j1->s4.portee;
	g = j1->coord.y;
	j = j1->coord.x - dist ;
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != j1->coord.y){
								point[g][j] = 'A' + car;
								car ++;
								if( ('A' + car) == 'o')
									car++;
						}
					}
				}
			}
		}
	}
	/* affichage */
	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

	//printf("x = %i y = %i\n", x, y);
  //vérifie si il y a des personnages dans la croix de largeur 'l' si oui leurs infliges les dégats
	int l=1;
	//ligne horizontale
	for(i=y,j=x-l;j!=x+(l+1);j++){
        if((point[i][j] == '4') || (point[i][j] == '3')){ /* si ce sont les personnages 2 des joueurs 1 ou 2* qui sont touchés */
            j2.perso2->pv -= j1->s3.degat;
    		printf("%s touché.\nPoint de vie : %i\n", j2.perso2->nom, j2.perso2->pv);
    	}
        else if((point[i][j] == '2') || (point[i][j] == '1')){
            j2.perso1->pv -= j1->s3.degat;
            printf("%s touché.\nPoint de vie : %i\n", j2.perso1->nom, j2.perso1->pv);
        }
	}

	//ligne verticale
	for(i=y-l,j=x;i!=y+(l+1);i+2){
        if((point[i][j] == '4') || (point[i][j] == '3')){ /* si ce sont les personnages 2 des joueurs 1 ou 2* qui sont touchés */
            j2.perso2->pv -= j1->s3.degat;
    		printf("%s touché.\nPoint de vie : %i\n", j2.perso2->nom, j2.perso2->pv);
    	}
        else if((point[i][j] == '2') || (point[i][j] == '1')){
            j2.perso1->pv -= j1->s3.degat;
            printf("%s touché.\nPoint de vie : %i\n", j2.perso1->nom, j2.perso1->pv);
        }
	}
}
