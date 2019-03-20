#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


void armure(t_personnage *p){

  creer_effet(p,1,p->coord.x,p->coord.y);

}

void felin(t_personnage *p){
  creer_effet(p,4,p->coord.x,p->coord.y);
}

void chouette(t_personnage *p){
  creer_effet(p,5 ,p->coord.x,p->coord.y);
}
