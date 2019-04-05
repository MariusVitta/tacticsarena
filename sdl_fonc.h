#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#ifndef LARGEUR
#define LARGEUR 1340
#endif
#ifndef HAUTEUR
#define HAUTEUR 800
#endif
#ifndef N
#define N 11
#endif
#ifndef NBPERSOS
#define NBPERSOS 4
#endif

extern SDL_Window* window;
extern SDL_Renderer *renderer;
extern SDL_Texture * texte;

extern SDL_Texture * bg;
extern SDL_Texture * accueil;
extern SDL_Texture * accueil1;
extern SDL_Texture * case_n;
extern SDL_Texture * case_p;
extern SDL_Texture * case_c;
extern SDL_Texture * case_s;
extern SDL_Texture * obstacle;
extern SDL_Texture * guerrier1;
extern SDL_Texture * archer1;
extern SDL_Texture * tank1;
extern SDL_Texture * druide1;

extern SDL_Texture * guerrier2;
extern SDL_Texture * archer2;
extern SDL_Texture * tank2;
extern SDL_Texture * druide2;

extern SDL_Texture * idguerrier1;
extern SDL_Texture * idarcher1;
extern SDL_Texture * idtank1;
extern SDL_Texture * iddruide1;

extern SDL_Texture * idguerrier2;
extern SDL_Texture * idarcher2;
extern SDL_Texture * idtank2;
extern SDL_Texture * iddruide2;

extern SDL_Texture * choix_perso;

extern TTF_Font * police;

extern SDL_Color noir;
extern SDL_Color blanc;
extern SDL_Color orange;
extern SDL_Color rouge;

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
void SDL_afficher_bg();
void SDL_afficher_acceuil();
void SDL_afficher_map(char map[N][N], t_joueur j1, t_joueur j2);
void SDL_afficher_message(char * message, int x, int y, char * police, int taille, char couleur, char style);
int SDL_creer_fenetre();
void SDL_creer_texture();
void SDL_afficher_sort(char * nom, int xsort, int ysort);
SDL_Texture * SDL_charger_image (char * image);
void SDL_ecrire_texte(char * chaine, char * police_ec, int taille, char color, char style);
float eq_droite(t_coord p1, t_coord p2, int x);
int dans_case(t_coord a, t_coord b, t_coord c, t_coord d, int x, int y);
int acces_possible(int x, int y, int * ymap, int * xmap);
int acces_choix_perso(int x, int y, int * classe);
void SDL_affichage_choix_perso(int num_j);
void SDL_afficher_perso_choisi(t_joueur joueur1, t_joueur joueur2);
void SDL_choix_perso(t_joueur *joueur1, t_joueur *joueur2);

void SDL_initialisation(char matriceJeu[N][N],t_joueur * joueur1,t_joueur * joueur2);
int SDL_deplacement(t_joueur j1,t_joueur j2,char map[N][N],int  n ,int num_j,int numero_perso );
int SDL_saut(t_joueur j1,t_joueur j2,char map[N][N],int num_j,int numero_perso);
