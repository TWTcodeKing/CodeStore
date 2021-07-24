#ifndef _COMMON_
#define _COMMON_
#include <string>
#include <vector>

//#include <windows.h>
#include <map>

//#include "json\json.h"
#include "jasonsrc\json.h"
using namespace std;
#define WM_SHOWDROP (WM_USER + 101)
#define HLMarkOCXPath "C:\\HLMarkOCX"
#define TYPE_TITLE 0 //��������
#define TYPE_PRICE 1
#define TYPE_DJ 2 
#define TYPE_NUM 3

#define RW_OPERATOR(functionname, type, obj)\
protected:\
	type obj; \
public:\
	type& functionname(){ return obj; }\
	const type& functionname##C(){ return obj; }

#define PRW_OPERATOR(functionname, type, obj)\
protected:\
	type obj; \
public:\
	type functionname(){ return obj; }


enum ATTRIBUTETYPE{
	TYPE_EMPTY = 100,						//Ĭ��ͼ����ӿ�ֵ��ʱ���Ĭ��ͼ��
	TYPE_XY = 0, TYPE_XY_X, TYPE_XY_R_X,	//1.��ҩ��
	TYPE_ZY, TYPE_ZY_X, TYPE_ZY_R_X,		//2.�г�ҩ��
	TYPE_YP, TYPE_YP_X, TYPE_YP_R_X,		//3.��ҩ��Ƭ��
	TYPE_ZC, TYPE_ZC_X, TYPE_ZC_R_X,		//4.����
	TYPE_JC, TYPE_JC_X, TYPE_JC_R_X,		//5.����
	TYPE_ZL, TYPE_ZL_X, TYPE_ZL_R_X,		//6.���Ʒ�
	TYPE_SS, TYPE_SS_X, TYPE_SS_R_X,		//7.������
	TYPE_HY, TYPE_HY_X, TYPE_HY_R_X,		//8.�����
	TYPE_HL, TYPE_HL_X, TYPE_HL_R_X,		//9.�����
	TYPE_SY, TYPE_SY_X, TYPE_SY_R_X,		//10.������
	TYPE_SX, TYPE_SX_X, TYPE_SX_R_X,		//11.��Ѫ��
	TYPE_CW, TYPE_CW_X, TYPE_CW_R_X,		//12.��λ��
	TYPE_QT, TYPE_QT_X, TYPE_QT_R_X,		//13.������
	TYPE_CL, TYPE_CL_X, TYPE_CL_R_X,		//14.���Ϸ�
	TYPE_MZ, TYPE_MZ_X, TYPE_MZ_R_X,		//15.�����
	TYPE_ZJ, TYPE_ZJ_X, TYPE_ZJ_R_X 		//16.�����Ƽ�
};//�����������������Ե�����ͣ����羯������ش����
//������ұ������ǵ�

//int g_role = 0;
//int g_ImgWid, g_imgHei;
//int m_pagedownup = -1;
//vector<int> firstLoadFromFile;  //���ⲿ�����еõ���ע�������ʼ��Ϊ0�����غ���1

