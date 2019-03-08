OBJ = main.o init.o fonc.o persosorts.o foncjeu.o deplacement.o tour_jeu.o

test: $(OBJ) fonc.h
	gcc $(OBJ) -o test

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
tour_jeu.o: tour_jeu.c fonc.h
	gcc -c $<

#
# test sur la fonction tour
#
#test_tour_jeu: tour_jeu.o fonc.

clean:
	- rm -rf *.o
	- rm test

mrproper: clean

tests :
	./test
