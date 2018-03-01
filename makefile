all: main

main:
	gcc -pthread -lncursesw main.c -o build 

run: main
	./build
