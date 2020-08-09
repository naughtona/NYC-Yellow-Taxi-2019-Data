# Andrew Naughton 9/8/2020

all: dict1 dict2


dict1: main1.o listops.o bstops.o readingops.o
	gcc -Wall -o dict1 main1.o listops.o bstops.o readingops.o

dict2: main2.o listops.o bstops.o readingops.o
	gcc -Wall -o dict2 main2.o listops.o bstops.o readingops.o


main1.o: bstops.c bstops.h listops.c listops.h readingops.c readingops.h
	gcc -Wall -c main1.c bstops.c listops.c readingops.c

main2.o: bstops.c bstops.h listops.c listops.h readingops.c readingops.h
	gcc -Wall -c main2.c bstops.c listops.c readingops.c


readingops.o: bstops.c bstops.h listops.c listops.h readingops.c readingops.h
	gcc -Wall -c readingops.c bstops.c listops.c

bstops.o: bstops.c bstops.h listops.c listops.h readingops.c readingops.h
	gcc -Wall -c bstops.c listops.c readingops.c

listops.o: bstops.c bstops.h listops.c listops.h
	gcc -Wall -c listops.c bstops.c


clean:
	rm -f *.o dict1 dict2
