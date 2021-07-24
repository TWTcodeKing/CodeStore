#pragma once

#if defined(_WIN32)

#include <afxinet.h>
#include <stdio.h>
#include <string>
#include "opencv2\opencv.hpp"

#pragma comment(lib,"Wininet.lib")

#define HTTP_POST_GB2312 1 //发送和接收的网页编码
#define HTTP_POST_UTF8  2

/************************************************************
 * 类名称：CHttpFileEx                                      *
 * 作  用：提供HTTP上传和下载功能                           *
 * 作  者：来源互联网                                       *
 * 版  权：所有权利归原作者所有                             *
 * 整理者：沈毅(shenyi0106@163.com) QQ:52851771             *
 * 时  间：2010-12-21                                       *
 *************************************************************/
/*************************************************************
 * 使用方法：                                                *
 * 上传带表单数据的图片:                                     *
 *  CHttpFileEx  httpPost;                                   *
 *  httpPost.SetServerParam("www.xx.com","/posttest.asp",80);*
 *  //添加表单数据                                           *
 *  httpPost.MakePostData("FormName","xxxxx");               *
 *  //添加图片数据                                           *
 *  TCHAR  *pRecvData = NULL; //接收数据的指针               *
 *  DWORD  dwRecvSize = 0;  //接收数据的大小                 *
 *  DWORD  dwRetSend = 0;  //发送函数返回值                  *
 *  int SendCode = HTTP_POST_GB2312;                         *
 *  int RecvCode =HTTP_POST_GB2312; //发送与接收的编码       *
 *  dwRetSend = httpPost.PostPicDataMethod("c:\\测试图片.jpg"*
 *  ,"filename", &pRecvData,dwRecvSize,SendCode,RecvCode);   *
 *************************************************************/

/*************************************************************
 * 修改人：zhiyuanc 
 * 时 间 ：20180515
 * 修改内容：由于在多字节项目下返回结果中文乱码，接收到再去转 *
 *			 码无效，所以返回结果定死为宽字节,即使在多字节项目*
 *			 下依然传入wchar_t*，收到后再转回来就可以解决中文 *
 *			 乱码问题										  *			
 *	CHttpFileEx httpFile;
 *	httpFile.SetServerParam("192.168.1.2", "/cognize", 8090); *
 *	wchar_t*  pRecvData = NULL; //接收数据的指针              *
 *	DWORD  dwRecvSize = 0;  //接收数据的大小				  *
 *	DWORD  dwRetSend = 0;  //发送函数返回值                   *
 *	int SendCode = HTTP_POST_UTF8; //                         *
 *	int RecvCode = HTTP_POST_UTF8; //发送与接收的编码         *
 *	dwRetSend = httpFile.PostPicDataMethod("caputre_temp.png",*
 * "image", &pRecvData, dwRecvSize, SendCode, RecvCode);
 *	string str = CStringOperator::ws2s(pRecvData);//自定义函数*
 *										wstring转string
 *	//解析json
 *************************************************************/




class CHttpFileEx
{
public:
	CHttpFileEx();
	virtual ~CHttpFileEx();
	void SetServerParam(CString strServerName, CString strObjectName, WORD Port);

	//构造协议数据内容
	BOOL MakePostData(LPCTSTR pPostName, LPCTSTR pPostValue);
	BOOL MakePostData(LPCTSTR pPostName,int iPostValue);


	//发送带图片的数据
	//changed by zhiyuanc 20180515 start 将第三个参数pRecvData的类型修改为wchar_t**，默认一直是宽字节，防止在多字节项目下中文乱码
	DWORD PostPicDataMethod(CString strLocalPath, LPCTSTR strFormName, wchar_t **pRecvData, DWORD &RecvSize,
		int SendCode = HTTP_POST_GB2312,//发送和接收的编码
		int RecvCode = HTTP_POST_GB2312); 
	//changed by zhiyuanc 20180515 end
	DWORD PostPicDataMethodForMat(cv::Mat srcImg, LPCTSTR strFormName, wchar_t **pRecvData, DWORD &RecvSize,
		int SendCode = HTTP_POST_GB2312,//发送和接收的编码
		int RecvCode = HTTP_POST_GB2312);

	//发送文本类数据
	DWORD PostDataMethod(LPCTSTR strDataSend, int DataSize, wchar_t **pRecvData, DWORD &RecvSize,
		int SendCode = HTTP_POST_GB2312,int RecvCode = HTTP_POST_GB2312);

	//下载HTTP文件，并保存成本地文件
	static BOOL DownLoadFile(CString strServerPath,CString strLocalFilePath);
private:
	void MakeHeaderData(); //构造协议头部数据
	void MakeEndData();  //构造协议尾部数据
	void MakePostPicData(LPCTSTR pPostName, LPCTSTR pPostValue); //构造图片前缀数据
	void MakePostPicData2(LPCTSTR strFormName, LPCTSTR Img);
	//返回值为图片大小，返回值为0表示不存在。
	DWORD GetExistPic(CString strPicPath);

	void WideCharToUTF8(LPCWSTR wpWideData, int WideLen);
	void MultiByteToUTF8(LPCSTR lpMultiData, int MultiLen);
	void UTF8ToWideChar(LPCSTR pUTF8,int UTF8Len);
	void UTF8ToMultiByte(LPCSTR pUTF8, int UTF8Len);
	void MultiToWide(LPCSTR strDataSend, int DataSize);
	void MultiToMulti(LPCSTR strDataSend, int DataSize);
	void WideToMulti(LPCWSTR wpWideData, int WideLen);
private:
	CString   m_strBoundary; //数据分隔符
	CString   m_strHeaderData; //协议头数据
	CString   m_strPostData; //协议正文数据
	CString   m_strEndData; //协议尾数据

	//服务器参数
	INTERNET_PORT m_nPort; 
	CString   m_strObjectName;
	CString   m_strServerName;
	/////编码转换/////////////////////////////////////////////////////////////
	//changed by zhiyuanc 20180515 start 取消多字节编码指针和其他相关变量
	char * m_lpUTF8;   //UTF8编码缓存指针
//	char * m_lpMultiByte; //Multil多字节编码指针
	wchar_t * m_wpWideChar;  //Widechar编码缓存指针
	int  m_nUTF8Len; 
//	int  m_nMultiByteLen;
	int  m_nWideCharLen;
	//changed by zhiyuanc 20180515 end
};


#endif