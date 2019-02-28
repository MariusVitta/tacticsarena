#include <stdio.h>
#include <stdlib.h>

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
		soin.degat=-10;
		soin.point_action=1;

		t_sort ptitcoup;
		ptitcoup.nom="Ptitcoup";
		ptitcoup.portee=3;
		ptitcoup.degat=10;
		ptitcoup.point_action=1;
		
		t_sort groscoup;
		groscoup.nom="Groscoup";
		groscoup.portee=1;
		groscoup.degat=20;
		groscoup.point_action=1;

		perso.nom="Guerrier";
		perso.pv=60;
		perso.pa=1;
		perso.s1=saut;
		perso.s2=soin;
		perso.s3=ptitcoup;
		perso.s4=groscoup;

		return perso;
	}

	if(classe==2){
		t_sort diago;
		diago.nom="Diago";
		diago.portee=3;
		diago.degat=0;
		diago.point_action=2;
		
		t_sort ligne;
		ligne.nom="ligne";
		ligne.portee=0;
		ligne.degat=-10;
		ligne.point_action=2;

		t_sort doubletape;
		doubletape.nom="Doubletape";
		doubletape.portee=3;
		doubletape.degat=10;
		doubletape.point_action=1;
		
		t_sort coupzone;
		coupzone.nom="Coupzone";
		coupzone.portee=1;
		coupzone.degat=20;
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