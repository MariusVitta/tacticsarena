#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include "fonc.h"
#include "define.h"
#include <time.h>

char buffer[BUFFER_LEN];
char map[N][N];

void fin(int sig){
	printf("fin du serveur");
}

int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }

    return 1;
}


void view_ip()
{
  char s[256];
  struct hostent *host;
  struct in_addr **adr;
  if (!gethostname(s, 256))
    if ((host = gethostbyname(s)) != NULL)
      for (adr = (struct in_addr **)host->h_addr_list; *adr; adr++)
          printf("IP : %s\n", inet_ntoa(**adr));
}

void send_all_tour(t_equipe ** tab_joueur, int j, int nb_client,int info_donnee){
	//Annonce aux autres joueurs que c'est le tour de j
	for(int i=0;i < nb_client;i++){

		switch(info_donnee){
			//info 1 : on envoie l'info à tout le monde
			case 1:
				send(tab_joueur[i]->client_socket, buffer+4, BUFFER_LEN, 0);
				break;
			//info 2 : on envoie la map
			/*case 2:
				send(tab_joueur[i]->client_socket, buffer, BUFFER_LEN, 0);
				break;*/
			//info 3 : on envoie l'info à tout le monde sauf au joueur dont le tour est en cours
			case 3:
				if(i==j);
				else{
					send(tab_joueur[i]->client_socket, buffer, BUFFER_LEN, 0);
				}
				break;
			default:
				printf("Erreur info_donnee\n");
				break;
		}

	}

}

void envoie_map(char matriceJeu[N][N], t_equipe ** tab_joueur, int j, int nb_client){
		int x, y;
		char chaine[BUFFER_LEN], buffer[BUFFER_LEN];

		/* Initialise la chaine */
		sprintf(chaine," %c |",matriceJeu[0][0]);
		for(x=0; x < N ; x++){
			for(y=0; y < N ; y++){
				if (x != 0 && y != 0) { /* La chaine est déjà initialisée avec le premier caractère du tableau */
					sprintf(buffer," %c |",matriceJeu[x][y]);
					strcpy(chaine,strcat(chaine, buffer));
				}
			}
			strcpy(chaine,strcat(chaine, "\n"));
			strcpy(buffer,chaine);
			send_all_tour(tab_joueur, j, nb_client, 1);
		}

}


void initialisation_partie(char matriceJeu[N][N],t_equipe * equipe1,t_equipe * equipe2, int nb_client, t_equipe ** tab_joueur, int j){
	srand(time(NULL));
	int y1 = rand()%3+(N-3), x1 = rand()%(N-4)+2, y2, x2;
	int i,choix1 = 0,choix2 = 0,numero_j=1,x=0;
	int nb_persos = 1;
	int nb_obs = 10; /* nb d'obstacles max sur la carte*/

  /* remplissage de la map sans les equipes positionnés */
	for(i = 0; i < N ; i++){
		for(j = 0;j < N; j++){
				matriceJeu[i][j] = '.';
		}
	}

	for(j=0; j <= nb_client; j++){
		sprintf(buffer,"\n ---- Choix des cases possibles pour le joueur %i ---- \n", j+1);
		send_all_tour(tab_joueur, j, nb_client, 1);

		matriceJeu[y1][x1]='1';
		matriceJeu[y1-1][x1-2]='2';
		matriceJeu[y1 -1][x1 + 2]='3';
		/* Choix possible pour le positionement */
		sprintf(buffer,"\nMSG[1]{x=%i y=%i}\n[2]{x=%i y=%i}\n[3]{x=%i y=%i}\n",x1,y1,x1-2,y1-1,x1+2,y1-1);
		send_all_tour(tab_joueur, j, nb_client, 1);
		envoie_map(matriceJeu, tab_joueur, j, nb_client);


		do{
			sprintf(buffer,"Le joueur %d choisit ou se placer ... ", j+1);
			send_all_tour(tab_joueur, j, nb_client, 3);
			if(nb_client==2)
				x=2;
			else
				x=1;
			for(i=0; i<x; i++){
				sprintf(buffer,"Où voulez vous placer votre %s ?", tab_joueur[j]->perso1->nom);
				send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);
				/*reception du/des choix*/
				memset(buffer, 0, sizeof(buffer));
				recv(tab_joueur[j]->client_socket,buffer,BUFFER_LEN, 0);
			}
		}while( ((choix1 < 1)||(choix1 >3)) || ((choix2 < 1)||(choix2 >3)) || (choix1 == choix2) );



	}//fin for










}


