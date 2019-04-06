#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

/**
 *\file effets.c
 *\brief programme d'initialisation du jeu
 *\author Dylan
 *\version 0.1
 *\date 28/02/2019
*/

/**
 *\fn void creer_effet(t_personnage * p,int effet_voulu,int x,int y)
 *\brief fonction qui crée un effet
 *\param p personnage dont on veut créer l'effet
 *\param effet_voulu effet que l'on souhaite appliquer sur le personnage p
 *\param x coordonnees du personnages sur lequel l'effet sera effectué
 *\param y coordonnees du personnages sur lequel l'effet sera effectué
 *\return void
 */
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
}
