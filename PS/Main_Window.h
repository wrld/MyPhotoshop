/*Producted by Guojiaxin,from ZJU in 2019.6.18*/
#pragma once
#ifndef PSGUI_H
#define PSGUI_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/gl.h>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Toggle_Light_Button.H>
#include <FL/fl_message.H>
#include <FL/forms.H> 
#include <FL/Fl_Input.H>
#include <errno.h>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include "basic_functions.h"
#include <vector>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  
#include "Draw_Map.h"
#include "PS_Box.h"
#include "stdlib.h"
using namespace cv;
using namespace std;
void browser_cb(Fl_Widget* o, void*);
void help_cb(Fl_Widget *o, void *p);
void window_cb(Fl_Widget* w, void*);
void tip_cb(Fl_Widget* w, void*);
void attention_pic_cb(int type);
void delete_old_pic();
void redraw_pic(Fl_Shared_Image *n);
void  log_pic_cb(Fl_Widget* w, void*);
void  index_pic_cb(Fl_Widget* w, void*);
void  canny_pic_cb(Fl_Widget* w, void*);
void  sobel_pic_cb(Fl_Widget* w, void*);
void  salt_pic_cb(Fl_Value_Slider*o, long);
void filter_geo_cb(Fl_Widget* w, void*);
void  filter_har_cb(Fl_Widget* w, void*);
void  filter_median_cb(Fl_Widget* w, void*);
void light_pic_cb(Fl_Value_Slider*o, long);
void threshold_pic_cb(Fl_Widget* w, void*);
void linear_transform_pic_cb(Fl_Widget* w, void*);
void equalize_hist_cb(Fl_Widget* w, void*);
void show_hist_cb(Fl_Widget* w, void*);
 void gray_pic_cb(Fl_Widget* w, void*);
 void light_pic_cb(Fl_Value_Slider*o, long);
 void rotate_pic_cb(Fl_Value_Slider*o, long);
 void posx_pic_cb(Fl_Value_Slider*o, long);
 void posy_pic_cb(Fl_Value_Slider*o, long);
 void size_pic_cb(Fl_Value_Slider*o, long);
 void face_detect_cb(Fl_Widget *o, void *);
 void compare_pic_cb(Fl_Value_Slider*o, long);
 void guassblur_pic_cb(Fl_Widget *o, void *);
 void avrblur_pic_cb(Fl_Widget *o, void *);
 void forward_cb(Fl_Widget *, void *);
 void erode_pic_cb(Fl_Widget *o, void *);
 void opened_pic_cb(Fl_Widget *o, void *);
 void closed_pic_cb(Fl_Widget *o, void *);
 void gradient_pic_cb(Fl_Widget *o, void *);
 void new_file_cb(const char *n);
 void avrblur_pic_cb(Fl_Widget *o, void *);
 void back_cb(Fl_Widget *, void *);
 void fullscreen_cb(Fl_Widget *o, void *p);
void load_file(const char *n);
void file_cb(const char *n);
 void color_cb(Fl_Widget* button, void* v);
 void draw_cb(Fl_Widget* button, void* v);
 void file_button_cb(Fl_Widget *, void *);
 void close_button_cb(Fl_Widget *o, void *v);	
 void window_cb(Fl_Widget* w, void*);
 void MainWindow();

#endif
