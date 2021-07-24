#include "StringOperator.h"
#include <Windows.h>
#include <iostream>
#include <sstream>  
#include <tchar.h>

using namespace std;
CStringOperator::CStringOperator(void)
{
}

CStringOperator::~CStringOperator(void)
{
}

bool CStringOperator::string2int(const std::string& string_key, int& int_key)
{
	char* str = new char[string_key.length() + 1];
	strcpy_s(str, string_key.length() + 1, string_key.c_str());
	char*p = str;
	int_key = 0;
	bool plus_minus = true;//正数还是负数
	while(*p != '\0')
	{
		if(*p == '-' && p ==str)
		{
			p++;
			plus_minus = false;
			continue;
		}
		if((*p - '0') > 9 || (*p - '0') < 0)
		{
			delete[] str;
			return false;
		}
		int_key *= 10;
		int_key += *p - '0';
		p++;
	}
	int_key *= plus_minus?1:-1;
	delete[] str;
	return true;
}
bool CStringOperator::int2string(const int& int_key, string& string_key)
{
	char str_in[1024] = { 0 };
	sprintf_s(str_in, "%d", int_key);
	string_key = string(str_in);
	return true;
}
string CStringOperator::int2string(const int& int_key)
{
	string string_key;
	char str_in[1024] = { 0 };
	sprintf_s(str_in, "%d", int_key);
	string_key = string(str_in);
	return string_key;
}
bool CStringOperator::double2string(const double& int_key, string& string_key)
{
	char str_in[1024] = { 0 };
	sprintf_s(str_in, "%.2f", int_key);
	string_key = string(str_in);
	return true;
}

//unsigned long 转换成string
bool CStringOperator::unsignedlong2string(const unsigned long& long_key, string& string_key)
{
	char str_in[1024] = { 0 };
	sprintf_s(str_in, "%u", long_key);
	string_key = string(str_in);
	return true;
}
bool CStringOperator::string2double(const std::string& string_key, double& float_key)
{
	char* str = new char[string_key.length() + 1];
	strcpy_s(str, string_key.length() + 1, string_key.c_str());
	char*p = str;
	char*q = str + string_key.length();
	bool plus_minus = true;//正数还是负数
	bool point_flag = false;//小数点前面还是后面
	float_key = 0.0f;
	double plus = 0.0f;//整数位
	double minus = 0.0f; //小数值
	double minus_count =1.0f; //小数位
	while(*p != '\0')
	{
		if(*p == '-' && p ==str)
		{
			p++;
			plus_minus = false;
			continue;
		}
		if(*p == '.')
		{
			if(point_flag)
			{
				//表示前面已经读到小数点了，再有就说明出错了
				delete[] str;
				return false;
			}
			else
			{
				point_flag = true;
				p++;
				continue;
			}
			
		}
		if((*p - '0') > 9 || (*p - '0') < 0)
		{
			delete[] str;
			return false;
		}
		if(point_flag)
		{
			//小数位相加;
			minus_count *= 0.1;
			minus *= 10;
			minus += *p - '0';
		}
		else
		{
			//整数位相加
			plus *= 10;
			plus += *p - '0';
		}
		p++;
	}
	minus *= minus_count;
	float_key = plus + minus;
	float_key *= plus_minus?1:-1;
	delete[] str;
	return true;
}

///将字串首尾两端的空格移除
void CStringOperator::Trim(string & str)
{
	if (str.empty()) {
		return;
	}
	string::size_type i, start_pos, end_pos;
	for (i = 0; i < str.size(); ++i) {
		if (!IsSpace(str[i])) {
			break;
		}
	}
	if (i == str.size()) { // 全部是空白字符串
		str = "";
		return;
	}

	start_pos = i;

	for (i = str.size() - 1; i >= 0; --i) {
		if (!IsSpace(str[i])) {
			break;
		}
	}
	end_pos = i;

	str = str.substr(start_pos, end_pos - start_pos + 1);
}
bool CStringOperator::IsSpace(char c)
{
	if (' ' == c || '\t' == c)
		return true;
	return false;
}

