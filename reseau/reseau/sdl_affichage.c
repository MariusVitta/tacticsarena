#include "fonc.h"
#include "sdl_fonc.h"

void afficher_sort(t_personnage * perso, int select){// -1 si aucune case n'est selectionnée

	SDL_Rect recsort;

	//if(SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255));
	//if(SDL_RenderFillRect(renderer, &recsort));

	/*RAJOUTER LE BOUTON 'x' pour annuler*/

	recsort.h = 310;
	recsort.w = 660;
	recsort.x = (LARGEUR/2) - (recsort.w/2);
	recsort.y = (HAUTEUR/2) - (recsort.h/2);
	if(!SDL_RenderCopy(renderer, cadresort, NULL, &recsort));

	int i, j, k = 0, y;

	if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255));
	SDL_afficher_message("ÌListe-des-sortsÍ", recsort.x + (recsort.w/2) - 145, recsort.y + 10, "Police/yorkwhiteletter.ttf", 50, 'r', 'N');

	recsort.w = (recsort.w/4) - 13;
	recsort.y = recsort.y + recsort.h - (recsort.h/2) - 70;
	recsort.h = (recsort.h/2) + 50;
	recsort.x += 10;

	printf("Largeur = %i\n", recsort.w);

	char carac[5][50];
	char p[20];


	y = recsort.y + 50; 
	SDL_Rect recbouton;
	recbouton.w = 130;
	recbouton.h = 22;

	for(i = 0; i < 4; i++){

		if(SDL_RenderDrawRect(renderer, &recsort));
		SDL_afficher_message(perso->sorts[i]->nom, recsort.x + (recsort.w/2) - 60, recsort.y + 12, "Police/Freshman.ttf", 15, 'b', 'N');

		strcpy(carac[k], "Portee : ");
		sprintf(p, "%i", perso->sorts[i]->portee);
		strcat(carac[k++], p);

		strcpy(carac[k], "Degats : ");
		sprintf(p, "%i", perso->sorts[i]->degat);
		strcat(carac[k++], p);

		strcpy(carac[k], "Utilisation par tour : ");

		if(perso->sorts[i]->upt > perso->sorts[i]->uptm)
			sprintf(p, "%i", 0);
		else 
			sprintf(p, "%i", perso->sorts[i]->upt);

		strcat(carac[k], p);
		strcat(carac[k], "/");

		sprintf(p, "%i", perso->sorts[i]->uptm);
		strcat(carac[k++], p);

		strcpy(carac[k], "Point d'action : ");
		sprintf(p, "%i", perso->sorts[i]->point_action);
		strcat(carac[k++], p);

		k = 0;

		for(j = 0; j < 4; j++){
			SDL_afficher_message(carac[j], recsort.x + 10, y, "Police/bombarde.ttf", 13, 'b', 'N');
			y += 20;
			strcpy(carac[j], "");
		}

		strcpy(p, "");

		recbouton.x = recsort.x + 10;
		recbouton.y = recsort.y + recsort.h - 40; 
		
		if(i == select - 1){
			if(!SDL_RenderCopy(renderer, boutonon, NULL, &recbouton));
		}
		else 
			(!SDL_RenderCopy(renderer, boutonoff, NULL, &recbouton));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

		SDL_afficher_message("Utiliser le sort", recbouton.x + 22, recbouton.y + 3, "Police/bombarde.ttf", 14, 'b', 'N');

		y = recsort.y + 50; 
		recsort.x += recsort.w + 10;
	}




}

void afficher_menu(t_personnage * perso, int num_j, int select){ // -1 si aucune case n'est selectionnée


	SDL_Rect reccadre;
	reccadre.x = 10;
	reccadre.y = 10;
	reccadre.h = 200;
	reccadre.w = 350;

	if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255));
	if(SDL_RenderDrawRect(renderer, &reccadre));
	if(num_j == 1){
		SDL_afficher_message("Joueur 1", reccadre.x + (reccadre.w/2) - 40, reccadre.y + 10, "Police/Freshman.ttf", 20, 'b', 'N');
	}
	else
		SDL_afficher_message("Joueur 2", reccadre.x + (reccadre.w/2) - 40, reccadre.y + 10, "Police/Freshman.ttf", 20, 'b', 'N');
	SDL_affficher_id_perso(perso, 70, reccadre.x + 40, reccadre.y + 30, 17, num_j);

	char point[4][100] = {"Point de vie : ", "Point d'action : ", "Point de mouvement : "};
	
	char p[50];

	sprintf(p, "%i", perso->pv);

	strcat(point[0], p);
	strcat(point[0], "/");
	//strcpy(point)
	sprintf(p, "%i", perso->pv_max);
	strcat(point[0], p);

	sprintf(p, "%i", perso->pa);
	strcat(point[1], p);

	sprintf(p, "%i", perso->pm);
	strcat(point[2], p);

	int j;
	int deca = 125;
	for(j = 0; j < 3; j++){
		SDL_afficher_message(point[j], reccadre.x + 15, reccadre.y + deca, "Police/bombarde.ttf", 14, 'o', 'N');
		deca += 20;
	}

	int i;

	if(SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255));
	reccadre.x = 190;
	reccadre.y = 80;
	reccadre.w = 130;
	reccadre.h = 22;
	char tabchaine[4][20] = {"Se déplacer", "Utiliser un sort", "Passer le tour"};
	int dec[4] = {30, 20, 23};

	for(i = 0; i < 3; i++){
		//if(SDL_RenderFillRect(renderer, &reccadre));
		if(i == select - 1){
			if(!SDL_RenderCopy(renderer, boutonon, NULL, &reccadre));
		}
		else 
			(!SDL_RenderCopy(renderer, boutonoff, NULL, &reccadre));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_afficher_message(tabchaine[i], reccadre.x + dec[i], reccadre.y + 3, "Police/bombarde.ttf", 14, 'b', 'N');
		reccadre.y += reccadre.h + 13;
	}



}


