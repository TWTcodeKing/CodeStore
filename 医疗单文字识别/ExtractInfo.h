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
ҽ��Ʊ����Ϣ��ȡ

*/
#define TYPE_TITLE 0
#define TYPE_PRICE 1
#define TYPE_CANPRICE 111  //���Ǽ۸�ĺ�ѡ��
#define TYPE_DJ 2 
#define TYPE_NUM 3
/*
//#define AUTO_MODIFY_NAME
class KeyWord
{
public:
string Name;  //��Ŀ����
string UnitPrice; //����
string Number; //����
string TotalPrice; //�ܼ�
float Pos[16];  //������Ŀ���ڵ�λ��(Pos[0-3]--��Ŀ, Pos[4-7]--�ܼ�,Pos[8-11]--����, Pos[12-15]-����,���Ϊ-1�����������)
vector<int> AdjIDOfName;  //���ƵĽ���ʶ��������

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
int  ID;  //��Ŀ
int  MatchedID; //���
int UnitPriceID; //����
float fPriceRate[2];  //���ۺ���Ŀ�����ı���
int NumID; //����
int flag;  //flag=0;  ��Ŀ�ͽ�����
};

class TitleKeyWord
{
public:
string Name;  //��Ŀ����
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
"data": "ʵ�ս��",
"position" : "2091,99,2303,97,2303,141,2091,140"

class RecogResult
{
public:
string RResult; //ʶ����
int orgID;
float Pos[8]; //��ͼ���е�λ�á�Pos[0]��Pos[1]�����Ͻ�  Pos[2]��Pos[3]�����Ͻ�  Pos[4]��Pos[5]�����½�  Pos[6]��Pos[7]�����½�
vector<PosOfChar> charPos;
int Flag;  //0:���� 1������ 2������, 3: �϶���ȷ�����֣��ܹ�ת��Ϊ���֣�����֮����ڼ����ϵ���������������ܺ͵���ǰ�����4: ��Ŀ 5������ 6����� 7������
int IsMatched;  //�Ƿ��Ѿ���ƥ��
#ifndef AUTO_RECOG_TITLE
int titleID;
#endif
public:
RecogResult(){ IsMatched = -1; };
};

inline bool operator<(const RecogResult& s1, const RecogResult& s2)
{
return s1.Pos[0] < s2.Pos[0]; //��С��������
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
	string Name;  //��Ŀ����
	int start_row;
	int start_column;
	int end_row;
	int end_column;
	int row_flag;
	int column_flag;
	int flag; //4��5��6��7����
	int merge[5];//�Ƿ�ϲ����ϲ�֮����ʼ�У���ֹ�У���ʼ�У���ֹ��
	float Pos[8];//�������
	float charPos[4];  //ÿ���ַ�����λ��
};

class ElemOfTable
{
public:
	int position[8];  //����ĸ�����λ�ã����ϣ����ϣ����£����£�
	int rowColumn[4]; //��ʼ���С���ֹ����
	string strText;
	vector<PosOfChar> charPos;  //ÿ���ַ���ռλ��
	vector<vector<PosOfChar>> allCharPos;//�����ַ�
	vector<string> allStrText;
	vector<vector<string>> CandChar; //ÿ���ַ���Ӧ�ĺ�ѡ�ַ�
	int isMatched;

public:
	ElemOfTable()
	{
		isMatched = 0;
	}
	ElemOfTable(const ElemOfTable& a2)//�������캯��
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


//�ޱ���ʱ����ͳ��ÿ������
class EachColumnInfo
{
public:
	int Column;//������
	int ChineseNumber; //����
	int number; //��������
	int dotNumber; //С����
	double num; //����
	int dateNum;//���ڸ���
	int percentNum;//�ٷֺŸ���
};

class TableInfo
{
public:
	vector<vector<ElemOfTable>> MatrixTable;  //Ԫ�ؾ���
	int TitleCol[4];  //TitleCol[0]: ��Ŀ���Ƶ���������TitleCol[1]: ���۵���������TitleCol[2]: ��������������TitleCol[3]:�ܼ۵���������
	vector<int> ColWid;  //ÿ����ռ���
	vector<int> RowHei;  //ÿ����ռ�߶�
	vector<EachColumnInfo> eachColumnInfoSet;  //����ͳ�ư������ġ����ֵ�
	vector<int> colSetForTitle;  //�ҵ��ĺ�ѡ��Ŀ������
	vector<int> colSetForPrice;  //�ҵ��ĺ�ѡ�ܼ���
	vector<int> colSetForDj;  //�ҵ��ĺ�ѡ��Ŀ������
	vector<int> colSetForNum;  //�ҵ��ĺ�ѡ�ܼ���
	vector<int> colSetForRow;  //��ѡ��

	vector<int> rowSetForTitle;  //�ҵ��ĺ�ѡ��Ŀ������
	vector<int> rowSetForPrice;  //�ҵ��ĺ�ѡ�ܼ���
	vector<int> rowSetForDj;  //�ҵ��ĺ�ѡ��Ŀ������
	vector<int> rowSetForNum;  //�ҵ��ĺ�ѡ�ܼ���

	int existTitle;//Ĭ���б���
	int Row;  //���������������-1,������ӵ�һ�п�ʼȡ���ݣ�
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
				tableNew.MatrixTable[i][j] = MatrixTable[i][j + splitCol];   //ElemOfTable��Ҫ����=��				
			}
			//ɾ���ⲿ������
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
					tableNew.MatrixTable[i][j] = MatrixTable[i][j + splitCol];   //ElemOfTable��Ҫ����=��				
				}
				//ɾ���ⲿ������
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
					tableNew.MatrixTable[i][j] = MatrixTable[i][j + splitCol];   //ElemOfTable��Ҫ����=��				
				}
				//ɾ���ⲿ������
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
	vector<RecogResult> RecoglList;  //ȥ���˲�����Чʶ����
	vector<RecogResult> OrgRecoglList;  //ԭʼʶ����

	vector<KeyWord> FinalList;  //���յõ�����ϸ
	vector<TitleKeyWord> TitleSet;  //���ڶ�λ����Ĺؼ���
	vector<MappedID>  mappedSet;  ///ƥ��Լ���

	vector<string>  splitedStr;  ///ƥ��Լ���


	int aveYPosOfTitle;  //�������ڵ�Yƽ������
	int NumofTitle;

	Mat InputImage;  //����ͼ��
	Mat TempImage;

	String openedfile;
	String openeddir;


	/*
	��ȡ��Ϣ��ں���
	���룺
	1. OCRʶ����������JASON�ṹ��ʾ���ַ���
	2. RGBImageʶ������Ӧ��ͼ��
	�����
	1. ʶ����ϸ������JASON�ṹ��ʾ���ַ���
	2. ��Ŀ����
	*/
	int ExtractInfo(char *ListDetail, unsigned char *RGBImage, int imageWidth, int imageHeight);
	string ExtractInfo(char *ColorImage, const char *IPAddress, const char *ObjFun, int Port/*,  vector<TitlePos>& v_titlePos*/);

	//��λ�����Ŀ
	int LocalName();

	//�ж�ʶ��������,�������������ڽ�ȡʶ��ı���������õ�����ԭ�ַ����е���ʼ��ֹ�ַ�����
	int CheckRecogType(string strRecog, int &, int &);

	//�����ҵ�����Ŀ�ͽ��
	int DecodeByNameAndTotal(int NameID, int TotalID, int curMapID);

	//�ҵ��·�������
	int FindNearBottom(int OrgID);

	//�ҵ��Ҳ�������
	int FindNearRight(int OrgID, int& IsDot);

	//�ҵ����������
	int FindNearLeft(int OrgID, int& IsDot);

	//���ҵ��Ľ���н��к�������
	int PostTotalPrice(int curID);

	int OutputImage(char *outputfile, int drawtitle = 0, int drawdetail = 0);

	int PostProcTotalPrice(string& input, string& output);

	//�ж���һ���Ƿ���Ч
	int IsValidElem(int nameID, int priceID);
	int IsValidElem(string str);
	//�ҵ�����ƥ�䵥��
	int FindMatchedUnitPrice(int nameID, int priceID, int mapID);

	//����ɨ�����ҳ���ʧ��
	void ResearchLoseItem();
	void ResearchLostItemByPrice();
	void ResearchLostItemByName();
	/*ȡ������*/
	int getItemPos(RecogResult& itemName, RecogResult& itemPrice);

	//��ȡ������ϸ
	const vector<KeyWord>& getFinalList(){ return FinalList; }

	void ImgRotate(Mat& src, Mat& dst, double angle);
