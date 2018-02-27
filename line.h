#include <ncurses.h>
#include <math.h>

void drawLine(int x1,int y1,int x2,int y2,char c) {

	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;

	if(dy1 <= dx1) {
		if(dx >= 0) {
			x = x1;
			y = y1;
			xe = x2;
		} else {
			x = x2;
			y = y2;
			xe = x1;
		}

		mvaddch(x,y,c);

		for(i=0; x < xe; i++) {
			x++;
			if(px < 0) {
				px += 2 * dy1;
			} else {
				if((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					y++;
				} else {
					y--;
				}

				px += 2 * (dy1 - dx1);
			}

			mvaddch(x,y,c);
		}
	} else {
		if(dy >= 0) {
			x = x1;
			y = y1;
			ye = y2;
		} else {
			x = x2;
			y = y2;
			ye = y1;
		}

		mvaddch(x,y,c);
		
		for(i = 0; y < ye; i++) {
			y++;
			if(py <= 0) {
				py += 2 * dx1;
			} else {
				if((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					x++;
				} else {
					x--;
				}
				py += 2 * (dx1 - dy1);
			}
			
			mvaddch(x,y,c);
		}
	}
}
