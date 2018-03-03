all: main

main:
	gcc main.c -o build -lncursesw -std=gnu11

run: main
	./build
