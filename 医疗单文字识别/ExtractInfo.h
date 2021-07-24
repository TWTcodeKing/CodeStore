#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#include "opencv2/opencv.hpp"
#include "common.h"
using namespace std;
using namespace cv;
//#define AUTO_RECOG_TITLE
//#define OUT_PUT
/*
医疗票据信息提取

*/
#define TYPE_TITLE 0
#define TYPE_PRICE 1
#define TYPE_CANPRICE 111  //这是价格的候选项
#define TYPE_DJ 2 
#define TYPE_NUM 3
/*
//#define AUTO_MODIFY_NAME
class KeyWord
{
public:
string Name;  //项目名称
string UnitPrice; //单价
string Number; //数量
string TotalPrice; //总价
float Pos[16];  //各个项目所在的位置(Pos[0-3]--项目, Pos[4-7]--总价,Pos[8-11]--单价, Pos[12-15]-数量,如果为-1则表明不存在)
vector<int> AdjIDOfName;  //名称的近邻识别结果（）

public:
KeyWord()
{
for (int i = 0; i < 16; i++)
{
Pos[i] = -1;
}
};

};

class MappedID
{
public:
int  ID;  //项目
int  MatchedID; //金额
int UnitPriceID; //单价
float fPriceRate[2];  //单价和项目、金额的比例
int NumID; //数量
int flag;  //flag=0;  项目和金额配对
};

class TitleKeyWord
{
public:
string Name;  //项目名称
int Flag;
int OrgID;
vector<string>filterName;
};

class PosOfChar
{
public:
PosOfChar(){}
PosOfChar &operator=(const PosOfChar&p)
{
this->pos[0] = p.pos[0];
this->pos[1] = p.pos[1];
this->pos[2] = p.pos[2];
this->pos[3] = p.pos[3];
return *this;
}
PosOfChar(int x, int y, int w, int l)
{
pos[0] = x;
pos[1] = y;
pos[2] = w;
pos[3] = l;
}
int pos[4];
};
*/

/*
"data": "实收金额",
"position" : "2091,99,2303,97,2303,141,2091,140"

class RecogResult
{
public:
string RResult; //识别结果
int orgID;
float Pos[8]; //在图像中的位置。Pos[0]，Pos[1]：左上角  Pos[2]，Pos[3]：右上角  Pos[4]，Pos[5]：左下角  Pos[6]，Pos[7]：右下角
vector<PosOfChar> charPos;
int Flag;  //0:待定 1：中文 2：数字, 3: 肯定正确的数字（能够转化为数字，几列之间存在计算关系：出现相等项，出现总和等于前两列项）4: 项目 5：单价 6：金额 7：数量
int IsMatched;  //是否已经被匹配
#ifndef AUTO_RECOG_TITLE
int titleID;
#endif
public:
RecogResult(){ IsMatched = -1; };
};

inline bool operator<(const RecogResult& s1, const RecogResult& s2)
{
return s1.Pos[0] < s2.Pos[0]; //从小到大排序
}
class TitlePos
{
public:

PosOfChar NamePos;
PosOfChar PricePos;
};
*/
//string g_iniPath;

class TitleKeyWordTable
{
public:
	string Name;  //项目名称
	int start_row;
	int start_column;
	int end_row;
	int end_column;
	int row_flag;
	int column_flag;
	int flag; //4、5、6、7类型
	int merge[5];//是否合并，合并之后起始行，终止行，起始列，终止列
	float Pos[8];//表格坐标
	float charPos[4];  //每个字符所在位置
};

class ElemOfTable
{
public:
	int position[8];  //表格四个顶点位置（左上，右上，右下，左下）
	int rowColumn[4]; //起始行列、终止行列
	string strText;
	vector<PosOfChar> charPos;  //每个字符所占位置
	vector<vector<PosOfChar>> allCharPos;//跨列字符
	vector<string> allStrText;
	vector<vector<string>> CandChar; //每个字符对应的候选字符
	int isMatched;

public:
	ElemOfTable()
	{
		isMatched = 0;
	}
	ElemOfTable(const ElemOfTable& a2)//拷贝构造函数
	{
		memcpy(this->position, a2.position, sizeof(int)* 8);
		memcpy(this->rowColumn, a2.rowColumn, sizeof(int)* 4);

		strText = a2.strText;
		isMatched = a2.isMatched;
		this->charPos.assign(a2.charPos.begin(), a2.charPos.end());

		this->allCharPos.resize(a2.allCharPos.size());
		for (int i = 0; i < a2.allCharPos.size(); i++)
		{
			this->allCharPos[i].assign(a2.allCharPos[i].begin(), a2.allCharPos[i].end());
		}

		this->allStrText.assign(a2.allStrText.begin(), a2.allStrText.end());

		this->CandChar.resize(a2.CandChar.size());
		for (int i = 0; i < a2.CandChar.size(); i++)
		{
			this->CandChar[i].assign(a2.CandChar[i].begin(), a2.CandChar[i].end());
		}
	}

