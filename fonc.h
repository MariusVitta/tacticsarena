#define N 11

/*structure d'un sort ayant un nom,une portée,des dégats et un nombre de points d'actions pour pouvoir l'utiliser*/

typedef struct s_sort{

	char * nom;
	int portee;
	int degat;
	int cd;/* cooldown*/
	int upt;/*utilisation par tour*/
	int point_action;

}t_sort;


/*structure contenant les coordonnées du personnage*/

typedef struct s_coordonnees{

	int x;
	int y;

}t_coordonnees;


/*structure d'un personnage ayant un nom,une position x/y, des points de vie, des points d'actions lui permettant d'utiliser ses sorts et 4sorts*/

typedef struct s_personnage{

	char* nom;
	int pv;
	int pv_max;
	int pa;
	t_coordonnees coord;
	t_sort s1,s2,s3,s4;

}t_personnage;
/*fonction qui crée un personnage(affection des sorts,vie,points d'actions pour le type de personnage choisi) */
t_personnage creer_perso(int,t_personnage);
/*affichage de tout les sorts du personnage choisi pour le joueur*/
void affichage_sort(t_personnage);
/* affichage de la matrice */
void affichage_map(char map[N][N]);
/* fonction booleenne qui renvoie vrai si la vie du personnage est inférieur ou égale à zéro */
int est_mort(t_personnage);
/* mise à jour de la carte suite à une déplacement d'un joueur */
void maj(char map[N][N], t_personnage perso1, t_personnage perso2);
/* fonction déplacement case par case pour le joueur */
int deplacement(t_personnage * j1,t_personnage *j2,char map[N][N],int  n ,int nbj);

int saut(t_personnage * j1,char mat[N][N]);
/*fonction d'initialisation (positionnement,création des obstacles) */
void initialisation(char matriceJeu[N][N],t_personnage * perso1,t_personnage * perso2);
/* affichage des coordonnées actuelles du personnage */
void affichage_coord(t_personnage perso);
/* affichage des sorts utilisable par le joueur */
void sort_uti(t_personnage perso);
/*fonction de tour de jeu (se déplacer,utiliser un sort, passer son tour) */
int tour(char map[N][N],t_personnage *j1,t_personnage *j2 ,int nb_j);
 
void diago(char map[N][N], t_personnage perso1, t_personnage * perso2);

void coup_zone(char map[N][N],t_personnage j1,t_personnage j2);
