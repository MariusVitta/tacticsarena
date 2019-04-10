#include "fonc.h"
#include "sdl_fonc.h"

/*************************************************************
*					              Sorts du guerrier		           			 *
*************************************************************/

int SDL_saut(t_joueur * j1,t_joueur * j2, int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g,car=0, coordi = 0, coordj = 0;
	char choix;

	t_personnage * temp;
  if(numero_perso == 1 )
      temp = j1->perso1;

  else
      temp = j1->perso2;

  int dist=temp->sorts[0]->portee;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					//verifie si il y a un obstacle ou un joueur à l'emplacement
					if(point[i][j] == '.'){
						point[i][j] = 'A' + car;
						car++;
						if('A' + car == 'o')
							car++;
					}
				}
			}
		}
	}

	dist=temp->sorts[0]->portee;
	g = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != temp->coord.y){
								point[g][j] = 'A' + car;
								car ++;
						}
					}
				}
			}
		}
	}

	/* affichage */
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

	temp->coord.x = coordj;
	temp->coord.y = coordi;

	if(j1->numJoueur==1){
		maj(map,j1,j2);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map, * j1, * j2);
		SDL_RenderPresent(renderer);
	}
	else{
		maj(map,j2,j1);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map, * j1, * j2);
		SDL_RenderPresent(renderer);
	}
	return 1;
}


void SDL_soin (t_joueur * j1, t_joueur * j2,int numero_perso){

  t_personnage * temp;
    if(numero_perso == 1 )
        temp = j1->perso1;
    else
        temp = j1->perso2;

  printf("Le guerrier a %d points de vie\n",temp->pv);

  if(temp->pv+temp->sorts[1]->degat <= temp->pv_max)
    temp->pv += temp->sorts[1]->degat;
  else
    temp->pv = temp->pv_max;

	effet_clignotement( * j1, * j2, temp);
	SDL_afficher_degat(* j1, * j2, temp, temp->sorts[1]->degat, 'p');

  printf("Le guerrier se soigne de %d et a maintenant %d points de vie sur %d\n",temp->sorts[1]->degat,temp->pv,temp->pv_max);
}

void SDL_petit_coup (t_joueur * j1, t_joueur * j2,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	char player;

	t_personnage * temp;
  if(numero_perso == 1 ){
    temp = j1->perso1;
    if(j1->numJoueur == 1 )
    	player ='1';
    else
    	player = '3';
  }

  else{
    temp = j1->perso2;
    if(j1->numJoueur == 1 )
      player ='2';
    else
      player = '4';
  }

	int i, j, g, dist = temp->sorts[2]->portee,car=0, coordi = 0, coordj = 0;
	char choix;

	printf("===== %c =========\n", player);

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					//verifie si il y a un obstacle ou un joueur à l'emplacement
					if(point[i][j] == '.'){
						point[i][j] = 'A' + car;
						car++;
					}
					else if(point[i][j] != player){
							switch(point[i][j]){
								case '1':
									point[i][j] = 'a';
								break;
								case '2':
									point[i][j] = 'b';
								break;
								case '3':
									point[i][j] = 'c';
								break;
								case '4':
									point[i][j] = 'd';
								break;
							}
					}
				}
			}
		}
	}

	dist=temp->sorts[2]->portee;
	g = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != temp->coord.y){
								point[g][j] = 'A' + car;
								car ++;
						}
					}
					else if(point[g][j] != player){
							switch(point[g][j]){
								case '1':
									point[g][j] = 'a';
								break;
								case '2':
									point[g][j] = 'b';
								break;
								case '3':
									point[g][j] = 'c';
								break;
								case '4':
									point[g][j] = 'd';
								break;
							}
					}
				}
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

  //réduction des points de vies après le coup
	if(j1->numJoueur==1){
		switch (map[coordi][coordj]){

			case '2' :
				j2->perso1->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);

			break;

			case '4' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
			 break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[coordi][coordj]){

			case '1' :
				j2->perso1->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
			break;

			case '3' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		 	break;
		}
	}
}

