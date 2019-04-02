#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonc.h"



//tous les sorts



/*************************************************************
*										Sorts du guerrier												 *
*************************************************************/

void saut (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

 char point[N][N];/*matrice affichant les possibilités de jeu*/
 int i, j, g,dist = portee,car=0;
 char choix;

 /* recopie matrice dans la matrice point qui affiche la portee */

 for(i = 0; i < N; i++){
   for(j = 0; j < N; j++){
     point[i][j] = map[i][j];
   }
 }

 dist = portee;

 i = perso1->coord.y;
 j = perso1->coord.x - dist ;
 //affiche la porter vers le haut
 for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
   j = perso1->coord.x - dist ;
   for( ;(j <= perso1->coord.x + dist) ; j++){
     if(j>=0){
       if(j<N){
         //verifie si il y a un obstacle ou un joueur à l'emplacement
         if(point[i][j] == '.'){
           point[i][j] = 'A' + car;
           car++;
           if('A' + car == 'o')
             car++;
         }
       }
     }
   }
 }

 dist=portee;

 g = perso1->coord.y;
 j = perso1->coord.x - dist ;
 //affiche la porter vers le bas
 for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
   j = perso1->coord.x - dist ;
   for( ;(j <= perso1->coord.x + dist) ; j++){
     if(j>=0){
       if(j<N){
         if(point[g][j] == '.'){
           //ne pas repasser une seconde fois sur la ligne du joueur
           if(g != perso1->coord.y){
               point[g][j] = 'A' + car;
               car ++;
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
     printf("Où souhaitez vous sauter : ");
     scanf(" %c", &choix);
 }while((!existe(point, choix, &x, &y)) || (((abs(perso1->coord.x-x)+abs(perso1->coord.y-y))>3) || (x<0 || x>=N) || (y<0 || y>=N)) || (map[y][x]!='.'));


 perso1->coord.x = x;

 perso1->coord.y = y;



 if(j1->numJoueur == 1){
   maj(map,j1,j2);
   affichage_map(map);
 }
 else{
   maj(map,j2,j1);
   affichage_map(map);
 }

}


/*
 * Fonction qui regarde la vie au personnage perso1
 * paramètre perso1: personnage1 que l'on souhaite soigner
 */
void soin (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){
  printf("Le guerrier a %d points de vie\n",perso1->pv);
  if(perso1->pv+degat <= perso1->pv_max)
    perso1->pv += degat;
  else
    perso1->pv = perso1->pv_max;

  printf("Le guerrier se soigne de %d et a maintenant %d points de vie sur %d\n",degat,perso1->pv,perso1->pv_max);
}

/*
 * Fonction qui effectue un sort d'un rayon "portee" autour du personnage
 * paramètre t_personnage * perso1: personnage qui attaque
 * paramètre t_joueur j2: personnage qui subit les dégats
 */
void petit_coup (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist=portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
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

	dist=portee;
	g = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != perso1->coord.y){
								point[g][j] = 'A' + car;
								car ++;
						}
					}
				}
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
		if(j1->numJoueur==1){
			switch (map[y][x]){

				case '2' :
						j2->perso1->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

			 	case '4' :
						j2->perso2->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
			  	break;
			}
		}

		if(j1->numJoueur==2){
			switch (map[y][x]){

				case '1' :
						j2->perso1->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

				case '3' :
						j2->perso2->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
				 	break;
			}
		}
}



/*
 * Fonction qui effectue un coup une case autour du personnage
 * sur une distance "portee"
 * paramètre t_personnage * perso1: personnage qui attaque
 * paramètre t_joueur j2: personnage qui subit les dégats
 */
void grosCoup (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

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

	for(; i < N && nb < portee && point[i][j] != 'o'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x;
	nb = 0;

	for(; i >= 0  && nb < portee && point[i][j] != 'o'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; j < N && nb < portee && point[i][j] != 'o'; j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < portee && point[i][j] != 'o'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));


	if(j1->numJoueur==1){
		switch (map[y][x]){

			case '2' :
					j2->perso1->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

		 	case '4' :
					j2->perso2->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		  	break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[y][x]){

			case '1' :
					j2->perso1->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

			case '3' :
					j2->perso2->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
			 	break;
		}
	}


}



