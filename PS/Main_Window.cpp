/*Producted by Guojiaxin,from ZJU in 2019.6.18*/
#include "Main_Window.h"
int px, py, pw, ph;
char name[1024];
char img_name[1024];
Fl_Box* left_box;
Fl_Box *welcome_box;
Fl_Double_Window  *window;
Fl_Window *wel_window;
Fl_Double_Window *win;
int g_argc;
char **g_argv;
Mat begin_img;
Fl_Output *text;
Fl_Shared_Image *img;
Fl_Shared_Image *new_img;
PS_Box *draw_area;
string new_pic;
MyImage *pic;
Fl_Color c;
/*帮助回调函数*/
void browser_cb(Fl_Widget* o, void*) {
	printf("callback, selection = %d, event_clicks = %d\n",
		((Fl_Browser*)o)->value(), Fl::event_clicks());
}
/*帮助回调函数*/
void help_cb(Fl_Widget *o, void *p) {
	int i;
	Fl_Select_Browser *browser;
	if (!Fl::args(g_argc, g_argv, i)) Fl::fatal(Fl::help);
	const char* fname = (i < g_argc) ? g_argv[i] : "MyPhotoshop.txt";
	Fl_Window *help_window = new Fl_Window(400, 400, fname);
	browser = new Fl_Select_Browser(0, 0, 400, 350, 0);
	browser->type(FL_MULTI_BROWSER);
	browser->color(95);
	browser->callback(browser_cb);
	if (!browser->load(fname)) {
#ifdef _MSC_VER
		int done = 1;
		if (i == g_argc)
		{
			fname = "MyPhotoshop.txt";
			done = browser->load(fname);
		}
		if (!done)
		{
			printf("Can't load %s, %s\n", fname, strerror(errno));
			exit(1);
		}
#else
		printf("Can't load %s, %s\n", fname, strerror(errno));
		exit(1);
#endif
	}
	browser->position(0);
	help_window->resizable(browser);
	help_window->show(g_argc, g_argv);
}
/*退出提示回调函数*/
void window_cb(Fl_Widget* w, void*) {
	if (!fl_choice("你确定想要退出吗(T＿T)？", "取消", "退出", 0L)) return;
	exit(0);
}
/*温馨提示回调函数*/
void tip_cb(Fl_Widget* w, void*) {
	fl_choice("可以鼠标直接拖动图片移动哦(*^▽^*) ", "取消", "确定", 0L);
}
/*防止文件误操作回调函数*/
void attention_pic_cb(int type) {
	switch (type) {
	case 0:
		if (!fl_choice("你还没有打开文件(￣▽￣)／！", "取消", "确定", 0L)) return;
		return;
		break;
	case 1:
		if (!fl_choice("已经是第一张图片(￣▽￣)／！", "取消", "确定", 0L)) return;
		return;
		break;
	case 2:
		if (!fl_choice("已经是最后一张图片(￣▽￣)／！", "取消", "确定", 0L)) return;
		return;
		break;
	case 3:
		if (!fl_choice("没有检测到人脸╮(╯﹏╰）╭！", "取消", "确定", 0L)) return;
		return;
		break;
	default:
		return;
		break;
	}
}
/*删除旧照片*/
void delete_old_pic() {
	pic->myDeletePic((pic->old_name).data());
	delete pic;
}
/*重新绘图*/
void redraw_pic(Fl_Shared_Image *n) {
	draw_area->image(n);
	win->redraw();
	pic->src = imread((pic->new_name).data());
	if(pic->new_name!=pic->old_name)pic->myDeletePic((pic->old_name).data());
	strcpy(name , (pic->new_name).data());
	if ((pic != NULL)) {
		stringstream  stream;
		string v;
		stream << pic->version;
		stream >> v;
		text->value(v.data());
	}
}
/*灰度图回调函数*/
void  gray_pic_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	
	pic->myGray();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*对数运算回调函数*/
void  log_pic_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myLog();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*指数运算回调函数*/
void  index_pic_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myIndex();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*canny算子回调函数*/
void  canny_pic_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0){
		attention_pic_cb(0);return;
	}
	pic->myCanny();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*sobel算法回调函数*/
