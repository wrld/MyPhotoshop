/*Producted by Guojiaxin,from ZJU in 2019.6.18*/
#ifndef DRAWMAP_H
#define DRAWMAP_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

class MyDrawImage {
public:
	const int MAX_WIDTH = 500;
	const int MAX_HEIGHT = 400;
	const char *pstrSaveImageName = "MouseDraw.jpg";
	friend class MyImage;
	MyDrawImage();
	MyDrawImage(char* name);
	friend void saveCallback(const char* name, IplImage* pic);
	friend void on_mouse(int event, int x, int y, int flags, void* param);
};
inline void saveCallback(const char* name, IplImage* pic);

inline void on_mouse(int event, int x, int y, int flags, void* param);
#endif
