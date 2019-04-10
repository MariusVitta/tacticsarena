#include "fonc.h"
#include "sdl_fonc.h"

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

void SDL_ecrire_texte(char * chaine, char * police_ec, int taille, char color, char style){

	SDL_Surface * tex_texte = NULL;

  	if((police = TTF_OpenFont(police_ec, taille)) == NULL){
  		fprintf(stderr, "erreur chargement font\n");
  	}

  	switch(style){
  		case 'N':
  			TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
  		break;
  		case 'G':
  			TTF_SetFontStyle(police, TTF_STYLE_BOLD);
  		break;

  		case 'I':
  			TTF_SetFontStyle(police, TTF_STYLE_ITALIC);
  		break;

  		case 'S':
  			TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);
  		break;
  	}

  	SDL_Color couleur;

  	switch(color){

  		case 'b':
  			couleur = blanc;
  		break;
  		case 'n':
  			couleur = noir;
  		break;
  		case 'o':
  			couleur = orange;
  		break;
  		case 'r':
  			couleur = rouge;
  		break;
  	}


  	tex_texte = TTF_RenderUTF8_Blended(police, chaine, couleur);

  	if(!tex_texte){
  		fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
  	}
  	texte = SDL_CreateTextureFromSurface(renderer, tex_texte);

    SDL_FreeSurface(tex_texte); /* on a la texture, plus besoin du texte */

  	if(!texte){
  		fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
  	}

}