void SDL_affficher_id_perso(t_personnage * perso, int c, int xi, int yi, int taille_p, int num_j){

	SDL_Rect recperso;
	int xt, yt;
	recperso.w = recperso.h = c;
	char car = perso->nom[0];
	//char * chaine = malloc(sizeof(char)*50);
	char chaine [50];
	switch(car){
		case 'G':
			recperso.x = xi;
			recperso.y = yi;
			xt = xi + 4;
			if(num_j == 1){
				if(!SDL_RenderCopy(renderer, idguerrier1, NULL, &recperso));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}
			else if (num_j == 2){
				if(!SDL_RenderCopy(renderer, idguerrier2, NULL, &recperso));
				//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}
		break;

		case 'A':
			recperso.x = xi;
			recperso.y = yi;
			xt = xi + 8;

			if(num_j == 1){
				if(!SDL_RenderCopy(renderer, idarcher1, NULL, &recperso));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}
			else if (num_j == 2){
				if(!SDL_RenderCopy(renderer, idarcher2, NULL, &recperso));
				//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}
		break;

		case 'T':
			recperso.x = xi;
			recperso.y = yi;
			xt = xi + 15;

			if(num_j == 1){
				if(!SDL_RenderCopy(renderer, idtank1, NULL, &recperso));
				//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}
			else if (num_j == 2){
				if(!SDL_RenderCopy(renderer, idtank2, NULL, &recperso));
				//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}
		break;

		case 'D':
			recperso.x = xi;
			recperso.y = yi;
			xt = xi + 13;

			if(num_j == 1){
				if(!SDL_RenderCopy(renderer, iddruide1, NULL, &recperso));
				//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}
			else if (num_j == 2){
				if(!SDL_RenderCopy(renderer, iddruide2, NULL, &recperso));
				//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}
		break;
	}

	//chaine = perso->nom;
	strcpy(chaine, perso->nom);
	if(strcmp(chaine, "Archer") == 0)
		//chaine = "Archere";
		strcat(chaine, "e");

	if(strcmp(chaine, "Guerrier") == 0 && num_j == 2)
		//chaine = "Gerriere";
		strcat(chaine, "e");
	yt = yi + c + 2;
	SDL_afficher_message(chaine, xt, yt, "Police/bombarde.ttf", taille_p, 'b', 'N');

}

void SDL_afficher_barre_point_de_vie(t_personnage * perso, int c, int xi, int yi){

	SDL_Rect recvie_max;
	SDL_Rect recvie_c;

	recvie_max.x = recvie_c.x = xi;
	recvie_c.x++;
	recvie_max.y = recvie_c.y = yi + c + 20;
	recvie_c.y++;
	recvie_max.h = recvie_c.h = 7;
	recvie_c.h-= 2;
	recvie_max.w = c;
	recvie_c.w = (perso->pv * c)/perso->pv_max;
	recvie_c.w-= 2;

	if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255));
	if(SDL_RenderDrawRect(renderer, &recvie_max));
	if(SDL_SetRenderDrawColor(renderer, 0, 160, 40, 255));
	if(perso->pv <= perso->pv_max/2){
		if(SDL_SetRenderDrawColor(renderer, 255, 127, 0, 255));
	}
	if(perso->pv <= perso->pv_max/4){
		if(SDL_SetRenderDrawColor(renderer, 168, 8, 8, 255));
	}
	if(SDL_RenderFillRect(renderer, &recvie_c));
}

void SDL_afficher_point_de_vie(t_joueur joueur1, t_joueur joueur2){

	int xi = 415, yi = 45, c = 60;


	char car;
	SDL_Rect recjoueur;

	recjoueur.x = xi + 25;
	recjoueur.y = yi - 35;

	SDL_ecrire_texte("Joueur 1", "Police/dimis.ttf", 25, 'b', 'N');
	SDL_QueryTexture(texte, NULL, NULL, &(recjoueur.w), &(recjoueur.h));
	if(!SDL_RenderCopy(renderer, texte, NULL, &recjoueur));

	SDL_Rect recvie_max;
	SDL_Rect recvie_c;


	SDL_affficher_id_perso(joueur1.perso1, c, xi, yi, 15, 1);
	SDL_afficher_barre_point_de_vie(joueur1.perso1, c, xi+2, yi);

	xi += c + 30;

	SDL_affficher_id_perso(joueur1.perso2, c, xi, yi, 15, 1);
	SDL_afficher_barre_point_de_vie(joueur1.perso2, c, xi+2, yi);

	xi += c + 205;
	recjoueur.x = xi - 125;
	recjoueur.y = 60 ;
	SDL_ecrire_texte("VS", "Police/eugenia.ttf", 50, 'b', 'N');
	SDL_QueryTexture(texte, NULL, NULL, &(recjoueur.w), &(recjoueur.h));
	if(!SDL_RenderCopy(renderer, texte, NULL, &recjoueur));

	recjoueur.x = xi + 20;
	recjoueur.y = yi - 35;
	SDL_ecrire_texte("Joueur 2", "Police/dimis.ttf", 25, 'b', 'N');
	SDL_QueryTexture(texte, NULL, NULL, &(recjoueur.w), &(recjoueur.h));
	if(!SDL_RenderCopy(renderer, texte, NULL, &recjoueur));

	SDL_affficher_id_perso(joueur2.perso1, c, xi, yi, 15, 2);
	SDL_afficher_barre_point_de_vie(joueur2.perso1, c, xi+2, yi);

	xi += c + 30;

	SDL_affficher_id_perso(joueur2.perso2, c, xi, yi, 15, 2);
	SDL_afficher_barre_point_de_vie(joueur2.perso2, c, xi+2, yi);
}

void SDL_afficher_degat(t_joueur j1, t_joueur j2, t_personnage * perso, int degat, char type){

	t_case casej = recherche_case(perso->coord.y, perso->coord.x);

	SDL_RenderClear(renderer);
	SDL_afficher_map(map, j1, j2);
	char chaine[10];
	char coul;
	if(type == 'p'){
		chaine[0] = '+';
		coul = 'j';
	}
	else{
		chaine[0]= '-';
		coul = 'R';
	}
	char c_degat[6]="";
	sprintf(c_degat, "%i", degat);

	strcat(chaine, c_degat);

	SDL_afficher_message(chaine, (casej.a.x + casej.c.x)/2 - 5, casej.b.y - 95, "Police/bombarde.ttf", 20, coul, 'N');
	SDL_RenderPresent(renderer);
	SDL_Delay(700);
}

void SDL_afficher_sort(char * nom, int xsort, int ysort){

	char c = nom[0];

	switch(c){
		case 'G':
			SDL_afficher_message("Saut : Portee [3] - Degat[0]", xsort + 22, ysort, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	  	SDL_afficher_message("Soin : Portee [0] - Degat[6]", xsort + 23, ysort + 16, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	  	SDL_afficher_message("Petit Coup : Portee [3] - Degat[10]", xsort + 10, ysort + 32, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	  	SDL_afficher_message("Gros Coup : Portee [1] - Degat[25]", xsort + 11, ysort + 48, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
		break;

		case 'A':
			SDL_afficher_message("Diago : Portee [7] - Degat[14]", xsort + 22, ysort, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	  	SDL_afficher_message("Ligne : Portee [7] - Degat[14]", xsort + 24, ysort + 16, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	  	SDL_afficher_message("Double Tape : Portee [5] - Degat[6]", xsort + 10, ysort + 32, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	  	SDL_afficher_message("Coup Zone : Portee [5] - Degat[12]", xsort + 13, ysort + 48, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
		break;
		case 'T':
			SDL_afficher_message("Armure : Portee [0] - Degat[0]", xsort + 19, ysort, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	 		SDL_afficher_message("Attire : Portee [15] - Degat[0]", xsort + 20, ysort + 16, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	 		SDL_afficher_message("ChenChen : Portee [2] - Degat[10]", xsort + 16, ysort + 32, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	 		SDL_afficher_message("BigShaq : Portee [1] - Degat[0]", xsort + 20, ysort + 48, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
		break;
		case 'D':
			SDL_afficher_message("Felin : Portee [0] - Degat[0]", xsort + 27, ysort, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	 		SDL_afficher_message("Chouette : Portee [15] - Degat[0]", xsort + 15, ysort + 16, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	 		SDL_afficher_message("Fuego : Portee [4] - Degat[12]", xsort + 25, ysort + 32, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
	 		SDL_afficher_message("Revitalisation : Portee [2] - Degat[8]", xsort + 6, ysort + 48, "Police/big_noodle_titling.ttf", 13, 'n', 'N');
		break;
	}
}

void SDL_afficher_message(char * message, int x, int y, char * police, int taille, char couleur, char style){

	SDL_Rect recquestion;
	recquestion.x = x;
	recquestion.y = y;

	SDL_ecrire_texte(message, police, taille, couleur, style);
	SDL_QueryTexture(texte, NULL, NULL, &(recquestion.w), &(recquestion.h));
	if(!SDL_RenderCopy(renderer, texte, NULL, &recquestion));

}

void SDL_afficher_perso_choisi(t_joueur joueur1, t_joueur joueur2){

	int xi = 400, yi = 75, c = 75;

	SDL_Rect recjoueur;
	recjoueur.x = xi + 20;
	recjoueur.y = 30 ;
	SDL_ecrire_texte("Joueur 1", "Police/dimis.ttf", 30, 'b', 'N');
	SDL_QueryTexture(texte, NULL, NULL, &(recjoueur.w), &(recjoueur.h));
	if(!SDL_RenderCopy(renderer, texte, NULL, &recjoueur));

	if(joueur1.perso1)
		SDL_affficher_id_perso(joueur1.perso1, c, xi, yi, 20, 1);

	else {
		SDL_afficher_message("Choix personnage 1", 410, HAUTEUR - 115, "Police/calendarnote.ttf", 50, 'o', 'N');
		SDL_afficher_message("ÌJoueur1Í",571, 592, "Police/yorkwhiteletter.ttf", 60, 'r', 'N');
	}

	xi += c + 10;
	if(joueur1.perso2)
		SDL_affficher_id_perso(joueur1.perso2, c, xi, yi, 20, 1);

	else if(joueur1.perso1){
		SDL_afficher_message("Choix personnage 2", 410, HAUTEUR - 115, "Police/calendarnote.ttf", 50, 'o', 'N');
		SDL_afficher_message("ÌJoueur1Í",571, 592, "Police/yorkwhiteletter.ttf", 60, 'r', 'N');
	}

	xi += c + 190;
	recjoueur.x = xi - 130;
	recjoueur.y = 90 ;
	SDL_ecrire_texte("VS", "Police/eugenia.ttf", 75, 'b', 'N');
	SDL_QueryTexture(texte, NULL, NULL, &(recjoueur.w), &(recjoueur.h));
	if(!SDL_RenderCopy(renderer, texte, NULL, &recjoueur));

	recjoueur.x = xi + 20;
	recjoueur.y = 30 ;
	SDL_ecrire_texte("Joueur 2", "Police/dimis.ttf", 30, 'b', 'N');
	SDL_QueryTexture(texte, NULL, NULL, &(recjoueur.w), &(recjoueur.h));
	if(!SDL_RenderCopy(renderer, texte, NULL, &recjoueur));

	if(joueur2.perso1)
		SDL_affficher_id_perso(joueur2.perso1, c, xi, yi, 20, 2);

	else if(joueur1.perso1 && joueur1.perso2){
		SDL_afficher_message("Choix personnage 1", 410, HAUTEUR - 115, "Police/calendarnote.ttf", 50, 'o', 'N');
		SDL_afficher_message("ÌJoueur2Í",571, 592, "Police/yorkwhiteletter.ttf", 60, 'r', 'N');
	}

	xi += c + 10;
	if(joueur2.perso2)
		SDL_affficher_id_perso(joueur2.perso2, c, xi, yi, 20, 2);

	else if(joueur1.perso1 && joueur1.perso2 && joueur2.perso1){
		SDL_afficher_message("Choix personnage 2", 410, HAUTEUR - 115, "Police/calendarnote.ttf", 50, 'o', 'N');
		SDL_afficher_message("ÌJoueur2Í",571, 592, "Police/yorkwhiteletter.ttf", 60, 'r', 'N');
	}
}

void SDL_afficher_bg(){
	SDL_Rect recbg;

	if(!SDL_QueryTexture(bg, NULL, NULL, &recbg.w, &recbg.h))
		;//fprintf(stderr, "Texture non chargée : %s\n", SDL_GetError());

	if(!SDL_RenderCopy(renderer, bg, NULL, NULL));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());*/

}

void SDL_afficher_acceuil(){

  SDL_Rect recaccueil;
	srand(time(NULL));
	int i = rand()%2;

	if(i == 0){

    if(!SDL_QueryTexture(accueil, NULL, NULL, &recaccueil.w, &recaccueil.h))
          ;//fprintf(stderr, "Texture non chargée : %s\n", SDL_GetError());

    	if(!SDL_RenderCopy(renderer, accueil, NULL, NULL));
          //fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());*/
	}
	else {
		if(!SDL_QueryTexture(accueil1, NULL, NULL, &recaccueil.w, &recaccueil.h))
          ;//fprintf(stderr, "Texture non chargée : %s\n", SDL_GetError());
    	if(!SDL_RenderCopy(renderer, accueil1, NULL, NULL));
          //fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());*/
	}
  SDL_RenderPresent(renderer);
  SDL_Delay(3000);
  SDL_RenderClear(renderer);

}

void SDL_affichage_choix_perso(int num_j){

	SDL_afficher_bg();
	SDL_Rect recchoix_perso;

	int x = 90, w = (LARGEUR/5) + 5, y = 160, h = (HAUTEUR/2) + 5 + 30;

	recchoix_perso.w = w;
	recchoix_perso.h = h;
	recchoix_perso.x = x;
	recchoix_perso.y = y;

	int ximg = recchoix_perso.x + 23, yimg = recchoix_perso.y + 37;

	SDL_choix_p[0].num_choix = 1;
	SDL_choix_p[0].b.x = ximg;
	SDL_choix_p[0].b.y = yimg;

	SDL_choix_p[0].a.y = yimg + h - (37*2);
	SDL_choix_p[0].c.x = ximg + w - (23*2);

	SDL_Rect rectexte;
	int xsort = 142, ysort = 460;

	if(num_j == 1){

		if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_ecrire_texte("Guerrier", "Police/bombarde.ttf", 22, 'o', 'N');
		rectexte.x = ximg + 78;
		rectexte.y = yimg + 20;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));

		SDL_Rect recguerrier1;
		recguerrier1.w = 135;
		recguerrier1.h = 150;
		recguerrier1.x = recchoix_perso.x + 67;
		recguerrier1.y = recchoix_perso.y + 115;

		if(!SDL_RenderCopy(renderer, guerrier1, NULL, &recguerrier1));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

		 //SDL_afficher_message("Liste(des(sorts!", xsort + 8, rectexte.y + 228, "Police/Kaldevaderibbon.ttf", 32, 'n', 'N');
		 SDL_afficher_sort("Guerrier", xsort, ysort);

		 recchoix_perso.x = recchoix_perso.x + w + 15;
		 ximg = recchoix_perso.x + 23;

		 SDL_choix_p[1].num_choix = 2;
		 SDL_choix_p[1].b.x = ximg;
		 SDL_choix_p[1].b.y = yimg;

		 SDL_choix_p[1].a.y = yimg + h - (37*2);
		 SDL_choix_p[1].c.x = ximg + w - (23*2);

		 if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_ecrire_texte("Archere", "Police/bombarde.ttf", 22, 'o', 'N');
		rectexte.x = ximg + 78;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));

		SDL_Rect recarcher1;

		recarcher1.w = 140;
		recarcher1.h = 155;
		recarcher1.x = recchoix_perso.x + 75;
		recarcher1.y = recchoix_perso.y + 110;

		if(!SDL_RenderCopy(renderer, archer1, NULL, &recarcher1));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		xsort += 288;
		//SDL_afficher_message("Liste(des(sorts!", xsort + 8, rectexte.y + 228, "Police/Kaldevaderibbon.ttf", 32, 'n', 'N');
		SDL_afficher_sort("Archere", xsort, ysort);
		recchoix_perso.x = recchoix_perso.x + w + 15;
		ximg = recchoix_perso.x + 23;

		SDL_choix_p[2].num_choix = 3;
	 	SDL_choix_p[2].b.x = ximg;
		SDL_choix_p[2].b.y = yimg;

		SDL_choix_p[2].a.y = yimg + h - (37*2);
		SDL_choix_p[2].c.x = ximg + w - (23*2);

		if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
		  	//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_ecrire_texte("Tank", "Police/bombarde.ttf", 22, 'o', 'N');
		rectexte.x = ximg + 92;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));

		SDL_Rect rectank1;

		rectank1.w = 155;
		rectank1.h = 180;
		rectank1.x = recchoix_perso.x + 62;
		rectank1.y = recchoix_perso.y + 98;

		if(!SDL_RenderCopy(renderer, tank1, NULL, &rectank1));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		xsort += 288;
		//SDL_afficher_message("Liste(des(sorts!", xsort + 8, rectexte.y + 228, "Police/Kaldevaderibbon.ttf", 32, 'n', 'N');
		SDL_afficher_sort("Tank", xsort, ysort);

		recchoix_perso.x = recchoix_perso.x + w + 15;
		ximg = recchoix_perso.x + 23;

		SDL_choix_p[3].num_choix = 4;
		SDL_choix_p[3].b.x = ximg;
		SDL_choix_p[3].b.y = yimg;

		SDL_choix_p[3].a.y = yimg + h - (37*2);
		SDL_choix_p[3].c.x = ximg + w - (23*2);

		if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_ecrire_texte("Druide", "Police/bombarde.ttf", 22, 'o', 'N');
		rectexte.x = ximg + 90;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));

		SDL_Rect recdruide1;

		recdruide1.w = 120;
		recdruide1.h = 150;
		recdruide1.x = recchoix_perso.x + 65;
		recdruide1.y = recchoix_perso.y + 110;

		if(!SDL_RenderCopy(renderer, druide1, NULL, &recdruide1));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		xsort += 288;
		 //SDL_afficher_message("Liste(des(sorts!", xsort + 8, rectexte.y + 228, "Police/Kaldevaderibbon.ttf", 32, 'n', 'N');
		SDL_afficher_sort("Druide", xsort, ysort);
	}

	else if(num_j == 2){

		if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_ecrire_texte("Guerriere", "Police/bombarde.ttf", 22, 'o', 'N');
		rectexte.x = ximg + 73;
		rectexte.y = yimg + 20;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));


		SDL_Rect recguerrier2;

		recguerrier2.w = 155;
		recguerrier2.h = 150;
		recguerrier2.x = recchoix_perso.x + 55;
		recguerrier2.y = recchoix_perso.y + 110;

		if(!SDL_RenderCopy(renderer, guerrier2, NULL, &recguerrier2));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		//SDL_afficher_message("Liste(des(sorts!", xsort + 8, rectexte.y + 228, "Police/Kaldevaderibbon.ttf", 32, 'n', 'N');
		SDL_afficher_sort("Guerrier", xsort, ysort);
		recchoix_perso.x = recchoix_perso.x + w + 15;
		ximg = recchoix_perso.x + 23;

		SDL_choix_p[1].num_choix = 2;
		SDL_choix_p[1].b.x = ximg;
		SDL_choix_p[1].b.y = yimg;

		SDL_choix_p[1].a.y = yimg + h - (37*2);
		SDL_choix_p[1].c.x = ximg + w - (23*2);

		if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_ecrire_texte("Archere", "Police/bombarde.ttf", 22, 'o', 'N');
		rectexte.x = ximg + 78;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));

		SDL_Rect recarcher2;

		recarcher2.w = 125;
		recarcher2.h = 145;
		recarcher2.x = recchoix_perso.x + 95;
		recarcher2.y = recchoix_perso.y + 112;

		if(!SDL_RenderCopy(renderer, archer2, NULL, &recarcher2));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		xsort += 287;
		//SDL_afficher_message("Liste(des(sorts!", xsort + 8, rectexte.y + 228, "Police/Kaldevaderibbon.ttf", 32, 'n', 'N');
		SDL_afficher_sort("Archere", xsort, ysort);

		recchoix_perso.x = recchoix_perso.x + w + 15;
		ximg = recchoix_perso.x + 23;

		SDL_choix_p[2].num_choix = 3;
	 	SDL_choix_p[2].b.x = ximg;
		SDL_choix_p[2].b.y = yimg;

		SDL_choix_p[2].a.y = yimg + h - (37*2);
		SDL_choix_p[2].c.x = ximg + w - (23*2);

		if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
		  	//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_ecrire_texte("Tank", "Police/bombarde.ttf", 22, 'o', 'N');
		rectexte.x = ximg + 92;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));

		SDL_Rect rectank2;

		rectank2.w = 155;
		rectank2.h = 165;
		rectank2.x = recchoix_perso.x + 57;
		rectank2.y = recchoix_perso.y + 103;

		if(!SDL_RenderCopy(renderer, tank2, NULL, &rectank2));
		//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		xsort += 288;
		//SDL_afficher_message("Liste(des(sorts!", xsort + 8, rectexte.y + 228, "Police/Kaldevaderibbon.ttf", 32, 'n', 'N');
		SDL_afficher_sort("Tank", xsort, ysort);


		recchoix_perso.x = recchoix_perso.x + w + 15;
		ximg = recchoix_perso.x + 23;

		SDL_choix_p[3].num_choix = 4;
		SDL_choix_p[3].b.x = ximg;
		SDL_choix_p[3].b.y = yimg;

		SDL_choix_p[3].a.y = yimg + h - (37*2);
		SDL_choix_p[3].c.x = ximg + w - (23*2);

		if(!SDL_RenderCopy(renderer, choix_perso, NULL, &recchoix_perso));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		SDL_ecrire_texte("Druide", "Police/bombarde.ttf", 22, 'o', 'N');
		rectexte.x = ximg + 90;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));

		SDL_Rect recdruide2;

		recdruide2.w = 145;
		recdruide2.h = 165;
		recdruide2.x = recchoix_perso.x + 70;
		recdruide2.y = recchoix_perso.y + 100;

		if(!SDL_RenderCopy(renderer, druide2, NULL, &recdruide2));
			//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
		xsort += 288;
		//SDL_afficher_message("Liste(des(sorts!", xsort + 8, rectexte.y + 228, "Police/Kaldevaderibbon.ttf", 32, 'n', 'N');
	 SDL_afficher_sort("Druide", xsort, ysort);
	}
}

void SDL_afficher_map(char map[N][N], t_joueur j1, t_joueur j2){

	SDL_afficher_bg();

	int i, j, w = 80, h = 40, x = 628, y = 175, k = 0; //x = 100, y = (HAUTEUR/2) - 50, k = 0;

	char car;

	SDL_Rect reccase_n;

	reccase_n.w = w;
	reccase_n.h = h;
	reccase_n.x = x;
	reccase_n.y = y;
	int depx = reccase_n.x, depy = reccase_n.y;

	SDL_Rect reccase_p;

	reccase_p.w = w;
	reccase_p.h = h;
	reccase_p.x = x;
	reccase_p.y = y;

	SDL_Rect reccase_c;

	reccase_c.w = w;
	reccase_c.h = h;
	reccase_c.x = x;
	reccase_c.y = y;

	SDL_Rect recobstacle;
	int xo = x+3, yo = y-38, wo = w - 5, ho = h + 40;//48

	recobstacle.w = wo;
	recobstacle.h = ho;//50
	recobstacle.x = xo;
	recobstacle.y = yo;

	SDL_Rect reccase_s;
	int ws = w - 15, hs = h - 15;

	reccase_s.w = ws;
	reccase_s.h = hs;

	SDL_Rect recguerrier1;

	recguerrier1.w = 95;
	recguerrier1.h = 100;

	SDL_Rect rectank1;

	rectank1.w = 115;
	rectank1.h = 115;

	SDL_Rect recarcher1;

	recarcher1.w = 100;
	recarcher1.h = 100;

	SDL_Rect recdruide1;

	recdruide1.w = 93;
	recdruide1.h = 95;

	SDL_Rect recguerrier2;

	recguerrier2.w = 105;
	recguerrier2.h = 103;

	SDL_Rect rectank2;

	rectank2.w = 110;
	rectank2.h = 110;

	SDL_Rect recarcher2;

	recarcher2.w = 90;
	recarcher2.h = 92;

	SDL_Rect recdruide2;

	recdruide2.w = 100;
	recdruide2.h = 102;

	for(i = 0; i < N; i++){
		for(j = N-1; j >= 0 ; j--){

			if(map[i][j] == 'o'){
				if(!SDL_RenderCopy(renderer, obstacle, NULL, &recobstacle));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());

				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k].type = OBSTACLE;
				SDL_map[k].a.x = reccase_n.x;
				SDL_map[k].a.y = reccase_n.y + (h/2);

				SDL_map[k].c.x = reccase_n.x + w;
				SDL_map[k].c.y = reccase_n.y + (h/2);

				SDL_map[k].b.y = reccase_n.y;
				SDL_map[k].b.x = reccase_n.x + (w/2);

				SDL_map[k].d.y = reccase_n.y + ho;
				SDL_map[k].d.x = reccase_n.x + (w/2);
				k++;
			}

			else if(map[i][j] >= 'A' && map[i][j] <= 'Z'){
				if(!SDL_RenderCopy(renderer, case_p, NULL, &reccase_p));
					//fprintf(stderr, "Textur1e non copiée : %s\n", SDL_GetError());
				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k].type = CASE_BLEUE;
				SDL_map[k].a.x = reccase_n.x;
				SDL_map[k].a.y = reccase_n.y + (h/2);

				SDL_map[k].c.x = reccase_n.x + w;
				SDL_map[k].c.y = reccase_n.y + (h/2);

				SDL_map[k].b.y = reccase_n.y;
				SDL_map[k].b.x = reccase_n.x + (w/2);

				SDL_map[k].d.y = reccase_n.y + h;
				SDL_map[k].d.x = reccase_n.x + (w/2);
				k++;
			}

			else if(map[i][j] == 'x'){
				if(!SDL_RenderCopy(renderer, case_c, NULL, &reccase_c));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			}

			else{

				if(map[i][j] >= 'a' && map[i][j] <= 'z'){
					if(!SDL_RenderCopy(renderer, case_p, NULL, &reccase_p));
					//fprintf(stderr, "Textur1e non copiée : %s\n", SDL_GetError());
				}


				else {
					if(!SDL_RenderCopy(renderer, case_n, NULL, &reccase_n));
						//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
				}

				SDL_map[k].i = i;
				SDL_map[k].j = j;
				SDL_map[k].type = CASE_GRISE;
				SDL_map[k].a.x = reccase_n.x;
				SDL_map[k].a.y = reccase_n.y + (h/2);

				SDL_map[k].c.x = reccase_n.x + w;
				SDL_map[k].c.y = reccase_n.y + (h/2);

				SDL_map[k].b.y = reccase_n.y;
				SDL_map[k].b.x = reccase_n.x + (w/2);

				SDL_map[k].d.y = reccase_n.y + h;
				SDL_map[k].d.x = reccase_n.x + (w/2);


				if(map[i][j] == '1' || map[i][j] == 'a'){

					car = j1.perso1->nom[0];
					switch(car){
						case 'A':
							recarcher1.x = reccase_n.x - 15;
							recarcher1.y = reccase_n.y - 72;

							if(!SDL_RenderCopy(renderer, archer1, NULL, &recarcher1));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'G':
							recguerrier1.x = reccase_n.x - 10;
							recguerrier1.y = reccase_n.y - 72;

							if(!SDL_RenderCopy(renderer, guerrier1, NULL, &recguerrier1));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'T':
							rectank1.x = reccase_n.x - 17;
							rectank1.y = reccase_n.y - 82;

							if(!SDL_RenderCopy(renderer, tank1, NULL, &rectank1));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'D':
							recdruide1.x = reccase_n.x - 30;
							recdruide1.y = reccase_n.y - 70;

							if(!SDL_RenderCopy(renderer, druide1, NULL, &recdruide1));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

					}
					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J1P1;
				}

				else if (map[i][j] == '2' || map[i][j] == 'b'){

					car = j2.perso1->nom[0];

					switch(car){

						case 'A':
							recarcher2.x = reccase_n.x + 15;
							recarcher2.y = reccase_n.y - 67;

							if(!SDL_RenderCopy(renderer, archer2, NULL, &recarcher2));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'G':
							recguerrier2.x = reccase_n.x - 18;
							recguerrier2.y = reccase_n.y - 77;

							if(!SDL_RenderCopy(renderer, guerrier2, NULL, &recguerrier2));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'T':
							rectank2.x = reccase_n.x - 17;
							rectank2.y = reccase_n.y - 79;

							if(!SDL_RenderCopy(renderer, tank2, NULL, &rectank2));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'D':
							recdruide2.x = reccase_n.x - 10;
							recdruide2.y = reccase_n.y - 72;

							if(!SDL_RenderCopy(renderer, druide2, NULL, &recdruide2));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

					}
					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J2P1;
				}

				else if(map[i][j] == '3'|| map[i][j] == 'c'){

					car = j1.perso2->nom[0];

					switch(car){

						case 'A':
							recarcher1.x = reccase_n.x - 10;
							recarcher1.y = reccase_n.y - 72;

							if(!SDL_RenderCopy(renderer, archer1, NULL, &recarcher1));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'G':
							recguerrier1.x = reccase_n.x - 10;
							recguerrier1.y = reccase_n.y - 72;

							if(!SDL_RenderCopy(renderer, guerrier1, NULL, &recguerrier1));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'T':
							rectank1.x = reccase_n.x - 17;
							rectank1.y = reccase_n.y - 82;

							if(!SDL_RenderCopy(renderer, tank1, NULL, &rectank1));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'D':
							recdruide1.x = reccase_n.x - 30;
							recdruide1.y = reccase_n.y - 70;

							if(!SDL_RenderCopy(renderer, druide1, NULL, &recdruide1));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

					}
					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J1P2;
				}

				else if(map[i][j] == '4' || map[i][j] == 'd'){

					car = j2.perso2->nom[0];

					switch(car){

						case 'A':
							recarcher2.x = reccase_n.x + 10;
							recarcher2.y = reccase_n.y - 67;

							if(!SDL_RenderCopy(renderer, archer2, NULL, &recarcher2));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'G':
							recguerrier2.x = reccase_n.x - 18;
							recguerrier2.y = reccase_n.y - 77;

							if(!SDL_RenderCopy(renderer, guerrier2, NULL, &recguerrier2));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'T':
							rectank2.x = reccase_n.x - 17;
							rectank2.y = reccase_n.y - 79;

							if(!SDL_RenderCopy(renderer, tank2, NULL, &rectank2));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

						case 'D':
							recdruide2.x = reccase_n.x - 10;
							recdruide2.y = reccase_n.y - 72;

							if(!SDL_RenderCopy(renderer, druide2, NULL, &recdruide2));
								//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
						break;

					}
					SDL_map[k].i = i;
					SDL_map[k].j = j;
					SDL_map[k].type = J2P2;
				}

				if(map[i][j] >= 'a' && map[i][j] <= 'z')
					SDL_map[k].type = CASE_BLEUE;

				k++;

			}
			reccase_n.y = reccase_n.y + (h/2) + 3;//5
			reccase_n.x = reccase_n.x - (w/2) - 8;//10

			reccase_p.y = reccase_p.y + (h/2) + 3;
			reccase_p.x = reccase_p.x - (w/2) - 8;

			reccase_c.y = reccase_c.y + (h/2) + 3;//5
			reccase_c.x = reccase_c.x - (w/2) - 8;//10

			recobstacle.y = recobstacle.y + (h/2) + 3;
			recobstacle.x = recobstacle.x - (w/2) - 8;
		}
	  	//printf("x = %i et y = %i\n", reccase_n.x, reccase_n.y);
		reccase_n.y = y + (((h/2) + 3)*(i+1));
		reccase_n.x = x + (((w/2) + 8)*(i+1));

		reccase_p.y = y + (((h/2) + 3)*(i+1));
		reccase_p.x = x + (((w/2) + 8)*(i+1));

		reccase_c.y = y + (((h/2) + 3)*(i+1));
		reccase_c.x = x + (((w/2) + 8)*(i+1));

		recobstacle.y = yo + (((h/2) + 3)*(i+1));
		recobstacle.x = xo + (((w/2) + 8)*(i+1));

		//printf("x = %i et y = %i\n", reccase_n.x, reccase_n.y);
	}
}