typedef struct _ImportantInfo{
	string unicodeID;//ΨһID
	string itemName;//��Ŀ����
	string expenseName;	//��������
	int expenseNameIndex;// �����������ڵ�����
	float expense;//����
	
	float expenseDeduction;	//�ۼ����
	string expenseCode; //���ô���
	string expenseType;	//�������
	int expenseTypeIndex;//�����������������޸����Ե�����ʱѡ�����Ե����Ҫ�������ԭ��������

	string originType;
	int originTypeIndex;//ԭʼ��������

	int expensePropertion; //�Էѱ���
//	int auditOptionIndex;//��������������
	float m_selExpense;//������
	string remark;//��ע
	string remarkrep;//�������
	int productionPlace;//�ε����� 0����,1����,2����
	int oldYearPayable;//�����֧��
	string photoBase64;//��Ƭ��base64ֵ
	string ocrRect;//����ʶ���Ĵ�Сֵ,����left,top,right,bottom,���Ÿ���

	string priceRect;//���ý��ʶ���Ĵ�Сֵleft, top, right, bottom���Ÿ���
	string capPic;//�������ƿ�ͼ��Ĵ�С
	
	//����Ӧ��ֻҪ����һ�ݵģ���Ϊͬһҳ�ĵ����ҳ����ת�Ƕȣ�ҳ�ķŴ�������һ����
	float rotate;	 //ҳ����ת�Ƕ�,�ֶ���ת
	float selfRotate;//�Զ���ת�Ƕ�
	float scaleNum;//ҳ�ķŴ���
	//int rotate90; //��ת90�ȵĴ���
	string itemRect1;//���������Լ���͸ߣ����Ÿ���
	string itemRect2;
	string priceRect1;
	string priceRect2;

	string DjRect1; //���۱�������
	string DjRect2;
	string NumRect1; //������������
	string NumRect2;


	string iteminfoRect; //��ϸ��������
	string priceinfoRect; //��ϸ�۸�����
	float ypsl; //����
	string numinfoRect; //��������
	float ypdj;//����
	string djinfoRect; //��������

	bool ischeck; //�Ƿ�ѡ��
	int titleId;
	struct _ImportantInfo()
	{
		expenseNameIndex = -1;
		expense = 0;
		ypsl = 0;
		ypdj = 0;
		expenseTypeIndex = -1;
		expensePropertion = 0;
		productionPlace = 0;
		oldYearPayable = -1;
		m_selExpense = 0;
		rotate = 0;
		scaleNum = 1;
		rotate = selfRotate ;
		originTypeIndex = -1;
		titleId = 0;
	}
	void clear()
	{
		originType = expenseType = expenseName = "";
		expenseNameIndex = -1;
		expenseTypeIndex = -1;
		oldYearPayable = -1;
		m_selExpense = 0;
		originTypeIndex = -1;
		expensePropertion = 0;
	}
}ImportantInfo, *PImportantInfo;

typedef struct _OWNEREXPENSEPROPORTY
{
	string number;
	float proporty;
	int isDeductible;
}OWNEREXPENSEPROPORTY, *POWNEREXPENSEPROPORTY;


