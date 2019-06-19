/*Producted by Guojiaxin,from ZJU in 2019.6.18*/

#include <FL/fl_draw.H>
#include <stdio.h>
#include <stdlib.h>
#include "PS_Box.h"
/*ÖØÔØhandleº¯Êý*/
int PS_Box::handle(int e) {
	switch (e) {
	case FL_PUSH:
		color(FL_RED);
		cur_x = Fl::event_x()-x();
		cur_y = Fl::event_y()-y();
		redraw();
		return 1;
	case FL_DRAG:
		this->position(Fl::event_x()-cur_x, Fl::event_y()-cur_y);
		this->window()->damage(FL_DAMAGE_ALL);
		redraw();
		return 1;
	case FL_RELEASE:
		show();
	}
	return 0;
}
