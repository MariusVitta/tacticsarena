#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

void creer_effet(t_personnage * p,int effet_voulu,int x,int y){


  switch(effet_voulu){
    case (1):
        p->effets.e1.nom = "armure";
        p->effets.e1.duree = 1;
        p->effets.e1.cible.x = x;
        p->effets.e1.cible.y = y;
      break;
    case (2):
        p->effets.e2.nom = "invincibilite";
        p->effets.e2.duree = 1;
        p->effets.e2.cible.x = x;
        p->effets.e2.cible.y = y;
      break;
    case (3):
        p->effets.e3.nom = "degat double";
        p->effets.e3.duree = 1;
        p->effets.e3.cible.x = x;
        p->effets.e3.cible.y = y;
      break;
    case (4):
        p->effets.e4.nom = "felin";
        p->effets.e4.duree = 100;
        p->effets.e4.cible.x = x;
        p->effets.e4.cible.y = y;
      break;
    case (5):
        p->effets.e4.nom = "chouette";
        p->effets.e4.duree = 100;
        p->effets.e4.cible.x = x;
        p->effets.e4.cible.y = y;
      break;

    case (7):
        p->effets.e1.nom = "vide";
        p->effets.e1.duree = 100;
        p->effets.e1.cible.x = x;
        p->effets.e1.cible.y = y;

        p->effets.e2.nom = "vide";
        p->effets.e2.duree = 100;
        p->effets.e2.cible.x = x;
        p->effets.e2.cible.y = y;

        p->effets.e3.nom = "vide";
        p->effets.e3.duree = 100;
        p->effets.e3.cible.x = x;
        p->effets.e3.cible.y = y;

      break;
  }
