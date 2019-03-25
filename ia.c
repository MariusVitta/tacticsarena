#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


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

int joueur (t_personnage *j1,t_personnage *j2, score){

  int


}





  if(!(strcmp("Guerrier",j1->nom))){
  switch(choix){
      case 1:
          if (j1->s1.point_action <= point_action  ) {
              saut(j1,j2,map,nb_j);point_action -= j1->s1.point_action ;
          }
          else{
              printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
          }
          break;
      case 2:
          if (j1->s2.point_action <= point_action ) {
              soin(j1);point_action -= j1->s2.point_action ;
          }
          else{
              printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");
          }
          break;
      case 3:
          if (j1->s3.point_action <= point_action  ) {
              petit_coup(map,j1,j2);point_action -= j1->s3.point_action ;

          }
          else{
              printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");

          }
          break;
      case 4:
          if (j1->s4.point_action <= point_action  ) {
              grosCoup(map,j1,j2);point_action -= j1->s4.point_action ;

          }
          else{
              printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");

          }
          break;
      }

  }
  else if(!(strcmp("Archer",j1->nom))){
  switch(choix){
      case 1:
          if (j1->s1.point_action <= point_action  ) {
              diago(map,j1,j2);
              point_action -= j1->s1.point_action ;

          }
          else{
              printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");

          }
          break;
      case 2:
          if (j1->s2.point_action <=  point_action) {
              ligne(map,j1,j2);point_action -= j1->s2.point_action ;

          }
          else{
              printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");

          }
          break;
      case 3:
          if (j1->s3.point_action <=  point_action) {
              double_tape(map,j1,j2);point_action -= j1->s3.point_action ;

          }
          else{
              printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");

          }
          break;
      case 4:
          if (j1->s4.point_action <= point_action) {

              coup_zone(map,j1,j2);point_action -= j1->s4.point_action ;
          }
          else{
              printf(" ---- Vous n'avez pas assez de points d'actions ----\n\n");

          }
          break;
  }

  }
  }
  else{
  printf("\n ---- Vous avez utilisé tous vos points d'actions ----\n\n");break;
}
