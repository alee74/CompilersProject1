# Makefile for Project One reference implemention.
# You will clearly need to change this depending on your language and implementation.

CFLAGS=-Wall -O2
#CFLAGS=-Wall g -O0

reader:		lexing.o parsing.o 
		gcc $(CFLAGS) -o reader lexing.o parsing.o

parsing.o:	lexing.h parsing.c parsing.h
		gcc $(CFLAGS) -c parsing.c

lexing.o:	lexing.c lexing.h 
		gcc $(CFLAGS) -c lexing.c

clean:
		rm *.o
		rm reader 

wc:		
		wc -l lexing.h lexing.c parsing.h parsing.c alloc.h alloc.c

export:		lexing.c parsing.c lexing.h parsing.h Makefile README
		tar cvf export.tar Makefile README *.c *.h 
