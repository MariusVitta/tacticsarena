#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include "fonc.h"


SDL_Window* window = NULL;
SDL_Renderer *renderer=NULL;

SDL_Texture * bg = NULL;
SDL_Texture * case_n = NULL;
SDL_Texture * case_p = NULL;
SDL_Texture * case_c = NULL;
SDL_Texture * case_s = NULL;
SDL_Texture * obstacle = NULL;
SDL_Texture * guerrier = NULL;
SDL_Texture * archer = NULL;
SDL_Texture * tank = NULL;

char map[N][N];

typedef enum {CASE_GRISE, CASE_BLEUE, OBSTACLE, J1, J2}t_type_case;

typedef struct s_borne{
	int borne1;
	int borne2;
}t_borne;

typedef struct s_case {
	t_type_case type;
	int i;
	int j;
	t_borne largeur;
	t_borne hauteur;
}t_case;

t_case SDL_map[N * N];

/* Verifie s'il est possible d'acceder à une case*/
int acces_possible(int x, int y, int * ymap, int * xmap){

	int i;

	for(i = 0; i < N*N; i++){
		if(SDL_map[i].type == OBSTACLE){
			if((x >= SDL_map[i].largeur.borne1 && x <= SDL_map[i].largeur.borne2) && (y >= SDL_map[i].hauteur.borne1 && y <= SDL_map[i].hauteur.borne2))
				return 0;
		}

		else if(SDL_map[i].type == CASE_GRISE){
			if((x >= SDL_map[i].largeur.borne1 && x <= SDL_map[i].largeur.borne2) && (y >= SDL_map[i].hauteur.borne1 && y <= SDL_map[i].hauteur.borne2))
				return 0;
		}

		else if(SDL_map[i].type == CASE_BLEUE){
			if((x >= SDL_map[i].largeur.borne1 && x <= SDL_map[i].largeur.borne2) && (y >= SDL_map[i].hauteur.borne1 && y <= SDL_map[i].hauteur.borne2)){
				* ymap = SDL_map[i].i;
				* xmap = SDL_map[i].j;
				return 1;
			}
		}
	}

	return 0;
}

