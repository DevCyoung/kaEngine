#include "pch.h"
#include "String.h"

namespace helper
{
	String::String()
	{
	}
	String::~String()
	{
	}

	//현재핵으로 하였음 추후에 정확히 사용법을 익힐것
	std::wstring String::StrToWStr(const std::string& STR)
	{
		const int SIZE = MultiByteToWideChar(CP_UTF8, 0, STR.c_str(), -1, nullptr, 0);
		std::wstring wstr(SIZE, 0);
		MultiByteToWideChar(CP_UTF8, 0, STR.c_str(), -1, wstr.data(), SIZE);
		return wstr;
	}

	std::string String::WStrToStr(const std::wstring& WSTR)
	{
		const int SIZE = WideCharToMultiByte(CP_UTF8, 0, WSTR.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string str(SIZE, 0);
		WideCharToMultiByte(CP_UTF8, 0, WSTR.c_str(), -1, str.data(), SIZE, nullptr, nullptr);
		return str;
	}
	//핵핵핵

	std::wstring String::SplitFilePathExtension(const std::wstring& FILE_PATH)
	{
		constexpr UINT PATH_LEN = 256;
		wchar_t szExtension[PATH_LEN] = {0, };

		errno_t err = _wsplitpath_s(FILE_PATH.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, PATH_LEN);
		(void)(err);

		Assert(!err, L"error file path");
		return szExtension;
	}
	
}