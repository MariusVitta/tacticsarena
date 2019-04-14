#include "define.h"

/*structure d'un sort ayant un nom,une portée,des dégats et un nombre de points d'actions pour pouvoir l'utiliser*/
typedef struct s_personnage t_personnage;


typedef struct s_equipe{

		int numEquipe;
		int nbPersoVivant;
		t_personnage * perso1;
		t_personnage * perso2;
		int client_socket;

}t_equipe;


typedef struct s_sort{

	int id;
	char * nom;
	int portee;
	int degat;
	int cd;/* cooldown*/
	int upt;/*utilisation par tour*/
  int uptm;
	int point_action;
	void (*sort)(char map[N][N], t_personnage * , t_equipe *,t_equipe *,int,int,int,int);

}t_sort;

/*structure contenant les coordonnées du personnage*/

typedef struct s_coordonnees{

	int x;
	int y;

}t_coordonnees;


typedef struct s_effet{

	char * nom;
	int duree;
	t_coordonnees cible;

}t_effet;

/*structure d'un personnage ayant un nom,une position x/y, des points de vie, des points d'actions lui permettant d'utiliser ses sorts et 4sorts*/

struct s_personnage{

	int id;
	char* nom;
	int pv;
	int pv_max;
	int pa;
	int pm;
	t_coordonnees coord;
	t_effet effets[MAX_NB_EFFET];
	t_sort * sorts[MAX_NB_SORT];

};
/*fonctions de réseau*/
int serveur (int, t_personnage *,t_equipe * , t_equipe *);
int client (int , char **);

/*affichage de tout les sorts du personnage choisi pour le equipe*/
void affichage_sort(t_personnage *);
/* affichage de la matrice */
void affichage_map(char map[N][N]);
/* fonction qui retourne le caractère du personnage i du equipe n */
char carac_perso(int ,int );
/* fonction booleenne qui renvoie vrai si la vie du personnage est inférieur ou égale à zéro */
int est_mort(t_equipe * , int );
/* mise à jour de la carte suite à une déplacement d'un equipe */
void maj(char map[N][N], t_equipe * , t_equipe * );
/*fonction d'initialisation (positionnement,création des obstacles) */
void initialisation(char matriceJeu[N][N],t_equipe * ,t_equipe * );
/* affichage des coordonnées actuelles du personnage */
void affichage_coord(t_equipe * );
/* affichage des sorts utilisable par le equipe */
void sort_uti(t_personnage * );
/*fonction de tour de jeu (se déplacer,utiliser un sort, passer son tour) */
void tour(char map[N][N],t_equipe * ,t_equipe * ,int  );
/* fonction qui teste si la case ciblé existe sur la carte temporaire et retourne les coordonnées de la case ciblée */
int existe(char mat[N][N], char , int * , int * );
/* fonction qui verifie si le equipe passé en paramètre n'a plus de personnages */
int partie_finie(t_equipe * );

void creer_effet(t_personnage *,int ,int ,int );

void suppr_sort(t_sort ** );
void suppr_perso(t_personnage ** );
void (*creer_sort(int id_sort))(char [N][N], t_personnage * , t_equipe* ,t_equipe* ,int,int ,int,int);
void creation_sorts(t_sort * sorts[]);
void creation_classes(t_personnage * persos[],t_sort * sorts[]);
t_sort * copie_sort(t_sort * sort);
t_personnage * copie_perso(t_personnage * );




/* sorts */
void armure  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void felin  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void chouette  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void attire  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void chenchen  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void bigshaq  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void diago  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void coup_zone  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void double_tape  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void petit_coup  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void ligne  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );;
void grosCoup  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void soin  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void saut  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void fuego  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );
void revitalisation  (char map[N][N], t_personnage * ,t_equipe *, t_equipe *,int ,int ,int ,int );

void portee_degat(char map[N][N], t_personnage * ,t_equipe * , t_equipe * ,int ,int ,int , int );

/* fonction déplacement case par case pour le equipe */
int deplacement(t_equipe * ,t_equipe * ,char map[N][N],int ,int  );