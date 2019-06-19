/*Producted by Guojiaxin,from ZJU in 2019.6.18*/

#include"Basic_Functions.h"

//膨胀与腐蚀：1：膨胀 2：腐蚀
Mat MyImage::myRot(int type) {
	Mat dilate_dst, gray, erode_dst;
	Mat element = getStructuringElement(MORPH_RECT, Size(8, 8));
	if (type == 1) {
		dilate(src, dilate_dst, element);
		version++;
		histry_pic.push_back(dilate_dst);
		src = dilate_dst;
		return dilate_dst;
	}
	else {
		erode(src, erode_dst, element);
		version++;
		histry_pic.push_back(erode_dst);
		src = erode_dst;
		return erode_dst;
	}
}
//开闭运算0：开 1：闭 3：形态梯度
Mat MyImage::myOpen_Close(int type) {
	Mat close, gray, open, dst;
	open = src;
	close = src;
	Mat element = getStructuringElement(MORPH_RECT, Size(8, 8));
	cvtColor(src, gray, CV_BGR2GRAY);
	threshold(gray, gray, 100, 255, THRESH_BINARY);
	switch (type) {
	case 1:
		morphologyEx(gray, open, MORPH_OPEN, element);
		version++;
		histry_pic.push_back(open);
		src = open;
		return open;
		break;
	case 2:
		morphologyEx(gray, close, MORPH_CLOSE, element);
		version++;
		histry_pic.push_back(close);
		src = close;
		return close;
		break;
	case 3:
		morphologyEx(src, dst, MORPH_GRADIENT, element);
		version++;
		histry_pic.push_back(dst);
		src = dst;
		return dst;
		break;
	default:
		return src;
		break;
	}
}
/*四种去噪方法*/
Mat MyImage::myImageRecover(string filter_type, Size size) {
	MyImageRecovery IR;
	Mat result = IR.MyFilter(src, filter_type, size);
	version++;
	histry_pic.push_back(result);
	src = result;
	return result;
}
/*椒盐噪声*/
Mat MyImage::mySalt(double salt_ratio) {
	Mat image;
	if (saltVersion != version) {
		image = src.clone();
	}
	else {
		image = rawSrc.clone();
	}
	int n = image.rows*image.cols*salt_ratio;
	for (int k = 0; k < n; k++)
	{
		int i = rand() % image.cols;
		int j = rand() % image.rows;
		int type = rand() % 2;
		if (type == 1) {
			image.at<Vec3b>(j, i)[0] = 255;
			image.at<Vec3b>(j, i)[1] = 255;
			image.at<Vec3b>(j, i)[2] = 255;
		}
		else {
			image.at<Vec3b>(j, i)[0] = 0;
			image.at<Vec3b>(j, i)[1] = 0;
			image.at<Vec3b>(j, i)[2] = 0;
		}
	}
	if (saltVersion != version) {
		rawSrc = image.clone();
	}
	version++;
	histry_pic.push_back(image);
	src = image;
	saltVersion = version;
	return image;
}
/*均值滤波*/
Mat MyImage::myBlur(int coe)
{
	Mat dest;
	blur(src, dest, Size(coe, coe));
	version++;
	histry_pic.push_back(dest);
	src = dest;
	return dest;
}
/*高斯滤波*/
Mat MyImage::myGaussianBlur(int coe)
{
	Mat dst;
	int ksize1 = 11;
	int ksize2 = 11;
	double sigma1 = 10.0;
	double sigma2 = 20.0;
	cv::GaussianBlur(src, dst, cv::Size(ksize1, ksize2), sigma1, sigma2);
	version++;
	histry_pic.push_back(dst);
	src = dst;
    return dst;
}
/*人脸美颜*/
int  MyImage::myBeauty() {
	string face_cascade_name = "haarcascade_frontalface_alt2.xml";

	CascadeClassifier face_cascade;
	Mat frame;
	if (!face_cascade.load(face_cascade_name))
	{
		cout << "load failed" << endl;
	}

	frame = src.clone();
	vector<Rect> faces;
	Mat frame_gray;
	vector<Mat> rois;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	if (faces.empty()) {
		return 0;
	}
	for (auto iter = faces.begin(); iter != faces.end(); iter++)
	{
		rectangle(frame, *iter, Scalar(0, 255, 0), 2);
		rois.push_back(frame(*iter));
	}
	for (auto iter = rois.begin(); iter != rois.end(); iter++)
	{
		int rows = iter->rows;
		int cols = iter->cols*iter->channels();
		for (int i = 0; i < rows; i++)
		{
			uchar* data = iter->ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				data[j] = saturate_cast<uchar>(data[j] * 1.1 + 68);
			}
		}
	}
	for (int i = 0; i < rois.size(); i++)
	{
		Mat roi;
		GaussianBlur(rois[i], roi, Size(5, 5), 0, 0);
		Mat roi1;
		bilateralFilter(roi, roi1, 30, 30 * 2, 30 / 2);  //双边滤波
		Mat matFinal;
		GaussianBlur(roi1, matFinal, Size(0, 0), 9);
		addWeighted(roi1, 1.5, matFinal, -0.5, 0, rois[i]);   //这一步相当于非掩膜锐化
		string win_name = "faces_" + to_string(i + 1);
	}
	version++;
	histry_pic.push_back(frame);
	src = frame;
	return 1;
}
/*毛玻璃效果*/
Mat MyImage::myGlass()
{
	Mat dest = src.clone();
	RNG rng;
	int randomNum;
	int Number = 5;

	for (int i = 0; i < src.rows - Number; i++)
		for (int j = 0; j < src.cols - Number; j++)
		{
			randomNum = rng.uniform(0, Number);
			dest.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i + randomNum, j + randomNum)[0];
			dest.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i + randomNum, j + randomNum)[1];
			dest.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i + randomNum, j + randomNum)[2];
		}
	version++;
	histry_pic.push_back(dest);
	src = dest;
	return dest;
}
/*得到直方图*/
MatND MyImage::getHistt() {
	MatND hist;
	int channels[] = { 0 };
	int dims = 1;
	int histSize[] = { 256 };  
	float granges[] = { 0, 255 };
	const float *ranges[] = { granges };  
	calcHist(&src, 1, channels, Mat(), hist, dims, histSize, ranges);
	return hist;  //这里得到的hist是256行一列的Mat
}
/*画出直方图*/
Mat MyImage::draw_Hist()
{
	cv::MatND hist = getHistt();
	Mat showImage(256, 256, CV_8U, Scalar(255));
	int i;
	double maxValue = 0;
	minMaxLoc(hist, 0, &maxValue, 0, 0);
	for (i = 0; i < 256; i++)
	{
		float value = hist.at<float>(i);
		int intensity = saturate_cast<int>(256 - 256 * (value / maxValue));
		rectangle(showImage, Point(i, 256 - 1), Point((i + 1) - 1, intensity), Scalar(0));
	}
	namedWindow("gray"); imshow("gray", showImage);
	return showImage;
}

