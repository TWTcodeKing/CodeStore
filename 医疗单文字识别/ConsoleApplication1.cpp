#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;


Mat Gaussian_filtering(Mat SrcImg){
	Mat result(SrcImg.rows, SrcImg.cols, CV_8U);
	double Gaussian_Matrix[3][3];
	int Regulized_Gaussian_Matrix[3][3];
	int Regulization_factor = 0;
	float DLT = 1.0;//高斯函数中的参数
	//生成高斯滤波器
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			Gaussian_Matrix[i][j] = (double)exp(-((i - 1)*(i - 1) + (1 - j)*(1 - j)) / (2 * DLT*DLT)) * (1 / (2 * 3.14*DLT));
			Regulization_factor = (int)1 / Gaussian_Matrix[0][0];
			Regulized_Gaussian_Matrix[i][j] = Gaussian_Matrix[i][j] * Regulization_factor;
			if (abs(i - 1) == 1 && abs(1 - j) == 1){
				Regulized_Gaussian_Matrix[i][j] = 1;
			}
		}
	}
	//接下来进行卷积
	uchar SlideWindow[3][3];
	for (int i = 0; i < SrcImg.rows; i++){
		for (int j = 0; j < SrcImg.cols; j++){
			if (i == 0 || i == SrcImg.rows - 1 || j == 0 || j == SrcImg.cols - 1){
				result.ptr<uchar>(i)[j] = SrcImg.ptr<uchar>(i)[j];
				continue;
			}
			int value = 0;
			for (int index_row = 0; index_row < 3; index_row++){
				for (int index_col = 0; index_col < 3; index_col++){
					value += SrcImg.ptr<uchar>(i + index_row - 1)[j + index_col - 1] * Regulized_Gaussian_Matrix[index_row][index_col];
				}
			}
			result.ptr<uchar>(i)[j] = value / Regulization_factor;
		}//正常情况
	}
	return result;
}//高斯滤波器
Mat Laplace_differencial(Mat SrcImg){
	Mat result(SrcImg.rows, SrcImg.cols, CV_8U);
	int Laplace_horizon[3][3] = { { 1, 1, 1 }, { 1, -8, 1 }, { 1, 1, 1 } };
	int Laplace_vertical[3][3] = { { -1, -1, -1 }, { -1, 8, -1 }, { -1, -1, -1 } };
	for (int i = 0; i < SrcImg.rows; i++){
		for (int j = 0; j < SrcImg.cols; j++){
			if (i == 0 || i == SrcImg.rows - 1 || j == 0 || j == SrcImg.cols - 1){
				result.ptr<uchar>(i)[j] = SrcImg.ptr<uchar>(i)[j];
				continue;
			}
			int value = 0;
			for (int index_row = 0; index_row < 3; index_row++){
				for (int index_col = 0; index_col < 3; index_col++){
					value += SrcImg.ptr<uchar>(i + index_row - 1)[j + index_col - 1] * Laplace_horizon[index_row][index_col];
				}
			}
			result.ptr<uchar>(i)[j] = value;
		}
	}
	imwrite("C:\\Users\\TWT\\Desktop\\Laplace.jpg", result);
	waitKey(0);
	return result;
}
Mat Sobel_differencial(Mat SrcImg){
	Mat result(SrcImg.rows, SrcImg.cols, CV_8U);//梯度强度图
	//还需要一张梯度方向图
	int Sobel_horizon[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
	int Sobel_vertical[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
	for (int i = 0; i < SrcImg.rows; i++){
		for (int j = 0; j < SrcImg.cols; j++){
			if (i == 0 || i == SrcImg.rows - 1 || j == 0 || j == SrcImg.cols - 1){
				result.ptr<uchar>(i)[j] = SrcImg.ptr<uchar>(i)[j];
				continue;
			}
			int x_Gradient = 0;
			int y_Gradient = 0;
			for (int index_row = 0; index_row < 3; index_row++){
				for (int index_col = 0; index_col < 3; index_col++){
					x_Gradient += SrcImg.ptr<uchar>(i + index_row - 1)[j + index_col - 1] * Sobel_horizon[index_row][index_col];
					y_Gradient += SrcImg.ptr<uchar>(i + index_row - 1)[j + index_col - 1] * Sobel_vertical[index_row][index_col];
				}
			}
			result.ptr<uchar>(i)[j] = abs(x_Gradient) + abs(y_Gradient);
		}
	}
	imwrite("C:\\Users\\TWT\\Desktop\\商店_79.jpg", result);
	waitKey(0);
	return result;
}
int main(){
	Mat SrcImg = imread("C:\\Users\\TWT\\Desktop\\商店_79.jpg",cv::COLOR_BGR2GRAY);
	imshow("灰度图", SrcImg);
	waitKey(0);
	SrcImg = Gaussian_filtering(SrcImg);
	imshow("高斯滤波结果", SrcImg);
	waitKey(0);
	Sobel_differencial(SrcImg);

	return 0;

}
// variables to store images
/*Mat dst, cimg, gray, img, edges;

int initThresh;
const int maxThresh = 1000;
double th1, th2;

// create a vector to store points of line
vector<Vec4i> lines;
void  Copyto(Mat dst,Mat setout){
	Mat imageROI1 = dst(Rect(0, 491, setout.cols, setout.rows));
	Mat mask1 = imread("C:\\Users\\TWT\\Desktop\\qr_barcode.jpg", 0);
	setout.copyTo(imageROI1, mask1);
}
void onTrackbarChange(int, void*)
{
	//复制目标图像
	cimg = img.clone();
	//结果图像
	dst = img.clone();

	th1 = initThresh;
	th2 = th1 * 0.4;
	//canny边缘检测
	Canny(img, edges, th1, th2);

	// apply hough line transform 霍夫曼变换
	HoughLinesP(edges, lines, 2, CV_PI / 180, 50, 10, 100);

	// draw lines on the detected points 画线

	for (size_t i = 0; i < lines.size(); i++)
	{
		//提取线条坐标点
		Vec4i l = lines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, CV_AA);
	}
	//Mat Init = imread("C:\\Users\\TWT\\Desktop\\qr_barcode.jpg");
	
	//Mat finalResult;
	//Copyto(Init, dst);
	imshow("Canny", edges);
	imshow("Result Image", dst);
	//imshow("result", Init);
	////imwrite("C:\\Users\\TWT\\Desktop\\result.jpg", Init);
}

int main()
{
	// Read image (color mode) 读图
	img = imread("C:\\Users\\TWT\\Desktop\\qr_barcode.jpg", 1);
	dst = img.clone();

	if (img.empty())
	{
		cout << "Error in reading image" << endl;
		return -1;
	}

	// Convert to gray-scale 转换为灰度图像
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// Detect edges using Canny Edge Detector
	// Canny(gray, dst, 50, 200, 3);

	// Make a copy of original image
	// cimg = img.clone();

	// Will hold the results of the detection
	namedWindow("Edges", 1);
	namedWindow("Result Image", 1);

	// Declare thresh to vary the max_radius of circles to be detected in hough transform
	// 霍夫曼变换阈值
	initThresh = 500;

	// Create trackbar to change threshold values
	//滑动条
	createTrackbar("threshold", "Result Image", &initThresh, maxThresh, onTrackbarChange);
	onTrackbarChange(initThresh, 0);
	
	while (true)
	{
		int key;
		key = waitKey(1);
		if ((char)key == 27)
		{
			break;
		}
	}
	destroyAllWindows();
	
	return 0;
}*/