
#include "RotateImage.h"
#include "config.hpp"
#include "opencv2/opencv.hpp"
#include <direct.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include<string>
#include <iostream>
#include <time.h>
using namespace cv;
using namespace std;

#define RES_OK 0
#define RES_CURL_INIT_ERROR (-1)
#define RES_READ_OCR_IMAGE_ERROR (-2)
#define RES_ALLOC_RES_MEMORY_ERROR (-3)
#define RES_CURL_PERFORM_ERROR (-4)
#define RES_REPLACE_BASE64_ERROR (-5)
#define RES_CURL_RETURN_NULL (-6)

//#ifdef _WIN32
//	#pragma comment(lib,"libcurl.lib")
//#endif
//Éú³ÉÐý×ªŸØÕóµÄsin cosœÇ¶ÈÖµ
//  [x1]   [cos0 -sin0  0]  [x0]
//  [y1] = [sin0  cos0  0]  [y0]
//  [1 ]   [ 0     0    1]  [1]
//Äæ±ä»»
//  [x0]   [cos0   sin0  0]  [x1]
//  [y0] = [-sin0  cos0  0]  [y1]
//  [1 ]   [  0     0    1]  [1]

//²œ³€Îª°ë¶È£¬ËùÒÔx2×öÏÂ±ê
//-40 ~40¶È£¬²œ³€Îª0.5
#include <curl/curl.h>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fstream>
#include<iostream>
using namespace std;
#define POSTURL    "211.138.112.184:9556/ocr/api/img/recognize"
#define POSTFIELDS "image=file"
#define FILENAME   "./1.txt"
//#ifdef _WIN32
//	#pragma comment(lib,"libcurl.lib")
//#endif
//#define OUTPUT_FILE






void GenPreCosSinValue()
{
	FILE *fp = fopen("angel.txt", "w+");

	//static int _sin65536[21]	
	int idx = 0;
	for (float i = -40; i <= 40; i+=0.5)
	{
		double arc = i  * CV_PI / 180.; // »¡¶È    
		double a = sin(arc);

		idx++;
		fprintf(fp, "%d, ", int(a * 65536));
	}
	fprintf(fp, "\n%d\n", idx);

	//static int _cos65536[21]	
	for (float i = -40; i <= 40; i += 0.5)
	{
		double arc = i  * CV_PI / 180.; // »¡¶È    
		double b = cos(arc);

		fprintf(fp, "%d, ", int(b * 65536));
	}
	fprintf(fp, "\n");

	//static int _invertSin65536[21]	
	for (float i = -40; i <= 40; i += 0.5)
	{
		double arc = i  * CV_PI / 180.; // »¡¶È    
		double a = -sin(arc);

		fprintf(fp, "%d, ", int(a * 65536));
	}
	fprintf(fp, "\n");
	//static int _invertCos65536[21]	
	for (float i = -40; i <= 40; i += 0.5)
	{
		double arc = i  * CV_PI / 180.; // »¡¶È    
		double b = cos(arc);

		fprintf(fp, "%d, ", int(b * 65536));
	}
	fprintf(fp, "\n");

	fclose(fp);
}

int Otsu(unsigned char *grayImage, int imageSize)
{
	const int N = 256;
	int i, j, h[N] = { 0 };

	for (j = 0; j <= imageSize - 4; j += 4)
	{
		int v0 = grayImage[j], v1 = grayImage[j + 1];
		h[v0]++; h[v1]++;
		v0 = grayImage[j + 2]; v1 = grayImage[j + 3];
		h[v0]++; h[v1]++;
	}
	for (; j < imageSize; j++)
		h[grayImage[j]]++;

	double mu = 0, scale = 1. / imageSize;
	for (i = 0; i < N; i++)
		mu += i*h[i];

	mu *= scale;
	double mu1 = 0, q1 = 0;
	double max_sigma = 0, max_val = 0;

	for (i = 0; i < N; i++)
	{
		double p_i, q2, mu2, sigma;

		p_i = h[i] * scale;
		mu1 *= q1;
		q1 += p_i;
		q2 = 1. - q1;

		double qmin = q1 < q2 ? q1 : q2;
		double qmax = q1 > q2 ? q1 : q2;

		if (qmin < FLT_EPSILON || qmax > 1. - FLT_EPSILON)
			continue;

		mu1 = (mu1 + i*p_i) / q1;
		mu2 = (mu - q1*mu1) / q2;
		sigma = q1*q2*(mu1 - mu2)*(mu1 - mu2);
		if (sigma > max_sigma)
		{
			max_sigma = sigma;
			max_val = i;
		}
	}

	return int(max_val);
}

