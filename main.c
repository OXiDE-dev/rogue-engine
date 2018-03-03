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
	int termMaxX = getmaxx(stdscr);
	int termMaxY = getmaxy(stdscr);
	long int camOffsetY = 0;
	long int camOffsetX = 0;
	long int lastCamOffsetY = 0;
	long int lastCamOffsetX = 0;
	bool stop = false;

	FILE *map = fopen("maps/testmap.map", "r, ccs=UTF-8");

	loadMapCol(map);
	loadMapObj(map, &y, &x);

	while (stop == false) {
		drawMap(map, camOffsetY, camOffsetX);

		if (is_term_resized(termMaxY, termMaxX) == true) {
			termMaxX = getmaxx(stdscr);
			termMaxY = getmaxy(stdscr);
		}

		attron(COLOR_PAIR(1));
		mvaddstr(y,x, playerChar);
		attroff(COLOR_PAIR(1));

		lastX = x;
		lastY = y;
		lastCamOffsetX = camOffsetX;
		lastCamOffsetY = camOffsetY;

		lastPress = getch();

		if (lastPress == 'q') {
			stop = true;
		}

		if (lastPress == 'w' && playerChar == "\u02C4") {
			if (y - 5 <= 0) {
				camOffsetY++;
			} else {
				y--;
			}
		} else if (lastPress == 'w' && playerChar != "\u02C4") {
			playerChar = "\u02C4";
		} else if (lastPress == 's' && playerChar == "\u02C5") {
			if (y + 5 >= termMaxY) {
				camOffsetY--;
			} else {
				y++;
			}
		} else if (lastPress == 's' && playerChar != "\u02C5") {
			playerChar = "\u02C5";
		} else if (lastPress == 'd' && playerChar == "\u02C3") {
			if (x + 5 >= termMaxX) {
				camOffsetX--;
			} else {
				x++;
			}
		} else if (lastPress == 'd' && playerChar != "\u02C3") {
			playerChar = "\u02C3";
		} else if (lastPress == 'a' && playerChar == "\u02C2") {
			if (x - 5 <= 0) {
				camOffsetX++;
			} else {
				x--;
			}
		} else if (lastPress == 'a' && playerChar != "\u02C2") {
			playerChar = "\u02C2";
		}

		if (colCheck(y - camOffsetY, x - camOffsetX)){
			x = lastX;
			y = lastY;
			camOffsetX = lastCamOffsetX;
			camOffsetY = lastCamOffsetY;
		}

		refresh();
		erase();
	}
	fclose(map);
	endwin();
}
