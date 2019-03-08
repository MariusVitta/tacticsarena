OBJ = main.o init.o fonc.o persosorts.o foncjeu.o deplacement.o

OBJ_COUP_ZONE = fonc.o coup_zone.o init.o foncjeu.o persosorts.o

test: $(OBJ) fonc.h
	gcc $(OBJ) -o test

test_coup_zone: $(OBJ_COUP_ZONE) fonc.h
	gcc $(OBJ_COUP_ZONE) -o test_coup_zone

#génération des .o
main.o: main.c fonc.h
	gcc -c $<
init.o: init.c fonc.h
	gcc -c $<
fonc.o: fonc.c fonc.h
	gcc -c $<
persosorts.o: persosorts.c fonc.h
	gcc -c $<
foncjeu.o: foncjeu.c fonc.h
	gcc -c $<
deplacement.o: deplacement.c fonc.h
	gcc -c $<
<<<<<<< HEAD
=======
tour_jeu.o: tour_jeu.c fonc.h
	gcc -c $<
coup_zone.o: coup_zone.c fonc.h
	gcc -c $<
>>>>>>> 160550df12d8e009f92494604f22a80338159563

all: test test_coup_zone

clean:
	- rm -rf *.o
	- rm test
	- rm test_coup_zone

mrproper: clean

tests :
	./test
