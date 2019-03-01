#include <stdio.h>
#include <stdlib.h>
#include "fonc.h" 

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

		perso.nom="https://github.com/MariusVitta/tacticsarenaGuerrier";
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
		ligne.nom="Ligne";
		ligne.portee=7;
		ligne.degat=-14;
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

