#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <pthread.h>
#include "mapparser.h"

void main() {
	setlocale(LC_ALL, "");
	initscr();

	curs_set(0);
	timeout(30);
	start_color();
	noecho();

	init_pair(1,COLOR_YELLOW,COLOR_BLACK);

	char lastPress;
	char *playerChar = "@";
	int x = 0;
	int y = 0;
	int lastX = 0;
	int lastY = 0;
	bool stop = false;

	FILE *map = fopen("maps/testmap.map", "r");

	loadMapCol(map);
	loadMapObj(map, &y, &x);

	while (stop == false) {

		drawMap(map);

		attron(COLOR_PAIR(1));
		mvprintw(y,x,"%s", playerChar);
		attroff(COLOR_PAIR(1));

		lastX = x;
		lastY = y;

		lastPress = getch();

		if (lastPress == 'q'){
			stop = true;
		}

		if (lastPress == 'w'){
			y--;
			playerChar = "\u02C4";
		}
		if (lastPress == 's'){
			y++;
			playerChar = "\u02C5";
		}
		if (lastPress == 'd'){
			x++;
			playerChar = "\u02C3";
		}
		if (lastPress == 'a'){
			x--;
			playerChar = "\u02C2";
		}

		if (colCheck(y,x)){
			x = lastX;
			y = lastY;
		}

		refresh();
		//erase();
	}
	fclose(map);
	endwin();
}
