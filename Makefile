all:
	gcc main.c -o main -std=c99 -Wall

run: mkresults
	./main

mkresults:
	@mkdir result2

clean:
	rm main