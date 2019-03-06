test: main.o init.o fonc.o persosorts.o foncjeu.o deplacement.o fonc.h
	gcc main.o init.o fonc.o persosorts.o foncjeu.o  deplacement.o -o test
main.o: main.c fonc.h
	gcc -c main.c
init.o: init.c fonc.h
	gcc -c init.c
fonc.o: fonc.c fonc.h
	gcc -c fonc.c
persosorts.o: persosorts.c fonc.h
	gcc -c persosorts.c
foncjeu.o: foncjeu.c fonc.h
	gcc -c foncjeu.c
deplacement.o: deplacement.c fonc.h
	gcc -c deplacement.c
clean:
	rm -rf *.o
mrproper: clean
