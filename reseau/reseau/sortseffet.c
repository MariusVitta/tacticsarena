#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

/**
 *\file sortseffet.c
 *\brief fonction de création de sorts
 *\author Dylan
 *\version 0.1
 *\date 28/02/2019
*/

/**
*\fn void armure(char map[N][N], t_personnage * p, t_joueur j,int numj)
*\brief sort armure
*\param matriceJeu[N][N] matrice qui sert au tour du jeu
*\param p personnage sur lequel on effectue le sort
*\return void
*/
void armure(char map[N][N], t_personnage * p, t_joueur j,int numj){
  creer_effet(p,1,p->coord.x,p->coord.y);
}

/**
*\fn void felin(char map[N][N], t_personnage * p, t_joueur j,int numj)
*\brief sort felin
*\param matriceJeu[N][N] matrice qui sert au tour du jeu
*\param p personnage sur lequel on effectue le sort
*\return void
*/

void felin(char map[N][N], t_personnage * p, t_joueur j,int numj){
  creer_effet(p,4,p->coord.x,p->coord.y);
}

/**
*\fn void armure(char map[N][N], t_personnage * p, t_joueur j,int numj)
*\brief sort chouette
*\param matriceJeu[N][N] matrice qui sert au tour du jeu
*\param p personnage sur lequel on effectue le sort
*\return void
*/
void chouette(char map[N][N], t_personnage * p, t_joueur j,int numj){
  creer_effet(p,5 ,p->coord.x,p->coord.y);
}