public:
	//
	void DecodeOneImage(char *imgename, const char *IPAddress, const char *ObjFun, int Port, int type);

	int IsGoodPair(int LastID, int ID, int MatchedLastID, int MatchedID);

	//�õ�ƥ�����Ŀ�ͽ��ID
	int GetMatchedNameAndTotal();

	//�õ�������Ľ��ڼ���ID
	int GetAdjIDofName(int CurID);

	//�Ƿ�����Ч��������
	int IsValidName();

	//�Ƿ�����Ч������
	int IsValidData(string strText);
	int IsValidNumber();
	//�Ƿ��������
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

	//�ҵ��з��ַ���ǰ��λ��
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
	void SplitTitle(RecogResult &, int, int);//�зֱ���

	int PushRecogResult2(string strText, string strPos, vector<PosOfChar>& charPos);
	void SubString(vector<RecogResult> &subEle, RecogResult ele);//���ݱ���λ�ý����з�
	int SplitRegions2(vector<RecogResult>& FinalelemSet, RecogResult elem, int type, int);//�зֺ�Ľ��������FinalelemSet��
	int TranFound2(int found, string strInfo);//�����ַ�λ�����ַ�����ʵ��λ�ã�С-����
	void MatchResult();//���յĽ��ƥ��
	int isSameLineByTitle(const RecogResult &, const RecogResult &);//���ձ���λ�õ���Ծ������ж��Ƿ���ͬһ��
	void DrawLine(const RecogResult &, const RecogResult &);//��������֮����ƺ���
	void addToFinalList(const RecogResult &, const RecogResult &);//��ӵ������

