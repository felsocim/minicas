CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -lm

all : obmn
	$(CC) $(CFLAGS) obj/matrix.o obj/resol.o obj/parseurs.o obj/variables.o obj/minicas.o -o minicas $(LDFLAGS)

matrix_test: source/matrix_test.c obr
	$(CC) $(CFLAGS) obj/matrix.o obj/resol.o source/matrix_test.c -o matrix_test $(LDFLAGS)

obm : objdir source/matrix.c include/matrix.h
	$(CC) $(CFLAGS) -c source/matrix.c -o obj/matrix.o

obr : obm source/resol.c include/resol.h include/matrix.h
	$(CC) $(CFLAGS) -c source/resol.c -o obj/resol.o

obp : obr source/parseurs.c include/parseurs.h include/resol.h
	$(CC) $(CFLAGS) -c source/parseurs.c -o obj/parseurs.o

obv : obp source/variables.c include/variables.h include/parseurs.h
	$(CC) $(CFLAGS) -c source/variables.c -o obj/variables.o

obmn : obv source/minicas.c include/matrix.h source/matrix.c include/resol.h source/resol.c include/parseurs.h source/parseurs.c include/variables.h source/variables.c
	$(CC) $(CFLAGS) -c source/minicas.c -o obj/minicas.o

objdir:
	test -d obj || mkdir obj

clean:
	rm -rf obj
	rm -f matrix_test minicas speedtest.png lestimate.txt
