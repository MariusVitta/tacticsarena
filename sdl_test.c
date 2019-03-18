#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include "fonc.h"

#define LARGEUR 1300
#define HAUTEUR 850
#define N 11

SDL_Window* window = NULL;
SDL_Renderer *renderer=NULL;

SDL_Texture * bg = NULL;
SDL_Texture * case_n = NULL;
SDL_Texture * case_p = NULL;
SDL_Texture * case_s = NULL;
SDL_Texture * obstacle = NULL;
SDL_Texture * guerrier = NULL;
SDL_Texture * archer = NULL;

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
	SDL_Surface * imgcase_s = NULL;
	SDL_Surface * imgobstacle = NULL;
	SDL_Surface * imgguerrier = NULL;
	SDL_Surface * imgarcher = NULL;

	SDL_RWops * r_bg = SDL_RWFromFile("fondn.png", "rb");
	SDL_RWops * r_case_n = SDL_RWFromFile("cn.png", "rb");
	SDL_RWops * r_case_p = SDL_RWFromFile("cp.png", "rb");
	SDL_RWops * r_case_s = SDL_RWFromFile("cs.png", "rb");
	SDL_RWops * r_obstacle = SDL_RWFromFile("obstacle.png", "rb");
	SDL_RWops * r_guerrier = SDL_RWFromFile("guerrier.png", "rb");
	SDL_RWops * r_archer = SDL_RWFromFile("archer.png", "rb");

	imgbg = IMG_LoadPNG_RW(r_bg);
	imgcase_n = IMG_LoadPNG_RW(r_case_n);
	imgcase_p = IMG_LoadPNG_RW(r_case_p);
	imgcase_s = IMG_LoadPNG_RW(r_case_s);
	imgobstacle = IMG_LoadPNG_RW(r_obstacle);
	imgguerrier = IMG_LoadPNG_RW(r_guerrier);
	imgarcher = IMG_LoadPNG_RW(r_archer);

	if(!imgbg)
		fprintf(stderr, "Image background non chargée : %s\n", IMG_GetError());
	if(!imgcase_n)
		fprintf(stderr, "Image case normale non chargée : %s\n", IMG_GetError());
	if(!imgcase_p)
		fprintf(stderr, "Image case possible non chargée : %s\n", IMG_GetError());
	if(!imgcase_s)
		fprintf(stderr, "Image case sélectionnée non chargée : %s\n", IMG_GetError());
	if(!imgobstacle)
		fprintf(stderr, "Image obstacle normale non chargée : %s\n", IMG_GetError());
	if(!imgguerrier)
		fprintf(stderr, "Image guerrier normale non chargée : %s\n", IMG_GetError());
	if(!imgarcher)
		fprintf(stderr, "Image archer normale non chargée : %s\n", IMG_GetError());

	bg = SDL_CreateTextureFromSurface(renderer, imgbg);
	case_n = SDL_CreateTextureFromSurface(renderer, imgcase_n);
	case_p = SDL_CreateTextureFromSurface(renderer, imgcase_p);
	case_s = SDL_CreateTextureFromSurface(renderer, imgcase_s);
	obstacle = SDL_CreateTextureFromSurface(renderer, imgobstacle);
	guerrier = SDL_CreateTextureFromSurface(renderer, imgguerrier);
	archer = SDL_CreateTextureFromSurface(renderer, imgarcher);

	SDL_FreeSurface(imgbg);
	SDL_FreeSurface(imgcase_n);
	SDL_FreeSurface(imgcase_p);
	SDL_FreeSurface(imgcase_s);
	SDL_FreeSurface(imgobstacle);
	SDL_FreeSurface(imgguerrier);
	SDL_FreeSurface(imgarcher);

	if(!bg)
		fprintf(stderr, "Texture background non créee : %s\n", SDL_GetError());
	if(!case_n)
		fprintf(stderr, "Texture case normale non créee : %s\n", SDL_GetError());
	if(!case_p)
		fprintf(stderr, "Texture case possible non créee : %s\n", SDL_GetError());
	if(!case_s)
		fprintf(stderr, "Texture case sélectionnée non créee : %s\n", SDL_GetError());
	if(!obstacle)
		fprintf(stderr, "Texture obstacle non créee : %s\n", SDL_GetError());
	if(!guerrier)
		fprintf(stderr, "Texture guerrier non créee : %s\n", SDL_GetError());
	if(!archer)
		fprintf(stderr, "Texture archer non créee : %s\n", SDL_GetError());


}

