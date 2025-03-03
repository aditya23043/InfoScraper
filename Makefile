target: something

something: src/main.c
	gcc -Wall src/main.c -o bin/main -lX11 -lXtst

run: bin/main
	./bin/main "make a song about arch linux" something.mp3

vim: src/main.c
	vim src/main.c
