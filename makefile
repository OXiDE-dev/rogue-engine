all: main

main:
	gcc main.c -o build -lncursesw

run: main
	./build
