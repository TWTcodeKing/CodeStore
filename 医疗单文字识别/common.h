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
#define TYPE_TITLE 0 //标题类型
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
	TYPE_EMPTY = 100,						//默认图标添加空值得时候的默认图标
	TYPE_XY = 0, TYPE_XY_X, TYPE_XY_R_X,	//1.西药费
	TYPE_ZY, TYPE_ZY_X, TYPE_ZY_R_X,		//2.中成药费
	TYPE_YP, TYPE_YP_X, TYPE_YP_R_X,		//3.中药饮片费
	TYPE_ZC, TYPE_ZC_X, TYPE_ZC_R_X,		//4.诊查费
	TYPE_JC, TYPE_JC_X, TYPE_JC_R_X,		//5.检查费
	TYPE_ZL, TYPE_ZL_X, TYPE_ZL_R_X,		//6.治疗费
	TYPE_SS, TYPE_SS_X, TYPE_SS_R_X,		//7.手术费
	TYPE_HY, TYPE_HY_X, TYPE_HY_R_X,		//8.化验费
	TYPE_HL, TYPE_HL_X, TYPE_HL_R_X,		//9.护理费
	TYPE_SY, TYPE_SY_X, TYPE_SY_R_X,		//10.输氧费
	TYPE_SX, TYPE_SX_X, TYPE_SX_R_X,		//11.输血费
	TYPE_CW, TYPE_CW_X, TYPE_CW_R_X,		//12.床位费
	TYPE_QT, TYPE_QT_X, TYPE_QT_R_X,		//13.其他费
	TYPE_CL, TYPE_CL_X, TYPE_CL_R_X,		//14.材料费
	TYPE_MZ, TYPE_MZ_X, TYPE_MZ_R_X,		//15.麻醉费
	TYPE_ZJ, TYPE_ZJ_X, TYPE_ZJ_R_X 		//16.自制制剂
};//这个可以用来标记属性点的类型，比如警告或者重大错误
//代表甲乙丙三类标记点

//int g_role = 0;
//int g_ImgWid, g_imgHei;
//int m_pagedownup = -1;
//vector<int> firstLoadFromFile;  //从外部数据中得到标注结果，初始化为0，加载后变成1

