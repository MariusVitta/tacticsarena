#include "fonc.h"
#include "sdl_fonc.h"

int SDL_creer_fenetre(){

	/* Initialisation simple */
   	if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
   	     fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
   	     return -1;
   	 }

	/* Création de la fenêtre */

	window = SDL_CreateWindow("Necrew Arena",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

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

  SDL_Surface * imgchoix_perso = NULL;

	SDL_RWops * r_bg = SDL_RWFromFile("bg.png", "rb");
	SDL_RWops * r_case_n = SDL_RWFromFile("cn.png", "rb");
	SDL_RWops * r_case_p = SDL_RWFromFile("cp.png", "rb");
	SDL_RWops * r_case_c = SDL_RWFromFile("cc.png", "rb");
	SDL_RWops * r_case_s = SDL_RWFromFile("cs.png", "rb");
	SDL_RWops * r_obstacle = SDL_RWFromFile("obstacle.png", "rb");
	SDL_RWops * r_guerrier = SDL_RWFromFile("guerrier.png", "rb");
	SDL_RWops * r_archer = SDL_RWFromFile("archer.png", "rb");
	SDL_RWops * r_tank = SDL_RWFromFile("tank.png", "rb");

  SDL_RWops * r_choix_perso = SDL_RWFromFile("carteperso.png", "rb");

	imgbg = IMG_LoadPNG_RW(r_bg);
	imgcase_n = IMG_LoadPNG_RW(r_case_n);
	imgcase_c = IMG_LoadPNG_RW(r_case_c);
	imgcase_p = IMG_LoadPNG_RW(r_case_p);
	imgcase_s = IMG_LoadPNG_RW(r_case_s);
	imgobstacle = IMG_LoadPNG_RW(r_obstacle);
	imgguerrier = IMG_LoadPNG_RW(r_guerrier);
	imgarcher = IMG_LoadPNG_RW(r_archer);
	imgtank = IMG_LoadPNG_RW(r_tank);

  imgchoix_perso = IMG_LoadPNG_RW(r_choix_perso);

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
		fprintf(stderr, "Image obstacle non chargée : %s\n", IMG_GetError());
	if(!imgguerrier)
		fprintf(stderr, "Image guerrier non chargée : %s\n", IMG_GetError());
	if(!imgarcher)
		fprintf(stderr, "Image archer non chargée : %s\n", IMG_GetError());
	if(!imgtank)
		fprintf(stderr, "Image tank non chargée : %s\n", IMG_GetError());

  if(!imgchoix_perso)
  	fprintf(stderr, "Image choix perso non chargée : %s\n", IMG_GetError());

	bg = SDL_CreateTextureFromSurface(renderer, imgbg);
	case_n = SDL_CreateTextureFromSurface(renderer, imgcase_n);
	case_p = SDL_CreateTextureFromSurface(renderer, imgcase_p);
	case_c = SDL_CreateTextureFromSurface(renderer, imgcase_c);
	case_s = SDL_CreateTextureFromSurface(renderer, imgcase_s);
	obstacle = SDL_CreateTextureFromSurface(renderer, imgobstacle);
	guerrier = SDL_CreateTextureFromSurface(renderer, imgguerrier);
	archer = SDL_CreateTextureFromSurface(renderer, imgarcher);
	tank = SDL_CreateTextureFromSurface(renderer, imgtank);

  choix_perso = SDL_CreateTextureFromSurface(renderer, imgchoix_perso);

	SDL_FreeSurface(imgbg);
	SDL_FreeSurface(imgcase_n);
	SDL_FreeSurface(imgcase_p);
	SDL_FreeSurface(imgcase_c);
	SDL_FreeSurface(imgcase_s);
	SDL_FreeSurface(imgobstacle);
	SDL_FreeSurface(imgguerrier);
	SDL_FreeSurface(imgarcher);
	SDL_FreeSurface(imgtank);

  SDL_FreeSurface(imgchoix_perso);
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

  if(!choix_perso)
    fprintf(stderr, "Texture choix perso non créee : %s\n", SDL_GetError());

}