int SDL_creer_fenetre(){

	/* Initialisation simple */
   	if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
   	     fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
   	     return -1;
   	 }

	/* Création de la fenêtre */

	window = SDL_CreateWindow("Tactics Arena du turfu",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

	if(!window){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	if(!renderer){
		fprintf(stderr, "Erreur à la création du renderer : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return 1;
}

void SDL_creer_texture(){

	SDL_Surface * imgbg = NULL;
	SDL_Surface * imgcase_n = NULL;
	SDL_Surface * imgcase_p = NULL;
	SDL_Surface * imgcase_c = NULL;
	SDL_Surface * imgcase_s = NULL;
	SDL_Surface * imgobstacle = NULL;
	SDL_Surface * imgguerrier = NULL;
	SDL_Surface * imgarcher = NULL;
	SDL_Surface * imgtank = NULL;

	SDL_RWops * r_bg = SDL_RWFromFile("fondn.png", "rb");
	SDL_RWops * r_case_n = SDL_RWFromFile("cn.png", "rb");
	SDL_RWops * r_case_p = SDL_RWFromFile("cp.png", "rb");
	SDL_RWops * r_case_c = SDL_RWFromFile("cc.png", "rb");
	SDL_RWops * r_case_s = SDL_RWFromFile("cs.png", "rb");
	SDL_RWops * r_obstacle = SDL_RWFromFile("obstacle.png", "rb");
	SDL_RWops * r_guerrier = SDL_RWFromFile("guerrier.png", "rb");
	SDL_RWops * r_archer = SDL_RWFromFile("archer.png", "rb");
	SDL_RWops * r_tank = SDL_RWFromFile("tank.png", "rb");

	imgbg = IMG_LoadPNG_RW(r_bg);
	imgcase_n = IMG_LoadPNG_RW(r_case_n);
	imgcase_c = IMG_LoadPNG_RW(r_case_c);
	imgcase_p = IMG_LoadPNG_RW(r_case_p);
	imgcase_s = IMG_LoadPNG_RW(r_case_s);
	imgobstacle = IMG_LoadPNG_RW(r_obstacle);
	imgguerrier = IMG_LoadPNG_RW(r_guerrier);
	imgarcher = IMG_LoadPNG_RW(r_archer);
	imgtank = IMG_LoadPNG_RW(r_tank);

	if(!imgbg)
		fprintf(stderr, "Image background non chargée : %s\n", IMG_GetError());
	if(!imgcase_n)
		fprintf(stderr, "Image case normale non chargée : %s\n", IMG_GetError());
	if(!imgcase_p)
		fprintf(stderr, "Image case possible non chargée : %s\n", IMG_GetError());
	if(!imgcase_c)
		fprintf(stderr, "Image case normale non chargée : %s\n", IMG_GetError());
	if(!imgcase_s)
		fprintf(stderr, "Image case sélectionnée non chargée : %s\n", IMG_GetError());
	if(!imgobstacle)
		fprintf(stderr, "Image obstacle normale non chargée : %s\n", IMG_GetError());
	if(!imgguerrier)
		fprintf(stderr, "Image guerrier normale non chargée : %s\n", IMG_GetError());
	if(!imgarcher)
		fprintf(stderr, "Image archer normale non chargée : %s\n", IMG_GetError());
	if(!imgtank)
		fprintf(stderr, "Image tank normale non chargée : %s\n", IMG_GetError());

	bg = SDL_CreateTextureFromSurface(renderer, imgbg);
	case_n = SDL_CreateTextureFromSurface(renderer, imgcase_n);
	case_p = SDL_CreateTextureFromSurface(renderer, imgcase_p);
	case_c = SDL_CreateTextureFromSurface(renderer, imgcase_c);
	case_s = SDL_CreateTextureFromSurface(renderer, imgcase_s);
	obstacle = SDL_CreateTextureFromSurface(renderer, imgobstacle);
	guerrier = SDL_CreateTextureFromSurface(renderer, imgguerrier);
	archer = SDL_CreateTextureFromSurface(renderer, imgarcher);
	tank = SDL_CreateTextureFromSurface(renderer, imgtank);

	SDL_FreeSurface(imgbg);
	SDL_FreeSurface(imgcase_n);
	SDL_FreeSurface(imgcase_p);
	SDL_FreeSurface(imgcase_c);
	SDL_FreeSurface(imgcase_s);
	SDL_FreeSurface(imgobstacle);
	SDL_FreeSurface(imgguerrier);
	SDL_FreeSurface(imgarcher);
	SDL_FreeSurface(imgtank);

	if(!bg)
		fprintf(stderr, "Texture background non créee : %s\n", SDL_GetError());
	if(!case_n)
		fprintf(stderr, "Texture case normale non créee : %s\n", SDL_GetError());
	if(!case_c)
		fprintf(stderr, "Texture case possible non créee : %s\n", SDL_GetError());
	if(!case_n)
		fprintf(stderr, "Texture case normale non créee : %s\n", SDL_GetError());
	if(!case_s)
		fprintf(stderr, "Texture case sélectionnée non créee : %s\n", SDL_GetError());
	if(!obstacle)
		fprintf(stderr, "Texture obstacle non créee : %s\n", SDL_GetError());
	if(!guerrier)
		fprintf(stderr, "Texture guerrier non créee : %s\n", SDL_GetError());
	if(!archer)
		fprintf(stderr, "Texture archer non créee : %s\n", SDL_GetError());
	if(!tank)
		fprintf(stderr, "Texture archer non créee : %s\n", SDL_GetError());


}

void SDL_afficher_map(char map[N][N]){

	SDL_Rect recbg;

	if(!SDL_QueryTexture(bg, NULL, NULL, &recbg.w, &recbg.h))
		;//fprintf(stderr, "Texture non chargée : %s\n", SDL_GetError());

	if(!SDL_RenderCopy(renderer, bg, NULL, NULL));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());*/

	int i, j, w = 80, h = 40, x = 628, y = 122, k = 0; //x = 100, y = (HAUTEUR/2) - 50, k = 0;


	SDL_Rect reccase_n;

	reccase_n.w = w;
	reccase_n.h = h;
	reccase_n.x = x;
	reccase_n.y = y;
	int depx = reccase_n.x, depy = reccase_n.y;

	SDL_Rect reccase_p;

	reccase_p.w = w;
	reccase_p.h = h;
	reccase_p.x = x;
	reccase_p.y = y;

	SDL_Rect reccase_c;

	reccase_c.w = w;
	reccase_c.h = h;
	reccase_c.x = x;
	reccase_c.y = y;

	SDL_Rect recobstacle;
	int xo = x+3, yo = y-38, wo = w - 5, ho = h + 40;//48

	recobstacle.w = wo;
	recobstacle.h = ho;//50
	recobstacle.x = xo;
	recobstacle.y = yo;

	SDL_Rect reccase_s;
	int ws = w - 15, hs = h - 15;

	reccase_s.w = ws;
	reccase_s.h = hs;

	SDL_Rect recguerrier;

	recguerrier.w = 100;
	recguerrier.h = 100;

	SDL_Rect rectank;

	rectank.w = 115;
	rectank.h = 115;

	SDL_Rect recarcher;

	recarcher.w = 95;
	recarcher.h = 95;

	for(i = 0; i < N; i++){
		for(j = N-1; j >= 0 ; j--){

			if(map[i][j] == 'o'){
				if(!SDL_RenderCopy(renderer, obstacle, NULL, &recobstacle));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k].type = OBSTACLE;
				SDL_map[k].largeur.borne1 = reccase_n.x;
				SDL_map[k].largeur.borne2 = reccase_n.x + w;
				SDL_map[k].hauteur.borne1 = reccase_n.y;
				SDL_map[k].hauteur.borne2 = reccase_n.y + ho;
				k++;
			}

			else if(map[i][j] >= 'A' && map[i][j] <= 'Z'){
				if(!SDL_RenderCopy(renderer, case_p, NULL, &reccase_p));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k].type = CASE_BLEUE;
				SDL_map[k].largeur.borne1 = reccase_n.x;
				SDL_map[k].largeur.borne2 = reccase_n.x + w;
				SDL_map[k].hauteur.borne1 = reccase_n.y;
				SDL_map[k].hauteur.borne2 = reccase_n.y + h;
				k++;
			}

			else if(map[i][j] == 'x'){
				if(!SDL_RenderCopy(renderer, case_c, NULL, &reccase_c));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}

			else{

				if(!SDL_RenderCopy(renderer, case_n, NULL, &reccase_n));
						//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k].type = CASE_GRISE;
				SDL_map[k].largeur.borne1 = reccase_n.x;
				SDL_map[k].largeur.borne2 = reccase_n.x + w;
				SDL_map[k].hauteur.borne1 = reccase_n.y;
				SDL_map[k].hauteur.borne2 = reccase_n.y + h;

				if (map[i][j] == '2'){

					//reccase_s.x = reccase_n.x + 7;
					//reccase_s.y = reccase_n.y + 7;
					recarcher.x = reccase_n.x - 32;
					recarcher.y = reccase_n.y - 70;

					//if(!SDL_RenderCopy(renderer, case_s, NULL, &reccase_s));
						//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

					if(!SDL_RenderCopy(renderer, archer, NULL, &recarcher));
						//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J2;

				}


				else if(map[i][j] == '1'){

					recguerrier.x = reccase_n.x - 10;
					recguerrier.y = reccase_n.y - 72;

					if(!SDL_RenderCopy(renderer, guerrier, NULL, &recguerrier));
						//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J2;
				}

				else if(map[i][j] == '3'){

					rectank.x = reccase_n.x - 20;
					rectank.y = reccase_n.y - 85;

					if(!SDL_RenderCopy(renderer, tank, NULL, &rectank));
						//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J2;
				}

				k++;

			}
			reccase_n.y = reccase_n.y + (h/2) + 3;//5
			reccase_n.x = reccase_n.x - (w/2) - 8;//10

			reccase_p.y = reccase_p.y + (h/2) + 3;
			reccase_p.x = reccase_p.x - (w/2) - 8;

			reccase_c.y = reccase_c.y + (h/2) + 3;//5
			reccase_c.x = reccase_c.x - (w/2) - 8;//10

			recobstacle.y = recobstacle.y + (h/2) + 3;
			recobstacle.x = recobstacle.x - (w/2) - 8;
		}
	  	//printf("x = %i et y = %i\n", reccase_n.x, reccase_n.y);
		reccase_n.y = y + (((h/2) + 3)*(i+1));
		reccase_n.x = x + (((w/2) + 8)*(i+1));

		reccase_p.y = y + (((h/2) + 3)*(i+1));
		reccase_p.x = x + (((w/2) + 8)*(i+1));

		reccase_c.y = y + (((h/2) + 3)*(i+1));
		reccase_c.x = x + (((w/2) + 8)*(i+1));

		recobstacle.y = yo + (((h/2) + 3)*(i+1));
		recobstacle.x = xo + (((w/2) + 8)*(i+1));

		//printf("x = %i et y = %i\n", reccase_n.x, reccase_n.y);
	}


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
			SDL_afficher_map(matriceJeu);
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
			SDL_afficher_map(matriceJeu);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);

			matriceJeu[coordi][coordj] = '1';
			joueur1->perso1->coord.x = coordj;
			joueur1->perso1->coord.y = coordi;


			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu);
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
			SDL_afficher_map(matriceJeu);
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
			SDL_afficher_map(matriceJeu);
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
			SDL_afficher_map(matriceJeu);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);

			matriceJeu[coordi][coordj] = '2';
			joueur2->perso1->coord.x = coordj;
			joueur2->perso1->coord.y = coordi;

			SDL_RenderClear(renderer);
			SDL_afficher_map(matriceJeu);
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
			SDL_afficher_map(matriceJeu);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
			matriceJeu[coordi][coordj] = '4';
			joueur2->perso2->coord.x = coordj;
			joueur2->perso2->coord.y = coordi;

			if(matriceJeu[y2][x2]!= '2' && matriceJeu[y2][x2]!= '4')
            		matriceJeu[y2][x2]='.';
            if(matriceJeu[y2+1][x2-2]!='2' && matriceJeu[y2+1][x2-2]!= '4')
            		matriceJeu[y2+1][x2-2]='.';
            if(matriceJeu[y2 +1][x2 + 2]!='2' && matriceJeu[y2 +1][x2 + 2]!= '2')
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
	//affichage_map(matriceJeu);
}