	ElemOfTable& operator=(const ElemOfTable& a2) 	{
		if (&a2 == this)
		{
			return *this;
		}
		memcpy(this->position, a2.position, sizeof(int)* 8);
		memcpy(this->rowColumn, a2.rowColumn, sizeof(int)* 4);

		strText = a2.strText;

		this->charPos.assign(a2.charPos.begin(), a2.charPos.end());

		this->allCharPos.resize(a2.allCharPos.size());
		for (int i = 0; i < a2.allCharPos.size(); i++)
		{
			this->allCharPos[i].assign(a2.allCharPos[i].begin(), a2.allCharPos[i].end());
		}

		this->allStrText.assign(a2.allStrText.begin(), a2.allStrText.end());

		this->CandChar.resize(a2.CandChar.size());
		for (int i = 0; i < a2.CandChar.size(); i++)
		{
			this->CandChar[i].assign(a2.CandChar[i].begin(), a2.CandChar[i].end());
		}

		return *this;
	}
};


//无标题时用于统计每列数据
class EachColumnInfo
{
public:
	int Column;//所在列
	int ChineseNumber; //中文
	int number; //数字总数
	int dotNumber; //小数点
	double num; //总数
	int dateNum;//日期个数
	int percentNum;//百分号个数
};

class TableInfo
{
public:
	vector<vector<ElemOfTable>> MatrixTable;  //元素矩阵
	int TitleCol[4];  //TitleCol[0]: 项目名称的列索引；TitleCol[1]: 单价的列索引；TitleCol[2]: 数量的列索引；TitleCol[3]:总价的列索引；
	vector<int> ColWid;  //每列所占宽度
	vector<int> RowHei;  //每行所占高度
	vector<EachColumnInfo> eachColumnInfoSet;  //各种统计包括中文、数字等
	vector<int> colSetForTitle;  //找到的候选项目名称列
	vector<int> colSetForPrice;  //找到的候选总价列
	vector<int> colSetForDj;  //找到的候选项目名称列
	vector<int> colSetForNum;  //找到的候选总价列
	vector<int> colSetForRow;  //候选行

	vector<int> rowSetForTitle;  //找到的候选项目名称列
	vector<int> rowSetForPrice;  //找到的候选总价列
	vector<int> rowSetForDj;  //找到的候选项目名称列
	vector<int> rowSetForNum;  //找到的候选总价列

	int existTitle;//默认有标题
	int Row;  //标题行索引（如果-1,则表明从第一行开始取数据）
	int titleID;
	TableInfo()
	{
		TitleCol[0] = -1;
		TitleCol[1] = -1;
		TitleCol[2] = -1;
		TitleCol[3] = -1;
		Row = -1;
		existTitle = 1;
	}