void GradYBinary(unsigned char *inGrayImage, int width, int height, unsigned char *outBinGradImage)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 1; j < height - 1; j++)
		{
			int pre = inGrayImage[(j - 1) *width + i];
			int next = inGrayImage[(j + 1) *width + i];
			outBinGradImage[j *width + i] = abs(next - pre);
		}
		outBinGradImage[i] = outBinGradImage[width + i];
		outBinGradImage[(height - 1) *width + i] = outBinGradImage[(height - 2) *width + i];
	}

	int thresh = Otsu(outBinGradImage, width *height);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j <height; j++)
		{
			if (outBinGradImage[j *width + i] >thresh)
			{
				outBinGradImage[j *width + i] = 255;
			}
			else
			{
				outBinGradImage[j *width + i] = 0;
			}
		}
	}
}

//[-40, 40£¬ 0.5]
static int _sin65536[161] = { -42125, -41686, -41243, -40797, -40347, -39895, -39440, -38982, -38521, -38056, -37589, -37119, -36647, -36171, -35693, -35212, -34728, -34242, -33753, -33262, -32767, -32271, -31772, -31271, -30767, -30261, -29752, -29242, -28729, -28213, -27696, -27177, -26655, -26132, -25606, -25079, -24550, -24019, -23486, -22951, -22414, -21876, -21336, -20794, -20251, -19707, -19160, -18613, -18064, -17513, -16961, -16408, -15854, -15299, -14742, -14184, -13625, -13065, -12504, -11942, -11380, -10816, -10252, -9686, -9120, -8554, -7986, -7418, -6850, -6281, -5711, -5141, -4571, -4000, -3429, -2858, -2287, -1715, -1143, -571, 0, 571, 1143, 1715, 2287, 2858, 3429, 4000, 4571, 5141, 5711, 6281, 6850, 7418, 7986, 8554, 9120, 9686, 10252, 10816, 11380, 11942, 12504, 13065, 13625, 14184, 14742, 15299, 15854, 16408, 16961, 17513, 18064, 18613, 19160, 19707, 20251, 20794, 21336, 21876, 22414, 22951, 23486, 24019, 24550, 25079, 25606, 26132, 26655, 27177, 27696, 28213, 28729, 29242, 29752, 30261, 30767, 31271, 31772, 32271, 32767, 33262, 33753, 34242, 34728, 35212, 35693, 36171, 36647, 37119, 37589, 38056, 38521, 38982, 39440, 39895, 40347, 40797, 41243, 41686, 42125 };
static int _cos65536[161] = { 50203, 50569, 50931, 51289, 51643, 51993, 52339, 52681, 53019, 53353, 53683, 54009, 54331, 54649, 54963, 55272, 55577, 55878, 56175, 56467, 56755, 57039, 57319, 57594, 57864, 58131, 58393, 58650, 58903, 59151, 59395, 59635, 59870, 60100, 60326, 60547, 60763, 60975, 61183, 61385, 61583, 61776, 61965, 62149, 62328, 62502, 62672, 62837, 62997, 63152, 63302, 63448, 63589, 63725, 63856, 63982, 64103, 64220, 64331, 64438, 64540, 64637, 64729, 64816, 64898, 64975, 65047, 65114, 65176, 65234, 65286, 65333, 65376, 65413, 65446, 65473, 65496, 65513, 65526, 65533, 65536, 65533, 65526, 65513, 65496, 65473, 65446, 65413, 65376, 65333, 65286, 65234, 65176, 65114, 65047, 64975, 64898, 64816, 64729, 64637, 64540, 64438, 64331, 64220, 64103, 63982, 63856, 63725, 63589, 63448, 63302, 63152, 62997, 62837, 62672, 62502, 62328, 62149, 61965, 61776, 61583, 61385, 61183, 60975, 60763, 60547, 60326, 60100, 59870, 59635, 59395, 59151, 58903, 58650, 58393, 58131, 57864, 57594, 57319, 57039, 56755, 56467, 56175, 55878, 55577, 55272, 54963, 54649, 54331, 54009, 53683, 53353, 53019, 52681, 52339, 51993, 51643, 51289, 50931, 50569, 50203 };
static int _invertSin65536[161] = { 42125, 41686, 41243, 40797, 40347, 39895, 39440, 38982, 38521, 38056, 37589, 37119, 36647, 36171, 35693, 35212, 34728, 34242, 33753, 33262, 32767, 32271, 31772, 31271, 30767, 30261, 29752, 29242, 28729, 28213, 27696, 27177, 26655, 26132, 25606, 25079, 24550, 24019, 23486, 22951, 22414, 21876, 21336, 20794, 20251, 19707, 19160, 18613, 18064, 17513, 16961, 16408, 15854, 15299, 14742, 14184, 13625, 13065, 12504, 11942, 11380, 10816, 10252, 9686, 9120, 8554, 7986, 7418, 6850, 6281, 5711, 5141, 4571, 4000, 3429, 2858, 2287, 1715, 1143, 571, 0, -571, -1143, -1715, -2287, -2858, -3429, -4000, -4571, -5141, -5711, -6281, -6850, -7418, -7986, -8554, -9120, -9686, -10252, -10816, -11380, -11942, -12504, -13065, -13625, -14184, -14742, -15299, -15854, -16408, -16961, -17513, -18064, -18613, -19160, -19707, -20251, -20794, -21336, -21876, -22414, -22951, -23486, -24019, -24550, -25079, -25606, -26132, -26655, -27177, -27696, -28213, -28729, -29242, -29752, -30261, -30767, -31271, -31772, -32271, -32767, -33262, -33753, -34242, -34728, -35212, -35693, -36171, -36647, -37119, -37589, -38056, -38521, -38982, -39440, -39895, -40347, -40797, -41243, -41686, -42125 };
static int _invertCos65536[161] = { 50203, 50569, 50931, 51289, 51643, 51993, 52339, 52681, 53019, 53353, 53683, 54009, 54331, 54649, 54963, 55272, 55577, 55878, 56175, 56467, 56755, 57039, 57319, 57594, 57864, 58131, 58393, 58650, 58903, 59151, 59395, 59635, 59870, 60100, 60326, 60547, 60763, 60975, 61183, 61385, 61583, 61776, 61965, 62149, 62328, 62502, 62672, 62837, 62997, 63152, 63302, 63448, 63589, 63725, 63856, 63982, 64103, 64220, 64331, 64438, 64540, 64637, 64729, 64816, 64898, 64975, 65047, 65114, 65176, 65234, 65286, 65333, 65376, 65413, 65446, 65473, 65496, 65513, 65526, 65533, 65536, 65533, 65526, 65513, 65496, 65473, 65446, 65413, 65376, 65333, 65286, 65234, 65176, 65114, 65047, 64975, 64898, 64816, 64729, 64637, 64540, 64438, 64331, 64220, 64103, 63982, 63856, 63725, 63589, 63448, 63302, 63152, 62997, 62837, 62672, 62502, 62328, 62149, 61965, 61776, 61583, 61385, 61183, 60975, 60763, 60547, 60326, 60100, 59870, 59635, 59395, 59151, 58903, 58650, 58393, 58131, 57864, 57594, 57319, 57039, 56755, 56467, 56175, 55878, 55577, 55272, 54963, 54649, 54331, 54009, 53683, 53353, 53019, 52681, 52339, 51993, 51643, 51289, 50931, 50569, 50203 };

