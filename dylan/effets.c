#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

void creer_effet(t_personnage * p,int effet_voulu,int x,int y){


  switch(effet_voulu){
    case (1):
        p->effets[0].nom = "armure";
        p->effets[0].duree = 1;
        p->effets[0].cible.x = x;
        p->effets[0].cible.y = y;
      break;
    case (2):
        p->effets[1].nom = "felin";
        p->effets[1].duree = 100;
        p->effets[1].cible.x = x;
        p->effets[1].cible.y = y;
      break;
    case (3):
        p->effets[1].nom = "chouette";
        p->effets[1].duree = 100;
        p->effets[1].cible.x = x;
        p->effets[1].cible.y = y;
      break;

    case (6):
        p->effets[0].nom = "vide";
        p->effets[0].duree = 100;
        p->effets[0].cible.x = x;
        p->effets[0].cible.y = y;

        p->effets[1].nom = "vide";
        p->effets[1].duree = 100;
        p->effets[1].cible.x = x;
        p->effets[1].cible.y = y;

      break;
  }
}
