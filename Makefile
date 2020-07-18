# Format is as follows:
# target: [dependencies]
# -TAB-> instructions

all: dict1 dict2

dict1: main1.c listops.c listops.h bstops.c bstops.h readingops.c readingops.h
	gcc -Wall -o dict1 main1.c listops.c bstops.c readingops.c

dict2: main2.c listops.c listops.h bstops.c bstops.h readingops.c readingops.h
	gcc -Wall -o dict2 main2.c listops.c bstops.c readingops.c

clean: rm -f *.o dict1 dict2