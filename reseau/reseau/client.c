#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<string.h>
#include "fonc.h"
#include "define.h"

//#define SERVEURNAME "192.168.1.106" // adresse IP de mon serveur
//#define SERVEURNAME "172.18.41.119" // adresse IP de mon serveur
int server_socket;
#define QUITTER "QUITTER"

char menu(){
	char choix;
	printf("Que voulez-vous faire ?\n");
	printf("m: Continuer \n");
	printf("q: quitter\n");
	scanf(" %c", &choix);
	return choix;
}

char menu_equipe(){
	char choix;
	printf("Equipe 1 : [1] ou Equipe 2 : [2]\n");
	scanf(" %c", &choix);
	return choix;
}

char menu_choix(){
	char choix;
	scanf(" %c", &choix);
	return choix;
}

void envoyer_message(int to_server_socket,char * m){
	char msg[200], buffer[BUFFER_LEN];
	strcpy(buffer,m);
	//memset(buffer, 0, sizeof(buffer));
	//scanf(" %[^\n]s", buffer);
	sprintf(msg, "MSG %s", buffer);
	send(to_server_socket, msg, strlen(msg), 0); //on augmente la taille de 4 pour l'entête
	// lecture de la réponse
	//memset(buffer, 0, sizeof(buffer));
	//recv(to_server_socket,buffer,BUFFER_LEN,0);
	//printf("Reponse du serveur : '%s'\n\n", buffer);
}

void affichage_map_reseau(char * buffer){

	printf(" ---- [Plan de jeu] ---- \n\n");
	printf("%s \n", buffer);

}

void choix_placement(int to_server_socket){
	char buffer[BUFFER_LEN];
	char choix;


	do{
		memset(buffer, 0, sizeof(buffer));
		recv(to_server_socket,buffer,BUFFER_LEN, 0);
		printf("%s \n", buffer);
	}while(strncmp("Initialisation \n", buffer,BUFFER_LEN) != 0);

	/*reception msg de choix*/
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket,buffer,BUFFER_LEN, 0);
	printf("%s \n", buffer);
	/*reception des cases possibles*/
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket,buffer,BUFFER_LEN, 0);
	printf("%s \n", buffer);
	/*reception map et affichage*/
	//affichage
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket,buffer,BUFFER_LEN, 0);
	affichage_map_reseau(buffer);

	/*Tant que ca n'est pas à ton tour de placer ton/tes perso*/
	do{
		memset(buffer, 0, sizeof(buffer));
		recv(to_server_socket,buffer,BUFFER_LEN, 0);
		printf("%s \n", buffer);
	}while(strncmp("Où voulez vous placer votre", buffer, strlen("Où voulez vous placer votre")) != 0);

	/*Lorsque c'est ton tour de placer ton/tes perso*/
	/*choix placement*/
	do{
		choix = menu_choix();
		envoyer_message(to_server_socket,&choix);
		memset(buffer, 0, sizeof(buffer));
		recv(to_server_socket,buffer,BUFFER_LEN, 0);
		printf("%s \n", buffer);
	}while(strncmp("Où voulez vous placer votre", buffer, strlen("Où voulez vous placer votre")) == 0);

}

void quitter(int to_server_socket){
	printf("[client] envoi message QUITTER au serveur\n");
	send(to_server_socket,QUITTER,7,0);
}

