#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;
class CStringOperator
{
public:
	CStringOperator(void);
	~CStringOperator(void);
	//string 转换成 int
	static bool string2int(const string& string_key, int& int_key);
	//int 转换成string
	static bool int2string(const int& int_key, string& string_key);
	static string int2string(const int& int_key);
	static bool double2string(const double& int_key, string& string_key);
	//unsigned long 转换成string
	static bool unsignedlong2string(const unsigned long& long_key, string& string_key);
	//string 传换成 double
	static bool string2double(const std::string& string_key, double& float_key);
	//去掉字符串两端空格
	static void Trim(string & str);
	static bool IsSpace(char c);
	//去掉字符串两端给定字符
	static void Trim(string& str, const char& limit_str);
	static void Trim(char* str, int& len, const char&limit_str);
	static bool IsLimit(const char& c, const char& limit);
	//去掉字符窜中给定字符窜
	static void LeftOutStr(string& src_str, const string& limit_str);
	//splite分裂函数
	static void splite(const string& key_str, const string& split_flag, vector<string>& value_vec);

	//编码转换
	static wstring UTF8ToUnicode(const string& str);
	static string UnicodeToUTF8(const wstring& str);
	static wstring ANSIToUnicode(const string& str);
	static string UnicodeToANSI(const wstring& str);

	//wchar转char
	static char* wChar2char(wchar_t* in_str);
	//char 转wchar
	static wchar_t* char2wchar(const char* in_str);
	/*转UTF-8*/
	static char* G2U2(const char* gb2312);
	/*转UTF-8*/
	static void transLateCode(const string& strSrc, string& str_dist);

	static wstring DecodeUtf8(string in);

	static string ws2s(const wstring& ws);
	/*将字符窜中所有给定字符替换成%2b*/
	static void wchangeCh(string& photo_base64, char ch);

	static bool StringToWString(const std::string &str, std::wstring &wstr);

	static void string_space(const string& s, string& res);

	static void UTF8ToGBK(char *&szOut);
	static void UTF8ToGBK(const char *szOut, string& strOut);
	static void GBKToUTF8(char* &szOut);

	//
//	static void string2Cimage(const char* buf, int len, ATL::CImage& image);
	//判断一个字符串是否是数字,vector中存放的是过滤字符，即这些字符可以出现
	static bool isnum(string s,const vector<string>& filterCh = vector<string>());

	static void replace_all(string& str, const string& old_value, const string& new_value)
	{
		while (true) {
			string::size_type pos(0);
			if ((pos = str.find(old_value)) != string::npos)
				str.replace(pos, old_value.length(), new_value);
			else break;
		}
	}
	static void AnsiToUTF8(string &str);
	static void UTF8ToAnsi(string& strUTF8);
	static string repaceWithRegex(const string & src, const string &pattern);
	static string getChineseHeadCharacter(const string & sChinese);
};

