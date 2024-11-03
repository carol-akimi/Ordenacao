all:
	gcc rascunho.c -Wall -std=c99 -o ras 

run:
	./ras < in.1 