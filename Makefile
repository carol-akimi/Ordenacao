all:
	gcc ordenacao.c -Wall -std=c99 -o ord 

run:
	./ord < in.1 

clean:
	rm ord