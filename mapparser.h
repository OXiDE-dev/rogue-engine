#include "collision.h"
#include <stdio.h>
#include <unistd.h>

int getMapSize(FILE *map){

	int size;
	fseek(map, 0, SEEK_END);
	size = ftell(map);
	fseek(map, 0, SEEK_SET);

	return size;
}

void loadMapObj(FILE *map, int *y, int *x) {

	fseek(map, 0, SEEK_SET);

	int i;
	char drawTracker;
	int fileX = 0;
	int fileY = 0;
	int size = getMapSize(map);

	for (i = 0; i < size; i++){
		fileX++;
		drawTracker = fgetc(map);
		if (drawTracker == '\n'){
			fileX = 0;
			fileY++;
		} else if (drawTracker == '@') {
			*y = fileY;
			*x = fileX;
		}
	}
}

void loadMapCol(FILE *map) {

	fseek(map, 0, SEEK_SET);

	int i;
	char drawTracker;
	int fileX = 0;
	int fileY = 0;
	int size = getMapSize(map);

	for (i = 0; i < size; i++){
		fileX++;
		drawTracker = fgetc(map);
		if (drawTracker == '\n'){
			fileX = 0;
			fileY++;
		} else if (drawTracker == '#') {
			addCol(fileY, fileX);
		}
	}
}

void drawMap(FILE *map) {

	fseek(map, 0, SEEK_SET);

	int i;
	char drawTracker;
	int fileX = 0;
	int fileY = 0;
	int size = getMapSize(map);

	for (i = 0; i < size; i++){
		fileX++;
		drawTracker = fgetc(map);
		if (drawTracker == '\n'){
			fileX = 0;
			fileY++;
		}
		if (drawTracker == '^') {
    			fileX++;
    			i++;
    			fseek(map, 1, SEEK_CUR);
    			continue;
		}
		mvaddch(fileY, fileX, drawTracker);
	}
}

