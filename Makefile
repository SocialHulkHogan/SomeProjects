CLIBS=		-lm	# math library
CFLAGS=		-ansi
CC = gcc
all:	Csort Ccat Caverage Cwc Ccp
	 
Ccat:	Ccat.c
	gcc Ccat.c -o Ccat

Caverage:	Caverage.c
	gcc Ccat.c -o Caverage

Cwc:	Cwc.c
	gcc Cwc.c -o Cwc

Csort:	Csort.c
	gcc Csort.c -o Csort

Ccp:	Ccp.c
	gcc Ccp.c -o Ccp