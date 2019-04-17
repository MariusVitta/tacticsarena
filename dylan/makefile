CC = gcc
CFLAGS = -lm
FLAGS=-Wall -g
OBJ = main.o init.o affichages.o persosorts.o sorts.o deplacement.o tour_jeu.o effets.o fin_partie.o

OBJ_SDL = sdl_test.o affichages.o init.o persosorts.o

OBJ_SORTS = sorts.o persosorts.o affichages.o
OBJ_IA = sorts.o ia.o affichages.o persosorts.o fin_partie.o effets.o

OBJ_RESEAU = main.o init.o affichages.o persosorts.o sorts.o deplacement.o tour_jeu.o effets.o fin_partie.o client.o serveur.o

SDL_DIR=${HOME}/Documents/Projet/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR}

main: $(OBJ) fonc.h
	$(CC) $(OBJ) -o $@
test_perso: $(OBJ_SORTS) fonc.h
	$(CC) $(OBJ_SORTS) -o $@
test_ia: $(OBJ_IA) fonc.h
	$(CC) $(OBJ_IA) -o $@  $(CFLAGS)
#executable SDL
sdl_test: $(OBJ_SDL) fonc.h
	$(CC) $(OBJ_SDL) -o $@ ${LIBS} ${INCLUDES}
#serveur
serveur: serveur.o
	$(CC) -o $@ $<
#client
client: client.o main_client.o
	$(CC) -o $@ $^ $(LDFLAGS)
#test main reseau
test_reseau: $(OBJ_RESEAU) in.h socket.h client
	$(CC) $(OBJ_RESEAU) -o $@

#génération des .o
main.o: main.c fonc.h
	$(CC) -c $<
init.o: init.c fonc.h
	$(CC) -c $<
affichages.o: affichages.c fonc.h
	$(CC) -c $<
persosorts.o: persosorts.c fonc.h
	$(CC) -c $<
sorts.o: sorts.c fonc.h
	$(CC) -c $<
deplacement.o: deplacement.c fonc.h
	$(CC) -c $<
tour_jeu.o: tour_jeu.c fonc.h
	$(CC) -c $<
effets.o :effets.c fonc.h
	$(CC) -c $<
fin_partie.o : fin_partie.c fonc.h
	$(CC) -c $<
ia.o : ia.c fonc.h
	$(CC) -c $<

#reseau
serveur.o: serveur.c
	$(CC) -o $@ -c $< $(FLAGS)
client.o: client.c
	$(CC) -o $@ -c $< $(FLAGS)
main_client.o: main_client.c
	$(CC) -o $@ -c $< $(FLAGS)

#SDL
sdl_test.o: sdl_test.c fonc.h
	$(CC) -c $< ${LIBS} ${INCLUDES}

all: main sdl_test test_perso test_ia client serveur test_reseau

clean:
	- rm -rf *.o
	- rm main
	- rm sdl_test
	- rm test_perso
	- rm test_ia
	- rm test_reseau
	- rm client

mrproper: clean

tests :
	./main
