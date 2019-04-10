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

#define QUITTER "QUITTER"

char menu(){
	char choix;
	printf("Que voulez-vous faire ?\n");
	printf("m: envoyer un message au serveur\n");
	printf("q: quitter\n");
	printf("Que voulez-vous faire ?\n");
	scanf(" %c", &choix);
	return choix;
}

char menu_equipe(){
	char choix;
	printf("Equipe 1 : [1] ou Equipe : [2]\n");
	scanf(" %c", &choix);
	return choix;
}

char menu_classe(){
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
	}while(strncmp("Choissisez votre équipe :\n", buffer,BUFFER_LEN) != 0);

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
		printf("%s \n", buffer);
	}while((strncmp("Choissisez votre classe :\n", buffer,BUFFER_LEN) != 0) && (strncmp("Choissisez vos classes :\n", buffer,BUFFER_LEN) != 0));

	//permet de savoir combien de persos il faut selectionner
	int x,i;

	if(strncmp("Choissisez vos classes :\n", buffer,BUFFER_LEN) == 0)
		x=2;
	else
		x=1;

	recv(to_server_socket,buffer,BUFFER_LEN, 0);
	do{
		for(i=1;i<=x;i++){
			printf("%s \n", buffer);
			choix = menu_classe();
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

	//reception matrice choix placement
	recv(to_server_socket,buffer,BUFFER_LEN, 0);

	do{
		memset(buffer, 0, sizeof(buffer));
		recv(to_server_socket,buffer,BUFFER_LEN, 0);
		printf("%s \n", buffer);
	}while((strncmp("Choissisez votre classe :\n", buffer,BUFFER_LEN) != 0) && (strncmp("Choissisez vos classes :\n", buffer,BUFFER_LEN) != 0));



	do {

		/* En attente de son tour */
		memset(buffer, 0, sizeof(buffer));
		do{
				memset(buffer, 0, sizeof(buffer));
				recv(to_server_socket,buffer,BUFFER_LEN, 0);
				printf("%s \n", buffer);
		}while(strncmp("Cest votre tour", buffer,BUFFER_LEN) != 0);


		do{
			oui=1;
			//uniquement pour la première action
			// on vide le buffer d'entré pour éviter que le joueur rentre des actions en dehors de son tour
			while ((choix=getchar()) != EOF && choix!= '\n');
				//fprintf(stderr, "Je vide le buffer\n");

			choix = menu();
				char buffer[BUFFER_LEN];
			switch(choix){
				case 'm':
					memset(buffer, 0, sizeof(buffer));
					printf("Saisissez votre message : ");
					scanf(" %[^\n]s", buffer);
					envoyer_message(to_server_socket,buffer);
					break;
				case 'q':
					quitter(to_server_socket);
					break;
				default:
					printf("Commande '%c' invalide... recommencez\n", choix);
					break;
			}
		}while(choix!='m' && choix!='q');

	} while (choix != 'q');

	/* fermeture de la connexion */
	shutdown(to_server_socket,SHUT_RDWR);
	close(to_server_socket);
	return 0;
}
