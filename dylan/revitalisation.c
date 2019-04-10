/**
 *\file revitalisation.c
 *\brief fonction revitalisation
 *\author Dylan
 *\version 0.1
 *\date 28/02/2019
*/

void revitalisation(char map[N][N],t_personnage * j1, t_joueur j1) {

  char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g, dist=j1->s4.portee,car=0;
	char choix;
  int numj=j1;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = j1->coord.y;
	j = j1->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] == '.'){
						point[i][j] = 'A' + car;
						car++;
					}
				}
			}
		}
	}

  dist=j1->s4.portee;
	g = j1->coord.y;
	j = j1->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = j1->coord.x - dist ;
		for( ;(j <= j1->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != j1->coord.y){
								point[g][j] = 'A' + car;
								car ++;
								if( ('A' + car )== 'o')
									car++;
						}
					}
				}
			}
		}
	}

  /* affichage */
	affichage_map(point);

	int x = 0, y = 0;
	do{
			printf("Où souhaitez vous soigner : ");
			scanf(" %c", &choix);
	}while(!existe(point, choix, &x, &y));

  if(numj==2){
    switch (map[y][x]){

      case '2' :
          j2.perso1->pv += perso1->s4.degat;
          printf("%s touché.\nPoint de vie : %i\n", j2.perso1->nom, j2.perso1->pv);
        break;

      case '4' :
          j2.perso2->pv += perso1->s4.degat;
          printf("%s touché.\nPoint de vie : %i\n", j2.perso2->nom, j2.perso2->pv);
        break;
    }
  }

  else if(numj==1){
    switch (map[y][x]){

      case '1' :
          j1.perso1->pv += perso1->s4.degat;
          printf("%s touché.\nPoint de vie : %i\n", j1.perso1->nom, j1.perso1->pv);
        break;

      case '3' :
          j1.perso2->pv += perso1->s4.degat;
          printf("%s touché.\nPoint de vie : %i\n", j1.perso2->nom, j1.perso2->pv);
        break;
    }
  }
}
