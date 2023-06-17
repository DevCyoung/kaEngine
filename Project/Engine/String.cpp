#include "pch.h"
#include "String.h"

namespace engine
{
	String::String()
	{
	}
	String::~String()
	{
	}

	//현재핵으로 하였음 추후에 정확히 사용법을 익힐것
	std::wstring String::StrToWStr(const std::string& str)
	{
		const int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		std::wstring wstr(size, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr.data(), size);
		return wstr;
	}

	std::string String::WStrToStr(const std::wstring& wstr)
	{
		const int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string str(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, str.data(), size, nullptr, nullptr);
		return str;
	}
	//핵핵핵
}
