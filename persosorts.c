#include <stdio.h>
#include <stdlib.h>
#include "fonc.h"

/*création de la classe choisie par l'utilisateur*/
t_personnage * creer_perso(int classe){

	t_personnage *perso = malloc(sizeof(t_personnage));


	if(classe==1){
		t_sort saut;
		saut.nom="Saut";
		saut.portee=3;
		saut.degat=0;
		saut.point_action=1;
		saut.cd=0;
		saut.uptm=1;

		t_sort soin;
		soin.nom="Soin";
		soin.portee=0;
		soin.degat=6;
		soin.point_action=1;
		soin.cd=0;
		soin.uptm=2;

		t_sort ptitcoup;
		ptitcoup.nom="Ptitcoup";
		ptitcoup.portee=3;
		ptitcoup.degat=10;
		ptitcoup.point_action=1;
		ptitcoup.cd=0;
		ptitcoup.uptm=2;

		t_sort groscoup;
		groscoup.nom="Groscoup";
		groscoup.portee=1;
		groscoup.degat=25;
		groscoup.point_action=2;
		groscoup.cd=0;
		groscoup.uptm=1;



		perso->nom="Guerrier";
		perso->pv=60;
		perso->pv_max=60;
		perso->pa=2;
		perso->pm=3;
		perso->s1=saut;
		perso->s2=soin;
		perso->s3=ptitcoup;
		perso->s4=groscoup;


	}

	if(classe==2){
		t_sort diago;
		diago.nom="Diago";
		diago.portee=7;
		diago.degat=14;
		diago.point_action=2;
		diago.cd=0;
		diago.uptm=1;

		t_sort ligne;
		ligne.nom="Ligne";
		ligne.portee=7;
		ligne.degat=14;
		ligne.point_action=2;
		ligne.cd=0;
		ligne.uptm=1;

		t_sort doubletape;
		doubletape.nom="Doubletape";
		doubletape.portee=5;
		doubletape.degat=6;
		doubletape.point_action=1;
		doubletape.cd=0;
		doubletape.uptm=2;

		t_sort coupzone;
		coupzone.nom="Coupzone";
		coupzone.portee=5;
		coupzone.degat=12;
		coupzone.point_action=2;
		coupzone.cd=0;
		coupzone.uptm=1;

		perso->nom="Archer";
		perso->pv=55;
		perso->pv_max=55;
		perso->pa=2;
		perso->pm=3;
		perso->s1=diago;
		perso->s2=ligne;
		perso->s3=doubletape;
		perso->s4=coupzone;


	}

	if(classe==3){
		t_sort armure;
		armure.nom="Armure";
		armure.portee=0;
		armure.point_action=1;
		armure.cd=2;
		armure.uptm=1;

		t_sort attire;
		attire.nom="Attire";
		attire.portee=15;
		attire.point_action=1;
		attire.cd=0;
		attire.uptm=1;

		t_sort chenchen;
		chenchen.nom="ChenChen";
		chenchen.portee=2;
		chenchen.degat=10;
		chenchen.point_action=1;
		chenchen.cd=0;
		chenchen.uptm=1;

		t_sort bigshaq;
		bigshaq.nom="BigShaq";
		bigshaq.portee=1;
		bigshaq.degat=0;
		bigshaq.point_action=2;
		bigshaq.cd=0;
		bigshaq.uptm=1;

		perso->nom="Tank";
		perso->pv=80;
		perso->pv_max=80;
		perso->pa=2;
		perso->pm=3;
		perso->s1=armure;
		perso->s2=attire;
		perso->s3=chenchen;
		perso->s4=bigshaq;

	}
	if(classe==4){

		t_sort felin;
		felin.nom="Transformation Felin";
		felin.portee=0;
		felin.point_action=1;
		felin.cd=2;
		felin.uptm=1;

		t_sort chouette;
		chouette.nom="Transformation Chouette";
		chouette.portee=15;
		chouette.point_action=1;
		chouette.cd=0;
		chouette.uptm=1;

		t_sort fuego;
		fuego.nom="Fuego";
		fuego.portee=4;
		fuego.degat=9;
		fuego.point_action=2;
		fuego.cd=0;
		fuego.uptm=1;

		t_sort revitalisation;
		revitalisation.nom="Revitalisation";
		revitalisation.portee=2;
		revitalisation.degat=8;
		revitalisation.point_action=2;
		revitalisation.cd=0;
		revitalisation.uptm=2;

		perso->nom="Druide";
		perso->pv=60;
		perso->pv_max=60;
		perso->pa=2;
		perso->pm=3;
		perso->s1=felin;
		perso->s2=chouette;
		perso->s3=fuego;
		perso->s4=revitalisation;

	}

	return perso;
}
