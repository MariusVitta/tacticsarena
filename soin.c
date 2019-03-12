#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"


void soin(t_personnage * j1) {
  printf("Le guerrier a %d points de vie\n",j1.s1.pv);
  j1.s1.pv-=j1.s1.degat;
  printf("Le guerrier se soigne de %d et a maintenant %d points de vie\n",j1.s1.pv);
}