//去掉字符串两端给定字符
void CStringOperator::Trim(string& str, const char& limit_str)
{
	if (str.empty()) {
		return;
	}
	string::size_type i, start_pos, end_pos;
	for (i = 0; i < str.size(); ++i) {
		if (!IsLimit(str[i], limit_str)) {
			break;
		}
	}
	if (i == str.size()) { // 全部是给定字符串
		str = "";
		return;
	}

	start_pos = i;

	for (i = str.size() - 1; i >= 0; --i) {
		if (!IsLimit(str[i], limit_str)) {
			break;
		}
	}
	end_pos = i;

	str = str.substr(start_pos, end_pos - start_pos + 1);
}

void CStringOperator::Trim(char* str, int& len, const char&limit_str)
{
	if (str == NULL)
		return;
	string std_str = str;
	CStringOperator::Trim(std_str, limit_str);
	len = std_str.length() + 1;
	sprintf_s(str, len, "%s", std_str.c_str());
}

bool CStringOperator::IsLimit(const char& c, const char& limit)
{
	if (limit == c )
		return true;
	return false;
}
void CStringOperator::LeftOutStr(string& src_str, const string& limit_str)
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

void CStringOperator::splite(const string& key_str, const string& split_flag, vector<string>& value_vec)
{
	string::iterator citr;
	int pre_ret = 0;
	int ret = key_str.find(split_flag, 0);
	if(ret == string::npos)
	{
		value_vec.push_back(key_str);
		return;
	}
	while(ret != string::npos)
	{
		string str = key_str.substr(pre_ret, ret - pre_ret);
		pre_ret = ret + split_flag.size();
		value_vec.push_back(str);
		ret = key_str.find(split_flag, pre_ret+1);
	}
	string str = key_str.substr(pre_ret, ret - pre_ret); 
	value_vec.push_back(str);
	int a = 0;
}


wstring CStringOperator::UTF8ToUnicode(const string& str)
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t *  pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	wstring  rt;
	rt = (wchar_t*)pUnicode;
	delete  pUnicode;

	return  rt;
}

string CStringOperator::UnicodeToUTF8(const wstring& str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char)* (iTextLen + 1));
	::WideCharToMultiByte(CP_UTF8,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

wstring CStringOperator::ANSIToUnicode(const string& str)
{
	int len = 0;
	len = str.length();
	int unicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t * pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	wstring rt;
	rt = (wchar_t*)pUnicode;
	delete pUnicode;
	return rt;
}


string CStringOperator::UnicodeToANSI(const wstring& str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char)* (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}


char* CStringOperator::wChar2char(wchar_t* in_str)
{
	//计算需要多少个字节才能表示对应的多字节字符串  
	DWORD num = WideCharToMultiByte(CP_ACP, 0, in_str, -1, NULL, 0, NULL, 0);

	//开辟空间  
	char *pChar = NULL;
	pChar = (char*)malloc((num)*sizeof(char));
	if (pChar == NULL)
	{
		free(pChar);
	}
	memset(pChar, 0, num*sizeof(char));

	//将宽字节字符串转换为多字节字符串  
	WideCharToMultiByte(CP_ACP, 0, in_str, -1, pChar, num, NULL, 0);//CP_THREAD_ACP
///	WideCharToMultiByte(CP_THREAD_ACP, 0, in_str, -1, pChar, num, NULL, 0);//
	return pChar;
}

wchar_t* CStringOperator::char2wchar(const char* in_str)
{
	wchar_t* pWCHAR = NULL;

	//计算pChar所指向的多字节字符串相当于多少个宽字节  
	DWORD num = MultiByteToWideChar(CP_ACP, 0, in_str, -1, NULL, 0);

	pWCHAR = (wchar_t*)malloc(num*sizeof(wchar_t));

	if (pWCHAR == NULL)
	{
		free(pWCHAR);
	}

	memset(pWCHAR, 0, num*sizeof(wchar_t));

	//多字节转换为宽字节  
	MultiByteToWideChar(CP_ACP, 0, in_str, -1, pWCHAR, num);
	return pWCHAR;
}


char* CStringOperator::G2U2(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}


void CStringOperator::transLateCode(const string& strSrc, string& str_dist)
{
	char* c_str = G2U2(strSrc.c_str());
	str_dist = c_str;
	if (c_str != NULL)
	{
		delete[] c_str;
	}
}

wstring CStringOperator::DecodeUtf8(string in)
{
	wstring s(in.length(), _T(' '));
	size_t len = ::MultiByteToWideChar(CP_UTF8, 0,
		in.c_str(), in.length(),
		&s[0], s.length());
	s.resize(len);
	return s;
}

string CStringOperator::ws2s(const wstring& ws)
{
	string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

void CStringOperator::wchangeCh(string& photo_base64, char ch)
{
	auto citr = find(photo_base64.begin(), photo_base64.end(), ch);
	while (citr != photo_base64.end())
	{
		char& current_str = *citr;
		current_str = '%2b';
		citr = find(citr, photo_base64.end(), ch);
	}
}


bool CStringOperator::StringToWString(const std::string &str, std::wstring &wstr)
 {
     int nLen = (int)str.length();
     wstr.resize(nLen, L' ');

     int nResult = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);

     if (nResult == 0)
     {
          return FALSE;
      }

      return TRUE;
  }


void CStringOperator::string_space(const string& s, string& res)
{
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '+') {
			res += "%2b";
		}
		else {
			res.push_back(s[i]);
		}
	}
}

