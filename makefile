all: main

main:
	gcc -lncursesw main.c -o build 

run: main
	./build