void RotateBinGradImage(unsigned char *inBinGradImage, int inWidth, int inHeight, int angle, unsigned char *outBinGradImage, int *outWidth, int *outHeight)
{
	angle += 80;
	int ltx = (-(inWidth >> 1) *_cos65536[angle] + (inHeight >> 1) *_sin65536[angle]) >> 16;
	int lty = ((inWidth >> 1) *_sin65536[angle] + (inHeight >> 1) *_cos65536[angle]) >> 16;

	int rtx = ((inWidth >> 1) *_cos65536[angle] + (inHeight >> 1) *_sin65536[angle]) >> 16;
	int rty = (-(inWidth >> 1) *_sin65536[angle] + (inHeight >> 1) *_cos65536[angle]) >> 16;

	int lbx = (-(inWidth >> 1) *_cos65536[angle] - (inHeight >> 1) *_sin65536[angle]) >> 16;
	int lby = ((inWidth >> 1) *_sin65536[angle] - (inHeight >> 1) *_cos65536[angle]) >> 16;

	int rbx = ((inWidth >> 1) *_cos65536[angle] - (inHeight >> 1) *_sin65536[angle]) >> 16;
	int rby = (-(inWidth >> 1) *_sin65536[angle] - (inHeight >> 1) *_cos65536[angle]) >> 16;

	*outWidth = abs(rbx - ltx)>abs(rtx - lbx) ? abs(rbx - ltx):abs(rtx - lbx);
	*outHeight = abs(rby - lty)>abs(rty - lby) ? abs(rby - lty):abs(rty - lby);

	int halfInWidth = (inWidth) >> 1;
	int halfInHeight = (inHeight) >> 1;
	int halfOutWidth = (*outWidth) >> 1;
	int halfOutHeight = (*outHeight) >> 1;
	for (int j = 0; j < *outHeight; j++)
	{
		for (int i = 0; i < *outWidth; i++)
		{
			int dx = ((i - halfOutWidth) *_invertCos65536[angle] + (j - halfOutHeight) *_invertSin65536[angle]) >> 16;
			int dy = ((-(i - halfOutWidth)) *_invertSin65536[angle] + (j - halfOutHeight) *_invertCos65536[angle]) >> 16;

			int x = dx + halfInWidth;
			int y = dy + halfInHeight;

			if (x <0 || x >inWidth - 1 || y <0 || y >inHeight - 1)
			{
				outBinGradImage[j *(*outWidth) + i] = 0;
			}
			else
			{
				outBinGradImage[j *(*outWidth) + i] = inBinGradImage[y *inWidth + x];
			}
		}
	}
}


