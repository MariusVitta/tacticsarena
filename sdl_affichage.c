#include "fonc.h"
#include "sdl_fonc.h"

void SDL_affichage_choix_perso(){

	SDL_Rect recchoix_perso;

	int x = 75, w = (LARGEUR/5) + 5, y = 150, h = (HAUTEUR/2) + 5;

	recchoix_perso.w = w;
	recchoix_perso.h = h;
	recchoix_perso.x = x;
	recchoix_perso.y = y;

	int ximg = recchoix_perso.x + 23, yimg = recchoix_perso.y + 37;

	SDL_choix_p[0].num_choix = 1;
	SDL_choix_p[0].b.x = ximg;
	SDL_choix_p[0].b.y = yimg;

	SDL_choix_p[0].a.y = yimg + h - (37*2);
	SDL_choix_p[0].c.x = ximg + w - (23*2);

	if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

		SDL_Rect recguerrier;

		recguerrier.w = 150;
		recguerrier.h = 150;
		recguerrier.x = recchoix_perso.x + 65;
		recguerrier.y = recchoix_perso.y + 105;

	if(!SDL_RenderCopy(renderer, guerrier, NULL, &recguerrier));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

	recchoix_perso.x = recchoix_perso.x + w + 15;
	ximg = recchoix_perso.x + 23;

	SDL_choix_p[1].num_choix = 2;
	SDL_choix_p[1].b.x = ximg;
	SDL_choix_p[1].b.y = yimg;

	SDL_choix_p[1].a.y = yimg + h - (37*2);
	SDL_choix_p[1].c.x = ximg + w - (23*2);

	if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

	SDL_Rect recarcher;

	recarcher.w = 145;
	recarcher.h = 160;
	recarcher.x = recchoix_perso.x + 50;
	recarcher.y = recchoix_perso.y + 92;

	if(!SDL_RenderCopy(renderer, archer, NULL, &recarcher));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
	recchoix_perso.x = recchoix_perso.x + w + 15;
	ximg = recchoix_perso.x + 23;

	SDL_choix_p[2].num_choix = 3;
	SDL_choix_p[2].b.x = ximg;
	SDL_choix_p[2].b.y = yimg;

	SDL_choix_p[2].a.y = yimg + h - (37*2);
	SDL_choix_p[2].c.x = ximg + w - (23*2);

	if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

	SDL_Rect rectank;

	rectank.w = 165;
	rectank.h = 165;
	rectank.x = recchoix_perso.x + 50;
	rectank.y = recchoix_perso.y + 90;

	if(!SDL_RenderCopy(renderer, tank, NULL, &rectank));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

	recchoix_perso.x = recchoix_perso.x + w + 15;
	ximg = recchoix_perso.x + 23;

	SDL_choix_p[3].num_choix = 4;
	SDL_choix_p[3].b.x = ximg;
	SDL_choix_p[3].b.y = yimg;

	SDL_choix_p[3].a.y = yimg + h - (37*2);
	SDL_choix_p[3].c.x = ximg + w - (23*2);

	if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

}
void SDL_afficher_map(char map[N][N], t_joueur j1, t_joueur j2){

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
					if(strcmp(j2.perso1->nom, "Archer") == 0){
						recarcher.x = reccase_n.x - 32;
						recarcher.y = reccase_n.y - 70;

						//if(!SDL_RenderCopy(renderer, case_s, NULL, &reccase_s));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

							if(!SDL_RenderCopy(renderer, archer, NULL, &recarcher));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					else if(strcmp(j2.perso1->nom, "Guerrier") == 0){
						recguerrier.x = reccase_n.x - 10;
						recguerrier.y = reccase_n.y - 72;

						if(!SDL_RenderCopy(renderer, guerrier, NULL, &recguerrier));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					else if(strcmp(j2.perso1->nom, "Tank") == 0){
						rectank.x = reccase_n.x - 20;
						rectank.y = reccase_n.y - 85;

						if(!SDL_RenderCopy(renderer, tank, NULL, &rectank));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J2P1;
				}


				else if(map[i][j] == '1'){

					if(strcmp(j1.perso1->nom, "Archer") == 0){
						recarcher.x = reccase_n.x - 32;
						recarcher.y = reccase_n.y - 70;

						//if(!SDL_RenderCopy(renderer, case_s, NULL, &reccase_s));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

							if(!SDL_RenderCopy(renderer, archer, NULL, &recarcher));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					else if(strcmp(j1.perso1->nom, "Guerrier") == 0){
						recguerrier.x = reccase_n.x - 10;
						recguerrier.y = reccase_n.y - 72;

						if(!SDL_RenderCopy(renderer, guerrier, NULL, &recguerrier));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					else if(strcmp(j1.perso1->nom, "Tank") == 0){
						rectank.x = reccase_n.x - 20;
						rectank.y = reccase_n.y - 85;

						if(!SDL_RenderCopy(renderer, tank, NULL, &rectank));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J1P1;
				}

				else if(map[i][j] == '3'){

					if(strcmp(j1.perso2->nom, "Archer") == 0){
						recarcher.x = reccase_n.x - 32;
						recarcher.y = reccase_n.y - 70;

						//if(!SDL_RenderCopy(renderer, case_s, NULL, &reccase_s));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

							if(!SDL_RenderCopy(renderer, archer, NULL, &recarcher));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					else if(strcmp(j1.perso2->nom, "Guerrier") == 0){
						recguerrier.x = reccase_n.x - 10;
						recguerrier.y = reccase_n.y - 72;

						if(!SDL_RenderCopy(renderer, guerrier, NULL, &recguerrier));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					else if(strcmp(j1.perso2->nom, "Tank") == 0){
						rectank.x = reccase_n.x - 20;
						rectank.y = reccase_n.y - 85;

						if(!SDL_RenderCopy(renderer, tank, NULL, &rectank));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J1P2;
				}

				else if(map[i][j] == '4'){

					if(strcmp(j2.perso2->nom, "Archer") == 0){
						recarcher.x = reccase_n.x - 32;
						recarcher.y = reccase_n.y - 70;

						//if(!SDL_RenderCopy(renderer, case_s, NULL, &reccase_s));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

							if(!SDL_RenderCopy(renderer, archer, NULL, &recarcher));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					else if(strcmp(j2.perso2->nom, "Guerrier") == 0){
						recguerrier.x = reccase_n.x - 10;
						recguerrier.y = reccase_n.y - 72;

						if(!SDL_RenderCopy(renderer, guerrier, NULL, &recguerrier));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					else if(strcmp(j2.perso2->nom, "Tank") == 0){
						rectank.x = reccase_n.x - 20;
						rectank.y = reccase_n.y - 85;

						if(!SDL_RenderCopy(renderer, tank, NULL, &rectank));
							//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
					}

					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J2P2;
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