int serveur (int nb_joueur,t_personnage * persos [CLASSES+1], t_equipe * equipe1, t_equipe * equipe2){
	int ma_socket;
	//int client_socket[N];
	struct sockaddr_in mon_address, client_address;
	unsigned int mon_address_longueur, lg;
	bzero(&mon_address,sizeof(mon_address));
	mon_address.sin_port = htons(30000);
	mon_address.sin_family = AF_INET;
	mon_address.sin_addr.s_addr = htonl(INADDR_ANY);

	char *hostname = "localhost";
    char ip[100];

    hostname_to_ip(hostname , ip);
	fprintf(stderr, "%s resolved to %s" , hostname , ip);
	view_ip();

	/* creation de socket */
	if ((ma_socket = socket(AF_INET,SOCK_STREAM,0))== -1) {
		printf("Impossible de créer la socket\n");
		exit(0);
	}

	/* bind serveur - socket */
	bind(ma_socket,(struct sockaddr *)&mon_address,sizeof(mon_address));
	/* ecoute sur la socket */
	listen(ma_socket,5);
	/* accept la connexion */
	mon_address_longueur = sizeof(client_address);


	//Boucle qui permet de garder le serveur ouvert prêt à relancer une nouvelle fin_partie
	//Tant que l'on à pas fermé le serveur avec un ctrl+c (    )ou sur la croix (sdl_quit)
	//while()

  /* on attend que les clients se connecte */
	int nb_client=0;
	t_equipe * tab_joueur[nb_joueur];

	for(int i = 0; i < nb_joueur;i++)
		tab_joueur[i] = malloc(sizeof(t_equipe));


	while (nb_client < nb_joueur) {
		printf("En attente de connection\n");
		tab_joueur[nb_client]->client_socket = accept(ma_socket,(struct sockaddr *)&client_address,&mon_address_longueur);
		nb_client++;
		printf("Nb de client connecté : %d\n", nb_client);
	}
	printf("tous les joueurs sont ready !\n");

	int i=0, j;

	memset(buffer, 0, sizeof(buffer));

	//demande aux joueurs son équipe
	int membre_team1=0, membre_team2=0;
	for(j=0;j < nb_client;j++){

		sprintf(buffer,"Choissisez votre équipe :\n");
		send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);

		sprintf(buffer,"Le joueur %d choisit son équipe :\n",j+1);
		send_all_tour(tab_joueur, j, nb_client, 3);

		memset(buffer, 0, sizeof(buffer));
		recv(tab_joueur[j]->client_socket, buffer, BUFFER_LEN,0);
		//verif si les equipes sont complete
		if(atoi(buffer+4) == 1 && membre_team1>=nb_client/2){
			sprintf(buffer,"Il n'y a plus de place dans l'équipe 1 :( vous allez rejoindre l'autre équipe\n");
			send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);
			tab_joueur[j]->numEquipe = 2;
		}
		else if(atoi(buffer+4) == 2 && membre_team2>=nb_client/2){
			sprintf(buffer,"Il n'y a plus de place dans l'équipe 2 :( vous allez rejoindre l'autre équipe\n");
			send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);
			tab_joueur[j]->numEquipe = 1;
		}
		else
			tab_joueur[j]->numEquipe = atoi(buffer+4);


		if(atoi(buffer+4)==1)
			membre_team1++;
		else if(atoi(buffer+4)==2)
			membre_team2++;

		sprintf(buffer,"Le joueur %d a choisit l'équipe : %d\n",j+1 ,tab_joueur[j]->numEquipe);
		send_all_tour(tab_joueur, j, nb_client, 3);
		fprintf(stderr,"Le joueur %d a choisit l'équipe : %d\n",j+1 ,tab_joueur[j]->numEquipe);
	}//fin for

	//demande aux joueurs son ou ses persos
	for(int j=0;j < nb_client;j++){
		int classe,classe2;
		char chaine[BUFFER_LEN];
		//si il y a quatre joueurs
		if(nb_client==4){
			sprintf(buffer,"Choissisez votre classe :\n");
			send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);

			sprintf(chaine,"[%d] : %s\n",1,persos[1]->nom);
			for(i = 2; i <= CLASSES; i++){
				sprintf(buffer,"[%d] : %s\n",i,persos[i]->nom);
				strcpy(chaine,strcat(chaine,	buffer));
			}
			sprintf(buffer,"%s\n",chaine);
			send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);

			sprintf(buffer,"Le joueur %d choisit sa classe :\n",j+1);
			send_all_tour(tab_joueur, j, nb_client, 3);

			memset(buffer, 0, sizeof(buffer));
			recv(tab_joueur[j]->client_socket, buffer, BUFFER_LEN,0);
			classe = atoi(buffer+4);
			if(strncmp("MSG", buffer, 3)==0){
				tab_joueur[j]->perso1 = copie_perso(persos[classe]);
				sprintf(buffer,"Le joueur %d a choisit sa classe : %s\n",j+1 ,tab_joueur[j]->perso1->nom);
				send_all_tour(tab_joueur, j, nb_client, 3);
				fprintf(stderr,"Le joueur %d a choisit la classe : %s\n",j+1 ,tab_joueur[j]->perso1->nom);
			}
		}

		//si il y a deux joueurs
		else{
			sprintf(buffer,"Choissisez vos classes :\n");
			send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);

			//affiche les choix possible et les envoies au client
			sprintf(chaine,"[%d] : %s\n",1,persos[1]->nom);
			for(i = 2; i <= CLASSES; i++){
				sprintf(buffer,"[%d] : %s\n",i,persos[i]->nom);
				strcpy(chaine,strcat(chaine,	buffer));
			}
			sprintf(buffer,"%s\n",chaine);
			send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);

			sprintf(buffer,"Le joueur %d choisit ses classes :\n",j+1);
			send_all_tour(tab_joueur, j, nb_client, 3);

			memset(buffer, 0, sizeof(buffer));
			//choix 1er classe
			recv(tab_joueur[j]->client_socket, buffer, BUFFER_LEN,0);
			classe = atoi(buffer+4);
			memset(buffer, 0, sizeof(buffer));
			//choix 2e classe
			recv(tab_joueur[j]->client_socket, buffer, BUFFER_LEN,0);
			classe2 = atoi(buffer+4);
			if(strncmp("MSG", buffer, 3)==0){
				tab_joueur[j]->perso1 = copie_perso(persos[classe]);
				tab_joueur[j]->perso2 = copie_perso(persos[classe2]);
				sprintf(buffer,"Le joueur %d a choisit ses classe : %s , %s\n",j+1 ,tab_joueur[j]->perso1->nom, tab_joueur[j]->perso2->nom);
				send_all_tour(tab_joueur, j, nb_client, 3);
				fprintf(stderr,"Le joueur %d a choisit les classes : %s , %s\n",j+1 ,tab_joueur[j]->perso1->nom, tab_joueur[j]->perso2->nom);
			}
		}
	}

	//initialisation partie
	initialisation_partie(map,equipe1,equipe2,nb_client,tab_joueur,j);
	//memcpy(buffer, map, sizeof(char)*N*N);
	fprintf(stderr,"===================================================\n\tDEMARRAGE DE LA  PARTIE\n===================================================\n");
	maj(map,equipe1,equipe2);
 	affichage_map(map);



	//boucle de partie
	int fin_partie=0, j_connect = nb_client,x=0;
	int liste_deco[nb_client];
  while(!fin_partie){

		//boucle d'un tour
		for( j=0; j < nb_client; j++){
			//on verifie que le joueur est connecté
			int verif=0;
			for( i=0; liste_deco[i] < nb_client; i++)
				if(j==liste_deco[i])
					verif=1;

			if(verif==0){
				memset(buffer, 0, sizeof(buffer));

				fprintf(stderr,"Tour de j%d \n", j);

				if(j_connect>0){
					//Annonce au joueur j que c'est son tour
					sprintf(buffer,"Cest votre tour");
					send(tab_joueur[j]->client_socket, buffer, BUFFER_LEN, 0);

					//Annonce aux autres joueurs que c'est le tour de j
					sprintf(buffer,"\n Cest le tour du joueur %d\n", j+1);
					send_all_tour(tab_joueur, j, nb_client, 3);

					//On attend les actions du joueur
					memset(buffer, 0, sizeof(buffer));
					lg = recv(tab_joueur[j]->client_socket, buffer, BUFFER_LEN,0);
					printf("Recu %i octets\n", lg);
					if(strncmp("MSG", buffer, 3)==0){
						printf(" message reçu : '%s'\n",buffer+4);
						//envoyer la réponse à tous
						send_all_tour(tab_joueur, j, nb_client, 1);
					}
					else if(strncmp("QUITTER", buffer, 7) == 0) {
						printf(" déconnexion demandée : '%s'\n",buffer);
						//nombre de joueurs encore connecté
						j_connect--;
						//Annonce aux autres joueurs que j est déco
						sprintf(buffer,"Le joueur %d vient de se déconnecter\n", j+1);
						send_all_tour(tab_joueur, j, nb_client, 3);
						//on met le joueur deco dans une liste de personne deco
						liste_deco[x]=j;
						//fprintf(stderr,"joueur co : %d\n", j_connect);
						shutdown(tab_joueur[j]->client_socket,SHUT_RDWR);//  desactive les futurs envois et receptions
						close(tab_joueur[j]->client_socket);
					}
					// permet de vérifier si la connection avec un client déconnecter est bien fermée
					else {
						printf("[serveur] message inconnu : '%s'\n", buffer);
					}
					//fermeture de la partie si tout les joueurs sont déconnecté
					if(j_connect == 0){
							fin_partie=1;
					}
				}//fin if
			}//fin if verif
		}//fin for
	}//fin while

	shutdown(ma_socket,2);
	close(ma_socket);
	return 0;
}




/*
 cree des fonctions pour chaque etapes
apres le premier joueur ca n'affiche plus que c'est a un autre de choisir ses classes

	faire une boucle de jeu pour ne pas fermer le serveur mais juste la fin_partie
	gerer reprise deco par ia
	gerer la gestion du ctrl+c (Pour serv et client)
	implementer le jeu
		- pas oublier de gere la fin de fin_partie
		- envoie des données
*/
