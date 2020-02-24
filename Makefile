build: functiiLista.o functiiStiva.o functiiCoada.o
	gcc functiiLista.o functiiStiva.o functiiCoada.o tema.c -o tema2

functiiLista.o: functiiLista.c
	gcc -c functiiLista.c

functiiStiva.o: functiiStiva.c
	gcc -c functiiStiva.c

functiiCoada.o: functiiCoada.c
	gcc -c functiiCoada.c

clean:
	rm -rf *.o *.out tema2