int HorizonAngle(unsigned char *inBinGradImage, int width, int height, unsigned char *inGradBuffer, unsigned int *inHistBuffer)
{
	int rotWidth = 0;
	int rotHeight = 0;

	int resAngle = 0;
	int maxHist = 0;

	for (int angle = -80; angle <= 80; angle++)
	{
		RotateBinGradImage(inBinGradImage, width, height, angle, inGradBuffer, &rotWidth, &rotHeight);

		memset(inHistBuffer, 0, rotHeight *sizeof(unsigned int));

		for (int j = 0; j < rotHeight; j++)
		{
			int count = 0;
			for (int i = 0; i < rotWidth; i++)
			{
				if (inGradBuffer[j *rotWidth + i])
				{
					count++;
				}
			}
			inHistBuffer[j] = count;
		}

		//ÕÒËÄžö×îŽóµÄ
		int sum = 0;
		int maxIdx = 0;
		for (int i = 0; i < 4; i++)
		{
			int max = inHistBuffer[0];
			for (int k = 1; k <rotHeight; k++)
			{
				if (inHistBuffer[k] >max)
				{
					maxIdx = k;
					max = inHistBuffer[k];
				}
			}
			inHistBuffer[maxIdx] = 0;
			sum += max;

		}

		if (sum > maxHist)
		{
			resAngle = angle;
			maxHist = sum;
		}
	}

	return resAngle;
}

void GetRotatedImageSize(unsigned char *inputRGBImage, int inputRGBImageWidth, int inputRGBImageHeight,
	int *outputRGBImageWidth, int *outputRGBImageHeight, int *angle)
{
	

	//
	int an = *angle + 80;
	int ltx = (-(inputRGBImageWidth >> 1) *_cos65536[an] + (inputRGBImageHeight >> 1) *_sin65536[an]) >> 16;
	int lty = ((inputRGBImageWidth >> 1) *_sin65536[an] + (inputRGBImageHeight >> 1) *_cos65536[an]) >> 16;

	int rtx = ((inputRGBImageWidth >> 1) *_cos65536[an] + (inputRGBImageHeight >> 1) *_sin65536[an]) >> 16;
	int rty = (-(inputRGBImageWidth >> 1) *_sin65536[an] + (inputRGBImageHeight >> 1) *_cos65536[an]) >> 16;

	int lbx = (-(inputRGBImageWidth >> 1) *_cos65536[an] - (inputRGBImageHeight >> 1) *_sin65536[an]) >> 16;
	int lby = ((inputRGBImageWidth >> 1) *_sin65536[an] - (inputRGBImageHeight >> 1) *_cos65536[an]) >> 16;

	int rbx = ((inputRGBImageWidth >> 1) *_cos65536[an] - (inputRGBImageHeight >> 1) *_sin65536[an]) >> 16;
	int rby = (-(inputRGBImageWidth >> 1) *_sin65536[an] - (inputRGBImageHeight >> 1) *_cos65536[an]) >> 16;

	*outputRGBImageWidth  = std::max(abs(rbx - ltx), abs(rtx - lbx));
	*outputRGBImageHeight = std::max(abs(rby - lty), abs(rty - lby));
}


