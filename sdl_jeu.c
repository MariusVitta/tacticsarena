#include "fonc.h"
#include "sdl_fonc.h"

void SDL_choix_perso(t_joueur *joueur1, t_joueur *joueur2){
	int i, j, classe;
	int num_j = 1,choix;
	int x = 0, y = 0;
	joueur1->perso1 = NULL;
	joueur1->perso2 = NULL;
	joueur2->perso1 = NULL;
	joueur2->perso2 = NULL;

	printf("Joueur 1: choisir une classe personnage 1\n");
	printf("[1] : Guerrier\n");
	printf("[2] : Archer\n");
	printf("[3] : Tank\nChoix personnage 1: ");
	SDL_RenderClear(renderer);
	SDL_affichage_choix_perso(1);
	SDL_afficher_perso_choisi(*joueur1, *joueur2);
	SDL_RenderPresent(renderer);

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
					x = e.button.x;
					y = e.button.y;
			}
		}
	} while(!acces_choix_perso(x, y, &classe));

	printf("Choix j1 p1 : %i\n", classe);
	joueur1->perso1 = malloc(sizeof(t_personnage));
	creer_perso(classe,joueur1->perso1);


	printf("Joueur 1: choisir une classe personnage 2\n");
	printf("[1] : Guerrier\n");
	printf("[2] : Archer\n");
	printf("[3] : Tank\nChoix personnage 1: ");
	SDL_RenderClear(renderer);
	SDL_affichage_choix_perso(1);
	SDL_afficher_perso_choisi(*joueur1, *joueur2);
	SDL_RenderPresent(renderer);
	x = 0;
	y = 0;
	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
					x = e.button.x;
					y = e.button.y;
			}
		}
	} while(!acces_choix_perso(x, y, &classe));

	printf("Choix j2 p2 : %i\n", classe);
	joueur1->perso2 = malloc(sizeof(t_personnage));
	creer_perso(classe,joueur1->perso2);

	joueur1->numJoueur = 1;
	joueur1->nbPVivant = 2;

	printf("Joueur 2: choisir une classe personnage 1\n");
	printf("[1] : Guerrier\n");
	printf("[2] : Archer\n");
	printf("[3] : Tank\nChoix personnage 1: ");

	SDL_RenderClear(renderer);
	SDL_affichage_choix_perso(2);
	SDL_afficher_perso_choisi(*joueur1, *joueur2);
	SDL_RenderPresent(renderer);

	x = 0;
	y = 0;
	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
					x = e.button.x;
					y = e.button.y;
			}
		}
	} while(!acces_choix_perso(x, y, &classe));

	printf("Choix j2 p1 : %i\n", classe);
	joueur2->perso1 = malloc(sizeof(t_personnage));
	creer_perso(classe,joueur2->perso1 );

	printf("Joueur 2: choisir une classe personnage 2\n");
	printf("[1] : Guerrier\n");
	printf("[2] : Archer\n");
	printf("[3] : Tank\nChoix personnage 1: ");
	SDL_RenderClear(renderer);
	SDL_affichage_choix_perso(2);
	SDL_afficher_perso_choisi(*joueur1, *joueur2);
	SDL_RenderPresent(renderer);

	x = 0;
	y = 0;
	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
					x = e.button.x;
					y = e.button.y;
			}
		}
	} while(!acces_choix_perso(x, y, &classe));

	printf("Choix j2 p2 : %i\n", classe);
	joueur2->perso2 = malloc(sizeof(t_personnage));
	creer_perso(classe,joueur2->perso2);
	joueur2->numJoueur = 2;
	joueur2->nbPVivant = 2;

	SDL_RenderClear(renderer);
	SDL_affichage_choix_perso(2);
	SDL_afficher_perso_choisi(*joueur1, *joueur2);
	SDL_RenderPresent(renderer);
	SDL_Delay(500);
}

