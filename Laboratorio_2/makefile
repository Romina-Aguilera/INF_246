main: ejecucion.out
	./ejecucion.out

ejecucion.out: main.o
	gcc main.o -o ejecucion.out -Wall

main.o: main.c jugador.h
	gcc -c main.c -Wall


.PHONY: clean

clean:
	rm *.o
	rm *.out
