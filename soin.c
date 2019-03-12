#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


void soin(t_personnage * j1) {
  printf("Le guerrier a %d points de vie\n",j1->pv);
  if(j1->pv+j1->s2.degat<=60)
    j1->pv+=j1->s2.degat;
  else
    j1->pv=60;

  printf("Le guerrier se soigne de %d et a maintenant %d points de vie\n",j1->s2.degat,j1->pv);
}