/*void GetRotatedImage(unsigned char *inputRGBImage, int inputRGBImageWidth, int inputRGBImageHeight,
	unsigned char *outputRGBImage, int outputRGBImageWidth, int outputRGBImageHeight,
	int angle)
{
	cv::Mat image(inputRGBImageHeight, inputRGBImageWidth, CV_8UC3, inputRGBImage);
	
}
*/
void RotateImage(Mat& src, Mat& des, int rotAngle)
{
	//float angle1=89;
	if (rotAngle == 0)
	{
		des = src.clone();
		return;
	}

	double angle = rotAngle;
	cv::Point2f center(src.cols / 2, src.rows / 2);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);
	cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();

	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	
	cv::warpAffine(src, des, rot, bbox.size());
	
	//cv::imwrite("c:/dst.jpg", dst);
	//cv::waitKey(0);

	//旋转图像是怎么旋转的?

}
void RotateByCenter(cv::Mat& src, cv::Mat& dst, float angle)
{
	angle = angle * CV_PI / 180.;
	cv::Mat tmp;
	int maxBorder = (int)(std::max(src.cols, src.rows) * 1.414); //即为sqrt(2)*max
	int dx = (maxBorder - src.cols) / 2;
	int dy = (maxBorder - src.rows) / 2;
	cv::copyMakeBorder(src, tmp, dy, dy, dx, dx, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));

	//旋转
	cv::Point2f center((float)(tmp.cols / 2), (float)(tmp.rows / 2));
	cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle / CV_PI * 180.0, 1.0);//求得旋转矩阵
	cv::warpAffine(tmp, tmp, affine_matrix, tmp.size());

	//计算图像旋转之后包含图像的最大的矩形
	float sinVal = std::abs(sin(angle));
	float cosVal = std::abs(cos(angle));
	cv::Size targetSize((int)(src.cols * cosVal + src.rows * sinVal),
		(int)(src.cols * sinVal + src.rows * cosVal));

	//剪掉多余边框
	int x = (tmp.cols - targetSize.width) / 2;
	int y = (tmp.rows - targetSize.height) / 2;
	cv::Rect rect(x, y, targetSize.width, targetSize.height);
	dst = cv::Mat(tmp, rect);
}

