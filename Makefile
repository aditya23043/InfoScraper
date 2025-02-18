target: something

something: src/main.c
	gcc -Wall src/main.c -o bin/main

run: bin/main
	./bin/main
