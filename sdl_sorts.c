#include "fonc.h"
#include "sdl_fonc.h"

int SDL_saut(t_joueur j1,t_joueur j2,char map[N][N],int num_j,int numero_perso){

	char point[N][N];/*matrice affichant les possibilités de jeu*/
	int i, j, g,car=0, coordi = 0, coordj = 0;
	char choix;

    t_personnage * temp;
    if(numero_perso == 1 ){
        temp = j1.perso1;
    }
    else{
        temp = j1.perso2;
    }
    int dist=temp->s1.portee;

	/* recopie matrice dans la matrice point qui affiche la portee */

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			point[i][j] = map[i][j];
		}
	}


	i = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le haut
	for( ; i >= 0  && ( dist >= 0 ) ; i--, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					//verifie si il y a un obstacle ou un joueur à l'emplacement
					if(point[i][j] == '.'){
						point[i][j] = 'A' + car;
						car++;
						if('A' + car == 'o')
							car++;
					}
				}
			}
		}
	}

	dist=temp->s1.portee;
	g = temp->coord.y;
	j = temp->coord.x - dist ;
	//affiche la porter vers le bas
	for( ; g < N  && ( dist >= 0 ) ; g++, dist--){
		j = temp->coord.x - dist ;
		for( ;(j <= temp->coord.x + dist) ; j++){
			if(j>=0){
				if(j<N){
					if(point[g][j] == '.'){
						//ne pas repasser une seconde fois sur la ligne du joueur
						if(g != temp->coord.y){
								point[g][j] = 'A' + car;
								car ++;
						}
					}
				}
			}
		}
	}

	/* affichage */
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, j1, j2);
	SDL_RenderPresent(renderer);

	int x = 0, y = 0;

	do{
		SDL_Event e;
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_MOUSEBUTTONDOWN){
				x = e.button.x;
				y = e.button.y;
			}
		}

	} while(!acces_possible(x, y, &coordi, &coordj));

	point[coordi][coordj] = 'x';
	SDL_RenderClear(renderer);
	SDL_afficher_map(point, j1, j2);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);


	temp->coord.x = coordj;

	temp->coord.y = coordi;



	if(num_j==1){
		maj(map,j1,j2);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map, j1, j2);
		SDL_RenderPresent(renderer);
	}
	else{
		maj(map,j2,j1);
		SDL_RenderClear(renderer);
		SDL_afficher_map(map, j1, j2);
		SDL_RenderPresent(renderer);
	}

	return 1;
}
