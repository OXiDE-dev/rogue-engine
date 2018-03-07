#include "headers/stats.h"

int hp[2] = {3, 10};
int lvl = 1;
int xp = 0;

void drawProgressBar(WINDOW *window, wchar_t full, wchar_t empty, int percentFull, int y, int start, int end) {
	int i;
	for (i = 0; i < (int)end - start; i++){
		mvwprintw(window, y, start + i, "%lc", empty);
	}
	for (i = 0; i < (int)(end - start) * percentFull / 100; i++) {
		mvwprintw(window, y, start + i, "%lc", full);
	}
}

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
	int maxx = getmaxx(statWindow);

	werase(statWindow);

		// fix the spacing

	box(statWindow, ACS_VLINE, ACS_HLINE);
	// I HATE THIS LIBRARY
	mvwprintw(statWindow, 0, 0, "%lc", L'╭');
	mvwprintw(statWindow, 0, maxx - 1, "%lc", L'╮');
	mvwprintw(statWindow, getmaxy(statWindow) - 1, 0, "%lc", L'╰');
	mvwprintw(statWindow, getmaxy(statWindow) - 1, maxx - 1, "%lc", L'╯');

	mvwprintw(statWindow, 2, maxx / 2 - 3, "Status:");
	drawSeparator(statWindow, L'├', L'─', L'┤', 4, maxx / 1.2);

	mvwprintw(statWindow, 6, maxx - maxx / 1.2 - 4 , "HP:");
	drawProgressBar(statWindow, L'█', L'▒', (hp[0] < hp[1] + 1) ? ((float)hp[0] / hp[1]) * 100 : 0, 6, maxx - maxx / 1.2 + 4, maxx / 1.2 - 3);
	mvwprintw(statWindow, 6, maxx / 1.2 + 3, (hp[0] < hp[1] + 1) ? "%i/%i" : "???" , hp[0], hp[1]);
	drawSeparator(statWindow, L'├', L'─', L'┤', 8, maxx / 1.2);

	drawSeparator(statWindow, L'├', L'─', L'┤', 12, maxx / 1.2);


	wrefresh(statWindow);
}

