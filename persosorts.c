#include <stdio.h>
#include <stdlib.h>

/*création d'un sort ayant un nom,une portée,des dégats et un nombre de points d'actions pour pouvoir l'utiliser*/

typedef struct s_sort{

	char * nom;
	int portee;
	int degat;
	int point_action;

}t_sort;

/*création d'un personnage ayant un nom, des points de vie, des points d'actions lui permettant d'utiliser ses sorts et 4sorts*/

typedef struct s_personnage{

	char* nom;
	int pv;
	int pa;
	t_sort s1,s2,s3,s4;

}t_personnage;

/*création de la classe choisie par l'utilisateur*/

t_personnage creer_perso(int classe,t_personnage perso){

	if(classe==1){
		t_sort saut;
		saut.nom="Saut";
		saut.portee=3;
		saut.degat=0;
		saut.point_action=1;
		
		t_sort soin;
		soin.nom="Soin";
		soin.portee=0;
		soin.degat=-6;
		soin.point_action=1;

		t_sort ptitcoup;
		ptitcoup.nom="Ptitcoup";
		ptitcoup.portee=3;
		ptitcoup.degat=10;
		ptitcoup.point_action=1;
		
		t_sort groscoup;
		groscoup.nom="Groscoup";
		groscoup.portee=1;
		groscoup.degat=25;
		groscoup.point_action=2;

		perso.nom="Guerrier";
		perso.pv=60;
		perso.pa=2;
		perso.s1=saut;
		perso.s2=soin;
		perso.s3=ptitcoup;
		perso.s4=groscoup;

		return perso;
	}

	if(classe==2){
		t_sort diago;
		diago.nom="Diago";
		diago.portee=7;
		diago.degat=14;
		diago.point_action=2;
		
		t_sort ligne;
		ligne.nom="ligne";
		ligne.portee=7;
		ligne.degat=14;
		ligne.point_action=2;

		t_sort doubletape;
		doubletape.nom="Doubletape";
		doubletape.portee=5;
		doubletape.degat=6;
		doubletape.point_action=1;
		
		t_sort coupzone;
		coupzone.nom="Coupzone";
		coupzone.portee=5;
		coupzone.degat=12;
		coupzone.point_action=2;

		perso.nom="Archer";
		perso.pv=55;
		perso.pa=2;
		perso.s1=diago;
		perso.s2=ligne;
		perso.s3=doubletape;
		perso.s4=coupzone;

		return perso;
	}
}

int main(){

	int classe;
	t_personnage personnage;
	printf("choisir classe\n");
	scanf("%d",&classe);

	personnage=creer_perso(classe,personnage);

	printf("%s %s %s %s %s \n",personnage.nom,personnage.s1.nom,personnage.s2.nom,personnage.s3.nom,personnage.s4.nom);



}