void CStringOperator::UTF8ToGBK(char *&szOut)
{
	unsigned short *wszGBK;
	char *szGBK;
	//长度
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, NULL, 0);
	wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, (LPWSTR)wszGBK, len);

	//长度
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

	//szOut = szGBK; //这样得到的szOut不正确，因为此句意义是将szGBK的首地址赋给szOut，当delete []szGBK执行后szGBK的内

	//存空间将被释放，此时将得不到szOut的内容

	memset(szOut, 0, strlen(szGBK) + 1); //改将szGBK的内容赋给szOut ，这样即使szGBK被释放也能得到正确的值
	memcpy(szOut, szGBK, strlen(szGBK));


	delete[]szGBK;
	delete[]wszGBK;
}

void CStringOperator::UTF8ToGBK(const char *szOut, string& strOut)
{
	unsigned short *wszGBK;
	char *szGBK;
	//长度
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, NULL, 0);
	wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, (LPWSTR)wszGBK, len);

	//长度
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

	//szOut = szGBK; //这样得到的szOut不正确，因为此句意义是将szGBK的首地址赋给szOut，当delete []szGBK执行后szGBK的内

	//存空间将被释放，此时将得不到szOut的内容

	strOut = string(szGBK);


	delete[]szGBK;
	delete[]wszGBK;
}

void CStringOperator::GBKToUTF8(char* &szOut)
{
	char* strGBK = szOut;

	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, NULL, 0);
	unsigned short * wszUtf8 = new unsigned short[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, (LPWSTR)wszUtf8, len);

	len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL, NULL);

	//szOut = szUtf8;
	int tmpLen = strlen(szUtf8) + 1;
	memset(szOut, 0, strlen(szUtf8) + 1);
	memcpy(szOut, szUtf8, strlen(szUtf8));

	delete[] szUtf8;
	delete[] wszUtf8;
}


