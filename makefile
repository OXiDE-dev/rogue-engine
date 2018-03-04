all: main

main:
	gcc -o build main.c mapparser.c collision.c arraycheck.c stats.c -lncursesw -std=gnu11

run: main
	./build
