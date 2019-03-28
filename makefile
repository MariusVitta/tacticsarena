CFLAGS = -lm
OBJ = main.o init.o affichages.o persosorts.o sorts.o deplacement.o tour_jeu.o attire.o chenchen.o bigshaq.o sortseffet.o effets.o fin_partie.o fuego.o

OBJ_INIT = init.o affichages.o persosorts.o sorts.o test_init.o tour_jeu.o deplacement.o

OBJ_ATTIRE = affichages.o attire.o init.o sorts.o persosorts.o

OBJ_SDL = sdl_main.o sdl_affichage.o sdl_fenetre.o sdl_outils.o sdl_jeu.o sdl_sorts.o fonc.o init.o persosorts.o foncjeu.o

OBJ_ORDI = affichages.o persosorts.o fonctions_ordi.o fin_partie.o

OBJ_IA = sorts.o ia.o affichages.o persosorts.o fin_partie.o

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
test_ordi: $(OBJ_ORDI) fonc.h
	gcc $(OBJ_ORDI) -o $@
test_ia: $(OBJ_IA) fonc.h
	gcc $(OBJ_IA) -o $@  $(CFLAGS)

#executable SDL
sdl_main: $(OBJ_SDL) sdl_fonc.h fonc.h
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
fonctions_ordi.: fonctions_ordi.c fonc.h
	gcc -c $<
ia.o: ia.c fonc.h
	gcc -c $<
#%.o: %.c fonc.h
#	gcc -c $<
# SDL

sdl_main.o: sdl_main.c sdl_fonc.h fonc.h
	gcc -c $< ${LIBS} ${INCLUDES}

sdl_affichage.o: sdl_affichage.c sdl_fonc.h fonc.h
	gcc -c $< ${LIBS} ${INCLUDES}

sdl_fenetre.o:	sdl_fenetre.c sdl_fonc.h fonc.h
	 gcc -c $< ${LIBS} ${INCLUDES}

sdl_outils.o: sdl_outils.c sdl_fonc.h fonc.h
	gcc -c $< ${LIBS} ${INCLUDES}

sdl_jeu.o: sdl_jeu.c sdl_fonc.h fonc.h
	gcc -c $< ${LIBS} ${INCLUDES}

sdl_sorts.o: sdl_sorts.c sdl_fonc.h fonc.h
	gcc -c $< ${LIBS} ${INCLUDES}

#SDL

all: main sdl_main test_init test_attire test_ordi

clean:
	- rm -rf *.o
	- rm main
	- rm test_init
	- rm test_attire
	- rm sdl_main
	- test_ordi
	- test_ia

mrproper: clean

tests :
	./main
