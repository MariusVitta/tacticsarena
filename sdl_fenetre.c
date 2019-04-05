#include "fonc.h"
#include "sdl_fonc.h"

SDL_Texture * SDL_charger_image (char * image){

  SDL_Texture * texture;
  SDL_Surface * img = NULL;
  SDL_RWops * r_rwops = SDL_RWFromFile(image, "rb");
  img = IMG_LoadPNG_RW(r_rwops);

  if(!img)
    fprintf(stderr, "Image non chargée : %s\n", IMG_GetError());

  texture = SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);

  if(!texture)
    fprintf(stderr, "Texture background non créee : %s\n", SDL_GetError());

  return texture;
}

int SDL_creer_fenetre(){

	/* Initialisation simple */
   	if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
   	     fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
   	     return -1;
   	 }
  if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
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

	bg = SDL_charger_image("Image/bg.png");
  accueil = SDL_charger_image("Image/accueil.png");
  accueil1 = SDL_charger_image("Image/accueil1.png");
	case_n = SDL_charger_image("Image/cn.png");
	case_p = SDL_charger_image("Image/cp.png");
	case_c = SDL_charger_image("Image/cc.png");
	case_s = SDL_charger_image("Image/cs.png");
	obstacle = SDL_charger_image("Image/obstacle.png");

	guerrier1 = SDL_charger_image("Image/guerrier1.png");
	archer1 = SDL_charger_image("Image/archer1.png");
	tank1 = SDL_charger_image("Image/tank1.png");
  druide1 = SDL_charger_image("Image/druide1.png");

  guerrier2 = SDL_charger_image("Image/guerrier2.png");
	archer2 = SDL_charger_image("Image/archer2.png");
	tank2 = SDL_charger_image("Image/tank2.png");
  druide2 = SDL_charger_image("Image/druide2.png");

  idguerrier1 = SDL_charger_image("Image/idguerrier1.png");
	idarcher1 = SDL_charger_image("Image/idarcher1.png");
	idtank1 = SDL_charger_image("Image/idtank1.png");
  iddruide1 = SDL_charger_image("Image/iddruide1.png");

  idguerrier2 = SDL_charger_image("Image/idguerrier2.png");
	idarcher2 = SDL_charger_image("Image/idarcher2.png");
	idtank2 = SDL_charger_image("Image/idtank2.png");
  iddruide2 = SDL_charger_image("Image/iddruide2.png");

  choix_perso = SDL_charger_image("Image/carteperso2.png");


}