void sobel_pic_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->mySobel();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*噪声回调函数*/
void  salt_pic_cb(Fl_Value_Slider*o, long) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->mySalt(o->value());
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*均值滤波回调函数*/
void  filter_aver_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myImageRecover("aver", Size(3, 3));
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*几何滤波回调函数*/
void filter_geo_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myImageRecover("geo", Size(3, 3));
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*谐波滤波回调函数*/
void  filter_har_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myImageRecover("har", Size(3, 3));
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*中值滤波回调函数*/
void  filter_median_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myImageRecover("median", Size(3, 3));
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*亮度调节回调函数*/
void light_pic_cb(Fl_Value_Slider*o, long) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myBrightChange(int(o->value()));
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*阈值化图像回调函数*/
void threshold_pic_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	pic->myThreshold(155, 2);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*线性灰度变换回调函数*/
void linear_transform_pic_cb(Fl_Widget* w, void*){
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myLinear_Transform();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*直方图均衡化回调函数*/
void equalize_hist_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myEqualize_hist();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*显示灰度图回调函数*/
void show_hist_cb(Fl_Widget* w, void*) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	pic->draw_Hist();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*旋转回调函数*/
void rotate_pic_cb(Fl_Value_Slider*o, long) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myRotation(o->value());
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*改变左右回调函数*/
void posx_pic_cb(Fl_Value_Slider*o, long) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	draw_area->position(400 - 250 + o->value(), draw_area->y());
	draw_area->redraw();
	win->redraw();
}
/*改变上下回调函数*/
void posy_pic_cb(Fl_Value_Slider*o, long) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	draw_area->position(draw_area->x(), 300 - 200 + o->value());
	draw_area->redraw();
	win->redraw();
}
/*改变图片大小回调函数*/
void size_pic_cb(Fl_Value_Slider*o, long) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;return;
		return;
	}
	img = Fl_Shared_Image::get(name);
	Fl_Image *temp;
	temp = img->copy(img->w() + o->value(), (img->w() + o->value())*img->h() / (img->w()));
	img->release();
	img = (Fl_Shared_Image *)temp;
	draw_area->image(img);
	draw_area->redraw();
	win->redraw();
}
/*人脸检测回调函数*/
void face_detect_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	if(!pic->myFaceDetection())attention_pic_cb(3);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*对比度调节回调函数*/
void compare_pic_cb(Fl_Value_Slider*o, long) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myCNTChange(int(o->value()));
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*玻璃化回调函数*/
void glass_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myGlass();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img= Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*高斯模糊回调函数*/
void guassblur_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myGaussianBlur(20);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*怀旧色回调函数*/
void old_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	pic->myOld();
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*膨胀回调函数*/
void dilate_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	pic->myRot(1);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*人脸美颜回调函数*/
void face_beauty_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0 && strlen(img_name) == 0) {
		attention_pic_cb(0); return;
	}
	if (!pic->myBeauty())attention_pic_cb(3);
	pic->mySavePic(); Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*腐蚀回调函数*/
void erode_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	pic->myRot(2);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*开运算回调函数*/
void opened_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	pic->myOpen_Close(1);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*闭运算回调函数*/
void closed_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	pic->myOpen_Close(2);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*形态梯度回调函数*/
void gradient_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	pic->myOpen_Close(3);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*图片混合回调函数*/
void new_file_cb(const char *n) {
	if (fl_filename_isdir(n)) {
		return;
	}
	Mat blend_img;
	blend_img = imread(n);
	double alpha = 0.5;
	pic->myBlend(blend_img, alpha);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*图片混合回调函数*/
void new_pic_cb(Fl_Widget *, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0); return;
	}
	fl_file_chooser_callback(new_file_cb);
	fl_file_chooser("Image file?", "*.{bm,bmp,gif,jpg,pbm,pgm,png,ppm,xbm,xpm}", name);
	fl_file_chooser_callback(0);
}
/*均值滤波回调函数*/
void avrblur_pic_cb(Fl_Widget *o, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	pic->myBlur(20);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	new_img = Fl_Shared_Image::get((pic->new_name).data());
	redraw_pic(new_img);
}
/*向后*/
void back_cb(Fl_Widget *, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	if (pic->version == 0) {
		attention_pic_cb(1); return;
	}
	pic->goToVersion(pic->version - 1);
	new_img = Fl_Shared_Image::get((pic->myNewName()).data());
	redraw_pic(new_img);
}
/*向前*/
void forward_cb(Fl_Widget *, void *) {
	if (strlen(name) == 0&&strlen(img_name)==0) {
		attention_pic_cb(0);return;
	}
	if (pic->version==pic->MyMaxVersion()-1) {
		attention_pic_cb(2); return;
	}

	pic->goToVersion(pic->version + 1);
	new_img = Fl_Shared_Image::get((pic->myNewName()).data());
	redraw_pic(new_img);
}

