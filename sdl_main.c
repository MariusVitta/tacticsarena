#include "fonc.h"
#include "sdl_fonc.h"

SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture * bg = NULL;
SDL_Texture * case_n = NULL;
SDL_Texture * case_p = NULL;
SDL_Texture * case_c = NULL;
SDL_Texture * case_s = NULL;
SDL_Texture * obstacle = NULL;
SDL_Texture * guerrier = NULL;
SDL_Texture * archer = NULL;
SDL_Texture * tank = NULL;

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

				int i, j, classe1, classe2,nb_tour = 1,mort1 = 0,mort2 = 0;
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
	//SDL_saut(joueur1, joueur2, map, 1, 1);*/
	int x = 0, y = 0;
	SDL_afficher_map(map);

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

	/*for(int i = 0; i < N*N; i++)
		printf("case %i - %i : a(%i;%i)  b(%i;%i)  c(%i;%i) d(%i;%i)\n", SDL_map[i].i, SDL_map[i].j, SDL_map[i].a.x,SDL_map[i].a.y, SDL_map[i].b.x, SDL_map[i].b.y, SDL_map[i].c.x, SDL_map[i].c.y, SDL_map[i].d.x, SDL_map[i].d.y);
	*/
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