	void SplitTable(TableInfo& tableNew, int splitCol)
	{
		int newcol = MatrixTable[0].size() - splitCol;

		tableNew.MatrixTable.resize(MatrixTable.size());

		for (int i = 0; i < MatrixTable.size(); i++)
		{
			tableNew.MatrixTable[i].resize(newcol);
			for (int j = 0; j < newcol; j++)
			{
				tableNew.MatrixTable[i][j] = MatrixTable[i][j + splitCol];   //ElemOfTable需要重载=号				
			}
			//删除这部分数据
			MatrixTable[i].erase(MatrixTable[i].begin() + splitCol, MatrixTable[i].end());
		}

		/*	tableNew.ColWid.assign(this->ColWid.begin() + splitCol, this->ColWid.end());
		this->ColWid.erase(this->ColWid.begin() + splitCol, this->ColWid.end());

		tableNew.RowHei.assign(this->RowHei.begin(), this->RowHei.end());*/

		tableNew.eachColumnInfoSet.assign(this->eachColumnInfoSet.begin() + splitCol, this->eachColumnInfoSet.end());

		this->eachColumnInfoSet.erase(this->eachColumnInfoSet.begin() + splitCol, this->eachColumnInfoSet.end());


		tableNew.ColWid.assign(this->ColWid.begin() + splitCol, this->ColWid.end());

		tableNew.RowHei.assign(this->RowHei.begin(), this->RowHei.end());

		for (int i = 0; i < ColWid.size(); i++)
		{
			if (i >= splitCol)
			{
				this->ColWid.erase(this->ColWid.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < tableNew.eachColumnInfoSet.size(); i++)
		{
			tableNew.eachColumnInfoSet[i].Column = tableNew.eachColumnInfoSet[i].Column - splitCol;
		}
		tableNew.eachColumnInfoSet.erase(tableNew.eachColumnInfoSet.begin() + newcol, tableNew.eachColumnInfoSet.end());

		for (int i = 0; i < colSetForTitle.size(); i++)
		{
			if (colSetForTitle[i] >= splitCol)
			{
				tableNew.colSetForTitle.push_back(colSetForTitle[i] - splitCol);
				tableNew.rowSetForTitle.push_back(rowSetForTitle[i]);
				this->colSetForTitle.erase(colSetForTitle.begin() + i);
				this->rowSetForTitle.erase(rowSetForTitle.begin() + i);
				tableNew.colSetForRow.push_back(colSetForRow[i]);
				this->colSetForRow.erase(colSetForRow.begin() + i);
			}
		}

		for (int i = 0; i < colSetForPrice.size(); i++)
		{
			if (colSetForPrice[i] >= splitCol)
			{
				tableNew.colSetForPrice.push_back(colSetForPrice[i] - splitCol);
				this->colSetForPrice.erase(colSetForPrice.begin() + i);
				tableNew.rowSetForPrice.push_back(rowSetForPrice[i]);
				this->rowSetForPrice.erase(rowSetForPrice.begin() + i);
			}
		}
		for (int i = 0; i < colSetForDj.size(); i++)
		{
			if (colSetForDj[i] >= splitCol)
			{
				tableNew.colSetForDj.push_back(colSetForDj[i] - splitCol);
				this->colSetForDj.erase(colSetForDj.begin() + i);
				tableNew.rowSetForDj.push_back(rowSetForDj[i]);
				this->rowSetForDj.erase(rowSetForDj.begin() + i);
			}
		}
		for (int i = 0; i < colSetForNum.size(); i++)
		{
			if (colSetForNum[i] >= splitCol)
			{
				tableNew.colSetForNum.push_back(colSetForNum[i] - splitCol);
				this->colSetForNum.erase(colSetForNum.begin() + i);
				tableNew.rowSetForNum.push_back(rowSetForNum[i]);
				this->rowSetForNum.erase(rowSetForNum.begin() + i);
			}
		}

	}
	void SplitTable(TableInfo& tableNew, int splitCol,bool isOverlap)
	{
		if (isOverlap)
		{
			int newcol = MatrixTable[0].size() - splitCol;

			tableNew.MatrixTable.resize(MatrixTable.size());

			for (int i = 0; i < MatrixTable.size(); i++)
			{
				tableNew.MatrixTable[i].resize(newcol);
				for (int j = 0; j < newcol; j++)
				{
					tableNew.MatrixTable[i][j] = MatrixTable[i][j + splitCol];   //ElemOfTable需要重载=号				
				}
				//删除这部分数据
				MatrixTable[i].erase(MatrixTable[i].begin() + splitCol+1, MatrixTable[i].end());
			}

			/*	tableNew.ColWid.assign(this->ColWid.begin() + splitCol, this->ColWid.end());
			this->ColWid.erase(this->ColWid.begin() + splitCol, this->ColWid.end());

			tableNew.RowHei.assign(this->RowHei.begin(), this->RowHei.end());*/

			tableNew.eachColumnInfoSet.assign(this->eachColumnInfoSet.begin() + splitCol, this->eachColumnInfoSet.end());

			this->eachColumnInfoSet.erase(this->eachColumnInfoSet.begin() + splitCol+1, this->eachColumnInfoSet.end());


			tableNew.ColWid.assign(this->ColWid.begin() + splitCol, this->ColWid.end());

			tableNew.RowHei.assign(this->RowHei.begin(), this->RowHei.end());

			for (int i = 0; i < ColWid.size(); i++)
			{
				if (i >= splitCol+1)
				{
					this->ColWid.erase(this->ColWid.begin() + i);
					i--;
				}
			}

			for (int i = 0; i < tableNew.eachColumnInfoSet.size(); i++)
			{
				tableNew.eachColumnInfoSet[i].Column = tableNew.eachColumnInfoSet[i].Column - splitCol;
			}
			tableNew.eachColumnInfoSet.erase(tableNew.eachColumnInfoSet.begin() + newcol, tableNew.eachColumnInfoSet.end());

			for (int i = 0; i < colSetForTitle.size(); i++)
			{
				if (colSetForTitle[i] >= splitCol)
				{
					tableNew.colSetForTitle.push_back(colSetForTitle[i] - splitCol);
					tableNew.rowSetForTitle.push_back(rowSetForTitle[i]);
					this->colSetForTitle.erase(colSetForTitle.begin() + i);
					this->rowSetForTitle.erase(rowSetForTitle.begin() + i);
					tableNew.colSetForRow.push_back(colSetForRow[i]);
					this->colSetForRow.erase(colSetForRow.begin() + i);
				}
			}

			for (int i = 0; i < colSetForPrice.size(); i++)
			{
				if (colSetForPrice[i] >= splitCol)
				{
					tableNew.colSetForPrice.push_back(colSetForPrice[i] - splitCol);
					this->colSetForPrice.erase(colSetForPrice.begin() + i);
					tableNew.rowSetForPrice.push_back(rowSetForPrice[i]);
					this->rowSetForPrice.erase(rowSetForPrice.begin() + i);
				}
			}
			for (int i = 0; i < colSetForDj.size(); i++)
			{
				if (colSetForDj[i] >= splitCol)
				{
					tableNew.colSetForDj.push_back(colSetForDj[i] - splitCol);
					this->colSetForDj.erase(colSetForDj.begin() + i);
					tableNew.rowSetForDj.push_back(rowSetForDj[i]);
					this->rowSetForDj.erase(rowSetForDj.begin() + i);
				}
			}
			for (int i = 0; i < colSetForNum.size(); i++)
			{
				if (colSetForNum[i] >= splitCol )
				{
					tableNew.colSetForNum.push_back(colSetForNum[i] - splitCol);
					this->colSetForNum.erase(colSetForNum.begin() + i);
					tableNew.rowSetForNum.push_back(rowSetForNum[i]);
					this->rowSetForNum.erase(rowSetForNum.begin() + i);
				}
			}
		}
		else
		{

			int newcol = MatrixTable[0].size() - splitCol;

			tableNew.MatrixTable.resize(MatrixTable.size());

			for (int i = 0; i < MatrixTable.size(); i++)
			{
				tableNew.MatrixTable[i].resize(newcol);
				for (int j = 0; j < newcol; j++)
				{
					tableNew.MatrixTable[i][j] = MatrixTable[i][j + splitCol];   //ElemOfTable需要重载=号				
				}
				//删除这部分数据
				MatrixTable[i].erase(MatrixTable[i].begin() + splitCol, MatrixTable[i].end());
			}

			/*	tableNew.ColWid.assign(this->ColWid.begin() + splitCol, this->ColWid.end());
			this->ColWid.erase(this->ColWid.begin() + splitCol, this->ColWid.end());

			tableNew.RowHei.assign(this->RowHei.begin(), this->RowHei.end());*/

			tableNew.eachColumnInfoSet.assign(this->eachColumnInfoSet.begin() + splitCol, this->eachColumnInfoSet.end());

			this->eachColumnInfoSet.erase(this->eachColumnInfoSet.begin() + splitCol, this->eachColumnInfoSet.end());


			tableNew.ColWid.assign(this->ColWid.begin() + splitCol, this->ColWid.end());

			tableNew.RowHei.assign(this->RowHei.begin(), this->RowHei.end());

			for (int i = 0; i < ColWid.size(); i++)
			{
				if (i >= splitCol)
				{
					this->ColWid.erase(this->ColWid.begin() + i);
					i--;
				}
			}

			for (int i = 0; i < tableNew.eachColumnInfoSet.size(); i++)
			{
				tableNew.eachColumnInfoSet[i].Column = tableNew.eachColumnInfoSet[i].Column - splitCol;
			}
			tableNew.eachColumnInfoSet.erase(tableNew.eachColumnInfoSet.begin() + newcol, tableNew.eachColumnInfoSet.end());

			for (int i = 0; i < colSetForTitle.size(); i++)
			{
				if (colSetForTitle[i] >= splitCol)
				{
					tableNew.colSetForTitle.push_back(colSetForTitle[i] - splitCol);
					tableNew.rowSetForTitle.push_back(rowSetForTitle[i]);
					this->colSetForTitle.erase(colSetForTitle.begin() + i);
					this->rowSetForTitle.erase(rowSetForTitle.begin() + i);
					tableNew.colSetForRow.push_back(colSetForRow[i]);
					this->colSetForRow.erase(colSetForRow.begin() + i);
					i--;
				}
			}

			for (int i = 0; i < colSetForPrice.size(); i++)
			{
				if (colSetForPrice[i] >= splitCol)
				{
					tableNew.colSetForPrice.push_back(colSetForPrice[i] - splitCol);
					this->colSetForPrice.erase(colSetForPrice.begin() + i);
					tableNew.rowSetForPrice.push_back(rowSetForPrice[i]);
					this->rowSetForPrice.erase(rowSetForPrice.begin() + i);
					i--;
				}
			}
			for (int i = 0; i < colSetForDj.size(); i++)
			{
				if (colSetForDj[i] >= splitCol)
				{
					tableNew.colSetForDj.push_back(colSetForDj[i] - splitCol);
					this->colSetForDj.erase(colSetForDj.begin() + i);
					tableNew.rowSetForDj.push_back(rowSetForDj[i]);
					this->rowSetForDj.erase(rowSetForDj.begin() + i);
					i--;
				}
			}
			for (int i = 0; i < colSetForNum.size(); i++)
			{
				if (colSetForNum[i] >= splitCol)
				{
					tableNew.colSetForNum.push_back(colSetForNum[i] - splitCol);
					this->colSetForNum.erase(colSetForNum.begin() + i);
					tableNew.rowSetForNum.push_back(rowSetForNum[i]);
					this->rowSetForNum.erase(rowSetForNum.begin() + i);
					i--;
				}
			}
		}

	}

	TableInfo &operator=(const TableInfo & p)
	{
		if (this != &p)
		{
			//this->MatrixTable.assign(p.MatrixTable.begin(), p.MatrixTable.end());
			this->MatrixTable.resize(p.MatrixTable.size());
			for (int i = 0; i < p.MatrixTable.size(); i++)
			{
				this->MatrixTable[i].assign(p.MatrixTable[i].begin(), p.MatrixTable[i].end());
			}

			this->Row = p.Row;
			this->ColWid.assign(p.ColWid.begin(), p.ColWid.end());
			this->RowHei.assign(p.RowHei.begin(), p.RowHei.end());
			this->colSetForTitle.assign(p.colSetForTitle.begin(), p.colSetForTitle.end());
			this->colSetForPrice.assign(p.colSetForPrice.begin(), p.colSetForPrice.end());
			this->colSetForDj.assign(p.colSetForDj.begin(), p.colSetForDj.end());
			this->colSetForNum.assign(p.colSetForNum.begin(), p.colSetForNum.end());

			this->rowSetForTitle.assign(p.rowSetForTitle.begin(), p.rowSetForTitle.end());
			this->rowSetForPrice.assign(p.rowSetForPrice.begin(), p.rowSetForPrice.end());

			this->rowSetForDj.assign(p.rowSetForDj.begin(), p.rowSetForDj.end());
			this->rowSetForNum.assign(p.rowSetForNum.begin(), p.rowSetForNum.end());

			memcpy(this->TitleCol, p.TitleCol, sizeof(int)* 4);
		}
		return *this;
	}
};

class HosElem
{
public:
	int hosID;
	string hosName;
};

class CExtractInfo
{
public:
	CExtractInfo();
	~CExtractInfo();
	vector<TitlePos> m_titlePos;
	vector<TitlePos> m_titlePosCand;
public:
	vector<RecogResult> RecoglList;  //去除了部分无效识别项
	vector<RecogResult> OrgRecoglList;  //原始识别结果

	vector<KeyWord> FinalList;  //最终得到的明细
	vector<TitleKeyWord> TitleSet;  //用于定位标题的关键字
	vector<MappedID>  mappedSet;  ///匹配对集合

	vector<string>  splitedStr;  ///匹配对集合


	int aveYPosOfTitle;  //标题所在的Y平均坐标
	int NumofTitle;

	Mat InputImage;  //输入图像
	Mat TempImage;

	String openedfile;
	String openeddir;


	/*
	提取信息入口函数
	输入：
	1. OCR识别结果，采用JASON结构表示的字符串
	2. RGBImage识别结果对应的图像
	输出：
	1. 识别明细，采用JASON结构表示的字符串
	2. 条目数量
	*/
	int ExtractInfo(char *ListDetail, unsigned char *RGBImage, int imageWidth, int imageHeight);
	string ExtractInfo(char *ColorImage, const char *IPAddress, const char *ObjFun, int Port/*,  vector<TitlePos>& v_titlePos*/);

	//定位检测项目
	int LocalName();

	//判断识别结果类型,后两个参数用于截取识别的标题过长，得到它在原字符串中的起始终止字符索引
	int CheckRecogType(string strRecog, int &, int &);

	//标题找到了项目和金额
	int DecodeByNameAndTotal(int NameID, int TotalID, int curMapID);

	//找到下方相邻项
	int FindNearBottom(int OrgID);

	//找到右侧相邻项
	int FindNearRight(int OrgID, int& IsDot);

	//找到左侧相邻项
	int FindNearLeft(int OrgID, int& IsDot);

	//对找到的金额列进行后续修正
	int PostTotalPrice(int curID);

	int OutputImage(char *outputfile, int drawtitle = 0, int drawdetail = 0);

	int PostProcTotalPrice(string& input, string& output);

	//判断这一项是否有效
	int IsValidElem(int nameID, int priceID);
	int IsValidElem(string str);
	//找到最优匹配单价
	int FindMatchedUnitPrice(int nameID, int priceID, int mapID);

	//二次扫描以找出丢失项
	void ResearchLoseItem();
	void ResearchLostItemByPrice();
	void ResearchLostItemByName();
	/*取标题项*/
	int getItemPos(RecogResult& itemName, RecogResult& itemPrice);

	//获取最终明细
	const vector<KeyWord>& getFinalList(){ return FinalList; }

	void ImgRotate(Mat& src, Mat& dst, double angle);
public:
	//
	void DecodeOneImage(char *imgename, const char *IPAddress, const char *ObjFun, int Port, int type);

	int IsGoodPair(int LastID, int ID, int MatchedLastID, int MatchedID);

	//得到匹配的项目和金额ID
	int GetMatchedNameAndTotal();

	//得到名字项的近邻集合ID
	int GetAdjIDofName(int CurID);

	//是否是有效的名字项
	int IsValidName();

	//是否是有效的日期
	int IsValidData(string strText);
	int IsValidNumber();
	//是否包含数字
	int IsValidNumber(string strText);

	int DrawVerLine(int beginID, int endID);
	//vector<RecogResult> recogList;

	int TranFound(int found, string strInfo);
	int InvTranFound(int found, string strInfo);

public:
	int PushRecogResult(string strText, string strPos, vector<PosOfChar>& charPos);


	int SplitRegions(vector<RecogResult>& FinalelemSet, RecogResult elem);

	//void SplitExceptionItem(vector<RecogResult>& FinalelemSet);
	//int FindExcetionItemPos(const vector<PosOfChar>& charPos);

	int CheckChinese(string InputStr, bool bNum, bool bChar, bool bAddLegal, vector<char>& LegalChar);
	int DrawVerLine();

	int DrawRectangle(Mat& drawImage, int ID, int colorID = 0);

	//找到切分字符最前面位置
	int FindSplitPos(RecogResult& InputStr);

#ifndef AUTO_RECOG_TITLE
	void DrawRect(RecogResult recog, int type = 1)
	{
		cv::Rect rc;
		rc.x = recog.Pos[0];
		rc.y = recog.Pos[1];
		rc.width = recog.Pos[2];
		rc.height = recog.Pos[3];

		auto color = CV_RGB(255, 0, 0);
		switch (type)
		{
		case 1:
			break;
		case 2:
			color = CV_RGB(255, 128, 0);
			break;
		case 3:
			color = CV_RGB(0, 0, 255);
			break;
		case 4:
			color = CV_RGB(0, 128, 200);
			break;
		default:
			color = CV_RGB(0, 0, 0);
			break;
		}
		//	rectangle(this->InputImage, rc, color);
	}
	void SplitTitle(RecogResult &, int, int);//切分标题

	int PushRecogResult2(string strText, string strPos, vector<PosOfChar>& charPos);
	void SubString(vector<RecogResult> &subEle, RecogResult ele);//根据标题位置进行切分
	int SplitRegions2(vector<RecogResult>& FinalelemSet, RecogResult elem, int type, int);//切分后的结果保存在FinalelemSet中
	int TranFound2(int found, string strInfo);//根据字符位置找字符串的实际位置，小-》大
	void MatchResult();//最终的结果匹配
	int isSameLineByTitle(const RecogResult &, const RecogResult &);//按照标题位置的相对距离来判断是否在同一行
	void DrawLine(const RecogResult &, const RecogResult &);//在两个项之间绘制横线
	void addToFinalList(const RecogResult &, const RecogResult &);//添加到结果中

#if defined(_WIN32)
	string ExtractInfo(cv::Mat ocrImg, const char *IPAddress, const char *ObjFun, int Port/*, vector<TitlePos>& v_titlePos*/);
	void DecodeOneImage(cv::Mat ocrImg, const  char *IPAddress, const char *ObjFun, int Port, int type);//type=1按版本1，type=2 按版本2
#endif

private:
	vector<RecogResult> v_title;//保留待匹配的标题结果
	vector<RecogResult> v_price;//保留待匹配的金额结果
	vector<RecogResult> v_dj;//保留待匹配的单价结果
	vector<RecogResult> v_num;//保留待匹配的数量结果

	vector<RecogResult> v_title_table;//保留待匹配的标题结果
	vector<RecogResult> v_price_table;//保留待匹配的金额结果
	vector<RecogResult> v_dj_table;//保留待匹配的单价结果
	vector<RecogResult> v_num_table;//保留待匹配的数量结果

	vector<vector<RecogResult>> v_title_table_set;
	vector<vector<RecogResult>> v_price_table_set;
	vector<vector<RecogResult>> v_dj_table_set;
	vector<vector<RecogResult>> v_num_table_set;


public:

	void AutoGetNamePricePos();//自动获取标题位置
	void findAdjacent(int curId, int &leftId, int &rightId);//根据curId找到它同行的左右两项的Id，未找到返回-1
	void findPosX(const cv::Mat&, int id, int &leftX, int &rightX);
	cv::Mat srcImg;

	void HandleLongPrice(RecogResult &priceEle);
	static bool traitNumber(string & price);//
	static bool traitNumber(string & price, int type);//小数点位数
	static string formatNumber(string s, int);//格式化逗号
	static void replace_all(string& str, const string& old_value, const string& new_value);
	static void replaceInvalidCharater(string & str);//替换无效字符

	void ReFindTitleWithSingleCharater();//用于标题未识别的情况，比如标题两个字离的特别远的
	int FindNextBlackPt(const cv::Mat&, int x, int y, int direction);//从x方向向左或向右找到第一个黑色的点
	void PostTitlePos(char *ColorImage, const char *IPAddress, const char *ObjFun, int Port);//如果名称识别项与价格识别项相差较多，则有可能标题位置不对，向两边延伸
	bool IsSameLine(RecogResult r1, RecogResult r2);
	//	bool isNeedSplit(const RecogResult &);//对于标题项识别有空格的，不切分
	//vector<RecogResult>m_titleName, m_priceName;

	//修正标题添加
	static void AnsiToUTF8(string &str);
	static void UTF8ToAnsi(string& strUTF8);
	static int callback(void *data, int argc, char **argv, char **azColName);
	void ModifyNameFromSqlite(string &);

	//外部导入全文识别结果
	void SetFullRecogJsonStr(const string &str){ m_strRecogJson = str; }

	//	sqlite3 *m_pDB;
public:
	int GetOcrVersion();
	string m_strRecogJson = "";

	//把识别结果转化成jason字符串
	string makeBillJson();

	string filename;

	//根据名称和金额识别单价和数量所在标题位置
	/*
	输入：
	输出：
	1：找到单价和数量位置
	-1：找不到单价和数量位置
	*/
	int RecognizePriceAndNumber(RecogResult& UnitPircPos, RecogResult& NumberPos,
		RecogResult& TitlePos, RecogResult& TotalPricePos);

	//根据单价和数量标题得到具体内容
	int RecognizePriceAndNumberByTitle(vector<KeyWord>& listSet,
		RecogResult& UnitPircPos, RecogResult& NumberPos,
		RecogResult& TitlePos, RecogResult& TotalPricePos, int colID);

	int FindBestMatchByTriplet(vector<KeyWord>& listSet, int curID, RecogResult& ThirdPos, RecogResult& TitlePos, RecogResult& TotalPricePos);

	int DrawRectangleForUnit(Mat& drawImage, RecogResult rectoList);

	void AddDjAndNum();

	void AddDjAndNumUnit();

	void extractNumber(string strText, string& strPrice);

	RecogResult GetPosInfo(PosOfChar &inPos);

	void DecodeOneImageFromString(char *imgename, const  char *IPAddress, const char *ObjFun, int Port, int type);

	string FormulateJasonList();
	string FormulateJasonFullText(string& recogJason);

	//对自动定位得到的标题进行修正处理
	void  RefineAutoTitle();

	//切分单价和金额
	int SplitTitleRegions(vector<RecogResult>& FinalelemSet, RecogResult elem);

	//对标题栏进行合并处理
	int MergeTitle();

	string PointToSting(int point[]);

	//获取最终明细
	const map<string, string>& GetMarkPos(){
		return m_MarkedPosMap;
	}

	cv::Rect PosToTect(PosOfChar& titlpos);
	cv::Rect ArrayToTect(float *titlpos);

	//对于名称中间有空格的，用这个方法进行拼接，
	int MergeForTitle();

	void optimizeNumber(string& strPrice);
	//bool extractNumberfromstring(string strText, string& strPrice);
	bool getNumber(string strText, string& strNumber);

	void LeftOutStr(string& src_str, const string& limit_str);
	void splite(const string& key_str, const string& split_flag, vector<string>& value_vec);

public:
	Json::Reader m_reader;
	Json::Value m_root;
	Json::Value m_data;
	int m_ocrEngineType;
	int m_djsl;
	int PageID;
	int angleRot;
	int m_initjson;
	map<string, string> m_MarkedPosMap; //记录待保存的模板坐标
	map<string, string> m_filemarkpos; //读取本地文件的模板坐标

	vector<RecogResult> CandTitleList;  //对于部分可能的标题数据先存储起来，后续做合并处理


	void GetDetailListTable();
	//这是一个根据医院名称增加解析准确率的代码
	int ProcessForSpecialHos();

	int ProcessForYuYaoHos();

	int m_nPriceCount;

	int isManual = -1;

	vector<HosElem> HospitalSet;  //特殊医院集合

	vector<TableInfo> TableSet;

	int HospitalID;//0: 武汉大学中南医院

	int CorrlastI;  //上次匹配成功的结果索引
	int CorrlastJ;

	int GetRecogedTable();

	//无表格
	int DecodeRecogedTable(int type);

	int DetectColFlagOfTable();

	//第二次解析，拆分表格，解决跨列问题
	int DecodeTableAgain();

	//根据所确定行列，添加每组数据
	int GetTableColumn(int tableID);

	//数字处理、过滤
	void JudgeRowTableType();

	//处理缺少单价或者数量的列
	void GetNumDj();

	int JudgeTwoColumn(int tableID);

	int JudgeTwoColumnWithoutTitle(int tableID);

	//统计每列的中文、数字相关信息
	void CountColInfo(vector<EachColumnInfo>& eachColumnInfoSet, int tableID);

	//查找标题所在列
	void FindTitleRowFlag(int tableID);

	//标题坐标位置
	void SetTitlePos(int tableID);

	int GetManualTitleInfo(int flag, int tableID);

	int FindBestColByTitle(PosOfChar& titlepos, int tableID);

	//拆分跨整列，添加相关列数据
	void SplitTableForWholeCol(int tableID);

	//合并跨行数据
	void MergeName();

	//数据处理完反推标题
	void SetTitlePosAgain();
	//老解析方式反算
	void GetDetailList();

	//拆分跨列、跨行
	void SplitTableByWholeRowCol(int tableID, int flag);
	void MergeTableByWholeRowCol(int tableID, int flag);

	int FindBestRowForTable(int tableID, string strText, string strPos, vector<PosOfChar>& charPos, string buf);

	int FindBestColForTable(int tableID, string strText, string strPos, vector<PosOfChar>& charPos, string buf);

	//根据标题坐标添加对应列的数据，对每列数据进行处理，合并、去重
	void SortColumn(int tableID, vector<RecogResult>& v_title_table2, vector<RecogResult>& v_price_table2, vector<RecogResult>& v_dj_table2, vector<RecogResult> & v_num_table2);

	//有标题-处理候选标题
	int SetTitlePosCand(int tableID);
	//无标题
	void SetTitlePosCand();

	void DrawVLineOnImage(PosOfChar& posChar, int type);
	void DrawGridOnImage(int type);

	bool IsSameLine2(RecogResult &r1, RecogResult &r2, float percent)
	{
		if (fabs(r1.Pos[1] + r1.Pos[3] / 2 - r2.Pos[1] - r2.Pos[3] / 2) < (r1.Pos[3] + r2.Pos[3]) * percent)
			return true;
		else
			return false;
	}
	void RecognizeRegion(vector<KeyWord> OutRecogResultList, vector<TitlePos> inTitlePos, int Pos[4]);
#endif

	float overlap(int titleid, int priceid);
	void VerifyEachColInfo();


	struct attribute
	{
		int sum;
		int average; //平均坐标
		int size;
		int dim;
	};
	void SortByKMeans(int dim);//
	void FindNoTableTitleFlag(const int dim, vector<int> &lableNum, vector<attribute> &attributeSet, int average);
	void FindNoTitlePos(vector<int> &lableNum, vector<attribute> &attributeSet, int titleFlag, int priceFlag, int djFlag);
	void GetNoTitlePos(vector<RecogResult>& titleRecoglList, int posTitle, int posPrice, int posDj);

	int FindDots(vector<RecogResult> &res);

	void JudgeTwoColumnByOverlap(int tableID);

	void MergeMultiColumn(const int tableID);//

	void MergeTitleCol(int tableID,int type); //正常表格，项目名称下面 一列识别成多列进行合并

	void VerifyTitleCol();//校验列信息

	int getK();
};

//pair<string, string> CExtractInfo::m_currentRes = pair<string, string>("", "");