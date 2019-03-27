#include "fonc.h"
#include "sdl_fonc.h"

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
				SDL_map[k].a.x = reccase_n.x;
				SDL_map[k].a.y = reccase_n.y + (h/2);

				SDL_map[k].c.x = reccase_n.x + w;
				SDL_map[k].c.y = reccase_n.y + (h/2);

				SDL_map[k].b.y = reccase_n.y;
				SDL_map[k].b.x = reccase_n.x + (w/2);

				SDL_map[k].d.y = reccase_n.y + ho;
				SDL_map[k].d.x = reccase_n.x + (w/2);
				k++;
			}

			else if(map[i][j] >= 'A' && map[i][j] <= 'Z'){
				if(!SDL_RenderCopy(renderer, case_p, NULL, &reccase_p));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k].type = CASE_BLEUE;
				SDL_map[k].a.x = reccase_n.x;
				SDL_map[k].a.y = reccase_n.y + (h/2);

				SDL_map[k].c.x = reccase_n.x + w;
				SDL_map[k].c.y = reccase_n.y + (h/2);

				SDL_map[k].b.y = reccase_n.y;
				SDL_map[k].b.x = reccase_n.x + (w/2);

				SDL_map[k].d.y = reccase_n.y + h;
				SDL_map[k].d.x = reccase_n.x + (w/2);
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
				SDL_map[k].a.x = reccase_n.x;
				SDL_map[k].a.y = reccase_n.y + (h/2);

				SDL_map[k].c.x = reccase_n.x + w;
				SDL_map[k].c.y = reccase_n.y + (h/2);

				SDL_map[k].b.y = reccase_n.y;
				SDL_map[k].b.x = reccase_n.x + (w/2);

				SDL_map[k].d.y = reccase_n.y + h;
				SDL_map[k].d.x = reccase_n.x + (w/2);

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