void SDL_grosCoup (t_joueur * j1, t_joueur * j2,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	char player;

	t_personnage * temp;

  	if(numero_perso == 1 ){
    	temp = j1->perso1;
    if(j1->numJoueur == 1 )
      	player ='1';
    else
		   	player = '3';
  	}

  	else{
    	temp = j1->perso2;
    	if(j1->numJoueur == 1 )
    	 	player ='2';
    	else
      		player = '4';
  	}

	int dist = temp->sorts[3]->portee, coordi = 0, coordj = 0;
	int i, j;
	char choix;

    /*copie plan jeu dans la matrice point*/
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = temp->coord.y + 1;
	j = temp->coord.x ;
	int nb = 0;
	int car = 0;

	for(; i < N && nb < dist && point[i][j] != 'o'; i++, nb++, car++){

		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y - 1;
	j = temp->coord.x;
	nb = 0;

	for(; i >= 0  && nb < dist && point[i][j] != 'o'; i--, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y;
	j = temp->coord.x + 1;
	nb = 0;

	for(; j < N && nb < dist && point[i][j] != 'o'; j++, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

		i = temp->coord.y;
		j = temp->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < dist && point[i][j] != 'o'; j--, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

  //réduction des points de vies après le coup
	if(j1->numJoueur==1){
		switch (map[coordi][coordj]){

			case '2' :
				j2->perso1->pv -= temp->sorts[3]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[3]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);

			break;

			case '4' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[3]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
			break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[coordi][coordj]){

			case '1' :
				j2->perso1->pv -= temp->sorts[3]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[3]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
			break;

			case '3' :
				j2->perso2->pv -= temp->sorts[3]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[3]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		 	break;
		}
	}
}

/*************************************************************
*					             Sorts de l'archer						         *
*************************************************************/

void SDL_diago (t_joueur * j1, t_joueur * j2,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;

	char player;

	t_personnage * temp;

  if(numero_perso == 1 ){
      temp = j1->perso1;
      if(j1->numJoueur == 1 )
      	player ='1';
      else
      	player = '3';
  }

  else{
      temp = j1->perso2;
      if(j1->numJoueur == 1 )
      	player ='2';
      else
      	player = '4';
  }

  int dist = temp->sorts[0]->portee, coordi = 0, coordj = 0;

/*copie plan jeu dans la matrice point*/

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = temp->coord.y + 1;
	j = temp->coord.x + 1;
	int nb = 0;
	int car = 0;
	//printf("%i\n", perso1.s1.portee);

	for(; (i < N && j < N) && nb < dist && point[i][j] != 'o'; i++, j++, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y - 1;
	j = temp->coord.x - 1;
	nb = 0;

	for(; (i >= 0  && j >= 0) && nb < dist && point[i][j] != 'o'; i--, j--, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y - 1;
	j = temp->coord.x + 1;
	nb = 0;

	for(; (i >= 0  && j < N) && nb < dist && point[i][j] != 'o'; i--, j++, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}


	i = temp->coord.y + 1;
	j = temp->coord.x - 1;
	nb = 0;

	for(; (i < N  && j >= 0) && nb < dist && point[i][j] != 'o'; i++, j--, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

  //réduction des points de vies après le coup
	if(j1->numJoueur==1){
		switch (map[coordi][coordj]){

			case '2' :
				j2->perso1->pv -= temp->sorts[0]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[0]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);

			break;

		 	case '4' :
				j2->perso2->pv -= temp->sorts[0]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[0]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
	  	break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[coordi][coordj]){

			case '1' :
				j2->perso1->pv -= temp->sorts[0]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[0]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
			break;

			case '3' :
				j2->perso2->pv -= temp->sorts[0]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[0]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		 	break;
		}
	}
}

void SDL_ligne (t_joueur * j1, t_joueur * j2,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j;
	char choix;

	char player;

	t_personnage * temp;

  if(numero_perso == 1 ){
      temp = j1->perso1;
      if(j1->numJoueur == 1 )
      	player ='1';
      else
      	player = '3';
  }

  else{
      temp = j1->perso2;
      if(j1->numJoueur == 1 )
      	player ='2';
      else
      	player = '4';
  }

  int dist = temp->sorts[1]->portee, coordi = 0, coordj = 0;
  /*copie plan jeu dans la matrice point*/

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = temp->coord.y + 1;
	j = temp->coord.x ;


	int nb = 0;
	int car = 0;

	for(; i < N && nb < dist && point[i][j] != 'o'; i++, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y - 1;
	j = temp->coord.x;
	nb = 0;

	for(; i >= 0  && nb < dist && point[i][j] != 'o'; i--, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y;
	j = temp->coord.x + 1;
	nb = 0;

	for(; j < N && nb < dist && point[i][j] != 'o'; j++, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y;
	j = temp->coord.x - 1;
	nb = 0;

	for(; j >= 0 && nb < dist && point[i][j] != 'o'; j--, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

  //réduction des points de vies après le coup
	if(j1->numJoueur==1){
		switch (map[coordi][coordj]){

			case '2' :
				j2->perso1->pv -= temp->sorts[1]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[1]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);

			break;

		 	case '4' :
				j2->perso2->pv -= temp->sorts[1]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[1]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
	  	break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[coordi][coordj]){

			case '1' :
				j2->perso1->pv -= temp->sorts[1]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[1]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
			break;

			case '3' :
				j2->perso2->pv -= temp->sorts[1]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[1]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		 	break;
		}
	}
}

void SDL_double_tape (t_joueur * j1, t_joueur * j2,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g;
	char choix, player;

	t_personnage * temp;
	if(numero_perso == 1 ){
        temp = j1->perso1;
        if(j1->numJoueur == 1 )
        	player ='1';
        else
        	player = '3';
  }

  else{
      temp = j1->perso2;
      if(j1->numJoueur == 1 )
      	player ='2';
      else
      	player = '4';
  }

  int dist = temp->sorts[2]->portee, coordi = 0, coordj = 0;
/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = temp->coord.y;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] == '.'){
						point[i][j] = 'A';
					}
					else if(point[i][j] != player){
						switch(point[i][j]){
							case '1':
								point[i][j] = 'a';
							break;
							case '2':
								point[i][j] = 'b';
							break;
							case '3':
								point[i][j] = 'c';
							break;
							case '4':
								point[i][j] = 'd';
							break;
						}
					}
				}
			}
		}
	}

	dist = temp->sorts[2]->portee;
	g = temp->coord.y;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(g != temp->coord.y){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(point[g][j] == '.'){
								point[g][j] = 'A';
						}
						else if(point[g][j] != player){
							switch(point[g][j]){
								case '1':
									point[g][j] = 'a';
								break;
								case '2':
									point[g][j] = 'b';
								break;
								case '3':
									point[g][j] = 'c';
								break;
								case '4':
									point[g][j] = 'd';
								break;
							}
						}
					}
				}
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

  //réduction des points de vies après le coup
	if(j1->numJoueur==1){
		switch (map[coordi][coordj]){

			case '2' :
				j2->perso1->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);

			break;

		 	case '4' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
	  	break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[coordi][coordj]){

			case '1' :
				j2->perso1->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
			break;

			case '3' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		 	break;
		}
	}
}