void SDL_afficher_perso_choisi(t_joueur joueur1, t_joueur joueur2){

	int xi = 400, yi = 75, c = 75;

	SDL_Rect recidguerrier1;
	recidguerrier1.w = c;
	recidguerrier1.h = c;
	SDL_Rect recidarcher1;
	recidarcher1.w = c;
	recidarcher1.h = c;
	SDL_Rect recidtank1;
	recidtank1.w = c;
	recidtank1.h = c;
	SDL_Rect reciddruide1;
	reciddruide1.w = c;
	reciddruide1.h = c;

	SDL_Rect recidguerrier2;
	recidguerrier2.w = c;
	recidguerrier2.h = c;
	SDL_Rect recidarcher2;
	recidarcher2.w = c;
	recidarcher2.h = c;
	SDL_Rect recidtank2;
	recidtank2.w = c;
	recidtank2.h = c;
	SDL_Rect reciddruide2;
	reciddruide2.w = c;
	reciddruide2.h = c;

	/* Majuscule initial pour les persos du joueur1 minuscules pour le joueur 2*/

	char car;

	SDL_Rect rectexte;
	SDL_Rect recjoueur;

	char * chaine = malloc(sizeof(char)*50);


	recjoueur.x = xi + 20;
	recjoueur.y = 30 ;
	SDL_ecrire_texte("Joueur 1", "Police/dimis.ttf", 30, 'b', 'N');
	SDL_QueryTexture(texte, NULL, NULL, &(recjoueur.w), &(recjoueur.h));
	if(!SDL_RenderCopy(renderer, texte, NULL, &recjoueur));

	if(joueur1.perso1){

		car = joueur1.perso1->nom[0];

		switch(car){

			case 'G':
				recidguerrier1.x = xi;
				recidguerrier1.y = yi;
				rectexte.x = xi + 4;
				if(!SDL_RenderCopy(renderer, idguerrier1, NULL, &recidguerrier1));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'A':
				recidarcher1.x = xi;
				recidarcher1.y = yi;
				rectexte.x = xi + 8;
				if(!SDL_RenderCopy(renderer, idarcher1, NULL, &recidarcher1));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'T':
				recidtank1.x = xi;
				recidtank1.y = yi;
				rectexte.x = xi + 16;
				if(!SDL_RenderCopy(renderer, idtank1, NULL, &recidtank1));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'D':
				reciddruide1.x = xi;
				reciddruide1.y = yi;
				rectexte.x = xi + 13;
				if(!SDL_RenderCopy(renderer, iddruide1, NULL, &reciddruide1));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;

		}

		chaine = joueur1.perso1->nom;
		if(strcmp(chaine, "Archer") == 0)
			chaine = "Archere";

		SDL_ecrire_texte(chaine, "Police/bombarde.ttf", 20, 'b', 'N');
		rectexte.y = yi + c + 2;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));
	}

	else {
		SDL_afficher_message("Choix personnage 1", 410, HAUTEUR - 115, "Police/calendarnote.ttf", 50, 'o', 'N');
		SDL_afficher_message("ÌJoueur1Í",571, 592, "Police/yorkwhiteletter.ttf", 60, 'r', 'N');
	}


	xi += c + 10;

	if(joueur1.perso2){


		car = joueur1.perso2->nom[0];

		switch(car){
			case 'G':
				recidguerrier1.x = xi;
				recidguerrier1.y = yi;
				rectexte.x = xi + 4;
				if(!SDL_RenderCopy(renderer, idguerrier1, NULL, &recidguerrier1));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'A':
				recidarcher1.x = xi;
				recidarcher1.y = yi;
				rectexte.x = xi + 8;
				if(!SDL_RenderCopy(renderer, idarcher1, NULL, &recidarcher1));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'T':
				recidtank1.x = xi;
				recidtank1.y = yi;
				rectexte.x = xi + 16;
				if(!SDL_RenderCopy(renderer, idtank1, NULL, &recidtank1));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'D':
				reciddruide1.x = xi;
				reciddruide1.y = yi;
				rectexte.x = xi + 13;
				if(!SDL_RenderCopy(renderer, iddruide1, NULL, &reciddruide1));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
		}

		chaine = joueur1.perso2->nom;
		if(strcmp(chaine, "Archer") == 0)
			chaine = "Archere";
		SDL_ecrire_texte(chaine, "Police/bombarde.ttf", 20, 'b', 'N');
		rectexte.y = yi + c + 2;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));
	}

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

	if(joueur2.perso1){

		car = joueur2.perso1->nom[0];

		switch(car){
			case 'G':
				recidguerrier2.x = xi;
				recidguerrier2.y = yi;
				rectexte.x = xi + 3;
				if(!SDL_RenderCopy(renderer, idguerrier2, NULL, &recidguerrier2));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'A':
				recidarcher2.x = xi;
				recidarcher2.y = yi;
				rectexte.x = xi + 8;
				if(!SDL_RenderCopy(renderer, idarcher2, NULL, &recidarcher2));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'T':
				recidtank2.x = xi;
				recidtank2.y = yi;
				rectexte.x = xi + 16;
				if(!SDL_RenderCopy(renderer, idtank2, NULL, &recidtank2));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'D':
				reciddruide2.x = xi;
				reciddruide2.y = yi;
				rectexte.x = xi + 13;
				if(!SDL_RenderCopy(renderer, iddruide2, NULL, &reciddruide2));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
		}
		chaine = joueur2.perso1->nom;
		if(strcmp(chaine, "Guerrier") == 0)
			chaine = "Gerriere";
		else if(strcmp(chaine, "Archer") == 0)
			chaine = "Archere";
		SDL_ecrire_texte(chaine, "Police/bombarde.ttf", 20, 'b', 'N');
		rectexte.y = yi + c + 2;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));
	}

	else if(joueur1.perso1 && joueur1.perso2){
		SDL_afficher_message("Choix personnage 1", 410, HAUTEUR - 115, "Police/calendarnote.ttf", 50, 'o', 'N');
		SDL_afficher_message("ÌJoueur2Í",571, 592, "Police/yorkwhiteletter.ttf", 60, 'r', 'N');
	}

	xi += c + 10;

	if(joueur2.perso2){

		car = joueur2.perso2->nom[0];
		rectexte.x = xi;

		switch(car){
			case 'G':
				recidguerrier2.x = xi;
				recidguerrier2.y = yi;
				rectexte.x = xi + 1;
				if(!SDL_RenderCopy(renderer, idguerrier2, NULL, &recidguerrier2));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'A':
				recidarcher2.x = xi;
				recidarcher2.y = yi;
				rectexte.x = xi + 8;
				if(!SDL_RenderCopy(renderer, idarcher2, NULL, &recidarcher2));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'T':
				recidtank2.x = xi;
				recidtank2.y = yi;
				rectexte.x = xi + 16;
				if(!SDL_RenderCopy(renderer, idtank2, NULL, &recidtank2));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
			case 'D':
				reciddruide2.x = xi;
				reciddruide2.y = yi;
				rectexte.x = xi + 13;
				if(!SDL_RenderCopy(renderer, iddruide2, NULL, &reciddruide2));
					//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
			break;
		}
		chaine = joueur2.perso2->nom;
		if(strcmp(chaine, "Guerrier") == 0)
			chaine = "Guerriere";
		else if(strcmp(chaine, "Archer") == 0)
			chaine = "Archere";
		SDL_ecrire_texte(chaine, "Police/bombarde.ttf", 20, 'b', 'N');
		rectexte.y = yi + c + 2;
		SDL_QueryTexture(texte, NULL, NULL, &(rectexte.w), &(rectexte.h));
		if(!SDL_RenderCopy(renderer, texte, NULL, &rectexte));
	}

	else if(joueur1.perso1 && joueur1.perso2 && joueur2.perso1){
		SDL_afficher_message("Choix personnage 2", 410, HAUTEUR - 115, "Police/calendarnote.ttf", 50, 'o', 'N');
		SDL_afficher_message("ÌJoueur2Í",571, 592, "Police/yorkwhiteletter.ttf", 60, 'r', 'N');	}

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
	char * chaine = malloc(sizeof(char)*50);
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

	int i, j, w = 80, h = 40, x = 628, y = 150, k = 0; //x = 100, y = (HAUTEUR/2) - 50, k = 0;

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

				if(!SDL_RenderCopy(renderer, case_n, NULL, &reccase_n));
						//fprintf(stderr, "Texture non copiée : %s\n", SDL_GetError());
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


				if(map[i][j] == '1'){

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

				else if (map[i][j] == '2'){

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

				else if(map[i][j] == '3'){

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

				else if(map[i][j] == '4'){

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
