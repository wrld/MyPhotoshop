/*Producted by Guojiaxin,from ZJU in 2019.6.18*/
#pragma once
#ifndef BASICFUNCTIONS_H
#define BASICFUNCTIONS_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;
// 均值模糊
class MyImage:public Mat{
public:
	/*图片功能*/
	friend class MyImageRecovery;
	Mat myRot(int type);
	Mat myOpen_Close(int type);
	Mat myImageRecover(string filter_type, Size size);
	Mat myBlur(  int coe);
	Mat myGaussianBlur(  int coe);
	Mat myGlass();
	Mat myRotation(  double angle);
	Mat myResize(  double scale);
	Mat myGray();
	Mat myBrightChange(  int beta);
	Mat myCNTChange(  int value);	
	int myFaceDetection();
	int myBeauty();
	Mat myThreshold( double threshold_value, int threshold_type);
	Mat myBlend(Mat src2, double alpha);
	Mat mySalt(double salt_ratio);
	MatND getHistt();
	Mat draw_Hist();
	Mat myCanny();
	Mat mySobel();
	Mat myLog();
	Mat myIndex();
	Mat myLinear_Transform();
	MatND getHist1();
	Mat myEqualize_hist();
	Mat myOld();
	/*文件操作*/
	void mySavePic();
	void myDeletePic(const char *a);
	string myNewName();
	Mat goToVersion(int v);
	MyImage(Mat src1,char* addr1);
	void mySavePic(const char* name);
	int version = 0;
	string new_name;
	string old_name;
	Mat src;
	string forward;
	string back;
	Mat rawSrc;
	int MyMaxVersion() {
		int MyMaxVersion;
		MyMaxVersion = histry_pic.size();
		return MyMaxVersion;
	}
	~MyImage(); 
private:
	double x;
	double y;
	int saltVersion;
	int cntVersion;
	int brightVersion;
	string addr;
	vector<Mat> histry_pic;

};
/*去噪类*/
class MyImageRecovery {
private:
	double MyFilterAver(Mat src);
	double MyFilterGeo(Mat src);
	double MyFilterHar(Mat src);
	void MyBubbleSort(float* pData, int count);
	double MyFilterMedian(Mat src);
public:
	friend class MyImage;
	Mat MyFilter(Mat image, string filter_type, Size size);
};

#endif