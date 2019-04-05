#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


void armure(char map[N][N], t_personnage * p, t_joueur j,int numj){
  creer_effet(p,1,p->coord.x,p->coord.y);
}

void felin(char map[N][N], t_personnage * p, t_joueur j,int numj){
  creer_effet(p,4,p->coord.x,p->coord.y);
}

void chouette(char map[N][N], t_personnage * p, t_joueur j,int numj){
  creer_effet(p,5 ,p->coord.x,p->coord.y);
}
