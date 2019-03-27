#include "fonc.h"
#include "sdl_fonc.h"

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
