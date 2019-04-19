#nom du Projet
TARGETS = main test_ia client serveur test_reseau #sdl_test


CC = gcc
#flags (maths et reseau)
CFLAGS = -lm
FLAGS=-Wall -g -I. -lm

OBJ = main.o init.o affichages.o persosorts.o sorts.o deplacement.o tour_jeu.o effets.o fin_partie.o

OBJ_SDL = sdl_test.o affichages.o init.o persosorts.o

OBJ_SORTS = sorts.o persosorts.o affichages.o
OBJ_IA = sorts.o ia.o affichages.o persosorts.o fin_partie.o effets.o tour_jeu.o deplacement.o

OBJ_RESEAU = main.o init.o affichages.o persosorts.o sorts.o deplacement.o tour_jeu.o effets.o fin_partie.o client.o serveur.o

# on mets chaque fichier dans le dossier lui correspondant
SRCDIR = src
OBJDIR = objetcs
BINDIR = bin
TRGS := $(TARGETS:%=$(BINDIR)/%)

DIRS = $(OBJDIR) $(BINDIR)

all: $(DIRS) $(TRGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS	 := $(TARGETS:%=$(OBJDIR)/%.o)
# Liste des fichiers .o sans ceux contenant un main
OBJS	 := $(filter-out $(MAINS),$(OBJECTS))
rm       = rm -f


SDL_DIR=${HOME}/Documents/Projet/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR}

# main: $(OBJ) fonc.h
# 	$(CC) $(OBJ) -o $@
# test_ia: $(OBJ_IA) fonc.h
# 	$(CC) $(OBJ_IA) -o $@  $(CFLAGS)
# #executable SDL
# sdl_test: $(OBJ_SDL) fonc.h
# 	$(CC) $(OBJ_SDL) -o $@ ${LIBS} ${INCLUDES}
# #serveur
# serveur: serveur.o
# 	$(CC) -o $@ $<
# #client
# client: client.o main_client.o
# 	$(CC) -o $@ $^ $(LDFLAGS)
# #test main reseau
# test_reseau: $(OBJ_RESEAU) in.h socket.h client
# 	$(CC) $(OBJ_RESEAU) -o $@
# executable
#$(BINDIR)/$(TARGET): $(OBJECTS)
$(TRGS): $(OBJECTS)
	$(CC) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(FLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

# #génération des .o
# main.o: main.c fonc.h
# 	$(CC) -c $<
# init.o: init.c fonc.h
# 	$(CC) -c $<
# affichages.o: affichages.c fonc.h
# 	$(CC) -c $<
# persosorts.o: persosorts.c fonc.h
# 	$(CC) -c $<
# sorts.o: sorts.c fonc.h
# 	$(CC) -c $<
# deplacement.o: deplacement.c fonc.h
# 	$(CC) -c $<
# tour_jeu.o: tour_jeu.c fonc.h
# 	$(CC) -c $<
# effets.o :effets.c fonc.h
# 	$(CC) -c $<
# fin_partie.o : fin_partie.c fonc.h
# 	$(CC) -c $<
# ia.o : ia.c fonc.h
# 	$(CC) -c $<
#
# #reseau
# serveur.o: serveur.c
# 	$(CC) -o $@ -c $< $(FLAGS)
# client.o: client.c
# 	$(CC) -o $@ -c $< $(FLAGS)
# main_client.o: main_client.c
# 	$(CC) -o $@ -c $< $(FLAGS)
#
# #SDL
# sdl_test.o: sdl_test.c fonc.h
# 	$(CC) -c $< ${LIBS} ${INCLUDES}

.PHONY: clean
clean:
	- rm -rf $(OBJECTS)
	- rm $(BINDIR)/$(TARGETS)
	@echo "Cleanup complete!"


mrproper: clean

tests :
	./main
