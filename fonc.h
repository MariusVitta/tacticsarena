#define N 11

typedef struct s_sort{

	char * nom;
	int portee;
	int degat;
	int point_action;

}t_sort;

typedef struct s_personnage{

	char* nom;
	int pv;
	int pa;
	t_sort s1,s2,s3,s4;

}t_personnage;

t_personnage creer_perso(int,t_personnage);
void affichage_sort(t_personnage);
void affichage_map(char map[N][N]);