#if defined(_WIN32)
	string ExtractInfo(cv::Mat ocrImg, const char *IPAddress, const char *ObjFun, int Port/*, vector<TitlePos>& v_titlePos*/);
	void DecodeOneImage(cv::Mat ocrImg, const  char *IPAddress, const char *ObjFun, int Port, int type);//type=1���汾1��type=2 ���汾2
#endif

private:
	vector<RecogResult> v_title;//������ƥ��ı�����
	vector<RecogResult> v_price;//������ƥ��Ľ����
	vector<RecogResult> v_dj;//������ƥ��ĵ��۽��
	vector<RecogResult> v_num;//������ƥ����������

	vector<RecogResult> v_title_table;//������ƥ��ı�����
	vector<RecogResult> v_price_table;//������ƥ��Ľ����
	vector<RecogResult> v_dj_table;//������ƥ��ĵ��۽��
	vector<RecogResult> v_num_table;//������ƥ����������

	vector<vector<RecogResult>> v_title_table_set;
	vector<vector<RecogResult>> v_price_table_set;
	vector<vector<RecogResult>> v_dj_table_set;
	vector<vector<RecogResult>> v_num_table_set;


public:

	void AutoGetNamePricePos();//�Զ���ȡ����λ��
	void findAdjacent(int curId, int &leftId, int &rightId);//����curId�ҵ���ͬ�е����������Id��δ�ҵ�����-1
	void findPosX(const cv::Mat&, int id, int &leftX, int &rightX);
	cv::Mat srcImg;

	void HandleLongPrice(RecogResult &priceEle);
	static bool traitNumber(string & price);//
	static bool traitNumber(string & price, int type);//С����λ��
	static string formatNumber(string s, int);//��ʽ������
	static void replace_all(string& str, const string& old_value, const string& new_value);
	static void replaceInvalidCharater(string & str);//�滻��Ч�ַ�

	void ReFindTitleWithSingleCharater();//���ڱ���δʶ�������������������������ر�Զ��
	int FindNextBlackPt(const cv::Mat&, int x, int y, int direction);//��x��������������ҵ���һ����ɫ�ĵ�
	void PostTitlePos(char *ColorImage, const char *IPAddress, const char *ObjFun, int Port);//�������ʶ������۸�ʶ�������϶࣬���п��ܱ���λ�ò��ԣ�����������
	bool IsSameLine(RecogResult r1, RecogResult r2);
	//	bool isNeedSplit(const RecogResult &);//���ڱ�����ʶ���пո�ģ����з�
	//vector<RecogResult>m_titleName, m_priceName;

	//�����������
	static void AnsiToUTF8(string &str);
	static void UTF8ToAnsi(string& strUTF8);
	static int callback(void *data, int argc, char **argv, char **azColName);
	void ModifyNameFromSqlite(string &);

	//�ⲿ����ȫ��ʶ����
	void SetFullRecogJsonStr(const string &str){ m_strRecogJson = str; }

	//	sqlite3 *m_pDB;
