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
	//string ת���� int
	static bool string2int(const string& string_key, int& int_key);
	//int ת����string
	static bool int2string(const int& int_key, string& string_key);
	static string int2string(const int& int_key);
	static bool double2string(const double& int_key, string& string_key);
	//unsigned long ת����string
	static bool unsignedlong2string(const unsigned long& long_key, string& string_key);
	//string ������ double
	static bool string2double(const std::string& string_key, double& float_key);
	//ȥ���ַ������˿ո�
	static void Trim(string & str);
	static bool IsSpace(char c);
	//ȥ���ַ������˸����ַ�
	static void Trim(string& str, const char& limit_str);
	static void Trim(char* str, int& len, const char&limit_str);
	static bool IsLimit(const char& c, const char& limit);
	//ȥ���ַ����и����ַ���
	static void LeftOutStr(string& src_str, const string& limit_str);
	//splite���Ѻ���
	static void splite(const string& key_str, const string& split_flag, vector<string>& value_vec);

	//����ת��
	static wstring UTF8ToUnicode(const string& str);
	static string UnicodeToUTF8(const wstring& str);
	static wstring ANSIToUnicode(const string& str);
	static string UnicodeToANSI(const wstring& str);

	//wcharתchar
	static char* wChar2char(wchar_t* in_str);
	//char תwchar
	static wchar_t* char2wchar(const char* in_str);
	/*תUTF-8*/
	static char* G2U2(const char* gb2312);
	/*תUTF-8*/
	static void transLateCode(const string& strSrc, string& str_dist);

	static wstring DecodeUtf8(string in);

	static string ws2s(const wstring& ws);
	/*���ַ��������и����ַ��滻��%2b*/
	static void wchangeCh(string& photo_base64, char ch);

	static bool StringToWString(const std::string &str, std::wstring &wstr);

	static void string_space(const string& s, string& res);

	static void UTF8ToGBK(char *&szOut);
	static void UTF8ToGBK(const char *szOut, string& strOut);
	static void GBKToUTF8(char* &szOut);

	//
//	static void string2Cimage(const char* buf, int len, ATL::CImage& image);
	//�ж�һ���ַ����Ƿ�������,vector�д�ŵ��ǹ����ַ�������Щ�ַ����Գ���
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