void SDL_coup_zone (t_joueur * j1, t_joueur * j2,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g;
	char choix, player;

	t_personnage * temp;
	if(numero_perso == 1 ){
        temp = j1->perso1;

        if(j1->numJoueur == 1 )
        	player ='1';
        else
        	player = '3';
  }

  else{
      temp = j1->perso2;
      if(j1->numJoueur == 1 )
      	player ='2';
      else
      	player = '4';
  }

  int dist = temp->sorts[3]->portee, coordi = 0, coordj = 0;
/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					//verifie si il y a un obstacle ou un joueur à l'emplacement
					if(point[i][j] == '.' ){
							point[i][j] = 'A';
					}
					else if(point[i][j] != player){
						switch(point[i][j]){
							case '1':
								point[i][j] = 'a';
							break;
							case '2':
								point[i][j] = 'b';
							break;
							case '3':
								point[i][j] = 'c';
							break;
							case '4':
								point[i][j] = 'd';
							break;
						}
					}
				}
			}
		}
	}

	dist = temp->sorts[3]->portee, coordi = 0, coordj = 0;
	g = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(g != temp->coord.y){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(point[g][j] == '.'){
								point[g][j] = 'A';
						}
						else if(point[g][j] != player){
							switch(point[g][j]){
								case '1':
									point[g][j] = 'a';
								break;
								case '2':
									point[g][j] = 'b';
								break;
								case '3':
									point[g][j] = 'c';
								break;
								case '4':
									point[g][j] = 'd';
								break;
							}
						}
					}
				}
			}
		}
	}
	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;
	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

	//printf("x = %i y = %i\n", x, y);
  //vérifie si il y a des personnages dans la croix de largeur 'l' si oui leurs infliges les dégats
	int l = 1;
	//ligne horizontale
	for(i = coordi, j = coordj-l; j <= coordj + l; j++){

		if(j1->numJoueur == 1){
			switch (map[i][j]){

				case '2' :
					j2->perso1->pv -= temp->sorts[3]->degat;
					effet_clignotement(* j1, * j2, j2->perso1);
					SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[3]->degat, 'n');
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

				case '4' :
					j2->perso2->pv -= temp->sorts[3]->degat;
					effet_clignotement(* j1, * j2, j2->perso2);
					SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[3]->degat, 'n');
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
				break;
			}
		}

		if(j1->numJoueur == 2){
			switch (map[i][j]){

				case '1' :
					j2->perso1->pv -= temp->sorts[3]->degat;
					effet_clignotement(* j1, * j2, j2->perso1);
					SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[3]->degat, 'n');
					printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
				break;

				case '3' :
					j2->perso2->pv -= temp->sorts[3]->degat;
					effet_clignotement(* j1, * j2, j2->perso2);
					SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[3]->degat, 'n');
					printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
				break;
			}
		}
	}

	//ligne verticale
	for(i = coordi - l, j = coordj; i <= coordi + l; i++){
		if(i!=coordi){
			if(j1->numJoueur == 1){
				switch (map[i][j]){

					case '2' :
						j2->perso1->pv -= temp->sorts[3]->degat;
						effet_clignotement(* j1, * j2, j2->perso1);
						SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[3]->degat, 'n');
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

					case '4' :
						j2->perso2->pv -= temp->sorts[3]->degat;
						effet_clignotement(* j1, * j2, j2->perso2);
						SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[3]->degat, 'n');
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
					break;
				}
			}

			if(j1->numJoueur == 2){
				switch (map[i][j]){

					case '1' :
						j2->perso1->pv -= temp->sorts[3]->degat;
						effet_clignotement(* j1, * j2, j2->perso1);
						SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[3]->degat, 'n');
						printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
					break;

					case '3' :
						j2->perso2->pv -= temp->sorts[3]->degat;
						effet_clignotement(* j1, * j2, j2->perso2);
						SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[3]->degat, 'n');
						printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
					break;
				}
			}
		}
	}
}

