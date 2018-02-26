#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include "collision.h"

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

	// ---=== DEBUG ===--- \\

	bool collision = true;

	// ---===   END  ===--- \\

	while (stop == false) {

		// ---=== DEBUG ===--- \\
		
		if (lastPress == 'e' && collision){
			collision = false;
		} else if (lastPress == 'e' && !collision) {
			collision = true;
		}
		mvprintw(9,20,"Is Collidable:%d",colCheck(y,x));
		mvprintw(10,20,"Collision enabled:%d",collision);
		mvprintw(11,20,"Y:%i X:%i",y,x);
		mvprintw(12,20,"lastPress:%c",lastPress);

		// ---===   END  ===--- \\

		drawColLine(5,5,12,14,'X');
		drawColLine(5,5,5,14,'X');
		drawColLine(5,5,14,5,'X');

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

		if (colCheck(y,x) && collision){
			x = lastX;
			y = lastY;
		}

		refresh();
		erase();
	}

	endwin();
}