/*图片旋转*/
Mat MyImage::myRotation(double angle)
{
	Mat dest;
	Size sz;
	sz.width = src.size().width;
	sz.height = src.size().height;
	Point2f center(sz.width / 2, sz.height / 2);
	Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);
	warpAffine(src, dest, rot_mat, sz);
	version++;
	histry_pic.push_back(dest);
	src = dest;
	return dest;
}
/*调整图片大小*/
Mat MyImage::myResize( double scale)
{
	Mat dest;
	Size sz;
	sz.width = src.size().width;
	sz.height = src.size().height;
	Size dest_sz = Size(sz.width*scale, sz.height*scale);
	cv::resize(src, dest, dest_sz);
	version++;
	histry_pic.push_back(dest);
	src = dest;
	return dest;
}
/*灰度图*/
Mat MyImage::myGray()
{
	Mat dest ;
	cvtColor(src, dest, CV_BGR2GRAY);
	version++;
	histry_pic.push_back(dest);
	src = dest;
	return dest;
}
/*调整为怀旧色*/
Mat MyImage::myOld() {
	int width = src.cols;
	int heigh = src.rows;
	RNG rng;
	Mat img(src.size(), CV_8UC3);
	for (int y = 0; y<heigh; y++)
	{
		uchar* P0 = src.ptr<uchar>(y);
		uchar* P1 = img.ptr<uchar>(y);
		for (int x = 0; x<width; x++)
		{
			float B = P0[3 * x];
			float G = P0[3 * x + 1];
			float R = P0[3 * x + 2];
			float newB = 0.272*R + 0.534*G + 0.131*B;
			float newG = 0.349*R + 0.686*G + 0.168*B;
			float newR = 0.393*R + 0.769*G + 0.189*B;
			if (newB<0)newB = 0;
			if (newB>255)newB = 255;
			if (newG<0)newG = 0;
			if (newG>255)newG = 255;
			if (newR<0)newR = 0;
			if (newR>255)newR = 255;
			P1[3 * x] = (uchar)newB;
			P1[3 * x + 1] = (uchar)newG;
			P1[3 * x + 2] = (uchar)newR;
		}

	}
	version++;
	histry_pic.push_back(img);
	src = img;
	return img;
}
/*亮度调整*/ 
Mat MyImage::myBrightChange(int beta)
{
	Mat image;
	if (brightVersion != version) {
		image = src.clone();
	}
	else {
		image = rawSrc.clone();
	}
	Mat dest = Mat::zeros(image.size(), image.type());
	for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
			for (int c = 0; c < 3; c++)
				dest.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(image.at<Vec3b>(y, x)[c] + beta);
	if (brightVersion != version) {
		rawSrc = dest.clone();
	}
	version++;
	histry_pic.push_back(dest);
	src = dest;
	brightVersion = version;
	return dest;
}
/*对比度调整*/
Mat MyImage::myCNTChange(int value)
{
	Mat image;
	if (cntVersion != version) {
		image = src.clone();
	}
	else {
		image = rawSrc.clone();
	}
	Mat dest = Mat::zeros(image.size(), image.type());
	float alpha = value / 100.0;
	for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
			for (int c = 0; c < 3; c++)
				dest.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((alpha + 1)*(image.at<Vec3b>(y, x)[c]));
	if (cntVersion != version) {
		rawSrc = dest.clone();
	}
	version++;
	histry_pic.push_back(dest);
	src = dest;
	cntVersion = version;
	return dest;
}
/*人脸识别*/
int MyImage::myFaceDetection()
{
	Mat src_gray;

	cvtColor(src, src_gray, CV_BGR2GRAY);//转为灰度图
	equalizeHist(src_gray, src_gray);

	CascadeClassifier eye_Classifier;  //载入分类器
	CascadeClassifier face_cascade;  
	if (!eye_Classifier.load("haarcascade_eye.xml")) {
		std::cout << "Load haarcascade_eye.xml failed!" << std::endl;
		return 0;
	}

	if (!face_cascade.load("haarcascade_frontalface_alt2.xml")) {
		std::cout << "Load haarcascade_frontalface_alt2 failed!" << std::endl;
		return 0;
	}
	std::vector<Rect> eyeRect;
	std::vector<Rect> faceRect;
	eye_Classifier.detectMultiScale(src_gray, eyeRect, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	if ( faceRect.empty()&& eyeRect.empty()) {
		return 0;
	}
	for (size_t eyeIdx = 0; eyeIdx < eyeRect.size(); eyeIdx++) {
		rectangle(src, eyeRect[eyeIdx], Scalar(0, 255, 0));   //用矩形画出检测到的位置
	}
	face_cascade.detectMultiScale(src_gray, faceRect, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faceRect.size(); i++) {
		rectangle(src, faceRect[i], Scalar(0, 255, 0));      //用矩形画出检测到的位置
	}
	version++;
	histry_pic.push_back(src);
	return 1;
}
// 图片阈值化
Mat MyImage::myThreshold(double threshold_value, int threshold_type)
{
	/* 0: 二进制阈值
	1: 反二进制阈值
	2: 截断阈值
	3: 0阈值
	4: 反0阈值
	*/

	Mat src_gray;
	Mat dest=src;
	cvtColor(src, src_gray, CV_BGR2GRAY);
	int max_BINARY_value = 255;
	threshold(src, dest, threshold_value, 255, 0);
	version++;
	histry_pic.push_back(dest);
	src = dest;
	return src;
}
/*canny算子边缘检测*/
Mat MyImage::myCanny()
{
	Mat DstPic, edge, grayImage;
	DstPic.create(src.size(), src.type());
	cvtColor(src, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, edge, Size(3, 3));
	Canny(edge, edge, 3, 9, 3);
	version++;
	histry_pic.push_back(edge);
	src = edge;
	return edge;
}

MatND MyImage::getHist1()
{
	MatND hist;
	int channels[] = { 0 };
	int dims = 1;
	int histSize[] = { 256 };   
	float granges[] = { 0, 255 };
	const float *ranges[] = { granges }; 
	calcHist(&src, 1, channels, Mat(), hist, dims, histSize, ranges);
	return hist; 
}

/*直方图均衡化*/
Mat MyImage::myEqualize_hist()
{
	MatND hist;
	Mat dst;
	int channels[] = { 0 };
	int dims = 1;
	int histSize[] = { 256 };
	float granges[] = { 0, 255 };
	const float *ranges[] = { granges };
	Mat image = src.clone();
	calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);
	float s[256];
	float p[256];
	cv::Mat lookup(cv::Size(1, 256), CV_8U);
	int pixNum = src.cols * src.rows;//总像素个数
	for (int i = 0; i < 256; i++) {
		s[i] = hist.at<float>(i) / pixNum;
		if (i == 0) {
			p[i] = s[i];
		}
		else {
			p[i] = p[i - 1] + s[i];
		}
	}
	for (int i = 0; i < 256; i++) {
		lookup.at <uchar>(i) = static_cast<uchar>(p[i] * 255.0);
	}

	cv::LUT(src, lookup, dst);//创建矩阵，把一个像素值映射到另一个像素值
	version++;
	histry_pic.push_back(dst);
	src = dst;
	return dst;
}
/*线性灰度增强*/
Mat MyImage::myLinear_Transform()
{
	Mat dst;
	int b = 0, a = 255;
	dst = src.clone();
	int row = dst.rows, col = dst.cols * dst.channels();
	uchar *cc = dst.data,c=255,d=0;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			int val = *cc;
			if (a > val) a = val;
			if (b < val) b = val;
			cc++;
		}
	}
	cc = dst.data;
	float k = float(d - c) / (b - a);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			int val = *cc;
			int s = (int)(k*(val - a) + c);
			*cc = s;
			cc++;
		}
	}
	version++;
	histry_pic.push_back(dst);
	src = dst;
	return dst;
}
/*对数变换*/
Mat MyImage::myLog()
{
	Mat dst;
	dst = src.clone();
	int row = dst.rows, col = dst.cols * dst.channels();
	uchar *cc = dst.data;
	double k = 255 / log10(256.0);
	for (int i = 0; i < row; ++i) {
	for (int j = 0; j < col; ++j) {
	int val = *cc;
	*cc = k * log10(1.0*(val + 1));
	cc++;

		}
	}
	version++;
	histry_pic.push_back(dst);
	src = dst;
	return dst;
}
/*指数变换*/
Mat MyImage::myIndex()
{
	Mat dst;
	dst = src.clone();
	int row = dst.rows, col = dst.cols * dst.channels();
	uchar *cc = dst.data;
	double k = 1.0 / 255;
	for (int i = 0; i < row; ++i) {
	for (int j = 0; j < col; ++j) {
	int val = *cc;
	 * cc = k * val * val;
     cc++;
		}
	
	}
	version++;
	histry_pic.push_back(dst);
	src = dst;
	return dst;
}
/*sobel算子边缘检测*/
Mat MyImage::mySobel()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//求x方向梯度
	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("x方向soble", abs_grad_x);

	//求y方向梯度
	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y向soble", abs_grad_y);

	//合并梯度
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	version++;
	histry_pic.push_back(dst);
	src = dst;
	return dst;
}
/*图片混合*/
Mat MyImage::myBlend(Mat src2, double alpha)
{
	Mat src1,dest, src2_re;
	src1 = this->src;
	double beta = 1 - alpha;

	Size sz;
	sz.width = src1.size().width;
	sz.height = src1.size().height;
	cv::resize(src2, src2_re, Size(src1.cols, src1.rows));
	addWeighted(src1, beta, src2_re, alpha, 0.0, dest);
	version++;
	histry_pic.push_back(dest);
	src = dest;
	return dest;
}
/*保存图片*/
void MyImage::mySavePic() {
	stringstream stream;
	string s;
	s = addr;
	forward = addr.substr(0, addr.length() - 4);
	back = addr.substr(addr.length() - 4, addr.length());
	stream << forward << version << back;
	stream >> s;
	imwrite(s,src);   //保存修改后的图片
	old_name = new_name;
	new_name = s;
}

