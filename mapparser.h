#include "collision.h"
#include <wchar.h>

int getMapSize(FILE *map){

	int size;
	fseek(map, 0, SEEK_END);
	size = ftell(map);
	fseek(map, 0, SEEK_SET);

	return size;
}

void loadMapObj(FILE *map, int *y, int *x) {

	fseek(map, 0, SEEK_SET);

	long int i;
	char drawTracker;
	long int fileX = 0;
	long int fileY = 0;
	long int size = getMapSize(map);

	while (feof(map) != 1) {
		drawTracker = fgetwc(map);
		fileX++;
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

	char drawTracker;
	long int fileX = 0;
	long int fileY = 0;

	while (feof(map) != 1) {
		drawTracker = fgetwc(map);
		fileX++;
		if (drawTracker == '\n'){
			fileX = 0;
			fileY++;
		} else if (drawTracker == '#') {
			addCol(fileY, fileX);
		}
	}
}

void drawMap(FILE *map, long int camOffsetY, long int camOffsetX) {

	fseek(map, 0, SEEK_SET);

	long int i;
	wchar_t drawTracker;
	long int fileX = 0;
	long int fileY = 0;
	long int size = getMapSize(map);

	for (i = 0; i < size; i++){
		drawTracker = fgetwc(map);
		fileX++;
		if (drawTracker == L'\n'){
			fileX = 0;
			fileY++;
		}
		if (drawTracker == L'^') {
			fileX++;
			i++;
			fseek(map, 1, SEEK_CUR);
			continue;
		}
		mvprintw(fileY + camOffsetY, fileX + camOffsetX, "%lc", drawTracker);
	}
}

