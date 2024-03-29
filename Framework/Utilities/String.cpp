#include "Framework.h"
#include "String.h"

#include <iomanip> // 입출력 스트림의 조작자를 정의하는 헤더 / 스트림의 출력 형식을 제어하는데 사용
#include <sstream> // 문자열 스트림을 정의, 메모리 버퍼에 데이터를 읽고 쓰는데 
#include <atlconv.h>

// npos -> no position

// 문자열을 지정된 구분자로 분할하는 기능
void String::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();
	int cutAt = 0;
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0)
			result->push_back(origin.substr(0, cutAt));
		
		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) // 자르고도 남은것이 있다면
		result->push_back(origin.substr(0, cutAt));

}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();
	int cutAt = 0;  // 자를 위치
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) // 자르는 위치가 0보다 크다면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) // 자르고도 남은것이 있다면
		result->push_back(origin.substr(0, cutAt));
}

// 특정한 문자로 시작하는지 체크
bool String::StartWith(string str, string comp)
{
	string::size_type index = str.find(comp);
	if (index != string::npos && (int)index == 0)
		return true;

	return false;
}

bool String::StartWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

// 특정한 문자를 포함하는지 체크
bool String::Contain(string str, string comp)
{

	size_t found = str.find(comp);

	return found != string::npos;
}

bool String::Contain(wstring str, wstring comp)
{

	size_t found = str.find(comp);

	return found != wstring::npos;
}

void String::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos))!= string::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}
	*str = temp;
}

void String::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}
	*str = temp;
}

string String::ToString(Vector3 vec3, int precision)
{
	// setprecision : 부동 소수점 숫자의 정밀도를 조정하는 조작자
	string temp;
	stringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;

	temp = " X : " + stream1.str() + " Y : " + stream2.str() + " Z : " + stream3.str();

	return temp;
}

wstring String::ToWString(Vector3 vec3, int precision)
{
	wstring temp;
	wstringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;

	temp = L"X : " + stream1.str() + L"Y : " + stream2.str() + L"Z : " + stream3.str();

	return temp;
}

string String::ToString(wstring str)
{
	string temp = "";
	temp.assign(str.begin(), str.end());

	return temp;
}

wstring String::ToWString(string str)
{
	USES_CONVERSION;
	wstring temp = A2W(str.c_str());
	//temp.assign(str.begin(), str.end());

	return temp;
}
