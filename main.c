//CURSES SUCKS // DO NOT REMOVE THIS COMMENT // VERY IMPORTANT//
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>
#include <locale.h>
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

	FILE *map = fopen("maps/testmap.map", "r, ccs=UTF-8");

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

		if (lastPress == 'w' && playerChar == "\u02C4") {
			y--;
		} else if (lastPress == 'w' && playerChar != "\u02C4") {
			playerChar = "\u02C4";
    		}
		if (lastPress == 's' && playerChar == "\u02C5") {
			y++;
		} else if (lastPress == 's' && playerChar != "\u02C5") {
			playerChar = "\u02C5";
		}
		if (lastPress == 'd' && playerChar == "\u02C3") {
			x++;
		} else if (lastPress == 'd' && playerChar != "\u02C3") {
			playerChar = "\u02C3";
    		}
		if (lastPress == 'a' && playerChar == "\u02C2") {
			x--;
		} else if (lastPress == 'a' && playerChar != "\u02C2") {
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