void SDL_initialisation(char matriceJeu[N][N],t_joueur * joueur1,t_joueur * joueur2){
	srand(time(NULL));
	int y1 = rand()%3+(N-3), x1 = rand()%(N-4)+2, y2, x2, x = 0, y = 0, coordi = 0, coordj = 0;
	int i,j,numero_j=1;
	char choix1 = '0',choix2 = '0';
	int nb_persos = 1;
	int nb_obs = 10; /* nb d'obstacles max sur la carte*/
    /* remplissage de la map sans les joueurs positionnés */
	for(i = 0; i < N ; i++){
		for(j = 0;j < N; j++){
				matriceJeu[i][j] = '.';
		}
	}
	

	while(numero_j <=2){
		printf("\n ---- Choix des cases possibles pour le joueur %i ---- \n",numero_j);
		/* choix des positions du premier joueurs*/
		if(numero_j == 1){

			matriceJeu[y1][x1]='A';
			matriceJeu[y1-1][x1-2]='B';
			matriceJeu[y1 -1][x1 + 2]='C';
			printf("\n[A]{x=%i y=%i}\n[B]{x=%i y=%i}\n[C]{x=%i y=%i}\n",x1,y1,x1-2,y1-1,x1+2,y1-1);

			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
			SDL_afficher_message("Placer personnage 1", 920, 80, "Police/calendarnote.ttf", 35, 'o', 'N');
			SDL_afficher_message("ÌJoueur1Í",1030, 15, "Police/yorkwhiteletter.ttf", 45, 'r', 'N');
			SDL_RenderPresent(renderer);

			do{
				SDL_Event e;
				while(SDL_PollEvent(&e)){
					if(e.type == SDL_MOUSEBUTTONDOWN){
							x = e.button.x;
							y = e.button.y;
							/*if(acces_possible(x, y, &coordi, &coordj)){
								printf("i = %i ; j = %i\n",coordi, coordj);
								matriceJeu[coordi][coordj] = 'x';
								SDL_RenderClear(renderer);
								SDL_afficher_map(matriceJeu);
								SDL_RenderPresent(renderer);
							}*/
					}
				}

				//printf("x = %i et y = %i\n", x, y);
				/*if(acces_possible(x, y, &coordi, &coordj))
					printf("L'accès est possible\n");
				else
					printf("L'accès est impossible\n");*/

			} while(!acces_possible(x, y, &coordi, &coordj));

			//printf("ifonc = %i et jfonc = %i\n", coordi, coordj);
			matriceJeu[coordi][coordj] = 'x';
			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);

			matriceJeu[coordi][coordj] = '1';
			joueur1->perso1->coord.x = coordj;
			joueur1->perso1->coord.y = coordi;


			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
			SDL_afficher_message("Placer personnage 2", 920, 80, "Police/calendarnote.ttf", 35, 'o', 'N');
			SDL_afficher_message("ÌJoueur1Í",1030, 15, "Police/yorkwhiteletter.ttf", 45, 'r', 'N');
			SDL_RenderPresent(renderer);

			coordj = 0;
			coordi = 0;

			do{
				SDL_Event e;
				while(SDL_PollEvent(&e)){
					if(e.type == SDL_MOUSEBUTTONDOWN){
							x = e.button.x;
							y = e.button.y;
					}
				}

				/*printf("x = %i et y = %i\n", x, y);
				if(acces_possible(x, y, &y1, &x1))
					printf("L'accès est possible\n");
				else
					printf("L'accès est impossible\n");*/

			} while(!acces_possible(x, y, &coordi, &coordj));

			//printf("ifonc = %i et jfonc = %i\n", coordi, coordj);
			matriceJeu[coordi][coordj] = 'x';
			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
            matriceJeu[coordi][coordj] = '3';

            joueur1->perso2->coord.x = coordj;
			joueur1->perso2->coord.y = coordi;

            if(matriceJeu[y1][x1]!= '1' && matriceJeu[y1][x1]!= '3')
            		matriceJeu[y1][x1]='.';
            if(matriceJeu[y1-1][x1-2]!='1' && matriceJeu[y1-1][x1-2]!= '3')
            		matriceJeu[y1-1][x1-2]='.';
            if(matriceJeu[y1 -1][x1 + 2]!='1' && matriceJeu[y1 -1][x1 + 2]!= '3')
            		matriceJeu[y1 -1][x1 + 2]='.';

        }


		else{
			/*choix des positions du deuxième joueur */
			y2 = rand()%3;
			x2 = rand()%(N-4)+2;
			matriceJeu[y2][x2]='D';
			matriceJeu[y2+1][x2-2]='E';
			matriceJeu[y2 +1][x2 + 2]='F';
			printf("\n[D]{x=%i y=%i}\n[E]{x=%i y=%i}\n[F]{x=%i y=%i}\n",x2 ,y2 ,x2 -2,y2+1,x2+2,y2+1);

			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
			SDL_afficher_message("Placer personnage 1", 920, 80, "Police/calendarnote.ttf", 35, 'o', 'N');
			SDL_afficher_message("ÌJoueur2Í",1030, 15, "Police/yorkwhiteletter.ttf", 45, 'r', 'N');
			SDL_RenderPresent(renderer);


			coordj = 0;
			coordi = 0;

			do{
				SDL_Event e;
				while(SDL_PollEvent(&e)){
					if(e.type == SDL_MOUSEBUTTONDOWN){
							x = e.button.x;
							y = e.button.y;
					}
				}

			} while(!acces_possible(x, y, &coordi, &coordj));

			matriceJeu[coordi][coordj] = 'x';
			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);

			matriceJeu[coordi][coordj] = '2';
			joueur2->perso1->coord.x = coordj;
			joueur2->perso1->coord.y = coordi;

			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
			SDL_afficher_message("Placer personnage 2", 920, 80, "Police/calendarnote.ttf", 35, 'o', 'N');
			SDL_afficher_message("ÌJoueur2Í",1030, 15, "Police/yorkwhiteletter.ttf", 45, 'r', 'N');
			SDL_RenderPresent(renderer);

			coordj = 0;
			coordi = 0;

			do{
				SDL_Event e;
				while(SDL_PollEvent(&e)){
					if(e.type == SDL_MOUSEBUTTONDOWN){
							x = e.button.x;
							y = e.button.y;
					}
				}

			} while(!acces_possible(x, y, &coordi, &coordj));

			matriceJeu[coordi][coordj] = 'x';
			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
			matriceJeu[coordi][coordj] = '4';
			joueur2->perso2->coord.x = coordj;
			joueur2->perso2->coord.y = coordi;

			if(matriceJeu[y2][x2]!= '2' && matriceJeu[y2][x2]!= '4')
            	matriceJeu[y2][x2]='.';
      if(matriceJeu[y2+1][x2-2]!='2' && matriceJeu[y2+1][x2-2]!= '4')
            	matriceJeu[y2+1][x2-2]='.';
      if(matriceJeu[y2 +1][x2 + 2]!='2' && matriceJeu[y2 +1][x2 + 2]!= '4')
            	matriceJeu[y2 +1][x2 + 2]='.';

		}

		choix1 = 0;
        choix2 = 0;
		numero_j++;
	}
    /* obstacles générés sur toutes la carte sauf les bords */
	int obs_x = rand()%(N-2)+1 , obs_y = rand()%(N-2)+1;

	/* génération des obstacles sur la carte */
	i = 1;
	while(i <= nb_obs){
		if(matriceJeu[obs_y][obs_x] == '.'){
			matriceJeu[obs_y][obs_x] = 'o';
			i++;
		}
		obs_x = rand()%(N-2)+1 , obs_y = rand()%(N-2)+1;
	}
	SDL_RenderClear(renderer);
	SDL_afficher_map(matriceJeu, *joueur1, *joueur2);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
}

