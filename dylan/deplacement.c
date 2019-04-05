#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "fonc.h"



/* Fonction permettant de deplacer son personnage et changer ses coordonnées
 * paramètre j1 : equipe que l'on souhaite déplacer
 * paramètre map
 * retourne : 1 si le déplacement a bien eu lieu
 */



/*avec personnage n le nombre de deplacements qu'il reste et numj le numero du equipe*/
int deplacement(t_equipe * j1,t_equipe * j2,char map[N][N],int  pm ,int nump){
    t_personnage * temp;
    int i = 0,compteur,j,test=0;


    if(nump == 1 ){
        temp = j1->perso1;
    }
    else{
        temp = j1->perso2;
    }

    char c;

    do{
        printf("Choisissez l'initial entre haut, bas, gauche, ou droite pour vous déplacer ou R pour rester sur place\n");

        scanf(" %c",&c);
    }
    while(c != 'h' && c != 'b' && c != 'g' && c != 'd' && c != 'R');

  		switch (c) {
  			case 'h':

  				if(temp->coord.y-1<0 || (map[temp->coord.y-1][temp->coord.x]!='.')){
    				printf(" ---- Déplacement impossible ---- \n" );
  					break;
  				}
  				else{
  					(temp->coord.y)--;
    				printf(" ---- Déplacement en Haut ---- \n" );
  					pm--;
  					break;
  				}

  			case 'b':

  				if(temp->coord.y+1>=N || (map[temp->coord.y+1][temp->coord.x]!='.')){
    				printf(" ---- Déplacement impossible ---- \n" );
  					break;
  				}

  				else{
  					(temp->coord.y)++;
    				printf(" ---- Déplacement en Bas ---- \n" );
  					pm--;
  					break;
  				}

  			case 'g':

  				if(temp->coord.x-1<0 || (map[temp->coord.y][temp->coord.x-1]!='.')){
    				printf(" ---- Déplacement impossible ---- \n" );
  					break;
  				}

  				else{
  					(temp->coord.x)--;
    				printf(" ---- Déplacement à Gauche ---- \n" );
  					pm--;
  					break;
  				}

  			case 'd':

  				if(temp->coord.x+1>=N || (map[temp->coord.y][temp->coord.x+1]!='.')){
    				printf(" ---- Déplacement impossible ---- \n" );
  					break;
  				}

  				else{
  					(temp->coord.x)++;
    				printf(" ---- Déplacement à Droite ---- \n" );
  					pm--;
  					break;
  				}

  			case 'R':

  				return pm;
  		}

  maj(map,j1,j2);
  affichage_map(map);

	return pm;
}
