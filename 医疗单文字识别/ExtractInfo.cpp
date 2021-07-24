
#include "stdafx.h"

#include "ExtractInfo.h"
#include <iostream>
using namespace std;

#include "KMeans.h"
#include <time.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//#include <regex>
#include <iomanip>
#if defined(_WIN32)
#include <direct.h>
#include "StringOperator.h"
#endif

//#include "reader.h"
//#include "value.h"
//#include "json.h"

//#include <algorithm>
//#define PRINT_ORIGIN_RES //是否输出原始识别项
//#define PRINT_CUT_RES

string CExtractInfo::PointToSting(int point[])
{
	char c1[8];
	sprintf(c1, "%d", point[0]);
	char c2[8];
	sprintf(c2, "%d", point[1]);
	char c3[8];
	sprintf(c3, "%d", point[2]);
	char c4[8];
	sprintf(c4, "%d", point[3]);
	string sc1 = c1;
	string sc2 = c2;
	string sc3 = c3;
	string sc4 = c4;
	string stilepos = sc1 + "," + sc2 + "," + sc3 + "," + sc4;
	return stilepos;
}



CExtractInfo::CExtractInfo()
{
	m_djsl = 1;

	TitleKeyWord title;
	//4: 项目 5：单价 6：金额 7：数量
	title.Flag = 4;
	title.Name = "项目名称";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "费用名称";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "费用明组";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "费电名竹";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "医嘱名称";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "直目";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "项日";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "项目";
	title.filterName.push_back("代码");
	title.filterName.push_back("编");
	TitleSet.push_back(title);

	/*title.Flag = 4;
	title.Name = "西药";
	TitleSet.push_back(title);*/

	title.Flag = 4;
	title.Name = "收费项目";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "收费项出";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "收费项日";
	TitleSet.push_back(title);
	//==================================
	//2.jpg
	title.Flag = 4;
	title.Name = "收费项吕";
	TitleSet.push_back(title);
	title.Flag = 6;
	title.Name = "金委";
	TitleSet.push_back(title);
	//====================================
	title.Flag = 4;
	title.Name = "名称";
	title.filterName.push_back("单");
	TitleSet.push_back(title);
	title.Flag = 4;
	title.Name = "收费顶目";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "细目";
	TitleSet.push_back(title);

	title.Flag = 4;
	title.Name = "细日";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "总费用";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "金额";
	title.filterName.clear();
	title.filterName.push_back("可报");
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "仓额";
	TitleSet.push_back(title);
	title.Flag = 6;
	title.Name = "总额";
	title.filterName.push_back("押金");
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "全额";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "收费金额";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "收费金销";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "费用";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "费用金";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "费用金额";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "可报金额";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "合计";
	TitleSet.push_back(title);

	//kang
	title.Flag = 6;
	title.Name = "总计";
	TitleSet.push_back(title);

	//kang
	title.Flag = 6;
	title.Name = "小计";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "总赞用";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "总爱用";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "费用小计";
	TitleSet.push_back(title);

	title.Flag = 6;
	title.Name = "全额";
	TitleSet.push_back(title);

	//title.Flag = 11;
	//title.Name = "名";
	//TitleSet.push_back(title);

	//title.Flag = 12;
	//title.Name = "称";
	//TitleSet.push_back(title);




	title.filterName.clear();
	title.Flag = 5;
	title.Name = "单价";
	TitleSet.push_back(title);

	title.Flag = 5;
	title.Name = "费用单价";
	TitleSet.push_back(title);

	title.Flag = 5;
	title.Name = "价格";
	TitleSet.push_back(title);

	title.Flag = 7;
	title.Name = "数量";
	TitleSet.push_back(title);
	title.Flag = 7;
	title.Name = "费用数量";
	TitleSet.push_back(title);
	title.Flag = 7;
	title.Name = "用量";
	TitleSet.push_back(title);



	//title.Flag = 7;
	//title.Name = "数量";
	//title.filterName.push_back("金额");
	//TitleSet.push_back(title);
	splitedStr.push_back(" ");
	splitedStr.push_back(":");
	//	splitedStr.push_back("|");
	/*
	//SettingConfig::getInstance()->getUserConfig();
	int res = sqlite3_open("E:\\post_name.db3", &m_pDB);
	if (res)
	{
	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_pDB));
	}
	else
	{
	fprintf(stderr, "Opened database successfully\n");
	}
	*/
	HosElem hosElem;

	hosElem.hosID = 0;
	hosElem.hosName = "武汉大学中南医院";
	HospitalSet.push_back(hosElem);

	hosElem.hosID = 1;
	hosElem.hosName = "余姚市人民医院";
	HospitalSet.push_back(hosElem);

	m_initjson = 0;
}

CExtractInfo::~CExtractInfo()
{
	//sqlite3_close(m_pDB);
}
int CExtractInfo::GetOcrVersion()
{
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(m_strRecogJson, root))
		return 1;
	Json::Value data;
	try
	{
		data = root["document"]["blocks"];
		if (data.isNull())
			return 1;
		else
			return 2;
	}
	catch (...)
	{
		return 1;
	}
}

void CExtractInfo::DecodeOneImageFromString(char *imgename, const  char *IPAddress, const char *ObjFun, int Port, int type)
{
	//WYP修改  添加获取OCR接口版本号	
	if (!m_reader.parse(m_strRecogJson, m_root))
		return;

	try
	{
		m_data = m_root["document"]["blocks"];
		if (m_data.isNull())
			m_ocrEngineType = 1;
		else
			m_ocrEngineType = 2;
	}
	catch (...)
	{
		return;
	}

	if (m_ocrEngineType == 2)
	{
		/*Json::Value strLinePos = strLineText["eachLinePos"];
		Json::Value strCharPos = root["charPos"];*/
		int k = 0;
		int s = m_data.size();
		for (int arrayIndex = 0; arrayIndex < m_data.size(); ++arrayIndex)
		{
			Json::Value linesObj, charObj;
			try
			{
				Json::Value::UInt index = 0;
				linesObj = m_data[arrayIndex]["lines"][index];
				charObj = linesObj["characters"];
			}
			catch (...)
			{
				//		AfxMessageBox("解析lines，characters失败");
				return;
			}
			string strText = linesObj["text"].asString();
			string strPos = "0,0,0,0";//strLinePos[arrayIndex].asString();

			//string charPos = strCharPos[0].asString();
			vector<PosOfChar> charPos;


			charPos.resize(charObj.size());
			k = 0;
			for (int i = 0; i < charObj.size(); i++)
			{
				Json::Value charPosObj;
				try
				{
					charPosObj = charObj[i]["position"]["bounding_box"];//.asString(); //strText1为识别的每个字符的位置{x,x,x,x}
				}
				catch (...)
				{
					//	AfxMessageBox("解析position.bounding_box失败");
					return;
				}
				//int s[4];
				//sscanf(strText1.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);

				charPos[i].pos[0] = charPosObj["left"].asInt();
				charPos[i].pos[1] = charPosObj["top"].asInt();
				charPos[i].pos[2] = charPosObj["width"].asInt();
				charPos[i].pos[3] = charPosObj["height"].asInt();
				//k++;
			}

			//	////cnt << strText << endl;
			if (type == 1)
				PushRecogResult(strText, strPos, charPos);
			else
				PushRecogResult2(strText, strPos, charPos);
		}
	}
	//===========此处是老版本的解析======================
	else if (m_ocrEngineType == 1)
	{
		Json::Value strScore = m_root["charScore"];
		//	////cnt << strScore << endl;
		Json::Value strLineText = m_root["lineText"];
		////cnt << strLineText << endl;
		Json::Value strLinePos = m_root["eachLinePos"];
		Json::Value strCharPos = m_root["charPos"];

		int k = 0;
		for (int arrayIndex = 0; arrayIndex < strLineText.size(); ++arrayIndex)
		{
			string strText = strLineText[arrayIndex].asString();
			string strPos = strLinePos[arrayIndex].asString();

			//string charPos = strCharPos[0].asString();
			vector<PosOfChar> charPos;

			Json::Value charPosItem = strCharPos[arrayIndex];
			charPos.resize(charPosItem.size());
			k = 0;
			for (int i = 0; i < charPosItem.size(); i++)
			{
				string strText1 = charPosItem[k].asString(); //strText1为识别的每个字符的位置{x,x,x,x}

				int s[4];
				//////cnt << strText1 << endl;
				sscanf(strText1.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);

				charPos[i].pos[0] = s[0]; charPos[i].pos[1] = s[1];
				charPos[i].pos[2] = s[2]; charPos[i].pos[3] = s[3];
				k++;
			}


			////cnt << strText << endl;
			if (type == 1)
				PushRecogResult(strText, strPos, charPos);
			else
				PushRecogResult2(strText, strPos, charPos);
		}

	}

	cv::imwrite("c:/1.jpg", this->InputImage);

	int te = 0;
	//WriteFile("E:\\res.txt");
}

void CExtractInfo::DecodeOneImage(char *imgename, const  char *IPAddress, const char *ObjFun, int Port, int type)//type=1按版本1，type=2 按版本2
{
	if (m_ocrEngineType == -1)
	{
		if (m_strRecogJson == "")
		{
			//CHttpFileEx httpFile;
			////http://192.168.1.4:8090/ocr/api/img/recognize 
			////httpFile.SetServerParam("192.168.1.4", "/ocr/api/img/recognize", 8090);
			//httpFile.SetServerParam(IPAddress, ObjFun, Port);
			//wchar_t*  pRecvData = NULL; //接收数据的指针               *
			//DWORD  dwRecvSize = 0;  //接收数据的大小                 *
			//DWORD  dwRetSend = 0;  //发送函数返回值                  *
			//int SendCode = HTTP_POST_UTF8; //                      *
			//int RecvCode = HTTP_POST_UTF8; //发送与接收的编码      *
			//dwRetSend = httpFile.PostPicDataMethod(imgename, "image", &pRecvData, dwRecvSize, SendCode, RecvCode);

			////char retCode[8] = { 0 };
			////sprintf(retCode, "%d", dwRetSend);
			//Json::Value outData;
			//if (dwRetSend != 100)
			//{
			//	return;
			//}

			////Json::Reader reader;
			////Json::Value root;
			//vector<string> textVec;
			//m_strRecogJson = CStringOperator::ws2s(pRecvData);
			////w////cnt  << pRecvData << endl;
			////printf("%ws\n", pRecvData.c_str());
			////string newStr = CStringOperator::WStringToString(pRecvData);
			//
			//int len =  ___mb_cur_max_func();
			//char *pmb = new char[len];
			//len = wcstombs(pmb, pRecvData, len);

			//auto pos1 = m_strRecogJson.find("\"imgData");
			//auto pos2 = m_strRecogJson.find("\"time_cost");
			////printf("%d,%d\n",pos1,pos2);
			//if (pos1 != string::npos && pos2 != string::npos)
			//	m_strRecogJson.replace(pos1, pos2 - pos1, "");
			//ofstream of2;
			//of2.open("D:\\res.txt");
			////of2.write(m_strRecogJson.c_str(), m_strRecogJson.length());
			//of2.write(m_strRecogJson.c_str(), m_strRecogJson.length());
			//of2.close();
			//////cnt << str << endl;
		}

		//WYP修改  添加获取OCR接口版本号	
		if (!m_reader.parse(m_strRecogJson, m_root))
			return;

		try
		{
			m_data = m_root["document"]["blocks"];
			if (m_data.isNull())
				m_ocrEngineType = 1;
			else
				m_ocrEngineType = 2;
		}
		catch (...)
		{
			return;
		}
	}

	//cv::imwrite("c:/1.jpg", this->InputImage);
	////cnt << m_ocrEngineType << endl;

	if (m_ocrEngineType == 2)
	{
		/*Json::Value strLinePos = strLineText["eachLinePos"];
		Json::Value strCharPos = root["charPos"];*/
		int k = 0;
		int s = m_data.size();
		////cnt << s << endl;
		for (int arrayIndex = 0; arrayIndex < m_data.size(); ++arrayIndex)
		{
			Json::Value linesObj, charObj;
			try
			{
				Json::Value::UInt index = 0;
				linesObj = m_data[arrayIndex]["lines"][index];
				charObj = linesObj["characters"];
			}
			catch (...)
			{
				//		AfxMessageBox("解析lines，characters失败");
				return;
			}
			string strText = linesObj["text"].asString();

#if defined(_WIN32)
			CStringOperator::UTF8ToAnsi(strText);
#endif
			string strPos = "0,0,0,0";//strLinePos[arrayIndex].asString();

			//string charPos = strCharPos[0].asString();
			vector<PosOfChar> charPos;


			charPos.resize(charObj.size());
			k = 0;
			for (int i = 0; i < charObj.size(); i++)
			{
				Json::Value charPosObj;
				try
				{
					charPosObj = charObj[i]["position"]["bounding_box"];//.asString(); //strText1为识别的每个字符的位置{x,x,x,x}
				}
				catch (...)
				{
					//	AfxMessageBox("解析position.bounding_box失败");
					return;
				}
				//int s[4];
				//////cnt << strText1 << endl;
				//sscanf(strText1.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);

				charPos[i].pos[0] = charPosObj["left"].asInt();
				charPos[i].pos[1] = charPosObj["top"].asInt();
				charPos[i].pos[2] = charPosObj["width"].asInt();
				charPos[i].pos[3] = charPosObj["height"].asInt();
				//k++;
			}

			//	////cnt << strText << endl;
			if (type == 1)
				PushRecogResult(strText, strPos, charPos);
			else
				PushRecogResult2(strText, strPos, charPos);
		}
	}
	//===========此处是老版本的解析======================
	else if (m_ocrEngineType == 1)
	{
		Json::Value strScore = m_root["charScore"];
		//	////cnt << strScore << endl;
		Json::Value strLineText = m_root["lineText"];
		////cnt << strLineText << endl;
		Json::Value strLinePos = m_root["eachLinePos"];
		Json::Value strCharPos = m_root["charPos"];

		int k = 0;
		for (int arrayIndex = 0; arrayIndex < strLineText.size(); ++arrayIndex)
		{
			string strText = strLineText[arrayIndex].asString();
			string strPos = strLinePos[arrayIndex].asString();

			//string charPos = strCharPos[0].asString();
			vector<PosOfChar> charPos;

			Json::Value charPosItem = strCharPos[arrayIndex];
			charPos.resize(charPosItem.size());
			k = 0;
			for (int i = 0; i < charPosItem.size(); i++)
			{
				string strText1 = charPosItem[k].asString(); //strText1为识别的每个字符的位置{x,x,x,x}

				int s[4];
				//////cnt << strText1 << endl;
				sscanf(strText1.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);

				charPos[i].pos[0] = s[0]; charPos[i].pos[1] = s[1];
				charPos[i].pos[2] = s[2]; charPos[i].pos[3] = s[3];
				k++;
			}


			////cnt << strText << endl;
			if (type == 1)
				PushRecogResult(strText, strPos, charPos);
			else
				PushRecogResult2(strText, strPos, charPos);
		}

	}

	//	cv::imwrite("c:/1.jpg", this->InputImage);

	int te = 0;
	//WriteFile("E:\\res.txt");
}




int CExtractInfo::OutputImage(char *outputfile, int drawtitle, int drawdetail)
{
	if (drawtitle == 1)
	{
		for (int i = 0; i < this->m_titlePos.size(); i++)
		{
			cv::Rect rect;

			rect = this->PosToTect(m_titlePos[i].NamePos);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect, CV_RGB(0, 255, 0), 3);
			rect = this->PosToTect(m_titlePos[i].PricePos);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect, CV_RGB(0, 255, 0), 3);
			rect = this->PosToTect(m_titlePos[i].NumPos);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect, CV_RGB(0, 255, 0), 3);
			rect = this->PosToTect(m_titlePos[i].DjPos);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect, CV_RGB(0, 255, 0), 3);
		}
	}

	if (drawdetail == 1)
	{
		for (int i = 0; i < this->FinalList.size(); i++)
		{
			cv::Rect rect1, rect2, rect3, rect4;

			rect1 = this->ArrayToTect(FinalList[i].Pos);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect1, CV_RGB(255, 0, 0));

			rect2 = this->ArrayToTect(&FinalList[i].Pos[4]);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect2, CV_RGB(255, 0, 0));

			rect3 = this->ArrayToTect(&FinalList[i].Pos[8]);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect3, CV_RGB(255, 0, 0));

			rect4 = this->ArrayToTect(&FinalList[i].Pos[12]);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect4, CV_RGB(255, 0, 0));

			cv::line(this->InputImage, cv::Point(rect1.x, rect1.y), cv::Point(rect2.x, rect2.y), CV_RGB(255, 0, 0));
		}
	}

	if (drawdetail == 1)
	{
		for (int i = 0; i < this->OrgRecoglList.size(); i++)
		{
			cv::Rect rect1;

			rect1 = this->ArrayToTect(OrgRecoglList[i].Pos);// >m_titlePos[i].NamePos.pos
			cv::rectangle(this->InputImage, rect1, CV_RGB(0, 0, 255));
		}
	}

	if (outputfile == NULL)
	{
		char outputpath[1024];
		sprintf(outputpath, "%s//export%s", this->openeddir.c_str(), this->openedfile.c_str());
		imwrite(outputpath, this->InputImage);
	}
	else
		imwrite(outputfile, this->InputImage);

	return 1;

}
/*取标题项*/
int CExtractInfo::getItemPos(RecogResult& itemName, RecogResult& itemPrice)
{
	if (mappedSet.empty())
	{
		return 0;
	}
	MappedID& mapId = *mappedSet.begin();
	itemName = OrgRecoglList[mapId.ID];
	itemPrice = OrgRecoglList[mapId.MatchedID];
	return mappedSet.size();
}
void CExtractInfo::ImgRotate(Mat& src, Mat& dst, double angle)
{
	Point2f center(src.cols / 2, src.rows / 2);
	Mat rot = cv::getRotationMatrix2D(center, angle, 1);
	Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();


	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;


	warpAffine(src, dst, rot, bbox.size());
	return;

}
string CExtractInfo::ExtractInfo(char *ColorImage, const char *IPAddress, const char *ObjFun, int Port/*, vector<TitlePos>& v_titlePos*/)
{

	clock_t start, finish01, finish02, finish03, finish1, finish2, finish3, finish4, finish5;
	double totaltime;
	start = clock();



	//如果未传入标题，则自动识别
	bool autoRecog = true;
	if (this->m_titlePos.size() > 0)
	{
		autoRecog = false;
		isManual = 1;
	}
	CandTitleList.clear();
	//m_titlePos.insert(m_titlePos.end(), v_titlePos.begin(), v_titlePos.end());


	Mat OrgoutputRGBImage;
	this->InputImage = imread(ColorImage);


	this->srcImg = this->InputImage.clone();

	int angle;
	auto ImgTmp = InputImage.clone();
	//	GetRotatedImage(ImgTmp, InputImage, angle);//自动旋转图片
	//	char *RotateImage = "D:\\AutoRotate.jpg";
	//	imwrite(RotateImage, InputImage);

	/*if (bAutoRotate)
	{
	int angle;

	OrgoutputRGBImage = InputImage.clone();

	GetRotatedImage(OrgoutputRGBImage, InputImage, angle);

	imwrite("c:\\12.jpg", InputImage);
	}*/

	string strResult = "---";

	string filename;

	filename = ColorImage;

	std::size_t found = filename.rfind("/");
	if (found == std::string::npos)
	{
		////cnt << "输入路径不合法" << endl;
		return strResult;
	}

	//openeddir = filename.substr(0, found);
	//openedfile = filename.substr(found, filename.length() - found);

	//TempImage = this->InputImage.clone();
	srcImg = this->InputImage.clone();
	//	////cnt << openeddir << "+++" << openedfile << endl;
	//识别图像
	aveYPosOfTitle = 0;
	NumofTitle = 0;

	//string m_strRecogJson;

	/*
	////HLW修改2 增加读取全文识别结果
	FILE* pf = fopen("c:/0910.txt", "rb");
	//FILE* pf = _wfopen(L"c:/111.txt", L"r,ccs=utf-8");
	char* szData = NULL;
	if (NULL != pf)
	{
	fseek(pf, 0, SEEK_END);
	long fLen = ftell(pf);
	szData = new char[fLen + 1];
	fseek(pf, 0, SEEK_SET);
	memset(szData, 0, fLen + 1);
	fread(szData, 1, fLen, pf);
	fclose(pf);

	m_strRecogJson = string(szData);
	delete[] szData;
	szData = NULL;
	}
	*/

	finish01 = clock();
#if defined(_WIN32)
	CStringOperator::AnsiToUTF8(m_strRecogJson);
#endif

	//先得到版本号（1：全文识别老版；2：全文识别新版；3：表格识别版；）
	m_ocrEngineType = -1;
	if (m_ocrEngineType == -1)
	{
		if (!m_reader.parse(m_strRecogJson, m_root))
			return "";

		try
		{
			m_data = m_root["table"];
			if (!m_data.isNull())
				m_ocrEngineType = 3;
			else
			{
				m_data = m_root["document"]["blocks"];
				if (m_data.isNull())
					m_ocrEngineType = 1;
				else
					m_ocrEngineType = 2;
			}
		}
		catch (...)
		{
			return "";
		}
	}

	if (m_ocrEngineType == 1 || m_ocrEngineType == 2)
	{
		if (autoRecog)
		{
			m_ocrEngineType = -1;
			HospitalID = -1;
			DecodeOneImage(ColorImage, IPAddress, ObjFun, Port, 1);
			////cnt << RecoglList.size() << endl;

			MergeForTitle();  //标题进行合并处理

			OrgRecoglList.reserve(RecoglList.size());
			OrgRecoglList.assign(RecoglList.begin(), RecoglList.end());

			//sort(OrgRecoglList.begin(), OrgRecoglList.end());//以x坐标排序

			//	imwrite("c:/2.jpg", this->InputImage);
			//	////cnt << "SIZE" << OrgRecoglList.size() << endl;
			GetMatchedNameAndTotal();//获取标题保存到mappedSet中

			////cnt << mappedSet.size() << endl;
			//	imwrite("c:/2.jpg", this->InputImage);

			if (mappedSet.size() > 0)
				AutoGetNamePricePos(); //根据标题确定左右边界位置

			//	cv::imwrite("c:/1.jpg", this->InputImage);
			m_nPriceCount = 0;

			ProcessForSpecialHos();  //对特殊医院进行处理

			if (this->m_titlePos.size() <= 0)
				return "";

			DecodeOneImage(ColorImage, IPAddress, ObjFun, Port, 2);
			PostTitlePos(ColorImage, IPAddress, ObjFun, Port);

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
				if (r.RResult.length() <= 2)
					return true;
				else
					return false;
			});
			v_title.erase(p, v_title.end());

			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());

			/*	for (int i = 0; i < v_price.size(); i++)
			{
			//cnt << v_price[i].RResult << "," << v_price[i].Pos[0] << endl;
			}*/
			/*sort(v_title.begin(), v_title.end(), [](const RecogResult& s1, const RecogResult& s2){
			if (s1.titleID != s2.titleID)
			return s1.titleID < s2.titleID;
			else if (fabs(s1.Pos[1] - s2.Pos[1])>10)
			return s1.Pos[1] < s2.Pos[1];
			else
			return s1.Pos[0] < s2.Pos[0];

			return s1.titleID < s2.titleID;

			});
			sort(v_price.begin(), v_price.end(), [](const RecogResult& s1, const RecogResult& s2){
			if (s1.titleID != s2.titleID)
			return s1.titleID < s2.titleID;
			else if (fabs(s1.Pos[1] - s2.Pos[1])>10)
			return s1.Pos[1] < s2.Pos[1];
			else
			return s1.Pos[0] < s2.Pos[0];
			});*/

			int d = 0;
			/*	auto ite = unique(v_title.begin(), v_title.end());
			v_title.erase(ite, v_title.end());

			auto ite2 = unique(v_price.begin(), v_price.end());
			v_price.erase(ite2, v_price.end());*/
			MatchResult();
			if (m_djsl == 1)
				AddDjAndNum();
			GetDetailList();
			//	OutputImage("D:\\temp.jpg");
			//}
		}
		else
		{
			m_ocrEngineType = -1;
			DecodeOneImage(ColorImage, IPAddress, ObjFun, Port, 2);

			//以y升序排
			//////cnt << "title" << v_title.size() << " ,price" << v_price.size() << endl;

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
				if (r.RResult.length() <= 2)
					return true;
				else
					return false;
			});
			v_title.erase(p, v_title.end());
			/*sort(v_title.begin(), v_title.end(), [](const RecogResult& s1, const RecogResult& s2){
			if (s1.titleID != s2.titleID)
			return s1.titleID < s2.titleID;
			else if (fabs(s1.Pos[1] - s2.Pos[1])>10)
			return s1.Pos[1] < s2.Pos[1];
			else
			return s1.Pos[0] < s2.Pos[0];

			});
			sort(v_price.begin(), v_price.end(), [](const RecogResult& s1, const RecogResult& s2){
			if (s1.titleID != s2.titleID)
			return s1.titleID < s2.titleID;
			else
			return s1.Pos[1] < s2.Pos[1];
			});*/

			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());
			MatchResult();

			AddDjAndNum();//根据标题确定左右边界位置

			GetDetailList();

		}
	}
	else
	{
		int res = GetRecogedTable();
		if (res == 0)
		{
			//无表格情况
			DecodeRecogedTable(1);

			MergeForTitle();  //标题进行合并处理

			OrgRecoglList.reserve(RecoglList.size());
			OrgRecoglList.assign(RecoglList.begin(), RecoglList.end());

			GetMatchedNameAndTotal();//获取标题保存到mappedSet中


			if (mappedSet.size() > 0)
				AutoGetNamePricePos(); //根据标题确定左右边界位置

			else
				SortByKMeans(10);

			m_nPriceCount = 0;

			ProcessForSpecialHos();  //对特殊医院进行处理

			if (this->m_titlePos.size() <= 0)
				return "";

			DecodeRecogedTable(2);
			PostTitlePos(ColorImage, IPAddress, ObjFun, Port);

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
				if (r.RResult.length() <= 2)
					return true;
				else
					return false;
			});
			v_title.erase(p, v_title.end());

			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());

			MatchResult();
			if (m_djsl == 1)
				AddDjAndNum();
			GetDetailList();
		}
		else if (res == 1)
		{
			//表格存在,拆分跨行问题
			DecodeTableAgain();

			//确定标题所在行，名称、金额所在列
			DetectColFlagOfTable();

			//校验每列标题对应的数据，与相邻数据进行比较
			VerifyEachColInfo();

			vector<int> isSplit;
			for (int i = 0; i < TableSet.size(); i++)
			{
				isSplit.push_back(0);
				for (int j = 0; j < TableSet[i].MatrixTable.size(); j++)//行
				{
					int flag = 0;
					vector<int> num;//某列每列跨行数量>2，先取整列数据，再同行匹配
					if (j > TableSet[i].Row)
					{
						for (int k = 0; k < TableSet[i].MatrixTable[j].size(); k++)//列
						{						
							if (j >= TableSet[i].MatrixTable[j][k].rowColumn[0] && j <= TableSet[i].MatrixTable[j][k].rowColumn[2])
							{
								if (k == TableSet[i].TitleCol[0] || k == TableSet[i].TitleCol[3])
								{
									if (TableSet[i].MatrixTable[j][k].allStrText.size()>2)										
									{
										//有一行表格跨行数>2且相等
										if (m_titlePos.size() > 0 && m_titlePos[i].NamePos.pos[1] < TableSet[i].MatrixTable[j][k].position[1])
											num.push_back(k);
									}
									if (num.size() == 2)
									{
										flag = 1;
										isSplit[i] = 1;
										break;
									}
								}
							}
						}
					}
					if (flag)
						break;
				}
			}

			//根据所确定行列，添加每组数据
			for (int i = 0; i < isSplit.size(); i++)
			{
				if (!isSplit[i])
				{
					//合并一行被识别成多个问题
					MergeTableByWholeRowCol(i, 1);
					MergeMultiColumn(i);

					MergeTitleCol(i, 1); //合并名称正常，明细被拆分成多列问题
					GetTableColumn(i);
				}
				else
				{					
					SplitTableForWholeCol(i);
				}

			}
			//合并项目名称换行
			MergeName();
			//数字处理、过滤
			JudgeRowTableType();
			//知道名称金额，计算单价或者数量
			GetNumDj();

			//得到FinalList
			GetDetailListTable();

			finish03 = clock();

			//部分有表格、部分无表格情况
			for (int i = 0; i < FinalList.size(); i++)
			{
				if (i == 0)
				{
					if (FinalList[i].Pos[1] >0 && FinalList[i].Pos[1] > this->InputImage.rows / 5)
					{
						int pos[4] = { 0, 0, (int)InputImage.cols, (int)FinalList[i].Pos[1]};
						RecognizeRegion(FinalList, m_titlePos, pos);
					}
				}
				else if (i == FinalList.size() - 1)
				{
					if (FinalList[i].Pos[1] > 0 && FinalList[i].Pos[1] < this->InputImage.rows / 5 * 4)
					{
						int pos[4] = { 0, (int)FinalList[i].Pos[1], (int)InputImage.cols, (int)(InputImage.rows - FinalList[i].Pos[1]) };
						RecognizeRegion(FinalList, m_titlePos, pos);
					}
				}
				else if (FinalList[i].Pos[1] > 0 && FinalList[i - 1].Pos[1] > 0 && (FinalList[i].Pos[1] - FinalList[i - 1].Pos[1]) > this->InputImage.rows / 5)
				{
					int pos[4] = { 0, (int)FinalList[i - 1].Pos[1], (int)InputImage.cols, (int)(FinalList[i].Pos[1] - FinalList[i - 1].Pos[1]) };
					RecognizeRegion(FinalList, m_titlePos, pos);
				}
			}

			if (this->FinalList.size() < 1)
			{
				int pos[4] = { 0, 0, InputImage.cols, InputImage.rows };
				m_titlePos.clear();
				RecognizeRegion(FinalList, m_titlePos, pos);
			}

			cout << "交叉解析耗时: " << (double)(finish03 - start) / CLOCKS_PER_SEC << endl;

			for (int i = 0; i<FinalList.size();i++)
			{
				if (FinalList[i].Name.size() > 80)
				{
					FinalList[i].Name = FinalList[i].Name.substr(0, 80);
				}
			}
			/*
			//识别结果为空
			if (this->FinalList.size() < 1)
			{
			//表格未识别出,按照无表格再次识别
			v_title.clear();
			v_num.clear();
			v_dj.clear();
			v_price.clear();

			v_title_table.clear();
			v_dj_table.clear();
			v_num_table.clear();
			v_price_table.clear();

			TableSet.clear();
			if (isManual == -1)
			{
			m_titlePos.clear();

			//无表格识别
			DecodeRecogedTable(1);

			MergeForTitle();  //标题进行合并处理

			OrgRecoglList.reserve(RecoglList.size());
			OrgRecoglList.assign(RecoglList.begin(), RecoglList.end());

			GetMatchedNameAndTotal();//获取标题保存到mappedSet中

			if (mappedSet.size() > 0)
			AutoGetNamePricePos(); //根据标题确定左右边界位置

			m_nPriceCount = 0;

			ProcessForSpecialHos();  //对特殊医院进行处理

			if (this->m_titlePos.size() <= 0)
			return "";


			DecodeRecogedTable(2);
			PostTitlePos(ColorImage, IPAddress, ObjFun, Port);

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
			if (r.RResult.length() <= 2)
			return true;
			else
			return false;
			});
			v_title.erase(p, v_title.end());

			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());

			MatchResult();
			if (m_djsl == 1)
			AddDjAndNum();

			GetDetailList();
			}
			else
			{
			//手工传入
			DecodeOneImage(ColorImage, IPAddress, ObjFun, Port, 2);


			DecodeRecogedTable(2);
			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
			if (r.RResult.length() <= 2)
			return true;
			else
			return false;
			});
			v_title.erase(p, v_title.end());

			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());

			MatchResult();


			AddDjAndNum();//根据标题确定左右边界位置

			GetDetailList();

			}
			}
			*/

		}

		else
		{
			;
		}
	}
	//return strResult;

	//mappedSet 为保存的是识别出的项目名称，金额在OrgRecogList中的Id


	//#endif
	//把识别结果写入到Jason中
	//Json::Value arrayObj;   // 构建对象
	//int pageIndex = 1;

	////ofstream outfile;//创建文件
	////outfile.open("c:\\20210126.txt",ios::app);

	for (auto i = 0; i < FinalList.size(); i++)
	{
		//Json::Value new_item;
		//if (FinalList.size()-i <= 20)
		cout << FinalList[i].Name << " ++ " << FinalList[i].TotalPrice << " ++ " << FinalList[i].Number << " ++ " << FinalList[i].UnitPrice << endl;
		//outfile << FinalList[i].Name << " ++ " << std::stoi(FinalList[i].TotalPrice) << " ++ " << std::stoi(FinalList[i].Number) << " ++ " << std::stoi(FinalList[i].UnitPrice) << endl;
		//cout << FinalList[i].Name << " ++ " << FinalList[i].TotalPrice << " ++ " << FinalList[i].Number << " ++ " << FinalList[i].UnitPrice << endl;
		//new_item["itemName"] = FinalList[i].Name;//项目名称
		//new_item["NameX"] = FinalList[i].Pos[0];
		//new_item["NameY"] = FinalList[i].Pos[1];
		//new_item["NameW"] = FinalList[i].Pos[2];
		//new_item["NameH"] = FinalList[i].Pos[3];
		//new_item["itemTotal"] = FinalList[i].TotalPrice;  //项目总价
		//new_item["TotalX"] = FinalList[i].Pos[4];
		//new_item["TotalY"] = FinalList[i].Pos[5];
		//new_item["TotalW"] = FinalList[i].Pos[6];
		//new_item["TotalH"] = FinalList[i].Pos[7];
		//new_item["itemNumber"] = FinalList[i].Number;  //药品数量
		//new_item["NumberX"] = FinalList[i].Pos[8];
		//new_item["NumberY"] = FinalList[i].Pos[9];
		//new_item["NumberW"] = FinalList[i].Pos[10];
		//new_item["NumberH"] = FinalList[i].Pos[11];
		//new_item["itemUnitPrice"] = FinalList[i].UnitPrice;  //药品单价
		//new_item["UnitPriceX"] = FinalList[i].Pos[12];
		//new_item["UnitPriceY"] = FinalList[i].Pos[13];
		//new_item["UnitPriceW"] = FinalList[i].Pos[14];
		//new_item["UnitPriceH"] = FinalList[i].Pos[15];

		//	arrayObj["data"].append(new_item); // 插入数组成员
		//arrayObj.append(new_item);
	}
	//outfile << endl;
	//outfile.close();

	//string jsonout = arrayObj.toStyledString();
	//	////cnt << jsonout << endl;
	//jsonout = AsciiToUtf8(jsonout);

	//string strJson = this->makeBillJson();

	//char szPath[1024];
	//memset(szPath, 0, 1024);
	//sprintf(szPath, "%s","c:\\testfile.txt");
	//FILE* pf = fopen(szPath, "wb");
	//if (NULL != pf)
	//{
	//	fwrite(strJson.c_str(), 1, strJson.length(), pf);
	//	fclose(pf);
	//}

	//return jsonout;

	return "";
}

void CExtractInfo::PostTitlePos(char *ColorImage, const char *IPAddress, const char *ObjFun, int Port)
{
	//如果识别的金额数目很少，则把金额标题的右边缘设到右边第一个黑点处（用于处理金额的识别项普遍在标题右边）
	if (v_title.size()*0.4 > v_price.size() && mappedSet.size() > 0)
	{
		//v_title.swap(vector<RecogResult>());
		//v_price.swap(vector<RecogResult>());
		v_title.clear();
		v_price.clear();

		cv::Mat thresholdedImg;
		cv::threshold(srcImg, thresholdedImg, 180, 255, CV_THRESH_BINARY);
		int priceId = mappedSet[0].MatchedID;
		//int leftX = FindNextBlackPt(thresholdedImg, OrgRecoglList[priceId].Pos[0] - 5, OrgRecoglList[priceId].Pos[1] + OrgRecoglList[priceId].Pos[3] / 2, 0);
		int rightX = FindNextBlackPt(thresholdedImg, OrgRecoglList[priceId].Pos[0] + OrgRecoglList[priceId].Pos[2] + 5, OrgRecoglList[priceId].Pos[1] + OrgRecoglList[priceId].Pos[3] / 2, 1);
		//m_titlePos[0].PricePos.pos[0] = leftX;
		m_titlePos[0].PricePos.pos[2] = rightX - m_titlePos[0].PricePos.pos[0] + 30;//TODO 目前只是有金额偏右的情况，所以加30后保证金额识别完整
		DecodeOneImage(ColorImage, IPAddress, ObjFun, Port, 2);
	}
	//当标题的识别项很少的时候则找项目名称的另一替代（陶县人民医院），
	else if (v_price.size()*0.4 > v_title.size() && mappedSet.size() > 0)
	{
		v_title.clear();
		v_price.clear();
		int nameId = mappedSet[0].ID;
		for (int i = 0; i < OrgRecoglList.size(); i++)
		{
			if (i != nameId && OrgRecoglList[i].Flag == 4 && IsSameLine(OrgRecoglList[nameId], OrgRecoglList[i]))
			{
				//m_titlePos.swap(vector<TitlePos>());//由于AutoGetNamePricePos中会重新添加标题，所以此处要先清空
				m_titlePos.clear();
				mappedSet[0].ID = i;
				AutoGetNamePricePos(); //根据标题确定左右边界位置
				DecodeOneImage(ColorImage, IPAddress, ObjFun, Port, 2);
				break;
			}
		}

	}
	//当识别出很多0的时候，则找同行其他金额的标题，如果没有，则把金额的标题项设为它的左侧。（用于处理切分了前面一列的很多0的情况）
	else
	{
		if (!mappedSet.size())
			return;
		//如果50%是0.00则查找下一项
		int zeroNum = 0;

		for (const auto & p : v_price)
		{
			if (p.RResult == "0.00" || p.RResult == "00.00")
			{
				zeroNum++;
			}
		}
		//	////cnt <<"0的个数"<< zeroNum << " , " << v_title.size() << endl;
		if (zeroNum > v_title.size()*0.5)//此处用v_title的size是因为当切分了前面一列后，v_price的size会比v_title大很多
		{
			v_title.clear();// .swap(vector<RecogResult>());
			v_price.clear(); //.swap(vector<RecogResult>());
			//////cnt << v_title.size() << "++++" << v_price.size();

			int nameId = mappedSet[0].MatchedID;
			for (int i = 0; i < OrgRecoglList.size(); i++)
			{
				if (i != nameId && OrgRecoglList[i].Flag == 6 && IsSameLine(OrgRecoglList[nameId], OrgRecoglList[i]))
				{
					m_titlePos.clear();// .swap(vector<TitlePos>());
					mappedSet[0].MatchedID = i;
					AutoGetNamePricePos(); //根据标题确定左右边界位置
					DecodeOneImage(ColorImage, IPAddress, ObjFun, Port, 2);
					return;
				}
			}
			int dst = OrgRecoglList[nameId].Pos[0] - m_titlePos[0].PricePos.pos[0];
			m_titlePos[0].PricePos.pos[0] = OrgRecoglList[nameId].Pos[0] - 5;
			m_titlePos[0].PricePos.pos[2] -= dst;
			DecodeOneImage(ColorImage, IPAddress, ObjFun, Port, 2);
			//mappedSet[0]
		}
	}
}
int CExtractInfo::FindNearRight(int OrgID, int& IsDot)
{
	float minDist = 100000;
	int minID = -1;

	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		if (i == OrgID)
			continue;

		if (OrgRecoglList[i].Pos[0] > OrgRecoglList[OrgID].Pos[0] + OrgRecoglList[OrgID].Pos[2] && abs(OrgRecoglList[i].Pos[1] - OrgRecoglList[OrgID].Pos[1]) < OrgRecoglList[OrgID].Pos[3] / 2)
		{
			float dist = fabs(OrgRecoglList[i].Pos[1] - OrgRecoglList[OrgID].Pos[1]) + fabs(OrgRecoglList[i].Pos[0] - OrgRecoglList[OrgID].Pos[0]);
			if (dist < minDist)
			{
				minDist = dist;
				minID = i;
			}
		}
	}

	if (minID != -1)
	{
		IsDot = 0;
		std::size_t found = OrgRecoglList[minID].RResult.rfind(".");
		if (found != std::string::npos)
		{
			IsDot = 1;
		}
	}
	return minID;
}

int CExtractInfo::FindNearLeft(int OrgID, int& IsDot)
{
	float minDist = 100000;
	int minID = -1;

	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		if (i == OrgID)
			continue;

		if (OrgRecoglList[i].Pos[0] + OrgRecoglList[i].Pos[2] < OrgRecoglList[OrgID].Pos[0] && abs(OrgRecoglList[i].Pos[1] - OrgRecoglList[OrgID].Pos[1]) < OrgRecoglList[OrgID].Pos[3] / 2)
		{
			float dist = fabs(OrgRecoglList[i].Pos[1] - OrgRecoglList[OrgID].Pos[1]) + fabs(OrgRecoglList[i].Pos[0] - OrgRecoglList[OrgID].Pos[0]);
			if (dist < minDist)
			{
				minDist = dist;
				minID = i;
			}
		}
	}

	if (minID != -1)
	{
		IsDot = 0;
		std::size_t found = OrgRecoglList[minID].RResult.rfind(".");
		if (found != std::string::npos)
		{
			IsDot = 1;
		}
	}
	return minID;
}


int CExtractInfo::FindMatchedUnitPrice(int nameID, int priceID, int mapID)
{
	float refX, refY;

	//	////cnt << this->OrgRecoglList[priceID].Pos[0] << "+++" << this->OrgRecoglList[nameID].Pos[0] << endl;
	refX = mappedSet[mapID].fPriceRate[0] * this->OrgRecoglList[priceID].Pos[0] + this->OrgRecoglList[nameID].Pos[0];
	refX = refX / (1 + mappedSet[mapID].fPriceRate[0]);
	refY = mappedSet[mapID].fPriceRate[1] * this->OrgRecoglList[priceID].Pos[1] + this->OrgRecoglList[nameID].Pos[1];
	refY = refY / (1 + mappedSet[mapID].fPriceRate[1]);
	//////cnt << refX << "+++" << refY << endl;

	float minDis[3] = { 100000, 10000, 10000 };
	int minID[3] = { 0 };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < this->OrgRecoglList.size(); j++)
		{
			if (i == 2)
			{
				if (minID[0] == j || minID[1] == j)
					continue;
			}
			if (i == 1)
			{
				if (minID[0] == j)
					continue;
			}

			int RefPriceID = mappedSet[mapID].MatchedID;
			float dis1 = fabs(refX - this->OrgRecoglList[j].Pos[0]) + fabs(refY - this->OrgRecoglList[j].Pos[1]);
			//	////cnt << dis1 << "+++" << minDis[0] << "+++" << minDis[1] << "+++" << minDis[2] << endl;
			if (dis1 < minDis[i])
			{
				minID[i] = j;
				minDis[i] = dis1;
			}

		}

		int test;

		test = 0;
	}

	//////cnt << minID[0] << "+++" << minID[1] << "+++" << minID[2] << endl;

	int FinalMinID = -1;
	float FinalMinDis = 100000000000;
	for (int i = 0; i < 3; i++)
	{


		float dis = fabs(this->OrgRecoglList[priceID].Pos[0] - this->OrgRecoglList[minID[i]].Pos[0]);
		if (dis < FinalMinDis
			&& fabs(this->OrgRecoglList[minID[i]].Pos[1] - this->OrgRecoglList[priceID].Pos[1]) < this->OrgRecoglList[priceID].Pos[3] / 2
			&& this->OrgRecoglList[minID[i]].Pos[0] < this->OrgRecoglList[priceID].Pos[0])
		{
			FinalMinID = minID[i];
			FinalMinDis = dis;
		}

	}

	if (FinalMinID != -1)
	{
		Rect rect;
		//	////cnt << minID[i] << endl;
		rect.x = this->OrgRecoglList[FinalMinID].Pos[0];
		rect.y = this->OrgRecoglList[FinalMinID].Pos[1];
		rect.width = this->OrgRecoglList[FinalMinID].Pos[2];
		rect.height = this->OrgRecoglList[FinalMinID].Pos[3];
		//	rectangle(this->InputImage, rect, CV_RGB(0, 255, 255));
	}
	//   imwrite("c:\\12.jpg", InputImage);

	//////cnt << this->OrgRecoglList[FinalMinID].Pos[0] << "+++" << this->OrgRecoglList[FinalMinID].Pos[1] << endl;

	return FinalMinID;
}

int CExtractInfo::PostTotalPrice(int curID)
{
	int refinedID = curID;

	int isDot;
	int minID = this->FindNearRight(curID, isDot);

	if (minID != -1)
	{
		float dis = fabs(this->OrgRecoglList[curID].Pos[1] - this->OrgRecoglList[minID].Pos[1]);

		if (isDot == 1 && dis < this->OrgRecoglList[curID].Pos[1] < this->OrgRecoglList[curID].Pos[3] / 2)
		{
			refinedID = minID;
			//		DrawRectangle(TempImage, curID);
			//		DrawRectangle(TempImage, minID);
			//	imwrite("c:\\123.jpg", TempImage);
		}
	}

	return refinedID;
}
int CExtractInfo::DecodeByNameAndTotal(int NameID, int TotalID, int curMapID)
{
	//初始化时的NameId为项目名称与总价的标题ID
	int nextNameID = NameID;
	int nextTotalID = TotalID;
	int lastNameID = NameID;
	int lastTotalID = TotalID;
	int err = 10;
	//	////cnt << OrgRecoglList[NameID].RResult << "___" << OrgRecoglList[TotalID].RResult<<endl;
	nextNameID = FindNearBottom(nextNameID);
	nextTotalID = FindNearBottom(nextTotalID);


	int nID = 0;


	while (nextNameID != -1 && nextTotalID != -1 && nID != -1)
	{
		//	////cnt << OrgRecoglList[nextNameID].RResult << "+++++" << OrgRecoglList[nextTotalID].RResult << endl;

		//近邻节点都存在
		/*nID
		1：ID需要下移，MatchedID保持不变
		2：ID保持不变，MatchedID需要下移
		*/
		nID = IsGoodPair(lastNameID, nextNameID, lastTotalID, nextTotalID);

		/*	std::size_t found = OrgRecoglList[nextNameID].RResult.rfind("治疗费");
		if (found != std::string::npos)
		{
		int s = 0;

		////cnt << OrgRecoglList[nextTotalID].RResult << endl;
		}*/
		/*if (nID != 0)
		////cnt << nID << ", " << OrgRecoglList[nextNameID].Pos[1] << ", " << OrgRecoglList[nextNameID].RResult << ", " <<
		OrgRecoglList[nextTotalID].Pos[1] << ", " << OrgRecoglList[nextTotalID].RResult << endl;*/

		if (nID == 0)
		{
			//////cnt << OrgRecoglList[nextNameID].RResult << "___" << OrgRecoglList[nextTotalID].RResult << endl;

			if (IsValidElem(nextNameID, nextTotalID) >= 0)//判断价格是否是数字
			{

				Point pt1, pt2;

				pt1.x = OrgRecoglList[nextNameID].Pos[0] + OrgRecoglList[nextNameID].Pos[2] / 2;
				pt1.y = OrgRecoglList[nextNameID].Pos[1] + OrgRecoglList[nextNameID].Pos[3] / 2;

				pt2.x = OrgRecoglList[nextTotalID].Pos[0] + OrgRecoglList[nextTotalID].Pos[2] / 2;
				pt2.y = OrgRecoglList[nextTotalID].Pos[1] + OrgRecoglList[nextTotalID].Pos[3] / 2;

				line(this->InputImage, pt1, pt2, CV_RGB(255, 0, 0));

				/*if (this->OrgRecoglList[nextNameID].RResult == "五淋化石丸")
				{
				////cnt <<"ismath" <<this->OrgRecoglList[nextNameID].IsMatched << endl;
				int t=0;
				}*/
				KeyWord keyWord;

				keyWord.Name = this->OrgRecoglList[nextNameID].RResult;
				memcpy(&keyWord.Pos[0], &this->OrgRecoglList[nextNameID].Pos[0], sizeof(float)* 4);

				//对金额列进行修正
				int nextTotalID2 = PostTotalPrice(nextTotalID);

				if (nextTotalID2 != nextTotalID && fabs(OrgRecoglList[TotalID].Pos[0] - OrgRecoglList[nextTotalID2].Pos[0]) < OrgRecoglList[nextTotalID2].Pos[2] / 2)
				{
					nextTotalID = nextTotalID2;
					//DrawRectangle(nextTotalID2);
					//DrawRectangle(nextTotalID);
				}

				lastNameID = nextNameID;
				lastTotalID = nextTotalID;

				/*	std::size_t found = OrgRecoglList[nextTotalID].RResult.rfind(":");
				if (found != std::string::npos)
				{
				////cnt << nextTotalID <<"+++"<< nextTotalID2 << endl;
				DrawRectangle(this->TempImage, nextTotalID);
				DrawRectangle(this->TempImage, nextTotalID2);
				///		imwrite("c:\\123.jpg", this->TempImage);
				}*/



				PostProcTotalPrice(this->OrgRecoglList[nextTotalID].RResult, keyWord.TotalPrice);
				memcpy(&keyWord.Pos[4], &this->OrgRecoglList[nextTotalID].Pos[0], sizeof(float)* 4);

				if (this->mappedSet[curMapID].UnitPriceID != -1)  //存在单价
				{
					int ID = this->FindMatchedUnitPrice(nextNameID, nextTotalID, curMapID);

					if (ID != -1)
					{
						keyWord.UnitPrice = this->OrgRecoglList[ID].RResult;
						memcpy(&keyWord.Pos[8], &this->OrgRecoglList[nextTotalID].Pos[0], sizeof(float)* 4);


						pt1.x = OrgRecoglList[ID].Pos[0];
						pt1.y = OrgRecoglList[ID].Pos[1];

						pt2.x = OrgRecoglList[ID].Pos[0] + OrgRecoglList[ID].Pos[2];
						pt2.y = OrgRecoglList[ID].Pos[1] + OrgRecoglList[ID].Pos[3];

						rectangle(this->InputImage, pt1, pt2, CV_RGB(255, 0, 0));

					}
				}

				if (this->OrgRecoglList[nextNameID].IsMatched == -1)
				{
					this->OrgRecoglList[nextNameID].IsMatched = 0;
					FinalList.push_back(keyWord);
					//	////cnt << keyWord.Name << "___" << keyWord.TotalPrice << endl;
					//ADD
					this->OrgRecoglList[nextTotalID].IsMatched = 0;
				}

			}

			nextNameID = FindNearBottom(nextNameID);
			nextTotalID = FindNearBottom(nextTotalID);
		}

		if (nID == 1)
		{
			nextNameID = FindNearBottom(nextNameID);
		}

		if (nID == 2)
		{
			nextTotalID = FindNearBottom(nextTotalID);
		}

	}
	//imwrite("c:\\1.jpg", InputImage);
	return 1;
}
void CExtractInfo::ResearchLoseItem()
{
	ResearchLostItemByPrice();
	ResearchLostItemByName();
}
#include<map>
void CExtractInfo::ResearchLostItemByPrice()
{
	//////cnt << "=====ResearchLostItemByPrice=====" << mappedSet.size() << endl;
	//vector<RecogResult> vec_nameID;

	//找出未匹配的价格
	for (int i = 0; i < mappedSet.size(); i++)
	{
		map<int, RecogResult>map_losePrice;
		//	vector<RecogResult> vec_priceID;


		int nextTotalID = mappedSet[i].MatchedID;
		int nID = 0;
		while (nextTotalID != -1 && nID != -1)
		{
			nextTotalID = FindNearBottom(nextTotalID);
			if (this->OrgRecoglList[nextTotalID].IsMatched == -1 && IsValidElem(0, nextTotalID) == 0)
			{
				map_losePrice.emplace(nextTotalID, OrgRecoglList[nextTotalID]);
				//vec_priceID.push_back(OrgRecoglList[nextTotalID]);
				//////cnt << "ID" << nextTotalID << "丢失的价格==>" << OrgRecoglList[nextTotalID].RResult << endl;
			}
		}

		int nameTitlePosY = OrgRecoglList[mappedSet[i].ID].Pos[1];
		int nameTitlePosX = OrgRecoglList[mappedSet[i].ID].Pos[0];

		for (auto &p : map_losePrice)
		{
			map<int, RecogResult> map_sameLine;
			int price_title_dst = fabs(p.second.Pos[1] - OrgRecoglList[mappedSet[i].MatchedID].Pos[1]);//当前待查找的丢失金额与标题之间的距离

			for (int j = 0; j<OrgRecoglList.size(); j++)
			{
				auto orgEle = OrgRecoglList[j];
				if (orgEle.Pos[1] - nameTitlePosY + orgEle.Pos[3] / 2.0 > price_title_dst&&
					orgEle.Pos[1] - nameTitlePosY - orgEle.Pos[3] / 2.0 < price_title_dst&&
					orgEle.Pos[0] + orgEle.Pos[2]>OrgRecoglList[mappedSet[i].ID].Pos[0] &&//不能在标题的左边缘再往左
					orgEle.Pos[0] < nameTitlePosX + OrgRecoglList[mappedSet[i].ID].Pos[2])//不能在标题的右边缘再往右
				{
					map_sameLine.emplace(j, orgEle);
				}

			}

			if (!map_sameLine.empty())
			{

				int minDst = 10000;
				pair<int, RecogResult> loseItem;
				for (auto m : map_sameLine)
				{
					float d = fabs(m.second.Pos[0] - OrgRecoglList[mappedSet[i].ID].Pos[0]);
					if (d < minDst)
					{
						minDst = d;
						loseItem = m;
					}
				}


				//////cnt << loseItem.second.RResult << "___" << p.second.RResult << endl;

				KeyWord keyWord;

				keyWord.Name = loseItem.second.RResult;
				memcpy(&keyWord.Pos[0], &loseItem.second.Pos[0], sizeof(float)* 4);
				keyWord.TotalPrice = p.second.RResult;
				memcpy(&keyWord.Pos[4], &p.second.Pos[0], sizeof(float)* 4);
				FinalList.push_back(keyWord);

				//找到匹配项
				OrgRecoglList[loseItem.first].IsMatched = 0;
				OrgRecoglList[p.first].IsMatched = 0;

				Point pt1, pt2;
				pt1.x = loseItem.second.Pos[0] + loseItem.second.Pos[2] / 2;
				pt1.y = loseItem.second.Pos[1] + loseItem.second.Pos[3] / 2;

				pt2.x = p.second.Pos[0] + p.second.Pos[2] / 2;
				pt2.y = p.second.Pos[1] + p.second.Pos[3] / 2;

				line(this->InputImage, pt1, pt2, CV_RGB(255, 0, 0));
			}
		}
	}


}
void CExtractInfo::ResearchLostItemByName()
{
	//////cnt << "=====ResearchLostItemByName=====" << mappedSet.size() << endl;


	//找出未匹配的名字
	for (int i = 0; i < mappedSet.size(); i++)
	{
		//vector<RecogResult> vec_name;//保存名称项
		//vector<int>vec_nameID;//保存名称ID
		map<int, RecogResult>map_loseName;
		int nextNameID = mappedSet[i].ID;
		int nID = 0;
		while (nextNameID != -1 && nID != -1)
		{
			nextNameID = FindNearBottom(nextNameID);
			//寻找丢失的名字时暂时假设必须要有中文。。用于过滤找到项目代码名称造成重复
			if (this->OrgRecoglList[nextNameID].IsMatched == -1 && IsValidElem(OrgRecoglList[nextNameID].RResult) == -1)
				//if (this->OrgRecoglList[nextNameID].IsMatched == -1 )
			{
				/*vec_name.push_back(OrgRecoglList[nextNameID]);
				vec_nameID.push_back(nextNameID);*/
				map_loseName.emplace(nextNameID, OrgRecoglList[nextNameID]);
				//////cnt << "ID" << nextNameID << "丢失的名字==>" << OrgRecoglList[nextNameID].RResult << endl;
			}
		}

		int priceTitlePosY = OrgRecoglList[mappedSet[i].MatchedID].Pos[1];//价格所在标题的位置
		for (auto & p : map_loseName)
		{
			/*vector<RecogResult>sameLinePrice;
			vector<int>sameLinePriceID;*/
			map<int, RecogResult>sameLinePrice;
			int name_title_dst = fabs(p.second.Pos[1] - OrgRecoglList[mappedSet[i].ID].Pos[1]);//当前待查找的丢失名字与标题之间的距离

			//找出名字对应行可能的价格以及ID
			for (int j = 0; j<OrgRecoglList.size(); j++)
			{

				if (OrgRecoglList[j].Pos[1] - priceTitlePosY + OrgRecoglList[j].Pos[3] / 2.0 > name_title_dst&&
					OrgRecoglList[j].Pos[1] - priceTitlePosY - OrgRecoglList[j].Pos[3] / 2.0 < name_title_dst&&
					IsValidElem(OrgRecoglList[j].RResult) == 0)//
					//orgEle.Pos[0] + orgEle.Pos[2]>OrgRecoglList[mappedSet[i].MatchedID].Pos[0] &&//不能在标题的左边缘再往左
					//orgEle.Pos[0] <OrgRecoglList[mappedSet[i].MatchedID].Pos[0] + OrgRecoglList[mappedSet[i].ID].Pos[2])
				{
					/*sameLinePrice.push_back(OrgRecoglList[j]);
					sameLinePriceID.push_back(j);*/
					sameLinePrice.emplace(j, OrgRecoglList[j]);
				}
			}

			if (!sameLinePrice.empty())
			{

				int minDst = 10000;
				pair<int, RecogResult> loseItem;
				for (auto &m : sameLinePrice)
				{
					float d = fabs(m.second.Pos[0] - OrgRecoglList[mappedSet[i].MatchedID].Pos[0]);
					if (d < minDst)
					{
						minDst = d;
						loseItem = m;
					}
				}
				//////cnt << p.second.RResult << "___" << loseItem.second.RResult << endl;
				OrgRecoglList[loseItem.first].IsMatched = 0;
				OrgRecoglList[p.first].IsMatched = 0;


				KeyWord keyWord;

				keyWord.Name = p.second.RResult;
				memcpy(&keyWord.Pos[0], &p.second.Pos[0], sizeof(float)* 4);
				keyWord.TotalPrice = loseItem.second.RResult;
				memcpy(&keyWord.Pos[4], &loseItem.second.Pos[0], sizeof(float)* 4);
				FinalList.push_back(keyWord);

				Point pt1, pt2;
				pt1.x = loseItem.second.Pos[0] + loseItem.second.Pos[2] / 2;
				pt1.y = loseItem.second.Pos[1] + loseItem.second.Pos[3] / 2;

				pt2.x = p.second.Pos[0] + p.second.Pos[2] / 2;
				pt2.y = p.second.Pos[1] + p.second.Pos[3] / 2;

				line(this->InputImage, pt1, pt2, CV_RGB(255, 0, 0));
			}
		}
	}

}
int CExtractInfo::FindNearBottom(int OrgID)
{
	float minDist = 100000;
	int minID = -1;
	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		if (i == OrgID)
			continue;
		/*if (findType == 1)
		{
		int nameTitlePosX = OrgRecoglList[mappedSet[0].ID].Pos[0];
		if(OrgRecoglList[i].Pos[0] > nameTitlePosX)
		continue;
		}*/
		//如果待项目名称判断列的左边缘大于项目名称标题的的列的右边缘，则说明不在同列
		/*if (findType == 1 && OrgRecoglList[OrgID].Pos[0] + OrgRecoglList[OrgID].Pos[2] / 2 < OrgRecoglList[i].Pos[0])
		continue*/;
		if (OrgRecoglList[OrgID].Pos[0] + OrgRecoglList[OrgID].Pos[2] < OrgRecoglList[i].Pos[0])
			continue;

		//ADD
		/*if (OrgRecoglList[i].Pos[0] + OrgRecoglList[i].Pos[2] < OrgRecoglList[OrgID].Pos[0])
		{
		continue;
		}*/


		//	////cnt << "name : " << OrgRecoglList[i].RResult << endl;
		//如果待查找项的y坐标在下面
		if (OrgRecoglList[i].Pos[1] > OrgRecoglList[OrgID].Pos[1] + OrgRecoglList[OrgID].Pos[3] / 2)
		{
			//ADD
			//float dist = fabs(OrgRecoglList[i].Pos[1] - OrgRecoglList[OrgID].Pos[1] - OrgRecoglList[OrgID].Pos[3]);
			float dist = fabs(OrgRecoglList[i].Pos[1] - OrgRecoglList[OrgID].Pos[1]) + fabs(OrgRecoglList[i].Pos[0] - OrgRecoglList[OrgID].Pos[0]);
			if (dist < minDist)
			{
				minDist = dist;
				minID = i;
			}
		}
	}


	return minID;
}

int CExtractInfo::PostProcTotalPrice(string& input, string& output)
{
	output = input;

	std::size_t found = input.rfind(".");
	if (found != std::string::npos)
	{
		if (found < input.length() - 2)  //小数点后面最多取2位
			output = input.substr(0, found + 3);
	}

	return 1;
}
/*判断是不是一个好的匹配对
0: 好的匹配对
1：ID需要下移，MatchedID保持不变
2：ID保持不变，MatchedID需要下移
*/
int CExtractInfo::IsGoodPair(int LastID, int ID, int MatchedLastID, int MatchedID)
{
	int err = 15;

	float dist1 = this->OrgRecoglList[ID].Pos[1] - this->OrgRecoglList[LastID].Pos[1];
	float dist2 = this->OrgRecoglList[MatchedID].Pos[1] - this->OrgRecoglList[MatchedLastID].Pos[1];
	//////cnt << dist1<<"|||||"<< dist2 << endl;

	if (fabs(dist2 - dist1) < err)
		return 0;

	if (dist2 - dist1 > 1.5 * err)
		return 1;

	if (dist1 - dist2 > 1.5 * err)
		return 2;
	else
	{
		//////cnt << dist1 << "," << dist2 << endl;
		//////cnt << OrgRecoglList[ID].RResult << endl;
	}
	return -1;

}

int CExtractInfo::IsValidElem(int nameID, int priceID)
{
	const char *ptrStr = this->OrgRecoglList[priceID].RResult.c_str();
	bool bFind = false;
	for (int i = 0; i < strlen(ptrStr); i++)
	if ((ptrStr[i] & 0x80) != 0)  //发现汉字编码
	{
		return -1;

	}
	return 0;
}
int CExtractInfo::IsValidElem(string str)
{
	const char *ptrStr = str.c_str();
	bool bFind = false;
	for (int i = 0; i < strlen(ptrStr); i++)
	if ((ptrStr[i] & 0x80) != 0)  //发现汉字编码
	{
		return -1;

	}
	return 0;
}
int CExtractInfo::ExtractInfo(char *ListDetail, unsigned char *RGBImage, int imageWidth, int imageHeight)
{
	//读取图像
	//Mat InImage(imageHeight, imageWidth, CV_8UC3, RGBImage);

	//调用接口得到识别结果

	//把识别结果放入到recogList中
	for (int i = 0; i < this->RecoglList.size(); i++)
	{
		this->RecoglList[i].Flag = 0;

		if (IsValidName())
			this->RecoglList[i].Flag = 1;  //汉字

		if (IsValidNumber())
			this->RecoglList[i].Flag = 2; //数字
	}

	//调用函数LocalName定位所有可能的检测项


	return 1;
}

//得到名字项的近邻集合ID
int CExtractInfo::GetAdjIDofName(int CurID)
{
	int err = 3;

	//X坐标要大于当前ID的右边坐标，且位置中心的Y坐标不超过设定误差


	return 1;
}

//是否是有效的名字项
int CExtractInfo::IsValidName()
{
	return 1;
}
int CExtractInfo::IsValidNumber()
{
	return 1;
}
int CExtractInfo::IsValidNumber(string str)
{
	const char *ptrStr = str.c_str();
	for (int i = 0; i < strlen(ptrStr); i++)
	{
		if (isdigit(ptrStr[i]))
			return 1;
	}
	return 0;
}

int CExtractInfo::LocalName()
{
	vector<int> SplitPos;
	int Thres = 50;  //用于横坐标聚类的阈值

	//imwrite("c:\\123.jpg", InputImage);

	//把所有结果按照左上角的X坐标进行排序
	sort(RecoglList.begin(), RecoglList.end());


	//把数据进行简单分片
	//	printf("%d\n", RecoglList.size());
	int lastI = 0;
	for (int i = 1; i < RecoglList.size(); i++)
	{
		printf("%d %f\n", i, RecoglList[i].Pos[0]);

		if (RecoglList[i].Flag == 4 || RecoglList[i].Flag == 5 || RecoglList[i].Flag == 6 || RecoglList[i].Flag == 7)
			continue;

		float diff = fabs(RecoglList[i].Pos[0] - RecoglList[i - 1].Pos[0]);
		//	printf("%f\n", diff);
		if (diff > Thres)
		{
			DrawVerLine(lastI, i - 1);
			SplitPos.push_back(i);  //每个分片的最后一个元素
			lastI = i;
			//	break;
		}
	}
	/**/
	return 1;
}

int CExtractInfo::DrawRectangle(Mat& drawImage, int ID, int colorID)
{
	Rect rect;

	rect.x = OrgRecoglList[ID].Pos[0];
	rect.y = OrgRecoglList[ID].Pos[1];
	rect.width = OrgRecoglList[ID].Pos[2];
	rect.height = OrgRecoglList[ID].Pos[3];

	switch (colorID)
	{
	case 0:
		rectangle(drawImage, rect, CV_RGB(255, 0, 0));
		break;
	case 1:
		rectangle(drawImage, rect, CV_RGB(255, 255, 0));
		break;
	case 2:
		rectangle(drawImage, rect, CV_RGB(255, 255, 255));
		break;
	case 3:
		rectangle(drawImage, rect, CV_RGB(255, 128, 128));
		break;
	default:
		rectangle(drawImage, rect, CV_RGB(0, 0, 0));
	}
	return 1;
}
//字符串，字符串位置，字符串中的每个字符的位置
int CExtractInfo::PushRecogResult(string strText, string strPos, vector<PosOfChar>& charPos)
{
	//const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";

	//Json::Reader reader;
	//Json::Value root;
	//if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	//{
	//	std::string upload_id = root["recognize_data_detail"].asString();  // 访问节点，upload_id = "UP000000"  
	//	
	//}
	RecogResult elem;

	int s[4];
	sscanf(strPos.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);

	//此处将字符串的左上位置设为第一个字符的左上角位置，将宽度设置最后一个字符位置减去第一个字符的位置
	//elem.Pos[0] = s[0];
	//elem.Pos[1] = s[1];
	//elem.Pos[2] = s[2];
	//elem.Pos[3] = s[3];
	elem.RResult = strText;
	elem.charPos.assign(charPos.begin(), charPos.end());

	int top = 1000000, bottom = -1;
	for (int i = 0; i < elem.charPos.size(); i++)
	{
		if (top > elem.charPos[i].pos[1])
			top = elem.charPos[i].pos[1];

		if (bottom < elem.charPos[i].pos[3])
			bottom = elem.charPos[i].pos[3];
	}
	elem.Pos[0] = elem.charPos[0].pos[0];
	elem.Pos[1] = top;// elem.charPos[0].pos[1] + 2;
	elem.Pos[2] = elem.charPos[elem.charPos.size() - 1].pos[0] + elem.charPos[elem.charPos.size() - 1].pos[2] - elem.charPos[0].pos[0];
	elem.Pos[3] = bottom;// elem.charPos[0].pos[3];

	Rect rect;
	for (int j = 0; j < elem.charPos.size(); j++)
	{
		rect.x = elem.charPos[j].pos[0];
		rect.y = elem.charPos[j].pos[1];
		rect.width = elem.charPos[j].pos[2];
		rect.height = elem.charPos[j].pos[3];
		//	rectangle(this->InputImage, rect, CV_RGB(0, 255, 0));
	}
	//DrawRect(elem,0);

	vector<RecogResult> FinalelemSet;
	this->SplitRegions(FinalelemSet, elem);
	for (int i = 0; i < FinalelemSet.size(); i++)
	{
		//FinalelemSet[i].Flag = this->CheckRecogType(FinalelemSet[i].RResult, _charPosIndex, _charEndPosIndex);
		//	FinalelemSet[i].IsMatched = -1;
		//	RecoglList.push_back(FinalelemSet[i]);

		//找出标题在识别字符串中的实际位置
		int _charPosIndex = 0;//
		int _charEndPosIndex = 0;

		FinalelemSet[i].Flag = this->CheckRecogType(FinalelemSet[i].RResult, _charPosIndex, _charEndPosIndex);
		if ((FinalelemSet[i].Flag == 11 || FinalelemSet[i].Flag == 12) &&
			FinalelemSet[i].RResult.length() < 4)//"名"//称
			CandTitleList.push_back(FinalelemSet[i]);

		if (FinalelemSet[i].Flag == 4 || FinalelemSet[i].Flag == 6)
		{
			auto tempEle = FinalelemSet[i];
			SplitTitle(tempEle, _charPosIndex, _charEndPosIndex);

		}
		else
		{
			//DrawRect(FinalelemSet[i]);
			FinalelemSet[i].IsMatched = -1;
			RecoglList.push_back(FinalelemSet[i]);
		}

	}



	return 0;
}





void CExtractInfo::SplitTitle(RecogResult & titleItem, int _charPosIndex, int _charEndPosIndex)
{
	if (titleItem.Flag == 4)
	{
		//金额与项目名称连在一起，就需要切开。由于搜索时优先名称，所以只需要判断Flag=4
		if (titleItem.RResult.find("金额") != string::npos || titleItem.RResult.find("总额") != string::npos)
		{
			RecogResult recog[2];
			recog[0].RResult.assign(titleItem.RResult.begin(), titleItem.RResult.begin() + 4);//中文一个字2字节，所以加4
			recog[0].Flag = 6;
			recog[0].charPos.assign(titleItem.charPos.begin(), titleItem.charPos.begin() + 2);
			recog[0].Pos[0] = titleItem.charPos[0].pos[0];
			recog[0].Pos[1] = titleItem.charPos[0].pos[1];
			recog[0].Pos[2] = titleItem.charPos[2].pos[0] - recog[0].Pos[0] - 2;//此处要减去一点距离因为两个标题是连在一起的
			recog[0].Pos[3] = titleItem.charPos[0].pos[3];
			recog[0].IsMatched = -1;

			recog[1].RResult.assign(titleItem.RResult.begin() + 4, titleItem.RResult.end());
			recog[1].Flag = 4;
			recog[1].Pos[0] = titleItem.charPos[2].pos[0] + 2;//同上
			recog[1].Pos[1] = titleItem.charPos[2].pos[1];
			recog[1].Pos[2] = titleItem.charPos[titleItem.charPos.size() - 1].pos[0] +
				titleItem.charPos[titleItem.charPos.size() - 1].pos[3] - recog[1].Pos[0];
			recog[1].Pos[3] = titleItem.charPos[2].pos[3];
			recog[1].IsMatched = -1;

			RecoglList.push_back(recog[0]);
			RecoglList.push_back(recog[1]);
			DrawRect(recog[0]);
			DrawRect(recog[1]);
			return;
			//RecoglList.push_back(titleItem);
		}
		//正常的项目名称标题在这添加
		titleItem.IsMatched = -1;
		RecoglList.push_back(titleItem);
		//	DrawRect(titleItem);
	}

	if (titleItem.Flag == 6)//暂时只切分金额
	{
		//对于识别出金额，左侧相邻很近的的话左边部分依然应该算作金额标题，比如“计价金额”，识别出金额，_charPosIndex=2,而计价两个字应该也
		//要算在里面，不然金额会截取不全

		int chWidth = titleItem.charPos[_charPosIndex].pos[2];
		if (_charPosIndex > 0 > 0 && titleItem.charPos[_charPosIndex].pos[0] - titleItem.charPos[_charPosIndex - 1].pos[0] < chWidth + 10)
			_charPosIndex--;
		int offsetNum = 2;
		while (_charEndPosIndex < titleItem.charPos.size() - 1 && offsetNum-- >0 && titleItem.charPos[_charEndPosIndex + 1].pos[0] - titleItem.charPos[_charEndPosIndex].pos[0] <  chWidth + 10)
			_charEndPosIndex++;
		//对于这种组合起来的，就不截取右边部分了
		if (titleItem.RResult.find("其中") != string::npos)
			_charEndPosIndex = titleItem.charPos.size();
		//左边项
		if (_charPosIndex > 0)
		{//切分识别连在一起的金额左边部分
			RecogResult leftItem;
			leftItem.charPos.assign(titleItem.charPos.begin(), titleItem.charPos.begin() + _charPosIndex);
			leftItem.Pos[0] = titleItem.charPos[0].pos[0];
			leftItem.Pos[1] = titleItem.charPos[0].pos[1];
			leftItem.Pos[2] = titleItem.charPos[_charPosIndex].pos[0] - leftItem.Pos[0] - 15;//此处要减去一点距离因为两个字符是连在一起的
			leftItem.Pos[3] = titleItem.charPos[0].pos[3];
			leftItem.IsMatched = -1;
			leftItem.Flag = 0;
			int bytePos = TranFound2(_charPosIndex, titleItem.RResult);
			string str = titleItem.RResult;
			leftItem.RResult = str.assign(str.begin(), str.begin() + bytePos);
			RecoglList.push_back(leftItem);
		}
		//右边项
		if (_charEndPosIndex < titleItem.charPos.size())
		{
			RecogResult rightItem;
			rightItem.charPos.assign(titleItem.charPos.begin() + _charEndPosIndex, titleItem.charPos.end());
			rightItem.Pos[0] = titleItem.charPos[_charEndPosIndex].pos[0] + 2;
			rightItem.Pos[1] = titleItem.charPos[_charEndPosIndex].pos[1];
			rightItem.Pos[2] = titleItem.Pos[0] + titleItem.Pos[2] - rightItem.Pos[0] + 2;
			rightItem.Pos[3] = titleItem.charPos[0].pos[3];
			rightItem.IsMatched = -1;
			rightItem.Flag = 0;
			int bytePos = TranFound2(_charEndPosIndex, titleItem.RResult);
			string str = titleItem.RResult;
			rightItem.RResult = str.assign(str.begin() + bytePos, str.end());
			RecoglList.push_back(rightItem);
		}
		//中间项
		int realStartPos = titleItem.charPos[_charPosIndex].pos[0];//实际开始位置
		int bytePos = TranFound2(_charPosIndex, titleItem.RResult);
		//	////cnt << "BytePos" << bytePos << endl;
		//titleItem.charPos.assign(titleItem.charPos.begin()+)
		if (_charEndPosIndex < titleItem.charPos.size())
			titleItem.Pos[2] = titleItem.charPos[_charEndPosIndex].pos[0] - realStartPos - 2;
		else
			titleItem.Pos[2] = titleItem.Pos[0] + titleItem.Pos[2] - realStartPos - 2;
		titleItem.Pos[0] = realStartPos;
		string str = titleItem.RResult;
		titleItem.RResult = str.substr(bytePos, (_charEndPosIndex - _charPosIndex) * 2);
		titleItem.IsMatched = -1;
		RecoglList.push_back(titleItem);

		DrawRect(titleItem);



	}

}
//
//int CExtractInfo::FindExcetionItemPos(const vector<PosOfChar>& charPos)
//{
//	int offset = 15;
//	for (int i = 0; i < charPos.size() - 1; i++)
//	{
//		if (charPos[i].pos[0] + charPos[i].pos[2] + offset < charPos[i + 1].pos[0])
//			return i + 1;
//	}
//	return -1;
//}
//void CExtractInfo::SplitExceptionItem(vector<RecogResult>& FinalelemSet)
//{
//	vector<RecogResult> res;
//	for (int i = 0; i < FinalelemSet.size(); i++)
//	{
//		//不划分中文字符
//		if (IsValidElem(FinalelemSet[i].RResult) == -1)
//			continue;
//		auto charPos = FinalelemSet[i].charPos;
//		int findPos = FindExcetionItemPos(charPos);
//		////cnt << "findPos" << findPos << "   内容 " << FinalelemSet[i].RResult << endl;
//		if (findPos != -1)
//		{
//
//			RecogResult elemSet[2];
//			elemSet[0].charPos.assign(charPos.begin(), charPos.begin() + findPos);
//			elemSet[0].RResult.assign(FinalelemSet[i].RResult.begin(), FinalelemSet[i].RResult.begin() + findPos);
//			elemSet[0].Pos[0] = FinalelemSet[i].Pos[0];
//			elemSet[0].Pos[1] = FinalelemSet[i].Pos[1];
//			elemSet[0].Pos[2] = FinalelemSet[i].charPos[findPos].pos[0] - FinalelemSet[i].charPos[0].pos[0];
//			elemSet[0].Pos[3] = FinalelemSet[i].Pos[3];
//
//			elemSet[1].charPos.assign(charPos.begin() + findPos, charPos.end());
//			elemSet[1].RResult.assign(FinalelemSet[i].RResult.begin() + findPos, FinalelemSet[i].RResult.end());
//			elemSet[1].Pos[0] = FinalelemSet[i].charPos[findPos].pos[0];
//			elemSet[1].Pos[1] = FinalelemSet[i].charPos[findPos].pos[1];
//			auto lastCharaterPos = FinalelemSet[i].charPos[FinalelemSet[i].charPos.size() - 1];
//			elemSet[1].Pos[2] = lastCharaterPos.pos[0] + lastCharaterPos.pos[2] - FinalelemSet[i].charPos[findPos].pos[0];
//			elemSet[1].Pos[3] = FinalelemSet[i].Pos[3];
//
//			res.push_back(elemSet[0]);
//			res.push_back(elemSet[1]);
//		}
//		else
//		{
//			res.push_back(FinalelemSet[i]);
//		}
//	}
//	if (!res.empty())
//		FinalelemSet = res;
//
//}
int CExtractInfo::FindSplitPos(RecogResult& InputStr)
{
	int minPos = -1;
	int flag = 1;
	int f3 = InputStr.RResult.find("可报");
	if (f3 != std::string::npos)
		flag = 0;
	string KeySplitSet = " :";
	////满足切分的条件（字符为空格与冒号，或者两个字符之间有着明显的间距超过一个字符的间距，且前面有两个字符）
	//for (int i = 0,k=0; i < InputStr.charPos.size() - 2; i++)
	//{
	//	if (flag == 0)
	//		////cnt << InputStr.RResult[i] << endl;
	//			
	//	if ((InputStr.RResult[i] & 0x80) != 0)
	//		k = k + 1;
	//	int find = KeySplitSet.find(InputStr.RResult[k]);

	//	if (i>0 && find != std::string::npos)  //找到关键切分字符
	//	{
	//		minPos = i;
	//		break;
	//	}
	//	else
	//	{
	//		if (i >= 2)
	//		{
	//			if ((InputStr.charPos[i + 1].pos[2]) > 2.0*(InputStr.charPos[i].pos[2]))
	//			{
	//				minPos = i + 1;
	//				break;
	//			}
	//		}
	//	}
	//}


	//splitedStr 为 空格与冒号与 |
	for (int i = 0; i < splitedStr.size(); i++)
	{
		int f3 = InputStr.RResult.find(splitedStr[i]);
		if (f3 != std::string::npos)
		{
			if (minPos == -1)
				minPos = f3;
			else
			{
				if (f3 < minPos)
					//f3 = minPos;
					minPos = f3;
			}
			//	////cnt << charfound2 << endl;
		}
	}

	//if (minPos == -1)  //如果找不到分割线，则进行二次分析
	//{
	//	int f3 = InputStr.RResult.find("西药费");
	//	if (f3 != std::string::npos)
	//	{
	//		//	////cnt << InputStr.RResult << endl;
	//	}
	//	for (int i = 0; i < InputStr.charPos.size() - 1; i++)
	//	{
	//		//	////cnt << InputStr.charPos[i].pos[0] << "+++" << InputStr.charPos[i].pos[2] << endl;
	//		if (InputStr.charPos[i + 1].pos[0] > InputStr.charPos[i].pos[0] + 2 * InputStr.charPos[i].pos[2] &&
	//			i < InputStr.charPos.size() - 3) //存在切分点
	//		{

	//			InvTranFound(i, InputStr.RResult);
	//			break;
	//		}
	//	}
	//}
	//////cnt << "min pos ====> " << minPos << endl;
	return minPos;
}
int CExtractInfo::SplitRegions(vector<RecogResult>& FinalelemSet, RecogResult elem)
{
	int found = FindSplitPos(elem);

	//int f3 = elem.RResult.find("一级");
	//if (f3 != std::string::npos)
	//	int flag = 0;
	//
	int charfound;// = TranFound(found, elem.RResult);

	RecogResult elemSet[2];
	if (found != -1)  //发现空格，把这个识别区域进行拆分
	{
		while (found != std::string::npos)
		{
			charfound = TranFound(found, elem.RResult);//?
			//	////cnt << "char found" << charfound << endl;
			Rect rect;

			//////cnt << charfound<<" "<< found << "++" << elem.RResult << endl;
			if (found > 0)
			{
				elemSet[0].charPos.resize(found);
				elemSet[0].charPos.assign(elem.charPos.begin(), elem.charPos.begin() + charfound);

				elemSet[0].RResult.assign(elem.RResult.begin(), elem.RResult.begin() + found);

				elemSet[0].Pos[0] = elem.Pos[0]; elemSet[0].Pos[1] = elem.Pos[1];
				if (charfound > 0)//分割后的宽度为最后一个字符的末尾减去第一个字符的开始
					elemSet[0].Pos[2] = elem.charPos[charfound - 1].pos[0] + elem.charPos[charfound - 1].pos[2] - elem.charPos[0].pos[0];
				else
					elemSet[0].Pos[2] = elem.charPos[0].pos[2];
				elemSet[0].Pos[3] = elem.Pos[3];

				//金额与其中放到一起
				if (FinalelemSet.size() > 0 && FinalelemSet.back().RResult == "金额"&&elemSet[0].RResult == "其中")
				{
					for (auto &charPos : elemSet[0].charPos)
						FinalelemSet.back().charPos.push_back(charPos);
					FinalelemSet.back().RResult += "其中";
					FinalelemSet.back().Pos[2] = FinalelemSet.back().Pos[2] + elemSet[0].Pos[2];
				}
				else if (FinalelemSet.size() > 0 && FinalelemSet.back().RResult == "金"&&elemSet[0].RResult == "额")
				{
					for (auto &charPos : elemSet[0].charPos)
						FinalelemSet.back().charPos.push_back(charPos);
					FinalelemSet.back().RResult += "额";
					FinalelemSet.back().Pos[2] = FinalelemSet.back().Pos[2] + elemSet[0].Pos[2];
				}
				else
					FinalelemSet.push_back(elemSet[0]);
				/*rect.x = elemSet[0].Pos[0];
				rect.y = elemSet[0].Pos[1];
				rect.width = elemSet[0].Pos[2];
				rect.height = elemSet[0].Pos[3];*/
				//	rectangle(this->InputImage, rect, CV_RGB(255, 0, 0));
			}
			/*
			for (int j = charfound; j < elem.charPos.size(); j++)
			{
			rect.x = elem.charPos[j].pos[0];
			rect.y = elem.charPos[j].pos[1];
			rect.width = elem.charPos[j].pos[2];
			rect.height = elem.charPos[j].pos[3];
			rectangle(this->InputImage, rect, CV_RGB(0, 255, 0));
			}*/

			//////cnt << "charfound?:" << elem.charPos.size() << ":" << charfound << endl;
			if (elem.charPos.size() - charfound - 1 > 0)
			{

				elemSet[1].charPos.resize(elem.charPos.size() - charfound - 1);
				elemSet[1].charPos.assign(elem.charPos.begin() + charfound + 1, elem.charPos.end());
				elemSet[1].RResult.assign(elem.RResult.begin() + found + 1, elem.RResult.end());

				elemSet[1].Pos[0] = elem.charPos[charfound + 1].pos[0]; elemSet[1].Pos[1] = elem.charPos[charfound].pos[1];
				elemSet[1].Pos[2] = elem.Pos[0] + elem.Pos[2] - elem.charPos[charfound + 1].pos[0];
				elemSet[1].Pos[3] = elem.Pos[3];

				//	////cnt << elem.charPos.size()<<"++"<<elemSet[1].Pos[0] << " " << elemSet[1].Pos[1] << " " << elemSet[1].Pos[2] << " " << elemSet[1].Pos[3] << endl;
				//	////cnt << elemSet[0].RResult << "+++" << elemSet[1].RResult << endl;
				elem.charPos.assign(elemSet[1].charPos.begin(), elemSet[1].charPos.end());
				elem.RResult = elemSet[1].RResult;
				elem.Pos[0] = elemSet[1].Pos[0]; elem.Pos[1] = elemSet[1].Pos[1];
				elem.Pos[2] = elemSet[1].Pos[2]; elem.Pos[3] = elemSet[1].Pos[3];

				found = FindSplitPos(elem);

				if (found == -1 || found == elem.RResult.size() - 1)
				{
					FinalelemSet.push_back(elemSet[1]);
					break;
				}

			}
			else
			{
				break;
			}

			/*rect.x = elemSet[1].Pos[0];
			rect.y = elemSet[1].Pos[1];
			rect.width = elemSet[1].Pos[2];
			rect.height = elemSet[1].Pos[3];*/
			//	rectangle(this->InputImage, rect, CV_RGB(255, 0, 0));
		}
	}
	else
	{
		FinalelemSet.push_back(elem);
	}

	return 0;
}
bool CExtractInfo::IsSameLine(RecogResult r1, RecogResult r2)
{
	////cnt << fabs(r1.Pos[1] + r1.Pos[3] / 2 - r2.Pos[1] - r2.Pos[3] / 2) << endl;
	////cnt << (r1.Pos[3] + r2.Pos[3]) * 0.4 << endl;
	if (fabs(r1.Pos[1] + r1.Pos[3] / 2 - r2.Pos[1] - r2.Pos[3] / 2) < (r1.Pos[3] + r2.Pos[3]) * 0.4)
		return true;
	else
		return false;
	//if (r1.Pos[1] >= r2.Pos[1] && r1.Pos[1] - r2.Pos[1] < r2.Pos[3])
	//	return true;
	//else if (r2.Pos[1] > r1.Pos[1] && r2.Pos[1] - r1.Pos[1] < r1.Pos[3])
	//	return true;
	//return false;
}
void CExtractInfo::findAdjacent(int curId, int &leftId, int &rightId)
{
	//TODO 左右没有找到的情况
	float leftMinDist = 100000;
	float rightMinDist = 100000;

	int minLeftId = -1, minRightId = -1;
	int curItemRight = OrgRecoglList[curId].Pos[0] + OrgRecoglList[curId].Pos[2];

	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		if (i == curId)
			continue;
		if (!IsSameLine(OrgRecoglList[i], OrgRecoglList[curId]))
			continue;
		//////cnt << OrgRecoglList[i].RResult << "  ====  " << OrgRecoglList[curId].RResult << endl;
		if (OrgRecoglList[i].Pos[0] > curItemRight)
		{
			float dist = fabs(OrgRecoglList[i].Pos[0] - curItemRight);
			if (dist < rightMinDist)
			{
				rightMinDist = dist;
				minRightId = i;
			}
		}
		else if (OrgRecoglList[i].Pos[0] + OrgRecoglList[i].Pos[2] < OrgRecoglList[curId].Pos[0])
		{
			float dist = fabs(OrgRecoglList[curId].Pos[0] - OrgRecoglList[i].Pos[0] - OrgRecoglList[i].Pos[2]);
			if (dist < leftMinDist)
			{
				leftMinDist = dist;
				minLeftId = i;
			}
		}
	}

	leftId = minLeftId;
	rightId = minRightId;
}
//获取id左右端项黑点最少的列
void CExtractInfo::findPosX(const cv::Mat &thresholdedImg, int nameId, int &leftX, int &rightX)
{
	const int maxBlackPtNum = 130;//TODO 这个阈值是否要考虑图片高度，但是由于有些图它并不是整页的，所以可能根据图片高度确定阈值也不是一个好的选择

	int nameLeft = OrgRecoglList[nameId].Pos[0];
	int nameRight = OrgRecoglList[nameId].Pos[0] + OrgRecoglList[nameId].Pos[2];
	int nameLeftItemId, nameRightItemId;
	findAdjacent(nameId, nameLeftItemId, nameRightItemId);//根据当前传入的项的id找到他所在行的左右项的id，如果未找到，那一项的id为-1	
	//////cnt << OrgRecoglList[nameLeftItemId].RResult << " <=" << OrgRecoglList[nameId].RResult << " =>" << OrgRecoglList[nameRightItemId].RResult << endl;
	int minBlackNum = 99999;
	if (nameLeftItemId != -1)
	{
		//	////cnt << "Left: " << OrgRecoglList[nameLeftItemId].RResult << endl;
		int nameLeftItemPos = OrgRecoglList[nameLeftItemId].Pos[0] + OrgRecoglList[nameLeftItemId].Pos[2];
		for (int i = nameLeftItemPos; i <= nameLeft; i++)
		{
			int blackNum = 0;
			for (int j = OrgRecoglList[nameLeftItemId].Pos[1]; j < thresholdedImg.rows - 100; j++)//此处减去100是因为旋转后的图片，最下方是黑色的
			{
				int m = thresholdedImg.at<uchar>(j, i * 3);
				if (m == 0)
					blackNum++;
			}
			if (minBlackNum > blackNum)
			{
				leftX = i;
				minBlackNum = blackNum;
			}
			//////cnt << "i:" << i << " num: " << blackNum << endl;
		}
		//黑点个数阈值
		if (minBlackNum > maxBlackPtNum)
			leftX = nameLeftItemPos + 5;

	}
	else
		leftX = 5;//如果左侧项没有找到，则为最左侧

	//////cnt << "左侧黑点" << minBlackNum << endl;
	if (nameRightItemId != -1)
	{
		//////cnt << "Right: " << OrgRecoglList[nameRightItemId].RResult << endl;
		int nameRightItemPos = OrgRecoglList[nameRightItemId].Pos[0] + 15;
		minBlackNum = 99999;

		for (int i = nameRightItemPos; i >= nameRight; i--)
		{
			int blackNum = 0;
			for (int j = OrgRecoglList[nameId].Pos[1]; j < thresholdedImg.rows - 100; j++)
			{
				int m = thresholdedImg.at<uchar>(j, i * 3);
				if (m == 0)
					blackNum++;
			}
			if (minBlackNum > blackNum)
			{
				rightX = i;
				minBlackNum = blackNum;
			}
			//////cnt << "i:" << i << " num: " << blackNum << endl;
		}
		//黑点个数阈值
		if (minBlackNum > maxBlackPtNum)
			rightX = nameRightItemPos - 5;
	}
	else
		rightX = thresholdedImg.cols - 5;//如果左侧项没有找到，则为最右侧
	//////cnt << "右侧黑点" << minBlackNum << endl;

	//查找区域中间黑点个数，
	/*const int maxBlackPtNum2 = 200;
	for (int i = leftX; i <= rightX; i++)
	{
	int blackNum = 0;
	for (int j = OrgRecoglList[nameId].Pos[1]; j < thresholdedImg.rows - 100; j++)
	{
	int m = thresholdedImg.at<uchar>(j, i * 3);
	if (m == 0)
	blackNum++;
	}
	////cnt << "blackNum" << blackNum << endl;
	if (blackNum>maxBlackPtNum2)
	return;
	}
	leftX = FindNextBlackPt(thresholdedImg, OrgRecoglList[nameId].Pos[0] - 5, OrgRecoglList[nameId].Pos[1] + OrgRecoglList[nameId].Pos[3] / 2, 0);
	rightX = FindNextBlackPt(thresholdedImg, OrgRecoglList[nameId].Pos[0] + OrgRecoglList[nameId].Pos[2] + 5, OrgRecoglList[nameId].Pos[1] + OrgRecoglList[nameId].Pos[3] / 2, 1);
	*/
}

void CExtractInfo::AutoGetNamePricePos()
{
	cv::Mat thresholdedImg;
	cv::Mat img_gray;

	if (srcImg.channels() == 1)
		img_gray = srcImg.clone();
	else
		cv::cvtColor(srcImg, img_gray, cv::COLOR_RGB2GRAY);


	//	imwrite("c:/1.jpg", srcImg);
	cv::threshold(img_gray, thresholdedImg, 180, 255, CV_THRESH_BINARY);

	int RightIDName[10] = { -1 }, LeftIDName[10] = { -1 }, RightIDPrice[10] = { -1 }, LeftIDPrice[10] = { -1 };
	//imwrite("D:\\二值化.jpg", thresholdedImg);
	for (int i = 0; i < mappedSet.size(); i++)
	{
		int nameId = mappedSet[i].ID;
		int priceId = mappedSet[i].MatchedID;

		if (mappedSet.size() >= 1 && i < 9)  //双行数据，会出现比较明显的重叠
		{
			int idDot;
			RightIDName[i] = FindNearRight(nameId, idDot);
			LeftIDName[i] = FindNearLeft(nameId, idDot);
			RightIDPrice[i] = FindNearRight(priceId, idDot);
			LeftIDPrice[i] = FindNearLeft(priceId, idDot);
		}

		int nameLeft, nameRight, priceLeft, priceRight;

		findPosX(thresholdedImg, nameId, nameLeft, nameRight);
		findPosX(thresholdedImg, priceId, priceLeft, priceRight);

		//左侧约束
		if (LeftIDName[i] != -1)
			nameLeft = OrgRecoglList[LeftIDName[i]].Pos[0] + OrgRecoglList[LeftIDName[i]].Pos[2] + 5;

		if (LeftIDPrice[i] != -1)
			priceLeft = OrgRecoglList[LeftIDPrice[i]].Pos[0] + OrgRecoglList[LeftIDPrice[i]].Pos[2] + 5;

		//右侧约束
		if (RightIDName[i] != -1)
			nameRight = OrgRecoglList[RightIDName[i]].Pos[0] - 5;

		if (RightIDPrice[i] != -1)
			priceRight = OrgRecoglList[RightIDPrice[i]].Pos[0];


		//line(this->InputImage, cv::Point(nameLeft, OrgRecoglList[nameId].Pos[1]), cv::Point(nameLeft, thresholdedImg.rows), CV_RGB(255, 0, 0));
		//line(this->InputImage, cv::Point(nameRight, OrgRecoglList[nameId].Pos[1]), cv::Point(nameRight, thresholdedImg.rows), CV_RGB(255, 0, 0));

		//line(InputImage, cv::Point(priceLeft, OrgRecoglList[priceId].Pos[1]), cv::Point(priceLeft, thresholdedImg.rows), CV_RGB(255, 0, 0));
		//line(InputImage, cv::Point(priceRight, OrgRecoglList[priceId].Pos[1]), cv::Point(priceRight, thresholdedImg.rows), CV_RGB(255, 0, 0));

		TitlePos  t1;

		t1.NamePos = PosOfChar(nameLeft, OrgRecoglList[nameId].Pos[1], nameRight - nameLeft, OrgRecoglList[nameId].Pos[3]);
		t1.PricePos = PosOfChar(priceLeft, OrgRecoglList[priceId].Pos[1], priceRight - priceLeft, OrgRecoglList[priceId].Pos[3]);

		//======添加标题=======
		m_titlePos.push_back(t1);
	}

	//如果两列数据且第一列找不到名称前面的标题，但是第二列找到了，则重叠数据
	if (mappedSet.size() >= 2)
	{
		if (LeftIDName[0] == -1 && LeftIDName[1] != -1 &&
			abs(OrgRecoglList[mappedSet[0].ID].Pos[1] - OrgRecoglList[mappedSet[1].ID].Pos[1]) < OrgRecoglList[mappedSet[0].ID].Pos[3] / 2)
		{
			int wid = OrgRecoglList[mappedSet[1].ID].Pos[0] - (OrgRecoglList[LeftIDName[1]].Pos[0] + OrgRecoglList[LeftIDName[1]].Pos[2]);
			int leftPos = OrgRecoglList[mappedSet[0].ID].Pos[0] - wid;
			if (leftPos >= 0)
			{
				m_titlePos[0].NamePos.pos[0] = leftPos;
				m_titlePos[0].NamePos.pos[2] = m_titlePos[1].NamePos.pos[2];
			}
		}
	}
	//imwrite("c:/1.jpg", this->InputImage);

	//根据找到的项目名称和价格标题继续找单价和数量	
	for (int i = 0; i < mappedSet.size(); i++)
	{
		RecogResult UnitPircPos, NumberPos;
		//float Pos[8]; //在图像中的位置。Pos[0]，Pos[1]：左上角  Pos[2]，Pos[3]：右上角  Pos[4]，Pos[5]：左下角  Pos[6]，Pos[7]：右下角
		//得到单价和数量的标题位置
		this->RecognizePriceAndNumber(UnitPircPos, NumberPos, this->OrgRecoglList[mappedSet[i].ID], this->OrgRecoglList[mappedSet[i].MatchedID]);

		//imwrite("c:/1.jpg", this->InputImage);

		m_titlePos[i].DjPos = PosOfChar(UnitPircPos.Pos[0], UnitPircPos.Pos[1], UnitPircPos.Pos[2], UnitPircPos.Pos[3]);// , nameRight - nameLeft, OrgRecoglList[nameId].Pos[3]);
		m_titlePos[i].NumPos = PosOfChar(NumberPos.Pos[0], NumberPos.Pos[1], NumberPos.Pos[2], NumberPos.Pos[3]);

	}



	/*for (int i = 0; i < mappedSet.size(); i++)
	{
	rectangle(this->InputImage, cv::Point(m_titlePos[i].NamePos.pos[0], m_titlePos[i].NamePos.pos[1]),
	cv::Point(m_titlePos[i].NamePos.pos[0] + m_titlePos[i].NamePos.pos[2],
	m_titlePos[i].NamePos.pos[1] + m_titlePos[i].NamePos.pos[3]), CV_RGB(255, 255, 0));

	rectangle(this->InputImage, cv::Point(m_titlePos[i].PricePos.pos[0], m_titlePos[i].PricePos.pos[1]),
	cv::Point(m_titlePos[i].PricePos.pos[0] + m_titlePos[i].PricePos.pos[2],
	m_titlePos[i].PricePos.pos[1] + m_titlePos[i].PricePos.pos[3]), CV_RGB(255, 255, 0));
	}	*/

	//cv::imwrite("c://1.jpg", InputImage);



}

void CExtractInfo::ReFindTitleWithSingleCharater()
{
	//TODO 如果找到了名称，但是配对的只找到 “额”或“金”
	vector<string>nameCh = { "名", "称" };
	vector<string>priceCh = { "金", "额" };

	vector<int>nameTitleId;
	vector<int>priceTitleId;
	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		for (int j = 0; j < nameCh.size(); j++)
		{
			if (OrgRecoglList[i].RResult.find(nameCh[j]) != string::npos)
			{
				//////cnt << "Name==> " << OrgRecoglList[i].RResult << endl;
				nameTitleId.push_back(i);
				break;
			}
		}
		for (int j = 0; j < priceCh.size(); j++)
		{
			if (OrgRecoglList[i].RResult.find(priceCh[j]) != string::npos)
			{
				//////cnt << "Price==> " << OrgRecoglList[i].RResult << endl;
				priceTitleId.push_back(i);
				break;
			}
		}
	}
	//根据单个字符查找是否在同行
	map<int, int>sameLineIdMap;//此map保存了同一行的名称，金额的ID
	for (int i = 0; i < nameTitleId.size(); i++)
	{
		for (int j = 0; j < priceTitleId.size(); j++)
		{
			if (IsSameLine(OrgRecoglList[nameTitleId[i]], OrgRecoglList[priceTitleId[j]]) && OrgRecoglList[nameTitleId[i]].IsMatched != 0 &&
				OrgRecoglList[priceTitleId[j]].IsMatched != 0)
			{
				OrgRecoglList[nameTitleId[i]].IsMatched = 0;
				OrgRecoglList[priceTitleId[j]].IsMatched = 0;
				sameLineIdMap.emplace(nameTitleId[i], priceTitleId[j]);
			}
		}
	}

	for (auto ids : sameLineIdMap)
	{

		bool bFindNameSameLine = false;
		for (auto ids2 : sameLineIdMap)
		{
			if (IsSameLine(OrgRecoglList[ids.first], OrgRecoglList[ids2.first]))
			{
				if (ids.first == ids2.first)
					continue;
				//////cnt << "二次查找标题===>" << OrgRecoglList[ids.first].RResult << " |  " << OrgRecoglList[ids2.first].RResult << endl;
				int leftNameId, leftPriceId, rightNameId, rightPriceId;
				if (OrgRecoglList[ids.first].Pos[0] < OrgRecoglList[ids2.first].Pos[0])
				{
					leftNameId = ids.first;
					rightNameId = ids2.first;
				}
				else
				{
					leftNameId = ids2.first;
					rightNameId = ids.first;
				}
				if (OrgRecoglList[ids.second].Pos[0] < OrgRecoglList[ids2.second].Pos[0])
				{
					leftPriceId = ids.second;
					rightPriceId = ids2.second;
				}
				else
				{
					leftPriceId = ids2.second;
					rightPriceId = ids.second;
				}

				TitlePos t;
				t.NamePos.pos[0] = OrgRecoglList[leftNameId].charPos[OrgRecoglList[leftNameId].charPos.size() - 1].pos[0];
				t.NamePos.pos[1] = (OrgRecoglList[leftNameId].charPos[0].pos[1] + OrgRecoglList[rightNameId].charPos[0].pos[1]) / 2;
				t.NamePos.pos[2] = OrgRecoglList[rightNameId].charPos[0].pos[0] + OrgRecoglList[rightNameId].charPos[0].pos[2] - t.NamePos.pos[0];
				t.NamePos.pos[3] = (OrgRecoglList[leftNameId].charPos[0].pos[3] + OrgRecoglList[rightNameId].charPos[0].pos[3]) / 2;

				t.PricePos.pos[0] = OrgRecoglList[leftPriceId].charPos[OrgRecoglList[leftPriceId].charPos.size() - 1].pos[0];
				t.PricePos.pos[1] = (OrgRecoglList[leftPriceId].charPos[0].pos[1] + OrgRecoglList[leftPriceId].charPos[0].pos[1]) / 2;
				t.PricePos.pos[2] = OrgRecoglList[rightPriceId].charPos[0].pos[0] + OrgRecoglList[rightPriceId].charPos[0].pos[2] - t.PricePos.pos[0];
				t.PricePos.pos[3] = (OrgRecoglList[rightPriceId].charPos[0].pos[3] + OrgRecoglList[rightPriceId].charPos[0].pos[3]) / 2;

				rectangle(InputImage, Rect(t.NamePos.pos[0], t.NamePos.pos[1], t.NamePos.pos[2], t.NamePos.pos[3]), CV_RGB(255, 0, 0));
				rectangle(InputImage, Rect(t.PricePos.pos[0], t.PricePos.pos[1], t.PricePos.pos[2], t.PricePos.pos[3]), CV_RGB(255, 0, 0));

				m_titlePos.push_back(t);
				bFindNameSameLine = true;
				//	sameLineIdMap.erase(ids2.first);
			}
		}
		if (bFindNameSameLine)//暂时只考虑一个标题的情况
			break;
		else
		{
			int nameFindType = 0;
			//////cnt << "二次查找标题2===>" << OrgRecoglList[ids.first].RResult << " |  " << OrgRecoglList[ids.second].RResult << endl;
			bool matchedNameLeft, matchedPriceLeft;
			//如果名称是找到一个完整的，而金额不是完整的，则只需要拼接出金额
			if (OrgRecoglList[ids.first].RResult.find("名称") != string::npos)
				nameFindType = 0;
			else if (OrgRecoglList[ids.first].RResult.find("名") != string::npos)
				nameFindType = 1;
			else
				nameFindType = 2;

			if (OrgRecoglList[ids.second].RResult.find("金") != string::npos)
				matchedPriceLeft = true;
			else
				matchedPriceLeft = false;

			int nameMargin, priceMargin;

			cv::Mat thresholdedImg;
			cv::threshold(srcImg, thresholdedImg, 180, 255, CV_THRESH_BINARY);
			//	imwrite("D:\\thread.jpg", thresholdedImg);
			TitlePos t;
			switch (nameFindType)
			{
			case 0:
				t.NamePos.pos[0] = OrgRecoglList[ids.first].Pos[0];
				t.NamePos.pos[1] = OrgRecoglList[ids.first].Pos[1];
				t.NamePos.pos[2] = OrgRecoglList[ids.first].Pos[2];
				t.NamePos.pos[3] = OrgRecoglList[ids.first].Pos[3];
				break;
			case 1:
			{
					  nameMargin = FindNextBlackPt(thresholdedImg, OrgRecoglList[ids.first].Pos[0] + OrgRecoglList[ids.first].Pos[2] + 10,
						  OrgRecoglList[ids.first].Pos[1] + OrgRecoglList[ids.first].Pos[3] / 2, 1);

					  t.NamePos.pos[0] = OrgRecoglList[ids.first].charPos[OrgRecoglList[ids.first].charPos.size() - 1].pos[0];
					  t.NamePos.pos[1] = OrgRecoglList[ids.first].charPos[0].pos[1];
					  t.NamePos.pos[2] = nameMargin + OrgRecoglList[ids.first].charPos[0].pos[2] - t.NamePos.pos[0];
					  t.NamePos.pos[3] = OrgRecoglList[ids.first].charPos[0].pos[3];
			}
				break;
			case 2:
			{
					  nameMargin = FindNextBlackPt(thresholdedImg, OrgRecoglList[ids.first].Pos[0] - 10,
						  OrgRecoglList[ids.first].Pos[1] + OrgRecoglList[ids.first].Pos[3] / 2, 0);
					  t.NamePos.pos[0] = OrgRecoglList[ids.first].charPos[0].pos[2] - 15;
					  t.NamePos.pos[1] = OrgRecoglList[ids.first].charPos[0].pos[1];
					  t.NamePos.pos[2] = OrgRecoglList[ids.first].charPos[0].pos[0] + OrgRecoglList[ids.first].charPos[0].pos[2] - t.NamePos.pos[0];
					  t.NamePos.pos[3] = OrgRecoglList[ids.first].charPos[0].pos[3];
			}
				break;
			}
			if (matchedPriceLeft)
			{
				priceMargin = FindNextBlackPt(thresholdedImg, OrgRecoglList[ids.second].Pos[0] + OrgRecoglList[ids.second].Pos[2] + 10,
					OrgRecoglList[ids.second].Pos[1] + OrgRecoglList[ids.second].Pos[3] / 2, 1);

				t.PricePos.pos[0] = OrgRecoglList[ids.second].charPos[OrgRecoglList[ids.second].charPos.size() - 1].pos[0];
				t.PricePos.pos[1] = OrgRecoglList[ids.second].charPos[0].pos[1];
				t.PricePos.pos[2] = priceMargin + OrgRecoglList[ids.second].charPos[0].pos[2] - t.PricePos.pos[0];
				t.PricePos.pos[3] = OrgRecoglList[ids.second].charPos[0].pos[3];
			}
			else
			{
				priceMargin = FindNextBlackPt(thresholdedImg, OrgRecoglList[ids.second].Pos[0] - 10,
					OrgRecoglList[ids.second].Pos[1] + OrgRecoglList[ids.second].Pos[3] / 2, 0);
				t.PricePos.pos[0] = priceMargin - 15;
				t.PricePos.pos[1] = OrgRecoglList[ids.second].charPos[0].pos[1];
				t.PricePos.pos[2] = OrgRecoglList[ids.second].charPos[0].pos[0] + OrgRecoglList[ids.second].charPos[0].pos[2] - t.PricePos.pos[0];
				t.PricePos.pos[3] = OrgRecoglList[ids.second].charPos[0].pos[3];
			}

			rectangle(InputImage, Rect(t.NamePos.pos[0], t.NamePos.pos[1], t.NamePos.pos[2], t.NamePos.pos[3]), CV_RGB(255, 0, 0));
			rectangle(InputImage, Rect(t.PricePos.pos[0], t.PricePos.pos[1], t.PricePos.pos[2], t.PricePos.pos[3]), CV_RGB(255, 0, 0));

			m_titlePos.push_back(t);
		}
		//	////cnt << OrgRecoglList[ids.first].RResult << "_________" << OrgRecoglList[ids.second].RResult << endl;

	}
	//////cnt << nameCh.size();


}

//direction为0，向左搜，  为1向右
int CExtractInfo::FindNextBlackPt(const cv::Mat&thresholdedImg, int x, int y, int direction)
{
	if (direction == 0)
	{
		for (int i = x; i >= 0; i--)
		{
			int m1 = thresholdedImg.at<uchar>(y - 1, i * 3);
			int m2 = thresholdedImg.at<uchar>(y, i * 3);
			int m3 = thresholdedImg.at<uchar>(y + 1, i * 3);
			if (m1 == 0 || m2 == 0 || m3 == 0)
				return i;
		}
		return 0;
	}
	else
	{
		for (int i = x; i < thresholdedImg.cols; i++)
		{
			int m1 = thresholdedImg.at<uchar>(y - 1, i * 3);
			int m2 = thresholdedImg.at<uchar>(y, i * 3);
			int m3 = thresholdedImg.at<uchar>(y + 1, i * 3);
			if (m1 == 0 || m2 == 0 || m3 == 0)
				return i;
		}
		return thresholdedImg.cols - 1;
	}
}

int CExtractInfo::GetMatchedNameAndTotal()
{
	int nCount = 0;

	for (int i = 0; i < this->OrgRecoglList.size(); i++)
	{
		if (this->OrgRecoglList[i].Flag == 4 && this->OrgRecoglList[i].IsMatched == -1)
		{
			//	//cnt << this->OrgRecoglList[i].RResult << endl;
			int BestMapped = -1;
			float minDis = 1000000;
			for (int j = 0; j < this->OrgRecoglList.size(); j++)
			{
				if (this->OrgRecoglList[j].Flag == 6 && this->OrgRecoglList[j].IsMatched == -1)
				{
					//	//cnt <<i<< OrgRecoglList[i].RResult<<" , "<<j<< OrgRecoglList[j].RResult << endl;
					//	//cnt << OrgRecoglList[i].Pos[0] << " , " << OrgRecoglList[i].Pos[2] << " , " << OrgRecoglList[j].Pos[0]<< endl;
					////cnt << OrgRecoglList[i].Pos[0] << " , " << OrgRecoglList[i].Pos[2] << " , " << OrgRecoglList[j].Pos[0] << endl;
					//	////cnt << BestMapped<<"++"<< j << endl;
					float disY = fabs(this->OrgRecoglList[i].Pos[1] - this->OrgRecoglList[j].Pos[1]);
					//	printf("(%d,%d) (%f,%f)",i,j, this->OrgRecoglList[i].Pos[1], this->OrgRecoglList[j].Pos[1]);
					////cnt << i << ":" << OrgRecoglList[i].RResult << j << ":" << OrgRecoglList[j].RResult<< ":"<<disY<<endl;
					if (disY > 3 * this->OrgRecoglList[i].Pos[3])
						continue;

					if (this->OrgRecoglList[j].Pos[0] > this->OrgRecoglList[i].Pos[0] + this->OrgRecoglList[i].Pos[2] && IsSameLine(OrgRecoglList[i], OrgRecoglList[j]))
					{
						float dis = fabs(this->OrgRecoglList[i].Pos[0] - this->OrgRecoglList[j].Pos[0]) + disY;
						if (BestMapped == -1)
						{
							BestMapped = j;
							minDis = dis;
						}
						else
						{
							if (dis < minDis)
							{
								minDis = dis;
								BestMapped = j;
							}

						}
					}
					nCount++;
				}
			}

			if (BestMapped != -1)
			{
				MappedID mapped;

				//	////cnt << i << " " << BestMapped << endl;
				mapped.ID = i;
				mapped.MatchedID = BestMapped;
				mapped.UnitPriceID = -1;
				mapped.NumID = -1;
				mapped.flag = 0;

				this->OrgRecoglList[i].IsMatched = 0;  //置起已经配对标志位
				this->OrgRecoglList[BestMapped].IsMatched = 0;

				Point pt1, pt2;
				pt1.x = this->OrgRecoglList[i].Pos[0] + this->OrgRecoglList[i].Pos[2] / 2;
				pt1.y = this->OrgRecoglList[i].Pos[1] + this->OrgRecoglList[i].Pos[3] / 2;
				pt2.x = this->OrgRecoglList[BestMapped].Pos[0] + this->OrgRecoglList[BestMapped].Pos[2] / 2;
				pt2.y = this->OrgRecoglList[BestMapped].Pos[1] + this->OrgRecoglList[BestMapped].Pos[3] / 2;
				//	line(this->InputImage, pt1, pt2, CV_RGB(255, 0, 0));

				//找到单价所在位置
				//for (int j = 0; j < this->OrgRecoglList.size(); j++)
				//{
				//	if (this->OrgRecoglList[j].Flag == 5 &&
				//		this->OrgRecoglList[j].Pos[0] > this->OrgRecoglList[i].Pos[0] &&
				//		this->OrgRecoglList[j].Pos[0] < this->OrgRecoglList[BestMapped].Pos[0])
				//	{
				//		mapped.UnitPriceID = j;

				//		mapped.fPriceRate[0] = (this->OrgRecoglList[j].Pos[0] - this->OrgRecoglList[i].Pos[0]) / (this->OrgRecoglList[mapped.MatchedID].Pos[0] - this->OrgRecoglList[j].Pos[0]);

				//		if (fabs(this->OrgRecoglList[j].Pos[1] - this->OrgRecoglList[mapped.MatchedID].Pos[1]) > 0.01)
				//			mapped.fPriceRate[1] = (this->OrgRecoglList[j].Pos[1] - this->OrgRecoglList[i].Pos[1]) / (this->OrgRecoglList[j].Pos[1] - this->OrgRecoglList[mapped.MatchedID].Pos[1]);
				//		else
				//			mapped.fPriceRate[1] = 1;

				//		//			////cnt << mapped.fPriceRate[0] << "++++"<<mapped.fPriceRate[1] << "+++"<<this->OrgRecoglList[j].Pos[1] - this->OrgRecoglList[mapped.MatchedID].Pos[1]<<endl;
				//		break;
				//	}
				//}

				mappedSet.push_back(mapped);
			}
		}
	}

	RefineAutoTitle();

	////cnt << "mappedset_size" << mappedSet.size() << endl;
	//for (auto t : mappedSet)
	////cnt << "标题: " << this->OrgRecoglList[t.ID].RResult << "  " << OrgRecoglList[t.MatchedID].RResult << endl;
	return 1;
}

#if defined(_WIN32)
int CExtractInfo::InvTranFound(int found, string strInfo)
{
	int newfound = found;
	const char *ptrStr = strInfo.c_str();
	for (int i = 0; i < found; i++)
	{
		if ((ptrStr[i] & 0x80) != 0)  //发现汉字编码
		{
			//		////cnt << newfound << endl;
			newfound = newfound + 1;
			i = i + 1;
		}
	}

	return newfound;

}
int CExtractInfo::TranFound(int found, string strInfo)
{


	int newfound = found;
	const char *ptrStr = strInfo.c_str();
	for (int i = 0; i < found; i++)
	{
		if ((ptrStr[i] & 0x80) != 0)  //发现汉字编码
		{
			//	////cnt << newfound << endl;
			newfound = newfound - 1;
			i = i + 1;
		}
	}

	return newfound;

}
#else
int CExtractInfo::InvTranFound(int found, string strInfo)

{

	int newfound = found;

	const char *ptrStr = strInfo.c_str();

	for (int i = 0; i < found; i++)

	{

		if ((ptrStr[i] & 0x80) != 0)  //·¢ÏÖºº×Ö±àÂë

		{

			//		////cnt << newfound << endl;

			newfound = newfound + 2;

			i = i + 2;

		}

	}

	return newfound;
}

int CExtractInfo::TranFound(int found, string strInfo)

{

	int newfound = found;

	const char *ptrStr = strInfo.c_str();

	for (int i = 0; i < found; i++)

	{

		if ((ptrStr[i] & 0x80) != 0)  //·¢ÏÖºº×Ö±àÂë

		{

			//	////cnt << newfound << endl;

			newfound = newfound - 2;

			i = i + 2;

		}

	}
	return newfound;
}
#endif
// CheckChinese 判断中文，附加一些特殊字符
//返回值为1 通过
//InputStr: 输入的字符串
//bNum=1   插入的数字合法  '0' - '9'
//bChar=1  插入的字符合法  'a' - 'z'  'A' - 'Z'
//bAddLegal =1  允许特定字符
//LegalChar  特定字符集
int CExtractInfo::CheckChinese(string InputStr, bool bNum, bool bChar, bool bAddLegal, vector<char>& LegalChar)
{
	unsigned char tmp;
	unsigned char tmp1;
	for (int i = 1; i <= InputStr.length(); i++)
	{
		if (bNum)
		{
			if (InputStr[i] >= '0' && InputStr[i] <= '9')
			{
				continue;
			}
		}
		if (bChar)
		{
			if ((InputStr[i] >= 'A' && InputStr[i] <= 'Z') || (InputStr[i] >= 'a' && InputStr[i] <= 'z'))
			{
				continue;
			}
		}
		if (bAddLegal)
		{
			bool bConTinue = false;
			for (int j = 0; j < LegalChar.size(); j++)
			{
				if (LegalChar[j] == InputStr[i])
				{
					bConTinue = true;
					break;
				}
			}
			if (bConTinue) continue;
		}
		if (i == InputStr.length())         //汉字两个字节，一个字节肯定是不对的
		{
			return 0;
		}
		tmp = InputStr[i];
		tmp1 = InputStr[i + 1];
		if (tmp < 128 || tmp == 163 || tmp == 161)     //小于128 是ascii范围内不是中文, 163 是特殊字符,全角字符,161 全角的空格 ．＇｀
		{
			return 0;
		}
		else i++;   //一个汉字,两个字节
	}
	return 1;
}

int CExtractInfo::CheckRecogType(string strRecog, int &_charPosStartIndex, int & _charPosEndIndex)
{
	std::size_t found = strRecog.find("余姚");
	if (found != std::string::npos)
	{
		;
	}

	if (HospitalID == -1)
	{
		for (int i = 0; i < this->HospitalSet.size(); i++)
		{
			std::size_t found = strRecog.find(this->HospitalSet[i].hosName);
			if (found != std::string::npos)
			{
				HospitalID = i;

			}
		}
	}

	//首先判断是否是标题
	for (int i = 0; i < TitleSet.size(); i++)
	{
		std::size_t found = strRecog.find(TitleSet[i].Name);
		if (found != std::string::npos)
		{

			//如果出现了应该过滤的名字，则不作为对应的Flag
			bool findFilterName = false;
			for (auto &p : TitleSet[i].filterName)
			if (strRecog.find(p) != std::string::npos)
				findFilterName = true;
			if (!findFilterName)
			{
				_charPosStartIndex = TranFound(found, strRecog);//标题在字符串中的实际位置
				_charPosEndIndex = _charPosStartIndex + TitleSet[i].Name.length() / 2;
				return TitleSet[i].Flag;
			}
		}
	}

	return 0;
}
int CExtractInfo::DrawVerLine(int beginID, int endID)
{
	int minY = 100000, maxY = 0;
	int left = 10000;
	for (int i = beginID; i <= endID; i++)
	{
		if (this->RecoglList[i].Pos[0] < left)
			left = this->RecoglList[i].Pos[0];

		if (this->RecoglList[i].Pos[1] < minY)
			minY = this->RecoglList[i].Pos[1];

		if (this->RecoglList[i].Pos[1] > maxY)
			maxY = this->RecoglList[i].Pos[1];

	}

	Point pt1, pt2;

	pt1.x = left;
	pt1.y = minY;
	pt2.x = left;// +RecoglList[lastI].Pos[2];
	pt2.y = maxY;// +RecoglList[lastI].Pos[3];
	line(this->InputImage, pt1, pt2, CV_RGB(255, 0, 0));

	return 0;
}

void CExtractInfo::splite(const string& key_str, const string& split_flag, vector<string>& value_vec)
{
	string::iterator citr;
	int pre_ret = 0;
	int ret = key_str.find(split_flag, 0);
	if (ret == string::npos)
	{
		value_vec.push_back(key_str);
		return;
	}
	while (ret != string::npos)
	{
		string str = key_str.substr(pre_ret, ret - pre_ret);
		pre_ret = ret + split_flag.size();
		value_vec.push_back(str);
		ret = key_str.find(split_flag, pre_ret + 1);
	}
	string str = key_str.substr(pre_ret, ret - pre_ret);
	value_vec.push_back(str);
	int a = 0;
}



void CExtractInfo::LeftOutStr(string& src_str, const string& limit_str)
{
	vector<string> str_vec;
	splite(src_str, limit_str, str_vec);
	src_str.clear();
	auto citr = str_vec.begin();
	for (; citr != str_vec.end(); ++citr)
	{
		const string& str = *citr;
		src_str += str;
	}
}
void CExtractInfo::optimizeNumber(string& strPrice)
{
	////1去掉逗号
	this->LeftOutStr(strPrice, ",");

	//3去掉开头非数字
	//if (*strPrice.begin() < 48 || *strPrice.begin() > 57)
	//2去掉-

	std::size_t pos = strPrice.find("-");
	/*
	while (pos != string::npos)
	{
	string::iterator citr0 = strPrice.begin() + pos;
	strPrice.erase(citr0);
	pos = strPrice.find("-");
	}
	*/
	//4.将o替换成0

	pos = strPrice.find("o");
	while (pos != string::npos)
	{
		strPrice[pos] = '0';
		pos = strPrice.find("o");
	}
	//5如果有两个小数点，去掉前面所有的
	pos = strPrice.find(".");
	string::iterator citr = strPrice.begin();

	while (pos != string::npos)
	{
		//放在内部去查找lastpos是因为每次删除后lastPos就会发生变化，如果查找的第一个不等于最后一个就删除第一个等于就退出
		int lastPos = strPrice.find_last_of(".");
		citr = strPrice.begin() + pos;
		if (pos != lastPos)
		{
			//大于1是因为需要保留一个，
			strPrice.erase(citr);
		}
		else
		{
			break;
		}
		pos = strPrice.find(".");

	}
	//6如果数据大于五位，没有小数点，末尾是两个0，给00前面加上小数点
	if (strPrice.size() >= 5)
	{
		std::size_t pos1 = strPrice.find(".");
		if (pos1 != string::npos)
		{
			return;
		}
		//无逗号
		string strTmp(strPrice.begin() + strPrice.length() - 2, strPrice.end());
		if (strTmp == "00")
		{
			string strResult(strPrice.begin(), strPrice.begin() + strPrice.length() - 2);
			strResult += string(".00");
			strPrice = strResult;
		}

	}

}

//从字符串中获取数字信息并优化
#if defined(_WIN32)
bool CExtractInfo::getNumber(string strText, string& strNumber)
{
	//strText = "+++dddd123ss.455";
	//cnt << strText << "---";
	std::regex rx("([-，,.0-9]+)", std::regex_constants::icase);
	//	std::regex rx("([，,.0-9]+)");
	std::string::const_iterator start = strText.begin();
	std::string::const_iterator end = strText.end();
	smatch what;
	vector<string> strTmp;


	while (regex_search(start, end, what, rx))
	{
		string msg(what[0].first, what[0].second);

		strTmp.push_back(msg);
		vector<string> results;
		start = what[0].second;
	}
	if (strTmp.empty())
	{
		//不包含数字
		return false;
	}
	else
	{
		//包含数字
		strNumber = *strTmp.begin();
	}

	//cnt << strNumber << endl;
	return true;
}
#else
#include <regex.h>
bool CExtractInfo::getNumber(string strText, string& strNumber)
{
	string str;
	string number;
	int i = 0;
	while (strText[i] != 0)
	{
		if (strText[i] & 0x80)
		{
			str += strText[i];
			str += strText[i + 1];
			i += 2;
		}
		else
		{
			number += strText[i];
			i++;
		}
	}

	regex_t reg;
	bool bresult = true;
	regmatch_t match[10];
	int ret;

	//cnt << strText << endl;

	const char *pattern = "([-，,.0-9]+)";

	bool iErr = regcomp(&reg, pattern, REG_EXTENDED);
	if (iErr)
	{
		regfree(&reg);
		return false;
	}
	ret = regexec(&reg, number.c_str(), 10, match, 0);

	//cnt << strText << endl;

	if (ret != REG_NOMATCH)
	{
		int len = match[1].rm_eo - match[1].rm_so;
		char buf[1024] = { 0 };
		memcpy(buf, number.c_str() + match[1].rm_so, len);
		strNumber = buf;
	}
	else
	{
		bresult = false;
	}
	//cnt << strNumber << endl;
	regfree(&reg);
	return bresult;
}
#endif

void CExtractInfo::extractNumber(string strText, string& strPrice)
{

	//中文占两个字节，优化数字时先去除中文
	//string str;
	//int i = 0;
	//while (strText[i] != 0)
	//{
	//	if (strText[i] & 0x80)
	//	{
	//		str += strText[i];
	//		str += strText[i + 1];
	//		i += 2;
	//	}
	//	else
	//		i++;
	//}

	string str;
	string number;
	int i = 0;
	while (strText[i] != 0)
	{
		if (strText[i] & 0x80)
		{
			str += strText[i];
			str += strText[i + 1];
			i += 2;
		}
		else
		{
			number += strText[i];
			i++;
		}
	}

	string strNumber;
	strPrice = "";
	if (!IsValidNumber(number))
	{
		return;
	}
	//判断是不是有数字在最左侧
	if (getNumber(number, strNumber))
	{
		//如果是数字，对数字进行优化
		//CStringOperator::LeftOutStr(strNumber, ",");		
		this->optimizeNumber(strNumber);
		strPrice = strNumber;
	}

	return;

}

//int CExtractInfo::Detect()
//{
//	if (OrgRecoglList.empty())
//		return -1;
//	int maxLen = 0;
//	int maxStrId = 0;
//	for (int i = 0; i < OrgRecoglList.size(); i++)
//	{
//
//		int strCount = OrgRecoglList[i].charPos.size();
//		//int len = width>height ? width : height;
//		if (maxLen < strCount)
//		{
//			maxLen = strCount;
//			maxStrId = i;
//
//		}
//	}
//
//	////cnt << OrgRecoglList[maxStrId].RResult << "zifushu" << OrgRecoglList[maxStrId].charPos.size() << endl;
//	int imgWidth = InputImage.cols;
//	int imgHeight = InputImage.rows;
//
//	auto charPosVec = OrgRecoglList[maxStrId].charPos;
//	int strWidth = abs(charPosVec[charPosVec.size() - 1].pos[0] + charPosVec[charPosVec.size() - 1].pos[2] - charPosVec[0].pos[0]);
//	int strHeight = abs(charPosVec[charPosVec.size() - 1].pos[1] + charPosVec[charPosVec.size() - 1].pos[3] - charPosVec[0].pos[1]);
//
//	printf("w%d,h%d", strWidth, strHeight);
//	if (strWidth < strHeight) //如果宽度小于高度，则说明需要逆时针或顺时针旋转
//	{
//		if (OrgRecoglList[maxStrId].Pos[0] < imgWidth / 2)
//			return 90;//逆时针旋转90
//		else
//			return -90;//顺时针旋转90
//
//	}
//	else if (OrgRecoglList[maxStrId].Pos[1] > imgHeight / 2 || OrgRecoglList[maxStrId].Pos[0] < imgWidth / 2)
//	{
//		return 0;//不需要旋转
//	}
//	else
//	{
//		return 180;//旋转180"
//	}
//
//	//system("pause");
//	return 0;
//}

#ifndef AUTO_RECOG_TITLE
int CExtractInfo::PushRecogResult2(string strText, string strPos, vector<PosOfChar>& charPos)
{
	if (strText == "中心静脉穿刺置管术")
	{
		int kk = 0;
		kk++;
	}
	RecogResult elem;

	int s[4];
	sscanf(strPos.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);
	elem.RResult = strText;
	elem.charPos.assign(charPos.begin(), charPos.end());

	int top = 1000000, bottom = -1;
	for (int i = 0; i < elem.charPos.size(); i++)
	{
		if (top > elem.charPos[i].pos[1])
			top = elem.charPos[i].pos[1];

		if (bottom < elem.charPos[i].pos[3])
			bottom = elem.charPos[i].pos[3];
	}
	elem.Pos[0] = elem.charPos[0].pos[0];
	elem.Pos[1] = top;// elem.charPos[0].pos[1] + 2;
	elem.Pos[2] = elem.charPos[elem.charPos.size() - 1].pos[0] + elem.charPos[elem.charPos.size() - 1].pos[2] - elem.charPos[0].pos[0];
	elem.Pos[3] = bottom;// elem.charPos[0].pos[3];

	//elem.Pos[0] = elem.charPos[0].pos[0];
	//elem.Pos[1] = elem.charPos[0].pos[1] + 2;
	//elem.Pos[2] = elem.charPos[elem.charPos.size() - 1].pos[0] + elem.charPos[elem.charPos.size() - 1].pos[2] - elem.charPos[0].pos[0];
	//elem.Pos[3] = elem.charPos[0].pos[3];


	/*	if (elem.RResult.find("989") != string::npos)
	{
	////cnt << elem.RResult << endl;
	}*/

	/*Rect rect;
	for (int j = 0; j < elem.charPos.size(); j++)
	{
	rect.x = elem.charPos[j].pos[0];
	rect.y = elem.charPos[j].pos[1];
	rect.width = elem.charPos[j].pos[2];
	rect.height = elem.charPos[j].pos[3];
	rectangle(this->InputImage, rect, CV_RGB(0, 255, 0));
	}*/
	//	DrawRect(elem, 3);
	vector<RecogResult> subEleSet;

	vector<RecogResult> FinalelemSet;
	this->SplitRegions(FinalelemSet, elem);//此处将文本以空格冒号等分割开来




	/*
	vector<RecogResult> FinalelemSet;
	this->SplitRegions(FinalelemSet, elem);
	for (int i = 0; i < FinalelemSet.size(); i++)
	{
	//FinalelemSet[i].Flag = this->CheckRecogType(FinalelemSet[i].RResult, _charPosIndex, _charEndPosIndex);
	//	FinalelemSet[i].IsMatched = -1;
	//	RecoglList.push_back(FinalelemSet[i]);

	//找出标题在识别字符串中的实际位置
	int _charPosIndex = 0;//
	int _charEndPosIndex = 0;

	FinalelemSet[i].Flag = this->CheckRecogType(FinalelemSet[i].RResult, _charPosIndex, _charEndPosIndex);
	if ((FinalelemSet[i].Flag == 11 || FinalelemSet[i].Flag == 12) &&
	FinalelemSet[i].RResult.length() < 4)//"名"//称
	CandTitleList.push_back(FinalelemSet[i]);

	if (FinalelemSet[i].Flag == 4 || FinalelemSet[i].Flag == 6)
	{
	auto tempEle = FinalelemSet[i];
	SplitTitle(tempEle, _charPosIndex, _charEndPosIndex);

	}
	else
	{
	//DrawRect(FinalelemSet[i]);
	FinalelemSet[i].IsMatched = -1;
	RecoglList.push_back(FinalelemSet[i]);
	}
	*/
	if (isManual == 1)
	{
		RecoglList.push_back(elem);
	}
	//再将文本根据标题截取，最终结果只保存可能为名称与金额的项
	for (auto ele : FinalelemSet)
	{
		SubString(subEleSet, ele);
	}


	for (int i = 0; i < subEleSet.size(); i++)
	{
		if (subEleSet[i].RResult.find("一级") != string::npos)
		{
			int a = 0;
		}


		/*	if (elem.RResult.find("维生素") != std::string::npos)
		////cnt << elem.RResult << endl;*/


		subEleSet[i].IsMatched = -1;
		if (subEleSet[i].Flag == TYPE_TITLE)
		{
			if (IsValidElem(subEleSet[i].RResult) == -1)//标题必须要有中文
			{
				int size = subEleSet[i].RResult.find("一");
				if (size == 0 && subEleSet[i].RResult.length() > 2)
				{
					subEleSet[i].Pos[1] = subEleSet[i].charPos[1].pos[1];
					subEleSet[i].Pos[3] = subEleSet[i].charPos[1].pos[3];
					//		//cnt << subEleSet[i].RResult << endl;
				}

				v_title.push_back(subEleSet[i]);

			}
		}
		else if (subEleSet[i].Flag == TYPE_PRICE)
		{
			//替换￥，不然会识别为有中文而不添加到待选项中
			replace_all(subEleSet[i].RResult, "￥", "");
			//金额中识别出不是数字不添加
			//WYP 去除中文字符
			extractNumber(subEleSet[i].RResult, subEleSet[i].RResult);
			//	//cnt << subEleSet[i].RResult << endl;
			if (IsValidElem(subEleSet[i].RResult) == 0)
			{
				auto ele = subEleSet[i];
				//HandleLongPrice(ele);//TODO 把尾部过长的部分去掉
				if (traitNumber(ele.RResult) && ele.Pos[2] > 0)
				{
					v_price.push_back(ele);
					m_nPriceCount++;
				}
			}

		}
		else if (subEleSet[i].Flag == TYPE_DJ)
		{
			//替换￥，不然会识别为有中文而不添加到待选项中
			replace_all(subEleSet[i].RResult, "￥", "");
			//金额中识别出不是数字不添加
			//WYP 去除中文字符
			extractNumber(subEleSet[i].RResult, subEleSet[i].RResult);
			if (IsValidElem(subEleSet[i].RResult) == 0)
			{
				auto ele = subEleSet[i];
				//HandleLongPrice(ele);//TODO 把尾部过长的部分去掉
				if (traitNumber(ele.RResult))
					v_dj.push_back(ele);
			}

		}
		else if (subEleSet[i].Flag == TYPE_NUM)
		{
			//替换￥，不然会识别为有中文而不添加到待选项中
			replace_all(subEleSet[i].RResult, "￥", "");
			//金额中识别出不是数字不添加
			//WYP 去除中文字符
			extractNumber(subEleSet[i].RResult, subEleSet[i].RResult);
			if (IsValidElem(subEleSet[i].RResult) == 0)
			{
				auto ele = subEleSet[i];
				//HandleLongPrice(ele);//TODO 把尾部过长的部分去掉
				if (traitNumber(ele.RResult))
					v_num.push_back(ele);
			}

		}
		//RecoglList.push_back(subEleSet[i]);


		//	DrawRect(subEleSet[i]);
	}
	return 0;
}
void CExtractInfo::HandleLongPrice(RecogResult & price)
{
	//如果某一个字符距离前一个字符两倍远，则认为它不属于价格里的字符了
	if (price.charPos.size() == 0)
		return;
	int dist = price.charPos[0].pos[2];
	for (int i = 1; i < price.charPos.size(); i++)
	{
		if (price.charPos[i].pos[0] - price.charPos[i - 1].pos[0] >= 2 * dist)
		{
			price.charPos.assign(price.charPos.begin(), price.charPos.begin() + i);
			price.Pos[2] = price.charPos[i - 1].pos[0] + price.charPos[i - 1].pos[2] - price.charPos[0].pos[0];
			price.RResult.assign(price.RResult.begin(), price.RResult.begin() + i);
			break;
		}
		dist = price.charPos[i].pos[2];
	}
}
void CExtractInfo::replace_all(string& str, const string& old_value, const string& new_value)
{
	while (true) {
		string::size_type pos(0);
		if ((pos = str.find(old_value)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else break;
	}
}
string CExtractInfo::formatNumber(string s, int dotPos)
{
	string sPrefix = s.substr(0, s.length() - dotPos - 1);
	string sExt = s.substr(s.length() - dotPos - 1);
	replace_all(sPrefix, ",", "");
	//	////cnt << sPrefix << endl;;

	string res;
	res.reserve(16);
	int n = 0;
	for (int index = sPrefix.size() - 1; index >= 0; index--)
	{
		if (n == 3)
		{
			res += ',';

			n = 0;
			index++;
			continue;
		}
		res += sPrefix[index];
		n++;
	}
	reverse(res.begin(), res.end());
	res += sExt;
	return res;
}
bool CExtractInfo::traitNumber(string & price)
{
	string s = price;
	replaceInvalidCharater(s);
	int priceFormat = 4;//SettingConfig::getInstance()->PriceFormat();
	char buf[64] = { 0 };
	int n = 0;
	bool bFindComma = false;//是否找到逗号
	bool bFindDot = false;

	bool bFindMinus = false;//第二个负号
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '-')
		{
			if (bFindMinus)
				s[i] = ' ';
			bFindMinus = true;

		}
	}

	if (s.empty())
		return true;
	//-.56情况
	for (int i = 0; i < s.length() - 1; i++)
	{
		if (s[i] == '-' && s[i + 1] == '.')
		{
			s[i] = ' ';
		}
	}
	//-
	if (s.size() == 1)
	if (s[0] == '-')
		s = ' ';

	if (s.empty())
		return true;
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
		{
			buf[n++] = s[i];
		}
		if (s[i] == '.')
		{
			buf[n++] = s[i];
			bFindDot = true;
		}
		if (s[i] == ',')
			bFindComma = true;
		if (s[i] == '-')
		{
			buf[n++] = s[i];
		}
	}
	buf[n] = '\0';
	if (n == 0)
	{
		strcpy(buf, "0.00");
		price = string(buf);
		return false;
	}
	//此时已经过滤掉所有非数字与点的字符

	if (priceFormat == 0)
	{
		int price = atoi(buf);
		sprintf(buf, "%d", price);
	}
	else if (priceFormat == 1)
	{
		if (bFindDot)
		{
			float price = atof(buf);
			sprintf(buf, "%.1f", price);
		}
		else
			strcat(buf, ".0");
	}
	else if (priceFormat == 2)
	{
		if (bFindDot)
		{
			double price = atof(buf);
			sprintf(buf, "%.2f", price);
		}
		else
			strcat(buf, ".00");
	}
	else if (priceFormat == 3)
	{
		if (bFindDot)
		{
			double price = atof(buf);
			sprintf(buf, "%.3f", price);
		}
		else
			strcat(buf, ".000");
	}
	else if (priceFormat == 4)
	{
		if (bFindDot)
		{
			double price = atof(buf);
			sprintf(buf, "%.4f", price);
		}
		else
			strcat(buf, ".0000");
	}



	s = string(buf);
	//如果本来有逗号，则还需要格式化为带逗号的格式
	/*if (bFindComma)
	{
	if (priceFormat != -1)
	s = formatNumber(s, priceFormat);
	else
	{
	int dotPos = s.rfind('.');
	if (dotPos != string::npos)
	s = formatNumber(s, s.length() - dotPos - 1);
	else
	s = formatNumber(s, 0);
	}
	}
	*/
	price = s;
	return true;
}
bool CExtractInfo::traitNumber(string & price, int type)
{
	string s = price;
	replaceInvalidCharater(s);
	int priceFormat = type;//SettingConfig::getInstance()->PriceFormat();
	char buf[64] = { 0 };
	int n = 0;
	bool bFindComma = false;//是否找到逗号
	bool bFindDot = false;
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
		{
			buf[n++] = s[i];
		}
		if (s[i] == '.')
		{
			buf[n++] = s[i];
			bFindDot = true;
		}
		if (s[i] == ',')
			bFindComma = true;
		if (s[i] == '-')
		{
			buf[n++] = s[i];
		}
	}
	buf[n] = '\0';
	if (n == 0)
	{
		strcpy(buf, "0.00");
		price = string(buf);
		return false;
	}
	//此时已经过滤掉所有非数字与点的字符

	if (priceFormat == 0)
	{
		int price = atoi(buf);
		sprintf(buf, "%d", price);
	}
	else if (priceFormat == 1)
	{
		if (bFindDot)
		{
			float price = atof(buf);
			sprintf(buf, "%.1f", price);
		}
		else
			strcat(buf, ".0");
	}
	else if (priceFormat == 2)
	{
		if (bFindDot)
		{
			double price = atof(buf);
			sprintf(buf, "%.2f", price);
		}
		else
			strcat(buf, ".00");
	}
	else if (priceFormat == 3)
	{
		if (bFindDot)
		{
			double price = atof(buf);
			sprintf(buf, "%.3f", price);
		}
		else
			strcat(buf, ".000");
	}
	else if (priceFormat == 4)
	{
		if (bFindDot)
		{
			double price = atof(buf);
			sprintf(buf, "%.4f", price);
		}
		else
			strcat(buf, ".0000");
	}



	s = string(buf);

	price = s;
	return true;
}

void CExtractInfo::replaceInvalidCharater(string & str)
{
	//, -> .
	int pos = str.find_last_of(',');
	if (pos != string::npos && pos == str.length() - 3)
	{
		str.replace(pos, 1, ".");
	}
	//替换表
	map<char, string> replaceMap;
	replaceMap.emplace('Q', "0");
	replaceMap.emplace('O', "0");
	replaceMap.emplace('o', "0");

	for (auto ele : replaceMap)
	{
		int pos = str.find(ele.first);
		if (pos != string::npos)
		{
			str.replace(pos, 1, ele.second);
		}
	}
}
void CExtractInfo::SubString(vector<RecogResult>& subEleSet, RecogResult elem)
{
	//由于多个标题时如果在同一行，需要遍历标题，而不在同一行不需要，所以下面判断一下
	//直接return是为了避免竖着有多个标题时重复添加项，用break是为了标题与金额连在一起时需要多次匹配
#define FIND_OPERATE \
	if (bSameLine)\
	continue; \
	else\
	return; \

	bool bSameLine = false;
	if (m_titlePos.size() > 1)
	{
		if (abs(m_titlePos[0].NamePos.pos[1] - m_titlePos[1].NamePos.pos[1]) < 30)
			bSameLine = true;
	}

	for (int i = 0; i < m_titlePos.size(); i++)
	{
		elem.titleID = i;//此标题ID用于按标题排序用
		PosOfChar namePos, pricePos;
		for (int m = 0; m < 4; m++)
		{
			namePos.pos[m] = m_titlePos[i].NamePos.pos[m];
			pricePos.pos[m] = m_titlePos[i].PricePos.pos[m];

		}


		/*char szNamePos[1024] = { 0 };
		sprintf(szNamePos, "NamePos========> %d,%d,%d,%d\n", namePos.pos[0], namePos.pos[1], namePos.pos[2], namePos.pos[3]);
		////cnt << szNamePos;*/

		/*namePos = m_titlePos[i].NamePos;
		pricePos = m_titlePos[i].PricePos;*/
		/*for (int j = 0; j < OrgRecoglList.size(); j++)
		{
		auto elem = OrgRecoglList[j];*/
		if (elem.RResult.find("维生素") != std::string::npos || elem.RResult.find("16") != std::string::npos)
		{
			////cnt << elem.RResult << endl;
			////cnt << namePos.pos[0] << "--" << namePos.pos[1] << namePos.pos[2] << "--" << namePos.pos[3] << endl;
			////cnt << elem.Pos[0] << "--" << elem.Pos[1] << elem.Pos[2] << "--" << elem.Pos[3] << endl;
		}
		if (elem.Pos[0] >= namePos.pos[0] &&
			elem.Pos[0]< namePos.pos[0] + namePos.pos[2] &&
			elem.Pos[1] + 5 > namePos.pos[1] + namePos.pos[3] &&
			elem.Pos[0] + elem.Pos[2] <= namePos.pos[0] + namePos.pos[2])//刚好在项目名称下面，且不需要截取
		{
			//////cnt << elem.RResult << endl;
			elem.Flag = TYPE_TITLE;
			subEleSet.push_back(elem);
			FIND_OPERATE
				//DrawRect(elem);
		}
		else if (elem.Pos[0] >= pricePos.pos[0] &&
			elem.Pos[0]< pricePos.pos[0] + namePos.pos[2] &&
			elem.Pos[1] + 5 > pricePos.pos[1] + pricePos.pos[3] &&
			elem.Pos[0] + elem.Pos[2] <= pricePos.pos[0] + pricePos.pos[2])//刚好在价格名称下面，且不需要截取
		{
			elem.Flag = TYPE_PRICE;
			subEleSet.push_back(elem);
			FIND_OPERATE
				//DrawRect(elem);
		}
		else if (elem.Pos[0] >= namePos.pos[0] &&
			elem.Pos[0] < namePos.pos[0] + namePos.pos[2] &&
			elem.Pos[1] + 5 > namePos.pos[1] + namePos.pos[3] &&
			elem.Pos[0] + elem.Pos[2] >= namePos.pos[0] + namePos.pos[2])//在项目名称下面，但右边超过边缘
		{
			//	DrawRect(elem);
#ifdef PRINT_CUT_RES
			////cnt << "截取名称右\t" << elem.RResult << endl;
#endif
			this->SplitRegions2(subEleSet, elem, 1, i);
			FIND_OPERATE
		}
		else if (elem.Pos[0] + elem.Pos[2] <= namePos.pos[0] + namePos.pos[2] &&//在项目名称下面，但左边超过边缘
			elem.Pos[1] + 5 > namePos.pos[1] + namePos.pos[3] &&
			elem.Pos[0] + elem.Pos[2] > namePos.pos[0] &&
			elem.Pos[0] <= namePos.pos[0])
		{
			//	DrawRect(elem);
#ifdef PRINT_CUT_RES
			////cnt << "截取名称左\t" << elem.RResult << endl;
#endif
			this->SplitRegions2(subEleSet, elem, 2, i);
			FIND_OPERATE
		}
		else if (elem.Pos[0] >= pricePos.pos[0] &&
			elem.Pos[0] < pricePos.pos[0] + pricePos.pos[2] &&
			elem.Pos[1] + 5 > pricePos.pos[1] + pricePos.pos[3] &&
			elem.Pos[0] + elem.Pos[2] >= pricePos.pos[0] + pricePos.pos[2])//在价格名称下面，但右边超过边缘
		{
#ifdef PRINT_CUT_RES
			////cnt << "截取价格右\t" << elem.RResult << endl;
#endif
			this->SplitRegions2(subEleSet, elem, 3, i);
			FIND_OPERATE
		}
		else if (elem.Pos[0] + elem.Pos[2] <= pricePos.pos[0] + pricePos.pos[2] &&//在价格名称下面，但左边超过边缘
			elem.Pos[1] + 5 > pricePos.pos[1] + pricePos.pos[3] &&
			elem.Pos[0] + elem.Pos[2] > pricePos.pos[0] &&
			elem.Pos[0] <= pricePos.pos[0])
		{
#ifdef PRINT_CUT_RES
			////cnt << "截取价格左\t" << elem.RResult << endl;
#endif
			/*错位情况
			12344  //价格标题位置
			2567     //价格明细位置
			*/
			if (elem.RResult.find("48") != string::npos)
			{
				//cnt << elem.Pos[0] << "++" << elem.Pos[1] << "++" << elem.Pos[2] << "++" << elem.Pos[3] << endl;
				//cnt << m_titlePos[0].PricePos.pos[0] << "++" << m_titlePos[0].PricePos.pos[1] << "++" << m_titlePos[0].PricePos.pos[2] << "++" << m_titlePos[0].PricePos.pos[3] << endl;
			}
			this->SplitRegions2(subEleSet, elem, 4, i);
			FIND_OPERATE
		}
		//对于项目名称识别过长的截取中间部分
		else if (elem.Pos[0] <= namePos.pos[0] &&
			elem.Pos[0] + elem.Pos[2] >= namePos.pos[0] + namePos.pos[2] &&
			elem.Pos[1] + 5 > namePos.pos[1] + namePos.pos[3])
		{
			this->SplitRegions2(subEleSet, elem, 5, i);
			FIND_OPERATE
		}
		//对于价格名称识别过长的截取中间部分
		else if (elem.Pos[0] <= pricePos.pos[0] &&
			elem.Pos[0] + elem.Pos[2] >= pricePos.pos[0] + pricePos.pos[2] &&
			elem.Pos[1] + 5 > pricePos.pos[1] + pricePos.pos[3])
		{
			this->SplitRegions2(subEleSet, elem, 6, i);
			FIND_OPERATE
		}
		//}
	}
}
/*
int CExtractInfo::SplitRegions2(vector<RecogResult>& subEleSet, RecogResult elem, int type, int titleIndex)
{
//ofstream outfile;//创建文件
//outfile.open("111.txt");

//outfile << titleIndex << endl;
//outfile.close();

int charPosIndex = 0;
int charPosIndex2 = 0;//只有在名称左右边都超过标题时用到
bool bOK = false;
RecogResult subEleResult;

auto namePos = m_titlePos[titleIndex].NamePos;
auto pricePos = m_titlePos[titleIndex].PricePos;
#pragma region
if (type == 1)//在项目名称下面，但右边超过边缘
{

for (charPosIndex = 0; charPosIndex<elem.charPos.size(); charPosIndex++)
{
if (elem.charPos[charPosIndex].pos[0] + elem.charPos[charPosIndex].pos[2] >= namePos.pos[0] + namePos.pos[2])
{
bOK = true;
break;
}
}
}

else if (type == 2)//在项目名称下面，但左边超过边缘
{

for (charPosIndex = 0; charPosIndex<elem.charPos.size(); charPosIndex++)
{
//////cnt << charPosIndex << endl;
if (elem.charPos[charPosIndex].pos[0] >= namePos.pos[0])
{
bOK = true;
break;
}
}
}
else if (type == 3)//在价格名称下面，但右边超过边缘
{
//kang -2 右侧超过两个字符再截取
for (charPosIndex = 0; charPosIndex<elem.charPos.size() - 2; charPosIndex++)
{
if (elem.charPos[charPosIndex].pos[0] + elem.charPos[charPosIndex].pos[2] >= pricePos.pos[0] + pricePos.pos[2])
{
bOK = true;
break;
}
}

}
else if (type == 4)//在价格名称下面，但左边超过边缘
{
//kang -1 左侧超过一个字符再截取
for (charPosIndex = 0; charPosIndex<elem.charPos.size()-1; charPosIndex++)
{
//	////cnt << charPosIndex << endl;
if (elem.charPos[charPosIndex].pos[0] >= pricePos.pos[0])
{
bOK = true;
break;
}
}
}
else if (type == 5)//对于项目名称识别过长的截取中间部分
{
//找左边起始点
for (charPosIndex = 0; charPosIndex<elem.charPos.size(); charPosIndex++)
{
//////cnt << charPosIndex << endl;
if (elem.charPos[charPosIndex].pos[0] + elem.charPos[charPosIndex].pos[2] >= namePos.pos[0])
{
//bOK = true;
break;
}
}
//找右边起始点
for (charPosIndex2 = 0; charPosIndex2<elem.charPos.size(); charPosIndex2++)
{
if (elem.charPos[charPosIndex2].pos[0] + elem.charPos[charPosIndex2].pos[2] >= namePos.pos[0] + namePos.pos[2])
{
bOK = true;
break;
}
}

}
else if (type == 6)//对于价格识别过长的截取中间部分
{
//找左边起始点
for (charPosIndex = 0; charPosIndex<elem.charPos.size(); charPosIndex++)
{
//////cnt << charPosIndex << endl;
if (elem.charPos[charPosIndex].pos[0] + elem.charPos[charPosIndex].pos[2] >= pricePos.pos[0])
{
//bOK = true;
break;
}
}
//找右边起始点
for (charPosIndex2 = 0; charPosIndex2<elem.charPos.size(); charPosIndex2++)
{
if (elem.charPos[charPosIndex2].pos[0] + elem.charPos[charPosIndex2].pos[2] >= pricePos.pos[0] + pricePos.pos[2])
{
bOK = true;
break;
}
}

}
//}

if (bOK)
{
if (type == 2 && charPosIndex>0)//项目名称左偏移一个字符
{
charPosIndex--;
}
int charfound = TranFound2(charPosIndex, elem.RResult);
//对于价格识别也向后偏移一个字符，但如果是中文字符就不偏移了
if (type == 3 && charPosIndex != elem.charPos.size() - 1)
{
if (elem.RResult[charfound + 1] & 0x80 == 0)
charPosIndex++;
}

if (type == 1 || type == 3)//截取右边,保留左边部分
{
//////cnt << "charPosIndex: " << charPosIndex << endl;
subEleResult.charPos.resize(charPosIndex);
subEleResult.charPos.assign(elem.charPos.begin(), elem.charPos.begin() + charPosIndex);

subEleResult.RResult.assign(elem.RResult.begin(), elem.RResult.begin() + charfound);

subEleResult.Pos[0] = elem.Pos[0]; subEleResult.Pos[1] = elem.Pos[1];
subEleResult.Pos[2] = elem.charPos[charPosIndex].pos[0] - elem.charPos[0].pos[0]; subEleResult.Pos[3] = elem.Pos[3];


//分割完第一个区域
//subEleSet.push_back(subEleResult);
}
else if (type == 2 || type == 4)//截取左边，保留右边部分
{

//	////cnt << "src: " << elem.RResult << " ";
subEleResult.charPos.resize(elem.charPos.size() - charPosIndex);
subEleResult.charPos.assign(elem.charPos.begin() + charPosIndex, elem.charPos.end());
subEleResult.RResult.assign(elem.RResult.begin() + charfound, elem.RResult.end());

subEleResult.Pos[0] = elem.charPos[charPosIndex].pos[0]; subEleResult.Pos[1] = elem.charPos[charPosIndex].pos[1];
subEleResult.Pos[2] = elem.Pos[0] + elem.Pos[2] - elem.charPos[charPosIndex].pos[0]; subEleResult.Pos[3] = elem.Pos[3];



//	////cnt << "charfound" << charfound << " res：" << subEleResult.RResult << endl;
//subEleSet.push_back(subEleResult);
}
else
{
int charfound2 = TranFound2(charPosIndex2, elem.RResult);
//////cnt << charfound << "," << charfound2 << "," << charPosIndex << "," << charPosIndex2 << endl;
subEleResult.charPos.resize(charPosIndex2 - charPosIndex);
subEleResult.charPos.assign(elem.charPos.begin() + charPosIndex, elem.charPos.begin() + charPosIndex2);
subEleResult.RResult.assign(elem.RResult.begin() + charfound, elem.RResult.begin() + charfound2);

subEleResult.Pos[0] = elem.charPos[charPosIndex].pos[0]; subEleResult.Pos[1] = elem.charPos[charPosIndex].pos[1];
subEleResult.Pos[2] = elem.charPos[charPosIndex2].pos[0] - elem.charPos[charPosIndex].pos[0]; subEleResult.Pos[3] = elem.Pos[3];
//subEleSet.push_back(subEleResult);
}
if (type == 1 || type == 2 || type == 5)
subEleResult.Flag = TYPE_TITLE;
else
subEleResult.Flag = TYPE_PRICE;
subEleResult.titleID = titleIndex;
subEleSet.push_back(subEleResult);
#ifdef PRINT_CUT_RES
////cnt << "截取结果" << subEleResult.RResult << endl;
#endif
}

else
{
int charfound = TranFound2(charPosIndex + 2, elem.RResult);

if (type == 3)//截取不右边,保留左边部分
{
//////cnt << "charPosIndex: " << charPosIndex << endl;
subEleResult.charPos.resize(charPosIndex);
subEleResult.charPos.assign(elem.charPos.begin(), elem.charPos.begin() + charPosIndex);
subEleResult.RResult.assign(elem.RResult.begin(), elem.RResult.begin() + charfound);

subEleResult.Pos[0] = elem.Pos[0]; subEleResult.Pos[1] = elem.Pos[1];
subEleResult.Pos[2] = elem.Pos[2]; subEleResult.Pos[3] = elem.Pos[3];
}
if (type == 3)
subEleResult.Flag = TYPE_PRICE;
subEleSet.push_back(subEleResult);
}

return 1;
}
*/

int CExtractInfo::SplitRegions2(vector<RecogResult>& subEleSet, RecogResult elem, int type, int titleIndex)
{

	int charPosIndex = 0;
	int charPosIndex2 = 0;//只有在名称左右边都超过标题时用到
	bool bOK = false;
	RecogResult subEleResult;

	auto namePos = m_titlePos[titleIndex].NamePos;
	auto pricePos = m_titlePos[titleIndex].PricePos;
#pragma region
	if (type == 1)//在项目名称下面，但右边超过边缘
	{

		for (charPosIndex = 0; charPosIndex < elem.charPos.size(); charPosIndex++)
		{
			if (elem.charPos[charPosIndex].pos[0] + elem.charPos[charPosIndex].pos[2] >= namePos.pos[0] + namePos.pos[2])
			{
				bOK = true;
				break;
			}
		}
	}

	else if (type == 2)//在项目名称下面，但左边超过边缘
	{

		for (charPosIndex = 0; charPosIndex < elem.charPos.size(); charPosIndex++)
		{
			//////cnt << charPosIndex << endl;
			if (elem.charPos[charPosIndex].pos[0] >= namePos.pos[0])
			{
				bOK = true;
				break;
			}
		}
	}
	else if (type == 3)//在价格名称下面，但右边超过边缘
	{

		for (charPosIndex = 0; charPosIndex < elem.charPos.size(); charPosIndex++)
		{
			if (elem.charPos[charPosIndex].pos[0] + elem.charPos[charPosIndex].pos[2] >= pricePos.pos[0] + pricePos.pos[2])
			{
				bOK = true;
				break;
			}
		}
	}
	else if (type == 4)//在价格名称下面，但左边超过边缘
	{
		for (charPosIndex = 0; charPosIndex < elem.charPos.size(); charPosIndex++)
		{
			//	////cnt << charPosIndex << endl;
			if (elem.charPos[charPosIndex].pos[0] >= pricePos.pos[0])
			{
				bOK = true;
				break;
			}
		}
	}
	else if (type == 5)//对于项目名称识别过长的截取中间部分
	{
		//找左边起始点
		for (charPosIndex = 0; charPosIndex < elem.charPos.size(); charPosIndex++)
		{
			//////cnt << charPosIndex << endl;
			if (elem.charPos[charPosIndex].pos[0] + elem.charPos[charPosIndex].pos[2] >= namePos.pos[0])
			{
				//bOK = true;
				break;
			}
		}
		//找右边起始点
		for (charPosIndex2 = 0; charPosIndex2 < elem.charPos.size(); charPosIndex2++)
		{
			if (elem.charPos[charPosIndex2].pos[0] + elem.charPos[charPosIndex2].pos[2] >= namePos.pos[0] + namePos.pos[2])
			{
				bOK = true;
				break;
			}
		}

	}
	else if (type == 6)//对于价格识别过长的截取中间部分
	{
		//找左边起始点
		for (charPosIndex = 0; charPosIndex < elem.charPos.size(); charPosIndex++)
		{
			//////cnt << charPosIndex << endl;
			if (elem.charPos[charPosIndex].pos[0] + elem.charPos[charPosIndex].pos[2] >= pricePos.pos[0])
			{
				//bOK = true;
				break;
			}
		}
		//找右边起始点
		for (charPosIndex2 = 0; charPosIndex2 < elem.charPos.size(); charPosIndex2++)
		{
			if (elem.charPos[charPosIndex2].pos[0] + elem.charPos[charPosIndex2].pos[2] >= pricePos.pos[0] + pricePos.pos[2])
			{
				bOK = true;
				break;
			}
		}

	}
	//}

	if (bOK)
	{
		if (type == 2 && charPosIndex > 0)//项目名称左偏移一个字符
		{
			charPosIndex--;
		}
		int charfound = TranFound2(charPosIndex, elem.RResult);
		//对于价格识别也向后偏移一个字符，但如果是中文字符就不偏移了
		if (type == 3 && charPosIndex != elem.charPos.size() - 1)
		{
			if (elem.RResult[charfound + 1] & 0x80 == 0)
				charPosIndex++;
		}

		if (type == 1 || type == 3)//截取右边,保留左边部分
		{
			//////cnt << "charPosIndex: " << charPosIndex << endl;
			subEleResult.charPos.resize(charPosIndex);
			subEleResult.charPos.assign(elem.charPos.begin(), elem.charPos.begin() + charPosIndex);

			subEleResult.RResult.assign(elem.RResult.begin(), elem.RResult.begin() + charfound);

			subEleResult.Pos[0] = elem.Pos[0]; subEleResult.Pos[1] = elem.Pos[1];
			subEleResult.Pos[2] = elem.charPos[charPosIndex].pos[0] - elem.charPos[0].pos[0]; subEleResult.Pos[3] = elem.Pos[3];
			//分割完第一个区域
			//subEleSet.push_back(subEleResult);
		}
		else if (type == 2 || type == 4)//截取左边，保留右边部分
		{

			//	////cnt << "src: " << elem.RResult << " ";
			subEleResult.charPos.resize(elem.charPos.size() - charPosIndex);
			subEleResult.charPos.assign(elem.charPos.begin() + charPosIndex, elem.charPos.end());
			subEleResult.RResult.assign(elem.RResult.begin() + charfound, elem.RResult.end());

			subEleResult.Pos[0] = elem.charPos[charPosIndex].pos[0]; subEleResult.Pos[1] = elem.charPos[charPosIndex].pos[1];
			subEleResult.Pos[2] = elem.Pos[0] + elem.Pos[2] - elem.charPos[charPosIndex].pos[0]; subEleResult.Pos[3] = elem.Pos[3];



			//	////cnt << "charfound" << charfound << " res：" << subEleResult.RResult << endl;
			//subEleSet.push_back(subEleResult);
		}
		else
		{
			int charfound2 = TranFound2(charPosIndex2, elem.RResult);
			//////cnt << charfound << "," << charfound2 << "," << charPosIndex << "," << charPosIndex2 << endl;
			subEleResult.charPos.resize(charPosIndex2 - charPosIndex);
			subEleResult.charPos.assign(elem.charPos.begin() + charPosIndex, elem.charPos.begin() + charPosIndex2);
			//202011-kang charfound>charfound2报错
			if (charfound2 >= charfound)
				subEleResult.RResult.assign(elem.RResult.begin() + charfound, elem.RResult.begin() + charfound2);
			else
				subEleResult.RResult.assign(elem.RResult.begin() + charfound2, elem.RResult.begin() + charfound);

			subEleResult.Pos[0] = (float)elem.charPos[charPosIndex].pos[0];
			subEleResult.Pos[1] = (float)elem.charPos[charPosIndex].pos[1];
			subEleResult.Pos[2] = elem.charPos[charPosIndex2].pos[0] - elem.charPos[charPosIndex].pos[0];
			subEleResult.Pos[3] = elem.Pos[3];
			//subEleSet.push_back(subEleResult);
		}
		if (type == 1 || type == 2 || type == 5)
			subEleResult.Flag = TYPE_TITLE;
		else
			subEleResult.Flag = TYPE_PRICE;
		subEleResult.titleID = titleIndex;
		subEleSet.push_back(subEleResult);
#ifdef PRINT_CUT_RES
		////cnt << "截取结果" << subEleResult.RResult << endl;
#endif
	}
	return 1;
}

int CExtractInfo::TranFound2(int found, string strInfo)
{
	if (found == 0)
		return 0;
	int chNum = 0;
	int enNum = 0;
	const char *ptrStr = strInfo.c_str();
	for (int i = 0; i < strInfo.length(); i++)
	{
		if ((ptrStr[i] & 0x80) != 0)  //发现汉字编码
		{
			chNum++;
			i = i + 1;
		}
		else
			enNum++;
		if (chNum + enNum >= found)
			return i + 1;
	}

	//////cnt << "Newfount" << newfound << endl;
	return 0;
}
int CExtractInfo::isSameLineByTitle(const RecogResult &r1, const RecogResult &r2)
{
	if (r1.titleID < r2.titleID)
		return 1;
	else if (r1.titleID>r2.titleID)
		return 2;

	int titleId = r1.titleID;



	int err = (r1.Pos[3] + r2.Pos[3]) * 0.3;// 配对名称金额组的高度偏差阈值

	float name_dist = r1.Pos[1] + r1.Pos[3] / 2 - m_titlePos[titleId].NamePos.pos[1] - m_titlePos[titleId].NamePos.pos[3] / 2;
	float price_dist = r2.Pos[1] + r2.Pos[3] / 2 - m_titlePos[titleId].PricePos.pos[1] - m_titlePos[titleId].PricePos.pos[3] / 2;

	float name_dist1 = r1.Pos[1] + r1.Pos[3];
	float price_dist1 = r2.Pos[1] + r2.Pos[3];


	//////cnt << dist1<<"|||||"<< dist2 << endl;

	if (fabs(price_dist - name_dist) < err || fabs(name_dist1 - price_dist1) < err)
	{
		//	////cnt << "误差" << fabs(r1.Pos[1] + r1.Pos[3] / 2 - r2.Pos[1] - r2.Pos[3] / 2) << endl;
		//dst = fabs(price_dist - name_dist);

		return 0;
	}

	if (CorrlastI != -1 && CorrlastJ != -1)  //上次有匹配结果
	{
		float dist_tit = r1.Pos[1] - (v_title[CorrlastI].Pos[1] + v_title[CorrlastI].Pos[3]);
		float dist_pri = r2.Pos[1] - (v_price[CorrlastJ].Pos[1] + v_price[CorrlastJ].Pos[3]);
		if (fabs(dist_tit - dist_pri) < err)
			return 0;
		else
		{
			dist_tit = (r1.Pos[1] + r1.Pos[3] / 2) - (v_title[CorrlastI].Pos[1] + v_title[CorrlastI].Pos[3] / 2);
			dist_pri = (r2.Pos[1] + r2.Pos[3] / 2) - (v_price[CorrlastJ].Pos[1] + v_price[CorrlastJ].Pos[3] / 2);
			if (fabs(dist_tit - dist_pri) < err)
				return 0;
		}

	}



	if (price_dist - name_dist >= err)
		return 1;

	if (name_dist - price_dist > err)
	{
		////cnt << "namedist" << name_dist << "price_dist" << price_dist<<"err"<<err<<endl;
		return 2;
	}
	else
	{
		return -1;
	}
	/*
	if ((r1.Pos[1] <= r2.Pos[1] && r1.Pos[1] + r1.Pos[3] >= r2.Pos[1]) || (r2.Pos[1] <= r1.Pos[1] && r2.Pos[1] + r2.Pos[3] >= r1.Pos[1]))
	return 0;
	else if ( r1.Pos[1] + r1.Pos[3] < r2.Pos[1])
	return 1;
	else if ( r2.Pos[1] + r2.Pos[3] <= r1.Pos[1])
	return 2;*/
}

void  CExtractInfo::DrawLine(const RecogResult &r1, const RecogResult &r2)
{

	Point pt1, pt2;
	pt1.x = r1.Pos[0] + r1.Pos[2] / 2;
	pt1.y = r1.Pos[1] + r1.Pos[3] / 2;

	pt2.x = r2.Pos[0] + r2.Pos[2] / 2;
	pt2.y = r2.Pos[1] + r2.Pos[3] / 2;

	line(this->InputImage, pt1, pt2, CV_RGB(255, 0, 0));
}
int CExtractInfo::callback(void *data, int argc, char **argv, char **azColName)
{
	if (argc <= 1)
		return 0;
	vector <pair<string, string> >* currentRes = (vector <pair<string, string> >*)data;
	string oldName, newName;
	oldName = string(*(argv));
	newName = string(*(argv + 1));
	UTF8ToAnsi(oldName);
	UTF8ToAnsi(newName);
	currentRes->push_back(pair<string, string>(oldName, newName));
	//m_currentRes = pair<string, string>(oldName, newName);
	return 0;
}
void CExtractInfo::ModifyNameFromSqlite(string & titleName)
{
	//{
	//	vector< pair<string, string> > m_currentRes;
	//	char *zErrMsg = 0;
	//	string sql = "select * from t_modify_name where '" + titleName + " ' like('%' || orginName || '%')";
	//	AnsiToUTF8(sql);//SQLite中是utf-8编码，所以sql语句要先转为utf-8再查询
	//	int res = sqlite3_exec(m_pDB, sql.c_str(), callback, (void*)&m_currentRes, &zErrMsg);
	//	if (res != SQLITE_OK)
	//	{
	//		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	//		sqlite3_free(zErrMsg);
	//	}
	//	if (m_currentRes.size()>0)
	//	{
	//		for (auto &p : m_currentRes)
	//			replace_all(titleName, p.first, p.second);
	//	}
}
void CExtractInfo::addToFinalList(const RecogResult &title, const RecogResult &price)
{
	string titleName = title.RResult;
#ifdef AUTO_MODIFY_NAME
	ModifyNameFromSqlite(titleName);
#endif

	KeyWord keyWord;
	keyWord.Name = titleName;
	memcpy(&keyWord.Pos[0], &title.Pos[0], sizeof(float)* 4);
	keyWord.TotalPrice = price.RResult;
	//replaceInvalidCharater(keyWord.TotalPrice);
	memcpy(&keyWord.Pos[4], &price.Pos[0], sizeof(float)* 4);
	FinalList.push_back(keyWord);

	////cnt << titleName << "___________" << price.RResult << endl;
}

void CExtractInfo::MatchResult()
{
	MergeTitle();

	CorrlastI = -1;
	CorrlastJ = -1;

	//此时v_title与v_price都是先按标题id排序再按y坐标排序
	int i = 0, j = 0;
	int lasti = -1, lastj = -1;
	FinalList.clear();

	while (i < v_title.size() && j < v_price.size())
	{


		int n1 = -1;
		int n = isSameLineByTitle(v_title[i], v_price[j]);
		if (j < v_price.size() - 1)
		{
			n1 = isSameLineByTitle(v_title[i], v_price[j + 1]);
		}
		if (n == 0 && n1 == 0)  //比较两行的效果，如果下一个匹配效果更好，则价格索引加1，跳过
		{

			if (v_price[j].titleID == v_price[j + 1].titleID  && fabs(v_price[j + 1].Pos[1] - v_price[j].Pos[1]) < 10)
			{

				int tid = v_price[j].titleID;
				if ((fabs(v_price[j].Pos[0] - m_titlePos[tid].PricePos.pos[0]) > fabs(v_price[j + 1].Pos[0] - m_titlePos[tid].PricePos.pos[0])))
					j = j + 1;
				else
				{
					if (this->CorrlastI != -1 && this->CorrlastJ != -1)
					{
						float disj = fabs(v_price[j].Pos[0] - v_price[CorrlastJ].Pos[0]);
						float disj1 = fabs(v_price[j + 1].Pos[0] - v_price[CorrlastJ].Pos[0]);
						if (disj1 * 3 < disj)
							j = j + 1;
						else
						{
							float overlap1 = this->overlap(tid, j);
							float overlap2 = this->overlap(tid, j + 1);
							if (overlap2 > 0.9 && overlap2 < 0.5)
								j = j + 1;
						}

					}
				}
			}

		}

		std::size_t found = v_title[i].RResult.rfind("面");
		if (found != string::npos)
		{
			//cnt << v_title[i].RResult<<"+++"<<v_title[i].Pos[0] << "--" << v_title[i].Pos[1] << "--" << v_title[i].Pos[2] << "--" << v_title[i].Pos[3] << endl;
			//cnt << v_price[j].Pos[0] << "--" << v_price[j].Pos[1] << "--" << v_price[j].Pos[2] << "--" << v_price[j].Pos[3] << endl;
			//cnt << v_price[j].RResult << "++" << v_price[j + 1].RResult << "++"<<n<<"--"<<n1<<endl;
		}

		string printName = "", printLine = "";
		int flag = 1;
		switch (n)
		{
		case 0:
			//如果价格中出现中文，则下一项

			v_title[i].IsMatched = 1;
			v_price[j].IsMatched = 1;


			if (lasti != -1 && lastj != -1)
			{
				if (v_title[i].Pos[1] - v_title[lasti].Pos[1] > 6 * v_title[i].Pos[3])  //发现不连续，判断为0
				{
					flag = 1;
					//	//cnt << v_title[i].RResult << endl;
				}
			}
			if (flag == 1)
			{
				addToFinalList(v_title[i], v_price[j]);
				lasti = i;
				lastj = j;
				CorrlastI = i;
				CorrlastJ = j;
			}
			i++;
			j++;
			break;
		case 1:
			i++;
			break;
		case 2:
			j++;
			break;
		default:
			i++;
			j++;
			break;
		}
	}

}

//void CExtractInfo::AnsiToUTF8(string &str)
//{
//	//int len = WideCharToMultiByte(CP_UTF8, 0, CA2W((char*)str.data()), -1, NULL, 0, NULL, NULL);
//	//char *strNew = new char[len + 1];
//	//WideCharToMultiByte(CP_UTF8, 0, CA2W((char*)str.data()), -1, strNew, len, NULL, NULL);
//	//strNew[len] = '\0';
//	//str.clear();
//	//str = strNew;
//	//delete[] strNew;
//	//return;
//}
void CExtractInfo::UTF8ToAnsi(string& strUTF8)
{
	//int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, nullptr, 0);
	//unsigned short * str1 = new unsigned short[len + 1];
	//memset(str1, 0, len * 2 + 2);
	//MultiByteToWideChar(CP_UTF8, 0, (const char*)strUTF8.c_str(), -1, (LPWSTR)str1, len);
	//len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)str1, -1, nullptr, 0, nullptr, nullptr);
	//char *str2 = new char[len + 1];
	//memset(str2, 0, len + 1);
	//WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)str1, -1, str2, len, nullptr, nullptr);
	//strUTF8 = string(str2);
	//delete[]str1;
	//delete[]str2;
}
static string rectToString(const float *Pos)
{
	//itemRect = CRect(Pos[0], Pos[1], Pos[0] + Pos[2], Pos[1] + Pos[3]);
	//priceRect = CRect(Pos[4], Pos[5], Pos[4] + Pos[6], Pos[5] + Pos[7]);

	char str[100];
	memset(str, 0, 100);
	sprintf(str, "%d,%d,%d,%d", (int)Pos[0], (int)Pos[1], (int)(Pos[0] + Pos[2]), (int)(Pos[1] + Pos[3]));
	return string(str);
}

static string rectToStringForMappedSet(const float *Pos)
{
	//itemRect = CRect(Pos[0], Pos[1], Pos[0] + Pos[2], Pos[1] + Pos[3]);
	//priceRect = CRect(Pos[4], Pos[5], Pos[4] + Pos[6], Pos[5] + Pos[7]);

	char str[100];
	memset(str, 0, 100);
	sprintf(str, "%d,%d,%d,%d", (int)Pos[0], (int)Pos[1], (int)(Pos[6]), (int)(Pos[7]));
	return string(str);
}

string CExtractInfo::makeBillJson()
{
	Json::Value root;
	root["type"] = "000";//账单明细
	Json::Value arrayObj;   // 构建对象

	vector<KeyWord> allpts = this->getFinalList();

	string pageIndex = "0";
	string pageName = "002";
	string pageRotate = "3.8255448076067506e-043";


	for (int i = 0; i < allpts.size(); i++)
	{
		Json::Value new_item;

		new_item["attributeType"] = "";

		new_item["unicodeID"] = "";
		new_item["itemName"] = allpts[i].Name;//项目名称
		new_item["fyje"] = allpts[i].TotalPrice;  //识别出来的总金额
		new_item["ypdj"] = allpts[i].UnitPrice; //药品单价
		new_item["ypsl"] = allpts[i].Number; //药品数量
		new_item["fylb"] = "";
		new_item["photo64"] = "";//项目名称的照片base64值

		//info.iteminfoRect = data[index]["new_add_itemRect"].asString();
		//info.priceinfoRect = data[index]["new_add_priceRect"].asString();

		new_item["ocrRect"] = rectToString(allpts[i].Pos); // 药品所在位置
		new_item["priceRect"] = rectToString(&allpts[i].Pos[4]);   // 总金额所在位置
		new_item["ypdjinfoRect"] = rectToString(&allpts[i].Pos[8]); // 药品单价所在位置
		new_item["ypslinfoRect"] = rectToString(&allpts[i].Pos[12]); //药品数量所在位置

		new_item["new_add_itemRect"] = new_item["ocrRect"];
		new_item["new_add_priceRect"] = new_item["priceRect"];


		new_item["xScroll"] = "";
		new_item["yScroll"] = "";
		new_item["capPic"] = new_item["ocrRect"];
		new_item["kjje"] = "";
		new_item["fylb"] = "";
		new_item["fylbdm"] = "";

		new_item["yslb"] = "";//原始识别项
		new_item["yslbid"] = ""; //原始识别项id

		new_item["majorType"] = "";
		new_item["ypmc"] = "";
		new_item["ypdm"] = "";
		new_item["ypmcdm"] = "";//药品（费用）名称代码
		new_item["zfbl"] = "";
		new_item["cdmc"] = "";
		new_item["lnkzf"] = "";

		new_item["pageIndex"] = pageIndex;
		new_item["pageName"] = pageName;//图像名称


		new_item["pageRotate"] = pageRotate;//页码旋转角度
		new_item["selfRotate"] = pageRotate;


		if (this->m_titlePos.size() > 0)  ///标题位置
		{
			//OrgRecoglList[mapId.MatchedID];
			new_item["itemRect1"] = this->m_titlePos[0].NamePos.getstringcode();// rectToStringForMappedSet(OrgRecoglList[mappedSet[0].ID].Pos);
			new_item["priceRect1"] = this->m_titlePos[0].PricePos.getstringcode(); //rectToStringForMappedSet(OrgRecoglList[mappedSet[0].MatchedID].Pos);

			new_item["djRect1"] = this->m_titlePos[0].DjPos.getstringcode();// rectToStringForMappedSet(OrgRecoglList[mappedSet[0].UnitPriceID].Pos);
			new_item["numRect1"] = this->m_titlePos[0].NumPos.getstringcode();// rectToStringForMappedSet(OrgRecoglList[mappedSet[0].NumID].Pos);

			if (this->m_titlePos.size() > 1)
			{
				new_item["itemRect2"] = this->m_titlePos[1].NamePos.getstringcode();// rectToStringForMappedSet(OrgRecoglList[mappedSet[0].ID].Pos);
				new_item["priceRect2"] = this->m_titlePos[1].PricePos.getstringcode(); //rectToStringForMappedSet(OrgRecoglList[mappedSet[0].MatchedID].Pos);

				new_item["djRect2"] = this->m_titlePos[1].DjPos.getstringcode();// rectToStringForMappedSet(OrgRecoglList[mappedSet[0].UnitPriceID].Pos);
				new_item["numRect2"] = this->m_titlePos[1].NumPos.getstringcode();// rectToStringForMappedSet(OrgRecoglList[mappedSet[0].NumID].Pos);

				/*	new_item["itemRect2"] = rectToStringForMappedSet(OrgRecoglList[mappedSet[1].ID].Pos);
				new_item["priceRect2"] = rectToStringForMappedSet(OrgRecoglList[mappedSet[1].MatchedID].Pos);
				new_item["djRect2"] = rectToStringForMappedSet(OrgRecoglList[mappedSet[1].UnitPriceID].Pos);
				new_item["numRect2"] = rectToStringForMappedSet(OrgRecoglList[mappedSet[2].NumID].Pos);*/
			}
		}

		new_item["scaleNum"] = "1.0";


		new_item["remark"] = "";
		new_item["remarkrep"] = "";

		//此处项为何
		new_item["titleId"] = "";


		new_item["xPos"] = 0; //(citr->AttributePt()).x;
		new_item["yPos"] = 0;//(citr->AttributePt()).y;

		//	arrayObj["data"].append(new_item); // 插入数组成员
		arrayObj.append(new_item);

	}

	root["data"] = arrayObj;

	//添加页面属性，字符串格式是  页码_旋转90度的次数，如第一页旋转90度，表示为 1_1,第二页旋转-90度为  2_-1 (参见parseBillJson解析)
	root["pageAttribute"] = "";

	std::string jsonout = root.toStyledString();

	return jsonout;
}

int CExtractInfo::DrawRectangleForUnit(Mat& drawImage, RecogResult rectoList)
{
	Rect rect;

	rect.x = rectoList.Pos[0];
	rect.y = rectoList.Pos[1];
	rect.width = rectoList.Pos[2];
	rect.height = rectoList.Pos[3];

	rectangle(drawImage, rect, CV_RGB(255, 0, 0));

	return 1;
}


int CExtractInfo::RecognizePriceAndNumber(RecogResult& UnitPircPos, RecogResult& NumberPos,
	RecogResult& TitlePos, RecogResult& TotalPricePos)
{
	//kang 2021-03 单价金额定位修改为就近原则
	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		//单价
		if (OrgRecoglList[i].Flag == 5)
		{
			if ((fabs(TitlePos.Pos[1] - this->OrgRecoglList[i].Pos[1]) > fabs(TotalPricePos.Pos[1] - this->OrgRecoglList[i].Pos[1])
				&& fabs(TotalPricePos.Pos[1] - this->OrgRecoglList[i].Pos[1]) < 15)
				|| (fabs(TitlePos.Pos[1] - this->OrgRecoglList[i].Pos[1]) < fabs(TotalPricePos.Pos[1] - this->OrgRecoglList[i].Pos[1])
				&& fabs(TitlePos.Pos[1] - this->OrgRecoglList[i].Pos[1]) < 15)
				&& fabs(TotalPricePos.Pos[0] - TitlePos.Pos[0]) > 10
				&& this->OrgRecoglList[i].Pos[0] < TotalPricePos.Pos[0] 
				&& this->OrgRecoglList[i].Pos[0] > TitlePos.Pos[0])
			{
				UnitPircPos = OrgRecoglList[i];

				int nDot;
				int nRight = this->FindNearRight(i, nDot);
				if (nRight != -1)
				{
					UnitPircPos.Pos[2] = OrgRecoglList[nRight].Pos[0] - 5 - OrgRecoglList[i].Pos[0];
				}
				//this->DrawRectangleForUnit(this->InputImage, UnitPircPos);
				//memcpy(&UnitPircPos, &OrgRecoglList[i], sizeof(RecogResult));
				//this->DrawRectangleForUnit(this->InputImage, UnitPircPos);
			}
		}

		//	////数量
		if (OrgRecoglList[i].Flag == 7)
		{
			if ((fabs(TitlePos.Pos[1] - this->OrgRecoglList[i].Pos[1]) > fabs(TotalPricePos.Pos[1] - this->OrgRecoglList[i].Pos[1])
				&& fabs(TotalPricePos.Pos[1] - OrgRecoglList[i].Pos[1]) < 15)
				|| (fabs(TitlePos.Pos[1] - this->OrgRecoglList[i].Pos[1]) < fabs(TotalPricePos.Pos[1] - this->OrgRecoglList[i].Pos[1])
				&& fabs(TitlePos.Pos[1] - OrgRecoglList[i].Pos[1]) < 15)
				&& fabs(TotalPricePos.Pos[0] - TitlePos.Pos[0]) > 10
				&& this->OrgRecoglList[i].Pos[0] < TotalPricePos.Pos[0]
				&& this->OrgRecoglList[i].Pos[0] > TitlePos.Pos[0])
			{
				NumberPos = OrgRecoglList[i];

				int nDot;
				int nRight = this->FindNearRight(i, nDot);
				if (nRight != -1)
				{
					NumberPos.Pos[2] = OrgRecoglList[nRight].Pos[0] - 5 - OrgRecoglList[i].Pos[0];
				}
				//	memcpy(&NumberPos, &RecoglList[i], sizeof(RecogResult));
				//this->DrawRectangleForUnit(this->InputImage, NumberPos);
			}
		}
	}
	return -1;
}


int CExtractInfo::FindBestMatchByTriplet(vector<KeyWord>& listSet, int curID, RecogResult& ThirdPos, RecogResult& TitlePos, RecogResult& TotalPricePos)
{
	int i = curID;

	//if (listSet[curID].Pos[0] < TitlePos.Pos[0] ||
	//	listSet[curID].Pos[0] > TotalPricePos.Pos[0])
	//	return -1;
	//循环遍历找到最近的单价匹配位置
	vector<int> YListId;
	for (int j = 0; j < RecoglList.size(); j++)
	{
		float disY1 = fabs(TitlePos.Pos[1] - listSet[i].Pos[1]);
		float disY2 = fabs(ThirdPos.Pos[1] - RecoglList[j].Pos[1]);

		if (fabs(disY1 - disY2) / (float)TitlePos.Pos[3] < 0.5 && ThirdPos.Pos[1] <= RecoglList[j].Pos[1])  //纵向位置在预测范围以内
		{
			YListId.push_back(j);
			//this->DrawRectangleForUnit(this->InputImage, RecoglList[j]);
		}
	}
	float minX = 10000, minID = -1;
	for (int j = 0; j < YListId.size(); j++)
	{
		float disX = fabs(ThirdPos.Pos[0] - RecoglList[YListId[j]].Pos[0]);
		if (disX < minX  && RecoglList[YListId[j]].Pos[0] > TitlePos.Pos[0] && RecoglList[YListId[j]].Pos[0] < TotalPricePos.Pos[0])
		{
			minID = j;
			minX = disX;
		}
	}
	if (minID >= 0)
	{
		if (ThirdPos.Pos[0] + ThirdPos.Pos[2] > RecoglList[YListId[minID]].Pos[0])
		{
			//	this->DrawRectangleForUnit(this->InputImage, RecoglList[YListId[minID]]);
			return YListId[minID];

		}
	}

	return -1;
}
/*
new_item["NameX"] = FinalList[i].Pos[0];
new_item["NameY"] = FinalList[i].Pos[1];
new_item["NameW"] = FinalList[i].Pos[2];
new_item["NameH"] = FinalList[i].Pos[3];
*/
int CExtractInfo::RecognizePriceAndNumberByTitle(vector<KeyWord>& listSet,
	RecogResult& UnitPircPos, RecogResult& NumberPos,
	RecogResult& TitlePos, RecogResult& TotalPricePos, int colID)
{
	for (int i = 0; i < listSet.size(); i++)
	{
		if (this->m_titlePos.size() > 0)  //多列，做个简单的判断

			int minJ = 0;
		float mindis = 1000000;
		for (int j = 0; j < this->m_titlePos.size(); j++)
		{
			if (abs(this->m_titlePos[j].NamePos.pos[0] - listSet[i].Pos[0]) < mindis)
			{
				listSet[i].titleId = j;
				mindis = abs(this->m_titlePos[j].NamePos.pos[0] - listSet[i].Pos[0]);
			}
		}

		if (colID != listSet[i].titleId)
			continue;

		//计算项目名称中间位置到顶部标题的位置dis
		int reID = FindBestMatchByTriplet(listSet, i, UnitPircPos, TitlePos, TotalPricePos);

		if (reID != -1)
		{
			listSet[i].Pos[8] = RecoglList[reID].Pos[0];
			listSet[i].Pos[9] = RecoglList[reID].Pos[1];
			listSet[i].Pos[10] = RecoglList[reID].Pos[2];
			listSet[i].Pos[11] = RecoglList[reID].Pos[3];
			extractNumber(RecoglList[reID].RResult, RecoglList[reID].RResult);
			listSet[i].UnitPrice = RecoglList[reID].RResult;
		}

		reID = FindBestMatchByTriplet(listSet, i, NumberPos, TitlePos, TotalPricePos);
		if (reID != -1)
		{
			listSet[i].Pos[12] = RecoglList[reID].Pos[0];
			listSet[i].Pos[13] = RecoglList[reID].Pos[1];
			listSet[i].Pos[14] = RecoglList[reID].Pos[2];
			listSet[i].Pos[15] = RecoglList[reID].Pos[3];
			extractNumber(RecoglList[reID].RResult, RecoglList[reID].RResult);
			listSet[i].Number = RecoglList[reID].RResult;
		}

		//	imwrite("c:/1.jpg", InputImage);

		//循环遍历找到最近的数量匹配位置


		//把结果写入到listSet中
	}

	//imwrite("c:/1.jpg", InputImage);
	return -1;
}

RecogResult CExtractInfo::GetPosInfo(PosOfChar &inPos)
{
	RecogResult ssResult;

	for (int i = 0; i < 4; i++)
		ssResult.Pos[i] = inPos.pos[i];

	return ssResult;
}

void CExtractInfo::AddDjAndNum()
{
	for (int i = 0; i < this->m_titlePos.size(); i++)
	{
		if (m_titlePos[i].DjPos.pos[0] != -1)
		{
			RecogResult UnitPircPos, NumberPos;
			RecogResult TitlePos, TotalPricePos;

			TitlePos = GetPosInfo(this->m_titlePos[i].NamePos);
			TotalPricePos = GetPosInfo(this->m_titlePos[i].PricePos);
			UnitPircPos = GetPosInfo(this->m_titlePos[i].DjPos);
			NumberPos = GetPosInfo(this->m_titlePos[i].NumPos);

			this->RecognizePriceAndNumberByTitle(FinalList, UnitPircPos, NumberPos, TitlePos, TotalPricePos, i);
		}
	}

	for (int i = 0; i < this->FinalList.size(); i++)
	{
		////cnt << this->FinalList[i].Name << "   ";
		////cnt << this->FinalList[i].Number << "   ";
		////cnt << this->FinalList[i].UnitPrice << "   ";
		////cnt << this->FinalList[i].TotalPrice << "   ";
		////cnt << endl;

	}
	//	for (int i = 0; i < FinalList.size(); i++)
	//	{

	//		int dst1 = 0;
	//		for (int j = 0; j < v_dj.size(); j++)
	//		{
	//			if (isSameLineByTitle(v_title[i], v_dj[j], dst1) == 0)
	//			{
	//				FinalList[i].Pos[8] = v_dj[j].Pos[0];
	//				FinalList[i].Pos[9] = v_dj[j].Pos[1];
	//				FinalList[i].Pos[10] = v_dj[j].Pos[2];
	//				FinalList[i].Pos[11] = v_dj[j].Pos[3];
	//				FinalList[i].UnitPrice = v_dj[j].RResult;
	//				break;
	//			}
	//		}
	//		for (int k = 0; k < v_num.size(); k++)
	//		{
	//			if (isSameLineByTitle(v_title[i], v_num[k], dst1) == 0)
	//			{
	//				FinalList[i].Pos[12] = v_num[k].Pos[0];
	//				FinalList[i].Pos[13] = v_num[k].Pos[1];
	//				FinalList[i].Pos[14] = v_num[k].Pos[2];
	//				FinalList[i].Pos[15] = v_num[k].Pos[3];
	//				FinalList[i].Number = v_num[k].RResult;
	//				break;
	//			}
	//		}
	//	}
	//}
}
void CExtractInfo::AddDjAndNumUnit()
{
	for (int i = 0; i < mappedSet.size(); i++)
	{
		int nameId = mappedSet[i].ID;
		int priceId = mappedSet[i].MatchedID;
		int numId = mappedSet[i].NumID;
		int DjId = mappedSet[i].UnitPriceID;
		if (numId != -1 && DjId != -1)
		{
			this->RecognizePriceAndNumberByTitle(this->FinalList, this->OrgRecoglList[DjId], this->OrgRecoglList[numId],
				this->OrgRecoglList[nameId], this->OrgRecoglList[priceId], i);
		}

	}
}

static string rectToString2(float Pos[4])
{
	char str[100];
	memset(str, 0, 100);
	sprintf(str, "%d,%d,%d,%d", (int)Pos[0], (int)Pos[1], (int)(Pos[0] + Pos[2]), (int)(Pos[1] + Pos[3]));
	return string(str);
}

string CExtractInfo::FormulateJasonList()
{
	//位置坐标是左上角和右下角
	if (m_titlePos.size() <= 0)
		return "";

	Json::Value root;
	Json::Value dataArr, data;
	for (int i = 0; i < this->FinalList.size(); i++)
	{
		data["unicodeID"] = "";

		data["itemName"] = this->FinalList[i].Name; //药品名称
		data["new_add_itemRect"] = rectToString2(&this->FinalList[i].Pos[0]);// ""; //名称位置

		data["fyje"] = this->FinalList[i].TotalPrice;    //药品价格
		data["new_add_priceRect"] = rectToString2(&this->FinalList[i].Pos[4]); //价格位置

		data["ypdj"] = this->FinalList[i].UnitPrice;    //药品单价
		data["ypdjinfoRect"] = rectToString2(&this->FinalList[i].Pos[8]); //单价所在位置

		data["ypsl"] = this->FinalList[i].Number;    //药品数量
		data["ypslinfoRect"] = rectToString2(&this->FinalList[i].Pos[12]); //药品数量所在位置

		//识别得到标题位置		
		data["itemRect1"] = m_titlePos[0].NamePos.getstringcode();
		data["priceRect1"] = m_titlePos[0].PricePos.getstringcode();
		data["djRect1"] = m_titlePos[0].DjPos.getstringcode();
		data["numRect1"] = m_titlePos[0].NumPos.getstringcode();

		data["itemRect2"] = "";
		data["priceRect2"] = "";
		data["djRect2"] = "";
		data["numRect2"] = "";
		if (m_titlePos.size() > 1)
		{
			data["itemRect2"] = m_titlePos[1].NamePos.getstringcode();
			data["priceRect2"] = m_titlePos[1].PricePos.getstringcode();
			data["djRect2"] = m_titlePos[1].DjPos.getstringcode();
			data["numRect2"] = m_titlePos[1].NumPos.getstringcode();
		}


		data["photo64"] = "";
		data["ocrRect"] = "";
		data["priceRect"] = "";   //价格位置？
		data["xScroll"] = 0;
		data["yScroll"] = 0;
		data["capPic"] = "";  //什么位置;
		data["ypmc"] = "";
		data["ypdm"] = "";
		data["ypmcdm"] = -1;
		data["zfbl"] = "0.0";
		data["fylb"] = "";
		data["fylbdm"] = -1;
		data["yslb"] = "";
		data["yslbid"] = 0;
		data["cdmc"] = 0;///.asInt();
		data["lnkzf"] = -1;// .asBool();



		data["kjje"] = "0.0";
		data["remark"] = "";
		data["remarkrep"] = "";
		data["ypmc"] = "";
		data["pageRotate"] = 0;// .asFloat();
		data["selfRotate"] = 0;// .asFloat();


		data["scaleNum"] = "1.0";
		data["titleId"] = 0;//.asInt();

		data["pageIndex"] = PageID;
		data["pageName"] = "";// .asString();
		data["selfangle"] = angleRot;// .asString();

		dataArr.append(data);
	}

	root["data"] = dataArr;

	std::string jsonout = root.toStyledString();

	return jsonout;
}

string CExtractInfo::FormulateJasonFullText(string& recogJason)
{
	Json::Value root;

	root["data"] = recogJason;

	return root.toStyledString();
}

void  CExtractInfo::RefineAutoTitle()
{
	//对于发现的名称和金额匹配对（如果同一行附件发现另外一个名称，则采用该名称进行配对）
	for (int i = 0; i < this->mappedSet.size(); i++)
	{
		int orgID = this->mappedSet[i].ID;
		int MatchID = this->mappedSet[i].MatchedID;
		for (int j = 0; j < OrgRecoglList.size(); j++)
		{
			if (this->OrgRecoglList[j].Flag == 4 && this->mappedSet[i].ID != j)
			{
				float disY = fabs(this->OrgRecoglList[orgID].Pos[1] - this->OrgRecoglList[j].Pos[1]);
				if (this->OrgRecoglList[j].Pos[0] > this->OrgRecoglList[orgID].Pos[0] &&
					this->OrgRecoglList[j].Pos[0] < this->OrgRecoglList[MatchID].Pos[0] &&
					disY < this->OrgRecoglList[orgID].Pos[3] / 2)
					this->mappedSet[i].ID = j;
			}
		}
	}
}

int CExtractInfo::SplitTitleRegions(vector<RecogResult>& FinalelemSet, RecogResult elem)
{

	return 0;
}


#if defined(_WIN32)
#include "HttpFileEx.h"
string CExtractInfo::ExtractInfo(cv::Mat ocrImg, const char *IPAddress, const char *ObjFun, int Port/*, vector<TitlePos>& v_titlePos*/)
{

	bool autoRecog = true;

	CandTitleList.clear();

	Mat OrgoutputRGBImage;

	this->InputImage = ocrImg.clone();
	//this->InputImage = ocrImg;
	if (m_titlePos.empty())
	{

		autoRecog = true;
	}
	else
	{
		autoRecog = false;
		isManual = 1;

		//DrawGridOnImage();
	}

	imwrite("c:/245.jpg", InputImage);
	string strResult = "---";


	if (m_strRecogJson == "")
	{
		CHttpFileEx httpFile;
		//http://192.168.1.4:8090/ocr/api/img/recognize 
		//httpFile.SetServerParam("192.168.1.4", "/ocr/api/img/recognize", 8090);
		httpFile.SetServerParam(IPAddress, ObjFun, Port);
		wchar_t*  pRecvData = NULL; //接收数据的指针               *
		DWORD  dwRecvSize = 0;  //接收数据的大小                 *
		DWORD  dwRetSend = 0;  //发送函数返回值                  *
		int SendCode = HTTP_POST_UTF8; //                      *
		int RecvCode = HTTP_POST_UTF8; //发送与接收的编码      *
		dwRetSend = httpFile.PostPicDataMethodForMat(InputImage, "image", &pRecvData, dwRecvSize, SendCode, RecvCode);


		vector<string> textVec;
		if (!pRecvData)
		{
			////cnt << "请求失败，错误码:" << dwRetSend << endl;
			return "";
		}
		m_strRecogJson = CStringOperator::ws2s(pRecvData);

		//HLW修改2 由于保存时需要去掉base64，所以在这边去除
		auto pos1 = m_strRecogJson.find("\"imgData");
		auto pos2 = m_strRecogJson.find("\"time_cost");
		//printf("%d,%d\n",pos1,pos2);
		if (pos1 != string::npos && pos2 != string::npos)
			m_strRecogJson.replace(pos1, pos2 - pos1, "");
		else
		{
			//AfxMessageBox("替换base64失败");
		}

		//ofstream outfile;//创建文件
		//outfile.open("C:\\111.txt");
		//outfile << m_strRecogJson << endl;
		//outfile.close();
	}

	//openeddir = filename.substr(0, found);
	//openedfile = filename.substr(found, filename.length() - found);

	TempImage = this->InputImage.clone();
	srcImg = this->InputImage.clone();
	//	////cnt << openeddir << "+++" << openedfile << endl;
	//识别图像
	aveYPosOfTitle = 0;
	NumofTitle = 0;

	//先得到版本号（1：全文识别老版；2：全文识别新版；3：表格识别版；）
	m_ocrEngineType = -1;

#if defined(_WIN32)
	CStringOperator::AnsiToUTF8(m_strRecogJson);
#endif


	if (m_ocrEngineType == -1)
	{
		if (!m_reader.parse(m_strRecogJson, m_root))
			return "";

		try
		{
			m_data = m_root["table"];
			if (!m_data.isNull())
				m_ocrEngineType = 3;
			else
			{
				m_data = m_root["document"]["blocks"];
				if (m_data.isNull())
					m_ocrEngineType = 1;
				else
					m_ocrEngineType = 2;
			}
		}
		catch (...)
		{
			return "";
		}
	}

	if (m_ocrEngineType == 1 || m_ocrEngineType == 2)
	{
		if (autoRecog)
		{
			HospitalID = -1;
			m_initjson = 0;
			DecodeOneImage(ocrImg, IPAddress, ObjFun, Port, 1);

			OrgRecoglList.assign(RecoglList.begin(), RecoglList.end());

			sort(OrgRecoglList.begin(), OrgRecoglList.end());//以x坐标排序


			GetMatchedNameAndTotal();//获取标题保存到mappedSet中

			if (mappedSet.size() > 0)
				AutoGetNamePricePos(); //根据标题确定左右边界位置

			//处理候选标题
			SetTitlePosCand();
			ProcessForSpecialHos();  //对特殊医院进行处理

			if (this->m_titlePos.size() <= 0)
				return "";

			//	cv::imwrite("c:/1.jpg", this->InputImage);
			m_nPriceCount = 0;

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
				if (r.RResult.length() <= 2)
					return true;
				else
					return false;
			});



			DecodeOneImage(ocrImg, IPAddress, ObjFun, Port, 2);

			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());

			MatchResult();

			AddDjAndNum();
			GetDetailList();
			//	if (mappedSet.size() > 0)
			//		OutputImage("D:\\temp.jpg");
		}
		else
		{
			m_initjson = 0;
			DecodeOneImage(this->InputImage, IPAddress, ObjFun, Port, 2);
			OrgRecoglList.assign(RecoglList.begin(), RecoglList.end());
			//以y升序排
			//////cnt << "title" << v_title.size() << " ,price" << v_price.size() << endl;

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
				if (r.RResult.length() <= 2)
					return true;
				else
					return false;
			});
			v_title.erase(p, v_title.end());
			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());


			MatchResult();

			//	OutputImage("c:\\temp.jpg");

			AddDjAndNum();//根据标题确定左右边界位置

			GetDetailList();
		}
	}
	else
	{
		int res = GetRecogedTable();
		if (res == 0)
		{
			//无表格情况
			HospitalID = -1;
			m_initjson = 0;
			DecodeRecogedTable(1);

			OrgRecoglList.assign(RecoglList.begin(), RecoglList.end());

			sort(OrgRecoglList.begin(), OrgRecoglList.end());//以x坐标排序

			GetMatchedNameAndTotal();//获取标题保存到mappedSet中

			if (mappedSet.size() > 0)
				AutoGetNamePricePos(); //根据标题确定左右边界位置
			else
				SortByKMeans(10);
			//处理候选标题
			SetTitlePosCand();
			ProcessForSpecialHos();  //对特殊医院进行处理

			if (this->m_titlePos.size() <= 0)
				return "";

			//	cv::imwrite("c:/1.jpg", this->InputImage);
			m_nPriceCount = 0;

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
				if (r.RResult.length() <= 2)
					return true;
				else
					return false;
			});

			DecodeRecogedTable(2);

			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());

			MatchResult();

			AddDjAndNum();

			GetDetailList();
		}
		else if (res == 1)
		{
			//表格存在,拆分跨行问题
			DecodeTableAgain();
			//确定标题所在行，名称、金额所在列
			DetectColFlagOfTable();

			//校验每列标题对应的数据，与相邻数据进行比较
			VerifyEachColInfo();

			vector<int> isSplit;
			for (int i = 0; i < TableSet.size(); i++)
			{
				int flag = 0;
				isSplit.push_back(0);
				for (int j = 0; j < TableSet[i].MatrixTable.size(); j++)//行
				{
					vector<int> num;//某列每列跨行数量>2
					if (j > TableSet[i].Row)
					{
						for (int k = 0; k < TableSet[i].MatrixTable[j].size(); k++)//列
						{
							if (j >= TableSet[i].MatrixTable[j][k].rowColumn[0] && j <= TableSet[i].MatrixTable[j][k].rowColumn[2])
							{
								if (k == TableSet[i].TitleCol[0] || k == TableSet[i].TitleCol[3])
								{
									if (TableSet[i].MatrixTable[j][k].allStrText.size()>2 && m_titlePos[i].NamePos.pos[1] < TableSet[i].MatrixTable[j][k].position[1])
										//有一行表格跨行数>2且相等
									{
										num.push_back(k);
									}
									if (num.size() == 2)
									{
										flag = 1;
										isSplit[i] = 1;
										break;
									}
								}
							}
						}
					}
					if (flag)
						break;
				}
			}
			//根据所确定行列，添加每组数据
			for (int i = 0; i < isSplit.size(); i++)
			{
				if (!isSplit[i])
				{
					//合并一行被识别成多个问题
					MergeTableByWholeRowCol(i, 1);
					MergeMultiColumn(i);

					MergeTitleCol(i,1);
					GetTableColumn(i);
				}
				else
					SplitTableForWholeCol(i);
			}

			//合并项目名称换行
			MergeName();



			//数字处理、过滤
			JudgeRowTableType();

			//知道名称金额，计算单价或者数量
			GetNumDj();
			GetDetailListTable();

			//部分有表格、部分无表格情况
			for (int i = 0; i < FinalList.size(); i++)
			{
				if (i == 0)
				{
					if (FinalList[i].Pos[1] > this->InputImage.rows / 5)
					{
						int pos[4];
						pos[0] = 0;
						pos[1] = 0;
						pos[2] = InputImage.cols;
						pos[3] = FinalList[i].Pos[1];
						RecognizeRegion(FinalList, m_titlePos, pos);
					}
				}
				else if (i == FinalList.size() - 1)
				{
					if (FinalList[i].Pos[1] < this->InputImage.rows / 5 * 4)
					{
						int pos[4];
						pos[0] = 0;
						pos[1] = FinalList[i].Pos[1];
						pos[2] = InputImage.cols;
						pos[3] = InputImage.rows - FinalList[i].Pos[1];
						RecognizeRegion(FinalList, m_titlePos, pos);
					}
				}
				else if ((FinalList[i].Pos[1] - FinalList[i - 1].Pos[1]) > this->InputImage.rows / 10)
				{
					int pos[4];
					pos[0] = 0;
					pos[1] = FinalList[i - 1].Pos[1];
					pos[2] = InputImage.cols;
					pos[3] = FinalList[i].Pos[1] - FinalList[i - 1].Pos[1];
					RecognizeRegion(FinalList, m_titlePos, pos);
				}
			}

			if (this->FinalList.size() < 1)
			{
				int pos[4];
				pos[0] = 0;
				pos[1] = 0;
				pos[2] = InputImage.cols;
				pos[3] = InputImage.rows;
				m_titlePos.clear();
				RecognizeRegion(FinalList, m_titlePos, pos);

			}
			for (int i = 0; i<FinalList.size(); i++)
			{
				if (FinalList[i].Name.size() > 80)
				{
					FinalList[i].Name = FinalList[i].Name.substr(0, 80);
				}
			}

			/*
			//识别结果为空
			if (this->FinalList.size() < 1)
			{
			//表格未识别出,按照无表格再次识别
			v_title.clear();
			v_num.clear();
			v_dj.clear();
			v_price.clear();

			v_title_table.clear();
			v_dj_table.clear();
			v_num_table.clear();
			v_price_table.clear();

			TableSet.clear();
			if (isManual == -1)
			{
			m_titlePos.clear();

			//无表格情况
			HospitalID = -1;
			m_initjson = 0;
			DecodeRecogedTable(1);

			OrgRecoglList.assign(RecoglList.begin(), RecoglList.end());
			sort(OrgRecoglList.begin(), OrgRecoglList.end());//以x坐标排序

			GetMatchedNameAndTotal();//获取标题保存到mappedSet中

			if (mappedSet.size() > 0)
			AutoGetNamePricePos(); //根据标题确定左右边界位置

			//处理候选标题
			SetTitlePosCand();
			ProcessForSpecialHos();  //对特殊医院进行处理

			if (this->m_titlePos.size() <= 0)
			return "";

			//	cv::imwrite("c:/1.jpg", this->InputImage);
			m_nPriceCount = 0;

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
			if (r.RResult.length() <= 2)
			return true;
			else
			return false;
			});

			DecodeRecogedTable(2);

			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());

			MatchResult();

			AddDjAndNum();

			GetDetailList();
			}
			else
			{
			m_initjson = 0;

			DecodeRecogedTable(2);
			OrgRecoglList.assign(RecoglList.begin(), RecoglList.end());

			auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
			if (r.RResult.length() <= 2)
			return true;
			else
			return false;
			});
			v_title.erase(p, v_title.end());
			sort(v_title.begin(), v_title.end());

			sort(v_price.begin(), v_price.end());

			MatchResult();

			AddDjAndNum();//根据标题确定左右边界位置

			GetDetailList();
			}
			}
			*/
		}
		else
		{
			;
		}
	}
	//return strResult;

	//mappedSet 为保存的是识别出的项目名称，金额在OrgRecogList中的Id

	//#endif
	//把识别结果写入到Jason中
	Json::Value arrayObj;   // 构建对象
	int pageIndex = 1;
	for (auto i = 0; i < FinalList.size(); i++)
	{
		Json::Value new_item;

		new_item["itemName"] = FinalList[i].Name;//项目名称		
		new_item["NameX"] = FinalList[i].Pos[0];
		new_item["NameY"] = FinalList[i].Pos[1];
		new_item["NameW"] = FinalList[i].Pos[2];
		new_item["NameH"] = FinalList[i].Pos[3];
		new_item["itemTotal"] = FinalList[i].TotalPrice;  //项目总价
		new_item["TotalX"] = FinalList[i].Pos[4];
		new_item["TotalY"] = FinalList[i].Pos[5];
		new_item["TotalW"] = FinalList[i].Pos[6];
		new_item["TotalH"] = FinalList[i].Pos[7];
		new_item["itemNumber"] = FinalList[i].Number;  //药品数量
		new_item["NumberX"] = FinalList[i].Pos[8];
		new_item["NumberY"] = FinalList[i].Pos[9];
		new_item["NumberW"] = FinalList[i].Pos[10];
		new_item["NumberH"] = FinalList[i].Pos[11];
		new_item["itemUnitPrice"] = FinalList[i].UnitPrice;  //药品单价
		new_item["UnitPriceX"] = FinalList[i].Pos[12];
		new_item["UnitPriceY"] = FinalList[i].Pos[13];
		new_item["UnitPriceW"] = FinalList[i].Pos[14];
		new_item["UnitPriceH"] = FinalList[i].Pos[15];

		arrayObj.append(new_item);
	}

	string jsonout = "";
	if (FinalList.size() > 0)
		jsonout = arrayObj.toStyledString();

	return m_strRecogJson;

}
void CExtractInfo::DecodeOneImage(cv::Mat ocrImg, const  char *IPAddress, const char *ObjFun, int Port, int type)//type=1按版本1，type=2 按版本2
{
	//	AfxMessageBox("CExtractInfo::DecodeOneImage");

	if (m_strRecogJson == "")
	{
		CHttpFileEx httpFile;
		//http://192.168.1.4:8090/ocr/api/img/recognize 
		//httpFile.SetServerParam("192.168.1.4", "/ocr/api/img/recognize", 8090);
		httpFile.SetServerParam(IPAddress, ObjFun, Port);
		wchar_t*  pRecvData = NULL; //接收数据的指针               *
		DWORD  dwRecvSize = 0;  //接收数据的大小                 *
		DWORD  dwRetSend = 0;  //发送函数返回值                  *
		int SendCode = HTTP_POST_UTF8; //                      *
		int RecvCode = HTTP_POST_UTF8; //发送与接收的编码      *
		dwRetSend = httpFile.PostPicDataMethodForMat(ocrImg, "image", &pRecvData, dwRecvSize, SendCode, RecvCode);

		vector<string> textVec;
		if (!pRecvData)
		{
			////cnt << "请求失败，错误码:" << dwRetSend << endl;
			return;
		}
		m_strRecogJson = CStringOperator::ws2s(pRecvData);

		//HLW修改2 由于保存时需要去掉base64，所以在这边去除
		auto pos1 = m_strRecogJson.find("\"imgData");
		auto pos2 = m_strRecogJson.find("\"time_cost");
		//printf("%d,%d\n",pos1,pos2);
		if (pos1 != string::npos && pos2 != string::npos)
			m_strRecogJson.replace(pos1, pos2 - pos1, "");
		else
		{
			//AfxMessageBox("替换base64失败");
		}

		//ofstream of2;
		//of2.open("D:\\res.txt");
		////of2.write(m_strRecogJson.c_str(), m_strRecogJson.length());
		//of2.write(m_strRecogJson.c_str(), m_strRecogJson.length());
		//of2.close();
	}

	//初始化JASON引擎，避免二次读取
	if (m_initjson == 0)
	{
		//WYP修改  添加获取OCR接口版本号	
		if (!m_reader.parse(m_strRecogJson, m_root))
		{
			return;
		}

		try
		{
			m_data = m_root["document"]["blocks"];
			if (m_data.isNull())
				m_ocrEngineType = 1;
			else
				m_ocrEngineType = 2;
		}
		catch (...)
		{
			return;
		}

		m_initjson = 1;
	}
	/*char szPath[MAX_PATH];
	sprintf(szPath, "c:\\full2.txt");
	FILE* pf = fopen(szPath, "wb");
	if (NULL != pf)
	{
	fwrite(m_strRecogJson.c_str(), 1, m_strRecogJson.length(), pf);
	fclose(pf);
	}*/

	/*CString strInfo;

	strInfo.Format("%d_%d_%d", m_initjson, m_ocrEngineType, m_data.size());
	AfxMessageBox(strInfo);
	*/
	Json::Reader reader;
	Json::Value root;
	//////cnt << str << endl;

	//WYP修改  添加获取OCR接口版本号	
	if (m_ocrEngineType == 2)
	{
		Json::Value data;
		try
		{
			data = m_root["document"]["blocks"];
		}
		catch (...)
		{
			return;
		}
		/*Json::Value strLinePos = strLineText["eachLinePos"];
		Json::Value strCharPos = root["charPos"];*/
		int k = 0;
		int s = data.size();
		//	FILE *fp = fopen("c:/line.txt", "w");
		for (int arrayIndex = 0; arrayIndex < data.size(); ++arrayIndex)
		{
			Json::Value linesObj, charObj;
			try
			{
				Json::Value::UInt index = 0;
				linesObj = data[arrayIndex]["lines"][index];
				charObj = linesObj["characters"];
			}
			catch (...)
			{
				return;
			}
			string strText = linesObj["text"].asString();

#if defined(_WIN32)
			CStringOperator::UTF8ToAnsi(strText);
#endif
			string strPos = "0,0,0,0";//strLinePos[arrayIndex].asString();

			//string charPos = strCharPos[0].asString();
			vector<PosOfChar> charPos;


			charPos.resize(charObj.size());
			k = 0;
			for (int i = 0; i < charObj.size(); i++)
			{
				Json::Value charPosObj;
				try
				{
					charPosObj = charObj[i]["position"]["bounding_box"];//.asString(); //strText1为识别的每个字符的位置{x,x,x,x}
				}
				catch (...)
				{
					return;
				}
				//int s[4];
				//////cnt << strText1 << endl;
				//sscanf(strText1.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);

				charPos[i].pos[0] = charPosObj["left"].asInt();
				charPos[i].pos[1] = charPosObj["top"].asInt();
				charPos[i].pos[2] = charPosObj["width"].asInt();
				charPos[i].pos[3] = charPosObj["height"].asInt();
				//k++;
			}
			if (type == 1)
			{
				PushRecogResult(strText, strPos, charPos);
				//		fprintf(fp, "%s\n", strText.c_str());
			}
			else
				PushRecogResult2(strText, strPos, charPos);
		}

		//	fclose(fp);
	}

#if 1	
	//===========此处是老版本的解析======================
	else if (m_ocrEngineType == 1)
	{
		Json::Value strLineText = m_root["lineText"];
		Json::Value strLinePos = m_root["eachLinePos"];
		Json::Value strCharPos = m_root["charPos"];

		int k = 0;
		for (int arrayIndex = 0; arrayIndex < strLineText.size(); ++arrayIndex)
		{
			string strText = strLineText[arrayIndex].asString();
			string strPos = strLinePos[arrayIndex].asString();

			//string charPos = strCharPos[0].asString();
			vector<PosOfChar> charPos;

			Json::Value charPosItem = strCharPos[arrayIndex];
			charPos.resize(charPosItem.size());
			k = 0;

			for (int i = 0; i < charPosItem.size(); i++)
			{
				string strText1 = charPosItem[k].asString(); //strText1为识别的每个字符的位置{x,x,x,x}

				int s[4];
				//////cnt << strText1 << endl;
				sscanf(strText1.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);

				charPos[i].pos[0] = s[0]; charPos[i].pos[1] = s[1];
				charPos[i].pos[2] = s[2]; charPos[i].pos[3] = s[3];
				k++;

			}

			//WYP 记录清单标题名称及坐标等信息
			if (!m_titlePos.empty())
			{
				/*
				int namepos[4];
				namepos[0] = g_titlePos[0].pos[0];
				namepos[1] = charPos[0].pos[1];
				namepos[2] = charPos[0].pos[2];
				namepos[3] = charPos[0].pos[3];
				string hosppos = PointToSting(pos);
				*/

				if (strText.find("医院") != string::npos)
				{
					m_MarkedPosMap["HospName"] = strText;
					int pos[4];
					pos[0] = charPos[0].pos[0];
					pos[1] = charPos[0].pos[1];
					pos[2] = charPos[0].pos[2];
					pos[3] = charPos[0].pos[3];
					string hosppos = PointToSting(pos);
					m_MarkedPosMap["HospPos"] = hosppos;
				}
				if (strText.find("姓名") != string::npos)
				{
					m_MarkedPosMap["TextName"] = strText;
					int pos[4];
					pos[0] = charPos[0].pos[0];
					pos[1] = charPos[0].pos[1];
					pos[2] = charPos[0].pos[2];
					pos[3] = charPos[0].pos[3];
					string hosppos = PointToSting(pos);
					m_MarkedPosMap["TextPos"] = hosppos;
				}
				int tilepos[4];
				tilepos[0] = m_titlePos[0].NamePos.pos[0];
				tilepos[1] = m_titlePos[0].NamePos.pos[1];
				tilepos[2] = m_titlePos[0].NamePos.pos[2];
				tilepos[3] = m_titlePos[0].NamePos.pos[3];
				string stilepos = PointToSting(tilepos);
				m_MarkedPosMap["tileName"] = "项目名称";
				m_MarkedPosMap["tilePos"] = stilepos;

				//CString cnamepos;
				//cnamepos.Format("%s", stilepos.data());
				//AfxMessageBox(cnamepos);

				int pricepos[4];
				pricepos[0] = m_titlePos[0].PricePos.pos[0];
				pricepos[1] = m_titlePos[0].PricePos.pos[1];
				pricepos[2] = m_titlePos[0].PricePos.pos[2];
				pricepos[3] = m_titlePos[0].PricePos.pos[3];
				string spricepos = PointToSting(pricepos);
				m_MarkedPosMap["PriceName"] = "金额";
				m_MarkedPosMap["PricePos"] = spricepos;
				//CString cpricepos;
				//cpricepos.Format("%s", spricepos.data());
				//AfxMessageBox(cpricepos);

			}
			//重新计算标题坐标 

			if (m_filemarkpos.find("HospName") != m_filemarkpos.end())
			{
				string pos = m_filemarkpos["HospPos"];
			}


			//重新计算标题坐标 			
			////cnt << strText << endl;
			if (type == 1)
				PushRecogResult(strText, strPos, charPos);
			else
				PushRecogResult2(strText, strPos, charPos);

		}

	}
#endif 

}
#endif

//v_title
int CExtractInfo::MergeTitle()
{
	vector<RecogResult> tempTitle;
	vector<int> mergeFlag;

	tempTitle.assign(v_title.begin(), v_title.end());
	sort(tempTitle.begin(), tempTitle.end());
	mergeFlag.resize(tempTitle.size());

	//kang 异常修改
	if (tempTitle.size() > 0)
	{
		for (int i = 0; i < tempTitle.size() - 1; i++)
		{
			mergeFlag[i] = 0;
		}
	}

	//for (int i = 0; i < tempTitle.size() - 1; i++)
	//{
	//	mergeFlag[i] = 0;
	//}

	v_title.clear();

	//kang-最后一行未识别 
	for (int i = 0; i < tempTitle.size(); i++)
	{
		//////cnt << i << ":" << tempTitle[i].RResult << mergeFlag[i] << endl;

		//找到水平方向和该点最近的点
		float minDis = 100000;
		int minID = -1;
		for (int j = 1; j < 4; j++)
		{
			if (i + j < tempTitle.size())
			{
				if (mergeFlag[i + j] == 0)
				{
					float dis = fabs(tempTitle[i + j].Pos[0] - tempTitle[i].Pos[0]);
					if (dis < minDis && fabs(tempTitle[i].Pos[1] - tempTitle[i + j].Pos[1]) < tempTitle[i].Pos[3] / 2)
					{
						minID = i + j;
						minDis = dis;
					}
				}
			}
		}

		if (mergeFlag[i] == 0)
		{
			v_title.push_back(tempTitle[i]);
			if (minID != -1)
			{
				//	////cnt <<i<< tempTitle[i].RResult << "--" << tempTitle[minID].RResult<<endl;
				if (tempTitle[i].titleID == tempTitle[minID].titleID)  //同属于一个标题栏。满足合并条件
				{
					mergeFlag[minID] = 1;
					vector<RecogResult> temp_vtitle;
					temp_vtitle.assign(v_title.begin(), v_title.end());
					sort(temp_vtitle.begin(), temp_vtitle.end());
					//识别名称更新
					//识别位置更新 kang-项目同行合并
					if (v_title[v_title.size() - 1].Pos[0] > tempTitle[minID].Pos[0])   //同行minID在左
					{
						v_title[v_title.size() - 1].RResult = tempTitle[minID].RResult + temp_vtitle[temp_vtitle.size() - 1].RResult;
						if (v_title[v_title.size() - 1].Pos[1] < tempTitle[minID].Pos[1] && (v_title[v_title.size() - 1].Pos[1] + v_title[v_title.size() - 1].Pos[3] < tempTitle[minID].Pos[1] + tempTitle[minID].Pos[3]))
						{
							//左上左边长
							v_title[v_title.size() - 1].Pos[0] = tempTitle[minID].Pos[0];
							v_title[v_title.size() - 1].Pos[1] = tempTitle[minID].Pos[1];
							v_title[v_title.size() - 1].Pos[2] = temp_vtitle[temp_vtitle.size() - 1].Pos[0] + temp_vtitle[temp_vtitle.size() - 1].Pos[2] - tempTitle[minID].Pos[0];
							v_title[v_title.size() - 1].Pos[3] = tempTitle[minID].Pos[3];

						}
						else if (v_title[v_title.size() - 1].Pos[1] < tempTitle[minID].Pos[1] && (v_title[v_title.size() - 1].Pos[0] + v_title[v_title.size() - 1].Pos[3] > tempTitle[minID].Pos[0] + tempTitle[minID].Pos[3]))
						{
							//左上右边长
							v_title[v_title.size() - 1].Pos[0] = tempTitle[minID].Pos[0];
							v_title[v_title.size() - 1].Pos[1] = tempTitle[minID].Pos[1];
							v_title[v_title.size() - 1].Pos[2] = temp_vtitle[temp_vtitle.size() - 1].Pos[0] + temp_vtitle[temp_vtitle.size() - 1].Pos[2] - tempTitle[minID].Pos[0];
							v_title[v_title.size() - 1].Pos[3] = tempTitle[minID].Pos[1] + tempTitle[minID].Pos[3] - temp_vtitle[temp_vtitle.size() - 1].Pos[1];

						}
						else if (v_title[v_title.size() - 1].Pos[1] > tempTitle[minID].Pos[1] && (v_title[v_title.size() - 1].Pos[0] + v_title[v_title.size() - 1].Pos[3] < tempTitle[minID].Pos[0] + tempTitle[minID].Pos[3]))
						{
							//左下左边长
							v_title[v_title.size() - 1].Pos[0] = tempTitle[minID].Pos[0];
							v_title[v_title.size() - 1].Pos[1] = temp_vtitle[temp_vtitle.size() - 1].Pos[1];
							v_title[v_title.size() - 1].Pos[2] = temp_vtitle[temp_vtitle.size() - 1].Pos[0] + temp_vtitle[temp_vtitle.size() - 1].Pos[2] - tempTitle[minID].Pos[0];
							v_title[v_title.size() - 1].Pos[3] = tempTitle[minID].Pos[1] + tempTitle[minID].Pos[3] - temp_vtitle[temp_vtitle.size() - 1].Pos[1];

						}
						else if (v_title[v_title.size() - 1].Pos[1] > tempTitle[minID].Pos[1] && (v_title[v_title.size() - 1].Pos[0] + v_title[v_title.size() - 1].Pos[3] < tempTitle[minID].Pos[0] + tempTitle[minID].Pos[3]))
						{
							//左下右边长
							v_title[v_title.size() - 1].Pos[0] = tempTitle[minID].Pos[0];
							v_title[v_title.size() - 1].Pos[1] = temp_vtitle[temp_vtitle.size() - 1].Pos[1];
							v_title[v_title.size() - 1].Pos[2] = temp_vtitle[temp_vtitle.size() - 1].Pos[0] + temp_vtitle[temp_vtitle.size() - 1].Pos[2] - tempTitle[minID].Pos[0];
							v_title[v_title.size() - 1].Pos[3] = temp_vtitle[temp_vtitle.size() - 1].Pos[3];

						}
					}
					else
					{
						v_title[v_title.size() - 1].RResult = temp_vtitle[temp_vtitle.size() - 1].RResult + tempTitle[minID].RResult;
						if (v_title[v_title.size() - 1].Pos[1] > tempTitle[minID].Pos[1] && (v_title[v_title.size() - 1].Pos[1] + v_title[v_title.size() - 1].Pos[3] < tempTitle[minID].Pos[1] + tempTitle[minID].Pos[3]))
						{
							//右上右边长
							v_title[v_title.size() - 1].Pos[0] = temp_vtitle[temp_vtitle.size() - 1].Pos[0];
							v_title[v_title.size() - 1].Pos[1] = tempTitle[minID].Pos[1];
							v_title[v_title.size() - 1].Pos[2] = tempTitle[minID].Pos[0] + tempTitle[minID].Pos[2] - temp_vtitle[temp_vtitle.size() - 1].Pos[0];
							v_title[v_title.size() - 1].Pos[3] = temp_vtitle[temp_vtitle.size() - 1].Pos[3];

						}
						else if (v_title[v_title.size() - 1].Pos[1] > tempTitle[minID].Pos[1] && (v_title[v_title.size() - 1].Pos[1] + v_title[v_title.size() - 1].Pos[3] > tempTitle[minID].Pos[1] + tempTitle[minID].Pos[3]))
						{
							//右上左边长
							v_title[v_title.size() - 1].Pos[0] = temp_vtitle[temp_vtitle.size() - 1].Pos[0];
							v_title[v_title.size() - 1].Pos[1] = tempTitle[minID].Pos[1];
							v_title[v_title.size() - 1].Pos[2] = tempTitle[minID].Pos[0] + tempTitle[minID].Pos[2] - temp_vtitle[temp_vtitle.size() - 1].Pos[0];
							v_title[v_title.size() - 1].Pos[3] = temp_vtitle[temp_vtitle.size() - 1].Pos[1] + temp_vtitle[temp_vtitle.size() - 1].Pos[3] - tempTitle[minID].Pos[1];
						}
						if (v_title[v_title.size() - 1].Pos[1] < tempTitle[minID].Pos[1] && (v_title[v_title.size() - 1].Pos[1] + v_title[v_title.size() - 1].Pos[3] < tempTitle[minID].Pos[1] + tempTitle[minID].Pos[3]))
						{
							//右下右边长
							v_title[v_title.size() - 1].Pos[0] = temp_vtitle[temp_vtitle.size() - 1].Pos[0];
							v_title[v_title.size() - 1].Pos[1] = temp_vtitle[temp_vtitle.size() - 1].Pos[1];
							v_title[v_title.size() - 1].Pos[2] = tempTitle[minID].Pos[0] + tempTitle[minID].Pos[2] - temp_vtitle[temp_vtitle.size() - 1].Pos[0];
							v_title[v_title.size() - 1].Pos[3] = tempTitle[minID].Pos[1] + tempTitle[minID].Pos[3] - temp_vtitle[temp_vtitle.size() - 1].Pos[1];

						}
						else if (v_title[v_title.size() - 1].Pos[1] < tempTitle[minID].Pos[1] && (v_title[v_title.size() - 1].Pos[1] + v_title[v_title.size() - 1].Pos[3] > tempTitle[minID].Pos[1] + tempTitle[minID].Pos[3]))
						{
							//右下左边长
							v_title[v_title.size() - 1].Pos[0] = temp_vtitle[temp_vtitle.size() - 1].Pos[0];
							v_title[v_title.size() - 1].Pos[1] = temp_vtitle[temp_vtitle.size() - 1].Pos[1];
							v_title[v_title.size() - 1].Pos[2] = tempTitle[minID].Pos[0] + tempTitle[minID].Pos[2] - temp_vtitle[temp_vtitle.size() - 1].Pos[0];
							v_title[v_title.size() - 1].Pos[3] = temp_vtitle[temp_vtitle.size() - 1].Pos[3];
						}
					}
					////识别名称更新
					//			//识别位置更新
					//if (v_title[v_title.size() - 1].Pos[0] < tempTitle[minID].Pos[0])   //同行右
					//{
					//	if (fabs(v_title[v_title.size() - 1].Pos[0] + v_title[v_title.size() - 1].Pos[2] - tempTitle[minID].Pos[0]) < 30)
					//	{
					//		v_title[v_title.size() - 1].Pos[2] = tempTitle[minID].Pos[0] + tempTitle[minID].Pos[2] - v_title[v_title.size() - 1].Pos[0];
					//		v_title[v_title.size() - 1].RResult = v_title[v_title.size() - 1].RResult + tempTitle[minID].RResult;
					//	}
					//}					 
					//else//同行左
					//{
					//	if (fabs(tempTitle[minID].Pos[0] + tempTitle[minID].Pos[2] - v_title[v_title.size() - 1].Pos[0]) < 30)
					//	{
					//		v_title[v_title.size() - 1].Pos[0] = tempTitle[minID].Pos[0];
					//		v_title[v_title.size() - 1].Pos[2] = v_title[v_title.size() - 1].Pos[0] + v_title[v_title.size() - 1].Pos[2] - v_title[v_title.size() - 1].Pos[0];
					//		v_title[v_title.size() - 1].RResult = tempTitle[minID].RResult + v_title[v_title.size() - 1].RResult;
					//	}						
					//}
				}
			}

			///	////cnt << v_title[v_title.size() - 1].RResult << endl;

		}
	}

	return 1;
}

cv::Rect CExtractInfo::PosToTect(PosOfChar& titlpos)
{
	cv::Rect rect;

	rect.x = titlpos.pos[0];
	rect.y = titlpos.pos[1];
	rect.width = titlpos.pos[2];
	rect.height = titlpos.pos[3];

	return rect;
}

cv::Rect CExtractInfo::ArrayToTect(float *titlpos)
{
	cv::Rect rect;

	rect.x = titlpos[0];
	rect.y = titlpos[1];
	rect.width = titlpos[2];
	rect.height = titlpos[3];

	return rect;
}

#endif


int CExtractInfo::MergeForTitle()
{
	///	//cnt <<"候选："<< CandTitleList.size() << endl;

	if (CandTitleList.size() <= 0)
		return 0;

	vector<int> flagVec;

	flagVec.resize(CandTitleList.size());
	for (int i = 0; i < this->CandTitleList.size(); i++)
	{

		flagVec[i] = 0;
	}
	for (int i = 0; i < this->CandTitleList.size(); i++)
	{
		if (this->CandTitleList[i].Flag == 11 && flagVec[i] == 0)
		{
			for (int j = 0; j < this->CandTitleList.size(); j++)
			{
				if (this->CandTitleList[j].Flag == 12 && flagVec[j] == 0)
				{
					//在同一行，且距离很近
					//		//cnt << "候选：" << CandTitleList[i].RResult << this->CandTitleList[i].Pos[1] <<"--"<< this->CandTitleList[j].Pos[1]<< "++"<<this->CandTitleList[j].Pos[3]<<endl;

					if (fabs(this->CandTitleList[j].Pos[1] - this->CandTitleList[i].Pos[1]) < this->CandTitleList[j].Pos[3] / 2 &&  //同一行条件
						(this->CandTitleList[j].Pos[0] - this->CandTitleList[i].Pos[0] - this->CandTitleList[i].Pos[2]) < 100 &&
						(this->CandTitleList[j].Pos[0] - this->CandTitleList[i].Pos[0] - this->CandTitleList[i].Pos[2]) > 0)
					{
						RecogResult recog[2];

						//cnt << this->CandTitleList[j].Pos[0] - this->CandTitleList[i].Pos[0] - this->CandTitleList[i].Pos[2] << endl;

						recog[1].RResult = this->CandTitleList[i].RResult + this->CandTitleList[j].RResult;
						recog[1].Flag = 4;
						recog[1].Pos[0] = this->CandTitleList[i].Pos[0];//同上
						recog[1].Pos[1] = this->CandTitleList[i].Pos[1];
						recog[1].Pos[2] = this->CandTitleList[j].Pos[0] + this->CandTitleList[j].Pos[2] - recog[1].Pos[0];
						recog[1].Pos[3] = this->CandTitleList[i].Pos[3];
						recog[1].IsMatched = -1;

						flagVec[i] = 1;
						flagVec[j] = 1;
						RecoglList.push_back(recog[1]);
					}
				}
			}
		}
	}
	return 0;
}

int CExtractInfo::ProcessForYuYaoHos()
{
	int titID = -1;
	int priID = -1;
	for (int i = 0; i < this->OrgRecoglList.size(); i++)
	{
		string str = OrgRecoglList[i].RResult;
		if (str.find("病区床位") != string::npos)
		{
			titID = i;
			break;
		}

	}

	if (titID != -1)
	{
		for (int i = 0; i < this->OrgRecoglList.size(); i++)
		{
			string str = OrgRecoglList[i].RResult;
			if (str.find("合计") != string::npos && OrgRecoglList[i].Pos[1] < OrgRecoglList[titID].Pos[1])
			{
				priID = i;
				break;
			}

		}
	}

	if (titID != -1 && priID != -1)
	{
		TitlePos titps;

		titps.NamePos.pos[0] = this->OrgRecoglList[titID].Pos[0];
		titps.NamePos.pos[1] = this->OrgRecoglList[titID].Pos[1];
		titps.NamePos.pos[2] = this->OrgRecoglList[titID].Pos[2] * 3;
		titps.NamePos.pos[3] = this->OrgRecoglList[titID].Pos[3];

		titps.PricePos.pos[0] = this->OrgRecoglList[priID].Pos[0] - this->OrgRecoglList[priID].Pos[2] / 2;
		titps.PricePos.pos[1] = titps.NamePos.pos[1];
		titps.PricePos.pos[2] = this->OrgRecoglList[priID].Pos[0] + this->OrgRecoglList[priID].Pos[2] - titps.PricePos.pos[0] + 20;
		titps.PricePos.pos[3] = titps.NamePos.pos[3];

		//	cout << titps.PricePos.pos[0] << "--" << titps.PricePos.pos[1] << "--" << titps.PricePos.pos[2] << "--" << titps.PricePos.pos[3] << endl;

		this->m_titlePos.push_back(titps);
	}

	return 1;
}

int CExtractInfo::ProcessForSpecialHos()
{
	switch (this->HospitalID)
	{
	case 0:  //
		if (this->m_titlePos.size() > 0)
		{
			this->m_titlePos[0].PricePos.pos[0] = this->m_titlePos[0].PricePos.pos[0] - 30;  //解决标题偏移问题			
		}
		break;
	case 1:  //余姚市人民医院	
		if (this->m_titlePos.size() == 0)
		{
			ProcessForYuYaoHos();
		}
		break;
	default:
		break;
	}
	return 0;
}


float CExtractInfo::overlap(int titleid, int priceid)
{
	int left = -1, right = -1;
	float overlap = 0;
	if (this->m_titlePos[titleid].PricePos.pos[2] < 10)
		return 0.0;

	if (this->v_price[priceid].Pos[0] + this->v_price[priceid].Pos[2] < this->m_titlePos[titleid].PricePos.pos[0])
		return 0.0;
	else if (this->m_titlePos[titleid].PricePos.pos[0] + this->m_titlePos[titleid].PricePos.pos[2] > this->v_price[priceid].Pos[0])
		return 0.0;
	else if (this->v_price[priceid].Pos[0] + this->v_price[priceid].Pos[2] < this->m_titlePos[titleid].PricePos.pos[0] + this->m_titlePos[titleid].PricePos.pos[2])
	{
		overlap = this->v_price[priceid].Pos[0] + this->v_price[priceid].Pos[2] - this->m_titlePos[titleid].PricePos.pos[0];
		overlap = overlap / this->m_titlePos[priceid].PricePos.pos[2];
	}
	else if (this->m_titlePos[titleid].PricePos.pos[0] + this->m_titlePos[titleid].PricePos.pos[2] < this->v_price[priceid].Pos[0] + this->v_price[priceid].Pos[2])
	{
		overlap = this->m_titlePos[titleid].PricePos.pos[0] + this->m_titlePos[titleid].PricePos.pos[2] - this->v_price[priceid].Pos[0];
		overlap = overlap / this->m_titlePos[priceid].PricePos.pos[2];
	}


	return 0;
}
int CExtractInfo::GetRecogedTable()
{
	//-1 180度，0无表格，1有表格
	clock_t start, finish1, finish2;
	double totaltime;
	start = clock();

	cout << "合合字符串大小____" << m_strRecogJson.size() / 1024 << "k" << endl;
	if (!m_reader.parse(m_strRecogJson, m_root))
		return 0;

	//旋转180会有问题
	int rotate_angle = m_root["rotate_angle"].asInt();
	if (rotate_angle == 180 || rotate_angle == 90)
		return -1;

	//ofstream outfile;//创建文件
	//outfile.open("C:\\111.txt");
	//outfile << m_strRecogJson << endl;
	//outfile.close();

	m_data = m_root["table"];

	//表格数>3转无表格处理
	if (m_data.size() > 4)
		return 0;
	this->TableSet.clear();//
	TableInfo tableMatrix;

	finish1 = clock();
	cout << "字符串耗时____" << (double)(finish1 - start) / CLOCKS_PER_SEC << endl;



	for (int i = 0; i < m_data.size(); i++)
	{
		Json::Value tableType;
		tableType = std::move(m_data[i]["type"]);

		if (tableType.asString() != "false")
		{
			int rows(m_data[i]["form_rows"].asInt());
			int cols(m_data[i]["form_columns"].asInt());

			Json::Value formRows(m_data[i]["rows_height"]);
			Json::Value colsWidth(m_data[i]["cols_width"]);
			tableMatrix.RowHei.clear();
			tableMatrix.ColWid.clear();

			tableMatrix.RowHei.resize(formRows.size());
			tableMatrix.ColWid.resize(colsWidth.size());

			for (int h = 0; h < formRows.size(); h++)
				tableMatrix.RowHei[h] = formRows[h].asInt();
			for (int w = 0; w < colsWidth.size(); w++)
				tableMatrix.ColWid[w] = colsWidth[w].asInt();

			//初始化矩阵元素
			tableMatrix.MatrixTable.resize(rows);
			for (int j = 0; j < tableMatrix.MatrixTable.size(); j++)
				tableMatrix.MatrixTable[j].resize(cols);

			Json::Value blocks = m_data[i]["form_blocks"];

			vector<PosOfChar> charPosTemp;
			vector<vector<PosOfChar>> allCharPosTemp;
			vector<string> allStrTextTemp;

			for (int j = 0; j < blocks.size(); j++)
			{
				Json::Value::UInt start_row(blocks[j]["start_row"].asInt());
				Json::Value::UInt start_column(blocks[j]["start_column"].asInt());
				Json::Value::UInt end_row(blocks[j]["end_row"].asInt());
				Json::Value::UInt end_column(blocks[j]["end_column"].asInt());

				string strText(blocks[j]["data"].asString());
#if defined(_WIN32)
				CStringOperator::UTF8ToAnsi(strText);
#endif	
				Json::Value org_position(blocks[j]["org_position"]);

				PosOfChar posChar;
				charPosTemp.clear();
				allCharPosTemp.clear();
				allStrTextTemp.clear();

				Json::Value lines(blocks[j]["lines"]);

				vector<PosOfChar> charPos;
				for (int m = 0; m < lines.size(); m++)
				{
					string text(lines[m]["text"].asString());				
#if defined(_WIN32)
					CStringOperator::UTF8ToAnsi(text);
#endif				

					Json::Value char_polygons(lines[m]["char_polygons"]);
					charPos.clear();

					for (int k = 0; k < char_polygons.size(); k++)
					{
						posChar.pos[0] = std::move(char_polygons[k][0u].asInt());
						posChar.pos[1] = std::move(char_polygons[k][1u].asInt());
						posChar.pos[2] = std::move(char_polygons[k][2u].asInt() - char_polygons[k][0u].asInt());
						posChar.pos[3] = std::move(char_polygons[k][5u].asInt() - char_polygons[k][3u].asInt());
						charPos.emplace_back(posChar);
					}
					if (m == 0)
						charPosTemp.assign(charPos.begin(), charPos.end());
					allCharPosTemp.emplace_back(charPos);
					allStrTextTemp.emplace_back(text);
				}

				for (int k = start_row; k <= end_row; k++)
				{
					for (int t = start_column; t <= end_column; t++)
					{
						if (charPosTemp.size() > 0)
							tableMatrix.MatrixTable[k][t].charPos.assign(charPosTemp.begin(), charPosTemp.end());
						if (allCharPosTemp.size() > 0)
							tableMatrix.MatrixTable[k][t].allCharPos.assign(allCharPosTemp.begin(), allCharPosTemp.end());
						if (allStrTextTemp.size() > 0)
							tableMatrix.MatrixTable[k][t].allStrText.assign(allStrTextTemp.begin(), allStrTextTemp.end());

						tableMatrix.MatrixTable[k][t].strText = std::move(strText);

						tableMatrix.MatrixTable[k][t].position[0] = std::move(org_position[0u].asInt());
						tableMatrix.MatrixTable[k][t].position[1] = std::move(org_position[1u].asInt());
						tableMatrix.MatrixTable[k][t].position[2] = std::move(org_position[2u].asInt());
						tableMatrix.MatrixTable[k][t].position[3] = std::move(org_position[3u].asInt());
						tableMatrix.MatrixTable[k][t].position[4] = std::move(org_position[4u].asInt());
						tableMatrix.MatrixTable[k][t].position[5] = std::move(org_position[5u].asInt());
						tableMatrix.MatrixTable[k][t].position[6] = std::move(org_position[6u].asInt());
						tableMatrix.MatrixTable[k][t].position[7] = std::move(org_position[7u].asInt());

						tableMatrix.MatrixTable[k][t].rowColumn[0] = std::move(start_row);
						tableMatrix.MatrixTable[k][t].rowColumn[1] = std::move(start_column);
						tableMatrix.MatrixTable[k][t].rowColumn[2] = std::move(end_row);
						tableMatrix.MatrixTable[k][t].rowColumn[3] = std::move(end_column);
					}
				}
			}
			TableSet.emplace_back(tableMatrix);
		}
	}
	finish2 = clock();
	cout << "存入表格耗时____" << (double)(finish2 - finish1) / CLOCKS_PER_SEC << endl;
	if (TableSet.size() > 0)
		return 1;
	else
		return 0;
}

int CExtractInfo::DecodeTableAgain()
{
	//拆分跨行
	for (int i = 0; i < TableSet.size(); i++)
	{
		SplitTableByWholeRowCol(i, 1);

		SplitTableByWholeRowCol(i, 2);

		SplitTableByWholeRowCol(i, 3);
	}
	return 1;
}

int CExtractInfo::DecodeRecogedTable(int type)
{
	try
	{
		if (!m_reader.parse(m_strRecogJson, m_root))
			return 0;
		int rotate_angle = m_root["rotate_angle"].asInt();
		if (rotate_angle == 180)
			return 0;

		m_data = m_root["table"];

		for (int i = 0; i < m_data.size(); i++)
		{
			Json::Value tableType;
			tableType = m_data[i]["type"];

			Json::Value lines;

			if (tableType.asString() == "false")
			{
				lines = m_data[i]["lines"];
				for (int j = 0; j < lines.size(); j++)
				{
					Json::Value curline;

					curline = lines[j];

					string strText = curline["text"].asString();

#if defined(_WIN32)
					CStringOperator::UTF8ToAnsi(strText);
#endif
					if (strText != "")
					{
						int pos[4];
						pos[0] = curline["poly"][0u].asInt();
						pos[1] = curline["poly"][1u].asInt();
						pos[2] = curline["poly"][2u].asInt() - curline["poly"][0u].asInt();
						pos[3] = curline["poly"][5u].asInt() - curline["poly"][3u].asInt();

						Json::Value charObj;
						charObj = curline["char_polygons"];

						vector<PosOfChar> charPos;
						charPos.resize(charObj.size());
						for (int k = 0; k < charObj.size(); k++)
						{
							charPos[k].pos[0] = charObj[k][0u].asInt();
							charPos[k].pos[1] = charObj[k][1u].asInt();
							charPos[k].pos[2] = charObj[k][2u].asInt() - charObj[k][0u].asInt();
							charPos[k].pos[3] = charObj[k][5u].asInt() - charObj[k][3u].asInt();
						}
						char buf[20];
						sprintf(buf, "{%d,%d,%d,%d}", pos[0], pos[1], pos[2], pos[3]);

						if (type == 1)
							PushRecogResult(strText, buf, charPos);
						else if (type == 2)
							PushRecogResult2(strText, buf, charPos);
					}
				}
			}
			else
			{
				lines = m_data[i]["form_blocks"];

				int p = lines.size();
				for (int j = 0; j < lines.size(); j++)
				{
					Json::Value curline;
					curline = lines[j]["lines"];
					for (int k = 0; k < curline.size(); k++)
					{
						string strText = curline[k]["text"].asString();
#if defined(_WIN32)
						CStringOperator::UTF8ToAnsi(strText);
#endif

						if (strText != "")
						{
							int pos[4];
							pos[0] = curline[k]["poly"][0u].asInt();
							pos[1] = curline[k]["poly"][1u].asInt();
							pos[2] = curline[k]["poly"][2u].asInt() - curline[k]["poly"][0u].asInt();
							pos[3] = curline[k]["poly"][5u].asInt() - curline[k]["poly"][3u].asInt();

							Json::Value charObj;
							charObj = curline[k]["char_polygons"];

							vector<PosOfChar> charPos;
							charPos.resize(charObj.size());
							for (int k = 0; k < charObj.size(); k++)
							{
								charPos[k].pos[0] = charObj[k][0u].asInt();
								charPos[k].pos[1] = charObj[k][1u].asInt();
								charPos[k].pos[2] = charObj[k][2u].asInt() - charObj[k][0u].asInt();
								charPos[k].pos[3] = charObj[k][5u].asInt() - charObj[k][3u].asInt();
							}
							char buf[20];
							sprintf(buf, "{%d,%d,%d,%d}", pos[0], pos[1], pos[2], pos[3]);

							if (type == 1)
								PushRecogResult(strText, buf, charPos);
							else if (type == 2)
								PushRecogResult2(strText, buf, charPos);
						}
					}
				}
			}
		}
		return 1;
	}
	catch (...)
	{
		return 1;
	}
}

void CExtractInfo::JudgeRowTableType()
{
	for (int m = 0; m < TableSet.size(); m++)
	{
		if (TableSet[m].TitleCol[0] == -1 || TableSet[m].TitleCol[3] == -1)
		{
			continue;
		}

		if (v_dj_table_set[m].size() != 0 && v_num_table_set[m].size() != 0)
		{
			for (int i = 0; i < v_title_table_set[m].size(); i++)
			{
				bool isDelete = false;
				if (i < 5)
				{
					for (int k = 0; k < TitleSet.size(); k++)
					{
						if (TitleSet[k].Flag == 4)
						{
							string strText = v_title_table_set[m][i].RResult;
							std::size_t found = strText.find(TitleSet[k].Name);
							if (found != std::string::npos)
							{
								isDelete = true;
								break;
							}
						}
					}
				}

				if (!v_title_table_set[m][i].RResult.empty())
				{
					//★、▲、△、*、#过滤

					vector<string> specialStr = { "★", "▲", "△", "*", "#" };
					for (auto temp : specialStr)
					{
						int pos = v_title_table_set[m][i].RResult.find(temp);
						if (pos >= 0)
							v_title_table_set[m][i].RResult = v_title_table_set[m][i].RResult.erase(pos, temp.size());
					}
				}

				//单价、数量、金额同时为空
				if (v_dj_table_set[m][i].RResult.empty() && v_num_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty())
				{
					isDelete = true;
				}
				//名称、单价或者名称、数量或者名称、金额为空
				if ((v_title_table_set[m][i].RResult.empty() && v_dj_table_set[m][i].RResult.empty())
					|| (v_title_table_set[m][i].RResult.empty() && v_num_table_set[m][i].RResult.empty())
					|| (v_title_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty()))
				{
					isDelete = true;
				}

				//名称==单价 或者 名称==数量 或者 名称==金额
				if ((v_title_table_set[m][i].RResult == v_dj_table_set[m][i].RResult)
					|| (v_title_table_set[m][i].RResult == v_num_table_set[m][i].RResult)
					|| (v_title_table_set[m][i].RResult == v_price_table_set[m][i].RResult))
				{
					isDelete = true;
				}

				//名称找到费、页、计且单价或数量为空
				if ((v_title_table_set[m][i].RResult.find("费") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					&& (v_dj_table_set[m][i].RResult.empty() || v_num_table_set[m][i].RResult.empty()))
				{
					isDelete = true;
				}

				//名称里能找到单价或者数量，且单价=数量时,且单价数量不为空
				if ((v_title_table_set[m][i].RResult.find(v_dj_table_set[m][i].RResult) != std::string::npos
					|| (v_title_table_set[m][i].RResult.find(v_num_table_set[m][i].RResult) != std::string::npos))
					&& (v_dj_table_set[m][i].RResult == v_num_table_set[m][i].RResult)
					&& (!v_dj_table_set[m][i].RResult.empty() && !v_num_table_set[m][i].RResult.empty()))
				{
					isDelete = true;
				}
				//名称找到合计、小计、总计、姓名、性别、年龄、Page、病人、住院号、日期、患者、ID号
				if (v_title_table_set[m][i].RResult.find("合计") != std::string::npos || v_title_table_set[m][i].RResult.find("小计") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("总计") != std::string::npos || v_title_table_set[m][i].RResult.find("姓名") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("性别") != std::string::npos || v_title_table_set[m][i].RResult.find("年龄") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("Page") != std::string::npos || v_title_table_set[m][i].RResult.find("住院号") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("日期") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("患者") != std::string::npos || v_title_table_set[m][i].RResult.find("ID号") != std::string::npos)
				{
					isDelete = true;
				}
				//名称找到第&页、共&页、共&条
				if ((v_title_table_set[m][i].RResult.find("第") != std::string::npos && v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					|| (v_title_table_set[m][i].RResult.find("共") != std::string::npos && v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					|| (v_title_table_set[m][i].RResult.find("共") != std::string::npos && v_title_table_set[m][i].RResult.find("条") != std::string::npos))
				{
					isDelete = true;
				}
				//名称为空
				if (v_title_table_set[m][i].RResult.empty())
				{
					isDelete = true;
				}

				if (isDelete)
				{
					v_title_table_set[m].erase(v_title_table_set[m].begin() + i);
					v_price_table_set[m].erase(v_price_table_set[m].begin() + i);
					v_dj_table_set[m].erase(v_dj_table_set[m].begin() + i);
					v_num_table_set[m].erase(v_num_table_set[m].begin() + i);
					i--;
					continue;
				}
			}
		}
		else if (v_dj_table_set[m].size() == 0 && v_num_table_set[m].size() != 0)
		{
			//单价列为空、数量列不为空
			for (int i = 0; i < v_title_table_set[m].size(); i++)
			{
				bool isDelete = false;
				if (i < 5)
				{
					for (int k = 0; k < TitleSet.size(); k++)
					{
						if (TitleSet[k].Flag == 4)
						{
							string strText = v_title_table_set[m][i].RResult;
							std::size_t found = strText.find(TitleSet[k].Name);
							if (found != std::string::npos)
							{
								isDelete = true;
								break;
							}
						}
					}
				}
				if (!v_title_table_set[m][i].RResult.empty())
				{
					//★、▲、△、*、#过滤
					vector<string> specialStr = { "★", "▲", "△", "*", "#" };
					for (auto temp : specialStr)
					{
						int pos = v_title_table_set[m][i].RResult.find(temp);
						if (pos >= 0)
							v_title_table_set[m][i].RResult = v_title_table_set[m][i].RResult.erase(pos, temp.size());
					}
				}
				//名称、数量、金额同时为空或者 名称、数量或者名称、金额为空
				if (v_title_table_set[m][i].RResult.empty() && v_num_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty()
					|| (v_title_table_set[m][i].RResult.empty() && v_num_table_set[m][i].RResult.empty())
					|| (v_title_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty()))
				{
					isDelete = true;
				}
				//名称==数量 或者 名称==金额
				if ((v_num_table_set[m][i].RResult == v_title_table_set[m][i].RResult)
					|| (v_price_table_set[m][i].RResult == v_title_table_set[m][i].RResult))
				{
					isDelete = true;
				}
				//名称找到费、页、计且数量为空
				if ((v_title_table_set[m][i].RResult.find("费") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					&& v_num_table_set[m][i].RResult.empty())
				{
					isDelete = true;
				}

				//名称找到合计、小计、总计、姓名、性别、年龄、Page、病人、住院号、日期、患者、ID号
				if (v_title_table_set[m][i].RResult.find("合计") != std::string::npos || v_title_table_set[m][i].RResult.find("小计") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("总计") != std::string::npos || v_title_table_set[m][i].RResult.find("姓名") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("性别") != std::string::npos || v_title_table_set[m][i].RResult.find("年龄") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("Page") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("住院号") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("日期") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("患者") != std::string::npos || v_title_table_set[m][i].RResult.find("ID号") != std::string::npos)
				{
					isDelete = true;
				}
				//名称找到第&页、共&页、共&条
				if ((v_title_table_set[m][i].RResult.find("第") != std::string::npos && v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					|| (v_title_table_set[m][i].RResult.find("共") != std::string::npos && v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					|| (v_title_table_set[m][i].RResult.find("共") != std::string::npos && v_title_table_set[m][i].RResult.find("条") != std::string::npos))
				{
					isDelete = true;
				}
				//名称为空
				if (v_title_table_set[m][i].RResult.empty())
				{
					isDelete = true;
				}

				if (isDelete)
				{
					v_title_table_set[m].erase(v_title_table_set[m].begin() + i);
					v_price_table_set[m].erase(v_price_table_set[m].begin() + i);
					v_num_table_set[m].erase(v_num_table_set[m].begin() + i);
					i--;
					continue;
				}
			}

		}
		else if (v_dj_table_set[m].size() != 0 && v_num_table_set[m].size() == 0)
		{
			//单价列不为空、数量列为空
			for (int i = 0; i < v_title_table_set[m].size(); i++)
			{
				bool isDelete = false;
				if (i < 5)
				{
					for (int k = 0; k < TitleSet.size(); k++)
					{
						if (TitleSet[k].Flag == 4)
						{
							string strText = v_title_table_set[m][i].RResult;
							std::size_t found = strText.find(TitleSet[k].Name);
							if (found != std::string::npos)
							{
								isDelete = true;
								break;
							}
						}
					}
				}

				if (!v_title_table_set[m][i].RResult.empty())
				{
					//★、▲、△、*、#过滤
					vector<string> specialStr = { "★", "▲", "△", "*", "#" };
					for (auto temp : specialStr)
					{
						int pos = v_title_table_set[m][i].RResult.find(temp);
						if (pos >= 0)
							v_title_table_set[m][i].RResult = v_title_table_set[m][i].RResult.erase(pos, temp.size());
					}
				}
				//名称、单价、金额同时为空，或者名称、单价为空或者名称、金额为空
				if (v_title_table_set[m][i].RResult.empty() && v_dj_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty()
					|| (v_title_table_set[m][i].RResult.empty() && v_dj_table_set[m][i].RResult.empty())
					|| (v_title_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty()))
				{
					isDelete = true;
				}

				//名称=单价或者名称=金额
				if (v_dj_table_set[m][i].RResult == v_title_table_set[m][i].RResult
					|| v_title_table_set[m][i].RResult == v_price_table_set[m][i].RResult)
				{
					isDelete = true;
				}
				//名称找到费、页、计且单价或单价为空
				if ((v_title_table_set[m][i].RResult.find("费") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					&& v_dj_table_set[m][i].RResult.empty())
				{
					isDelete = true;
				}

				//名称找到合计、小计、总计、姓名、性别、年龄、Page、病人、住院号、日期、患者、ID号
				if (v_title_table_set[m][i].RResult.find("合计") != std::string::npos || v_title_table_set[m][i].RResult.find("小计") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("总计") != std::string::npos || v_title_table_set[m][i].RResult.find("姓名") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("性别") != std::string::npos || v_title_table_set[m][i].RResult.find("年龄") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("Page") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("住院号") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("日期") != std::string::npos
					|| v_title_table_set[m][i].RResult.find("患者") != std::string::npos || v_title_table_set[m][i].RResult.find("ID号") != std::string::npos)
				{
					isDelete = true;
				}
				//名称找到第&页、共&页、共&条
				if ((v_title_table_set[m][i].RResult.find("第") != std::string::npos && v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					|| (v_title_table_set[m][i].RResult.find("共") != std::string::npos && v_title_table_set[m][i].RResult.find("页") != std::string::npos)
					|| (v_title_table_set[m][i].RResult.find("共") != std::string::npos && v_title_table_set[m][i].RResult.find("条") != std::string::npos))
				{
					isDelete = true;
				}
				//名称为空
				if (v_title_table_set[m][i].RResult.empty())
				{
					isDelete = true;
				}
				if (isDelete)
				{
					v_title_table_set[m].erase(v_title_table_set[m].begin() + i);
					v_price_table_set[m].erase(v_price_table_set[m].begin() + i);
					v_dj_table_set[m].erase(v_dj_table_set[m].begin() + i);
					i--;
					continue;
				}
			}
		}


		int djNum = -1;
		int priceNum = -1;
		int numPrice = -1;


		if (v_dj_table_set[m].size() != 0 && v_price_table_set[m].size() != 0 && v_num_table_set[m].size() != 0)
		{
			//列校验，确定当前列小数点所在位置，如果行检验不准确，进行填充
			djNum = FindDots(v_dj_table_set[m]);
			priceNum = FindDots(v_price_table_set[m]);
			numPrice = FindDots(v_num_table_set[m]);

			for (int i = 0; i < v_price_table_set[m].size(); i++)
			{
				//数量	
				if (!v_price_table_set[m][i].RResult.empty() && v_dj_table_set[m][i].RResult.empty() && v_num_table_set[m][i].RResult.empty())
				{
					std::string price = v_price_table_set[m][i].RResult;
					std::string dj = v_dj_table_set[m][i].RResult;
					std::string num = v_num_table_set[m][i].RResult;

					if (atof(dj.c_str()) >0 && atof(num.c_str()) > 0 && atof(price.c_str()) > 0)
					{
						if (atof(dj.c_str()) * atof(num.c_str()) == atof(price.c_str()))
						{
							continue;
						}
						else
						{
							if (!IsValidNumber(price))
								continue;
							//先检验金额
							if (price.find('.') != price.npos)//没找到小数点
							{
								if (price[i] == -1 && price.size() > 1 && price.size() >= priceNum && priceNum > 0)
								{
									//没有小数点再进行补，存在则跳过
									string str1 = price.substr(0, price.size() - priceNum + 1);
									string str2 = price.substr(price.size() - priceNum + 1, price.size());
									string temp = price.substr(0, price.size() - priceNum + 1) + "." + price.substr(price.size() - priceNum + 1, price.size());
									v_price_table_set[m][i].RResult = temp;
									price = temp;
								}

							}

							//再检验单价
							if (atof(dj.c_str()) > 0 && atof(num.c_str()) > 0 && atof(price.c_str()) > 0)
							{
								if (atof(dj.c_str()) * atof(num.c_str()) == atof(price.c_str()))
								{
									continue;
								}
								else
								{
									if (!IsValidNumber(dj))
										continue;

									if (dj.find('.') != dj.npos)//没找到小数点
									{
										if (dj[i] == -1 && dj.size() > 1 && dj.size() >= djNum && djNum > 0)
										{
											//没有小数点再进行补，存在则跳过
											string str1 = dj.substr(0, dj.size() - djNum + 1);
											string str2 = dj.substr(dj.size() - djNum + 1, dj.size());
											string temp = dj.substr(0, dj.size() - djNum + 1) + "." + dj.substr(dj.size() - djNum + 1, dj.size());
											v_dj_table_set[m][i].RResult = temp;
										}

									}
								}
							}
						}
					}
				}
			}
		}

		//数字处理
		if (v_dj_table_set.size() != 0)
		{
			for (int i = 0; i < v_dj_table_set[m].size(); i++)
			{
				if (!v_dj_table_set[m][i].RResult.empty())
				{
					//单价
					replace_all(v_dj_table_set[m][i].RResult, "￥", "");
					//金额中识别出不是数字不添加
					//去除中文字符
					extractNumber(v_dj_table_set[m][i].RResult, v_dj_table_set[m][i].RResult);
					if (IsValidElem(v_dj_table_set[m][i].RResult) == 0)
					{
						if (v_dj_table_set[m][i].RResult.empty())
						{
							v_dj_table_set[m][i].charPos.clear();
							v_dj_table_set[m][i].Pos[0] = -1;
							v_dj_table_set[m][i].Pos[1] = -1;
							v_dj_table_set[m][i].Pos[2] = -1;
							v_dj_table_set[m][i].Pos[3] = -1;
						}
						else
						{
							//HandleLongPrice(ele);//TODO 把尾部过长的部分去掉
							if (v_dj_table_set[m][i].RResult.size() > 10)
								v_dj_table_set[m][i].RResult = "0";
							if (traitNumber(v_dj_table_set[m][i].RResult, 4))
							{

								v_dj_table_set[m][i].RResult = v_dj_table_set[m][i].RResult;
							}
						}
					}
				}
			}
		}
		if (v_price_table_set.size() != 0)
		{
			for (int i = 0; i < v_price_table_set[m].size(); i++)
			{
				if (i == v_price_table_set[m].size() - 2)
					int pp = 0;
				//金额	
				if (!v_price_table_set[m][i].RResult.empty())
				{
					//替换￥，不然会识别为有中文而不添加到待选项中
					replace_all(v_price_table_set[m][i].RResult, "￥", "");
					//金额中识别出不是数字不添加
					//WYP 去除中文字符
					extractNumber(v_price_table_set[m][i].RResult, v_price_table_set[m][i].RResult);
					if (IsValidElem(v_price_table_set[m][i].RResult) == 0)
					{
						if (v_price_table_set[m][i].RResult.empty())
						{
							v_price_table_set[m][i].charPos.clear();
							v_price_table_set[m][i].Pos[0] = -1;
							v_price_table_set[m][i].Pos[1] = -1;
							v_price_table_set[m][i].Pos[2] = -1;
							v_price_table_set[m][i].Pos[3] = -1;
						}
						else
						{
							//HandleLongPrice(ele);//TODO 把尾部过长的部分去掉
							if (v_price_table_set[m][i].RResult.size() > 10)
								v_price_table_set[m][i].RResult = "0";
							if (traitNumber(v_price_table_set[m][i].RResult, 2))
							{
								v_price_table_set[m][i].RResult = v_price_table_set[m][i].RResult;
							}
						}
					}
				}

			}
		}
		if (v_num_table_set.size() != 0)
		{
			for (int i = 0; i < v_num_table_set[m].size(); i++)
			{
				//数量	
				if (!v_num_table_set[m][i].RResult.empty())
				{
					//替换￥，不然会识别为有中文而不添加到待选项中
					replace_all(v_num_table_set[m][i].RResult, "￥", "");
					//金额中识别出不是数字不添加
					//WYP 去除中文字符
					extractNumber(v_num_table_set[m][i].RResult, v_num_table_set[m][i].RResult);
					if (IsValidElem(v_num_table_set[m][i].RResult) == 0)
					{
						//把尾部过长的部分去掉
						if (v_num_table_set[m][i].RResult.empty())
						{	//kang 202102 只识别-,坐标清空
							v_num_table_set[m][i].charPos.clear();
							v_num_table_set[m][i].Pos[0] = -1;
							v_num_table_set[m][i].Pos[1] = -1;
							v_num_table_set[m][i].Pos[2] = -1;
							v_num_table_set[m][i].Pos[3] = -1;
						}
						else
						{
							if (v_num_table_set[m][i].RResult.size() > 10)
								v_num_table_set[m][i].RResult = "0";
							if (traitNumber(v_num_table_set[m][i].RResult, 2))
							{
								v_num_table_set[m][i].RResult = v_num_table_set[m][i].RResult;
							}
						}
					}
				}
			}
		}
	}
}

void CExtractInfo::GetNumDj()
{

	for (int m = 0; m < TableSet.size(); m++)
	{
		if (v_price_table_set[m].size() != v_title_table_set[m].size())
		{
			v_title_table_set[m].clear();
			v_price_table_set[m].clear();
			v_num_table_set[m].clear();
			v_dj_table_set[m].clear();

			continue;
		}
		if (v_price_table_set[m].size() == 0 || v_title_table_set[m].size() == 0)
		{
			v_title_table_set[m].clear();
			v_price_table_set[m].clear();
			v_num_table_set[m].clear();
			v_dj_table_set[m].clear();

			continue;
		}


		if (TableSet[m].TitleCol[1] != -1 && TableSet[m].TitleCol[2] != -1)
		{
			//金额、单价数量都在反算
			for (int i = 0; i < v_title_table_set[m].size(); i++)
			{
				if (!v_dj_table_set[m][i].RResult.empty() && v_dj_table_set[m][i].Pos[0] == v_num_table_set[m][i].Pos[0]
					&& v_dj_table_set[m][i].Pos[1] == v_num_table_set[m][i].Pos[1])
				{//单价、数量粘连
					v_num_table_set[m][i].RResult = "0.00";
					v_num_table_set[m][i].Pos[0] = 0;
					v_num_table_set[m][i].Pos[1] = 0;
					v_num_table_set[m][i].Pos[2] = 0;
					v_num_table_set[m][i].Pos[3] = 0;
				}
				if (!v_dj_table_set[m][i].RResult.empty() && v_price_table_set[m][i].Pos[0] == v_dj_table_set[m][i].Pos[0]
					&& v_price_table_set[m][i].Pos[1] == v_dj_table_set[m][i].Pos[1])
				{//单价、金额粘连
					v_dj_table_set[m][i].RResult = "0.000";
					v_dj_table_set[m][i].Pos[0] = 0;
					v_dj_table_set[m][i].Pos[1] = 0;
					v_dj_table_set[m][i].Pos[2] = 0;
					v_dj_table_set[m][i].Pos[3] = 0;
				}//金额、数量粘连
				if (!v_num_table_set[m][i].RResult.empty() && v_price_table_set[m][i].Pos[0] == v_num_table_set[m][i].Pos[0]
					&& v_price_table_set[m][i].Pos[1] == v_num_table_set[m][i].Pos[1])
				{
					v_num_table_set[m][i].RResult = "0.00";
					v_num_table_set[m][i].Pos[0] = 0;
					v_num_table_set[m][i].Pos[1] = 0;
					v_num_table_set[m][i].Pos[2] = 0;
					v_num_table_set[m][i].Pos[3] = 0;
				}

				if (!v_dj_table_set[m][i].RResult.empty())
				{
					if (!v_num_table_set[m][i].RResult.empty())
					{
						if (!v_price_table_set[m][i].RResult.empty())
						{
							double dj = atof(v_dj_table_set[m][i].RResult.c_str());
							double num = atof(v_num_table_set[m][i].RResult.c_str());
							double price = atof(v_price_table_set[m][i].RResult.c_str());

							char djStr[20];
							sprintf(djStr, "%.4f", dj);

							char numStr[20];
							sprintf(numStr, "%.2f", num);

							char priceStr[20];
							sprintf(priceStr, "%.2f", price);

							v_dj_table_set[m][i].RResult = djStr;
							v_num_table_set[m][i].RResult = numStr;
							v_price_table_set[m][i].RResult = priceStr;
							if (dj * num == price)
							{
								continue;
							}

						}
						else
						{
							//只有金额空
							double price = atof(v_dj_table_set[m][i].RResult.c_str()) * atof(v_num_table_set[m][i].RResult.c_str());
							char buf[20];
							sprintf(buf, "%.2f", price);
							v_price_table_set[m][i].RResult = buf;
						}
					}
					else
					{
						//数量为空,金额不为空
						if (!v_price_table_set[m][i].RResult.empty() && atoi(v_price_table_set[m][i].RResult.c_str()) != 0)
						{
							double num = atof(v_price_table_set[m][i].RResult.c_str()) / atof(v_dj_table_set[m][i].RResult.c_str());
							char buf[20];
							sprintf(buf, "%.2f", num);
							v_num_table_set[m][i].RResult = buf;
						}
						else
						{
							//数量为空,金额为空，默认数量为1
							double price = atof(v_price_table_set[m][i].RResult.c_str());
							char buf[20];
							sprintf(buf, "%.2f", price);
							v_num_table_set[m][i].RResult = "1.00";
							v_price_table_set[m][i].RResult = buf;
						}
					}
				}
				else
				{
					//单价空
					//,数量不为空
					if (!v_num_table_set[m][i].RResult.empty())
					{
						//金额不为空
						if (!v_price_table_set[m][i].RResult.empty() && atoi(v_price_table_set[m][i].RResult.c_str()) != 0)
						{
							double dj = atof(v_price_table_set[m][i].RResult.c_str()) / atof(v_num_table_set[m][i].RResult.c_str());
							char buf[20];
							sprintf(buf, "%.4f", dj);
							v_dj_table_set[m][i].RResult = buf;
						}
						else
						{
							//金额为空，单价和金额 = 数量
							double dj = atof(v_num_table_set[m][i].RResult.c_str());
							v_dj_table_set[m][i].RResult = to_string(dj);
							v_price_table_set[m][i].RResult = to_string(dj);
						}
					}
					else
					{
						//单价空
						//数量为空,默认数量为1
						//金额不为空
						if (!v_price_table_set[m][i].RResult.empty() && atoi(v_price_table_set[m][i].RResult.c_str()) != 0)
						{
							v_num_table_set[m][i].RResult = "1.00";
							double price = atof(v_price_table_set[m][i].RResult.c_str());
							char buf[20];
							sprintf(buf, "%.4f", price);
							v_dj_table_set[m][i].RResult = buf;
						}
						else
						{
							//金额为空
							v_dj_table_set[m][i].RResult = "1.000";
							v_num_table_set[m][i].RResult = "1.00";
							v_price_table_set[m][i].RResult = "1.00";
						}
					}
				}
			}
		}

		if (TableSet[m].TitleCol[1] == -1 && TableSet[m].TitleCol[2] != -1)
		{
			//缺少单价dj
			for (int j = 0; j < v_price_table_set[m].size(); j++)
			{
				//金额、数量粘连
				if (!v_num_table_set[m][j].RResult.empty() && v_price_table_set[m][j].Pos[0] == v_num_table_set[m][j].Pos[0]
					&& v_price_table_set[m][j].Pos[1] == v_num_table_set[m][j].Pos[1])
				{
					v_num_table_set[m][j].RResult = "0.00";
					v_num_table_set[m][j].Pos[0] = 0;
					v_num_table_set[m][j].Pos[1] = 0;
					v_num_table_set[m][j].Pos[2] = 0;
					v_num_table_set[m][j].Pos[3] = 0;
				}

				if (!v_num_table_set[m][j].RResult.empty() && atoi(v_num_table_set[m][j].RResult.c_str()) != 0)
				{

					if (v_price_table_set[m][j].RResult.empty())
						v_price_table_set[m][j].RResult = "0.00";
					double dj = atof(v_price_table_set[m][j].RResult.c_str()) / atof(v_num_table_set[m][j].RResult.c_str());

					char buf[20];
					sprintf(buf, "%.4f", dj);
					RecogResult tempDj;

					tempDj.RResult = buf;
					tempDj.Pos[0] = 0;
					tempDj.Pos[1] = 0;
					tempDj.Pos[2] = 0;
					tempDj.Pos[3] = 0;
					tempDj.Flag = v_price_table_set[m][j].Flag;

					v_dj_table_set[m].emplace_back(tempDj);

				}
				else
				{
					v_num_table_set[m][j].RResult = "1.00";
					if (v_price_table_set[m][j].RResult.empty())
						v_price_table_set[m][j].RResult = "0.00";
					double dj = atof(v_price_table_set[m][j].RResult.c_str());

					char buf[20];
					sprintf(buf, "%.4f", dj);

					RecogResult tempDj;
					tempDj.RResult = v_price_table_set[m][j].RResult;
					tempDj.Flag = v_price_table_set[m][j].Flag;
					tempDj.Pos[0] = 0;
					tempDj.Pos[1] = 0;
					tempDj.Pos[2] = 0;
					tempDj.Pos[3] = 0;

					v_dj_table_set[m].emplace_back(tempDj);

				}
			}
		}
		if (TableSet[m].TitleCol[2] == -1 && TableSet[m].TitleCol[1] != -1)
		{
			//缺少数量num
			for (int j = 0; j < v_price_table_set[m].size(); j++)
			{
				if (!v_dj_table_set[m][j].RResult.empty() && v_price_table_set[m][j].Pos[0] == v_dj_table_set[m][j].Pos[0]
					&& v_price_table_set[m][j].Pos[1] == v_dj_table_set[m][j].Pos[1])
				{//单价、金额粘连
					v_dj_table_set[m][j].RResult = "0.0000";
					v_dj_table_set[m][j].Pos[0] = 0;
					v_dj_table_set[m][j].Pos[1] = 0;
					v_dj_table_set[m][j].Pos[2] = 0;
					v_dj_table_set[m][j].Pos[3] = 0;
				}
				if (!v_dj_table_set[m][j].RResult.empty() && atoi(v_dj_table_set[m][j].RResult.c_str()) != 0)
				{
					if (v_price_table_set[m][j].RResult.empty())
						v_price_table_set[m][j].RResult = "0.00";
					double num = atof(v_price_table_set[m][j].RResult.c_str()) / atof(v_dj_table_set[m][j].RResult.c_str());

					char buf[20];
					sprintf(buf, "%.2f", num);

					RecogResult tempNum;

					tempNum.RResult = buf;
					tempNum.Pos[0] = 0;
					tempNum.Pos[1] = 0;
					tempNum.Pos[2] = 0;
					tempNum.Pos[3] = 0;
					tempNum.Flag = v_price_table_set[m][j].Flag;

					v_num_table_set[m].emplace_back(tempNum);
				}
				else
				{
					if (v_price_table_set[m][j].RResult.empty())
						v_price_table_set[m][j].RResult = "0.00";
					v_dj_table_set[m][j].RResult = v_price_table_set[m][j].RResult;
					RecogResult tempDum;
					tempDum.RResult = "1.00";
					tempDum.Flag = v_price_table_set[m][j].Flag;
					tempDum.Pos[0] = 0;
					tempDum.Pos[1] = 0;
					tempDum.Pos[2] = 0;
					tempDum.Pos[3] = 0;

					v_num_table_set[m].emplace_back(tempDum);
				}
			}
		}
		if (TableSet[m].TitleCol[2] == -1 && TableSet[m].TitleCol[1] == -1)
		{
			//单价数量都缺少
			for (int j = 0; j < v_price_table_set[m].size(); j++)
			{
				if (!v_price_table_set[m][j].RResult.empty() && atoi(v_price_table_set[m][j].RResult.c_str()) != 0)
				{
					RecogResult tempDj;
					tempDj.RResult = v_price_table_set[m][j].RResult;
					tempDj.Pos[0] = 0;
					tempDj.Pos[1] = 0;
					tempDj.Pos[2] = 0;
					tempDj.Pos[3] = 0;
					tempDj.Flag = 0;

					v_dj_table_set[m].emplace_back(tempDj);

					RecogResult tempNum;
					tempNum.RResult = "1.00";
					tempNum.Pos[0] = 0;
					tempNum.Pos[1] = 0;
					tempNum.Pos[2] = 0;
					tempNum.Pos[3] = 0;
					tempNum.Flag = 0;
					v_num_table_set[m].emplace_back(tempNum);
				}
				else
				{
					RecogResult tempDj;
					tempDj.RResult = "0.000";
					tempDj.Pos[0] = 0;
					tempDj.Pos[1] = 0;
					tempDj.Pos[2] = 0;
					tempDj.Pos[3] = 0;
					tempDj.Flag = 0;

					v_dj_table_set[m].emplace_back(tempDj);

					RecogResult tempNum;
					tempNum.RResult = "0.00";
					tempNum.Pos[0] = 0;
					tempNum.Pos[1] = 0;
					tempNum.Pos[2] = 0;
					tempNum.Pos[3] = 0;
					tempNum.Flag = 0;
					v_num_table_set[m].emplace_back(tempNum);
				}
			}
		}
	}
}

void CExtractInfo::GetDetailListTable()
{
	for (int m = 0; m < TableSet.size(); m++)
	{
		for (int i = 0; i < v_title_table_set[m].size(); i++)
		{
			KeyWord keyWord;

			keyWord.Name = v_title_table_set[m][i].RResult;
			memcpy(&keyWord.Pos[0], &v_title_table_set[m][i].Pos[0], sizeof(float)* 4);

			keyWord.TotalPrice = v_price_table_set[m][i].RResult;
			memcpy(&keyWord.Pos[4], &v_price_table_set[m][i].Pos[0], sizeof(float)* 4);


			if (v_dj_table_set.size() > 0 && v_dj_table_set[m].size() > 0)
			{
				keyWord.UnitPrice = v_dj_table_set[m][i].RResult;
				if (v_dj_table_set[m][i].Pos[0] == 0 && v_dj_table_set[m][i].Pos[1] == 0)
				{
					v_dj_table_set[m][i].Pos[0] = 0;
					v_dj_table_set[m][i].Pos[1] = 0;
					v_dj_table_set[m][i].Pos[2] = 1;
					v_dj_table_set[m][i].Pos[3] = 1;

				}
				memcpy(&keyWord.Pos[8], &v_dj_table_set[m][i].Pos[0], sizeof(float)* 4);
			}

			if (v_num_table_set.size() > 0 && v_num_table_set[m].size() > 0)
			{
				if (v_num_table_set[m][i].Pos[0] == 0 && v_num_table_set[m][i].Pos[1] == 0)
				{
					v_num_table_set[m][i].Pos[0] = 0;
					v_num_table_set[m][i].Pos[1] = 0;
					v_num_table_set[m][i].Pos[2] = 1;
					v_num_table_set[m][i].Pos[3] = 1;
				}
				keyWord.Number = v_num_table_set[m][i].RResult;
				memcpy(&keyWord.Pos[12], &v_num_table_set[m][i].Pos[0], sizeof(float)* 4);
			}
			FinalList.emplace_back(keyWord);
		}
	}
}

int CExtractInfo::DetectColFlagOfTable()
{
	for (int i = 0; i < TableSet.size(); i++)
	{
		if (TableSet[i].ColWid.size() < 3)
			TableSet.erase(TableSet.begin() + i);
	}
	//1表示首页传入标题与自动定位没有交叉，按照手动定位识别
	int titleCand = 0;
	if (this->m_titlePos.size() <= 0)
	{
		//自动定位标题
		bool isFlag = false;
		for (int i = 0; i < TableSet.size(); i++)
		{
			if (TableSet[i].TitleCol[0] != -1)  //该表格已经被处理
				continue;

			TableSet[i].eachColumnInfoSet.clear();
			this->CountColInfo(TableSet[i].eachColumnInfoSet, i);

			//找到标题所在行
			for (int j = 0; j < this->TableSet[i].MatrixTable.size(); j++)
			{
				for (int k = 0; k < this->TableSet[i].MatrixTable[j].size(); k++)
				{
					string strText = this->TableSet[i].MatrixTable[j][k].strText;
					//找出项目名称所在行列
					for (int m = 0; m < TitleSet.size(); m++)
					{
						if (TitleSet[m].Flag == 4)
						{
							std::size_t found = strText.find(TitleSet[m].Name);
							if (found != std::string::npos)
							{
								//if (find(TableSet[i].colSetForTitle.begin(), TableSet[i].colSetForTitle.end(), k) == TableSet[i].colSetForTitle.end())
								//{
									TableSet[i].colSetForTitle.emplace_back(k); //把找到的候选项目名称保存起来
									TableSet[i].colSetForRow.emplace_back(j);
									TableSet[i].rowSetForTitle.emplace_back(j);
								//}
							}
						}
						if (TitleSet[m].Flag == 6)
						{
							std::size_t found = strText.find(TitleSet[m].Name);
							if (found != std::string::npos)
							{
								//if (find(TableSet[i].colSetForPrice.begin(), TableSet[i].colSetForPrice.end(), k) == TableSet[i].colSetForPrice.end())
								//{
									TableSet[i].colSetForPrice.emplace_back(k);
									TableSet[i].rowSetForPrice.emplace_back(j);
								//}
							}
						}
						if (TitleSet[m].Flag == 5)
						{
							std::size_t found = strText.find(TitleSet[m].Name);
							if (found != std::string::npos)
							{
								//if (find(TableSet[i].colSetForDj.begin(), TableSet[i].colSetForDj.end(), k) == TableSet[i].colSetForDj.end())
								//{
									TableSet[i].colSetForDj.emplace_back(k);
									TableSet[i].rowSetForDj.emplace_back(j);
								//}
							}
						}
						if (TitleSet[m].Flag == 7)
						{
							std::size_t found = strText.find(TitleSet[m].Name);
							if (found != std::string::npos)
							{
								//if (find(TableSet[i].colSetForNum.begin(), TableSet[i].colSetForNum.end(), k) == TableSet[i].colSetForNum.end())
								//{
									TableSet[i].colSetForNum.emplace_back(k);
									TableSet[i].rowSetForNum.emplace_back(j);
								//}
							}
						}
					}
				}
			}
			//分为有表头和没有表头两种情况处理
			if (TableSet[i].colSetForTitle.size() > 0 && TableSet[i].colSetForPrice.size() > 0 && !isFlag) //如果找到了标题栏，则判断是单列还是双列
			{
				//JudgeTwoColumn(i);
				JudgeTwoColumnByOverlap(i);
				isFlag = true;
				i--;
				continue;
			}
			else if (!isFlag)
			{
				TableSet[i].existTitle = 0;
				JudgeTwoColumnWithoutTitle(i);
				isFlag = true;
				i--;
				continue;
			}

			//没有找到标题列
			if (TableSet[i].colSetForTitle.size() <= 0 && TableSet[i].TitleCol[0] == -1)
			{
				for (int k = 0; k < TableSet[i].ColWid.size(); k++)
				{
					TableSet[i].colSetForTitle.emplace_back(k);
				}

				for (int k = 0; k < TableSet[i].ColWid.size(); k++)
				{
					TableSet[i].colSetForPrice.emplace_back(k);
				}
				for (int k = 0; k < TableSet[i].ColWid.size(); k++)
				{
					TableSet[i].colSetForDj.emplace_back(k);
				}
			}

			FindTitleRowFlag(i);

			//无标题时，根据关键字只定位到标题或金额且定位错，再次定位
			if (TableSet[i].TitleCol[0] == -1 || TableSet[i].TitleCol[3] == -1)
			{
				TableSet[i].TitleCol[0] = -1;
				TableSet[i].TitleCol[3] = -1;
				TableSet[i].colSetForRow.clear();

				TableSet[i].rowSetForPrice.clear();
				TableSet[i].colSetForPrice.clear();

				TableSet[i].rowSetForDj.clear();
				TableSet[i].colSetForDj.clear();

				TableSet[i].rowSetForNum.clear();
				TableSet[i].colSetForNum.clear();

				for (int k = 0; k < TableSet[i].ColWid.size(); k++)
				{
					TableSet[i].colSetForTitle.emplace_back(k);
				}

				for (int k = 0; k < TableSet[i].ColWid.size(); k++)
				{
					TableSet[i].colSetForPrice.emplace_back(k);
				}
				for (int k = 0; k < TableSet[i].ColWid.size(); k++)
				{
					TableSet[i].colSetForDj.emplace_back(k);
				}

				FindTitleRowFlag(i);
			}
			if (TableSet[i].TitleCol[0] != -1 && TableSet[i].TitleCol[3] != -1)
			{
				//标题不准时缺少数量列 进行校验，确定数量列
				VerifyTitleCol();

				SetTitlePos(i);
			}
			else
			{
				//只找到一个
				TableSet[i].TitleCol[0] = -1;
				TableSet[i].TitleCol[3] = -1;
			}

			//排除干扰的信息有表格，明细无表格部分
			if (TableSet[i].TitleCol[1] != -1 && TableSet[i].TitleCol[3] != -1)
			{
				int priceCol = TableSet[i].TitleCol[3];
				int djCol = TableSet[i].TitleCol[1];
				if (TableSet[i].eachColumnInfoSet[djCol].number < 5 && TableSet[i].eachColumnInfoSet[priceCol].number < 5)
				{
					TableSet[i].TitleCol[0] = -1;
					TableSet[i].TitleCol[1] = -1;
					TableSet[i].TitleCol[2] = -1;
					TableSet[i].TitleCol[3] = -1;
					return 0;
				}
			}
			//跨行标题
			SetTitlePosAgain();
			if (m_titlePosCand.size() > 0)
			if (SetTitlePosCand(i))
				titleCand = 1;
		}
	}
	if (((this->m_titlePos.size() == 1 && isManual == 1)))  //外部传入标题（单列）
	{
		for (int i = 0; i < TableSet.size(); i++)
		{
			if (TableSet[i].ColWid.size() < 3)
				TableSet.erase(TableSet.begin() + i);
		}
		for (int i = 0; i < TableSet.size(); i++)
		{
			if (TableSet[i].TitleCol[0] != -1)  //该表格已经被处理
				continue;
			//统计表格的相关信息
			this->CountColInfo(TableSet[i].eachColumnInfoSet, i);

			GetManualTitleInfo(1, i);

			FindTitleRowFlag(i);
		}
	}
	if ((this->m_titlePos.size() > 1 && isManual == 1))  //外部传入标题（双列）
	{
		//把表格拆分，得到每个表格的列标志
		for (int i = 0; i < TableSet.size(); i++)
		{
			if (TableSet[i].ColWid.size() < 6)
				TableSet.erase(TableSet.begin() + i);
		}
		for (int i = 0; i < TableSet.size(); i++)
		{
			if (TableSet[i].TitleCol[0] != -1)  //该表格已经被处理
				continue;
			this->CountColInfo(TableSet[i].eachColumnInfoSet, i);

			GetManualTitleInfo(2, i);

			FindTitleRowFlag(i);
		}
	}

	//202103kang -多表格多标题时ocx异常，只保留两个标题，无表格可以进行解析
	if (this->m_titlePos.size() > 2)
	{
		m_titlePos.assign(m_titlePos.begin(), m_titlePos.begin() + 2);
	}
	return 0;
}
int CExtractInfo::SetTitlePosCand(int tableID)
{
	/***************************************************************************
	使用场景：有表格时，ocx传入首页候选标题
	代码思路：
	1、自动定位出标题时，判断候选标题和自动标题垂直方向是否交叉，不交叉采用候选，交叉采用自动识别标题
	2、无标题时或者标题数量不相等时直接采用候选标题
	***************************************************************************/

	if (m_titlePos.size() > 0)
	{
		if (m_titlePos.size() != m_titlePosCand.size())
		{
			m_titlePos.assign(m_titlePosCand.begin(), m_titlePosCand.end());
			TableSet[tableID].TitleCol[0] = -1;
			TableSet[tableID].TitleCol[1] = -1;
			TableSet[tableID].TitleCol[2] = -1;
			TableSet[tableID].TitleCol[3] = -1;
			isManual = 1;
			return 1;
		}

		for (int k = 0; k < m_titlePosCand.size(); k++)
		{
			if (k == tableID)
			{
				for (int m = 0; m < 3; m++)
				{
					int overlap = 0;
					int left1 = 0, right1 = 0, left2 = 0, right2 = 0;
					if (m == 0)
					{
						left1 = m_titlePosCand[k].NamePos.pos[0];
						right1 = m_titlePosCand[k].NamePos.pos[0] + m_titlePosCand[k].NamePos.pos[2];
						left2 = m_titlePos[k].NamePos.pos[0];
						right2 = m_titlePos[k].NamePos.pos[0] + m_titlePos[k].NamePos.pos[2];
					}
					if (m == 1)
					{
						left1 = m_titlePosCand[k].DjPos.pos[0];
						right1 = m_titlePosCand[k].DjPos.pos[0] + m_titlePosCand[k].DjPos.pos[2];
						left2 = m_titlePos[k].DjPos.pos[0];
						right2 = m_titlePos[k].DjPos.pos[0] + m_titlePos[k].DjPos.pos[2];
					}
					if (m == 2)
					{
						left1 = m_titlePosCand[k].NumPos.pos[0];
						right1 = m_titlePosCand[k].NumPos.pos[0] + m_titlePosCand[k].NumPos.pos[2];
						left2 = m_titlePos[k].NumPos.pos[0];
						right2 = m_titlePos[k].NumPos.pos[0] + m_titlePos[k].NumPos.pos[2];
					}
					if (m == 3)
					{
						left1 = m_titlePosCand[k].PricePos.pos[0];
						right1 = m_titlePosCand[k].PricePos.pos[0] + m_titlePosCand[k].PricePos.pos[2];
						left2 = m_titlePos[k].PricePos.pos[0];
						right2 = m_titlePos[k].PricePos.pos[0] + m_titlePos[k].PricePos.pos[2];
					}
					if (left1 > left2 && left1 > right2)
						overlap = 0;
					else if (right1 < left2 && right1 < right2)
						overlap = 0;
					else
						overlap = 10000;
					if (overlap == 0)
					{
						//交集为0，按照首页手动标记
						m_titlePos.assign(m_titlePosCand.begin(), m_titlePosCand.end());
						TableSet[tableID].TitleCol[0] = -1;
						TableSet[tableID].TitleCol[1] = -1;
						TableSet[tableID].TitleCol[2] = -1;
						TableSet[tableID].TitleCol[3] = -1;
						isManual = 1;
						return 1;
					}
				}
				return 0;
			}
		}
	}
	else
	{
		m_titlePos.assign(m_titlePosCand.begin(), m_titlePosCand.end());
	}
}
int CExtractInfo::GetTableColumn(int tableID)
{
	v_title_table.clear();
	v_price_table.clear();
	v_dj_table.clear();
	v_num_table.clear();
	int mSize = 0;//判断名称、单价、数量、金额在同一个表格里，如果size==2的数量>=3就认为在同一行，此时取出第二个数据
	vector<int> multiRows;//两列数据单独放进去


	for (int j = 0; j < TableSet[tableID].MatrixTable.size(); j++)
	{
		mSize = 0;
		if (TableSet[tableID].TitleCol[0] == -1 || TableSet[tableID].TitleCol[3] == -1)
			continue;

		int startRow = 0;

		if (TableSet[tableID].existTitle == 1)
			startRow = TableSet[tableID].Row;
		else
			startRow = TableSet[tableID].Row - 1;
		if (j > startRow)
		{
			for (int k = 0; k < TableSet[tableID].MatrixTable[j].size(); k++)
			{
				if (k == TableSet[tableID].TitleCol[0] || k == TableSet[tableID].TitleCol[1] || k == TableSet[tableID].TitleCol[2] || k == TableSet[tableID].TitleCol[3])
				{
					if (this->TableSet[tableID].MatrixTable[j][k].allStrText.size() == 2 && mSize >= 2 && mSize <= 4)
					{
						mSize++;
						if (mSize == 3) multiRows.push_back(j);
					}
				}
			}
		}
	}

	for (int j = 0; j < TableSet[tableID].MatrixTable.size(); j++)
	{
		if (TableSet[tableID].TitleCol[0] == -1 || TableSet[tableID].TitleCol[3] == -1)
			continue;

		int startRow = 0;

		if (TableSet[tableID].existTitle == 1)
			startRow = TableSet[tableID].Row;
		else
			startRow = TableSet[tableID].Row - 1;
		if (j > startRow)
		{
			for (int k = 0; k < TableSet[tableID].MatrixTable[j].size(); k++)
			{
				if (k == TableSet[tableID].TitleCol[0] || k == TableSet[tableID].TitleCol[1] || k == TableSet[tableID].TitleCol[2] || k == TableSet[tableID].TitleCol[3]
					|| (TableSet[tableID].MatrixTable[j][k].rowColumn[1] != TableSet[tableID].MatrixTable[j][k].rowColumn[3]
					&& TableSet[tableID].TitleCol[0] >= TableSet[tableID].MatrixTable[j][k].rowColumn[1]
					&& TableSet[tableID].TitleCol[0] <= TableSet[tableID].MatrixTable[j][k].rowColumn[3]))
				{
					RecogResult title;
					title.RResult = this->TableSet[tableID].MatrixTable[j][k].strText;

					for (int tt = 0; tt < multiRows.size(); tt++)
					{
						if (multiRows[tt] == j)
						{
							if (this->TableSet[tableID].MatrixTable[j][k].allStrText.size() >= 1)
								title.RResult = this->TableSet[tableID].MatrixTable[j][k].allStrText[0];
							else
								title.RResult = "";
						}
					}

					if (title.RResult.empty())
					{
						title.Pos[0] = -1; title.Pos[1] = -1; title.Pos[2] = -1; title.Pos[3] = -1;
					}
					else
					{
						//元素不为空存字符串坐标
						vector<PosOfChar> charPos;
						if (TableSet[tableID].MatrixTable[j][k].allCharPos.size() >= 1 || TableSet[tableID].MatrixTable[j][k].charPos.size() >= 1)
						{
							for (int p = 0; p < TableSet[tableID].MatrixTable[j][k].charPos.size(); p++)
							{
								PosOfChar tableCharPos;
								tableCharPos.pos[0] = TableSet[tableID].MatrixTable[j][k].charPos[p].pos[0];
								tableCharPos.pos[1] = TableSet[tableID].MatrixTable[j][k].charPos[p].pos[1];
								tableCharPos.pos[2] = TableSet[tableID].MatrixTable[j][k].charPos[p].pos[2];
								tableCharPos.pos[3] = TableSet[tableID].MatrixTable[j][k].charPos[p].pos[3];
								charPos.emplace_back(tableCharPos);
							}

							//合合返回顺序不对，title.Pos[2]会为负数，这里先排序
							auto cmp = [](PosOfChar s1, PosOfChar s2)
							{
								return s1.pos[0] < s2.pos[0];
							};
							sort(charPos.begin(), charPos.end(), cmp);

							title.charPos.assign(charPos.begin(), charPos.end());

							int top = 1000000, bottom = -1;
							for (int i = 0; i < title.charPos.size(); i++)
							{
								if (top > title.charPos[i].pos[1])
									top = title.charPos[i].pos[1];

								if (bottom < title.charPos[i].pos[3])
									bottom = title.charPos[i].pos[3];
							}
							title.Pos[0] = title.charPos[0].pos[0];
							title.Pos[1] = top;
							title.Pos[2] = title.charPos[title.charPos.size() - 1].pos[0] + title.charPos[title.charPos.size() - 1].pos[2] - title.charPos[0].pos[0];
							title.Pos[3] = bottom;
						}
						else
						{
							title.Pos[0] = -1; title.Pos[1] = -1; title.Pos[2] = -1; title.Pos[3] = -1;
						}

						for (int tt = 0; tt < multiRows.size(); tt++)
						{
							if (multiRows[tt] == j)
							{
								if (TableSet[tableID].MatrixTable[j][k].allCharPos.size() >= 2)
								{
									for (int p = 0; p < TableSet[tableID].MatrixTable[j][k].allCharPos[0].size(); p++)
									{
										PosOfChar tableCharPos;
										tableCharPos.pos[0] = TableSet[tableID].MatrixTable[j][k].allCharPos[0][p].pos[0];
										tableCharPos.pos[1] = TableSet[tableID].MatrixTable[j][k].allCharPos[0][p].pos[1];
										tableCharPos.pos[2] = TableSet[tableID].MatrixTable[j][k].allCharPos[0][p].pos[2];
										tableCharPos.pos[3] = TableSet[tableID].MatrixTable[j][k].allCharPos[0][p].pos[3];
										charPos.emplace_back(tableCharPos);
									}
									//合合返回顺序不对，title.Pos[2]会为负数，这里先排序
									auto cmp = [](PosOfChar s1, PosOfChar s2)
									{
										return s1.pos[0] < s2.pos[0];
									};
									sort(charPos.begin(), charPos.end(), cmp);

									title.charPos.assign(charPos.begin(), charPos.end());

									int top = 1000000, bottom = -1;
									for (int i = 0; i < title.charPos.size(); i++)
									{
										if (top > title.charPos[i].pos[1])
											top = title.charPos[i].pos[1];

										if (bottom < title.charPos[i].pos[3])
											bottom = title.charPos[i].pos[3];
									}

									title.Pos[0] = title.charPos[0].pos[0];
									title.Pos[1] = top;
									title.Pos[2] = title.charPos[title.charPos.size() - 1].pos[0] + title.charPos[title.charPos.size() - 1].pos[2] - title.charPos[0].pos[0];
									title.Pos[3] = bottom;
								}
								else
									title.Pos[0] = -1;title.Pos[1] = -1;title.Pos[2] = -1;title.Pos[3] = -1;
							}
						}
					}
					if (k == TableSet[tableID].TitleCol[0])
					{
						v_title_table.emplace_back(title);

					}
					if (k == TableSet[tableID].TitleCol[1])
					{
						v_dj_table.emplace_back(title);
					}
					if (k == TableSet[tableID].TitleCol[2])
					{
						v_num_table.emplace_back(title);
					}
					if (k == TableSet[tableID].TitleCol[3])
					{
						v_price_table.emplace_back(title);
					}
				}
			}
		}
	}

	//一个表格跨两行数据，取第二个数据
	for (int j = 0; j < multiRows.size(); j++)
	{
		for (int k = 0; k < TableSet[tableID].MatrixTable[multiRows[j]].size(); k++)
		{
			if (k == TableSet[tableID].TitleCol[0] || k == TableSet[tableID].TitleCol[1] || k == TableSet[tableID].TitleCol[2] || k == TableSet[tableID].TitleCol[3])
			{
				RecogResult title;
				if (this->TableSet[tableID].MatrixTable[multiRows[j]][k].allStrText.size() == 2)
					title.RResult = this->TableSet[tableID].MatrixTable[multiRows[j]][k].allStrText.at(1);
				else
					title.RResult = "";

				vector<PosOfChar> charPos;
				if (TableSet[tableID].MatrixTable[multiRows[j]][k].allCharPos.size() >= 2)
				{
					for (int m = 0; m < TableSet[tableID].MatrixTable[multiRows[j]][k].allCharPos[1].size(); m++)
					{
						PosOfChar tableCharPos;
						tableCharPos.pos[0] = TableSet[tableID].MatrixTable[multiRows[j]][k].allCharPos[1][m].pos[0];
						tableCharPos.pos[1] = TableSet[tableID].MatrixTable[multiRows[j]][k].allCharPos[1][m].pos[1];
						tableCharPos.pos[2] = TableSet[tableID].MatrixTable[multiRows[j]][k].allCharPos[1][m].pos[2];
						tableCharPos.pos[3] = TableSet[tableID].MatrixTable[multiRows[j]][k].allCharPos[1][m].pos[3];
						charPos.emplace_back(tableCharPos);
					}

					//合合返回顺序不对，title.Pos[2]会为负数，这里先排序
					auto cmp = [](PosOfChar s1, PosOfChar s2)
					{
						return s1.pos[0] < s2.pos[0];
					};
					sort(charPos.begin(), charPos.end(), cmp);
					title.charPos.assign(charPos.begin(), charPos.end());

					int top = 1000000, bottom = -1;
					for (int i = 0; i < title.charPos.size(); i++)
					{
						if (top > title.charPos[i].pos[1])
							top = title.charPos[i].pos[1];

						if (bottom < title.charPos[i].pos[3])
							bottom = title.charPos[i].pos[3];
					}
					title.Pos[0] = title.charPos[0].pos[0];
					title.Pos[1] = top;
					title.Pos[2] = title.charPos[title.charPos.size() - 1].pos[0] + title.charPos[title.charPos.size() - 1].pos[2] - title.charPos[0].pos[0];
					title.Pos[3] = bottom;
				}
				else
				{
					title.Pos[0] = -1;title.Pos[1] = -1;title.Pos[2] = -1;title.Pos[3] = -1;
				}
				if (k == TableSet[tableID].TitleCol[0])
				{
					v_title_table.emplace_back(title);

				}
				if (k == TableSet[tableID].TitleCol[1])
				{
					v_dj_table.emplace_back(title);
				}
				if (k == TableSet[tableID].TitleCol[2])
				{
					v_num_table.emplace_back(title);
				}
				if (k == TableSet[tableID].TitleCol[3])
				{
					v_price_table.emplace_back(title);
				}
			}

		}
	}
	v_title_table_set.emplace_back(v_title_table);
	v_dj_table_set.emplace_back(v_dj_table);
	v_price_table_set.emplace_back(v_price_table);
	v_num_table_set.emplace_back(v_num_table);

	return 1;
}

int CExtractInfo::IsValidData(string strText)
{
	LeftOutStr(strText, "|");
	int s[3];
	sscanf(strText.c_str(), "%d-%d-%d", &s[0], &s[1], &s[2]);
	if (s[0] > 0 && s[0]<2050 && s[1]>0 && s[1]<13 && s[2]>0 && s[2] < 32)
		return 1;
	else
	{
		sscanf(strText.c_str(), "%d.%d.%d", &s[0], &s[1], &s[2]);
		if (s[0] > 0 && s[0]<2050 && s[1]>0 && s[1]<13 && s[2]>0 && s[2] < 32)
			return 1;
		else
		{
			sscanf(strText.c_str(), "%d/%d/%d", &s[0], &s[1], &s[2]);
			if (s[0] > 0 && s[0]<2050 && s[1]>0 && s[1]<13 && s[2]>0 && s[2] < 32)
				return 1;
		}
	}
	return 0;
}

int CExtractInfo::JudgeTwoColumn(int tableID)
{
	//判断双列以及切分点：前提同一行项目名称距离>1列
	//找到第一个金额所在行为切分点
	int i = tableID;

	int splitcol = -1;
	for (int k = 0; k < this->TableSet[i].colSetForTitle.size() - 1; k++)
	{
		if (this->TableSet[i].colSetForTitle[k + 1] - this->TableSet[i].colSetForTitle[k] > 1 &&
			this->TableSet[i].colSetForRow[k + 1] == this->TableSet[i].colSetForRow[k])
		{
			int bFlag = 0;
			for (int j = this->TableSet[i].colSetForTitle[k] + 1; j < this->TableSet[i].colSetForTitle[k + 1] && bFlag == 0; j++)
			{
				int row = this->TableSet[i].colSetForRow[k + 1];
				string str = this->TableSet[i].MatrixTable[row][j].strText;

				//找出项目名称所在行列
				for (int m = 0; m < TitleSet.size(); m++)
				{
					if (TitleSet[m].Flag == 6 && str.find(TitleSet[m].Name) != std::string::npos)
					{
						bFlag = 1;
						break;
					}
				}
			}
			if (bFlag == 1)
				splitcol = this->TableSet[i].colSetForTitle[k + 1];
		}
	}

	//找到切分点，且拆分前和拆分后列>2，表明是双列数据
	if (splitcol > 2 && TableSet[tableID].ColWid.size() > 2 && TableSet[tableID].ColWid.size() - splitcol > 2 && splitcol < TableSet[tableID].ColWid.size())
	{
		TableInfo tableInfo;
		this->TableSet[tableID].SplitTable(tableInfo, splitcol);
		this->TableSet.emplace_back(tableInfo);
	}
	else
	{
		;
	}
	return 1;
}

int CExtractInfo::JudgeTwoColumnWithoutTitle(int tableID)
{
	//if (this->TableSet[tableID].ColWid.size() < 7)
	//	return 0;
	vector<EachColumnInfo> eachColumnInfoSet;

	CountColInfo(eachColumnInfoSet, tableID);

	for (int i = 0; i < eachColumnInfoSet.size(); i++)
	{
		//数字平均长度>5认为是编码或者日期，
		if (eachColumnInfoSet[i].number / this->TableSet[tableID].MatrixTable.size() >5)
		{
			eachColumnInfoSet[i].num = 0;
		}
		//cout << i << (float)eachColumnInfoSet[i].percentNum / this->TableSet[tableID].MatrixTable.size()<<endl;
		if ((float)eachColumnInfoSet[i].percentNum / this->TableSet[tableID].MatrixTable.size() > 0.3)
		{
			eachColumnInfoSet[i].num = 0;
		}
	}

	//自定义排序对中文字符数量进行排序

	sort(eachColumnInfoSet.begin(), eachColumnInfoSet.end(), [](EachColumnInfo s1, EachColumnInfo s2){return s1.ChineseNumber > s2.ChineseNumber; });
	int MaxColChin = eachColumnInfoSet[0].Column;
	int SecMaxColChin = eachColumnInfoSet[1].Column;

	//自定义排序，num值最大为金额

	sort(eachColumnInfoSet.begin(), eachColumnInfoSet.end(), [](EachColumnInfo s1, EachColumnInfo s2){return s1.num > s2.num; });

	int MaxColPrice = eachColumnInfoSet[0].Column;
	int SecMaxColSecPric = eachColumnInfoSet[1].Column;

	int SplitCol = -1;
	TableInfo tableInfo;
	if (MaxColChin - MaxColPrice == SecMaxColChin - SecMaxColSecPric && (SecMaxColChin > MaxColPrice || MaxColChin > SecMaxColSecPric))
	{
		this->TableSet[tableID].TitleCol[0] = MaxColChin;
		this->TableSet[tableID].TitleCol[3] = MaxColPrice;
		tableInfo.TitleCol[0] = SecMaxColChin - SecMaxColChin;
		tableInfo.TitleCol[3] = SecMaxColSecPric - SecMaxColChin;

		SplitCol = SecMaxColChin;
	}
	else if (SecMaxColChin - MaxColPrice == MaxColChin - SecMaxColSecPric && (MaxColChin > MaxColPrice || SecMaxColChin > SecMaxColSecPric))
	{
		this->TableSet[tableID].TitleCol[0] = SecMaxColChin;
		this->TableSet[tableID].TitleCol[3] = MaxColPrice;

		tableInfo.TitleCol[0] = MaxColChin - MaxColChin;
		tableInfo.TitleCol[3] = SecMaxColSecPric - MaxColChin;

		SplitCol = MaxColChin;
	}
	else
	{
		this->TableSet[tableID].TitleCol[0] = MaxColChin;
		this->TableSet[tableID].TitleCol[3] = MaxColPrice;
	}

	//名称列等于金额列
	if (this->TableSet[tableID].TitleCol[0] == this->TableSet[tableID].TitleCol[3])
	{
		this->TableSet[tableID].TitleCol[0] = -1;
		this->TableSet[tableID].TitleCol[3] = -1;
		return 0;
	}


	if (SplitCol > 2 && (eachColumnInfoSet.size() - SplitCol) > 2 && SplitCol < eachColumnInfoSet.size())
	{
		this->TableSet[tableID].SplitTable(tableInfo, SplitCol);

		//this->TableSet[tableID].TitleCol[0] = SecMaxColChin;
		//this->TableSet[tableID].TitleCol[3] = MaxColPrice;

		this->TableSet.emplace_back(tableInfo);

	}
	else
	{
		this->TableSet[tableID].TitleCol[0] = -1;
		this->TableSet[tableID].TitleCol[3] = -1;
	}

	return 0;
}

void CExtractInfo::CountColInfo(vector<EachColumnInfo>& eachColumnInfoSet, int tableID)
{
	//去掉小计-合计-总计所在行的数据,影响金额列定位
	vector<int> isFlag(this->TableSet[tableID].MatrixTable.size(), 0);	//合计小计不进行统计
	vector<int> timeData(this->TableSet[tableID].MatrixTable[0].size(), 0);//记录编码出现次数,出现次数大于行的1/3,数字为0
	vector<int> remainRows(this->TableSet[tableID].MatrixTable[0].size(), 0); //2020- 干扰项所占比例
	int realRows = 0;
	for (int j = 0; j < this->TableSet[tableID].MatrixTable.size(); j++)
	{
		for (int k = 0; k < this->TableSet[tableID].MatrixTable[j].size(); k++)
		{
			//名称找到合计、小计、总计
			if (TableSet[tableID].MatrixTable[j][k].strText.find("合计") != std::string::npos
				|| TableSet[tableID].MatrixTable[j][k].strText.find("小计") != std::string::npos
				|| TableSet[tableID].MatrixTable[j][k].strText.find("总计") != std::string::npos)
			{
				isFlag[j] = 1;
			}
		}
	}

	//统计实际行数
	for (int j = 0; j < this->TableSet[tableID].MatrixTable.size(); j++)
	{
		if (isFlag[j] == 0)
			realRows++;
	}

	for (int j = 0; j < this->TableSet[tableID].MatrixTable.size(); j++)
	{
		//if (isFlag[j] == 1)  //如果
		//	continue;

		for (int k = 0; k < this->TableSet[tableID].MatrixTable[j].size(); k++)
		{
			string strText = this->TableSet[tableID].MatrixTable[j][k].strText;

			int ChineseNumber = 0; //中文
			int number = 0; //数字个数
			int dotNumber = 0; //小数点
			int dateNumber = 0;
			int percentNum = 0;

			replace_all(strText, "￥", "");
			double num = atof(strText.c_str());

			for (int p = 0; p < strText.size(); p++)
			{
				if (strText.at(p) >= '0' &&strText.at(p) <= '9')
				{
					number++;
				}
				else if (strText.at(p) == '.')
				{
					dotNumber++;
				}
				else if (strText.at(p)<0 || strText.at(p)>126)
				{
					ChineseNumber++;
				}
				if (strText.at(p) == '%')
					percentNum++;
			}

			if (ChineseNumber > 0)
				ChineseNumber /= 2;
			if (IsValidData(strText))
				dateNumber = 1;
			EachColumnInfo eachColumnInfo;

			if (number > 5 && dotNumber < 1 || isFlag[j] == 1)
			{
				number = 0;
				num = 0;
				timeData[k]++;
			}
			if (number>0)
				remainRows[k]++;

			eachColumnInfo.Column = k;
			eachColumnInfo.ChineseNumber = ChineseNumber;
			eachColumnInfo.dotNumber = dotNumber;
			eachColumnInfo.number = number;
			eachColumnInfo.num = num; //数字之和
			eachColumnInfo.dateNum = dateNumber;
			eachColumnInfo.percentNum = percentNum;

			if (j > 0)
			{
				eachColumnInfoSet[k].ChineseNumber += ChineseNumber;
				eachColumnInfoSet[k].dotNumber += dotNumber;
				eachColumnInfoSet[k].number += number;
				eachColumnInfoSet[k].num += num;
				eachColumnInfoSet[k].dateNum += dateNumber;
				eachColumnInfoSet[k].percentNum += percentNum;
			}
			else
			{
				eachColumnInfoSet.emplace_back(eachColumnInfo);
			}
		}
	}

	//如果无效行数超过实际行数的1/3，则重置值
	for (int i = 0; i < timeData.size(); i++)
	{
		if (timeData[i] >(realRows / 3))
		{
			eachColumnInfoSet[i].number = 0;
			eachColumnInfoSet[i].num = 0;
		}
	}

	//去掉头部干扰信息，比如日期 2020-,统计包含数字行（不能是纯数字）占整行的比例
	//整行比例<1/5暂时认为是干扰信息
	for (int i = 0; i < remainRows.size(); i++)
	{
		if (remainRows[i] <(realRows / 5))
		{
			eachColumnInfoSet[i].number = 0;
			eachColumnInfoSet[i].num = 0;
		}
	}
}

void CExtractInfo::FindTitleRowFlag(int tableID)
{
	int i;
	if (this->TableSet[tableID].TitleCol[0] == -1) //项目名称没找到
	{
		int maxChinese = 0;
		//同时出现项目名称-项目类别时，优先级项目名称 > 类别
		bool isFindTitleType = false, isFindTitleName = false;
		int flag = -1;
		for (i = 0; i < this->TableSet[tableID].colSetForTitle.size(); i++)
		{
			int colID = this->TableSet[tableID].colSetForTitle[i];
			int rowID = 0;
			if (this->TableSet[tableID].colSetForRow.size()>0)
				rowID = this->TableSet[tableID].colSetForRow[i];

			std::string text = this->TableSet[tableID].MatrixTable[rowID][colID].strText;
			if (text == "项目类别")
			{
				isFindTitleType = true;
				flag = i;
			}
			if (text == "费用名称")
			{
				isFindTitleName = true;
			}
			if (isFindTitleType && isFindTitleName)
			{
				this->TableSet[tableID].colSetForTitle.erase(TableSet[tableID].colSetForTitle.begin() + flag);
				this->TableSet[tableID].colSetForRow.erase(TableSet[tableID].colSetForRow.begin() + flag);
				break;
			}
		}

		for (i = 0; i < this->TableSet[tableID].colSetForTitle.size(); i++)
		{
			//找到不同列中中文字数最多的列
			int colID = this->TableSet[tableID].colSetForTitle[i];
			int rowID = 0;
			if (this->TableSet[tableID].colSetForRow.size()>0)
				rowID = this->TableSet[tableID].colSetForRow[i];
			int chineseNum = 0;
			for (int j = 0; j < this->TableSet[tableID].eachColumnInfoSet.size(); j++)
			{
				if (colID == this->TableSet[tableID].eachColumnInfoSet[j].Column)
				{
					chineseNum = this->TableSet[tableID].eachColumnInfoSet[j].ChineseNumber;
					break;
				}
			}

			if (chineseNum > maxChinese)
			{
				maxChinese = chineseNum;
				this->TableSet[tableID].TitleCol[0] = colID;
				this->TableSet[tableID].Row = rowID;

			}
		}
	}
	if (this->TableSet[tableID].Row >= 0)
	{
		//确定了标题所在行，排除其他关键字不在此行的数据
		for (int i = 0; i < this->TableSet[tableID].rowSetForPrice.size(); i++)
		{
			if ((this->TableSet[tableID].Row != -1) && (this->TableSet[tableID].Row != this->TableSet[tableID].rowSetForPrice.at(i)))
			{
				this->TableSet[tableID].rowSetForPrice.erase(this->TableSet[tableID].rowSetForPrice.begin() + i);
				this->TableSet[tableID].colSetForPrice.erase(this->TableSet[tableID].colSetForPrice.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < this->TableSet[tableID].rowSetForDj.size(); i++)
		{
			if ((this->TableSet[tableID].Row != -1) && (this->TableSet[tableID].Row != this->TableSet[tableID].rowSetForDj.at(i)))
			{
				this->TableSet[tableID].rowSetForDj.erase(this->TableSet[tableID].rowSetForDj.begin() + i);
				this->TableSet[tableID].colSetForDj.erase(this->TableSet[tableID].colSetForDj.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < this->TableSet[tableID].rowSetForNum.size(); i++)
		{
			if ((this->TableSet[tableID].Row != -1) && (this->TableSet[tableID].Row != this->TableSet[tableID].rowSetForNum.at(i)))
			{
				this->TableSet[tableID].rowSetForNum.erase(this->TableSet[tableID].rowSetForNum.begin() + i);
				this->TableSet[tableID].colSetForNum.erase(this->TableSet[tableID].colSetForNum.begin() + i);
				i--;
			}
		}
	}

	for (i = 0; i < this->TableSet[tableID].colSetForPrice.size(); i++)
	{
		for (int j = 0; j < this->TableSet[tableID].eachColumnInfoSet.size(); j++)
		{
			int col = this->TableSet[tableID].colSetForPrice.at(i);
			if (col == j && this->TableSet[tableID].colSetForPrice.at(i) <= this->TableSet[tableID].TitleCol[0] && (float)this->TableSet[tableID].eachColumnInfoSet[j].dotNumber / this->TableSet[tableID].MatrixTable.size() < 0.3)
			{
				this->TableSet[tableID].colSetForPrice.erase(this->TableSet[tableID].colSetForPrice.begin() + i);
				i--;
				break;
			}
			if (col == j && (float)this->TableSet[tableID].eachColumnInfoSet[j].percentNum / this->TableSet[tableID].MatrixTable.size() > 0.3)
			{
				this->TableSet[tableID].colSetForPrice.erase(this->TableSet[tableID].colSetForPrice.begin() + i);
				i--;
				break;
			}
		}

	}
	for (i = 0; i < this->TableSet[tableID].colSetForDj.size(); i++)
	{
		for (int j = 0; j < this->TableSet[tableID].eachColumnInfoSet.size(); j++)
		{
			int col = this->TableSet[tableID].colSetForDj.at(i);
			if (col == j && this->TableSet[tableID].colSetForDj.at(i) <= this->TableSet[tableID].TitleCol[0] && (float)this->TableSet[tableID].eachColumnInfoSet[j].dotNumber / this->TableSet[tableID].MatrixTable.size() < 0.3)
			{
				this->TableSet[tableID].colSetForDj.erase(this->TableSet[tableID].colSetForDj.begin() + i);
				i--;
				break;
			}
			if (col == j && (float)this->TableSet[tableID].eachColumnInfoSet[j].percentNum / this->TableSet[tableID].MatrixTable.size() > 0.3)
			{
				this->TableSet[tableID].colSetForDj.erase(this->TableSet[tableID].colSetForDj.begin() + i);
				i--;
				break;
			}
		}

	}
	for (i = 0; i < this->TableSet[tableID].colSetForNum.size(); i++)
	{
		for (int j = 0; j < this->TableSet[tableID].eachColumnInfoSet.size(); j++)
		{
			int col = this->TableSet[tableID].colSetForNum.at(i);

			if (col == j && this->TableSet[tableID].colSetForNum.at(i) <= this->TableSet[tableID].TitleCol[0] && (float)this->TableSet[tableID].eachColumnInfoSet[j].dotNumber / this->TableSet[tableID].MatrixTable.size() < 0.3)
			{
				this->TableSet[tableID].colSetForNum.erase(this->TableSet[tableID].colSetForNum.begin() + i);
				i--;
				break;
			}
			if (col == j && (float)this->TableSet[tableID].eachColumnInfoSet[j].percentNum / this->TableSet[tableID].MatrixTable.size() > 0.3)
			{
				this->TableSet[tableID].colSetForNum.erase(this->TableSet[tableID].colSetForNum.begin() + i);
				i--;
				break;
			}
		}
	}

	if (this->TableSet[tableID].TitleCol[3] == -1) //总价没找到
	{
		float maxPrice = -1;
		for (i = 0; i < this->TableSet[tableID].colSetForPrice.size(); i++)
		{
			//找到金额之和最大的列
			int colID = this->TableSet[tableID].colSetForPrice[i];

			float price = 0;
			int dateNum = 0;
			for (int j = 0; j < this->TableSet[tableID].eachColumnInfoSet.size(); j++)
			{
				if (colID == this->TableSet[tableID].eachColumnInfoSet[j].Column)
				{
					price = this->TableSet[tableID].eachColumnInfoSet[j].num;
					break;
				}
			}
			if (price >= maxPrice)
			{
				maxPrice = price;
				this->TableSet[tableID].TitleCol[3] = colID;
			}
		}
	}

	//名称、金额都没找到
	if (this->TableSet[tableID].TitleCol[0] == -1 || this->TableSet[tableID].TitleCol[3] == -1)
		return;

	//找到了总价列，在单价和数量候选列排除总价列
	for (i = 0; i < this->TableSet[tableID].colSetForDj.size(); i++)
	{
		if (this->TableSet[tableID].TitleCol[3] == this->TableSet[tableID].colSetForDj.at(i))
		{
			this->TableSet[tableID].colSetForDj.erase(this->TableSet[tableID].colSetForDj.begin() + i);
		}
	}
	for (i = 0; i < this->TableSet[tableID].colSetForNum.size(); i++)
	{
		if (this->TableSet[tableID].TitleCol[3] == this->TableSet[tableID].colSetForNum.at(i))
		{
			this->TableSet[tableID].colSetForNum.erase(this->TableSet[tableID].colSetForNum.begin() + i);
		}
	}

	if (this->TableSet[tableID].TitleCol[1] == -1) //单价没找到
	{
		//kang2020-11-20 负值因为单价如果被识别成两列，其中一列数据为空会定位不到，其他列同理
		float maxDj = -1;
		for (i = 0; i < this->TableSet[tableID].colSetForDj.size(); i++)
		{
			//找到不同列中中文字数最多的列
			int colID = this->TableSet[tableID].colSetForDj[i];

			float dj = 0;
			for (int j = 0; j < this->TableSet[tableID].eachColumnInfoSet.size(); j++)
			{
				if (colID == this->TableSet[tableID].eachColumnInfoSet[j].Column)
				{
					dj = this->TableSet[tableID].eachColumnInfoSet[j].num;
					break;
				}
			}
			if (dj > maxDj)
			{
				maxDj = dj;
				this->TableSet[tableID].TitleCol[1] = colID;
			}
		}
	}

	//找到了单价列，在数量候选列排除总价列
	for (i = 0; i < this->TableSet[tableID].colSetForNum.size(); i++)
	{
		if (this->TableSet[tableID].TitleCol[1] == this->TableSet[tableID].colSetForNum.at(i))
		{
			this->TableSet[tableID].colSetForNum.erase(this->TableSet[tableID].colSetForNum.begin() + i);
		}
	}

	if (this->TableSet[tableID].TitleCol[2] == -1) //数量没找到
	{
		int maxNum = -1;
		for (i = 0; i < this->TableSet[tableID].colSetForNum.size(); i++)
		{
			//找到不同列中中文字数最多的列
			int colID = this->TableSet[tableID].colSetForNum[i];

			int num = -1;
			for (int j = 0; j < this->TableSet[tableID].eachColumnInfoSet.size(); j++)
			{
				if (colID == this->TableSet[tableID].eachColumnInfoSet[j].Column)
				{
					num = this->TableSet[tableID].eachColumnInfoSet[j].num;
					break;
				}
			}

			if (num > maxNum)
			{
				maxNum = num;
				this->TableSet[tableID].TitleCol[2] = colID;
			}
		}
	}

	//单价都没找到，继续找，优先找单价
	if (!(this->TableSet[tableID].TitleCol[1] == -1 && this->TableSet[tableID].TitleCol[2] == -1))
		return;

	i = tableID;
	if (this->TableSet[tableID].TitleCol[1] == -1) //单价没找到
	{

		vector<EachColumnInfo> eachColumnInfoSet;

		eachColumnInfoSet.assign(this->TableSet[tableID].eachColumnInfoSet.begin(), this->TableSet[tableID].eachColumnInfoSet.end());

		if (eachColumnInfoSet.size() < 4)
			return;

		for (int i = 0; i < eachColumnInfoSet.size(); i++)
		{
			//数字平均长度>5认为是编码或者日期，
			if (eachColumnInfoSet[i].number / this->TableSet[tableID].MatrixTable.size() >5)
			{
				eachColumnInfoSet[i].num = 0;
			}

			if ((float)eachColumnInfoSet[i].percentNum / this->TableSet[tableID].MatrixTable.size() > 0.3)
			{
				eachColumnInfoSet[i].num = 0;
			}
		}
		sort(eachColumnInfoSet.begin(), eachColumnInfoSet.end(), [](EachColumnInfo s1, EachColumnInfo s2){return s1.num > s2.num; });

		//对每行的数字进行比较，找到最大值所在列，然后列序号最多的列就是单价列，否则为数量列
		//num排名二、三列数据与金额比较，统计相等的次数，如果相等次数>列数的1/4且小于等于总数数量列则为单价列
		int numEqual2 = 0, numEqual3 = 0, allNum2, allNum3;
		for (int j = 0; j < this->TableSet[i].MatrixTable.size(); j++)
		{
			allNum2 = this->TableSet[i].MatrixTable.size();
			for (int k = 0; k < this->TableSet[i].MatrixTable[j].size(); k++)
			{
				if (k == eachColumnInfoSet[1].Column)
				{
					string strText = this->TableSet[i].MatrixTable[j][k].strText;

					replace_all(strText, "￥", "");
					string strPrice = this->TableSet[i].MatrixTable[j][TableSet[i].TitleCol[3]].strText;
					replace_all(strPrice, "￥", "");

					if (strText == strPrice)
					{
						numEqual2++;
					}
				}
				if (k == eachColumnInfoSet[2].Column)
				{
					string strText = this->TableSet[i].MatrixTable[j][k].strText;
					replace_all(strText, "￥", "");

					string strPrice = this->TableSet[i].MatrixTable[j][TableSet[i].TitleCol[3]].strText;
					replace_all(strPrice, "￥", "");

					if (strText == strPrice)
					{
						numEqual3++;
					}
				}
			}
		}
		if (numEqual2 > numEqual3)
			this->TableSet[tableID].TitleCol[1] = eachColumnInfoSet[1].Column;
		else
			this->TableSet[tableID].TitleCol[1] = eachColumnInfoSet[2].Column;
	}

	if (this->TableSet[tableID].TitleCol[2] == -1) //数量没找到
	{
		;
	}
}

void CExtractInfo::SetTitlePos(int tableID)
{
	//确定标题坐标，排除标题跨列
	if (this->TableSet[tableID].Row == -1)
		this->TableSet[tableID].Row = 0;
	TitlePos titlePos;

	//for (int j = 0; j < this->TableSet[tableID].MatrixTable.size(); j++)
	//{
	//	bool isFind = false;
	//	//排除标题跨列，标题跨列后面部分有表格、无表格标题错无法取出数据
	//	for (int k = 0; k < this->TableSet[tableID].MatrixTable[j].size(); k++)
	//	{
	//		if (k == TableSet[tableID].TitleCol[0])
	//		{
	//			if (this->TableSet[tableID].MatrixTable[j][k].rowColumn[1] == this->TableSet[tableID].MatrixTable[j][k].rowColumn[3])
	//			{
	//				this->TableSet[tableID].Row = j;
	//				isFind = true;
	//				break;
	//			}
	//		}
	//	}
	//	if (isFind)
	//		break;
	//}
	for (int j = 0; j < this->TableSet[tableID].MatrixTable.size(); j++)
	{
		for (int k = 0; k < this->TableSet[tableID].MatrixTable[j].size(); k++)
		{
			PosOfChar namePos(-1, -1, -1, -1), djPos(-1, -1, -1, -1), pricePos(-1, -1, -1, -1), numPos(-1, -1, -1, -1);
			if (j == this->TableSet[tableID].Row)
			{
				if (k == TableSet[tableID].TitleCol[0])
				{
					namePos.pos[0] = TableSet[tableID].MatrixTable[j][k].position[0];
					namePos.pos[1] = TableSet[tableID].MatrixTable[j][k].position[1];
					namePos.pos[2] = TableSet[tableID].MatrixTable[j][k].position[2] - TableSet[tableID].MatrixTable[j][k].position[0];
					namePos.pos[3] = TableSet[tableID].MatrixTable[j][k].position[5] - TableSet[tableID].MatrixTable[j][k].position[3];
					//倒立图片，坐标为负值
					if (namePos.pos[0] >= 0 && namePos.pos[1] >= 0 && namePos.pos[2] >= 0 && namePos.pos[3] >= 0)
						titlePos.NamePos = namePos;
					else
					{
						TableSet[tableID].TitleCol[0] = -1;
						return;
					}
				}
				if (k == TableSet[tableID].TitleCol[1])
				{
					djPos.pos[0] = TableSet[tableID].MatrixTable[j][k].position[0];
					djPos.pos[1] = TableSet[tableID].MatrixTable[j][k].position[1];
					djPos.pos[2] = TableSet[tableID].MatrixTable[j][k].position[2] - TableSet[tableID].MatrixTable[j][k].position[0];
					djPos.pos[3] = TableSet[tableID].MatrixTable[j][k].position[5] - TableSet[tableID].MatrixTable[j][k].position[3];
					if (djPos.pos[0] >= 0 && djPos.pos[1] >= 0 && djPos.pos[2] >= 0 && djPos.pos[3] >= 0)
						titlePos.DjPos = djPos;
					else
					{
						TableSet[tableID].TitleCol[1] = -1;
						return;
					}
				}
				if (k == TableSet[tableID].TitleCol[2])
				{
					numPos.pos[0] = TableSet[tableID].MatrixTable[j][k].position[0];
					numPos.pos[1] = TableSet[tableID].MatrixTable[j][k].position[1];
					numPos.pos[2] = TableSet[tableID].MatrixTable[j][k].position[2] - TableSet[tableID].MatrixTable[j][k].position[0];
					numPos.pos[3] = TableSet[tableID].MatrixTable[j][k].position[5] - TableSet[tableID].MatrixTable[j][k].position[3];
					if (numPos.pos[0] >= 0 && numPos.pos[1] >= 0 && numPos.pos[2] >= 0 && numPos.pos[3] >= 0)
						titlePos.NumPos = numPos;
					else
					{
						TableSet[tableID].TitleCol[2] = -1;
						return;
					}
				}
				if (k == TableSet[tableID].TitleCol[3])
				{
					pricePos.pos[0] = TableSet[tableID].MatrixTable[j][k].position[0];
					pricePos.pos[1] = TableSet[tableID].MatrixTable[j][k].position[1];
					pricePos.pos[2] = TableSet[tableID].MatrixTable[j][k].position[2] - TableSet[tableID].MatrixTable[j][k].position[0];
					pricePos.pos[3] = TableSet[tableID].MatrixTable[j][k].position[5] - TableSet[tableID].MatrixTable[j][k].position[3];
					if (pricePos.pos[0] >= 0 && pricePos.pos[1] >= 0 && pricePos.pos[2] >= 0 && pricePos.pos[3] >= 0)
						titlePos.PricePos = pricePos;
					else
					{
						TableSet[tableID].TitleCol[3] = -1;
						return;
					}
				}
			}
		}
	}
	if (TableSet[tableID].TitleCol[1] == -1)
	{
		PosOfChar djPos(-1, -1, -1, -1);
		titlePos.DjPos = djPos;
	}
	if (TableSet[tableID].TitleCol[2] == -1)
	{
		PosOfChar numPos(-1, -1, -1, -1);
		titlePos.NumPos = numPos;
	}
	m_titlePos.emplace_back(titlePos);
}

int CExtractInfo::GetManualTitleInfo(int flag, int tableID)
{
	if (flag == 1)
	{
		//如果传入标题位置在表格下面，跳过,出现情况，1有表格，2无表格，传入标题位置为无表格位置
		int row = TableSet[tableID].RowHei.size();
		if (this->m_titlePos[0].NamePos.pos[1] > TableSet[tableID].MatrixTable[row - 1][0].position[1])
			return 1;

		this->TableSet[tableID].TitleCol[0] = FindBestColByTitle(this->m_titlePos[0].NamePos, tableID);
		this->TableSet[tableID].TitleCol[3] = FindBestColByTitle(this->m_titlePos[0].PricePos, tableID);

		if (this->m_titlePos[0].DjPos.pos[0] > 0)
			this->TableSet[tableID].TitleCol[1] = FindBestColByTitle(this->m_titlePos[0].DjPos, tableID);

		if (this->m_titlePos[0].NumPos.pos[0] > 0)
			this->TableSet[tableID].TitleCol[2] = FindBestColByTitle(this->m_titlePos[0].NumPos, tableID);
		return 1;
	}
	else
	{
		this->TableSet[tableID].TitleCol[0] = FindBestColByTitle(this->m_titlePos[0].NamePos, tableID);
		this->TableSet[tableID].TitleCol[3] = FindBestColByTitle(this->m_titlePos[0].PricePos, tableID);

		if (this->m_titlePos[0].DjPos.pos[0] > 0)
			this->TableSet[tableID].TitleCol[1] = FindBestColByTitle(this->m_titlePos[0].DjPos, tableID);

		if (this->m_titlePos[0].NumPos.pos[0] > 0)
			this->TableSet[tableID].TitleCol[2] = FindBestColByTitle(this->m_titlePos[0].NumPos, tableID);

		int maxJ = 0;
		for (int i = 0; i < 4; i++)
		{
			if (this->TableSet[tableID].TitleCol[i] > maxJ)
				maxJ = this->TableSet[tableID].TitleCol[i];
		}
		TableInfo tableInfo;
		this->TableSet[tableID].SplitTable(tableInfo, maxJ + 1);
		tableInfo.titleID = 1;
		this->TableSet.emplace_back(tableInfo);

		this->TableSet[this->TableSet.size() - 1].TitleCol[0] = FindBestColByTitle(this->m_titlePos[1].NamePos, this->TableSet.size() - 1);
		this->TableSet[this->TableSet.size() - 1].TitleCol[3] = FindBestColByTitle(this->m_titlePos[1].PricePos, this->TableSet.size() - 1);

		if (this->m_titlePos[0].DjPos.pos[0] > 0)
			this->TableSet[this->TableSet.size() - 1].TitleCol[1] = FindBestColByTitle(this->m_titlePos[1].DjPos, this->TableSet.size() - 1);

		if (this->m_titlePos[0].NumPos.pos[0] > 0)
			this->TableSet[this->TableSet.size() - 1].TitleCol[2] = FindBestColByTitle(this->m_titlePos[1].NumPos, this->TableSet.size() - 1);
	}
}

int CExtractInfo::FindBestColByTitle(PosOfChar& titlepos, int tableID)
{
	int flag = 0;
	int row = 0;
	int pSize = 0;
	for (int m = 0; m < this->TableSet[tableID].RowHei.size(); m++)
	{
		pSize = 0;
		for (int p = 0; p < this->TableSet[tableID].ColWid.size(); p++)
		{
			if (this->TableSet[tableID].MatrixTable[m][p].rowColumn[1] == this->TableSet[tableID].MatrixTable[m][p].rowColumn[3])
			{
				pSize++;
				if (pSize == this->TableSet[tableID].ColWid.size())
				{
					//取不跨列所在的行为起始行
					row = m;
					flag = 1;
					break;
				}
			}
		}
		if (flag == 1)
			break;
	}
	if (!flag)
	{
		map<int, int> map;
		//所有数据跨行,用map存储所在列以及对应出现次数,取次数最多的列
		for (int m = 0; m < this->TableSet[tableID].RowHei.size(); m++)
		{
			map.insert(pair<int, int>(m, 0));
			for (int p = 0; p < this->TableSet[tableID].ColWid.size(); p++)
			{
				int count = 0;
				if (this->TableSet[tableID].MatrixTable[m][p].rowColumn[1] == this->TableSet[tableID].MatrixTable[m][p].rowColumn[3])
				{
					map[m] = ++count;
				}
			}
		}

		int max = 0;
		for (auto it = map.begin(); it != map.end(); it++)
		{
			if (max <= it->second)
			{
				max = it->second;
				row = it->first;
			}
		}
	}

	vector<int> PosXY(this->TableSet[tableID].MatrixTable[row].size() * 2);
	for (int j = 0; j < this->TableSet[tableID].MatrixTable[row].size(); j++)
	{
		PosXY[j * 2 + 0] = 100000;
		PosXY[j * 2 + 1] = 0;
	}
	for (int j = 0; j < this->TableSet[tableID].MatrixTable[row].size(); j++)
	{
		if (this->TableSet[tableID].MatrixTable[row][j].position[0] < PosXY[j * 2 + 0])
			PosXY[j * 2 + 0] = this->TableSet[tableID].MatrixTable[row][j].position[0];

		if (this->TableSet[tableID].MatrixTable[row][j].position[2] > PosXY[j * 2 + 1])
			PosXY[j * 2 + 1] = this->TableSet[tableID].MatrixTable[row][j].position[2];
	}


	int left1, left2, right2, right1;
	left1 = titlepos.pos[0];
	right1 = titlepos.pos[0] + titlepos.pos[2];
	int maxlap = 0, overlap = 0;

	int matchJ = 0;
	for (int j = 0; j < this->TableSet[tableID].MatrixTable[row].size(); j++)
	{
		left2 = PosXY[j * 2 + 0];
		right2 = PosXY[j * 2 + 1];

		if (right2 >= left1 && right2 <= right1 && left2 <= left1)
		{
			overlap = right2 - left1;
		}
		else if (right1 >= left2 && right1 <= right2 && right2 >= right1)
		{
			overlap = right1 - left2;
		}
		else if (left2 >= left1 && right1 >= right2)
		{
			overlap = right2 - left2;
		}
		else
		{
			overlap = 0;
		}

		if (maxlap < overlap)
		{
			maxlap = overlap;
			matchJ = j;
		}
	}
	return matchJ;
}
void CExtractInfo::SplitTableForWholeCol(int tableID)
{
	v_title_table.clear();
	v_dj_table.clear();
	v_num_table.clear();
	v_price_table.clear();
	//拆分跨整列，添加相关列数据
	for (int j = 0; j < TableSet[tableID].MatrixTable.size(); j++)//行
	{
		int startRow = 0;
		if (TableSet[tableID].existTitle == 1)
			startRow = TableSet[tableID].Row;
		else
			startRow = TableSet[tableID].Row - 1;
		if (j > startRow)
		{
			for (int k = 0; k < TableSet[tableID].MatrixTable[j].size(); k++)//列
			{
				if (j >= TableSet[tableID].MatrixTable[j][k].rowColumn[0] && j <= TableSet[tableID].MatrixTable[j][k].rowColumn[2])
				{
					//跨列根据标题坐标添加	
					int nameFlag = 0, priceFlag = 0, djFlag = 0, numFlag = 0;
					if (this->TableSet[tableID].MatrixTable[j][k].rowColumn[1] != this->TableSet[tableID].MatrixTable[j][k].rowColumn[3])
					{
						for (int m = 0; m < this->TableSet[tableID].MatrixTable[j][k].allStrText.size(); m++)
						{
							RecogResult title;
							title.RResult = this->TableSet[tableID].MatrixTable[j][k].allStrText.at(m);
							vector<PosOfChar> charPosTable;
							for (int p = 0; p < TableSet[tableID].MatrixTable[j][k].allCharPos[m].size(); p++)
							{
								PosOfChar tableCharPos;
								tableCharPos.pos[0] = TableSet[tableID].MatrixTable[j][k].allCharPos[m][p].pos[0];
								tableCharPos.pos[1] = TableSet[tableID].MatrixTable[j][k].allCharPos[m][p].pos[1];
								tableCharPos.pos[2] = TableSet[tableID].MatrixTable[j][k].allCharPos[m][p].pos[2];
								tableCharPos.pos[3] = TableSet[tableID].MatrixTable[j][k].allCharPos[m][p].pos[3];
								charPosTable.emplace_back(tableCharPos);
							}

							title.charPos.assign(charPosTable.begin(), charPosTable.end());
							int top = 1000000, bottom = -1;
							for (int i = 0; i < title.charPos.size(); i++)
							{
								if (top > title.charPos[i].pos[1])
									top = title.charPos[i].pos[1];

								if (bottom < title.charPos[i].pos[3])
									bottom = title.charPos[i].pos[3];
							}
							title.Pos[0] = title.charPos[0].pos[0];
							title.Pos[1] = top;
							title.Pos[2] = title.charPos[title.charPos.size() - 1].pos[0] + title.charPos[title.charPos.size() - 1].pos[2] - title.charPos[0].pos[0];
							title.Pos[3] = bottom;

							if (title.Pos[0] > m_titlePos[tableID].NamePos.pos[0] && title.Pos[0] + title.Pos[2] < m_titlePos[tableID].NamePos.pos[0] + m_titlePos[tableID].NamePos.pos[2] + 20)
								v_title_table.emplace_back(title);
							if (title.Pos[0] > m_titlePos[tableID].PricePos.pos[0] && title.Pos[0] + title.Pos[2] < m_titlePos[tableID].PricePos.pos[0] + m_titlePos[tableID].PricePos.pos[2] + 20)
								v_price_table.emplace_back(title);
							if (title.Pos[0] > m_titlePos[tableID].DjPos.pos[0] && title.Pos[0] + title.Pos[2] < m_titlePos[tableID].DjPos.pos[0] + m_titlePos[tableID].DjPos.pos[2] + 20)
							{
								if (IsValidElem(title.RResult) != -1)
									v_dj_table.emplace_back(title);
							}
							if (title.Pos[0] > m_titlePos[tableID].NumPos.pos[0] && title.Pos[0] + title.Pos[2] < m_titlePos[tableID].NumPos.pos[0] + m_titlePos[tableID].NumPos.pos[2] + 20)
							{
								if (IsValidElem(title.RResult) != -1)
									v_num_table.emplace_back(title);
							}
						}
					}


					if (k == TableSet[tableID].TitleCol[0] || k == TableSet[tableID].TitleCol[1] || k == TableSet[tableID].TitleCol[2] || k == TableSet[tableID].TitleCol[3])
					{
						for (int m = 0; m < this->TableSet[tableID].MatrixTable[j][k].allStrText.size(); m++)
						{
							RecogResult title;
							title.RResult = this->TableSet[tableID].MatrixTable[j][k].allStrText.at(m);

							if (!title.RResult.empty())
							{
								vector<PosOfChar> charPos;
								charPos.resize(1);
								charPos = TableSet[tableID].MatrixTable[j][k].allCharPos.at(m);

								vector<PosOfChar> charPosTable;
								for (int p = 0; p < charPos.size(); p++)
								{
									PosOfChar tableCharPos;
									tableCharPos.pos[0] = charPos[p].pos[0];
									tableCharPos.pos[1] = charPos[p].pos[1];
									tableCharPos.pos[2] = charPos[p].pos[2];
									tableCharPos.pos[3] = charPos[p].pos[3];
									charPosTable.emplace_back(tableCharPos);
								}

								title.charPos.assign(charPosTable.begin(), charPosTable.end());
								int top = 1000000, bottom = -1;
								for (int i = 0; i < title.charPos.size(); i++)
								{
									if (top > title.charPos[i].pos[1])
										top = title.charPos[i].pos[1];

									if (bottom < title.charPos[i].pos[3])
										bottom = title.charPos[i].pos[3];
								}
								title.Pos[0] = title.charPos[0].pos[0];
								title.Pos[1] = top;
								title.Pos[2] = title.charPos[title.charPos.size() - 1].pos[0] + title.charPos[title.charPos.size() - 1].pos[2] - title.charPos[0].pos[0];
								title.Pos[3] = bottom;

								if (k == TableSet[tableID].TitleCol[0])
								{
									if (m_titlePos[tableID].NamePos.pos[0] >= -1 && !(m_titlePos[tableID].NamePos.pos[0] >= title.Pos[0] + title.Pos[2] || m_titlePos[tableID].NamePos.pos[0] + m_titlePos[tableID].NamePos.pos[2] <= title.Pos[0]))
										v_title_table.emplace_back(title);
								}
								if (k == TableSet[tableID].TitleCol[1])
								{
									if (m_titlePos[tableID].DjPos.pos[0] >= -1 && !(m_titlePos[tableID].DjPos.pos[0] >= title.Pos[0] + title.Pos[2] || m_titlePos[tableID].DjPos.pos[0] + m_titlePos[tableID].DjPos.pos[2] <= title.Pos[0]))
										v_dj_table.emplace_back(title);
								}
								if (k == TableSet[tableID].TitleCol[2])
								{
									if (m_titlePos[tableID].NumPos.pos[0] >= -1 && !(m_titlePos[tableID].NumPos.pos[0] >= title.Pos[0] + title.Pos[2] || m_titlePos[tableID].NumPos.pos[0] + m_titlePos[tableID].NumPos.pos[2] <= title.Pos[0]))
										v_num_table.emplace_back(title);
								}
								if (k == TableSet[tableID].TitleCol[3])
								{
									if (m_titlePos[tableID].PricePos.pos[0] >= -1 && !(m_titlePos[tableID].PricePos.pos[0] >= title.Pos[0] + title.Pos[2] || m_titlePos[tableID].PricePos.pos[0] + m_titlePos[tableID].PricePos.pos[2] <= title.Pos[0]))
										v_price_table.emplace_back(title);
								}
							}
						}
					}
				}
			}
		}
	}
	//个数为0时，重置标志位
	if (v_title_table.size() == 0)
		TableSet[tableID].TitleCol[0] = -1;
	if (v_dj_table.size() == 0)
		TableSet[tableID].TitleCol[1] = -1;
	if (v_num_table.size() == 0)
		TableSet[tableID].TitleCol[2] = -1;
	if (v_price_table.size() == 0)
		TableSet[tableID].TitleCol[3] = -1;
	SortColumn(tableID, v_title_table, v_price_table, v_dj_table, v_num_table);
}

void CExtractInfo::SplitTableByWholeRowCol(int tableID, int flag)
{
	//拆分跨行数据，列不变
	for (int i = 0; i < TableSet[tableID].MatrixTable.size(); i++)//行
	{
		for (int j = 0; j < TableSet[tableID].MatrixTable[i].size(); j++)//列
		{
			for (int m = 0; m < this->TableSet[tableID].MatrixTable[i][j].allStrText.size(); m++)
			{
				if (this->TableSet[tableID].MatrixTable[i][j].allStrText.size() >1)
				{
					string strText = this->TableSet[tableID].MatrixTable[i][j].allStrText.at(m);

					vector<PosOfChar> charPos(TableSet[tableID].MatrixTable[i][j].allCharPos.at(m));

					int position[4];
					int top = 1000000, bottom = -1;
					for (int i = 0; i < charPos.size(); i++)
					{
						if (top > charPos[i].pos[1])
							top = charPos[i].pos[1];

						if (bottom < charPos[i].pos[3])
							bottom = charPos[i].pos[3];
					}
					position[0] = charPos[0].pos[0];
					position[1] = top;
					position[2] = charPos[charPos.size() - 1].pos[0] + charPos[charPos.size() - 1].pos[2] - charPos[0].pos[0];
					position[3] = bottom;

					char strPos[20];
					sprintf(strPos, "{%d,%d,%d,%d}", position[0], position[1], position[2], position[3]);

					char buf[20];
					sprintf(buf, "{%d,%d,%d,%d}", TableSet[tableID].MatrixTable[i][j].rowColumn[0], TableSet[tableID].MatrixTable[i][j].rowColumn[1],
						TableSet[tableID].MatrixTable[i][j].rowColumn[2], TableSet[tableID].MatrixTable[i][j].rowColumn[3]);
					if (flag == 1)
						FindBestRowForTable(tableID, strText, strPos, charPos, buf);
					else if (flag == 2)
						FindBestColForTable(tableID, strText, strPos, charPos, buf);
					else if (flag == 3)
					{
						if (!TableSet[tableID].MatrixTable[i][j].isMatched &&TableSet[tableID].MatrixTable[i][j].allStrText.size() > 2)
							TableSet[tableID].MatrixTable[i][j].strText = "";
					}
				}
			}
		}
	}
}
void CExtractInfo::MergeTableByWholeRowCol(int tableID, int flag)
{
	//合并项目名称,项目名称多列问题
	if (TableSet[tableID].TitleCol[0] != -1)
	{
		int row = 0;
		if (TableSet[tableID].Row < 0)
			row = 0;
		else
			row = TableSet[tableID].Row;
		int col = TableSet[tableID].TitleCol[0];
		int startCol = TableSet[tableID].MatrixTable[row][col].rowColumn[1];
		int endCol = TableSet[tableID].MatrixTable[row][col].rowColumn[3];
		int leftPos = TableSet[tableID].MatrixTable[row][col].position[0];
		int rightPos = TableSet[tableID].MatrixTable[row][col].position[3];

		for (int i = 0; i < TableSet[tableID].MatrixTable.size(); i++)//行
		{
			for (int j = 0; j < TableSet[tableID].MatrixTable[i].size(); j++)//列
			{
				if (TableSet[tableID].MatrixTable[i][j].rowColumn[1] >= startCol && TableSet[tableID].MatrixTable[i][j].rowColumn[1] <= endCol
					&& endCol - startCol < 4)
				{
					if (!this->TableSet[tableID].MatrixTable[i][j].strText.empty() && j != col)
					{
						//当前位置
						string str = this->TableSet[tableID].MatrixTable[i][j].strText;
						vector<PosOfChar> charPos;
						charPos = TableSet[tableID].MatrixTable[i][j].charPos;

						//中心位置
						string str2 = this->TableSet[tableID].MatrixTable[i][col].strText;
						vector<PosOfChar> charPos2;
						charPos2 = TableSet[tableID].MatrixTable[i][col].charPos;

						if (charPos.size() > 0 && charPos2.size() > 0)
						{
							if (charPos[0].pos[0] > charPos2[0].pos[0])
							{
								this->TableSet[tableID].MatrixTable[i][col].strText = str2 + str;
								for (auto temp : charPos)
									TableSet[tableID].MatrixTable[i][col].charPos.push_back(temp);
							}
							else
							{
								this->TableSet[tableID].MatrixTable[i][col].strText = str + str2;
								for (auto temp : charPos)
									TableSet[tableID].MatrixTable[i][col].charPos.push_back(temp);
							}
						}
					}
				}
			}
		}
	}
}
int CExtractInfo::FindBestColForTable(int tableID, string strText, string strPos, vector<PosOfChar>& charPos, string buf)
{
	int s[4], rowCol[4];
	sscanf(strPos.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);
	sscanf(buf.c_str(), "{%d,%d,%d,%d}", &rowCol[0], &rowCol[1], &rowCol[2], &rowCol[3]);

	for (int i = 0; i < TableSet[tableID].MatrixTable.size(); i++)//行
	{
		for (int j = 0; j < TableSet[tableID].MatrixTable[i].size(); j++)//列
		{
			//先确定所在列，排除跨列数据
			if ((s[0] >= (TableSet[tableID].MatrixTable[i][j].position[0] + TableSet[tableID].MatrixTable[i][j].position[6]) / 2 - 10) &&
				(s[0] + s[2] <= (TableSet[tableID].MatrixTable[i][j].position[2] + TableSet[tableID].MatrixTable[i][j].position[4]) / 2 + 10)
				&& TableSet[tableID].MatrixTable[i][j].rowColumn[1] == TableSet[tableID].MatrixTable[i][j].rowColumn[3])
			{
				vector<int> PosXY;
				int matchJ;

				int flag = 0;
				int col = 0;
				for (int m = 0; m < this->TableSet[tableID].RowHei.size(); m++)
				{
					if (m >= rowCol[0] && m <= rowCol[2])
					{
						for (int p = 0; p < this->TableSet[tableID].ColWid.size(); p++)
						{
							if (this->TableSet[tableID].MatrixTable[m][p].rowColumn[0] == this->TableSet[tableID].MatrixTable[m][p].rowColumn[2])
							{
								col = p;
								flag = 1;
								break;
							}
						}
						if (flag == 1)
							break;
					}
				}

				PosXY.resize(this->TableSet[tableID].MatrixTable.size() * 2);
				for (int k = 0; k < this->TableSet[tableID].MatrixTable.size(); k++)
				{
					PosXY[k * 2 + 0] = 100000;
					PosXY[k * 2 + 1] = 0;
				}

				for (int n = 0; n < this->TableSet[tableID].MatrixTable.size(); n++)
				{
					if ((this->TableSet[tableID].MatrixTable[n][col].position[1] + this->TableSet[tableID].MatrixTable[n][col].position[3]) / 2 < PosXY[n * 2 + 0])
						PosXY[n * 2 + 0] = (this->TableSet[tableID].MatrixTable[n][col].position[1] + this->TableSet[tableID].MatrixTable[n][col].position[3]) / 2;

					if ((this->TableSet[tableID].MatrixTable[n][col].position[5] + this->TableSet[tableID].MatrixTable[n][col].position[7]) / 2 > PosXY[n * 2 + 1])
						PosXY[n * 2 + 1] = (this->TableSet[tableID].MatrixTable[n][col].position[5] + this->TableSet[tableID].MatrixTable[n][col].position[7]) / 2;
				}


				int left1, left2, right2, right1;
				left1 = s[1];
				right1 = s[1] + s[3];
				int maxlap = 0, overlap;

				matchJ = 0;
				for (int n = 0; n < this->TableSet[tableID].MatrixTable.size(); n++)
				{
					left2 = PosXY[n * 2 + 0];
					right2 = PosXY[n * 2 + 1];

					if (right2 >= left1 && right2 <= right1)
					{
						overlap = right2 - left1;
					}
					else if (right1 > left2 && right1 < right2)
					{
						overlap = right1 - left2;
					}
					else
					{
						overlap = 0;
					}

					if (maxlap < overlap)
					{
						maxlap = overlap;
						matchJ = n;
					}
				}
				int brst = matchJ;

				if (!TableSet[tableID].MatrixTable[matchJ][j].isMatched)
				{
					TableSet[tableID].MatrixTable[matchJ][j].strText = strText;
					TableSet[tableID].MatrixTable[matchJ][j].charPos = charPos;

					TableSet[tableID].MatrixTable[matchJ][j].isMatched = 1;

					//根据此列不跨行顶点坐标更新表格顶点坐标，
					TableSet[tableID].MatrixTable[matchJ][j].position[1] = this->TableSet[tableID].MatrixTable[matchJ][col].position[1];
					TableSet[tableID].MatrixTable[matchJ][j].position[3] = this->TableSet[tableID].MatrixTable[matchJ][col].position[3];
					TableSet[tableID].MatrixTable[matchJ][j].position[5] = this->TableSet[tableID].MatrixTable[matchJ][col].position[5];
					TableSet[tableID].MatrixTable[matchJ][j].position[7] = this->TableSet[tableID].MatrixTable[matchJ][col].position[7];

				}
				else if (TableSet[tableID].MatrixTable[matchJ][j].isMatched &&TableSet[tableID].MatrixTable[matchJ][j].strText.find(strText) == std::string::npos)
				{
					TableSet[tableID].MatrixTable[matchJ][j].strText += strText;
					TableSet[tableID].MatrixTable[matchJ][j].charPos.insert(TableSet[tableID].MatrixTable[matchJ][j].charPos.end(), charPos.begin(), charPos.end());

				}
				return 0;
			}
		}
	}
}
int CExtractInfo::FindBestRowForTable(int tableID, string strText, string strPos, vector<PosOfChar>& charPos, string buf)
{
	int s[4], rowCol[4];
	sscanf(strPos.c_str(), "{%d,%d,%d,%d}", &s[0], &s[1], &s[2], &s[3]);
	sscanf(buf.c_str(), "{%d,%d,%d,%d}", &rowCol[0], &rowCol[1], &rowCol[2], &rowCol[3]);
	for (int i = 0; i < TableSet[tableID].MatrixTable.size(); i++)//行
	{
		for (int j = 0; j < TableSet[tableID].MatrixTable[i].size(); j++)//列
		{
			//先确定所在行，排除跨行数据
			if ((s[1] >= (TableSet[tableID].MatrixTable[i][j].position[1] + TableSet[tableID].MatrixTable[i][j].position[3]) / 2 - 10) &&
				(s[1] + s[3] <= (TableSet[tableID].MatrixTable[i][j].position[5] + TableSet[tableID].MatrixTable[i][j].position[7]) / 2 + 10)
				&& TableSet[tableID].MatrixTable[i][j].rowColumn[0] == TableSet[tableID].MatrixTable[i][j].rowColumn[2])
			{
				vector<int> PosXY;
				int matchJ;

				int flag = 0;
				int row = 0;
				for (int m = 0; m < this->TableSet[tableID].RowHei.size(); m++)
				{
					for (int p = 0; p < this->TableSet[tableID].ColWid.size(); p++)
					{
						if (p >= rowCol[1] && p <= rowCol[3])
						{
							if (this->TableSet[tableID].MatrixTable[m][p].rowColumn[1] == this->TableSet[tableID].MatrixTable[m][p].rowColumn[3])
							{
								//取不跨列所在的行为起始行
								row = m;
								flag = 1;
								break;
							}
						}
					}
					if (flag == 1)
						break;
				}

				PosXY.resize(this->TableSet[tableID].MatrixTable[row].size() * 2);
				for (int k = 0; k < this->TableSet[tableID].MatrixTable[row].size(); k++)
				{
					PosXY[k * 2 + 0] = 100000;
					PosXY[k * 2 + 1] = 0;
				}

				for (int n = 0; n < this->TableSet[tableID].MatrixTable[row].size(); n++)
				{
					if (this->TableSet[tableID].MatrixTable[row][n].position[0] < PosXY[n * 2 + 0])
						PosXY[n * 2 + 0] = this->TableSet[tableID].MatrixTable[row][n].position[0];

					if (this->TableSet[tableID].MatrixTable[row][n].position[2] > PosXY[n * 2 + 1])
						PosXY[n * 2 + 1] = this->TableSet[tableID].MatrixTable[row][n].position[2];
				}

				int left1, left2, right2, right1;
				left1 = s[0];
				right1 = s[0] + s[2];
				int maxlap = 0, overlap;

				matchJ = 0;
				for (int j = 0; j < this->TableSet[tableID].MatrixTable[row].size(); j++)
				{
					left2 = PosXY[j * 2 + 0];
					right2 = PosXY[j * 2 + 1];

					if (right2 >= left1 && right2 <= right1)
					{
						overlap = right2 - left1;
					}
					else if (right1 > left2 && right1 < right2)
					{
						overlap = right1 - left2;
					}
					else
					{
						overlap = 0;
					}

					if (maxlap < overlap)
					{
						maxlap = overlap;
						matchJ = j;
					}
				}
				int brst = matchJ;

				if (!TableSet[tableID].MatrixTable[i][matchJ].isMatched)
				{
					//TableSet[tableID].MatrixTable[i][matchJ].strText += strText;
					//TableSet[tableID].MatrixTable[i][matchJ].charPos.insert(TableSet[tableID].MatrixTable[i][matchJ].charPos.end(), charPos.begin(), charPos.end());

					TableSet[tableID].MatrixTable[i][matchJ].strText = strText;
					TableSet[tableID].MatrixTable[i][matchJ].charPos = charPos;
					TableSet[tableID].MatrixTable[i][matchJ].isMatched = 1;

					//根据此列不跨行顶点坐标更新表格顶点坐标，
					TableSet[tableID].MatrixTable[i][matchJ].position[0] = this->TableSet[tableID].MatrixTable[row][matchJ].position[0];
					TableSet[tableID].MatrixTable[i][matchJ].position[2] = this->TableSet[tableID].MatrixTable[row][matchJ].position[2];
					TableSet[tableID].MatrixTable[i][matchJ].position[4] = this->TableSet[tableID].MatrixTable[row][matchJ].position[4];
					TableSet[tableID].MatrixTable[i][matchJ].position[6] = this->TableSet[tableID].MatrixTable[row][matchJ].position[6];

				}
				if (TableSet[tableID].MatrixTable[i][matchJ].isMatched &&TableSet[tableID].MatrixTable[i][matchJ].strText.find(strText) == std::string::npos)
				{
					TableSet[tableID].MatrixTable[i][matchJ].strText += strText;
					TableSet[tableID].MatrixTable[i][matchJ].charPos.insert(TableSet[tableID].MatrixTable[i][matchJ].charPos.end(), charPos.begin(), charPos.end());
				}
				return 0;
			}
		}
	}
}
void CExtractInfo::MergeName()
{
	for (int m = 0; m < TableSet.size(); m++)
	{
		//处理换行（考虑未识别 或者被遮挡问题）
		//1、找到项目名称存在、其他项不存在的行
		//2、取距离上下行最近一行进行合并
		//3、换多行情况
		vector<int> isMerge;
		if (v_price_table_set[m].size()>0 && v_title_table_set[m].size() > 0 &&
			v_num_table_set[m].size() > 0 && v_dj_table_set[m].size() > 0)
		{
			//四项都在进行合并
			for (int i = 0; i < v_title_table_set[m].size(); i++)
			if (!v_title_table_set[m][i].RResult.empty())
			if (v_num_table_set[m][i].RResult.empty() && v_dj_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty())
				isMerge.push_back(i);
		}
		else if (v_price_table_set[m].size()>0 && v_title_table_set[m].size() > 0 &&
			v_num_table_set[m].size() > 0)
		{
			//单价不在
			for (int i = 0; i < v_title_table_set[m].size(); i++)
			if (!v_title_table_set[m][i].RResult.empty())
			if (v_num_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty())
				isMerge.push_back(i);
		}
		else if (v_price_table_set[m].size() > 0 && v_title_table_set[m].size() > 0 &&
			v_dj_table_set[m].size() > 0)
		{
			//数量不在
			for (int i = 0; i < v_title_table_set[m].size(); i++)
			if (!v_title_table_set[m][i].RResult.empty())
			if (v_dj_table_set[m][i].RResult.empty() && v_price_table_set[m][i].RResult.empty())
				isMerge.push_back(i);
		}
		if (isMerge.size() > 0)
		{
			for (int i = 0; i < isMerge.size(); i++)
			{
				if (isMerge[i] - 1>-1)
				{
					int heightCenter = v_title_table_set[m][isMerge[i]].Pos[1] + v_title_table_set[m][isMerge[i]].Pos[3] / 2;
					int heightTop;
					if (isMerge[i] - 1 < 0)
						heightTop = 0;
					else
						heightTop = v_price_table_set[m][isMerge[i] - 1].Pos[1] + v_price_table_set[m][isMerge[i] - 1].Pos[3] / 2;
					int heightBottom = v_price_table_set[m][isMerge[i] + 1].Pos[1] + v_price_table_set[m][isMerge[i] + 1].Pos[3] / 2;
					if ((abs(heightCenter - heightTop) <= abs(heightCenter - heightBottom) && isMerge[i] != 0) || isMerge[i] == v_title_table_set[m].size() - 1)
					{
						//和上一行合并
						v_title_table_set[m][isMerge[i]].RResult = v_title_table_set[m][isMerge[i] - 1].RResult + v_title_table_set[m][isMerge[i]].RResult;

						int width, height;
						if (v_title_table_set[m][isMerge[i] - 1].Pos[2] > v_title_table_set[m][isMerge[i]].Pos[2])
							width = v_title_table_set[m][isMerge[i] - 1].Pos[2];
						else
							width = v_title_table_set[m][isMerge[i]].Pos[2];

						height = v_title_table_set[m][isMerge[i]].Pos[1] + v_title_table_set[m][isMerge[i]].Pos[3]
							- v_title_table_set[m][isMerge[i] - 1].Pos[1];

						v_title_table_set[m][isMerge[i] - 1].Pos[0] = v_title_table_set[m][isMerge[i] - 1].Pos[0];
						v_title_table_set[m][isMerge[i] - 1].Pos[1] = v_title_table_set[m][isMerge[i] - 1].Pos[1];
						v_title_table_set[m][isMerge[i] - 1].Pos[2] = width;
						v_title_table_set[m][isMerge[i] - 1].Pos[3] = height;

						v_title_table_set[m].erase(v_title_table_set[m].begin() + isMerge[i]);
						v_price_table_set[m].erase(v_price_table_set[m].begin() + isMerge[i]);
						if (v_num_table_set[m].size() > 0)
							v_num_table_set[m].erase(v_num_table_set[m].begin() + isMerge[i]);
						if (v_dj_table_set[m].size() > 0)
							v_dj_table_set[m].erase(v_dj_table_set[m].begin() + isMerge[i]);
					}
					else
					{
						v_title_table_set[m][isMerge[i] + 1].RResult = v_title_table_set[m][isMerge[i]].RResult + v_title_table_set[m][isMerge[i] + 1].RResult;

						int width, height;
						if (v_title_table_set[m][isMerge[i] + 1].Pos[2] >= v_title_table_set[m][isMerge[i]].Pos[2])
							width = v_title_table_set[m][isMerge[i] + 1].Pos[2];
						else
							width = v_title_table_set[m][isMerge[i]].Pos[2];

						height = v_title_table_set[m][isMerge[i] + 1].Pos[1] + v_title_table_set[m][isMerge[i] + 1].Pos[3]
							- v_title_table_set[m][isMerge[i]].Pos[1];

						v_title_table_set[m][isMerge[i] + 1].Pos[0] = v_title_table_set[m][isMerge[i]].Pos[0];
						v_title_table_set[m][isMerge[i] + 1].Pos[1] = v_title_table_set[m][isMerge[i]].Pos[1];
						v_title_table_set[m][isMerge[i] + 1].Pos[2] = width;
						v_title_table_set[m][isMerge[i] + 1].Pos[3] = height;

						v_title_table_set[m].erase(v_title_table_set[m].begin() + isMerge[i]);
						v_price_table_set[m].erase(v_price_table_set[m].begin() + isMerge[i]);
						if (v_num_table_set[m].size() > 0)
							v_num_table_set[m].erase(v_num_table_set[m].begin() + isMerge[i]);
						if (v_dj_table_set[m].size() > 0)
							v_dj_table_set[m].erase(v_dj_table_set[m].begin() + isMerge[i]);

					}
					//删除一行就更新isMerge的值
					for (int j = i; j < isMerge.size(); j++)
					{
						isMerge[j] = isMerge[j] - 1;
					}
				}
			}
		}
	}

	for (int m = 0; m < TableSet.size(); m++)
	{
		if (v_price_table_set[m].size()>0 && v_title_table_set[m].size() > 0)
		{
			for (int i = 0; i < v_price_table_set[m].size() - 1; i++)
			{
				if (!v_price_table_set[m][i].RResult.empty() && (v_price_table_set[m][i].Pos[1] == v_price_table_set[m][i + 1].Pos[1]) && v_price_table_set[m][i].Pos[0] > 0)
				{
					//项目名称换行
					if (abs(v_title_table_set[m][i].Pos[0] - v_title_table_set[m][i + 1].Pos[0]) < 20)
					{
						v_title_table_set[m][i].RResult = v_title_table_set[m][i].RResult + v_title_table_set[m][i + 1].RResult;
						v_title_table_set[m][i].Pos[0] = v_title_table_set[m][i].Pos[0];
						v_title_table_set[m][i].Pos[1] = v_title_table_set[m][i].Pos[1];

						int width, height;
						if (v_title_table_set[m][i + 1].Pos[2] > v_title_table_set[m][i].Pos[2])
							width = v_title_table_set[m][i + 1].Pos[2];
						else
							width = v_title_table_set[m][i].Pos[2];

						height = v_title_table_set[m][i + 1].Pos[1] + v_title_table_set[m][i + 1].Pos[3] - v_title_table_set[m][i].Pos[1];

						v_title_table_set[m][i].Pos[2] = width;
						v_title_table_set[m][i].Pos[3] = height;

						v_title_table_set[m].erase(v_title_table_set[m].begin() + i + 1);
						v_price_table_set[m].erase(v_price_table_set[m].begin() + i + 1);
						if (v_num_table_set[m].size() > 0)
							v_num_table_set[m].erase(v_num_table_set[m].begin() + i + 1);
						if (v_dj_table_set[m].size() > 0)
							v_dj_table_set[m].erase(v_dj_table_set[m].begin() + i + 1);
						i--;
					}
					else
					{
						//同行误识别,取距离平均距离近的数据，排除长度<=1的数据位置影响
						int sum = 0;
						int num = v_title_table_set[m].size();
						double average = 0.0;
						for (int k = 0; k < v_title_table_set[m].size(); k++)
						{
							if (strlen(v_title_table_set[m][k].RResult.c_str()) >= 2)
							{
								sum += v_title_table_set[m][k].Pos[0];
							}
							else
							{
								num--;
							}
							if (k == v_title_table_set[m].size() - 1 && num > 0)
								average = sum / num;
						}
						if (abs(v_title_table_set[m][i].Pos[0] - average) >= abs(v_title_table_set[m][i + 1].Pos[0] - average))
						{
							v_title_table_set[m].erase(v_title_table_set[m].begin() + i);
							v_price_table_set[m].erase(v_price_table_set[m].begin() + i);
							if (v_num_table_set[m].size() > 0)
								v_num_table_set[m].erase(v_num_table_set[m].begin() + i);
							if (v_dj_table_set[m].size() > 0)
								v_dj_table_set[m].erase(v_dj_table_set[m].begin() + i);
							i--;
						}
						else
						{
							v_title_table_set[m].erase(v_title_table_set[m].begin() + i + 1);
							v_price_table_set[m].erase(v_price_table_set[m].begin() + i + 1);
							if (v_num_table_set[m].size() > 0)
								v_num_table_set[m].erase(v_num_table_set[m].begin() + i + 1);
							if (v_dj_table_set[m].size() > 0)
								v_dj_table_set[m].erase(v_dj_table_set[m].begin() + i + 1);
							i--;
						}
					}
				}
			}
		}
	}
}

void CExtractInfo::GetDetailList()
{
	//反算
	for (int i = 0; i < FinalList.size(); i++)
	{
		if (!FinalList[i].TotalPrice.empty())
		{
			//金额不为空
			if (!FinalList[i].UnitPrice.empty())
			{
				//单价不为空
				if (!FinalList[i].Number.empty())
				{
					double dj = atof(FinalList[i].UnitPrice.c_str());
					double num = atof(FinalList[i].Number.c_str());
					double price = atof(FinalList[i].TotalPrice.c_str());
					char djStr[20];
					sprintf(djStr, "%.4f", dj);

					char numStr[20];
					sprintf(numStr, "%.2f", num);

					char priceStr[20];
					sprintf(priceStr, "%.2f", price);

					FinalList[i].UnitPrice = djStr;
					FinalList[i].Number = numStr;
					FinalList[i].TotalPrice = priceStr;

				}
				else
				{
					//数量为空
					double number = 0.00;
					if (std::atoi(FinalList[i].UnitPrice.c_str()) == 0)
						FinalList[i].UnitPrice = "0.0000";
					else
						number = atof(FinalList[i].TotalPrice.c_str()) / atof(FinalList[i].UnitPrice.c_str());
					char buf[20];
					sprintf(buf, "%.4f", number);
					FinalList[i].Number = buf;
				}
			}
			else
			{
				if (!FinalList[i].Number.empty())
				{
					//单价为空
					double dj = 0.000;
					if (std::atoi(FinalList[i].Number.c_str()) == 0)
						FinalList[i].Number = "0.00";
					else
						dj = atof(FinalList[i].TotalPrice.c_str()) / atof(FinalList[i].Number.c_str());
					char buf[20];
					sprintf(buf, "%.4f", dj);
					FinalList[i].UnitPrice = buf;
				}
				else
				{
					//数量、单价为空	
					double price = atof(FinalList[i].TotalPrice.c_str());
					char priceStr[20];
					sprintf(priceStr, "%.2f", price);
					FinalList[i].TotalPrice = priceStr;

					sprintf(priceStr, "%.4f", price);
					FinalList[i].UnitPrice = priceStr;
					FinalList[i].Number = "1.00";
				}
			}
		}
		else
		{
			if (!FinalList[i].UnitPrice.empty())
			{
				if (!FinalList[i].Number.empty())
				{
					//金额为空
					double price = atof(FinalList[i].UnitPrice.c_str()) * atof(FinalList[i].Number.c_str());
					char buf[20];
					sprintf(buf, "%.4f", price);
					FinalList[i].TotalPrice = buf;
				}
				else
				{
					//金额数量为空
					double dj = atof(FinalList[i].UnitPrice.c_str());
					char djStr[20];
					sprintf(djStr, "%.4f", dj);
					FinalList[i].UnitPrice = djStr;

					sprintf(djStr, "%.2f", dj);
					FinalList[i].TotalPrice = djStr;
					FinalList[i].Number = "1.00";
				}
			}
			else
			{
				if (!FinalList[i].Number.empty())
				{
					//金额单价为空
					FinalList[i].UnitPrice = "0.0000";
					FinalList[i].TotalPrice = "0.00";

					double num = atof(FinalList[i].Number.c_str());
					char numStr[20];
					sprintf(numStr, "%.2f", num);
					FinalList[i].Number = numStr;

				}
				else
				{
					//金额单价数量为空
					FinalList[i].Number = "0.00";
					FinalList[i].UnitPrice = "0.0000";
					FinalList[i].TotalPrice = "0.00";
				}
			}
		}
	}

	for (int i = 0; i < FinalList.size(); i++)
	{
		//名称找到合计、小计、总计、姓名、性别、年龄、Page、病人、住院号、日期 、患者、ID号
		if (FinalList[i].Name.empty() || FinalList[i].Name.find("合计") != std::string::npos || FinalList[i].Name.find("小计") != std::string::npos
			|| FinalList[i].Name.find("总计") != std::string::npos || FinalList[i].Name.find("姓名") != std::string::npos
			|| FinalList[i].Name.find("性别") != std::string::npos || FinalList[i].Name.find("年龄") != std::string::npos
			|| FinalList[i].Name.find("Page") != std::string::npos || FinalList[i].Name.find("住院号") != std::string::npos
			|| FinalList[i].Name.find("日期") != std::string::npos
			|| FinalList[i].Name.find("患者") != std::string::npos || FinalList[i].Name.find("ID号") != std::string::npos
			)
		{
			FinalList.erase(FinalList.begin() + i);
			i--;
			continue;
		}
		if ((FinalList[i].Name.find("第") != std::string::npos && FinalList[i].Name.find("页") != std::string::npos)
			|| (FinalList[i].Name.find("共") != std::string::npos && FinalList[i].Name.find("页") != std::string::npos)
			|| (FinalList[i].Name.find("共") != std::string::npos && FinalList[i].Name.find("条") != std::string::npos))
		{
			FinalList.erase(FinalList.begin() + i);
			i--;
			continue;
		}
	}
}
void CExtractInfo::SetTitlePosAgain()
{
	//标题不存在、标题跨列
	for (int i = 0; i < m_titlePos.size(); i++)
	{
		if (m_titlePos[i].NamePos.getstringcode() == m_titlePos[i].PricePos.getstringcode())
		{
			int row = -1;
			for (int m = 0; m < this->TableSet[i].MatrixTable.size(); m++)
			{
				if (row > -1)
					break;
				for (int p = 0; p < this->TableSet[i].MatrixTable[m].size(); p++)
				{
					if (this->TableSet[i].MatrixTable[m][p].rowColumn[1] == this->TableSet[i].MatrixTable[m][p].rowColumn[3])
					{
						row = m;
						if (m == row && p == TableSet[i].TitleCol[0])
						{
							//取不跨列所在的行为起始行
							m_titlePos[i].NamePos.pos[0] = TableSet[i].MatrixTable[m][p].position[0];
							m_titlePos[i].NamePos.pos[2] = TableSet[i].MatrixTable[m][p].position[2] - TableSet[i].MatrixTable[m][p].position[0];
						}
						if (m == row && p == TableSet[i].TitleCol[3])
						{
							m_titlePos[i].PricePos.pos[0] = TableSet[i].MatrixTable[m][p].position[0];
							m_titlePos[i].PricePos.pos[2] = TableSet[i].MatrixTable[m][p].position[2] - TableSet[i].MatrixTable[m][p].position[0];
						}
						if (m == row && p == TableSet[i].TitleCol[1])
						{
							m_titlePos[i].DjPos.pos[0] = TableSet[i].MatrixTable[m][p].position[0];
							m_titlePos[i].DjPos.pos[2] = TableSet[i].MatrixTable[m][p].position[2] - TableSet[i].MatrixTable[m][p].position[0];
						}
						if (m == row && p == TableSet[i].TitleCol[2])
						{
							m_titlePos[i].NumPos.pos[0] = TableSet[i].MatrixTable[m][p].position[0];
							m_titlePos[i].NumPos.pos[2] = TableSet[i].MatrixTable[m][p].position[2] - TableSet[i].MatrixTable[m][p].position[0];
						}
					}
				}
			}
		}
	}
	//标题跨多行，
	for (int i = 0; i < m_titlePos.size(); i++)
	{
		map<int, int> titleID;
		titleID.insert(pair<int, int>(m_titlePos[i].NamePos.pos[3], 1));
		titleID.insert(pair<int, int>(m_titlePos[i].PricePos.pos[3], 2));
		titleID.insert(pair<int, int>(m_titlePos[i].DjPos.pos[3], 3));
		titleID.insert(pair<int, int>(m_titlePos[i].NumPos.pos[3], 4));

		int minHeight, minNum;
		int maxHeight, maxNum;
		map<int, int>::iterator it;
		for (it = titleID.begin(); it != titleID.end(); it++)
		{
			if (it->first != -1)
			{
				minHeight = it->first;
				minNum = it->second;
				break;
			}
		}

		for (it = titleID.begin(); it != titleID.end(); it++)
		{
			if (it->first != -1 && it->first != minHeight && minHeight != 0)
			{
				maxHeight = it->first;
				maxNum = it->second;
				if (maxHeight / minHeight > 2)
				{
					if (maxNum == 1)
					{
						if (minNum == 2)
						{
							m_titlePos[i].NamePos.pos[1] = m_titlePos[i].PricePos.pos[1];
							m_titlePos[i].NamePos.pos[3] = m_titlePos[i].PricePos.pos[3];
						}
						if (minNum == 3)
						{
							m_titlePos[i].NamePos.pos[1] = m_titlePos[i].DjPos.pos[1];
							m_titlePos[i].NamePos.pos[3] = m_titlePos[i].DjPos.pos[3];
						}
						if (minNum == 4)
						{
							m_titlePos[i].NamePos.pos[1] = m_titlePos[i].NumPos.pos[1];
							m_titlePos[i].NamePos.pos[3] = m_titlePos[i].NumPos.pos[3];
						}
					}
					if (maxNum == 2)
					{
						if (minNum == 1)
						{
							m_titlePos[i].PricePos.pos[1] = m_titlePos[i].NamePos.pos[1];
							m_titlePos[i].PricePos.pos[3] = m_titlePos[i].NamePos.pos[3];
						}
						if (minNum == 3)
						{
							m_titlePos[i].PricePos.pos[1] = m_titlePos[i].DjPos.pos[1];
							m_titlePos[i].PricePos.pos[3] = m_titlePos[i].DjPos.pos[3];
						}
						if (minNum == 4)
						{
							m_titlePos[i].PricePos.pos[1] = m_titlePos[i].NumPos.pos[1];
							m_titlePos[i].PricePos.pos[3] = m_titlePos[i].NumPos.pos[3];
						}
					}
					if (maxNum == 3)
					{
						if (minNum == 1)
						{
							m_titlePos[i].DjPos.pos[1] = m_titlePos[i].NamePos.pos[1];
							m_titlePos[i].DjPos.pos[3] = m_titlePos[i].NamePos.pos[3];
						}
						if (minNum == 2)
						{
							m_titlePos[i].DjPos.pos[1] = m_titlePos[i].PricePos.pos[1];
							m_titlePos[i].DjPos.pos[3] = m_titlePos[i].PricePos.pos[3];
						}
						if (minNum == 4)
						{
							m_titlePos[i].DjPos.pos[1] = m_titlePos[i].NumPos.pos[1];
							m_titlePos[i].DjPos.pos[3] = m_titlePos[i].NumPos.pos[3];
						}
					}
					if (maxNum == 4)
					{
						if (minNum == 1)
						{
							m_titlePos[i].NumPos.pos[1] = m_titlePos[i].NamePos.pos[1];
							m_titlePos[i].NumPos.pos[3] = m_titlePos[i].NamePos.pos[3];
						}
						if (minNum == 3)
						{
							m_titlePos[i].NumPos.pos[1] = m_titlePos[i].DjPos.pos[1];
							m_titlePos[i].NumPos.pos[3] = m_titlePos[i].DjPos.pos[3];
						}
						if (minNum == 2)
						{
							m_titlePos[i].NumPos.pos[1] = m_titlePos[i].PricePos.pos[1];
							m_titlePos[i].NumPos.pos[3] = m_titlePos[i].PricePos.pos[3];
						}
					}
				}
			}
		}
	}
}

void CExtractInfo::SortColumn(int tableID, vector<RecogResult>& v_title_table, vector<RecogResult>& v_price_table, vector<RecogResult>& v_dj_table, vector<RecogResult> & v_num_table)
{
	vector<RecogResult> v_title_table2;//保留待匹配的标题结果
	vector<RecogResult> v_price_table2;//保留待匹配的金额结果
	vector<RecogResult> v_dj_table2;//保留待匹配的单价结果
	vector<RecogResult> v_num_table2;//保留待匹配的数量结果

	//排序去重
	auto cmp = [](RecogResult s1, RecogResult s2)
	{
		return s1.Pos[1] < s2.Pos[1];
	};
	sort(v_title_table.begin(), v_title_table.end(), cmp);
	sort(v_price_table.begin(), v_price_table.end(), cmp);
	sort(v_dj_table.begin(), v_dj_table.end(), cmp);
	sort(v_num_table.begin(), v_num_table.end(), cmp);
	if (v_title_table.size()>0)
	{
		for (int i = 0; i < v_title_table.size() - 1; i++)
		{
			if (v_title_table[i].Pos[1] == v_title_table[i + 1].Pos[1] && v_title_table[i].Pos[0] == v_title_table[i + 1].Pos[0])
			{
				v_title_table.erase(v_title_table.begin() + i);
				i--;
			}
		}
	}
	if (v_price_table.size()>0)
	{
		for (int i = 0; i < v_price_table.size() - 1; i++)
		{
			if (v_price_table[i].Pos[1] == v_price_table[i + 1].Pos[1])
			{
				v_price_table.erase(v_price_table.begin() + i);
				i--;
			}
		}
	}
	if (v_dj_table.size()>0)
	{
		for (int i = 0; i < v_dj_table.size() - 1; i++)
		{
			if (v_dj_table[i].Pos[1] == v_dj_table[i + 1].Pos[1])
			{
				v_dj_table.erase(v_dj_table.begin() + i);
				i--;
			}
		}
	}
	if (v_num_table.size()>0)
	{
		for (int i = 0; i < v_num_table.size() - 1; i++)
		{
			if (v_num_table[i].Pos[1] == v_num_table[i + 1].Pos[1])
			{
				v_num_table.erase(v_num_table.begin() + i);
				i--;
			}
		}
	}

	//根据名称金额确定
	vector<int> isMatchedTitle;
	for (int i = 0; i < v_title_table.size(); i++)
	{
		isMatchedTitle.emplace_back(0);
		for (int j = 0; j < v_price_table.size(); j++)
		{
			if (IsSameLine2(v_title_table.at(i), v_price_table.at(j), 0.5))
			{
				v_title_table2.emplace_back(v_title_table.at(i));
				v_price_table2.emplace_back(v_price_table.at(j));
				isMatchedTitle[i] = 1;
			}
			//if (v_title_table.at(i).Pos[1] +50 > v_price_table.at(j).Pos[1] + 50)
			//	break;
		}
		if (isMatchedTitle[i] == 0)
		{
			RecogResult title;
			v_title_table2.emplace_back(v_title_table.at(i));
			v_price_table2.emplace_back(title);
		}
	}

	//添加单价
	vector<int> isMatchedDj;
	for (int i = 0; i < v_title_table2.size(); i++)
	{
		if (v_dj_table.size() == 0) break;
		isMatchedDj.emplace_back(0);
		for (int j = 0; j < v_dj_table.size(); j++)
		{
			if (IsSameLine(v_title_table2.at(i), v_dj_table.at(j)) && isMatchedDj[i] == 0)
			{
				//同一行
				v_dj_table2.emplace_back(v_dj_table.at(j));
				isMatchedDj[i] = 1;
			}
			else if (IsSameLine(v_title_table2.at(i), v_dj_table.at(j)) && isMatchedDj[i] == 1)
			{
				//同行多个单价
				int length1 = v_dj_table.at(j).Pos[0] + v_dj_table.at(j).Pos[2] / 2;
				int length2 = v_dj_table2.at(i).Pos[0] + v_dj_table2.at(i).Pos[2] / 2;

				int length = m_titlePos[tableID].DjPos.pos[0] + m_titlePos[tableID].DjPos.pos[2] / 2;

				if (fabs((float)(length - length1)) >= fabs((float)(length - length2)))
				{
					//距离标题中心点坐标最近 
					;
				}
				else
				{
					v_dj_table2[i] = v_dj_table.at(j);
					isMatchedDj[i] = 1;
				}
			}
		}
		if (isMatchedDj[i] == 0)
		{
			RecogResult title;
			v_dj_table2.emplace_back(title);
		}
	}

	vector<int> isMatchedNum;
	for (int i = 0; i < v_title_table2.size(); i++)
	{
		if (v_num_table.size() == 0) break;
		isMatchedNum.emplace_back(0);
		for (int j = 0; j < v_num_table.size(); j++)
		{
			if (IsSameLine(v_title_table2.at(i), v_num_table.at(j)))
			{
				v_num_table2.emplace_back(v_num_table.at(j));
				isMatchedNum[i] = 1;
				j++;
			}
			else if (IsSameLine(v_title_table2.at(i), v_num_table.at(j)) && isMatchedNum[i] == 1)
			{
				//同行多个单价
				int length1 = v_num_table.at(j).Pos[0] + v_num_table.at(j).Pos[2] / 2;
				int length2 = v_num_table2.at(i).Pos[0] + v_num_table2.at(i).Pos[2] / 2;

				int length = m_titlePos[tableID].NumPos.pos[0] + m_titlePos[tableID].NumPos.pos[2] / 2;

				if (fabs((float)(length - length1)) >= fabs((float)(length - length2)))
				{
					//距离标题中心点坐标最近 
					;
				}
				else
				{
					v_num_table2[i] = v_dj_table.at(j);
					isMatchedDj[i] = 1;
				}
			}
		}
		if (isMatchedNum[i] == 0)
		{
			RecogResult title;
			v_num_table2.emplace_back(title);
		}
	}

	if (v_title_table2.size() > 0)
	{
		for (int i = 0; i < v_title_table2.size() - 1; i++)
		{
			if (v_title_table2[i].Pos[1] == v_title_table2[i + 1].Pos[1] && v_title_table2[i].Pos[0] == v_title_table2[i + 1].Pos[0])
			{
				v_title_table2.erase(v_title_table2.begin() + i);
				v_price_table2.erase(v_price_table2.begin() + i);
				if (v_dj_table.size() > 0)
					v_dj_table2.erase(v_dj_table2.begin() + i);
				if (v_num_table.size() > 0)
					v_num_table2.erase(v_num_table2.begin() + i);
				i--;
			}
		}
	}
	v_title_table_set.emplace_back(v_title_table2);
	v_price_table_set.emplace_back(v_price_table2);
	v_dj_table_set.emplace_back(v_dj_table2);
	v_num_table_set.emplace_back(v_num_table2);

}
void CExtractInfo::DrawVLineOnImage(PosOfChar& posChar, int type)
{
	//type 0-左侧，1-右侧，2-两侧
	if (posChar.pos[0] == -1)
		return;

	cv::Point pnt1, pnt2;
	pnt1.x = posChar.pos[0] + posChar.pos[2];
	pnt1.y = posChar.pos[1];
	pnt2.x = posChar.pos[0] + posChar.pos[2];
	pnt2.y = this->InputImage.rows - 1;
	if (type == 1 || type == 2)
		line(this->InputImage, pnt1, pnt2, CV_RGB(0, 0, 0), 2);

	pnt1.x = posChar.pos[0];
	pnt1.y = posChar.pos[1];
	pnt2.x = posChar.pos[0];
	pnt2.y = this->InputImage.rows - 1;
	if (type == 0 || type == 2)
		line(this->InputImage, pnt1, pnt2, CV_RGB(0, 0, 0), 2);

}
void CExtractInfo::DrawGridOnImage(int type)
{
	//type-1画两侧 type-0画全部，两个线靠太近只画一条，画右边的
	if (this->m_titlePos.size() <= 0)
		return;

	cv::Point pnt1, pnt2;
	int leftTop[2], rightBot[2];
	leftTop[0] = leftTop[1] = 100000000;
	rightBot[0] = 0;
	for (int i = 0; i < this->m_titlePos.size(); i++)
	{
		vector<PosOfChar> allPos;
		if (this->m_titlePos[i].NamePos.pos[0] != -1)
			allPos.emplace_back(this->m_titlePos[i].NamePos);
		if (this->m_titlePos[i].PricePos.pos[0] != -1)
			allPos.emplace_back(this->m_titlePos[i].PricePos);
		if (this->m_titlePos[i].DjPos.pos[0] != -1)
			allPos.emplace_back(this->m_titlePos[i].DjPos);
		if (this->m_titlePos[i].NumPos.pos[0] != -1)
			allPos.emplace_back(this->m_titlePos[i].NumPos);

		sort(allPos.begin(), allPos.end(), [](const PosOfChar& pt1, const PosOfChar& pt2){return pt1.pos[0] < pt2.pos[0];});
		if (type == 0)
		{
			for (int j = 1; j <= allPos.size(); j++)
			{
				if (j < allPos.size())
				{
					if ((allPos[j].pos[0] - allPos[j - 1].pos[0] - allPos[j - 1].pos[2]) >= 30)
						DrawVLineOnImage(allPos[j - 1], 2);
					else
						DrawVLineOnImage(allPos[j - 1], 0);
				}
				else
				{
					int k = allPos[j - 1].pos[0] - allPos[j - 2].pos[0] - allPos[j - 2].pos[2];
					if ((allPos[j - 1].pos[0] - allPos[j - 2].pos[0] - allPos[j - 2].pos[2]) >= 30)
						DrawVLineOnImage(allPos[j - 1], 2);
					else
						DrawVLineOnImage(allPos[j - 1], 0);
				}
			}
		}
		else
		{
			DrawVLineOnImage(allPos[0], 0);
			DrawVLineOnImage(allPos[allPos.size() - 1], 1);
		}
		leftTop[0] = allPos[0].pos[0];
		leftTop[1] = allPos[0].pos[1];

		rightBot[0] = allPos[allPos.size() - 1].pos[0] + allPos[allPos.size() - 1].pos[2];

	}
	rightBot[1] = this->InputImage.rows - 1;

	////顶部水平线
	//pnt1.x = leftTop[0];
	//pnt1.y = leftTop[1];
	//pnt2.x = rightBot[0];
	//pnt2.y = leftTop[1];
	//line(this->InputImage, pnt1, pnt2, CV_RGB(0, 0, 0), 2);

	//左侧垂直线
	pnt1.x = leftTop[0];
	pnt1.y = leftTop[1];
	pnt2.x = leftTop[0];
	pnt2.y = rightBot[1];
	line(this->InputImage, pnt1, pnt2, CV_RGB(0, 0, 0), 2);

	////右侧垂直线
	pnt1.x = rightBot[0];
	pnt1.y = leftTop[1];
	pnt2.x = rightBot[0];
	pnt2.y = rightBot[1];
	line(this->InputImage, pnt1, pnt2, CV_RGB(0, 0, 0), 2);

	////底部水平线
	//pnt1.x = leftTop[0];
	//pnt1.y = rightBot[1];
	//pnt2.x = rightBot[0];
	//pnt2.y = rightBot[1];
	//line(this->InputImage, pnt1, pnt2, CV_RGB(0, 0, 0), 2);

	imwrite("c:/245.jpg", InputImage);

}

void CExtractInfo::SetTitlePosCand()
{
	if (m_titlePos.size() > 0)
	{
		for (int k = 0; k < m_titlePosCand.size(); k++)
		{
			for (int m = 0; m < 3; m++)
			{
				int overlap = 0;
				int left1 = 0, right1 = 0, left2 = 0, right2 = 0;
				if (m == 0)
				{
					left1 = m_titlePosCand[k].NamePos.pos[0];
					right1 = m_titlePosCand[k].NamePos.pos[0] + m_titlePosCand[k].NamePos.pos[2];
					left2 = m_titlePos[k].NamePos.pos[0];
					right2 = m_titlePos[k].NamePos.pos[0] + m_titlePos[k].NamePos.pos[2];
				}
				if (m == 1)
				{
					left1 = m_titlePosCand[k].DjPos.pos[0];
					right1 = m_titlePosCand[k].DjPos.pos[0] + m_titlePosCand[k].DjPos.pos[2];
					left2 = m_titlePos[k].DjPos.pos[0];
					right2 = m_titlePos[k].DjPos.pos[0] + m_titlePos[k].DjPos.pos[2];
				}
				if (m == 2)
				{
					left1 = m_titlePosCand[k].NumPos.pos[0];
					right1 = m_titlePosCand[k].NumPos.pos[0] + m_titlePosCand[k].NumPos.pos[2];
					left2 = m_titlePos[k].NumPos.pos[0];
					right2 = m_titlePos[k].NumPos.pos[0] + m_titlePos[k].NumPos.pos[2];
				}
				if (m == 3)
				{
					left1 = m_titlePosCand[k].PricePos.pos[0];
					right1 = m_titlePosCand[k].PricePos.pos[0] + m_titlePosCand[k].PricePos.pos[2];
					left2 = m_titlePos[k].PricePos.pos[0];
					right2 = m_titlePos[k].PricePos.pos[0] + m_titlePos[k].PricePos.pos[2];
				}
				if (left1 > left2 && left1 > right2)
					overlap = 0;
				else if (right1 < left2 && right1 < right2)
					overlap = 0;
				else
					overlap = 10000;
				if (overlap == 0)
				{
					//交集为0，按照首页手动标记
					m_titlePos.assign(m_titlePosCand.begin(), m_titlePosCand.end());
					isManual = 1;
				}
			}
		}
	}
	else
	{
		m_titlePos.assign(m_titlePosCand.begin(), m_titlePosCand.end());
	}
}
void CExtractInfo::RecognizeRegion(vector<KeyWord> OutRecogResultList, vector<TitlePos> inTitlePos, int Pos[4])
{
	/***************************************************************************
	2020/12/1	kang-修改
	使用场景：部分有表格\部分无表格、有表格解析数据为空、漏项、替换原来解析方式。

	代码思路：
	1、备份原始m_titlePos
	2、如果RecoglList存在，遍历的第二次，不需要PushRecogResult
	3、传入m_titlePos存在，不需要定位标题
	4、根据m_titlePos找项目名称-金额，然后添加单价数量
	5、反算，和传入识别结果合并排序
	6、标题复位，以便下次遍历
	***************************************************************************/
	vector<TitlePos> orgTitlePos;
	orgTitlePos = inTitlePos;

	if (inTitlePos.size() > 0)
	{
		//inTitlePos = m_titlePos;
		inTitlePos[0].NamePos.pos[1] = 0;
		inTitlePos[0].PricePos.pos[1] = 0;
		inTitlePos[0].NumPos.pos[1] = 0;
		inTitlePos[0].DjPos.pos[1] = 0;

		m_titlePos = inTitlePos;
	}

	//假设原始数据都已经存放在变量RecoglList中
	vector<RecogResult> OldOrgRecoglList;

	//如果历史数据不存在，则调用DecodeRecogedTable得到所有的字符串数据
	if (RecoglList.size() <= 0)
		DecodeRecogedTable(1);

	//保存老的数据
	OldOrgRecoglList.assign(this->RecoglList.begin(), this->RecoglList.end());


	//在原始数据中得到符合要求的数据集合
	v_title.clear();
	v_price.clear();
	v_dj.clear();
	v_num.clear();

	//如果没有标题信息，则自动寻找标题
	if (inTitlePos.size() <= 0)
	{
		MergeForTitle();  //标题进行合并处理

		OrgRecoglList.reserve(OldOrgRecoglList.size());
		OrgRecoglList.assign(OldOrgRecoglList.begin(), OldOrgRecoglList.end());

		GetMatchedNameAndTotal();//获取标题保存到mappedSet中

		if (mappedSet.size() > 0)
			AutoGetNamePricePos(); //根据标题确定左右边界位置
		else
			SortByKMeans(10);
	}

	for (int i = 0; i < OldOrgRecoglList.size(); i++)
	{
		//在识别结果中找出符合位置信息的字符串，并进行标题等标记
		if (OldOrgRecoglList[i].Pos[0] >= Pos[0] && OldOrgRecoglList[i].Pos[1] >= Pos[1] &&
			OldOrgRecoglList[i].Pos[0] + OldOrgRecoglList[i].Pos[2] <= Pos[0] + Pos[2] &&
			OldOrgRecoglList[i].Pos[1] + OldOrgRecoglList[i].Pos[3] <= Pos[1] + Pos[3])
		{
			string strPos = "0,0,0,0";
			if (OldOrgRecoglList[i].charPos.size()>0)
				PushRecogResult2(OldOrgRecoglList[i].RResult, strPos, OldOrgRecoglList[i].charPos);
		}
	}

	//备份原始数据m_titlePos，FinalList
	auto p = remove_if(v_title.begin(), v_title.end(), [](RecogResult r){
		if (r.RResult.length() <= 2)
			return true;
		else
			return false;
	});
	v_title.erase(p, v_title.end());

	sort(v_title.begin(), v_title.end());
	sort(v_price.begin(), v_price.end());

	//得到项目名称和单价的匹配结果
	MatchResult();

	//根据映射关系加入单价和数量
	AddDjAndNum();

	//进行数据反算等后续处理	
	GetDetailList();

	//恢复原始数据（注意FinalList需要更新）
	for (auto temp : OutRecogResultList)
	{
		//删除重复添加数据
		for (int i = 0; i < FinalList.size(); i++)
		{
			if (temp.Name == FinalList[i].Name && temp.Pos[0] == FinalList[i].Pos[0] && abs(temp.Pos[1] - FinalList[i].Pos[1]) < 5)
			{
				FinalList.erase(FinalList.begin() + i);
				i--;
			}
		}
	}
	OutRecogResultList.insert(OutRecogResultList.end(), FinalList.begin(), FinalList.end());
	FinalList.clear();
	FinalList.assign(OutRecogResultList.begin(), OutRecogResultList.end());

	sort(FinalList.begin(), FinalList.end(), [](KeyWord s1, KeyWord s2){return s1.Pos[1] < s2.Pos[1]; });

	//标题存在时进行复位
	if (inTitlePos.size() > 0)
		m_titlePos = orgTitlePos;

}
void CExtractInfo::VerifyEachColInfo()
{
	for (int i = 0; i < TableSet.size(); i++)
	{
		//只校验金额、单价、数量
		if (TableSet[i].TitleCol[3] >= 0)
		{//金额
			int col = TableSet[i].TitleCol[3];
			if (col == 0)
			{
				//首列
			}
			else if (col == TableSet[i].ColWid.size() - 1)
			{
				//尾列
			}
			else
			{
				//中间校验前后,当前列数字数量num < 行/4，取相邻行不在TitleCol[]的数据，都不在取num多的列
				if (TableSet[i].eachColumnInfoSet[col].number < TableSet[i].RowHei.size() / 3)
				{
					if (col - 1 == TableSet[i].TitleCol[1] || col - 1 == TableSet[i].TitleCol[2])
						TableSet[i].TitleCol[3] = col - 1;
					else if (col + 1 == TableSet[i].TitleCol[1] || col + 1 == TableSet[i].TitleCol[2])
						TableSet[i].TitleCol[3] = col + 1;
					else
					{
						if (TableSet[i].eachColumnInfoSet[col - 1].num >= TableSet[i].eachColumnInfoSet[col + 1].num)
							TableSet[i].TitleCol[3] = col - 1;
						else
							TableSet[i].TitleCol[3] = col + 1;
					}
				}
			}
		}

		if (TableSet[i].TitleCol[2] >= 0)
		{//数量
			int col = TableSet[i].TitleCol[2];
			if (col == 0)
			{
				//首列
			}
			else if (col == TableSet[i].ColWid.size() - 1)
			{
				//尾列
			}
			else
			{
				//中间校验前后,当前列数字数量num < 行/4，取相邻行不在TitleCol[]的数据，都不在取num多的列
				if (TableSet[i].eachColumnInfoSet[col].number < TableSet[i].RowHei.size() / 4)
				{
					if (col - 1 == TableSet[i].TitleCol[1] || col - 1 == TableSet[i].TitleCol[3])
						TableSet[i].TitleCol[2] = col + 1;
					else if (col + 1 == TableSet[i].TitleCol[1] || col + 1 == TableSet[i].TitleCol[3])
						TableSet[i].TitleCol[2] = col + 1;
					else
					{
						if (TableSet[i].eachColumnInfoSet[col - 1].num >= TableSet[i].eachColumnInfoSet[col + 1].num)
							TableSet[i].TitleCol[2] = col - 1;
						else
							TableSet[i].TitleCol[2] = col + 1;
					}

				}
			}
		}
		if (TableSet[i].TitleCol[1] >= 0)
		{//单价
			int col = TableSet[i].TitleCol[1];
			if (col == 0)
			{
				//首列

			}
			else if (col == TableSet[i].ColWid.size() - 1)
			{
				//尾列
			}
			else
			{
				//中间校验前后,当前列数字数量num < 行/4，取相邻行不在TitleCol[]的数据，都不在取num多的列
				if (TableSet[i].eachColumnInfoSet[col].number < TableSet[i].RowHei.size() / 3)
				{
					if (col - 1 == TableSet[i].TitleCol[2] || col - 1 == TableSet[i].TitleCol[3])
						TableSet[i].TitleCol[1] = col + 1;
					else if (col + 1 == TableSet[i].TitleCol[2] || col + 1 == TableSet[i].TitleCol[3])
						TableSet[i].TitleCol[1] = col + 1;
					else
					{
						if (TableSet[i].eachColumnInfoSet[col - 1].num >= TableSet[i].eachColumnInfoSet[col + 1].num)
							TableSet[i].TitleCol[1] = col - 1;
						else
							TableSet[i].TitleCol[1] = col + 1;
					}
				}
			}
		}
	}
}

int CExtractInfo::getK()
{
	/***************************************************************************
	2021/03/10	kang
	使用场景：无表格无标题时得到Kmeans中K值
	代码思路：
	1、识别出的字符串x左边+20个像素-->直方图
	2、像素值排序->假设至少存在2列，两列均值/5>每列值时k++
	***************************************************************************/

	cv::Mat grayImg, binImage;
	if (srcImg.channels() == 1)
		grayImg = srcImg.clone();
	else
		cv::cvtColor(srcImg, grayImg, cv::COLOR_RGB2GRAY);

	cv::threshold(grayImg, binImage, 100, 255, THRESH_OTSU);

	//构造mask
	Mat histogramImage(binImage.rows, binImage.cols, CV_8UC1);
	for (int i = 0; i < binImage.rows; i++)
	{
		for (int j = 0; j < binImage.cols; j++)
		{
			histogramImage.at<uchar>(i, j) = 255;
		}
	}
	Mat histogramImage2 = histogramImage.clone();
	Mat histogramImage3 = histogramImage.clone();
	//for (int k = 0; k < OrgRecoglList.size(); k++)
	//{
	//	int startCol = OrgRecoglList[k].Pos[0]; //列
	//	int startRow = OrgRecoglList[k].Pos[1];	//行
	//	for (; startRow <= (OrgRecoglList[k].Pos[1] + OrgRecoglList[k].Pos[3]); startRow++)
	//	{
	//		for (; startCol <= (OrgRecoglList[k].Pos[0] + OrgRecoglList[k].Pos[2]); startCol++)
	//		{
	//			histogramImage.at<uchar>(startRow, startCol) = 0;
	//		}
	//		startCol = OrgRecoglList[k].Pos[0];;
	//	}
	//}
	//
	//imwrite("c:/histogramImage1.jpg", histogramImage);

	for (int k = 0; k < OrgRecoglList.size(); k++)
	{
		int startCol = OrgRecoglList[k].Pos[0]; //列
		int startRow = OrgRecoglList[k].Pos[1];	//行
		for (; startRow <= (OrgRecoglList[k].Pos[1] + OrgRecoglList[k].Pos[3]); startRow++)
		{
			for (int p = 1; p < 21; p++)
				histogramImage2.at<uchar>(startRow, startCol + p) = 0;
		}
	}

	vector<int> res(histogramImage2.cols, 0);
	for (int i = 0; i < histogramImage2.cols; i++)
	{
		for (int j = 0; j < histogramImage2.rows; j++)
		{
			if (histogramImage2.at<uchar>(j, i) == 0)
				res[i]++;
		}
	}
	for (int i = 0; i < histogramImage2.cols; i++)
	{
		for (int j = 0; j < res[i]; j++)
		{
			histogramImage3.at<uchar>(histogramImage2.rows - 1 - j, i) = 0;
		}
	}

	vector<vector<int>> slist;//直方图每列累计值->空白行为间隔
	for (int i = 0; i <res.size(); i++)
	{
		vector<int> temp;
		while (res[i] != 0)
		{
			temp.push_back(res[i]);
			i++;
		}
		if (temp.size() != 0)
			slist.push_back(temp);
			
	}

	//vector<int> slistMean;
	//for (int i = 0; i < slist.size(); i++)
	//{
	//	int smean = std::accumulate(slist[i].begin(), slist[i].end(), 0) / slist[i].size();
	//	slistMean.push_back(smean);
	//}
	//sort(slistMean.begin(), slistMean.end(),greater<int>());

	//int result = 2;
	//if (slistMean.size()>2)
	//{
	//	int smean = (slistMean[0] + slistMean[1]) / 2;
	//	for (int i = 2; i < slistMean.size(); i++)
	//	{
	//		if (slistMean[i] > smean / 50)
	//			result++;
	//	}
	//}
	//else
	//	result = 10;
	return slist.size();
	//imwrite("c:/histogramImage2.jpg", histogramImage2);
	//imwrite("c:/histogramImage3.jpg", histogramImage3);
}
void CExtractInfo::SortByKMeans(int col)
{
	/***************************************************************************
	2020/11/25	kang
	使用场景：无表格无标题时定位标题位置
	代码思路：
	1、通过KMeans对OrgRecoglList中x坐标进行分类（暂定10）
	2、根据分类结果统计每列（类）信息（中文、数字个数、数字之和等，同时排除编码、日期等干扰数据）
	3、中文字最多的列为项目名称列，数字和最大列为金额列，数字第二大列为单价列
	4、列属性定位完，定位项目名称-金额所在的行，然后记录同行数据（垂直交叉只保留一个）
	5、定位到的项目名称、金额取项目名称最宽的行作为标题宽，
	6、同时根据单价列属性和定位出的行信息定位出单价位置
	7、根据定位的位置信息与同行的关系，计算项目名称、金额、单价坐标位置
	***************************************************************************/

	if (OrgRecoglList.size() < 1)
		return;

	double* data = new double[OrgRecoglList.size()];
	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		data[i] = OrgRecoglList[i].Pos[0];
	}

	col = getK();


	const int size = OrgRecoglList.size(); //Number of samples
	const int dim = 1;   //Dimension of feature
	const int cluster_num = col; //Cluster number

	KMeans* kmeans = new KMeans(dim, cluster_num);
	int* labels = new int[size];
	kmeans->SetInitMode(KMeans::InitUniform);
	kmeans->Cluster(data, size, labels);

	vector<int> lableNum;
	for (int i = 0; i < size; ++i)
	{
		lableNum.push_back(labels[i]);
		//printf("%f, belongs to %d cluster\n", data[i*dim + 0], labels[i]);
	}

	delete[]data;
	delete[]labels;
	delete kmeans;

	//只统计大于平均列数的数据,取同一行数据标记为标题行
	vector<attribute> attributeSet;
	attributeSet.resize(col);
	for (int i = 0; i < OrgRecoglList.size(); ++i)
	{
		attributeSet[lableNum[i]].sum += OrgRecoglList[i].Pos[0];
		attributeSet[lableNum[i]].size++;
		attributeSet[lableNum[i]].dim = lableNum[i];
	}

	int sum = 0;
	for (int i = 0; i < col; ++i)
	{
		if (attributeSet[i].size > 0)
			attributeSet[i].average += attributeSet[i].sum / attributeSet[i].size;
		sum += attributeSet[i].size++;
	}

	int average = sum / col;
	FindNoTableTitleFlag(col, lableNum, attributeSet, average);
}

void CExtractInfo::FindNoTableTitleFlag(const int col, vector<int> &lableNum, vector<attribute> &attributeSet, int average)
{
	//根据每列属性信息，定位名称、金额所在列
	//中文最多的标题，金额数字最大
	//只统计距离簇中心近的数据abs < 20
	vector<EachColumnInfo> eachColumnInfoSet;
	eachColumnInfoSet.resize(col);

	vector<int> timeData(col, 0);//记录编码出现次数,出现次数大于行的1/3,数字为0
	vector<int> seqNum(col, 0);//1-2-3-4编码，上下相减=1出现的次数大于行的1/3,数字为0

	vector<int> seqNumLast(col, 0);//存储 
	for (int i = 0; i < lableNum.size(); i++)
	{
		int distance = abs(attributeSet[lableNum[i]].average - OrgRecoglList[i].Pos[0]);
		if (attributeSet[lableNum[i]].size >= average / 3 && distance < 20)
		{
			string strText = OrgRecoglList[i].RResult;
			int ChineseNumber = 0; //中文
			int number = 0; //数字个数
			int dotNumber = 0; //小数点
			int dateNumber = 0;
			int percentNum = 0;

			replace_all(strText, "￥", "");
			double num = atof(strText.c_str());

			for (int p = 0; p < strText.size(); p++)
			{
				if (strText.at(p) >= '0' &&strText.at(p) <= '9')
				{
					number++;
				}
				else if (strText.at(p) == '.')
				{
					dotNumber++;
				}
				else if (strText.at(p)<0 || strText.at(p)>126)
				{
					ChineseNumber++;
				}
				if (strText.at(p) == '%')
					percentNum++;
			}

			if (ChineseNumber > 0)
				ChineseNumber /= 2;
			if (IsValidData(strText))
			{
				number = 0;
				num = 0;
				dateNumber = 1;
			}

			for (int p = 0; p < seqNum.size(); p++)
			{
				int currentNum = atoi(strText.c_str());
				//初始化
				if (lableNum[i] == p && currentNum!= 0)
				{				
					if (abs(currentNum - seqNumLast[p]) == 1)
					{
						seqNum[lableNum[i]]++;
					}
					seqNumLast[p] = currentNum;
				}
			}
			int currentNum = atoi(strText.c_str());

			

			EachColumnInfo eachColumnInfo;

			//统计0在小数点
			int leftZero = 0;
			for (int k = strText.size() - 1; k >= 0; k--)
			{
				if (strText[k] == '0')
				{
					leftZero++;
				}
				else
					break;
			}
			if (number > 5 && (strText.size() - leftZero) > 5)
			{
				number = 0;
				num = 0;
				timeData[lableNum[i]]++;
			}

			eachColumnInfo.Column = lableNum[i];
			eachColumnInfo.ChineseNumber = ChineseNumber;
			eachColumnInfo.dotNumber = dotNumber;
			eachColumnInfo.number = number;
			eachColumnInfo.num = num; //数字之和
			eachColumnInfo.dateNum = dateNumber;
			eachColumnInfo.percentNum = percentNum;

			eachColumnInfoSet[lableNum[i]].Column = lableNum[i];
			eachColumnInfoSet[lableNum[i]].ChineseNumber += ChineseNumber;
			eachColumnInfoSet[lableNum[i]].dotNumber += dotNumber;
			eachColumnInfoSet[lableNum[i]].number += number;
			eachColumnInfoSet[lableNum[i]].num += num;
			eachColumnInfoSet[lableNum[i]].dateNum += dateNumber;
			eachColumnInfoSet[lableNum[i]].percentNum += percentNum;
		}
	}
	for (int i = 0; i < timeData.size(); i++)
	{
		if (timeData[i] >(average / 3))
		{
			eachColumnInfoSet[i].number = 0;
			eachColumnInfoSet[i].num = 0;
		}
	}

	for (int i = 0; i < seqNum.size(); i++)
	{
		if (seqNum[i] >(average / 3))
		{
			eachColumnInfoSet[i].number = 0;
			eachColumnInfoSet[i].num = 0;
		}
	}

	int maxChinese = 0, maxPrice = 0, secondPrice = 0;
	int titleFlag = 0, priceFlag = 0, djFlag = 0;

	for (int i = 0; i < eachColumnInfoSet.size(); i++)
	{
		//找到不同列中中文字数最多的列
		int chineseNum = eachColumnInfoSet[i].ChineseNumber;
		int num = eachColumnInfoSet[i].num;

		if (chineseNum > maxChinese)
		{
			maxChinese = chineseNum;
			titleFlag = i;
		}
	}
	sort(eachColumnInfoSet.begin(), eachColumnInfoSet.end(), [](EachColumnInfo s1, EachColumnInfo s2){return s1.num > s2.num; });

	priceFlag = eachColumnInfoSet[0].Column;
	djFlag = eachColumnInfoSet[1].Column;
	if (djFlag == titleFlag)
		djFlag = eachColumnInfoSet[2].Column;

	//验证金额可能是编码1-2-3-4
	FindNoTitlePos(lableNum, attributeSet, titleFlag, priceFlag, djFlag);
}
void CExtractInfo::FindNoTitlePos(vector<int> &lableNum, vector<attribute> &attributeSet, int titleFlag, int priceFlag, int djFlag)
{
	//定位标题位置所在行，项目名称-金额同一行误差10，且与簇中心坐标误差在15像素以内
	//找到此行所有数据，取出
	int titlePosX = attributeSet[titleFlag].average;
	int pricePosX = attributeSet[priceFlag].average;

	bool isFindName = false;
	bool isFindPrice = false;
	bool isFindDj = false;

	bool isFind = false;
	vector<int> res;//记录同行是否匹配过
	res.resize(lableNum.size());

	int orgTitleFlag = 0, orgPriceFlag = 0, orgDjFlag = 0;
	unordered_map<int, int> titlePrice;//项目名称-金额同行所有数据

	int runtimes = 0;//防止死循环退出
	while (!isFind)
	{
		for (int i = 0; i < OrgRecoglList.size(); i++)
		{
			if (titleFlag == lableNum[i] && !isFindName && res[i] == 0)
			{
				isFindName = true;
				orgTitleFlag = i;
				res[i] = 1;
			}
			if (priceFlag == lableNum[i] && !isFindPrice && res[i] == 0)
			{
				isFindPrice = true;
				orgPriceFlag = i;
				res[i] = 1;
			}
		}

		//不在同一行, 且x坐标与误差>10,则继续找
		if (OrgRecoglList[orgTitleFlag].Pos[1] + 10 > OrgRecoglList[orgPriceFlag].Pos[1] + OrgRecoglList[orgPriceFlag].Pos[3]
			|| OrgRecoglList[orgTitleFlag].Pos[1] + OrgRecoglList[orgTitleFlag].Pos[3] < OrgRecoglList[orgPriceFlag].Pos[1] + 10
			|| IsValidElem(OrgRecoglList[orgPriceFlag].RResult) == -1
			|| abs(OrgRecoglList[orgTitleFlag].Pos[0] - titlePosX) > 15
			|| abs(OrgRecoglList[orgPriceFlag].Pos[0] - pricePosX) > 15)
		{
			isFindName = false;
			isFindPrice = false;

			if (orgTitleFlag > orgPriceFlag)
				res[orgTitleFlag] = 0;
			else
				res[orgPriceFlag] = 0;

			runtimes++;
			if (runtimes > OrgRecoglList.size())
				isFind = true;
		}
		else
		{
			if (titlePrice.find(orgTitleFlag) != titlePrice.end())
				isFind = true;
			else
			{
				titlePrice.insert(make_pair(orgTitleFlag, orgPriceFlag));

				isFindName = false;
				isFindPrice = false;
				if (orgTitleFlag > orgPriceFlag)
					res[orgTitleFlag] = 0;
				else
					res[orgPriceFlag] = 0;
			}
		}
	}
	auto  it = titlePrice.begin();
	int maxWidth = 0;
	while (it != titlePrice.end())
	{
		int temp = OrgRecoglList[it->first].Pos[0] + OrgRecoglList[it->first].Pos[2];
		if (temp > maxWidth)
		{
			maxWidth = temp;
			orgTitleFlag = it->first;
			orgPriceFlag = it->second;
		}
		it++;
	}

	//找到同行左右，水平出现交叉且垂直方向不能交叉
	vector<RecogResult> titleRecoglList;
	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		if (OrgRecoglList[orgTitleFlag].Pos[1] + 10 > OrgRecoglList[i].Pos[1] + OrgRecoglList[i].Pos[3]
			|| OrgRecoglList[orgTitleFlag].Pos[1] + OrgRecoglList[orgTitleFlag].Pos[3] < OrgRecoglList[i].Pos[1] + 10
			|| OrgRecoglList[orgPriceFlag].Pos[1] + 10 > OrgRecoglList[i].Pos[1] + OrgRecoglList[i].Pos[3]
			|| OrgRecoglList[orgPriceFlag].Pos[1] + OrgRecoglList[orgPriceFlag].Pos[3] < OrgRecoglList[i].Pos[1] + 10)
		{
			;
		}
		else
		{
			//垂直方向	
			if ((OrgRecoglList[orgTitleFlag].Pos[0]> OrgRecoglList[i].Pos[0] + OrgRecoglList[i].Pos[2]
				|| OrgRecoglList[orgTitleFlag].Pos[0] + OrgRecoglList[orgTitleFlag].Pos[2] < OrgRecoglList[i].Pos[0])
				&& (OrgRecoglList[orgPriceFlag].Pos[0]  > OrgRecoglList[i].Pos[0] + OrgRecoglList[i].Pos[2]
				|| OrgRecoglList[orgPriceFlag].Pos[0] + OrgRecoglList[orgPriceFlag].Pos[2] < OrgRecoglList[i].Pos[0]))
				titleRecoglList.push_back(OrgRecoglList[i]);
			else if (i == orgTitleFlag || i == orgPriceFlag)
				titleRecoglList.push_back(OrgRecoglList[i]);
		}
	}
	//定位单价所在的具体位置
	vector<RecogResult> OrgDjList;
	for (int i = 0; i < OrgRecoglList.size(); i++)
	{
		for (int j = 0; j < titleRecoglList.size(); j++)
		{
			if (djFlag == lableNum[i])
			{
				//cout << titleRecoglList[j].Pos[0] << " " << OrgRecoglList[i].Pos[0] << " " << titleRecoglList[j].Pos[1] << " "<<OrgRecoglList[i].Pos[1] << endl;
				if ((int)titleRecoglList[j].Pos[0] == (int)OrgRecoglList[i].Pos[0] && (int)titleRecoglList[j].Pos[1] == (int)OrgRecoglList[i].Pos[1])
				{
					orgDjFlag = i;
					OrgDjList.push_back(OrgRecoglList[i]);
				}
			}
		}
	}
	//单价列为0,找一个距离当前列最近的数据
	int minHeight = 10000;
	if (OrgDjList.size() == 0)
	{
		for (int i = 0; i < OrgRecoglList.size(); i++)
		{
			for (int j = 0; j < titleRecoglList.size(); j++)
			{
				if (djFlag == lableNum[i])
				{
					if (abs(titleRecoglList[j].Pos[1] + titleRecoglList[j].Pos[3] / 2 - OrgRecoglList[i].Pos[1] - OrgRecoglList[i].Pos[3] / 2) < minHeight)
					{
						orgDjFlag = i;
					}
				}
			}
		}
		titleRecoglList.push_back(OrgRecoglList[orgDjFlag]);
	}

	//金额不在同一行时按照x坐标进行排序
	//sort(titleRecoglList.begin(), titleRecoglList.end(), [](RecogResult &a, RecogResult&b) {return a.Pos[0]<b.Pos[0]; });
	for (int i = 0; i < titleRecoglList.size(); i++)
	{
		for (int j = 0; j < titleRecoglList.size() - i - 1; j++)
		{
			if (titleRecoglList[j].Pos[0] > titleRecoglList[j + 1].Pos[0])
			{
				RecogResult Temp = titleRecoglList[j];
				titleRecoglList[j] = titleRecoglList[j + 1];
				titleRecoglList[j + 1] = Temp;
			}
		}
	}

	int posTitle = 0, posPrice = 0, posDj = 0;
	for (int i = 0; i < titleRecoglList.size(); i++)
	{
		//先定位出名称、金额所在位置
		if (titleRecoglList[i].Pos[0] == OrgRecoglList[orgTitleFlag].Pos[0])
			posTitle = i;
		if (titleRecoglList[i].Pos[0] == OrgRecoglList[orgPriceFlag].Pos[0])
			posPrice = i;
		if (titleRecoglList[i].Pos[0] == OrgRecoglList[orgDjFlag].Pos[0])
			posDj = i;
	}
	GetNoTitlePos(titleRecoglList, posTitle, posPrice, posDj);

}
void CExtractInfo::GetNoTitlePos(vector<RecogResult> &titleRecoglList, int posTitle, int posPrice, int posDj)
{
	TitlePos  t1;
	for (int i = 0; i < titleRecoglList.size(); i++)
	{
		//根据左右位置定位边界
		if (posTitle == 0 && posTitle == i)
		{
			int rightGap = (titleRecoglList[i + 1].Pos[0] - (titleRecoglList[i].Pos[0] + titleRecoglList[i].Pos[2])) / 2;
			int width = titleRecoglList[i].Pos[2] + rightGap + titleRecoglList[i].Pos[0] / 2;
			t1.NamePos = PosOfChar(titleRecoglList[i].Pos[0] / 2, titleRecoglList[i].Pos[1], width, titleRecoglList[i].Pos[3]);
		}
		else if (posTitle == titleRecoglList.size() - 1 && posTitle == i)
		{
			;
		}
		else if (posPrice == 0 && posPrice == i)
		{
			int rightGap = (titleRecoglList[i + 1].Pos[0] - (titleRecoglList[i].Pos[0] + titleRecoglList[i].Pos[2])) / 2;
			int width = titleRecoglList[i].Pos[2] + rightGap + titleRecoglList[i].Pos[0] / 2;
			t1.PricePos = PosOfChar(titleRecoglList[i].Pos[0] / 2, titleRecoglList[i].Pos[1], width, titleRecoglList[i].Pos[3]);
			
		}
		else if (posPrice == titleRecoglList.size() - 1 && posPrice == i)
		{
			int leftGap = (titleRecoglList[i].Pos[0] - (titleRecoglList[i - 1].Pos[0] + titleRecoglList[i - 1].Pos[2])) / 2;
			int left = titleRecoglList[i].Pos[0] - leftGap;
			int rightGap = (this->InputImage.cols - (titleRecoglList[i].Pos[0] + titleRecoglList[i].Pos[2])) / 2;
			int width = titleRecoglList[i].Pos[2] + rightGap + leftGap;
			t1.PricePos = PosOfChar(left, titleRecoglList[i].Pos[1], width, titleRecoglList[i].Pos[3]);
		}
		else
		{
 			int leftGap = (titleRecoglList[i].Pos[0] - (titleRecoglList[i - 1].Pos[0] + titleRecoglList[i - 1].Pos[2])) / 2;
			int left = titleRecoglList[i].Pos[0] - leftGap;
			int rightGap = (titleRecoglList[i + 1].Pos[0] - (titleRecoglList[i].Pos[0] + titleRecoglList[i].Pos[2])) / 2;
			int width = titleRecoglList[i].Pos[2] + rightGap + leftGap;
			if (i == posTitle)
				t1.NamePos = PosOfChar(left, titleRecoglList[i].Pos[1], width, titleRecoglList[i].Pos[3]);
			if (i == posPrice)
				t1.PricePos = PosOfChar(left, titleRecoglList[i].Pos[1], width, titleRecoglList[i].Pos[3]);
			if (i == posDj)
				t1.DjPos = PosOfChar(left, titleRecoglList[i].Pos[1], width, titleRecoglList[i].Pos[3]);
		}
	}
	if (titleRecoglList.size() > 0)
	{
		t1.NumPos = PosOfChar(-1, -1, -1, -1);
		t1.NamePos.pos[1] = 20;
		t1.PricePos.pos[1] = 20;
		t1.DjPos.pos[1] = 20;
		m_titlePos.push_back(t1);
	}
}
int CExtractInfo::FindDots(vector<RecogResult> &res)
{
	/***************************************************************************
	2020/12	kang 小数点校验
	***************************************************************************/

	if (res.size() < 5)
		return -1;

	//小数点个数>1/2补充
	int dotNum = 0;
	for (int i = 0; i < res.size(); i++)
	{
		string str = res[i].RResult;
		for (int j = 0; j < str.length(); j++)
		{
			if ((str[j] >= 48 && str[j] <= 57) || str[j] == '.')
			{
				if (str[j] == '.')
				{
					dotNum++;
					continue;
				}
			}
		}
	}
	if (dotNum < res.size() / 2)
		return -1;
	vector<int> dotpos(res.size(), -1);
	//小数点个数及小数点倒数第几位		
	for (int i = 0; i < res.size(); i++)
	{
		string str = res[i].RResult;
		res[i].RResult = str;
		replace_all(res[i].RResult, "￥", "");
		//去除中文字符
		if (!IsValidNumber(str))
			continue;
		bool isFindDot = false;
		for (int j = str.length() - 1; j > 0; j--)
		{
			if (str[j] == '.')
			{
				isFindDot = true;
				dotpos[i] = str.length() - j;
				break;
			}
		}
	}
	vector<int> dotposBak(dotpos.begin(), dotpos.end());
	sort(dotpos.begin(), dotpos.end(), [](int x, int y){return x > y; });
	//后几位增加
	int average = 0, sum = 0;
	for (int i = 0; i < dotpos.size() / 2; i++)
		sum += dotpos[i];

	if (dotpos.size()>0)
		average = sum / (dotpos.size() / 2);

	return average;

}
void CExtractInfo::JudgeTwoColumnByOverlap(int tableID)
{
	/***************************************************************************
	2021/01	kang 针对双列存在重叠情况，进行拆分
	1、判断是否存在两个金额（只针对存在标题时、金额项目名称重叠，下次会不会遇到其他重叠情况？）
	2、其中的一个金额和项目名称是在同一个表格
	3、在同一个表格时进行拆分，两个表格各保留重叠的列
	***************************************************************************/

	bool isOverlap = false;
	int splitcol = -1;
	for (int k = 0; k < this->TableSet[tableID].colSetForTitle.size() - 1; k++)
	{
		if (this->TableSet[tableID].colSetForTitle[k + 1] - this->TableSet[tableID].colSetForTitle[k] > 1 &&
			this->TableSet[tableID].colSetForRow[k + 1] == this->TableSet[tableID].colSetForRow[k])
		{
			int bFlag = 0;
			for (int j = this->TableSet[tableID].colSetForTitle[k] + 1; j <= this->TableSet[tableID].colSetForTitle[k + 1] && bFlag == 0; j++)
			{
				int row = this->TableSet[tableID].colSetForRow[k + 1];
				string str = this->TableSet[tableID].MatrixTable[row][j].strText;

				//找出项目名称所在行列
				for (int m = 0; m < TitleSet.size(); m++)
				{
					if (TitleSet[m].Flag == 6 && str.find(TitleSet[m].Name) != std::string::npos)
					{
						if (j == this->TableSet[tableID].colSetForTitle[k + 1])
								isOverlap = true;
						bFlag = 1;
						break;					
					}
				}
			}
			if (bFlag == 1)
				splitcol = this->TableSet[tableID].colSetForTitle[k + 1];
		}
	}

	//找到切分点，且拆分前和拆分后列>2，表明是双列数据
	if (splitcol > 2 && TableSet[tableID].ColWid.size() > 2 && TableSet[tableID].ColWid.size() - splitcol > 2 && splitcol < TableSet[tableID].ColWid.size())
	{
		//重叠了
		TableInfo tableInfo;
		this->TableSet[tableID].SplitTable(tableInfo, splitcol, isOverlap);
		this->TableSet.emplace_back(tableInfo);
	}
	else
	{
		;
	}

}
void CExtractInfo::MergeMultiColumn(const int tableID)
{
	/***************************************************************************
	2021/01	kang CPU项目名称一列识别成多列情况
	1、判断项目名称所在行列是否跨多列
	2、跨多列时将其他跨列合并到项目名称所在列
	***************************************************************************/
	//GetTableColumn(i);

	if (TableSet[tableID].TitleCol[0] == -1 || TableSet[tableID].TitleCol[3] == -1)
		return;

	int startRow = 0;

	if (TableSet[tableID].existTitle == 1)
	{
		if (TableSet[tableID].Row >= 0)
			startRow = TableSet[tableID].Row;
	}
	else
		return;

	bool isMultiColumn = false;
	int startCol = 0, endCol = 0, currCol = TableSet[tableID].TitleCol[0];

	for (int k = 0; k < TableSet[tableID].MatrixTable[startRow].size(); k++)
	{
		if (k == TableSet[tableID].TitleCol[0])
		{
			startCol = this->TableSet[tableID].MatrixTable[startRow][k].rowColumn[1];
			endCol = this->TableSet[tableID].MatrixTable[startRow][k].rowColumn[3];

			if (startCol != endCol)
			{
				isMultiColumn = true;
				break;
			}
		}
	}

	//合并
	if (isMultiColumn)
	{
		for (int j = startRow + 1; j < TableSet[tableID].MatrixTable.size(); j++)
		{
			for (int k = 0; k < TableSet[tableID].MatrixTable[j].size(); k++)
			{
				if (k >= startCol && k <= endCol && k != currCol)
				{
					if (k > currCol)
					{
						RecogResult title;
						title.RResult = this->TableSet[tableID].MatrixTable[j][k].strText;

						vector<PosOfChar> charPos(TableSet[tableID].MatrixTable[j][k].charPos.begin(), TableSet[tableID].MatrixTable[j][k].charPos.end());

						if (!title.RResult.empty() && title.RResult != this->TableSet[tableID].MatrixTable[j][currCol].strText
							&& this->TableSet[tableID].MatrixTable[j][k].charPos.size() != this->TableSet[tableID].MatrixTable[j][currCol].charPos.size())
						{
							this->TableSet[tableID].MatrixTable[j][currCol].strText += title.RResult;

							this->TableSet[tableID].MatrixTable[j][currCol].charPos.insert(TableSet[tableID].MatrixTable[j][currCol].charPos.end(),
								TableSet[tableID].MatrixTable[j][k].charPos.begin(), TableSet[tableID].MatrixTable[j][k].charPos.end());
						}
						//vector<PosOfChar> charPos2(TableSet[tableID].MatrixTable[j][currCol].charPos.begin(), TableSet[tableID].MatrixTable[j][currCol].charPos.end());
					}
					else
					{

						RecogResult title;
						title.RResult = this->TableSet[tableID].MatrixTable[j][k].strText;

						if (!title.RResult.empty())
						{
							this->TableSet[tableID].MatrixTable[j][currCol].strText.insert(this->TableSet[tableID].MatrixTable[j][currCol].strText.end(),
								title.RResult.begin(), title.RResult.end());

							this->TableSet[tableID].MatrixTable[j][currCol].charPos.insert(TableSet[tableID].MatrixTable[j][currCol].charPos.begin(),
								TableSet[tableID].MatrixTable[j][k].charPos.begin(), TableSet[tableID].MatrixTable[j][k].charPos.end());
						}
					}
				}
			}
		}
	}
}

void CExtractInfo::VerifyTitleCol()
{
	//校验时可能金额和单价列定位是错的
	for (int i = 0; i < TableSet.size(); i++)
	{
		int colCurr = -1;
		//数量列不存在时
		if (TableSet[i].TitleCol[3] >= 0 && TableSet[i].TitleCol[1] >= 0 && TableSet[i].TitleCol[2] == -1)
		{
			int num = 0;
			for (int j = 0; j < TableSet[i].MatrixTable[0].size(); j++)//列
			{
				if (j != TableSet[i].TitleCol[0] && j != TableSet[i].TitleCol[1] && j != TableSet[i].TitleCol[3])
				{
					for (int k = 0; k < TableSet[i].MatrixTable.size(); k++) //行
					{
						if (k > TableSet[i].Row)
						{
							std::string price = TableSet[i].MatrixTable[k][TableSet[i].TitleCol[3]].strText;
							std::string dj = TableSet[i].MatrixTable[k][TableSet[i].TitleCol[1]].strText;
							std::string curr = TableSet[i].MatrixTable[k][j].strText;							
							if (atof(curr.c_str()) > 0 && atof(dj.c_str()) > 0 && atof(curr.c_str()) * atof(dj.c_str()) == atof(price.c_str()))
								num++;
						}
					}
				}
				if (num > TableSet[i].MatrixTable[j].size() * 3 / 5)
				{
					TableSet[i].TitleCol[2] = j;
					if (m_titlePos.size() == i+1)
						m_titlePos.erase(m_titlePos.begin() + i);
					break;
				}
				num = 0;
			}
		}
	}

}
void CExtractInfo::MergeTitleCol(int tableID, int type)
{
	/***************************************************************************
	2021/02	kang 正常表格 CPU项目一列、明细识别成多列情况
	1、先查询项目名称列_字符串为空的数量（应该去相对数量、可能相邻列数据也为空）
	2、数量比例>50，统计相邻列不为空数量
	3、取字符串多的列进行合并
	***************************************************************************/

	if (TableSet[tableID].TitleCol[0] == -1 || TableSet[tableID].TitleCol[3] == -1)
		return;

	int startRow = 0;

	if (TableSet[tableID].existTitle == 1)
	{
		if (TableSet[tableID].Row >= 0)
			startRow = TableSet[tableID].Row;
	}
	else
		return;

	int num = 0; //字符串为空的相对数量
	int j = TableSet[tableID].TitleCol[0];
	int allNum = TableSet[tableID].MatrixTable.size() - startRow;

	if (allNum <= 0)
		return;

	for (int k = startRow; k < TableSet[tableID].MatrixTable.size(); k++) //行
	{
		RecogResult title;
		title.RResult = this->TableSet[tableID].MatrixTable[k][j].strText;
		////相邻都为空
		//if (j == 0)
		//{
		//	//项目名称最左
		//}
		if (title.RResult.empty())
		{
			num++;
		}
	}

	float p = (float)num / (float)allNum;
	if ((float)num / (float)allNum > 0.6)
	{
		//相邻列信息，排除单价，金额，数量列、
		int leftCol = j - 1;
		int rightCol = j + 1;

		//先确定左列 
		if (leftCol >= 0)
		{
			//leftCol排除首列情况
			if (leftCol != TableSet[tableID].TitleCol[3])
			{
				if (TableSet[tableID].TitleCol[1] != -1 && TableSet[tableID].TitleCol[2] != -1)
				{
					//单价、数量都存在
					if (leftCol != TableSet[tableID].TitleCol[1] && leftCol != TableSet[tableID].TitleCol[2])
					{
						;
					}
				}
				if (TableSet[tableID].TitleCol[1] == -1 && TableSet[tableID].TitleCol[2] != -1)
				{
					//只数量存在
				}
				if (TableSet[tableID].TitleCol[1] != -1 && TableSet[tableID].TitleCol[2] == -1)
				{				
					//只单价存在
				}
			}
		}

		if (rightCol <= TableSet[tableID].MatrixTable[0].size()-1)
		{
			//rightCol排除为尾列
			if (rightCol != TableSet[tableID].TitleCol[3])
			{
				if (TableSet[tableID].TitleCol[1] != -1 && TableSet[tableID].TitleCol[2] != -1)
				{
					//单价、数量都存在
					if (rightCol != TableSet[tableID].TitleCol[1] && rightCol != TableSet[tableID].TitleCol[2])
					{
						;
					}
				}
				if (TableSet[tableID].TitleCol[1] == -1 && TableSet[tableID].TitleCol[2] != -1)
				{
					;//只数量存在
				}
				if (TableSet[tableID].TitleCol[1] != -1 && TableSet[tableID].TitleCol[2] == -1)
				{
					;//只单价存在
				}
			}
		}

		if (leftCol < 0 && rightCol > 0)
		{
			int itemCol = TableSet[tableID].TitleCol[0];
			//只合并右侧,右侧往左边进行合并
			for (int k = startRow; k < TableSet[tableID].MatrixTable.size(); k++) //行
			{
				RecogResult title;
				title.RResult = this->TableSet[tableID].MatrixTable[k][rightCol].strText;

				vector<PosOfChar> charPos(TableSet[tableID].MatrixTable[k][rightCol].charPos.begin(), TableSet[tableID].MatrixTable[k][rightCol].charPos.end());

				TableSet[tableID].MatrixTable[k][itemCol].strText += title.RResult;
				TableSet[tableID].MatrixTable[k][itemCol].charPos.insert(TableSet[tableID].MatrixTable[k][itemCol].charPos.end(),charPos.begin(), charPos.end());		
			}		
		}
		else if (leftCol >= 0 && rightCol < 0)
		{
			//合并左侧.左侧往右边合
			int itemCol = TableSet[tableID].TitleCol[0];
			//只合并右侧,右侧往左边进行合并
			for (int k = startRow; k < TableSet[tableID].MatrixTable.size(); k++) //行
			{
				RecogResult title;
				title.RResult = this->TableSet[tableID].MatrixTable[k][leftCol].strText;

				vector<PosOfChar> charPos(TableSet[tableID].MatrixTable[k][leftCol].charPos.begin(), TableSet[tableID].MatrixTable[k][leftCol].charPos.end());

				TableSet[tableID].MatrixTable[k][itemCol].strText = title.RResult + TableSet[tableID].MatrixTable[k][itemCol].strText;
				TableSet[tableID].MatrixTable[k][itemCol].charPos.insert(TableSet[tableID].MatrixTable[k][itemCol].charPos.begin(),charPos.begin(), charPos.end());
			}

		}
		else if (leftCol >= 0 && rightCol > 0)
		{
			//左右都合并、比较左右两列不为空数量
			int numLeft = 0, rightNum = 0;
			int itemCol = TableSet[tableID].TitleCol[0];

			for (int k = startRow; k < TableSet[tableID].MatrixTable.size(); k++) //行
			{
				if (!this->TableSet[tableID].MatrixTable[k][leftCol].strText.empty())
					numLeft++;
				if (!this->TableSet[tableID].MatrixTable[k][rightCol].strText.empty())
					rightNum++;
			}
			if (numLeft <= rightNum)
			{
				for (int k = startRow; k < TableSet[tableID].MatrixTable.size(); k++) //行
				{
					//合并右侧
					RecogResult title;
					title.RResult = this->TableSet[tableID].MatrixTable[k][rightCol].strText;

					vector<PosOfChar> charPos;
					charPos.assign(TableSet[tableID].MatrixTable[k][rightCol].charPos.begin(), TableSet[tableID].MatrixTable[k][rightCol].charPos.end());

					TableSet[tableID].MatrixTable[k][itemCol].strText += title.RResult;
					TableSet[tableID].MatrixTable[k][itemCol].charPos.insert(TableSet[tableID].MatrixTable[k][itemCol].charPos.end(),charPos.begin(), charPos.end());
				}
			}
			else
			{
				for (int k = startRow; k < TableSet[tableID].MatrixTable.size(); k++) //行
				{
					//合并左侧
					RecogResult title;
					title.RResult = this->TableSet[tableID].MatrixTable[k][leftCol].strText;

					vector<PosOfChar> charPos(TableSet[tableID].MatrixTable[k][leftCol].charPos.begin(), TableSet[tableID].MatrixTable[k][leftCol].charPos.end());

					TableSet[tableID].MatrixTable[k][itemCol].strText = title.RResult + TableSet[tableID].MatrixTable[k][itemCol].strText;
					TableSet[tableID].MatrixTable[k][itemCol].charPos.insert(TableSet[tableID].MatrixTable[k][itemCol].charPos.begin(),charPos.begin(), charPos.end());
				}
			}
		}
	}	
}