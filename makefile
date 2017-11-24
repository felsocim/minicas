all : obm obr obmn obp obv
	gcc -g -Wall -Wextra -Werror obj/matrix.o obj/resol.o obj/parseurs.o obj/variables.o obj/minicas.o -lm -o minicas

obm : source/matrix.c include/matrix.h
	gcc -c source/matrix.c -o obj/matrix.o

obr : source/resol.c include/resol.h include/matrix.h
	gcc -c source/resol.c -o obj/resol.o

obp : source/parseurs.c include/parseurs.h include/resol.h
	gcc -c source/parseurs.c -o obj/parseurs.o

obv : source/variables.c include/variables.h include/parseurs.h
	gcc -c source/variables.c -o obj/variables.o

obmn : bin/minicas.c include/matrix.h source/matrix.c include/resol.h source/resol.c include/parseurs.h source/parseurs.c include/variables.h source/variables.c
	gcc -c bin/minicas.c -o obj/minicas.o

clean:
	rm -f obj/*
	rm -f tmp/*
	rm -f mtest minicas
	rm -f speedtest.png lestimate.txt