class Drug
{
public:
	RW_OPERATOR(UniqueCoding, string, m_uniqueCoding)		//Ψһ����
		RW_OPERATOR(ExpenseType, string, m_expenseType)		//��������
		RW_OPERATOR(ExpenseTypeCode, string, m_expenseTypeCode)		//�������ʹ���
		RW_OPERATOR(ExpenseCode, string, m_expenseCode)		//���ô������
		RW_OPERATOR(ExpenseName, string, m_expenseName)		//���ô�������
		RW_OPERATOR(SelfExpense, float, m_selfExpense)		//Ĭ���Էѱ���
		RW_OPERATOR(oldYearPayable, bool, m_oldYearPayable) //����ɵֿ� false�ǲ��ɵֿۣ�true�ǿɵֿ�
		RW_OPERATOR(ProductPlace, int, m_productPlace)		//��������	0���ޣ�1�ǹ�����2�Ǻ��ʣ�3�ǽ���
};
#define  DRUG_MAP map<string, Drug>					//ҩƷΨһ�����ҩƷ��ӳ��
typedef struct _Invoice
{
	//�˵�
	string m_itemRect;	
	string m_priceRect;
	float m_xyf;		//��ҩ��
	string m_allXYF;
	string m_xyfRect;
	float m_zcyf;	//�г�ҩ��
	string m_allZCYF;
	string m_zcyfRect;
	float m_zyypf;	//��ҩ��Ƭ��
	string m_allZYYPF;
	string m_zyypfRect;
	float m_zcf;		//����
	string m_allZCF;
	string m_zcfRect;
	float m_jcf;		//����
	string m_allJCF;
	string m_jcfRect;
	float m_zlf;		//���Ʒ�
	string m_allZLF;
	string m_zlfRect;
	float m_ssf;		//������
	string m_allSSF;
	string m_ssfRect;
	float m_hyf;		//�����
	string m_allHYF;
	string m_hyfRect;
	float m_hlf;		//�����
	string m_allHLF;
	string m_hlfRect;
	float m_syf;		//������
	string m_allSYF;
	string m_syfRect;
	float m_sxf;		//��Ѫ��
	string m_allSXF;
	string m_sxfRect;
	float m_cwf;		//��λ��
	string m_allCWF;
	string m_cwfRect;
	float m_qtf;		//������
	string m_allQTF;
	string m_qtfRect;
	float m_clf;		//���Ϸ�
	string m_allCLF;
	string m_clfRect;
	float m_mzf;		//�����
	string m_allMZF;
	string m_mzfRect;
	float m_zzzj;	//�����Ƽ�
	string m_allZZZJF;
	string m_zzzjRect;
	float m_rotate; //��ת�Ƕ�
	
	string m_imageName;//��Ƭ����;
	int m_pageIndex; //����ҳ��
	struct _Invoice(){
		m_xyf = 0;		//��ҩ��
		m_zcyf = 0;	//�г�ҩ��
		m_zyypf = 0;	//��ҩ��Ƭ��
		m_zcf = 0;		//����
		m_jcf = 0;		//����
		m_zlf = 0;		//���Ʒ�
		m_ssf = 0;		//������
		m_hyf = 0;		//�����
		m_hlf = 0;		//�����
		m_syf = 0;		//������
		m_sxf = 0;		//��Ѫ��
		m_cwf = 0;		//��λ��
		m_qtf = 0;		//������
		m_clf = 0;		//���Ϸ�
		m_mzf = 0;		//�����
		m_zzzj = 0;	//�����Ƽ�
		m_rotate = 0; //��ת�Ƕ�
		m_imageName = "";//��Ƭ����
		m_pageIndex = 0; //����ҳ��
	}
	float getNum(int type)
	{
		switch (type)
		{
		case 1:
			return m_xyf;
		case 2:
			return m_zcyf;
		case 3:
			return m_zyypf;
		case 4:
			return m_zcf;
		case 5:
			return m_jcf;
		case 6:
			return m_zlf;
		case 7:
			return m_ssf;
		case 8:
			return m_hyf;
		case 9:
			return m_hlf;
		case 10:
			return m_syf;
		case 11:
			return m_sxf;
		case 12:
			return m_cwf;
		case 13:
			return m_clf;
		case 14:
			return m_mzf;
		case 15:
			return m_zzzj;
		case 16:
			return m_qtf;
		}
	}
	bool isNull()
	{
		return (m_xyf + m_zcyf + m_zyypf + m_zcf + m_jcf + m_zlf + m_ssf + m_hyf + m_hlf + m_syf + m_sxf + m_cwf + m_qtf + m_clf + m_mzf + m_zzzj) == 0;
	}
}Invoice, *PInvoice;


typedef struct FINALLIST_
{
	struct FINALLIST_(){ itemName = ""; price = "0.0"; type = -1;}
	string itemName;
	string price;
	int type;
	float resultRect[4];//���ϡ��ҡ���
	float baseResult[4];
}FINALLIST, *PFINALLIST;



/*
ҽ��Ʊ����Ϣ��ȡ

*/
class KeyWord
{
public:
	string Name;  //��Ŀ����
	string UnitPrice; //����
	string Number; //����
	string TotalPrice; //�ܼ�
	float Pos[16];  //������Ŀ���ڵ�λ��(Pos[0-3]--��Ŀ, Pos[4-7]--�ܼ�,Pos[8-11]--����, Pos[12-15]-����,���Ϊ-1�����������)
	vector<int> AdjIDOfName;  //���ƵĽ���ʶ��������	
	int titleId;//����id��˫�е�ʱ����ݱ��������õ�
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

	string getstringcode()
	{
		char str[100];
		memset(str, 0, 100);
		sprintf(str, "%d,%d,%d,%d", (int)pos[0], (int)pos[1], (int)(pos[0] + pos[2]), (int)(pos[1] + pos[3]));
		return string(str);
	}
		 
	int pos[4];
};

