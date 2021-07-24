

#ifndef __ROTATEIMAGE__H__
#define __ROTATEIMAGE__H__

#include "opencv2/opencv.hpp"
#include<stdio.h>
	
/*
inputPath 输入路径
outputPath 输出路径
angle 旋转角度
*/

	bool GetRotatedImageWithPathOCR(unsigned char * inputPath,unsigned char *outputPath, int &angle);
/*

*/
	int GetRotatedImageOCR(unsigned char *RGBImage, int imageWidth, int imageHeight,
	unsigned char *&RGBOutImage, int &imageOutWidth, 
	int &imageOutHeight,float *paraList);

/*
	输入cv::Mat的内存对象以及图像宽高，输出角度
*/
	int GetRotatedImageAngle(unsigned char *RGBImage, int imageWidth, int imageHeight);
	
/*
	
*/
//
	int GetRecogResultIn(const char *ocrUrl, const char * tmpFileSavePath, const char * inputPath, char ** strJson, int *strLen);
	int GetRecogResultWithTitle(const char *ocrUrl, const char * tmpFileSavePath, const char * inputPath, 
								int *TitlePos,
								char ** strJson, int *strLen);
	int ReleaseResultMemoryIn(char * p);



#endif