void SDL_afficher_map(char map[N][N]){

	SDL_Rect recbg;

	if(!SDL_QueryTexture(bg, NULL, NULL, &recbg.w, &recbg.h))
		fprintf(stderr, "Texture non chargée : %s\n", SDL_GetError());

	if(!SDL_RenderCopy(renderer, bg, NULL, NULL))
		fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

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

	SDL_Rect recobstacle;
	int xo = x+3, yo = y-38;//48

	recobstacle.w = w-5;
	recobstacle.h = h + 40;//50
	recobstacle.x = xo;
	recobstacle.y = yo;

	SDL_Rect reccase_s;
	int ws = w - 15, hs = h - 15;

	reccase_s.w = ws;
	reccase_s.h = hs;

	SDL_Rect recguerrier;

	recguerrier.w = 100;
	recguerrier.h = 100;

	SDL_Rect recarcher;

	recarcher.w = 100;
	recarcher.h = 100;


	/*for( i = N - 1; i >= 0; i--){
		if(!SDL_RenderCopy(renderer, case_n, NULL, &reccase_n))
				fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			reccase_n.y = reccase_n.y + (h/2) + 5;
			reccase_n.x = reccase_n.x - (w/2) - 10;
	}

	reccase_n.x = x;
	reccase_n.y = y;
	for( i = 0; i < 11; i++){
		if(!SDL_RenderCopy(renderer, case_n, NULL, &reccase_n))
				fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			reccase_n.y = reccase_n.y + (h/2) + 5;
			reccase_n.x = reccase_n.x + (w/2) + 10;
	}*/

	for(i = 0; i < N; i++){
		for(j = N-1; j >= 0 ; j--){


			if(map[i][j] == 'o'){
				if(!SDL_RenderCopy(renderer, obstacle, NULL, &recobstacle))
					fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k++].type = OBSTACLE;
			}

			else if(map[i][j] >= 'A' && map[i][j] <= 'Z'){
				if(!SDL_RenderCopy(renderer, case_p, NULL, &reccase_p))
					fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k++].type = CASE_BLEUE;
			}

			else{

				if(!SDL_RenderCopy(renderer, case_n, NULL, &reccase_n))
						fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k].type = CASE_GRISE;

				if (map[i][j] == '2'){

					reccase_s.x = reccase_n.x + 7;
					reccase_s.y = reccase_n.y + 7;
					recarcher.x = reccase_n.x - 30;
					recarcher.y = reccase_n.y - 72;

					if(!SDL_RenderCopy(renderer, case_s, NULL, &reccase_s))
						fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

					if(!SDL_RenderCopy(renderer, archer, NULL, &recarcher))
						fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J2;

				}

				else if(map[i][j] == '1'){

					recguerrier.x = reccase_n.x - 10;
					recguerrier.y = reccase_n.y - 72;

					if(!SDL_RenderCopy(renderer, guerrier, NULL, &recguerrier))
						fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

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

			recobstacle.y = recobstacle.y + (h/2) + 3;
			recobstacle.x = recobstacle.x - (w/2) - 8;
		}
	  	//printf("x = %i et y = %i\n", reccase_n.x, reccase_n.y);
		reccase_n.y = y + (((h/2) + 3)*(i+1));
		reccase_n.x = x + (((w/2) + 8)*(i+1));

		reccase_p.y = y + (((h/2) + 3)*(i+1));
		reccase_p.x = x + (((w/2) + 8)*(i+1));

		recobstacle.y = yo + (((h/2) + 3)*(i+1));
		recobstacle.x = xo + (((w/2) + 8)*(i+1));

		//printf("x = %i et y = %i\n", reccase_n.x, reccase_n.y);
	}


}

int main (int argc, char** argv){


	/*char map[N][N] = {{'.','.','.','.','.','.','.','.','.','.','.'},

				{'.','.','.','.','.','.','.','.','.','o','A'},

				{'.','.','.','o','.','.','.','.','.','A','.'},

				{'.','.','.','.','A','.','o','.','A','.','.'},

				{'.','.','.','.','.','A','1','A','.','.','1'},

				{'.','.','.','.','.','.','2','o','.','o','1'},

				{'.','.','o','.','.','A','.','A','.','.','.'},

				{'.','.','o','.','A','.','.','.','A','.','.'},

				{'.','.','.','A','.','.','.','o','o','A','.'},

				{'.','.','A','.','.','.','.','o','o','.','A'},

				{'.','A','.','.','.','.','.','.','.','.','.'}};*/

	int i, j, classe1, classe2;
    int num_j = 1;
	t_personnage personnage1,personnage2;

	do{
		printf("Joueur 1: choisir une classe\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\nChoix:");
		scanf("%d",&classe1);

		if((classe1 != 1)&&(classe1 != 2))
			printf("Vous devez taper 1 ou 2\n");

	}while((classe1 != 1)&&(classe1 != 2));

	do{
		printf("Joueur 2: choisir une classe\n");
		printf("[1] : Guerrier\n");
		printf("[2] : Archer\nChoix:");


		scanf("%d",&classe2);

		if((classe2 != 1)&&(classe2 != 2))
			printf("Vous devez taper 1 ou 2\n");

	}while((classe2 != 1)&&(classe2 != 2));

	personnage1 = creer_perso(classe1,&personnage1);
	personnage2 = creer_perso(classe2,&personnage2);
    personnage1.pv = 10;
    personnage2.pv = 5;

	initialisation(map,&personnage1,&personnage2);

	if(!SDL_creer_fenetre())
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
	SDL_creer_texture();
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
					case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:
            						SDL_RenderPresent(renderer);
							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:
						printf("x = %i; y = %i\n", e.button.x, e.button.y);
					break;
				}
			}
		}
	} else
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());

	/*for(int i = 0; i < N*N; i++)
		printf("case %i - %i\n", SDL_map[i].i, SDL_map[i].j);*/

	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