typedef struct _ImportantInfo{
	string unicodeID;//唯一ID
	string itemName;//项目名称
	string expenseName;	//费用名称
	int expenseNameIndex;// 费用名称所在的索引
	float expense;//费用
	
	float expenseDeduction;	//扣减金额
	string expenseCode; //费用代码
	string expenseType;	//费用类别
	int expenseTypeIndex;//费用类别的索引，当修改属性点属性时选中属性点就需要这个来还原他的属性

	string originType;
	int originTypeIndex;//原始类别的索引

	int expensePropertion; //自费比例
//	int auditOptionIndex;//审核意见所在索引
	float m_selExpense;//自理金额
	string remark;//备注
	string remarkrep;//复审意见
	int productionPlace;//参地性质 0国产,1合资,2进口
	int oldYearPayable;//历年可支付
	string photoBase64;//照片的base64值
	string ocrRect;//整体识别框的大小值,坐标left,top,right,bottom,逗号隔开

	string priceRect;//费用金额识别框的大小值left, top, right, bottom逗号隔开
	string capPic;//费用名称抠图框的大小
	
	//下面应该只要保存一份的，因为同一页的点对于页的旋转角度，页的放大倍数都是一样的
	float rotate;	 //页码旋转角度,手动旋转
	float selfRotate;//自动旋转角度
	float scaleNum;//页的放大倍数
	//int rotate90; //旋转90度的次数
	string itemRect1;//左上坐标以及宽和高，逗号隔开
	string itemRect2;
	string priceRect1;
	string priceRect2;

	string DjRect1; //单价标题坐标
	string DjRect2;
	string NumRect1; //数量标题坐标
	string NumRect2;


	string iteminfoRect; //明细名称坐标
	string priceinfoRect; //明细价格坐标
	float ypsl; //数量
	string numinfoRect; //数量坐标
	float ypdj;//单价
	string djinfoRect; //单价坐标

	bool ischeck; //是否选中
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
	RW_OPERATOR(UniqueCoding, string, m_uniqueCoding)		//唯一编码
		RW_OPERATOR(ExpenseType, string, m_expenseType)		//费用类型
		RW_OPERATOR(ExpenseTypeCode, string, m_expenseTypeCode)		//费用类型代码
		RW_OPERATOR(ExpenseCode, string, m_expenseCode)		//费用大类代码
		RW_OPERATOR(ExpenseName, string, m_expenseName)		//费用大类名称
		RW_OPERATOR(SelfExpense, float, m_selfExpense)		//默认自费比例
		RW_OPERATOR(oldYearPayable, bool, m_oldYearPayable) //历年可抵扣 false是不可抵扣，true是可抵扣
		RW_OPERATOR(ProductPlace, int, m_productPlace)		//产地名称	0是无，1是国产，2是合资，3是进口
};
#define  DRUG_MAP map<string, Drug>					//药品唯一编码和药品的映射
typedef struct _Invoice
{
	//账单
	string m_itemRect;	
	string m_priceRect;
	float m_xyf;		//西药费
	string m_allXYF;
	string m_xyfRect;
	float m_zcyf;	//中成药费
	string m_allZCYF;
	string m_zcyfRect;
	float m_zyypf;	//中药饮片费
	string m_allZYYPF;
	string m_zyypfRect;
	float m_zcf;		//诊察费
	string m_allZCF;
	string m_zcfRect;
	float m_jcf;		//检查费
	string m_allJCF;
	string m_jcfRect;
	float m_zlf;		//治疗费
	string m_allZLF;
	string m_zlfRect;
	float m_ssf;		//手术费
	string m_allSSF;
	string m_ssfRect;
	float m_hyf;		//化验费
	string m_allHYF;
	string m_hyfRect;
	float m_hlf;		//护理费
	string m_allHLF;
	string m_hlfRect;
	float m_syf;		//输氧费
	string m_allSYF;
	string m_syfRect;
	float m_sxf;		//输血费
	string m_allSXF;
	string m_sxfRect;
	float m_cwf;		//床位费
	string m_allCWF;
	string m_cwfRect;
	float m_qtf;		//其他费
	string m_allQTF;
	string m_qtfRect;
	float m_clf;		//材料费
	string m_allCLF;
	string m_clfRect;
	float m_mzf;		//麻醉费
	string m_allMZF;
	string m_mzfRect;
	float m_zzzj;	//自制制剂
	string m_allZZZJF;
	string m_zzzjRect;
	float m_rotate; //旋转角度
	
	string m_imageName;//照片名称;
	int m_pageIndex; //所在页码
	struct _Invoice(){
		m_xyf = 0;		//西药费
		m_zcyf = 0;	//中成药费
		m_zyypf = 0;	//中药饮片费
		m_zcf = 0;		//诊察费
		m_jcf = 0;		//检查费
		m_zlf = 0;		//治疗费
		m_ssf = 0;		//手术费
		m_hyf = 0;		//化验费
		m_hlf = 0;		//护理费
		m_syf = 0;		//输氧费
		m_sxf = 0;		//输血费
		m_cwf = 0;		//床位费
		m_qtf = 0;		//其他费
		m_clf = 0;		//材料费
		m_mzf = 0;		//麻醉费
		m_zzzj = 0;	//自制制剂
		m_rotate = 0; //旋转角度
		m_imageName = "";//照片名称
		m_pageIndex = 0; //所在页码
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
	float resultRect[4];//左、上、右、下
	float baseResult[4];
}FINALLIST, *PFINALLIST;



/*
医疗票据信息提取

*/
class KeyWord
{
public:
	string Name;  //项目名称
	string UnitPrice; //单价
	string Number; //数量
	string TotalPrice; //总价
	float Pos[16];  //各个项目所在的位置(Pos[0-3]--项目, Pos[4-7]--总价,Pos[8-11]--单价, Pos[12-15]-数量,如果为-1则表明不存在)
	vector<int> AdjIDOfName;  //名称的近邻识别结果（）	
	int titleId;//标题id，双列的时候根据标题排序用到
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
"data": "实收金额",
"position" : "2091,99,2303,97,2303,141,2091,140"
*/
class RecogResult
{
public:
	string RResult; //识别结果
	int orgID;
	float Pos[8]; //在图像中的位置。Pos[0]，Pos[1]：左上角,  Pos[2]，Pos[3]：宽度和高度   Pos[4]，Pos[5]：左下角  Pos[6]，Pos[7]：右下角
	vector<PosOfChar> charPos;
	int Flag;  //0:待定 1：中文 2：数字, 3: 肯定正确的数字（能够转化为数字，几列之间存在计算关系：出现相等项，出现总和等于前两列项）4: 项目 5：单价 6：金额 7：数量
	int IsMatched;  //是否已经被匹配
	int titleID;   //标题ID

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


	//bool operator< (RecogResult& rec)//注意比较的顺序。this是被比的对象。
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
//	return s1.Pos[0] < s2.Pos[0]; //从小到大排序
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
	RecogResult item; //这个是费用类别标题位置
	RecogResult price;//这个是金额标题位置
	bool isOptimizeImg;//是否优化过图片
}PAGESAVEOCRINFO, *PPAGESAVEOCRINFO;

typedef struct ITEMINFO_
{
	PosOfChar itemPos;	//标题名，项目名称坐标
	PosOfChar pricePos; //标题名，价格坐标
	float leftPos;
	float topPos;

}ITEMINFO, *PITEMINFO;


typedef struct  _SHORTCUTTYPE
{
	int code;//快捷键对应类型 101 XY 西药 , 201 CXY工具栏中西药(自费比例为3）
	int type;//控制键类型 Ctrl Shift Alt(1,2,3)
	int shortcurt;//功能键键值
	bool bUseShortcut;//是否启用快捷键
	struct _SHORTCUTTYPE()
	{
		code = -1;
		type = -1;
		shortcurt = -1;
		bUseShortcut = false;
	}
}SHORTCUTTYPE;//快捷键类型
#endif