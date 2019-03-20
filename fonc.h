#define N 11

/*structure d'un sort ayant un nom,une portée,des dégats et un nombre de points d'actions pour pouvoir l'utiliser*/

typedef struct s_sort{

	char * nom;
	int portee;
	int degat;
	int cd;/* cooldown*/
	int upt;/*utilisation par tour*/
    int uptm;
	int point_action;

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


typedef struct s_liste_effet{

	t_effet e1,e2,e3,e4;

}t_liste_effet;

/*structure d'un personnage ayant un nom,une position x/y, des points de vie, des points d'actions lui permettant d'utiliser ses sorts et 4sorts*/

typedef struct s_personnage{

	char* nom;
	int pv;
	int pv_max;
	int pa;
	int pm;
	t_coordonnees coord;
	t_liste_effet effets;
	t_sort s1,s2,s3,s4;

}t_personnage;

typedef struct s_joueur{

		int numJoueur;
		int nbPVivant;
		t_personnage * perso1;
		t_personnage * perso2;

}t_joueur;



/*fonction qui crée un personnage(affection des sorts,vie,points d'actions pour le type de personnage choisi) */
void creer_perso(int,t_personnage *);
/*affichage de tout les sorts du personnage choisi pour le joueur*/
void affichage_sort(t_personnage);
/* affichage de la matrice */
void affichage_map(char map[N][N]);
/* fonction booleenne qui renvoie vrai si la vie du personnage est inférieur ou égale à zéro */
int est_mort(t_personnage *);
/* mise à jour de la carte suite à une déplacement d'un joueur */
void maj(char map[N][N], t_joueur joueur1, t_joueur joueur2);
/*fonction d'initialisation (positionnement,création des obstacles) */
void initialisation(char matriceJeu[N][N],t_joueur * joueur1,t_joueur * joueur2);
/* affichage des coordonnées actuelles du personnage */
void affichage_coord(t_joueur joueur);
/* affichage des sorts utilisable par le joueur */
void sort_uti(t_personnage perso);
/*fonction de tour de jeu (se déplacer,utiliser un sort, passer son tour) */
int tour(char map[N][N],t_joueur joueur1,t_joueur joueur2,int nb_j,int numero_perso );
/* fonction qui teste si la case ciblé existe sur la carte temporaire et retourne les coordonnées de la case ciblée */
int existe(char mat[N][N], char choix, int * x, int * y);

void creer_effet(t_personnage * p,int effet_voulu,int x,int y);

/* sorts */
void armure(t_personnage *p);
void felin(t_personnage *p);
void chouette(t_personnage *p);
void attire(char map[N][N], t_personnage * perso1, t_personnage * perso2);
void chenchen(char map[N][N],t_personnage * j1,t_personnage  * j2);
void bigshaq(char map[N][N], t_personnage * perso1, t_personnage * perso2);
void diago(char map[N][N], t_personnage * perso1,t_joueur j2,int numj);
void coup_zone(char map[N][N],t_personnage *perso1,t_joueur j2,int numj);
void double_tape(char map[N][N],t_personnage *perso1,t_joueur j2,int numj);
void petit_coup(char map[N][N],t_personnage * perso1,t_joueur j2,int numj);
void ligne(char map[N][N], t_personnage * perso1,t_joueur j2,int numj);
void grosCoup(char map[N][N], t_personnage * perso1, t_joueur j2,int numj);
void soin(t_personnage * perso1);
int saut(t_joueur j1,t_joueur j2,char map[N][N],int nbj,int numero_perso );
/* fonction déplacement case par case pour le joueur */
int deplacement(t_joueur j1,t_joueur j2,char map[N][N],int  n ,int nbj,int numero_perso );