/*重载保存图片*/
void MyImage::mySavePic(const char* name) {
	stringstream stream;
	string s;
	s = addr;
	stream << name << version << back;
	stream >> s;
	//new_name = s;
	imwrite(s, src);   //保存修改后的图片
	old_name = new_name;
	new_name = s;
}
/*删除图片*/
void MyImage::myDeletePic(const char * a) {
	int result = remove(a); 
	if (result == 0)
		cout << "delete succeeded!" << endl;
	else
		cout << "delete failed!" << endl;
}
/*回退、前进*/
Mat MyImage::goToVersion(int v){
	Mat pick_pic;
	pick_pic = histry_pic[v];
	src = pick_pic;
	version = v;
	return pick_pic;
}
/*获得最新的地址*/
string MyImage::myNewName() {
	stringstream stream;
	string s;
	string forward;
	string back;
	s = addr;
	forward = addr.substr(0, addr.length() - 4);
	back = addr.substr(addr.length() - 4, addr.length());
	stream << forward << version << back;
	stream >> s;
	old_name = new_name;
	new_name = s;
	imwrite(s,src);
	return s;
}
/*构造函数*/
MyImage::MyImage(Mat src1, char* addr1) {
	stringstream stream;
	string s;
	stream << addr1;
	stream >> s;
	this->src = src1;
	this->addr = s;
	new_name = addr;
	x = src.size().width;
	y = src.size().height;
	histry_pic.push_back(src1);
}
/*析构函数*/
MyImage::~MyImage() {
	src.release();
	rawSrc.release();
	histry_pic.clear();
}
/*算数均值滤波*/
double MyImageRecovery::MyFilterAver(Mat src)
{
	double sum = 0;
	for (int i = 0; i < src.rows; i++) {
		uchar* data = src.ptr<uchar>(i);
		for (int j = 0; j <src.cols; j++) {
			sum += double(data[j]);
		}
	}
	return sum / double(src.cols* src.rows);
}
/*几何均值滤波*/
double MyImageRecovery::MyFilterGeo(Mat src)
{
	double geo = 1;
	for (int i = 0; i < src.rows; i++) {
		uchar* data = src.ptr<uchar>(i);
		for (int j = 0; j <src.cols; j++) {
			if (data[j] != 0) geo *= data[j];
		}
	}
	double power = 1.0 / double(src.cols*src.rows);
	return pow(geo, power);
}
/*谐波滤波*/
double MyImageRecovery::MyFilterHar(Mat src)
{
	double har = 0;
	for (int i = 0; i < src.rows; i++) {
		uchar* data = src.ptr<uchar>(i);
		for (int j = 0; j <src.cols; j++) {
			if (data[j] != 0) har += 1 / (double)(data[j]);
		}
	}
	return (src.cols*src.rows) / har;
}
/*冒泡排序*/
void MyImageRecovery::MyBubbleSort(float* pData, int count)
{
	float tData;
	for (int i = 1; i < count; i++) {
		for (int j = count - 1; j >= i; j--) {
			if (pData[j] < pData[j - 1]) {
				tData = pData[j - 1];
				pData[j - 1] = pData[j];
				pData[j] = tData;
			}
		}
	}
}
/*中值滤波*/
double MyImageRecovery::MyFilterMedian(Mat src)
{
	int index = 0;
	int bubble_len = (src.cols)*(src.rows);
	float* bubble = new float[bubble_len];
	for (int i = 0; i < src.rows; i++) {
		uchar* data = src.ptr<uchar>(i);
		for (int j = 0; j <src.cols; j++) {
			bubble[index] = data[j];
			index++;
		}
	}
	MyBubbleSort(bubble, bubble_len);
	double median = bubble[bubble_len / 2];
	return median;
}
/*去噪*/
Mat MyImageRecovery::MyFilter(Mat image, string filter_type, Size size)
	{
		Mat result;
		image.copyTo(result);
		Mat channel[3];
		split(image, channel);
		int l = (size.height - 1) / 2;
		int w = (size.width - 1) / 2;
		for (int i = l; i < result.rows - l; i++) {
			for (int j = w; j < result.cols - w; j++) {
				for (int ii = 0; ii < 3; ii++) {
					if (filter_type == "aver")    result.at<Vec3b>(i, j)[ii] = saturate_cast<uchar>(MyFilterAver(channel[ii](Rect(j - w, i - l, size.width, size.height))));
					if (filter_type == "geo")    result.at<Vec3b>(i, j)[ii] = saturate_cast<uchar>(MyFilterGeo(channel[ii](Rect(j - w, i - l, size.width, size.height))));
					if (filter_type == "har")    result.at<Vec3b>(i, j)[ii] = saturate_cast<uchar>(MyFilterHar(channel[ii](Rect(j - w, i - l, size.width, size.height))));
					if (filter_type == "median") result.at<Vec3b>(i, j)[ii] = saturate_cast<uchar>(MyFilterMedian(channel[ii](Rect(j - w, i - l, size.width, size.height))));
				}
			}
		}
		return result;
	}