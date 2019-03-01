#include <stdio.h>
#include <stdlib.h>
#include "fonc.h" 

int est_mort(t_personnage perso){
	return (perso.pv <= 0);
}

