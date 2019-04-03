#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#ifndef LARGEUR
#define LARGEUR 1300
#endif
#ifndef HAUTEUR
#define HAUTEUR 850
#endif
#ifndef N
#define N 11
#endif
#ifndef NBPERSOS
#define NBPERSOS 4
#endif

extern SDL_Window* window;
extern SDL_Renderer *renderer;

extern SDL_Texture * bg;
extern SDL_Texture * case_n;
extern SDL_Texture * case_p;
extern SDL_Texture * case_c;
extern SDL_Texture * case_s;
extern SDL_Texture * obstacle;
extern SDL_Texture * guerrier;
extern SDL_Texture * archer;
extern SDL_Texture * tank;

extern SDL_Texture * choix_perso;

typedef enum {CASE_GRISE, CASE_BLEUE, OBSTACLE, J1P1, J1P2, J2P1, J2P2}t_type_case;

typedef struct s_coord{
	int x, y;
}t_coord;

typedef struct s_case {
	t_type_case type;
	int i;
	int j;
	t_coord a;
	t_coord b;
	t_coord c;
	t_coord d;
}t_case;

typedef struct s_choix_perso{
	int num_choix;
	t_coord a;
	t_coord b;
	t_coord c;
}t_choix;

char map[N][N];
t_case SDL_map[N * N];
t_choix SDL_choix_p[NBPERSOS];

void SDL_choix_perso();
void SDL_afficher_map(char map[N][N], t_joueur j1, t_joueur j2);
int SDL_creer_fenetre();
void SDL_creer_texture();
float eq_droite(t_coord p1, t_coord p2, int x);
int dans_case(t_coord a, t_coord b, t_coord c, t_coord d, int x, int y);
int acces_possible(int x, int y, int * ymap, int * xmap);
int acces_choix_perso(int x, int y, int * classe);
void SDL_affichage_choix_perso();
void SDL_choix_perso(t_joueur *joueur1, t_joueur *joueur2);

void SDL_initialisation(char matriceJeu[N][N],t_joueur * joueur1,t_joueur * joueur2);
int SDL_deplacement(t_joueur j1,t_joueur j2,char map[N][N],int  n ,int num_j,int numero_perso );
int SDL_saut(t_joueur j1,t_joueur j2,char map[N][N],int num_j,int numero_perso);