/*avec personnage n le nombre de deplacements qu'il reste et nbj le numero du joueur*/
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
	SDL_afficher_map(point);
	SDL_RenderPresent(renderer);

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
	SDL_afficher_map(point);
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
		SDL_afficher_map(map);
		SDL_RenderPresent(renderer);
	}
	else{
		maj(map,j2,j1);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map);
		SDL_RenderPresent(renderer);
	}

	return n - nb_dep;
}

int SDL_saut(t_joueur j1,t_joueur j2,char map[N][N],int num_j,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g,car=0, coordi = 0, coordj = 0;
	char choix;

    t_personnage * temp;
    if(numero_perso == 1 ){
        temp = j1.perso1;
    }
    else{
        temp = j1.perso2;
    }
    int dist=temp->s1.portee;

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

	dist=temp->s1.portee;
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
	SDL_afficher_map(point);
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
	SDL_afficher_map(point);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);


	temp->coord.x = coordj;

	temp->coord.y = coordi;



	if(num_j==1){
		maj(map,j1,j2);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map);
		SDL_RenderPresent(renderer);
	}
	else{
		maj(map,j2,j1);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map);
		SDL_RenderPresent(renderer);
	}

	return 1;
}

int main (int argc, char** argv){


	/*char map[N][N] = {{'.','.','.','.','.','.','.','.','.','.','.'},

				{'.','.','.','.','.','.','.','.','.','o','A'},

				{'.','.','.','o','.','.','.','.','.','A','.'},

				{'.','.','.','.','A','.','o','.','A','.','.'},

				{'.','3','.','.','.','A','1','A','.','.','1'},

				{'.','.','.','.','.','.','2','o','.','o','1'},

				{'.','.','o','.','.','A','.','A','.','.','.'},

				{'.','.','o','.','A','.','.','.','A','.','.'},

				{'.','.','.','A','.','.','.','o','o','A','.'},

				{'.','.','A','.','.','.','.','o','o','.','A'},

				{'.','A','.','.','.','.','.','.','.','.','.'}};

			*/	int i, j, classe1, classe2,nb_tour = 1,mort1 = 0,mort2 = 0;
			    int num_j = 1,choix;
				t_joueur joueur1,joueur2;

				do{
					printf("Joueur 1: choisir une classe personnage 1 et classe personnage 2\n");
					printf("[1] : Guerrier\n");
					printf("[2] : Archer\n");
					printf("[3] : Tank\nChoix personnage 1: ");
					scanf("%d",&classe1);
			        printf("Choix personnage 2: ");
			        scanf("%d",&classe2);

					if((classe1 < 1)&&(classe1 > 3) && (classe2 < 1)&&(classe2 > 3) )
						printf("Vous devez taper 1 ou 2\n");

				}while((classe1 < 1)&&(classe1 > 3) && (classe2 < 1)&&(classe2 > 3));

			    joueur1.perso1 = malloc(sizeof(t_personnage));
			    joueur1.perso2 = malloc(sizeof(t_personnage));
			  	creer_perso(classe1,joueur1.perso1);
				creer_perso(classe2,joueur1.perso2);
			    joueur1.numJoueur = 1;
			    joueur1.nbPVivant = 2;



					do{
						printf("Joueur 1: choisir une classe personnage 2 et classe personnage 2\n");
						printf("[1] : Guerrier\n");
						printf("[2] : Archer\n");
						printf("[3] : Tank\nChoix personnage 1: ");
						scanf("%d",&classe1);
				        printf("Choix personnage 2: ");
				        scanf("%d",&classe2);

						if((classe1 < 1)&&(classe1 > 3) && (classe2 < 1)&&(classe2 > 3) )
							printf("Vous devez taper 1 ou 2\n");

					}while((classe1 < 1)&&(classe1 > 3) && (classe2 < 1)&&(classe2 > 3));

			    joueur2.perso1 = malloc(sizeof(t_personnage));
			    joueur2.perso2 = malloc(sizeof(t_personnage));
					creer_perso(classe1,joueur2.perso1 );
					creer_perso(classe2,joueur2.perso2);
			    joueur2.numJoueur = 2;
			    joueur2.nbPVivant = 2;


			    /*joueur1.pv = 10;
			    joueur2.pv = 5;*/

	if(!SDL_creer_fenetre())
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
	SDL_creer_texture();

	SDL_initialisation(map,&joueur1,&joueur2);
	//initialisation(map,&joueur1,&joueur2);
	int nb = 3;
	if(nb > 0)
		nb = SDL_deplacement(joueur1, joueur2, map, nb, 1, 1);
	if(nb > 0)
		nb = SDL_deplacement(joueur1, joueur2, map, nb, 1, 1);
	if(nb > 0)
		nb = SDL_deplacement(joueur1, joueur2, map, nb, 1, 1);
	//SDL_saut(joueur1, joueur2, map, 1, 1);
	SDL_afficher_map(map);
	//int x, y;
	if( window )
	{
		int running = 1;
		while(running) {
			//SDL_GetMouseState(&x,&y);
			//printf("x:%i | y:%i\n",x,y);
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: running = 0;
					break;
					/*case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:

							break;
						}
					break;*/

					case SDL_MOUSEBUTTONDOWN:
						printf("\t x = %i et y = %i\n", e.button.x, e.button.y);
						//map[0][0] = '1';
					break;
				}
			}
			SDL_RenderClear(renderer);
			SDL_afficher_map(map);
			SDL_RenderPresent(renderer);
			SDL_Delay(16);
		}
	} else
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());

	/*	int l = 0;
	for(int i = 0; i < N*N; i++)
		printf("case %i - %i : \n - LARGEUR: borne 1: %i borne %i\n - HAUTEUR: borne 1: %i borne 2 : %i\n", SDL_map[i].i, SDL_map[i].j, SDL_map[i].largeur.borne1, SDL_map[i].largeur.borne2, SDL_map[i].hauteur.borne1, SDL_map[i].hauteur.borne2);
	*/

	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
