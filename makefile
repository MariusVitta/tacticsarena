test: main.o init.o fonc.o persosorts.o foncjeu.o init.h fonc.h
	gcc main.o init.o fonc.o persosorts.o foncjeu.c -o test
main.o: main.c fonc.h
	gcc -c main.c
init.o: init.c init.h
	gcc -c init.c
fonc.o: fonc.c fonc.h
	gcc -c fonc.c
persosorts.o: persosorts.c fonc.h
	gcc -c persosorts.c
foncjeu.o: foncjeu.c fonc.h
	gcc -c foncjeu.c
clean:
	rm -rf *.o
mrproper: clean
