#include "fonc.h"
#include "sdl_fonc.h"

void SDL_ecrire_texte(char * chaine, char * police_ec, int taille, char color, char style){

	SDL_Surface * tex_texte;

  	if((police = TTF_OpenFont(police_ec, taille)) == NULL){
  		fprintf(stderr, "erreur chargement font\n");
  	}

  	switch(style){
  		case 'N':
  			TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
  		break;
  		case 'G':
  			TTF_SetFontStyle(police, TTF_STYLE_BOLD);
  		break;

  		case 'I':
  			TTF_SetFontStyle(police, TTF_STYLE_ITALIC);
  		break;

  		case 'S':
  			TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);
  		break;
  	}

  	SDL_Color couleur;
  	switch(color){

  		case 'b':
  			couleur = blanc;
  		break;
  		case 'n':
  			couleur = noir;
  		break;
  		case 'o':
  			couleur = orange;
  		break;
  		case 'r':
  			couleur = rouge;
  		break;
  		case 'j':
  			couleur = jaune;
  		break;
  		case 'R':
  			couleur = rouge2;
  		break;
  	}

  	tex_texte = TTF_RenderUTF8_Blended(police, chaine, couleur);
  	if(!tex_texte){
  		fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
  	}
  	texte = SDL_CreateTextureFromSurface(renderer, tex_texte);

    SDL_FreeSurface(tex_texte); /* on a la texture, plus besoin du texte */
  	if(!texte){
  		fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
  	}
}

void effet_clignotement(t_joueur j1, t_joueur j2, t_personnage * perso){

	char c = map[perso->coord.y][perso->coord.x];

	int i;

	for(i = 0; i < 4; i++){
		map[perso->coord.y][perso->coord.x] = '.';
		SDL_RenderClear(renderer);
		SDL_afficher_map(map, j1, j2);
		SDL_RenderPresent(renderer);
		SDL_Delay(30);
		map[perso->coord.y][perso->coord.x] = c;
		SDL_RenderClear(renderer);
		SDL_afficher_map(map, j1, j2);
		SDL_RenderPresent(renderer);
		SDL_Delay(30);
	}
}

t_case recherche_case(int i, int j){

	int x;
	for(x = 0; x < N * N; x++){
		if(SDL_map[x].i == i && SDL_map[x].j == j)
			return SDL_map[x];
	}
}

int acces_choix_perso(int x, int y, int * classe){

	for(int i = 0; i < NBPERSOS; i++){
		if(x > SDL_choix_p[i].b.x && y > SDL_choix_p[i].b.y && x < SDL_choix_p[i].c.x && y < SDL_choix_p[i].a.y){
			* classe = SDL_choix_p[i].num_choix;
			return 1;
		}
	}
	return 0;
}

float eq_droite(t_coord p1, t_coord p2, int x){

	float m = ((float)p2.y - (float)p1.y)/((float)p2.x - (float)p1.x);
	float p = (float)p1.y - (m * (float)p1.x);
	float y = (m * x) + p;
	return y;
}

int dans_case(t_coord a, t_coord b, t_coord c, t_coord d, int x, int y){

	if((float)y >= eq_droite(a,b,x) && (float)y >= eq_droite(b,c,x) && (float)y <= eq_droite(a,d,x) && (float)y <= eq_droite(d,c,x))
		return 1;
	return 0;
}

/* Verifie s'il est possible d'acceder à une case*/
int acces_possible(int x, int y, int * ymap, int * xmap){

	int i;
	for(i = 0; i < N*N; i++){

		if(SDL_map[i].type == OBSTACLE){
			//if((x >= SDL_map[i].a.x && x <= SDL_map[i].c.x) && (y >= SDL_map[i].b.y && y <= SDL_map[i].d.y))
			if(dans_case(SDL_map[i].a, SDL_map[i].b, SDL_map[i].c, SDL_map[i].d, x, y))
				return 0;
		}

		else if(SDL_map[i].type == CASE_GRISE){
			if(dans_case(SDL_map[i].a, SDL_map[i].b, SDL_map[i].c, SDL_map[i].d, x, y))
				//printf("x1 case p = %i - x2 = %i\ny1 = %i - y2 = %i\n", SDL_map[i].largeur.borne1,SDL_map[i].largeur.borne2,SDL_map[i].hauteur.borne1,SDL_map[i].hauteur.borne2 );
				return 0;
		}

		else if(SDL_map[i].type == CASE_BLEUE){
			if(dans_case(SDL_map[i].a, SDL_map[i].b, SDL_map[i].c, SDL_map[i].d, x, y)){
				* ymap = SDL_map[i].i;
				* xmap = SDL_map[i].j;
				//printf("x1 case bleue = %i - x2 = %i\ny1 = %i - y2 = %i\n", SDL_map[i].largeur.borne1,SDL_map[i].largeur.borne2,SDL_map[i].hauteur.borne1,SDL_map[i].hauteur.borne2 );
				return 1;
			}
		}
	}
	return 0;
}