int client (  int argc, char** argv )
{
	struct sockaddr_in serveur_addr;
	struct hostent *serveur_info;
	long hostAddr;
	char buffer[BUFFER_LEN];
	int to_server_socket;
	//on recupère ici l'adresse du serveur passer en parametre
	char * SERVEURNAME = argv[1];

	// vérifie si il y a erreur lors de la récupération de l'adresse
	bzero(&serveur_addr,sizeof(serveur_addr));
	hostAddr = inet_addr(SERVEURNAME);
	if ( (long)hostAddr != (long)-1 ){
		bcopy(&hostAddr,&serveur_addr.sin_addr,sizeof(hostAddr));
	} else {
		serveur_info = gethostbyname(SERVEURNAME);
	  	if (serveur_info == NULL) {
			printf("Impossible de récupérer les infos du serveur\n");
			exit(0);
	  	}
	  	bcopy(serveur_info->h_addr,&serveur_addr.sin_addr,serveur_info->h_length);
	}


	//Spécification de l'adresse du socket : type / port
	serveur_addr.sin_family = AF_INET;
	serveur_addr.sin_port = htons(30000);  //<-- fonction de convertion pour le port
	//serveur_addr.sin_addr.s_addr = inet_addr(SERVEURNAME); //<-- connection local ( trouve l'ip )


	/* creation de la socket */
		//int socket(int domain, int type, int protocol)
	if ( (to_server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		printf("Impossible de créer la socket client\n");
	  	exit(0);
	}
	/* requete de connexion */
		//int connect(int socket, struct sockaddr* addr, socklen_t addrlen);
	if(connect( to_server_socket, (struct sockaddr *)&serveur_addr, sizeof(serveur_addr)) < 0 ) {
		printf("Impossible de se connecter au serveur\n");
	  	exit(0);
	}

	server_socket = to_server_socket;
	printf("En attente de connection des autres joueurs ...\n");
    /* Un menu pour faire differentes actions */
	char choix;
	int oui=0;

	//Choix équipe
	printf("Les joueurs selectionnent leur équipe ...\n");

	do{
		memset(buffer, 0, sizeof(buffer));
		recv(to_server_socket,buffer,BUFFER_LEN, 0);
		printf("%s \n", buffer);
	}while(strncmp("Choissisez votre équipe :\n", buffer, strlen("Choissisez votre équipe :\n")) != 0);

	// vérifie si le client a déjà taper quelque chose pour ne pas réafficher ce message
	if(oui==0)
		printf("Appuyez sur ENTRER pour continuer\n");

	do{
		oui=1;
		//uniquement pour la première action
		// on vide le buffer d'entré pour éviter que le joueur rentre des actions en dehors de son tour
		while ((choix=getchar()) != EOF && choix!= '\n');
			//fprintf(stderr, "Je vide le buffer\n");

		choix = menu_equipe();

		switch(choix){
			case '1':
				envoyer_message(to_server_socket,&choix);
				break;
			case '2':
				envoyer_message(to_server_socket,&choix);
				break;
			default:
				printf("Commande '%c' invalide... recommencez\n", choix);
				break;
			}
	}while(choix!='1' && choix!='2');

	//Choix persos
	do{
		memset(buffer, 0, sizeof(buffer));
		recv(to_server_socket,buffer,BUFFER_LEN, 0);
		printf(" %s \n", buffer);
	}while((strncmp("Choissisez votre classe :\n", buffer,strlen("Choissisez votre classe :\n")) != 0) && (strncmp("Choissisez vos classes :\n", buffer,strlen("Choissisez votre classe :\n")) != 0));

	//permet de savoir combien de persos il faut selectionner
	int x,i;

	if(strncmp("Choissisez vos classes :\n", buffer,BUFFER_LEN) == 0)
		x=2;
	else
		x=1;

		// réception des classes
	recv(to_server_socket,buffer,BUFFER_LEN, 0);
	do{
		for(i=1;i<=x;i++){
			printf("%s \n", buffer);
			choix = menu_choix();
			switch(choix){
				case '1':
				case '2':
				case '3':
				case '4':
					envoyer_message(to_server_socket,&choix);
					break;
				default:
					printf("Commande '%c' invalide... recommencez\n", choix);
					break;
			}
		}
	}while(choix!='1' && choix!='2' && choix!='3' && choix!='4');


	choix_placement(to_server_socket);

	do {

		/* En attente de son tour */
		do{
				memset(buffer, 0, sizeof(buffer));
				recv(to_server_socket,buffer,BUFFER_LEN, 0);
				printf("%s",buffer);
		}while(strncmp("Cest votre tour\n", buffer,BUFFER_LEN) != 0);


		do{
			oui=1;
			//uniquement pour la première action
			// on vide le buffer d'entré pour éviter que le joueur rentre des actions en dehors de son tour
			while ((choix=getchar()) != EOF && choix!= '\n');
				//fprintf(stderr, "Je vide le buffer\n");

			choix = menu();
			switch(choix){
				case 'm':
					memset(buffer, 0, sizeof(buffer));
					envoyer_message(to_server_socket, buffer);
					break;
				case 'q':
					quitter(to_server_socket);
					break;
				default:
					printf("Commande '%c' invalide... recommencez\n", choix);
					break;
			}
		}while(choix!='m' && choix!='q');

		if(choix=='m'){

			memset(buffer, 0, sizeof(buffer));
			do{
				/* reception des messages en attendant que l'on puisse faire une action */
				do{
					printf("on est dans al boucle  :\n");
					memset(buffer, 0, sizeof(buffer));
					recv(to_server_socket,buffer,BUFFER_LEN, 0);
					printf("%s",buffer);
				}while(strncmp(" ---- Quelle action souhaitez vous effectuer ? ---- ", buffer, strlen(" ---- Quelle action souhaitez vous effectuer ? ---- ")) != 0);
				printf("sortie boucle :\n");
				/* Choix de l'action */
					printf("Choix actions :\n");
				choix = menu_choix();
				memset(buffer, 0, sizeof(buffer));
				strcpy(buffer, &choix);
				envoyer_message(to_server_socket, buffer);

				if(choix=='1' || choix=='2'){
					/*Reception des choix possibles */
					printf("recep choix :\n");
					memset(buffer, 0, sizeof(buffer));
					recv(to_server_socket,buffer,BUFFER_LEN, 0);
					printf("%s",buffer);
					if(choix=='2'){
						/* Choix du client pour le sort */
						printf("Choix sort :\n");
						choix = menu_choix();
						memset(buffer, 0, sizeof(buffer));
						strcpy(buffer, &choix);
						envoyer_message(to_server_socket, buffer);
						/* reception map avec portee*/
						printf("recep portee :\n");
						memset(buffer, 0, sizeof(buffer));
						recv(to_server_socket,buffer,BUFFER_LEN, 0);
						printf("%s",buffer);

						/* reception msg d'info*/
						printf("recep info :\n");
						memset(buffer, 0, sizeof(buffer));
						recv(to_server_socket,buffer,BUFFER_LEN, 0);
						printf("%s",buffer);
					}
					/* parce que soin est relou faudra changer ca après */
					if(choix!='2'){
						/* Choix du client */
						printf("choix target :\n");
						choix = menu_choix();
						memset(buffer, 0, sizeof(buffer));
						strcpy(buffer, &choix);
						envoyer_message(to_server_socket, buffer);
					}
				}

				else{
					printf("si tu passe :\n");
					memset(buffer, 0, sizeof(buffer));
					recv(to_server_socket,buffer,BUFFER_LEN, 0);
				}
			}while(strncmp("\n ---- Vous avez passé votre tour ---- \n\n", buffer, strlen("\n ---- Vous avez passé votre tour ---- \n\n") != 0));

		}//fin if
		printf(" tiens tiens tiens");
		if(strncmp("===================================================\n\tAFFICHAGE COORDONNEES | FIN DU TOUR\n===================================================\n\n", buffer, strlen("===================================================\n\tAFFICHAGE COORDONNEES | FIN DU TOUR\n===================================================\n\n") == 0)){
			/*Affichage pour l'équipe 1*/
			memset(buffer, 0, sizeof(buffer));
			recv(to_server_socket,buffer,BUFFER_LEN, 0);
			/*Affichage pour l'équipe 2*/
			memset(buffer, 0, sizeof(buffer));
			recv(to_server_socket,buffer,BUFFER_LEN, 0);
		}

	} while (choix != 'q');

	/* fermeture de la connexion */
	shutdown(to_server_socket,SHUT_RDWR);
	close(to_server_socket);
	return 0;
}