/*全屏*/
void fullscreen_cb(Fl_Widget *o, void *p) {
	Fl_Window *w = (Fl_Window *)p;
	int d = ((Fl_Button *)o)->value();

	if (d) {
		px = w->x();
		py = w->y();
		pw = w->w();
		ph = w->h();
		w->fullscreen();
	}
	else {
		w->fullscreen_off(px, py, pw, ph);
	}
}
/*加载文件*/
void load_file(const char *n) {
	if (img) {
		img->release();
		img = 0L;
	}
	if (fl_filename_isdir(n)) {
		draw_area->labelsize(64);
		draw_area->labelcolor(FL_LIGHT2);
		draw_area->image(0);
		draw_area->redraw();
		return;
	}
	img = Fl_Shared_Image::get(n);
	Fl_Image *temp;
	if (img->w() > draw_area->w() || img->h() > draw_area->h()) {
		Fl_Image *temp;
		if (img->w() > img->h()) temp = img->copy(draw_area->w(), draw_area->h() * img->h() / img->w());
		else temp = img->copy(draw_area->w() * img->w() / img->h(), draw_area->h());

		img->release();
		img = (Fl_Shared_Image *)temp;
	}
	draw_area->image(img);
	draw_area->redraw();
	window->redraw();
}
/*保存文件*/
void save_file(const char *n) {
	if (fl_filename_isdir(n)) {
		draw_area->label("@fileopen"); 
		draw_area->labelsize(64);
		draw_area->labelcolor(FL_LIGHT2);
		pic->mySavePic(n);
	}
	
}
/*存入图片*/
void pic_save(char *n, Mat img) {
	pic = new MyImage(img, n);
	pic->mySavePic();Fl_Shared_Image::get((pic->new_name).data())->reload();
	pic->rawSrc = img;
	new_pic = pic->new_name;
	new_img = Fl_Shared_Image::get(new_pic.data());
	strcpy(name, new_pic.data());
	draw_area->image(new_img);
	window->redraw();
}
/*file_chooser回调函数*/
void file_cb(const char *n) {
	if (!strcmp(name, n)) return;
	load_file(n);
	strcpy(name, n);
	if (!fl_filename_isdir(n)) {
		Mat img = imread(name);
		pic_save(name, img);
	}
	}