//2020090-kang自动旋转角度修改 type 1老旋转 2新旋转
void AutoRotateImageOCR(cv::Mat& src, cv::Mat& dst, int& angleOut, int type)
{
	if (type == 1)
	{
		cv::Mat grayImage;
		if (src.channels() == 1)
			grayImage = src.clone();
		else
			cv::cvtColor(src, grayImage, CV_BGR2GRAY);
		

		//resize, µÈ±ÈËõ·Å£¬¿í¶ÈËõµœ400
		cv::Mat smallImage;
		const int smallWidth = 400;
		int smallHeight = grayImage.rows *smallWidth / grayImage.cols;
		cv::resize(grayImage, smallImage, cv::Size(smallWidth, smallHeight));

		//clip 
		int minSize = std::min(smallImage.rows, smallImage.cols);
		int clipSize = minSize / 10;

		cv::Rect rect(clipSize, clipSize, smallImage.cols - 2 * clipSize, smallImage.rows - 2 * clipSize);
		cv::Mat clipImage = smallImage(rect).clone();

		//
		cv::Mat gradBinMat = clipImage.clone();
		int maxSqrtLen = sqrt(clipImage.rows * clipImage.rows + clipImage.cols * clipImage.cols) + 1;
		cv::Mat rotateBinMat(maxSqrtLen, maxSqrtLen, CV_8UC1);

		unsigned int *uintBuf = new unsigned int[maxSqrtLen];
		GradYBinary(clipImage.data, clipImage.cols, clipImage.rows, gradBinMat.data);
		angleOut = HorizonAngle(gradBinMat.data, clipImage.cols, clipImage.rows, rotateBinMat.data, uintBuf);
		angleOut = angleOut / 2;
		delete[]uintBuf;

	}
	else if (type == 2)
	{  
			float angle = 0.;
			int maxHistVal = 0;

			if (src.cols >800 && src.rows >800)
				src = src(cv::Rect(200, 200, src.cols-400, src.rows-400));
			cv::Mat resizedImg;
			cv::resize(src, resizedImg, cv::Size(src.cols / 4, src.rows / 4));

			for (float k = -10.; k <= 10.; k += 0.5)
			{
				cv::Mat rotImg;
				RotateByCenter(resizedImg, rotImg, k);

				cv::Mat gray;

				if(rotImg.channels() == 1)
					gray = rotImg.clone();
				else
					cv::cvtColor(rotImg, gray, cv::COLOR_RGB2GRAY);

				cv::Mat binary;
				cv::threshold(gray, binary, 100, 255, cv::THRESH_OTSU);

				//std::vector<int> hist(binary.cols, 0);
				std::vector<int> hist(binary.rows, 0);

				for (int j = 0; j < binary.rows; j++)
				{
					for (int i = 0; i < binary.cols; i++)
					{
						int val = binary.at<uchar>(j, i);
						if (val == 0)
						{
							//hist[i] ++;
							hist[j] ++;
						}
					}
				}

				//找四个最大的
				int sum = 0;
				int maxIdx = 0;
				for (int i = 0; i < 20; i++)
				{
					int max = hist[0];
					//for (int j = 1; j < binary.cols; j++)
					for (int j = 1; j < binary.rows; j++)
					{
						if (hist[j] > max)
						{
							maxIdx = j;
							max = hist[j];
						}
					}
					hist[maxIdx] = 0;
					sum += max;
				}

				if (sum > maxHistVal)
				{
					angle = k;
					maxHistVal = sum;

					//printf("angle =%f\n", angle);
				}
			}

			if (fabs(angle) > 5)
				angle = 0;

			angleOut = angle;

			//RotateByCenter(src, dst, angle);
		
	}
	
}

//void AutoRotateImageOCR(cv::Mat inputRGBImage, cv::Mat &outputRGBImage, int &angle)
//{
//	cv::Mat grayImage;
//	cv::cvtColor(inputRGBImage, grayImage, CV_BGR2GRAY);
//
//	//resize, µÈ±ÈËõ·Å£¬¿í¶ÈËõµœ400
//	cv::Mat smallImage;
//	const int smallWidth = 400;
//	int smallHeight = grayImage.rows *smallWidth / grayImage.cols;
//	cv::resize(grayImage, smallImage, cv::Size(smallWidth, smallHeight));
//
//	//clip 
//	int minSize = std::min(smallImage.rows, smallImage.cols);
//	int clipSize = minSize / 10;
//
//	cv::Rect rect(clipSize, clipSize, smallImage.cols - 2 * clipSize, smallImage.rows - 2 * clipSize);
//	cv::Mat clipImage = smallImage(rect).clone();
//
//	//
//	cv::Mat gradBinMat = clipImage.clone();
//	int maxSqrtLen = sqrt(clipImage.rows * clipImage.rows + clipImage.cols * clipImage.cols) + 1;
//	cv::Mat rotateBinMat(maxSqrtLen, maxSqrtLen, CV_8UC1);
//
//	unsigned int *uintBuf = new unsigned int[maxSqrtLen];
//	GradYBinary(clipImage.data, clipImage.cols, clipImage.rows, gradBinMat.data);
//	angle = HorizonAngle(gradBinMat.data, clipImage.cols, clipImage.rows, rotateBinMat.data, uintBuf);
//	angle = angle/2;
//	delete[]uintBuf;
//
//
////	float tureAngle = float(angle) / 2;
////	printf("angle =%d\n", angle);
////////cnt<<"++++++++++++++++++++++"<<endl;
//	//
//	/*cv::Mat rot_mat = cv::getRotationMatrix2D(cv::Point2f(inputRGBImage.rows / 2.0, inputRGBImage.cols / 2.0), tureAngle, 1.0);
//
//	double angle2 = tureAngle  * CV_PI / 180.; // »¡¶È    
//	double a = sin(angle2), b = cos(angle2);
//	int width = inputRGBImage.cols;
//	int height = inputRGBImage.rows;
//	int width_rotate = int(height * fabs(a) + width * fabs(b)) +1;
//	int height_rotate = int(width * fabs(a) + height * fabs(b)) +1;
//*/
//	
//
//	//RotateImg2(inputRGBImage,outputRGBImage,cv::Point2f(inputRGBImage.cols / 2.0, inputRGBImage.rows / 2.0),tureAngle);
//	//angle=angle/2.0;
//
//}

