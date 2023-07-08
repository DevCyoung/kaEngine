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
	std::wstring String::StrToWStr(const std::string& str)
	{
		const int WSTR_LEN = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		std::wstring wstr(WSTR_LEN, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr.data(), WSTR_LEN);
		return wstr;
	}

	std::string String::WStrToStr(const std::wstring& wstr)
	{
		const int STR_LEN = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string str(STR_LEN, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, str.data(), STR_LEN, nullptr, nullptr);
		return str;
	}
	//핵핵핵

	std::wstring String::SplitFilePathExtension(const std::wstring& filePath)
	{
		constexpr UINT FILE_PATH_MAX_LEN = 256;
		wchar_t szExtension[FILE_PATH_MAX_LEN] = { 0, };

		errno_t err = _wsplitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, FILE_PATH_MAX_LEN);
		(void)(err);

		Assert(!err, L"error file path");

		return szExtension;
	}
}