/*
"data": "ʵ�ս��",
"position" : "2091,99,2303,97,2303,141,2091,140"
*/
class RecogResult
{
public:
	string RResult; //ʶ����
	int orgID;
	float Pos[8]; //��ͼ���е�λ�á�Pos[0]��Pos[1]�����Ͻ�,  Pos[2]��Pos[3]����Ⱥ͸߶�   Pos[4]��Pos[5]�����½�  Pos[6]��Pos[7]�����½�
	vector<PosOfChar> charPos;
	int Flag;  //0:���� 1������ 2������, 3: �϶���ȷ�����֣��ܹ�ת��Ϊ���֣�����֮����ڼ����ϵ���������������ܺ͵���ǰ�����4: ��Ŀ 5������ 6����� 7������
	int IsMatched;  //�Ƿ��Ѿ���ƥ��
	int titleID;   //����ID

public:
	RecogResult &operator=(const RecogResult&p)
	{
		this->RResult = p.RResult;
		this->orgID = p.orgID;
		memcpy(Pos, p.Pos, sizeof(float)* 8);// this->RResult = p.RResult;
		this->charPos.assign(p.charPos.begin(), p.charPos.end());// = p.RResult;
		this->Flag = p.Flag;
		this->IsMatched = p.IsMatched;
		this->titleID = p.titleID;

		return *this;
	};


	//bool operator< (RecogResult& rec)//ע��Ƚϵ�˳��this�Ǳ��ȵĶ���
	//{/*
	//	if (this->Pos[1] < rec.Pos[1])
	//		return true;
	//	else
	//		return false;*/

	//	if (this->titleID != rec.titleID)
	//		return this->titleID < rec.titleID;
	//	else if (fabs(this->Pos[1] - rec.Pos[1])>5)
	//		return this->Pos[1] < rec.Pos[1];
	//	else
	//		return this->Pos[0] < rec.Pos[0];

	//	//return s1.titleID < s2.titleID;
	//};
	RecogResult(){ IsMatched = -1; };
};

inline bool operator<(const RecogResult& s1, const RecogResult& s2)

{
	if (s1.titleID != s2.titleID)
		return s1.titleID < s2.titleID;
	else if (fabs(s1.Pos[1] - s2.Pos[1])>5)
		return s1.Pos[1] < s2.Pos[1];
	else
		return s1.Pos[0] < s2.Pos[0];

}

//inline bool operator<(const RecogResult& s1, const RecogResult& s2)
//{
//	return s1.Pos[0] < s2.Pos[0]; //��С��������
//}
class TitlePos
{
public:
	/*TitlePos(){}

	TitlePos &operator=(const TitlePos & p)
	{
	memcpy(&NamePos, &p.NamePos, sizeof(int)* 4);
	memcpy(&PricePos, &p.PricePos, sizeof(int)* 4);
	return *this;
	}
	TitlePos(const TitlePos & p)
	{
	memcpy(&NamePos, &p.NamePos, sizeof(int)* 4);
	memcpy(&PricePos, &p.PricePos, sizeof(int)* 4);
	}*/
	PosOfChar NamePos;
	PosOfChar PricePos;
	PosOfChar NumPos;
	PosOfChar DjPos;
	TitlePos &operator=(const TitlePos & p)
	{
		this->NamePos = p.NamePos;
		this->PricePos = p.PricePos;
		this->NumPos = p.NumPos;
		this->DjPos = p.DjPos;
		//memcpy(&PricePos, &p.PricePos, sizeof(int)* 4);
		return *this;
	}
	int PageID;
};
//vector<TitlePos> g_titlePos;
typedef struct PAGESAVEOCRINFO_
{
	vector<FINALLIST> ocrResult;
	int flag;
	RecogResult item; //����Ƿ���������λ��
	RecogResult price;//����ǽ�����λ��
	bool isOptimizeImg;//�Ƿ��Ż���ͼƬ
}PAGESAVEOCRINFO, *PPAGESAVEOCRINFO;

typedef struct ITEMINFO_
{
	PosOfChar itemPos;	//����������Ŀ��������
	PosOfChar pricePos; //���������۸�����
	float leftPos;
	float topPos;

}ITEMINFO, *PITEMINFO;


typedef struct  _SHORTCUTTYPE
{
	int code;//��ݼ���Ӧ���� 101 XY ��ҩ , 201 CXY����������ҩ(�Էѱ���Ϊ3��
	int type;//���Ƽ����� Ctrl Shift Alt(1,2,3)
	int shortcurt;//���ܼ���ֵ
	bool bUseShortcut;//�Ƿ����ÿ�ݼ�
	struct _SHORTCUTTYPE()
	{
		code = -1;
		type = -1;
		shortcurt = -1;
		bUseShortcut = false;
	}
}SHORTCUTTYPE;//��ݼ�����
#endif