/*avec personnage n le nombre de deplacements qu'il reste et num_j le numero du joueur*/
int SDL_deplacement(t_joueur j1,t_joueur j2,char map[N][N],int  n ,int num_j,int numero_perso ){

    int x = 0, y = 0, coordi = 0, coordj = 0;
    t_personnage * temp;

    if(numero_perso == 1 ){
        temp = j1.perso1;
    }
    else{
        temp = j1.perso2;
    }
	char choix;

	char point[N][N];

	int i, j;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}

	i = temp->coord.y + 1;
	j = temp->coord.x ;
	printf("temp x = %i et temp y = %i\n", temp->coord.x,temp->coord.y);
	printf("j x = %i et j y = %i\n", j1.perso1->coord.x, j1.perso1->coord.y);


	int nb = 0;
	int car = 0;

	for(; i < N && nb < n && point[i][j] == '.'; i++, nb++, car++)
		point[i][j] = 'A' + car;

	i = temp->coord.y - 1;
	j = temp->coord.x;
	nb = 0;

	for(; i >= 0  && nb < n && point[i][j] == '.'; i--, nb++, car++)
		point[i][j] = 'A' + car;

	i = temp->coord.y;
	j = temp->coord.x + 1;
	nb = 0;

	for(; j < N && nb < n && point[i][j] == '.'; j++, nb++, car++){
		point[i][j] = 'A' + car;
	}

	i = temp->coord.y;
	j = temp->coord.x - 1;
	nb = 0;

	for(; j >= 0 && nb < n && point[i][j] == '.'; j--, nb++, car++)
		point[i][j] = 'A' + car;

	if(n >= 2){
		if(point[temp->coord.y + 1][temp->coord.x + 1] == '.' && (temp->coord.y + 1) < N && (temp->coord.x + 1) < N)
			point[temp->coord.y + 1][temp->coord.x + 1] = 'A' + car++;
		if(point[temp->coord.y - 1][temp->coord.x - 1] == '.' && (temp->coord.y - 1) >= 0 && (temp->coord.x - 1) >= 0)
			point[temp->coord.y - 1][temp->coord.x - 1] = 'A' + car++;
		if(point[temp->coord.y + 1][temp->coord.x - 1] == '.' && (temp->coord.y + 1) < N && (temp->coord.x - 1) >= 0)
			point[temp->coord.y + 1][temp->coord.x - 1] = 'A' + car++;
		if(point[temp->coord.y - 1][temp->coord.x + 1] == '.' && (temp->coord.y - 1) >= 0 && (temp->coord.x + 1) < N)
			point[temp->coord.y - 1][temp->coord.x + 1] = 'A' + car++;
	}

	if(n >= 3){
		if(point[temp->coord.y + 2][temp->coord.x + 1] == '.' && (temp->coord.y + 2) < N && (temp->coord.x + 1) < N)
			point[temp->coord.y + 2][temp->coord.x + 1] = 'A' + car++;
		if(point[temp->coord.y - 2][temp->coord.x - 1] == '.' && (temp->coord.y - 2) >= 0 && (temp->coord.x - 1) >= 0)
			point[temp->coord.y - 2][temp->coord.x - 1] = 'A' + car++;
		if(point[temp->coord.y + 2][temp->coord.x - 1] == '.' && (temp->coord.y + 2) < N && (temp->coord.x - 1) >= 0)
			point[temp->coord.y + 2][temp->coord.x - 1] = 'A' + car++;
		if(point[temp->coord.y - 2][temp->coord.x + 1] == '.' && (temp->coord.y - 2) >= 0 && (temp->coord.x + 1) < N)
			point[temp->coord.y - 2][temp->coord.x + 1] = 'A' + car++;

		if(point[temp->coord.y + 1][temp->coord.x + 2] == '.' && (temp->coord.y + 1) < N && (temp->coord.x + 2) < N)
			point[temp->coord.y + 1][temp->coord.x + 2] = 'A' + car++;
		if(point[temp->coord.y - 1][temp->coord.x - 2] == '.' && (temp->coord.y - 1) >=  0 && (temp->coord.x - 2) >= 0)
			point[temp->coord.y - 1][temp->coord.x - 2] = 'A' + car++;
		if(point[temp->coord.y + 1][temp->coord.x - 2] == '.' && (temp->coord.y + 1) < N && (temp->coord.x - 2) >= 0)
			point[temp->coord.y + 1][temp->coord.x - 2] = 'A' + car++;
		if(point[temp->coord.y - 1][temp->coord.x + 2] == '.' && (temp->coord.y - 1) >= 0 && (temp->coord.x + 2) < N)
			point[temp->coord.y - 1][temp->coord.x + 2] = 'A' + car++;
	}
	affichage_map(point);
	affichage_map(map);
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, j1, j2);
	SDL_RenderPresent(renderer);

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
				printf("x = %i et y = %i\n", x, y);
			}
		}
	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, j1, j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);


	int nb_dep = abs(temp->coord.x - coordj) + abs(temp->coord.y - coordi);

	printf("nb deplacements = %i\n", nb_dep);
	temp->coord.x = coordj;
	temp->coord.y = coordi;

	printf("temp x = %i et temp y = %i\n", temp->coord.x, temp->coord.y);

	if(num_j==1){
		//printf("j1 x = %i et j2 y = %i\n", j1.perso1->coord.x, j1.perso2->coord.y);
		maj(map,j1,j2);
		affichage_map(point);
		affichage_map(map);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map, j1, j2);
		SDL_RenderPresent(renderer);
	}
	else{
		maj(map,j2,j1);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map, j1, j2);
		SDL_RenderPresent(renderer);
	}

	return n - nb_dep;
}
