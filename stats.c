#include "stats.h"

int hp = 10;
int lvl = 1;
int xp = 0;

void drawSeparator(WINDOW *window, wchar_t start, wchar_t mid, wchar_t end, int y, int lenght) {
	mvwprintw(window, y, (int)((getmaxx(window) / 2) - (lenght / 2)), "%lc", start);
	int drawTracker = 1;
	int i;
	for (i = 0; i < lenght - 1; i++) {
		mvwprintw(window, y, drawTracker + (int)((getmaxx(window) / 2) - (lenght / 2)), "%lc", mid);
		drawTracker++;
	}
	mvwprintw(window, y, (int)((getmaxx(window) / 2) + (lenght / 2)), "%lc", end);
}

const void drawStatWin() {
	WINDOW *statWindow = subwin(stdscr ,getmaxy(stdscr) - 4, getmaxx(stdscr) - 4, 2, 2);
	werase(statWindow);
	box(statWindow, ACS_VLINE, ACS_HLINE);
	drawSeparator(statWindow, L'├', L'─', L'┤', 4, 20);
	mvwprintw(statWindow, 2, 4, "test");
	wrefresh(statWindow);
}

