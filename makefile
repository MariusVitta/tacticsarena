OBJ = main.o init.o fonc.o persosorts.o foncjeu.o deplacement.o tour_jeu.o

OBJ_COUP_ZONE = fonc.o coup_zone.o init.o foncjeu.o persosorts.o

OBJ_PTIT_COUP = fonc.o petit_coup.o init.o foncjeu.o persosorts.o

OBJ_DOUBLE_TAPE = fonc.o double_tape.o init.o foncjeu.o persosorts.o

test: $(OBJ) fonc.h
	gcc $(OBJ) -o test

test_coup_zone: $(OBJ_COUP_ZONE) fonc.h
	gcc $(OBJ_COUP_ZONE) -o test_coup_zone

test_petit_coup: $(OBJ_PTIT_COUP) fonc.h
	gcc $(OBJ_PTIT_COUP) -o $@

test_double_tape: $(OBJ_DOUBLE_TAPE) fonc.h
	gcc $(OBJ_DOUBLE_TAPE) -o $@

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
coup_zone.o: coup_zone.c fonc.h
	gcc -c $<
petit_coup.o: petit_coup.c fonc.h
	gcc -c $<
double_tape.o: double_tape.c fonc.h
	gcc -c $<


all: test test_coup_zone test_petit_coup

clean:
	- rm -rf *.o
	- rm test
	- rm test_coup_zone
	- rm test_petit_coup
	- rm test_double_tape

mrproper: clean

tests :
	./test