bool uChar2cvMat(unsigned char * BGRInImage, cv::Mat & OutImage, int InW, int InH)
{
	try
	{
		OutImage.create(InH, InW, CV_8UC3);
		for (int i = 0; i < InH; i++)
		{
			for (int j = 0; j < InW; j++)
			{
				unsigned char* pixel = OutImage.data + OutImage.step[0] * (i)+OutImage.step[1] * (j);
				pixel[0] = BGRInImage[i*InW * 3 + j * 3 + 0];
				pixel[1] = BGRInImage[i*InW * 3 + j * 3 + 1];
				pixel[2] = BGRInImage[i*InW * 3 + j * 3 + 2];
			}
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

//===================接口函数==========================================

int GetRotatedImageWithPathOCR(const char * inputPath,const char *outputPath, int &angle)
{
	char configPath[1024];

	cv::Mat image = cv::imread(inputPath);
	if(image.empty())
		return RES_READ_OCR_IMAGE_ERROR;
	cv::Mat outputRGBImage;
	
	//从配置文件中读取是否要先旋转90度
	
	_getcwd(configPath, 1024);
	strcat(configPath,"\\config.txt");
	////cnt << configPath << endl;

//	printf("config path2222222222:%s\n",configPath);

	int preRotateAngle = 0;
	try
	{
		//const char ConfigFile[]= "config.txt";   
		//printf("config path2222222222:%s\n",configPath);
		Config configSettings(configPath);
		preRotateAngle = configSettings.Read("preRotate", 0);
	}
	catch (...)
	{
		printf("can't find config.txt\n");
	}
	////cnt << preRotateAngle << endl;

	//xuanz 90
	cv::Mat rotate90Img = image.clone();
	if(preRotateAngle!=0)
		RotateImage(image,rotate90Img,preRotateAngle);
	
	//预旋转完了再让它自动旋转
	//angle = 2;
	////cnt << angle << endl;
	AutoRotateImageOCR(rotate90Img,outputRGBImage,angle,2);
	if(preRotateAngle!=0)
		angle += preRotateAngle;

	//printf("angle++++++++++++++ %d\n", angle);//<<endl;
	RotateImage(image,outputRGBImage,angle);

//	printf("%s\n", outputPath);//<<endl;
	cv::imwrite(outputPath, outputRGBImage);
	return RES_OK;
}

int GetRotatedImage(unsigned char *RGBImage, int imageWidth, int imageHeight,
	unsigned char *&RGBOutImage, int &imageOutWidth, 
	int &imageOutHeight,float *paraList)
{
	cv::Mat input;
	if(!uChar2cvMat(RGBImage,input,imageWidth,imageHeight) && input.empty())
		return 0;
	cv::Mat outputRGBImage;
	int angle;
	AutoRotateImageOCR(input,outputRGBImage,angle,1);
	imageOutWidth = outputRGBImage.cols;
	imageOutHeight = outputRGBImage.rows;
	RGBOutImage = new unsigned char[imageOutWidth * imageOutHeight * 3];
	memcpy(RGBOutImage,outputRGBImage.data,imageOutWidth * imageOutHeight * 3);
	return angle;
	
}
int GetRotatedImageAngle(unsigned char *RGBImage, int imageWidth, int imageHeight)
{
	cv::Mat input;
	if(!uChar2cvMat(RGBImage,input,imageWidth,imageHeight) && input.empty())
		return 0;
	int angle;
	cv::Mat outputRGBImage;
	AutoRotateImageOCR(input,outputRGBImage,angle,1);
	return angle;
}
std::string getRandomName(int len=16)
{
	std::string res = "";
	srand(time(NULL));
	for (int i = 0; i < len; i++)
	{
		int r = rand() % 26;
		res += (r + 'a');
	}
	res+=".jpg";
	return res;
}

int AAAA()
{
	return 2;
}
int GetRecogResultIn(const char *ocrUrl, const char * tmpFileSavePath, const char * inputPath, char ** strJson, int *len)
{
	int angle;
	//char tmpsavePath[128]={0};

	int res = GetRotatedImageWithPathOCR(inputPath, tmpFileSavePath, angle);
	
	return angle;
}
int ReleaseResultMemoryIn(char * p)
{
	if (p)
	{
		printf("ReleaseResultMemory success\n");
		delete[]p;
		p = nullptr;
		return 0;
	}
	printf("ReleaseResultMemory error\n");
	return -1;
}


//int GetRecogResultForList(const char *ocrUrl, const char * tmpFileSavePath, const char * inputPath, char ** strJson, char ** strRecogJson, int *len, int pageID)
//{
//	int angle;
//	char tmpsavePath[128] = { 0 };
//
//	//full text
//	int res = GetRecogResultIn(ocrUrl, tmpFileSavePath, inputPath, strJson, len);
//
//	//list
//	CExtractInfo extractInfo;
//	extractInfo.m_strRecogJson = *strJson;
//	extractInfo.angleRot = angle;
//	extractInfo.PageID = pageID;
//	extractInfo.ExtractInfo(inputPath, "211.138.112.184", "/ocr/api/img/recognize", 9556);
//
//	string strJsonlist;
//	strJsonlist = extractInfo.FormulateJasonList();
//
//	*strRecogJson = new char[strJsonlist.length() - 2];
//	strJsonlist.copy(*strRecogJson, strJsonlist.length() - 1, 1);
//	*(*strRecogJson + strJsonlist.length() - 3) = '\0'; //需手动加结束符
//
//	//////cnt<<strJson2<<endl;
//	return res;
//}

int DoOCR3(const char *szOcrUrl, const  char * imgPath, char * &pRecogRes, const int rotateAngle)
{
	//CURL *curl;
//	CURLcode res;

	char *pos1, *pos2;

	////cnt << "ddddd" << endl;
	/*
	struct curl_slist *http_header = NULL;
	curl = curl_easy_init();
	if (!curl)
	{
	return RES_CURL_INIT_ERROR;
	}
	struct curl_slist *headers = NULL; // init to NULL is important
	headers = curl_slist_append(headers, "application/x-www-formurlencoded");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POST, 1); //设置问非0表示本次操作为post
	curl_easy_setopt(curl, CURLOPT_URL, szOcrUrl); //url地址
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTFIELDS); //post参数

	//==============================================================================================
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);//设置为1说明告诉库准备和执行一个上传操作
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, &read_data);//可通过 CURL_READFUNC_PAUSE 暂停
	FILE * readfp;
	if ((readfp = fopen(imgPath, "rb")) == NULL)
	{
	curl_easy_cleanup(curl);

	return RES_READ_OCR_IMAGE_ERROR;
	}
	//获取文件长度
	fseek(readfp, 0, SEEK_END);
	long file_size = ftell(readfp);
	rewind(readfp);
	curl_easy_setopt(curl, CURLOPT_READDATA, readfp);
	//========================================================================================

	//curl_easy_setopt(curl, CURLOPT_HEADER, 1); //将响应头信息和相应体一起传给write_data
	//char *pRecogRes;
	try
	{
	pRecogRes = new char[file_size*2];
	memset(pRecogRes, '\0', file_size*2);
	}
	catch (bad_alloc bd)
	{
	curl_easy_cleanup(curl);

	return RES_ALLOC_RES_MEMORY_ERROR;
	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //对返回的数据进行操作的函数地址
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, pRecogRes); //这是write_data的第四个参数值
	if(!pRecogRes)
	return RES_CURL_RETURN_NULL;
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1); //打印调试信息

	res = curl_easy_perform(curl);//执行操作

	if (res != CURLE_OK)
	{

	return RES_CURL_PERFORM_ERROR ;
	}
	else
	{
	//替换base64字符串
	pos1 = strstr(pRecogRes, "\"imgData");
	pos2 = strstr(pRecogRes, "\"time_cost");

	if (pos1 != NULL && pos2 !=NULL)
	{
	printf("with base64\n");// << endl;
	strcpy(pos1, pos2);
	}
	else
	printf("without base64\n");

	AddAngleToJson(pRecogRes, rotateAngle);

	////cnt<<pRecogRes<<endl;

	}
	curl_easy_cleanup(curl);

	fclose(readfp);
	//delete[]pRecogRes;
	*/
	return 1;
}