/*************************************************************
*					                 Sorts du tank          					 *
*************************************************************/

void SDL_chenchen (t_joueur * j1, t_joueur * j2, int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g;
	char choix, player;

	t_personnage * temp;
	if(numero_perso == 1 ){
        temp = j1->perso1;

        if(j1->numJoueur == 1 )
        	player ='1';
        else
        	player = '3';
  	}

  else{
      temp = j1->perso2;
      if(j1->numJoueur == 1 )
      	player ='2';
      else
      	player = '4';
  	}

  	int dist = temp->sorts[2]->portee, coordi = 0, coordj = 0;
/* recopie matrice dans la matrice point qui affiche la portee */
	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] == '.' ){
							point[i][j] = 'A';
					}
					else if(point[i][j] != player){
						switch(point[i][j]){
							case '1':
								point[i][j] = 'a';
							break;
							case '2':
								point[i][j] = 'b';
							break;
							case '3':
								point[i][j] = 'c';
							break;
							case '4':
								point[i][j] = 'd';
							break;
						}
					}
				}
			}
		}
	}

	dist = temp->sorts[2]->portee;
	g = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(g != temp->coord.y){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(point[g][j] == '.'){
								point[g][j] = 'A';
						}
						else if(point[g][j] != player){
							switch(point[g][j]){
								case '1':
									point[g][j] = 'a';
								break;
								case '2':
									point[g][j] = 'b';
								break;
								case '3':
									point[g][j] = 'c';
								break;
								case '4':
									point[g][j] = 'd';
								break;
							}
						}
					}
				}
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

  //réduction des points de vies après le coup
	if(j1->numJoueur==1){
		switch (map[coordi][coordj]){

			case '2' :
				j2->perso1->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);

			break;

		 	case '4' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
	  	break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[coordi][coordj]){

			case '1' :
				j2->perso1->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
			break;

			case '3' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		 	break;
		}
	}
  }

