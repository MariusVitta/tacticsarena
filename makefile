<<<<<<< HEAD
OBJ = main.o init.o fonc.o persosorts.o foncjeu.o deplacement.o tour_jeu.o attire.o chenchen.o bigshaq.o sortseffet.o effets.o
=======
OBJ = main.o init.o fonc.o persosorts.o foncjeu.o deplacement.o tour_jeu.o attire.o bigshaq.o sortseffet.o effets.o chenchen.o
>>>>>>> 07a0ab859c12dc614534bd001dd3148df20ba3bd

OBJ_INIT = init.o fonc.o persosorts.o foncjeu.o test_init.o tour_jeu.o deplacement.o

OBJ_ATTIRE = fonc.o attire.o init.o foncjeu.o persosorts.o

OBJ_SDL = sdl_test.o fonc.o init.o persosorts.o

SDL_DIR=${HOME}/Documents/Projet/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR}

main: $(OBJ) fonc.h
	gcc $(OBJ) -o $@
test_init: $(OBJ_INIT) fonc.h
	gcc $(OBJ_INIT) -o $@
test_attire: $(OBJ_ATTIRE) fonc.h
	gcc $(OBJ_ATTIRE) -o $@
#executable SDL
sdl_test: $(OBJ_SDL) fonc.h
	gcc $(OBJ_SDL) -o $@ ${LIBS} ${INCLUDES}

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
test_init.o :test_init.c fonc.h
	gcc -c $<
attire.o :attire.c fonc.h
	gcc -c $<
bigshaq.o :bigshaq.c fonc.h
	gcc -c $<
<<<<<<< HEAD
chenchen.o :chenchen.c fonc.h
	gcc -c $<
=======
>>>>>>> 07a0ab859c12dc614534bd001dd3148df20ba3bd
sortseffet.o :sortseffet.c fonc.h
	gcc -c $<
effets.o :effets.c fonc.h
	gcc -c $<
<<<<<<< HEAD
#SDL
=======
chenchen.o :chenchen.c fonc.h
	gcc -c $<

>>>>>>> 07a0ab859c12dc614534bd001dd3148df20ba3bd
sdl_test.o: sdl_test.c fonc.h
	gcc -c $< ${LIBS} ${INCLUDES}

all: main sdl_test test_init test_attire

clean:
	- rm -rf *.o
	- rm main
	- rm test_init
	- rm test_attire
	- rm sdl_test

mrproper: clean

tests :
	./main
