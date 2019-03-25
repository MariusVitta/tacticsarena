OBJ = main.o init.o affichages.o persosorts.o sorts.o deplacement.o tour_jeu.o attire.o chenchen.o bigshaq.o sortseffet.o effets.o fin_partie.o fuego.o

OBJ_INIT = init.o affichages.o persosorts.o sorts.o test_init.o tour_jeu.o deplacement.o

OBJ_ATTIRE = affichages.o attire.o init.o sorts.o persosorts.o

OBJ_SDL = sdl_test.o affichages.o init.o persosorts.o

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
affichages.o: affichages.c fonc.h
	gcc -c $<
persosorts.o: persosorts.c fonc.h
	gcc -c $<
sorts.o: sorts.c fonc.h
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
chenchen.o :chenchen.c fonc.h
	gcc -c $<
sortseffet.o :sortseffet.c fonc.h
	gcc -c $<
effets.o :effets.c fonc.h
	gcc -c $<
fin_partie.o : fin_partie.c fonc.h
	gcc -c $<
fuego.o : fuego.c fonc.h
	gcc -c $<
#SDL
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
