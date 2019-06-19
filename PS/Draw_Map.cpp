/*Producted by Guojiaxin,from ZJU in 2019.6.18*/
#pragma once
#include "Draw_Map.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
const char *WINDOW_NAME = "鼠标绘图";

MyDrawImage::MyDrawImage() {}
/*构造函数*/
MyDrawImage::MyDrawImage(char* name) {
		char *imagename = name;
		IplImage *pSrcImage = cvLoadImage(imagename);
		cvNamedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
		cvShowImage(WINDOW_NAME, pSrcImage);
		cvResizeWindow(WINDOW_NAME, pSrcImage->width, pSrcImage->height);
		cvSetMouseCallback(WINDOW_NAME, on_mouse, (void*)pSrcImage);
			int c;
		do {
			c = cvWaitKey(0);
			switch ((char)c)
			{
			case 'r':
				cvSet(pSrcImage, CV_RGB(255, 255, 255));
				cvShowImage(WINDOW_NAME, pSrcImage);
				break;

			case 's':
				cvSaveImage(pstrSaveImageName, pSrcImage);
				break;
			}
		} while (c > 0 && c != 27);

		cvDestroyWindow(WINDOW_NAME);
		cvReleaseImage(&pSrcImage);
	}
/*保存回调函数*/
void saveCallback(const char* name,IplImage* pic) {
	cvSaveImage(name, pic);
}
/*鼠标回调函数*/
void on_mouse(int event, int x, int y, int flags, void* param) {
	static bool s_bMouseLButtonDown = false;
	static CvPoint s_cvPrePoint = cvPoint(0, 0);

	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		s_bMouseLButtonDown = true;
		s_cvPrePoint = cvPoint(x, y);
		break;

	case  CV_EVENT_LBUTTONUP:
		s_bMouseLButtonDown = false;
		break;

	case CV_EVENT_MOUSEMOVE:
		if (s_bMouseLButtonDown)
		{
			CvPoint cvCurrPoint = cvPoint(x, y);
			cvLine((IplImage*)param, s_cvPrePoint, cvCurrPoint, CV_RGB(50, 50, 20), 3);
			s_cvPrePoint = cvCurrPoint;
			cvShowImage(WINDOW_NAME, (IplImage*)param);
		}
		break;
	}
}
	

