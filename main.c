//CURSES SUCKS // DO NOT REMOVE THIS COMMENT // VERY IMPORTANT//
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>
#include <locale.h>
#include "headers/mapparser.h"
#include "headers/stats.h"
#include "headers/collision.h"

void main() {

	setlocale(LC_ALL, "");
	initscr();

	curs_set(0);
	timeout(30);
	start_color();
	noecho();

	init_pair(1,COLOR_YELLOW,COLOR_BLACK);

	int x = 20;
	int y = 20;
	int lastX = 0;
	int lastY = 0;
	int termMaxX = getmaxx(stdscr);
	int termMaxY = getmaxy(stdscr);
	int worldOffsetY = 0;
	int worldOffsetX = 0;
	int lastWorldOffsetY = 0;
	int lastWorldOffsetX = 0;
	bool stop = false;
	char lastPress;
	char *playerChar = "@";

	FILE *map = fopen("maps/testmap.map", "r, ccs=UTF-8");

	cacheMap(map);
	loadMapCol(map);
	loadMapObj(map, &worldOffsetY, &worldOffsetX, y, x);

	while (stop == false) {
		if (is_term_resized(termMaxY, termMaxX) == true) {
			termMaxX = getmaxx(stdscr);
			termMaxY = getmaxy(stdscr);
		}

		drawMap(worldOffsetY, worldOffsetX, termMaxY, termMaxX);

		attron(COLOR_PAIR(1));
		mvaddstr(y,x, playerChar);
		attroff(COLOR_PAIR(1));

		lastX = x;
		lastY = y;
		lastWorldOffsetX = worldOffsetX;
		lastWorldOffsetY = worldOffsetY;

		lastPress = getch();

		if (lastPress == 'q') {
			stop = true;
		}

		if (lastPress == 'e') {
			timeout(60);
			lastPress = ' ';
			while (lastPress != 'q' && lastPress != 'e') {
				lastPress = getch();
				erase();
				drawStatWin();
				if (lastPress == 'w') {
					hp[0]++;
				}
				if (lastPress == 's') {
					hp[0]--;
				}
			}
			timeout(30);
		}

		if (lastPress == 'w' && playerChar == "\u02C4") {
			if (y - 5 <= 0 && worldOffsetY > 0) {
				worldOffsetY--;
			} else {
				y--;
			}
		} else if (lastPress == 'w' && playerChar != "\u02C4") {
			playerChar = "\u02C4";
		} else if (lastPress == 's' && playerChar == "\u02C5") {
			if (y + 5 >= termMaxY) {
				worldOffsetY++;
			} else {
				y++;
			}
		} else if (lastPress == 's' && playerChar != "\u02C5") {
			playerChar = "\u02C5";
		} else if (lastPress == 'd' && playerChar == "\u02C3") {
			if (x + 5 >= termMaxX) {
				worldOffsetX++;
			} else {
				x++;
			}
		} else if (lastPress == 'd' && playerChar != "\u02C3") {
			playerChar = "\u02C3";
		} else if (lastPress == 'a' && playerChar == "\u02C2") {
			if (x - 5 <= 0 && worldOffsetX > 0) {
				worldOffsetX--;
			} else {
				x--;
			}
		} else if (lastPress == 'a' && playerChar != "\u02C2") {
			playerChar = "\u02C2";
		}

		if ((lastWorldOffsetX != worldOffsetY || lastWorldOffsetX != worldOffsetX) || (lastY != y || lastX != x)){
			if (colCheck(worldOffsetY + y, worldOffsetX + x) || (y < 0 || x < 0)){
				x = lastX;
				y = lastY;
				worldOffsetX = lastWorldOffsetX;
				worldOffsetY = lastWorldOffsetY;
			}
		}

		refresh();
		erase();
	}
	fclose(map);
	endwin();
}
