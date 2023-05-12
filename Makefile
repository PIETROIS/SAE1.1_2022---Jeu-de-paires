but : jeu_de_paires

OFILES = affichage.o \
		 menu_v2.o

CC = gcc

CFLAGS = -lgraph


affichage.o : affichage.c

menu_v2.o : affichage.h menu_v2.c

jeu_de_paires : $(OFILES)
	$(CC) $(CFLAGS) -o jeu_de_paires $(OFILES)

clean :
	-rm -f $OFILES) jeu_de_paires

.PHONY : but clean