/*选择主界面颜色*/
void color_cb(Fl_Widget* button, void* v) {
	switch ((long)v) {
	case 0: c = FL_BACKGROUND2_COLOR; break;
	case 1: c = FL_SELECTION_COLOR; break;
	default: c = FL_FOREGROUND_COLOR; break;
	}
	uchar r, g, b;
	Fl::get_color(c, r, g, b);
	if (fl_color_chooser(0, r, g, b)) {
		Fl::set_color(c, r, g, b);
		Fl::redraw();
		button->labelcolor(fl_contrast(FL_BLACK, c));
		button->redraw();
		win->color(c);
		welcome_box->color(c);
		left_box->color(c);
		win->redraw();
	}
}
/*鼠标画图回调函数*/
void draw_cb(Fl_Widget* button, void* v) {
	fl_choice("保存按s, 清空按r哦(^_−)☆", "取消", "确定", 0L);
	MyDrawImage draw_board(name);

}
/*删除图片回调函数*/
void delete_button_cb(Fl_Widget *, void *) {
	pic->myDeletePic((pic->new_name).data());
	draw_area->image(0);
	window->redraw();
	if (!fl_choice("已经成功删除(～￣▽￣)～ ！", "取消", "确定", 0L))  return;
	return;
}
/*关闭图片回调函数*/
void close_button_cb(Fl_Widget *, void *) {
	draw_area->image(0);
	window->redraw();
}
/*保存按钮回调函数*/
void save_button_cb(Fl_Widget *, void *) {
	stringstream stream;
	string s;
	stream << pic->forward << pic->version <<"save"<< pic->back;
	stream >> s;
	imwrite(s, pic->src);
	if (!fl_choice("已经成功保存(*^▽^*)！", "取消", "确定", 0L))  return;
	return;

}
/*打开文件回调函数*/
void file_button_cb(Fl_Widget *, void *) {
	fl_file_chooser_callback(file_cb);
	fl_file_chooser("Image file?", "*.{bm,bmp,gif,jpg,pbm,pgm,png,ppm,xbm,xpm}", name);
	fl_file_chooser_callback(0);

}
/*定义上方菜单栏*/
Fl_Menu_Item menutable[] = {
	{ "&文件",0,0,0,FL_SUBMENU },
	{ "&打开图片",	FL_ALT + 'o', file_button_cb, 0,FL_MENU_DIVIDER },
	{ "&删除图片",	FL_ALT + 'e', delete_button_cb, 0,FL_MENU_DIVIDER },
	{ "&保存图片",	FL_ALT + 's', save_button_cb, 0,FL_MENU_DIVIDER },
	{ "&关闭图片",FL_ALT + 'c',	close_button_cb, 0,FL_MENU_DIVIDER },
	{ "&退出",	FL_ALT + 'q', window_cb, 0, FL_MENU_DIVIDER },
	{ 0 },
	{ "&图像变换",FL_F + 2,0,0,FL_SUBMENU },
	{ "线性灰度增强",	FL_ALT + 'r',linear_transform_pic_cb, 0,FL_MENU_DIVIDER },
	{ "对数变换",	FL_ALT + 't',log_pic_cb, 0, FL_MENU_DIVIDER },
	{ "指数变换",	FL_ALT + 'f',index_pic_cb,	0,FL_MENU_DIVIDER },
	{ "直方图均衡化",	FL_ALT + 'j',equalize_hist_cb,	0 ,FL_MENU_DIVIDER },
	{ "显示直方图",	FL_ALT + 'h' , show_hist_cb,0,FL_MENU_DIVIDER },
	{ 0 },
	{ "&滤镜",0,0,0,FL_SUBMENU },
	{ "&高斯模糊",	FL_ALT + 'g', guassblur_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&均值模糊",		FL_ALT + 'a', avrblur_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&毛玻璃效果",		FL_ALT + 'l', glass_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&灰度图",		FL_ALT + 'd',gray_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&怀旧色",		FL_ALT + 'b',old_pic_cb, 0,FL_MENU_DIVIDER },
	{ 0 },
	{ "&智能功能",0,0,0,FL_SUBMENU },
	{ "&人脸识别",	FL_CTRL + 'f', face_detect_cb, 0,FL_MENU_DIVIDER },
	{ "&人脸美颜",	FL_CTRL + 'm', face_beauty_cb, 0,FL_MENU_DIVIDER },
	{ "&图片拼接",	FL_CTRL + 'n', new_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&阈值化",	FL_CTRL + 't', threshold_pic_cb, 0,FL_MENU_DIVIDER },
	{ 0 },
	{ "&边缘检测",0,0,0,FL_SUBMENU },
	{ "&canny算子",	FL_CTRL + 'c', canny_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&sobel算法",	FL_CTRL + 's', sobel_pic_cb, 0,FL_MENU_DIVIDER },
	{ 0 },
	{ "图片去噪",0,0,0,FL_SUBMENU },
	{ "&算术均值滤波",	FL_CTRL + 'a', filter_aver_cb, 0,FL_MENU_DIVIDER },
	{ "&几何均值滤波",	FL_CTRL + 'g', filter_geo_cb, 0,FL_MENU_DIVIDER },
	{ "&谐波滤波",	FL_CTRL + 'x', filter_har_cb, 0,FL_MENU_DIVIDER },
	{ "&中值滤波",	FL_CTRL + 'e', filter_median_cb, 0,FL_MENU_DIVIDER },
	{ 0 },
	{ "形态学处理",0,0,0,FL_SUBMENU },
	{ "&腐蚀",	FL_CTRL + 'r', erode_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&膨胀",	FL_CTRL + 'p', dilate_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&开操作",	FL_CTRL + 'd', opened_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&闭操作",	FL_CTRL + 'l', closed_pic_cb, 0,FL_MENU_DIVIDER },
	{ "&形态梯度",	FL_CTRL + 't', gradient_pic_cb, 0,FL_MENU_DIVIDER },
	{ 0 },
	{ "帮助",0,0,0,FL_SUBMENU },
	{ "&打开",	FL_CTRL + 'o', help_cb, 0,FL_MENU_DIVIDER },
	{ 0 }
};
/*主界面初始化*/
void MainWindow() {
	/*窗口初始化*/
	window = new Fl_Double_Window(200, 200, 800, 600,"MyPhotoshop"); ::win = window;
	window->color((Fl_Color)43);
	window->selection_color((Fl_Color)43);
	window->begin();
    /*初始化背景*/
	{Fl_Box *win = new Fl_Box(180, 140, 500, 400);
	win->align(FL_ALIGN_CENTER);
	win->when(FL_WHEN_RELEASE);
	Fl_JPEG_Image* img2 = new Fl_JPEG_Image("background2.jpg");
	win->image(img2);
	/*初始化修改次数提醒*/
	text = new Fl_Output(52 + 100, 600 - 50, 40, 30, "更改：");
	text->align(FL_ALIGN_LEFT);
	text->tooltip("This is an Fl_Output widget.");
	/*初始化欢迎*/
	welcome_box = new Fl_Box(400 - 100 - 30, 600 - 70, 260, 60, "Welcome to use photoshop!");
	welcome_box->labelsize(20);
	welcome_box->labeltype(FL_SHADOW_LABEL);
	welcome_box->box(FL_THIN_DOWN_BOX);
	}
	/*初始化图片显示区域*/
	{draw_area = new PS_Box(400 - 250, 300 - 200, 500, 400);
	draw_area->align(FL_ALIGN_CENTER);
	draw_area->when(FL_WHEN_RELEASE);
	if (strlen(img_name)) {
		pic_save(img_name, begin_img);
		window->label(name);
	}
	} 
	/*初始化左边菜单栏*/
	{Fl_Widget *tobj[1];
	tobj[0] = fl_add_clock(FL_ANALOG_CLOCK, 0, 93, 50, 50, "");
	left_box = new Fl_Box(0, 90, 52, 600);
	left_box->box(FL_ENGRAVED_BOX);
	left_box->align(FL_ALIGN_TOP | FL_ALIGN_INSIDE);
	/*打开文件按钮初始化*/
	Fl_Button *file_left_button = new Fl_Button(0, 93 + 70, 50, 50);
	file_left_button->callback(file_button_cb, (void*)0);
	Fl_Shared_Image *file;
	file = Fl_Shared_Image::get("file.png");
	file_left_button->image(file);
	/*鼠标绘图按钮初始化*/
	Fl_Button *draw_button = new Fl_Button(0, 93 + 70 *2 , 50, 50);
	draw_button->callback(draw_cb, (void*)0);
	Fl_Shared_Image *img_color;
	img_color = Fl_Shared_Image::get("draw_board.png");
	draw_button->image(img_color);
	/*颜色选择按钮初始化*/
	Fl_Button *color_button = new Fl_Button(0, 93 + 70*3, 50, 50);
	color_button->callback(color_cb, (void*)0);
	img_color = Fl_Shared_Image::get("color.png");
	color_button->image(img_color);
	/*保存按钮初始化*/
	Fl_Button *save_left_button = new Fl_Button(0, 93 + 70*4, 50, 50);
	save_left_button->callback(save_button_cb, (void*)0);
	img_color = Fl_Shared_Image::get("save.png");
	save_left_button->image(img_color);
	/*删除按钮初始化*/
	Fl_Button *delete_button = new Fl_Button(0, 93 + 70 * 5, 50, 50);
	delete_button->callback(close_button_cb, (void*)0);
	img_color = Fl_Shared_Image::get("delete.png");
	delete_button->image(img_color);
	/*返回按钮初始化*/
	Fl_Button *exit_button = new Fl_Button(0, 93 + 70 * 6, 50, 50);
	exit_button->callback(window_cb, (void*)0);
	img_color = Fl_Shared_Image::get("return.png");
	exit_button->image(img_color);
	/*提示按钮初始化*/
	Fl_Button *tip_button = new Fl_Button(800 - 80, 93 + 70 * 6, 50, 50);
	tip_button->callback(tip_cb, (void*)0);
	img_color = Fl_Shared_Image::get("小贴士.png");
	tip_button->image(img_color);

	}
	/*初始化上方菜单栏*/
	Fl_Menu_Bar menu_bar(0, 0, 800, 30);
	menu_bar.menu(menutable);

	{ Fl_Box* first_box = new Fl_Box(0, 30, 800, 30);
	first_box->box(FL_ENGRAVED_BOX);
	first_box->align(FL_ALIGN_TOP | FL_ALIGN_INSIDE);
	/*向前按钮*/
	Fl_Button *back_button = new Fl_Button(660, 30, 30, 30);
	Fl_JPEG_Image* img2 = new Fl_JPEG_Image("smallback.jpg");
	back_button->image(img2);
	back_button->callback(back_cb);
	/*向后按钮*/
	Fl_Button *forward_button = new Fl_Button(710, 30, 30, 30);
	Fl_JPEG_Image* img3 = new Fl_JPEG_Image("smallForward.jpg");
	forward_button->image(img3);
	forward_button->callback(forward_cb);
	}
	/*对比度滑条初始化*/
	{Fl_Value_Slider* cnt_slider = new Fl_Value_Slider(100, 30, 120, 25, "对比度：");
	cnt_slider->align(FL_ALIGN_LEFT);
	cnt_slider->selection_color((Fl_Color)1);
	cnt_slider->type(FL_HOR_NICE_SLIDER);
	cnt_slider->range(0, 100);
	cnt_slider->step(1);
	cnt_slider->callback((Fl_Callback*)compare_pic_cb);
	}
	/*亮度滑条初始化*/
	{Fl_Value_Slider* bright_slider = new Fl_Value_Slider(300, 30, 120, 25, "亮度：");
	bright_slider->align(FL_ALIGN_LEFT);
	bright_slider->selection_color((Fl_Color)1);
	bright_slider->type(FL_HOR_NICE_SLIDER);
	bright_slider->range(0, 100);
	bright_slider->step(1);
	bright_slider->callback((Fl_Callback*)light_pic_cb);
	}
	/*噪声滑条初始化*/
	{ Fl_Value_Slider* salt_slider = new Fl_Value_Slider(520, 30, 120, 25, "噪声：");
	salt_slider->align(FL_ALIGN_LEFT);
	salt_slider->selection_color((Fl_Color)1);
	salt_slider->type(FL_HOR_NICE_SLIDER);
	salt_slider->range(0, 1);
	salt_slider->step(0.05);
	salt_slider->callback((Fl_Callback*)salt_pic_cb);
	}
	/*第三行菜单栏初始化*/
	{ Fl_Box* second_box = new Fl_Box(0, 60, 800, 30);
	second_box->box(FL_ENGRAVED_BOX);
	second_box->align(FL_ALIGN_TOP | FL_ALIGN_INSIDE);
	}
	/*旋转滑条初始化*/
	{Fl_Value_Slider* rotate_slider = new Fl_Value_Slider(100, 60, 120, 25, "旋转：");
	rotate_slider->align(FL_ALIGN_LEFT);
	rotate_slider->selection_color((Fl_Color)2);
	rotate_slider->type(FL_HORIZONTAL);
	rotate_slider->range(0, 360);
	rotate_slider->step(0.5);
	rotate_slider->callback((Fl_Callback*)rotate_pic_cb);
	}
	/*左右滑条初始化*/
	{Fl_Value_Slider* LnR_slider = new Fl_Value_Slider(240, 60, 120, 25, "左右：");
	LnR_slider->align(FL_ALIGN_CENTER); 
	LnR_slider->selection_color((Fl_Color)2);
	LnR_slider->type(FL_HORIZONTAL);
	LnR_slider->range(-400, 400);
	LnR_slider->step(0.5);
	LnR_slider->callback((Fl_Callback*)posx_pic_cb);
	}
	/*上下滑条初始化*/
	{Fl_Value_Slider* UnD_slider = new Fl_Value_Slider(380, 60, 120, 25, "上下：");
	UnD_slider->align(FL_ALIGN_CENTER); 
	UnD_slider->selection_color((Fl_Color)2);
	UnD_slider->type(FL_HORIZONTAL);
	UnD_slider->range(-400, 400);
	UnD_slider->step(0.5);
	UnD_slider->callback((Fl_Callback*)posy_pic_cb);
	}
	/*大小滑条初始化*/
	{Fl_Value_Slider* size_slider = new Fl_Value_Slider(520, 60, 120, 25, "大小：");
	size_slider->align(FL_ALIGN_CENTER);
	size_slider->selection_color((Fl_Color)2);
	size_slider->type(FL_HORIZONTAL);
	size_slider->range(-360, 360);
	size_slider->step(0.15);
	size_slider->callback((Fl_Callback*)size_pic_cb);
	}
	/*全屏按钮初始化*/
	Fl_Toggle_Light_Button fullwin_button(640+25, 60, 100, 27, "全屏");
	fullwin_button.callback(fullscreen_cb, win);
	win->resizable(window);
	win->show(g_argc, g_argv);
	win->redraw();
	win->end();
	win->callback(window_cb);
	Fl::run();
}
/*开始窗口开始初始化*/
void start_cb(Fl_Widget *o, void *p) {
	wel_window->hide();
	MainWindow();

}
/*开始窗口打开文件功能*/
void file_begin_cb(const char *n) {
	if (fl_filename_isdir(n)) {
		return;
	}
	img = Fl_Shared_Image::get(n);
	begin_img = imread(n);
	strcpy(img_name, n);
	strcpy(name, img_name);
}
/*开始窗口打开文件功能*/
void start_file_cb(Fl_Widget *o, void *p) {
	fl_file_chooser_callback(file_begin_cb);
	fl_file_chooser("Image file?", "*.{bmp,gif,jpg,pbm,pgm,png,ppm,xbm,xpm}", name);
	fl_file_chooser_callback(0);
	wel_window->hide();
	MainWindow();
}
/*开始窗口初始化*/
void welcome_window() {
	wel_window = new Fl_Double_Window(200, 200, 800, 600, "Photoshop start menu");
	wel_window->begin();
	{
		Fl_Box *win = new Fl_Box(0, 0, 800, 600);
		win->align(FL_ALIGN_CENTER);
		win->when(FL_WHEN_RELEASE);
		// Fl_Group::current()->resizable(draw_area);
		Fl_JPEG_Image* img2 = new Fl_JPEG_Image("background3.jpg");
		win->image(img2);
	}
	Fl_Button *start_button = new Fl_Button(400-75, 300 -30-15, 150, 40, "开始");
	start_button->callback(start_cb, (void*)0);
	Fl_Button *open_file_button = new Fl_Button(400-75, 300+60-5-5, 150, 40, "  打开文件");
	open_file_button->callback(start_file_cb, (void*)0);
	Fl_Button *help_button = new Fl_Button(400 - 75, 300 + 60+40+60-15, 150, 40, "帮助");
	help_button->callback(help_cb,(void*)0);
	wel_window->show(g_argc,g_argv);
}
int main(int argc, char **argv) {
	fl_register_images();
	g_argc = argc;
	g_argv = argv;
	welcome_window();
	return Fl::run();
}