void SDL_bigshaq (t_joueur * j1, t_joueur * j2,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g;
	char choix, player;

	t_personnage * temp;
	if(numero_perso == 1 ){
        temp = j1->perso1;

        if(j1->numJoueur == 1 )
        	player ='1';
        else
        	player = '3';
    }

  	else{
      temp = j1->perso2;
      if(j1->numJoueur == 1 )
      	player ='2';
      else
      	player = '4';
  	}

  	int dist = temp->sorts[3]->portee, coordi = 0, coordj = 0;

	int degats[4]={8,16,32,128};
	/*copie plan jeu dans la matrice point*/

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = temp->coord.y + 1;
	j = temp->coord.x ;


	int nb = 0;
	int car = 0;

	for(; i < N && nb < dist && point[i][j] != 'o'; i++, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y - 1;
	j = temp->coord.x;
	nb = 0;

	for(; i >= 0  && nb < dist && point[i][j] != 'o'; i--, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	i = temp->coord.y;
	j = temp->coord.x + 1;
	nb = 0;

	for(; j < N && nb < dist && point[i][j] != 'o'; j++, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

		i = temp->coord.y;
		j = temp->coord.x - 1;
		nb = 0;

	for(; j >= 0 && nb < dist && point[i][j] != 'o'; j--, nb++, car++){
		if(point[i][j] == '.'){
			point[i][j] = 'A' + car;
			car++;
		}
		else if(point[i][j] != player){
			switch(point[i][j]){
				case '1':
					point[i][j] = 'a';
				break;
				case '2':
					point[i][j] = 'b';
				break;
				case '3':
					point[i][j] = 'c';
				break;
				case '4':
					point[i][j] = 'd';
				break;
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

	int deg;
    //réduction des points de vies après le coup
    if(j1->numJoueur==1){
  		switch (map[coordi][coordj]){

  			case '2' :
          		if(temp->pv > 50){
            		j2->perso1->pv -= degats[0];
            		deg = degats[0];
            	}
          		else if(temp->pv > 25){
            		j2->perso1->pv -= degats[1];
            		deg = degats[1];
          		}
          		else if(temp->pv > 2){
            		j2->perso1->pv -= degats[2];
            		deg = degats[2];
            	}	
          		else if(temp->pv == 1){
            		j2->perso1->pv -= degats[3];
            		deg = degats[3];
          		}

          		effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, deg, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
  			break;

  		 	case '4' :
          		if(temp->pv > 50){
            		j2->perso2->pv -= degats[0];
            		deg = degats[0];
          		}
          		else if(temp->pv > 25){
            		j2->perso2->pv -= degats[1];
            		deg = degats[1];
          		}
          		else if(temp->pv > 2){
            		j2->perso2->pv -= degats[2];
            		deg = degats[2];
          		}
          		else if(temp->pv == 1){
            		j2->perso2->pv -= degats[3];
            		deg = degats[3];
          		}
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, deg, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
          break;
        }
  	}

    if(j1->numJoueur==2){
    	switch (map[coordi][coordj]){

        case '1' :
         	if(temp->pv > 50){
   	        	j2->perso1->pv -= degats[0];
            	deg = degats[0];
       		}
       		else if(temp->pv > 25){
            	j2->perso1->pv -= degats[1];
           		deg = degats[1];
       		}
       		else if(temp->pv > 2){
           		j2->perso1->pv -= degats[2];
            	deg = degats[2];
           	}	
          	else if(temp->pv == 1){
           		j2->perso1->pv -= degats[3];
           		deg = degats[3];
          	}

       		effet_clignotement(* j1, * j2, j2->perso1);
			SDL_afficher_degat(* j1, * j2, j2->perso1, deg, 'n');
			printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
    	break;

    	case '3' :
          	if(temp->pv > 50){
            	j2->perso2->pv -= degats[0];
            	deg = degats[0];
          	}
          	else if(temp->pv > 25){
            	j2->perso2->pv -= degats[1];
            	deg = degats[1];
          	}
          	else if(temp->pv > 2){
            	j2->perso2->pv -= degats[2];
            	deg = degats[2];
          	}
          	else if(temp->pv == 1){
            	j2->perso2->pv -= degats[3];
            	deg = degats[3];
        	}
			effet_clignotement(* j1, * j2, j2->perso2);
			SDL_afficher_degat(* j1, * j2, j2->perso2, deg, 'n');
			printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
        break;
      }
  	}
}

/*************************************************************
*					                 Sorts du druide          					 *
*************************************************************/

void SDL_fuego(t_joueur * j1, t_joueur * j2,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g;
	char choix, player;

	t_personnage * temp;
	if(numero_perso == 1 ){
        temp = j1->perso1;

        if(j1->numJoueur == 1 )
        	player ='1';
        else
        	player = '3';
  	}

  else{
      temp = j1->perso2;
      if(j1->numJoueur == 1 )
      	player ='2';
      else
      	player = '4';
  	}

  	int dist = temp->sorts[2]->portee, coordi = 0, coordj = 0;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] == '.' ){
							point[i][j] = 'A';
					}
					else if(point[i][j] != player){
						switch(point[i][j]){
							case '1':
								point[i][j] = 'a';
							break;
							case '2':
								point[i][j] = 'b';
							break;
							case '3':
								point[i][j] = 'c';
							break;
							case '4':
								point[i][j] = 'd';
							break;
						}
					}
				}
			}
		}
	}

	dist=temp->sorts[2]->portee;
	g = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(g != temp->coord.y){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(point[g][j] == '.'){
								point[g][j] = 'A';
						}
						else if(point[g][j] != player){
							switch(point[g][j]){
								case '1':
									point[g][j] = 'a';
								break;
								case '2':
									point[g][j] = 'b';
								break;
								case '3':
									point[g][j] = 'c';
								break;
								case '4':
									point[g][j] = 'd';
								break;
							}
						}
					}
				}
			}
		}
	}

	/* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

  //réduction des points de vies après le coup
	if(j1->numJoueur==1){
		switch (map[coordi][coordj]){

			case '2' :
				j2->perso1->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);

			break;

		 	case '4' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
	  	break;
		}
	}

	if(j1->numJoueur==2){
		switch (map[coordi][coordj]){

			case '1' :
				j2->perso1->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso1);
				SDL_afficher_degat(* j1, * j2, j2->perso1, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso1->nom, j2->perso1->pv);
			break;

			case '3' :
				j2->perso2->pv -= temp->sorts[2]->degat;
				effet_clignotement(* j1, * j2, j2->perso2);
				SDL_afficher_degat(* j1, * j2, j2->perso2, temp->sorts[2]->degat, 'n');
				printf("%s touché.\nPoint de vie : %i\n", j2->perso2->nom, j2->perso2->pv);
		 	break;
		}
	}
}

void SDL_revitalisation (t_joueur * j1, t_joueur * j2,int numero_perso){

  	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g;
	char choix, player;

	t_personnage * temp;
	if(numero_perso == 1 ){
        temp = j1->perso1;

        if(j1->numJoueur == 1 )
        	player ='1';
        else
        	player = '3';
  	}

  	else{
      temp = j1->perso2;
      if(j1->numJoueur == 1 )
      	player ='2';
      else
      	player = '4';
  	}

  	int dist = temp->sorts[3]->portee, coordi = 0, coordj = 0;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la portée vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[i][j] == '.' ){
							point[i][j] = 'A';
					}
					else if(point[i][j] != player){
						switch(point[i][j]){
							case '1':
								point[i][j] = 'a';
							break;
							case '2':
								point[i][j] = 'b';
							break;
							case '3':
								point[i][j] = 'c';
							break;
							case '4':
								point[i][j] = 'd';
							break;
						}
					}
				}
			}
		}
	}

  	dist = temp->sorts[3]->portee;
	g = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la portée vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(g != temp->coord.y){
						//ne pas repasser une seconde fois sur la ligne du j
						if(point[g][j] == '.'){
								point[g][j] = 'A';
						}
						else if(point[g][j] != player){
							switch(point[g][j]){
								case '1':
									point[g][j] = 'a';
								break;
								case '2':
									point[g][j] = 'b';
								break;
								case '3':
									point[g][j] = 'c';
								break;
								case '4':
									point[g][j] = 'd';
								break;
							}
						}
					}
				}
			}
		}
	}

  /* affichage de la carte avec le choix des cases atteignables par le personnage perso1*/
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	affichage_map(point);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, * j1, * j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);

  //réduction des points de vies après le coup
	if(j1->numJoueur==2){
		switch (map[coordi][coordj]){

			case '2' :
				j1->perso1->pv += temp->sorts[3]->degat;
				effet_clignotement(* j1, * j2, j1->perso1);
				SDL_afficher_degat(* j1, * j2, j1->perso1, temp->sorts[3]->degat, 'p');
				printf("%s soigné.\nPoint de vie : %i\n", j1->perso1->nom, j1->perso1->pv);

			break;

		 	case '4' :
				j1->perso2->pv += temp->sorts[3]->degat;
				effet_clignotement(* j1, * j2, j1->perso2);
				SDL_afficher_degat(* j1, * j2, j1->perso2, temp->sorts[3]->degat, 'p');
				printf("%s soigné.\nPoint de vie : %i\n", j1->perso2->nom, j1->perso2->pv);
	  	break;
		}
	}

	if(j1->numJoueur==1){
		switch (map[coordi][coordj]){

			case '1' :
				j1->perso1->pv += temp->sorts[3]->degat;
				effet_clignotement(* j1, * j2, j1->perso1);
				SDL_afficher_degat(* j1, * j2, j1->perso1, temp->sorts[3]->degat, 'p');
				printf("%s soigné.\nPoint de vie : %i\n", j1->perso1->nom, j1->perso1->pv);
			break;

			case '3' :
				j1->perso2->pv += temp->sorts[3]->degat;
				effet_clignotement(* j1, * j2, j1->perso2);
				SDL_afficher_degat(* j1, * j2, j1->perso2, temp->sorts[3]->degat, 'p');
				printf("%s soigné.\nPoint de vie : %i\n", j1->perso2->nom, j1->perso2->pv);
		 	break;
		}
	}
}