public:
	int GetOcrVersion();
	string m_strRecogJson = "";

	//��ʶ����ת����jason�ַ���
	string makeBillJson();

	string filename;

	//�������ƺͽ��ʶ�𵥼ۺ��������ڱ���λ��
	/*
	���룺
	�����
	1���ҵ����ۺ�����λ��
	-1���Ҳ������ۺ�����λ��
	*/
	int RecognizePriceAndNumber(RecogResult& UnitPircPos, RecogResult& NumberPos,
		RecogResult& TitlePos, RecogResult& TotalPricePos);

	//���ݵ��ۺ���������õ���������
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

	//���Զ���λ�õ��ı��������������
	void  RefineAutoTitle();

	//�зֵ��ۺͽ��
	int SplitTitleRegions(vector<RecogResult>& FinalelemSet, RecogResult elem);

	//�Ա��������кϲ�����
	int MergeTitle();

	string PointToSting(int point[]);

	//��ȡ������ϸ
	const map<string, string>& GetMarkPos(){
		return m_MarkedPosMap;
	}

	cv::Rect PosToTect(PosOfChar& titlpos);
	cv::Rect ArrayToTect(float *titlpos);

	//���������м��пո�ģ��������������ƴ�ӣ�
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
	map<string, string> m_MarkedPosMap; //��¼�������ģ������
	map<string, string> m_filemarkpos; //��ȡ�����ļ���ģ������

	vector<RecogResult> CandTitleList;  //���ڲ��ֿ��ܵı��������ȴ洢�������������ϲ�����


	void GetDetailListTable();
	//����һ������ҽԺ�������ӽ���׼ȷ�ʵĴ���
	int ProcessForSpecialHos();

	int ProcessForYuYaoHos();

	int m_nPriceCount;

	int isManual = -1;

	vector<HosElem> HospitalSet;  //����ҽԺ����

	vector<TableInfo> TableSet;

	int HospitalID;//0: �人��ѧ����ҽԺ

	int CorrlastI;  //�ϴ�ƥ��ɹ��Ľ������
	int CorrlastJ;

	int GetRecogedTable();

	//�ޱ��
	int DecodeRecogedTable(int type);

	int DetectColFlagOfTable();

	//�ڶ��ν�������ֱ�񣬽����������
	int DecodeTableAgain();

	//������ȷ�����У����ÿ������
	int GetTableColumn(int tableID);

	//���ִ�������
	void JudgeRowTableType();

	//����ȱ�ٵ��ۻ�����������
	void GetNumDj();

	int JudgeTwoColumn(int tableID);

	int JudgeTwoColumnWithoutTitle(int tableID);

	//ͳ��ÿ�е����ġ����������Ϣ
	void CountColInfo(vector<EachColumnInfo>& eachColumnInfoSet, int tableID);

	//���ұ���������
	void FindTitleRowFlag(int tableID);

	//��������λ��
	void SetTitlePos(int tableID);

	int GetManualTitleInfo(int flag, int tableID);

	int FindBestColByTitle(PosOfChar& titlepos, int tableID);

	//��ֿ����У�������������
	void SplitTableForWholeCol(int tableID);

	//�ϲ���������
	void MergeName();

	//���ݴ����귴�Ʊ���
	void SetTitlePosAgain();
	//�Ͻ�����ʽ����
	void GetDetailList();

	//��ֿ��С�����
	void SplitTableByWholeRowCol(int tableID, int flag);
	void MergeTableByWholeRowCol(int tableID, int flag);

	int FindBestRowForTable(int tableID, string strText, string strPos, vector<PosOfChar>& charPos, string buf);

	int FindBestColForTable(int tableID, string strText, string strPos, vector<PosOfChar>& charPos, string buf);

	//���ݱ���������Ӷ�Ӧ�е����ݣ���ÿ�����ݽ��д����ϲ���ȥ��
	void SortColumn(int tableID, vector<RecogResult>& v_title_table2, vector<RecogResult>& v_price_table2, vector<RecogResult>& v_dj_table2, vector<RecogResult> & v_num_table2);

	//�б���-�����ѡ����
	int SetTitlePosCand(int tableID);
	//�ޱ���
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
		int average; //ƽ������
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

	void MergeTitleCol(int tableID,int type); //���������Ŀ�������� һ��ʶ��ɶ��н��кϲ�

	void VerifyTitleCol();//У������Ϣ

	int getK();
};

//pair<string, string> CExtractInfo::m_currentRes = pair<string, string>("", "");