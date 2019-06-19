/*Producted by Guojiaxin,from ZJU in 2019.6.18*/
#pragma once
#ifndef PSBOX_H
#define PSBOX_H
#include "Main_Window.h"
class PS_Box : public Fl_Box {
	int handle(int);
public:
	int cur_x, cur_y;
	PS_Box(int x, int y, int w, int h) : Fl_Box(x, y, w, h) {}
};
class PS_Window : public Fl_Window {
	int handle(int);
public:
	int cur_x, cur_y;
	PS_Window(int x, int y, int w, int h,char * l) : Fl_Window(x, y, w, h,l) {}
};


#endif