/*************************************************************
*										Sorts de l'archer												 *
*************************************************************/


/*
 * Fonction qui effectue une coup en diagonale dans les 4 directions par rapport à la position actuel du perso1
 * sur une distance "portee"
 * paramètre t_personnage * perso1: personnage qui attaque
 * paramètre t_joueur j2: personnage qui subit les dégats
 */

void diago (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

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

	for(; (i < N && j < N) && nb < portee && point[i][j] == '.'; i++, j++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x - 1;
	nb = 0;

	for(; (i >= 0  && j >= 0) && nb < portee && point[i][j] == '.'; i--, j--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; (i >= 0  && j < N) && nb < portee && point[i][j] == '.'; i--, j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y + 1;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; (i < N  && j >= 0) && nb < portee && point[i][j] == '.'; i++, j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
		if(j1->numJoueur==1){
			switch (map[y][x]){

				case '2' :
						j2->perso1->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

			 	case '4' :
						j2->perso2->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
			  	break;
			}
		}

		if(j1->numJoueur==2){
			switch (map[y][x]){

				case '1' :
						j2->perso1->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

				case '3' :
						j2->perso2->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
				 	break;
			}
		}
}

 /*
  * Fonction qui effectue une coup en ligne dans les 4 directions par rapport à la position actuel du perso1
  * sur une distance "portee"
  * paramètre t_personnage * perso1: personnage qui attaque
  * paramètre t_joueur j2: personnage qui subit les dégats
  */
void ligne (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

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

	for(; i < N && nb < portee && point[i][j] == '.'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x;
	nb = 0;

	for(; i >= 0  && nb < portee && point[i][j] == '.'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; j < N && nb < portee && point[i][j] == '.'; j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < portee && point[i][j] == '.'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
		if(j1->numJoueur == 1){
			switch (map[y][x]){

				case '2' :
						j2->perso1->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

			 	case '4' :
						j2->perso2->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
			  	break;
			}
		}

		if(j1->numJoueur == 2){
			switch (map[y][x]){

				case '1' :
						j2->perso1->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

				case '3' :
						j2->perso2->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
				 	break;
			}
		}
}

/*
 * Fonction qui effectue un sort d'un rayon "portee" autour du personnage
 * paramètre t_personnage * perso1: personnage qui attaque
 * paramètre t_joueur j2: personnage qui subit les dégats
 */
void double_tape (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist = portee,car = 0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
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

	dist = portee;
	g = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != perso1->coord.y){
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
	if(j1->numJoueur==1){
		switch (map[y][x]){

			case '2' :
					j2->perso1->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

		 	case '4' :
					j2->perso2->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		  	break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[y][x]){

			case '1' :
					j2->perso1->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

			case '3' :
					j2->perso2->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
			 	break;
		}
  }
}


void coup_zone (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist = portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
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

	dist = portee;
	g = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != perso1->coord.y){
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
		if(j1->numJoueur==1){
			switch (map[i][j]){

				case '2' :
						j2->perso1->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

				case '4' :
						j2->perso2->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
					break;
			}
		}

		if(j1->numJoueur==2){
			switch (map[i][j]){

				case '1' :
						j2->perso1->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

				case '3' :
						j2->perso2->pv -= degat;
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
					break;
			}
		}
	}

	//ligne verticale
	for(i=y-l,j=x;i!=y+(l+1);i++){
		if(i!=y){
			if(j1->numJoueur==1){
				switch (map[i][j]){

					case '2' :
							j2->perso1->pv -= degat;
							printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
						break;

					case '4' :
							j2->perso2->pv -= degat;
							printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
						break;
				}
			}

			if(j1->numJoueur==2){
				switch (map[i][j]){

					case '1' :
							j2->perso1->pv -= degat;
							printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
						break;

					case '3' :
							j2->perso2->pv -= degat;
							printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
						break;
				}
			}
		}
	}
}

/*************************************************************
*										Sorts du Tank												     *
*************************************************************/

void armure (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){
  creer_effet(perso1,1,perso1->coord.x,perso1->coord.y);
}

void attire (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

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

	for(; i < N && nb < portee && point[i][j] == '.'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x;
	nb = 0;

	for(; i >= 0  && nb < portee && point[i][j] == '.'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; j < N && nb < portee && point[i][j] == '.'; j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < portee && point[i][j] == '.'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
		if(j1->numJoueur==1){
			switch (map[y][x]){

				case '2' :
          if(perso1->coord.y == j2->perso1->coord.y ){
            /* Si l'écart entre les 2 joueurs est de plus de 3 cases */
            if(abs(perso1->coord.x - j2->perso1->coord.x >= 3)){
              if(perso1->coord.x < j2->perso1->coord.x )
                  j2->perso1->coord.x -= 3;
              else if(perso1->coord.x > j2->perso1->coord.x )
                  j2->perso1->coord.x += 3;
            }
            /* Sinon l'attire a son corps à corps du nb de cases d'écart*/
            else{
              if(perso1->coord.x < j2->perso1->coord.x )
                j2->perso1->coord.x = perso1->coord.x + 1;
              else if(perso1->coord.x > j2->perso1->coord.x )
                j2->perso1->coord.x = perso1->coord.x - 1;
            }
          }
          else if(perso1->coord.y == j2->perso1->coord.y ){
      			/* Si l'écart entre les 2 joueurs est de plus de 3 cases */
            if(abs(perso1->coord.y - j2->perso1->coord.y >= 3)){
              if(perso1->coord.y < j2->perso1->coord.y )
                  j2->perso1->coord.y -= 3;
              else if(perso1->coord.y > j2->perso1->coord.y )
                  j2->perso1->coord.y += 3;
            }
            /* Sinon l'attire a son corps à corps du nb de cases d'écart*/
            else{
              if(perso1->coord.y < j2->perso1->coord.y )
                j2->perso1->coord.y = perso1->coord.y + 1;
              else if(perso1->coord.y > j2->perso1->coord.y )
                j2->perso1->coord.y = perso1->coord.y - 1;
            }
      		}
					break;

			 	case '4' :
          if(perso1->coord.y == j2->perso2->coord.y ){
            /* Si l'écart entre les 2 joueurs est de plus de 3 cases */
            if(abs(perso1->coord.x - j2->perso2->coord.x >= 3)){
              if(perso1->coord.x < j2->perso2->coord.x )
                  j2->perso2->coord.x -= 3;
              else if(perso1->coord.x > j2->perso2->coord.x )
                  j2->perso2->coord.x += 3;
            }
            /* Sinon l'attire a son corps à corps du nb de cases d'écart*/
            else{
              if(perso1->coord.x < j2->perso2->coord.x )
                j2->perso2->coord.x = perso1->coord.x + 1;
              else if(perso1->coord.x > j2->perso2->coord.x )
                j2->perso2->coord.x = perso1->coord.x - 1;
            }
          }
          else if(perso1->coord.y == j2->perso2->coord.y ){
            /* Si l'écart entre les 2 joueurs est de plus de 3 cases */
            if(abs(perso1->coord.y - j2->perso2->coord.y >= 3)){
              if(perso1->coord.y < j2->perso2->coord.y )
                  j2->perso2->coord.y -= 3;
              else if(perso1->coord.y > j2->perso2->coord.y )
                  j2->perso2->coord.y += 3;
            }
            /* Sinon l'attire a son corps à corps du nb de cases d'écart*/
            else{
              if(perso1->coord.y < j2->perso2->coord.y )
                j2->perso2->coord.y = perso1->coord.y + 1;
              else if(perso1->coord.y > j2->perso2->coord.y )
                j2->perso2->coord.y = perso1->coord.y - 1;
            }
          }
        break;
			}
	  }

		if(j1->numJoueur==2){
			switch (map[y][x]){

        case '1' :
          if(perso1->coord.y == j2->perso1->coord.y ){
            /* Si l'écart entre les 2 joueurs est de plus de 3 cases */
            if(abs(perso1->coord.x - j2->perso1->coord.x >= 3)){
              if(perso1->coord.x < j2->perso1->coord.x )
                  j2->perso1->coord.x -= 3;
              else if(perso1->coord.x > j2->perso1->coord.x )
                  j2->perso1->coord.x += 3;
            }
            /* Sinon l'attire a son corps à corps du nb de cases d'écart*/
            else{
              if(perso1->coord.x < j2->perso1->coord.x )
                j2->perso1->coord.x = perso1->coord.x + 1;
              else if(perso1->coord.x > j2->perso1->coord.x )
                j2->perso1->coord.x = perso1->coord.x - 1;
            }
          }
          else if(perso1->coord.y == j2->perso1->coord.y ){
      			/* Si l'écart entre les 2 joueurs est de plus de 3 cases */
            if(abs(perso1->coord.y - j2->perso1->coord.y >= 3)){
              if(perso1->coord.y < j2->perso1->coord.y )
                  j2->perso1->coord.y -= 3;
              else if(perso1->coord.y > j2->perso1->coord.y )
                  j2->perso1->coord.y += 3;
            }
            /* Sinon l'attire a son corps à corps du nb de cases d'écart*/
            else{
              if(perso1->coord.y < j2->perso1->coord.y )
                j2->perso1->coord.y = perso1->coord.y + 1;
              else if(perso1->coord.y > j2->perso1->coord.y )
                j2->perso1->coord.y = perso1->coord.y - 1;
            }
      		}
					break;

			 	case '3' :
          if(perso1->coord.y == j2->perso2->coord.y ){
            /* Si l'écart entre les 2 joueurs est de plus de 3 cases */
            if(abs(perso1->coord.x - j2->perso2->coord.x >= 3)){
              if(perso1->coord.x < j2->perso2->coord.x )
                  j2->perso2->coord.x -= 3;
              else if(perso1->coord.x > j2->perso2->coord.x )
                  j2->perso2->coord.x += 3;
            }
            /* Sinon l'attire a son corps à corps du nb de cases d'écart*/
            else{
              if(perso1->coord.x < j2->perso2->coord.x )
                j2->perso2->coord.x = perso1->coord.x + 1;
              else if(perso1->coord.x > j2->perso2->coord.x )
                j2->perso2->coord.x = perso1->coord.x - 1;
            }
          }
          else if(perso1->coord.y == j2->perso2->coord.y ){
            /* Si l'écart entre les 2 joueurs est de plus de 3 cases */
            if(abs(perso1->coord.y - j2->perso2->coord.y >= 3)){
              if(perso1->coord.y < j2->perso2->coord.y )
                  j2->perso2->coord.y -= 3;
              else if(perso1->coord.y > j2->perso2->coord.y )
                  j2->perso2->coord.y += 3;
            }
            /* Sinon l'attire a son corps à corps du nb de cases d'écart*/
            else{
              if(perso1->coord.y < j2->perso2->coord.y )
                j2->perso2->coord.y = perso1->coord.y + 1;
              else if(perso1->coord.y > j2->perso2->coord.y )
                j2->perso2->coord.y = perso1->coord.y - 1;
            }
          }
        break;
			}
		}
}

void chenchen (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist = portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
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

	dist = portee;
	g = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != perso1->coord.y){
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
	if(j1->numJoueur==1){
		switch (map[y][x]){

			case '2' :
					j2->perso1->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

		 	case '4' :
					j2->perso2->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		  	break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[y][x]){

			case '1' :
					j2->perso1->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

			case '3' :
					j2->perso2->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
			 	break;
		}
	}
}

void bigshaq (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;
	int degats[4]={8,16,32,128};
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

	for(; i < N && nb < portee && point[i][j] != 'o'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y - 1;
	j = perso1->coord.x;
	nb = 0;

	for(; i >= 0  && nb < portee && point[i][j] != 'o'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = perso1->coord.y;
	j = perso1->coord.x + 1;
	nb = 0;

	for(; j < N && nb < portee && point[i][j] != 'o'; j++, nb++, car++)
		point[i][j] = 'A' + car;

		i = perso1->coord.y;
		j = perso1->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < portee && point[i][j] != 'o'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	affichage_map(point);

	int x = 0, y = 0;
  do{
			printf("Où souhaitez vous taper : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

    //réduction des points de vies après le coup
	if(j1->numJoueur==1){
		switch (map[y][x]){

			case '2' :
        if(perso1->pv > 50)
          j2->perso1->pv -= degats[0];
        else if(perso1->pv > 25)
          j2->perso1->pv -= degats[1];
        else if(perso1->pv > 2)
          j2->perso1->pv -= degats[2];
        else if(perso1->pv == 1)
          j2->perso1->pv -= degats[3];
        printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

		 	case '4' :
        if(perso1->pv > 50)
          j2->perso2->pv -= degats[0];
        else if(perso1->pv > 25)
          j2->perso2->pv -= degats[1];
        else if(perso1->pv > 2)
          j2->perso2->pv -= degats[2];
        else if(perso1->pv == 1)
          j2->perso2->pv -= degats[3];
        printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
        break;
      }
	}

  if(j1->numJoueur==2){
  	switch (map[y][x]){

      case '1' :
        if(perso1->pv > 50)
          j2->perso1->pv -= degats[0];
        else if(perso1->pv > 25)
          j2->perso1->pv -= degats[1];
        else if(perso1->pv > 2)
          j2->perso1->pv -= degats[2];
        else if(perso1->pv == 1)
          j2->perso1->pv -= degats[3];
        printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
  			break;

  	 	case '3' :
        if(perso1->pv > 50)
          j2->perso2->pv -= degats[0];
        else if(perso1->pv > 25)
          j2->perso2->pv -= degats[1];
        else if(perso1->pv > 2)
          j2->perso2->pv -= degats[2];
        else if(perso1->pv == 1)
          j2->perso2->pv -= degats[3];
        printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
        break;
    }
	}
}



void felin (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){
  creer_effet(perso1,4,perso1->coord.x,perso1->coord.y);
}

void chouette (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){
  creer_effet(perso1,5,perso1->coord.x,perso1->coord.y);
}

void fuego (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist = portee,car=0;
	char choix;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
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

	dist=portee;
	g = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != perso1->coord.y){
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

	if(j1->numJoueur==2){
		switch (map[y][x]){

			case '1' :
					j2->perso1->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

			case '3' :
					j2->perso2->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
				break;
		}
	}

	else if(j1->numJoueur==1){
		switch (map[y][x]){

			case '2' :
					j2->perso1->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

			case '4' :
					j2->perso2->pv -= degat;
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
				break;
		}
	}
}

void revitalisation (char map[N][N], t_personnage * perso1,t_joueur * j2, t_joueur * j1,int nump,int degat,int portee){

  char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist = portee,car=0;
	char choix;


	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
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

  dist = portee;
	g = perso1->coord.y;
	j = perso1->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = perso1->coord.x - dist ;
		for( ;(j <= perso1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != perso1->coord.y){
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
			printf("Où souhaitez vous soigner : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

  if(j1->numJoueur==2){
    switch (map[y][x]){

      case '2' :
          j2->perso1->pv += degat;
          printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
        break;

      case '4' :
          j2->perso2->pv += degat;
          printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
        break;
    }
  }

  else if(j1->numJoueur==1){
    switch (map[y][x]){

      case '1' :
          j2->perso1->pv += degat;
          printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
        break;

      case '3' :
          j2->perso2->pv += degat;
          printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
        break;
    }
  }
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
