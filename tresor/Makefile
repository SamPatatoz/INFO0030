CC=gcc
LD=gcc
CFLAGS=
LDFLAGS=
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
DOXYGEN=doxygen

all: tresor

tresor: main.o controleur_tresor.o vue_tresor.o modele_tresor.o
	$(LD) -o tresor main.o vue_tresor.o controleur_tresor.o modele_tresor.o $(LDFLAGS) $(GTKFLAGS)

main.o: main.c vue_tresor.h controleur_tresor.h modele_tresor.h
	$(CC) -c main.c -o main.o $(CFLAGS) $(GTKFLAGS)

controleur_tresor.o: controleur_tresor.h controleur_tresor.c vue_tresor.h modele_tresor.h
	$(CC) -c controleur_tresor.c -o controleur_tresor.o $(CFLAGS) $(GTKFLAGS)	

vue_tresor.o: vue_tresor.h vue_tresor.c controleur_tresor.h modele_tresor.h
	$(CC) -c vue_tresor.c -o vue_tresor.o $(CFLAGS) $(GTKFLAGS)

modele_tresor.o: modele_tresor.h modele_tresor.c
	$(CC) -c modele_tresor.c -o modele_tresor.o $(CFLAGS) $(GTKFLAGS)

doc: 
	mkdir doc
	$(DOXYGEN) Doxyfile

archive:
	tar -zcvf tresor.tar.gz *.h *.c *.jpg Makefile Doxyfile

clean:
	rm -f *.o
	rm -f tresor
	-rm -r doc
	clear
