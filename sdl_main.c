#include "fonc.h"
#include "sdl_fonc.h"

SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture * texte = NULL;
SDL_Texture * bg = NULL;
SDL_Texture * accueil = NULL;
SDL_Texture * accueil1 = NULL;
SDL_Texture * case_n = NULL;
SDL_Texture * case_p = NULL;
SDL_Texture * case_c = NULL;
SDL_Texture * case_s = NULL;
SDL_Texture * obstacle = NULL;
/*Texture joueur 1*/
SDL_Texture * guerrier1 = NULL;
SDL_Texture * archer1 = NULL;
SDL_Texture * tank1 = NULL;
SDL_Texture * druide1 = NULL;
/*Texture joueur 2*/
SDL_Texture * guerrier2 = NULL;
SDL_Texture * archer2 = NULL;
SDL_Texture * tank2 = NULL;
SDL_Texture * druide2 = NULL;

/*Texture id joueur 1*/
SDL_Texture * idguerrier1 = NULL;
SDL_Texture * idarcher1 = NULL;
SDL_Texture * idtank1 = NULL;
SDL_Texture * iddruide1 = NULL;
/*Texture id joueur 2*/
SDL_Texture * idguerrier2 = NULL;
SDL_Texture * idarcher2 = NULL;
SDL_Texture * idtank2 = NULL;
SDL_Texture * iddruide2 = NULL;

SDL_Texture * choix_perso = NULL;

TTF_Font * police = NULL;

/*Liste de couleur*/

SDL_Color noir = {0, 0, 0};
SDL_Color blanc = {255, 255, 255};
SDL_Color orange = {204, 102, 0};
SDL_Color rouge = {139, 0, 0};

int main (int argc, char** argv){


	char map[N][N] = {{'.','.','.','.','.','.','.','.','.','.','.'},
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


	t_joueur joueur1,joueur2;

	if(!SDL_creer_fenetre())
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
	SDL_creer_texture();

	SDL_afficher_acceuil();

	//SDL_affichage_choix_perso();
	//SDL_Delay(5000);
	SDL_choix_perso(&joueur1, &joueur2);
	SDL_initialisation(map,&joueur1,&joueur2);
	//initialisation(map,&joueur1,&joueur2);
	/*int nb = 3;
	if(nb > 0)
		nb = SDL_deplacement(joueur1, joueur2, map, nb, 1, 1);
	if(nb > 0)
		nb = SDL_deplacement(joueur1, joueur2, map, nb, 1, 1);
	if(nb > 0)
		nb = SDL_deplacement(joueur1, joueur2, map, nb, 1, 1);
	//SDL_saut(joueur1, joueur2, map, 1, 1);*/
	int x = 0, y = 0;
	SDL_afficher_message("Go!", 519, 306, "Police/RunDemo.ttf", 110, 'r', 'N');
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);

	//SDL_affichage_choix_perso(1);


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
						x = e.button.x;
						y = e.button.y;

						printf("x = %i - y = %i\n", x, y);

					break;
				}
			}
			SDL_RenderClear(renderer);
			SDL_afficher_map(map, joueur1, joueur2);
			//SDL_affichage_choix_perso(2);
			SDL_RenderPresent(renderer);
		}
	} else
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());

	/*for(int i = 0; i < N*N; i++)
		printf("case %i - %i : a(%i;%i)  b(%i;%i)  c(%i;%i) d(%i;%i)\n", SDL_map[i].i, SDL_map[i].j, SDL_map[i].a.x,SDL_map[i].a.y, SDL_map[i].b.x, SDL_map[i].b.y, SDL_map[i].c.x, SDL_map[i].c.y, SDL_map[i].d.x, SDL_map[i].d.y);
	*/

	SDL_DestroyRenderer(renderer);
  	SDL_DestroyWindow(window);
	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
  	SDL_Quit();

	return EXIT_SUCCESS;
}
