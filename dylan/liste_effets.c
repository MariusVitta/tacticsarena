#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

/**
 *\file liste_effets.c
 *\brief fonction sur les effets
 *\author Dylan
 *\version 0.1
 *\date 28/02/2019
*/

/**
*\fn void creer_effet (int effet,t_personnage * perso)
*\brief création d'un effet
*\param effet numéro de l'effet
*\param perso personnage sur lequel on effectue l'effet
*\return void
*/
creer_effet (int effet,t_personnage * perso){

  switch (effet) {
    case 1:


      break;

    case 7:
      eff effet_actuel;

      char * liste {effet1;effet2;effet3;effet4};

    }


/**
*\fn int armure(t_personnage * j)
*\brief création d'une armure sur un personnage
*\param j personnage sur lequel on effectue l'armure prendra effet
*\return int
*/
int armure(t_personnage * j){

  j->liste_effet.effet1.nom='reduction de degat';
  j->liste_effet.effet1.cible=j;
  j->liste_effet.effet1.duree=1;
}


/**
*\fn int damage_nul()
*\brief degat nul
*\return int
*/
int damage_nul(){
}


/**
*\fn int forme(t_effet )
*\brief forme prise
*\return int
*/
int forme(t_effet ){
}