//HLW修改： filterCh是字符串中出现这里的字符，也可以当做数字字符
bool CStringOperator::isnum(string s,const vector<string>& filterCh)
{
	string stmp = s;
	for (auto p : filterCh)
		replace_all(stmp, p, "");
 

	stringstream sin(stmp);
	double t;
	char p;
	if (!(sin >> t))
		/*解释：
		sin>>t表示把sin转换成double的变量（其实对于int和float型的都会接收），如果转换成功，则值为非0，如果转换不成功就返回为0
		*/
		return false;
	if (sin >> p)
		/*解释：此部分用于检测错误输入中，数字加字符串的输入形式（例如：34.f），在上面的的部分（sin>>t）已经接收并转换了输入的数字部分，在stringstream中相应也会把那一部分给清除，如果此时传入字符串是数字加字符串的输入形式，则此部分可以识别并接收字符部分，例如上面所说的，接收的是.f这部分，所以条件成立，返回false;如果剩下的部分不是字符，那么则sin>>p就为0,则进行到下一步else里面
		*/
		return false;
	else
		return true;
}
#include "atlbase.h"
#include "atlstr.h"
void CStringOperator::AnsiToUTF8(string &str)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, ATL::CA2W((char*)str.data()), -1, NULL, 0, NULL, NULL);
	char *strNew = new char[len + 1];
	WideCharToMultiByte(CP_UTF8, 0, ATL::CA2W((char*)str.data()), -1, strNew, len, NULL, NULL);
	strNew[len] = '\0';
	str.clear();
	str = strNew;
	delete[] strNew;
	return;
}
void CStringOperator::UTF8ToAnsi(string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, nullptr, 0);
	unsigned short * str1 = new unsigned short[len + 1];
	memset(str1, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (const char*)strUTF8.c_str(), -1, (LPWSTR)str1, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)str1, -1, nullptr, 0, nullptr, nullptr);
	char *str2 = new char[len + 1];
	memset(str2, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)str1, -1, str2, len, nullptr, nullptr);
	strUTF8 = string(str2);
	delete[]str1;
	delete[]str2;
}
string CStringOperator::repaceWithRegex(const string & src, const string &strPattern)
{
	//string str = "12%硫酸";
	regex pattern(strPattern);
	string res = regex_replace(src, pattern, "");	//输出：_2018，将Hello替换为""
	return res;
}
bool In(wchar_t start, wchar_t end, wchar_t code)
{
	if (code >= start && code <= end)
	{
		return true;
	}
	return false;
}
char convert(wchar_t n)
{
	if (In(0xB0A1, 0xB0C4, n)) return 'a';
	if (In(0XB0C5, 0XB2C0, n)) return 'b';
	if (In(0xB2C1, 0xB4ED, n)) return 'c';
	if (In(0xB4EE, 0xB6E9, n)) return 'd';
	if (In(0xB6EA, 0xB7A1, n)) return 'e';
	if (In(0xB7A2, 0xB8c0, n)) return 'f';
	if (In(0xB8C1, 0xB9FD, n)) return 'g';
	if (In(0xB9FE, 0xBBF6, n)) return 'h';
	if (In(0xBBF7, 0xBFA5, n)) return 'j';
	if (In(0xBFA6, 0xC0AB, n)) return 'k';
	if (In(0xC0AC, 0xC2E7, n)) return 'l';
	if (In(0xC2E8, 0xC4C2, n)) return 'm';
	if (In(0xC4C3, 0xC5B5, n)) return 'n';
	if (In(0xC5B6, 0xC5BD, n)) return 'o';
	if (In(0xC5BE, 0xC6D9, n)) return 'p';
	if (In(0xC6DA, 0xC8BA, n)) return 'q';
	if (In(0xC8BB, 0xC8F5, n)) return 'r';
	if (In(0xC8F6, 0xCBF0, n)) return 's';
	if (In(0xCBFA, 0xCDD9, n)) return 't';
	if (In(0xCDDA, 0xCEF3, n)) return 'w';
	if (In(0xCEF4, 0xD188, n)) return 'x';
	if (In(0xD1B9, 0xD4D0, n)) return 'y';
	if (In(0xD4D1, 0xD7F9, n)) return 'z';
	return '\0';
}
string CStringOperator::getChineseHeadCharacter(const string & sChinese)

{
	char chr[3];
	wchar_t wchr = 0;

	char *buff = new char[sChinese.length()  ];
	memset(buff, '\0', sChinese.length());
	for (int i = 0, j = 0; j < sChinese.length();)
	{
		if ((sChinese[j] & 0x80) == 0)
		{
			buff[i++] = sChinese[j];
			j++;
			continue;
		}
		memset(chr, 0x00, sizeof(chr));
		chr[0] = sChinese[j++];
		chr[1] = sChinese[j++];

		wchr = 0;
		wchr = (chr[0] & 0xff) << 8;
		wchr |= (chr[1] & 0xff);
		buff[i++] = convert(wchr);
	}

	string dst = string(buff);

	delete[]buff;

	return dst;

}

