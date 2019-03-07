#define N 11

/*structure d'un sort ayant un nom,une portée,des dégats et un nombre de points d'actions pour pouvoir l'utiliser*/

typedef struct s_sort{

	char * nom;
	int portee;
	int degat;
	int point_action;

}t_sort;


/*structure contenant les coordonnées du personnage*/

typedef struct s_coordonnees{
	
	double x;
	double y;

}t_coordonnees;


/*structure d'un personnage ayant un nom,une position x/y, des points de vie, des points d'actions lui permettant d'utiliser ses sorts et 4sorts*/

typedef struct s_personnage{

	char* nom;
	int pv;
	int pa;
	t_coordonnees coord;
	t_sort s1,s2,s3,s4;

}t_personnage;

t_personnage creer_perso(int,t_personnage);
void affichage_sort(t_personnage);                   
void affichage_map(char map[N][N]);
int est_mort(t_personnage);
void maj(char map[N][N], t_personnage perso1, t_personnage perso2);
int deplacement(t_personnage * j1,t_personnage j2);
void initialisation(char matriceJeu[N][N],t_personnage * perso1,t_personnage * perso2);
void affichage_coord(t_personnage perso);


typedef enum {NORD,SUD,EST,OUEST}t_direction;

int direction(int * x, int * y, t_direction dir, int nb_cases);


