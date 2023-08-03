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

	//ÇöÀçÇÙÀ¸·Î ÇÏ¿´À½ ÃßÈÄ¿¡ Á¤È®È÷ »ç¿ë¹ýÀ» ÀÍÈú°Í
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
	//ÇÙÇÙÇÙ

	std::wstring String::SplitFilePathExtension(const std::wstring& filePath)
	{
		constexpr UINT FILE_PATH_MAX_LEN = 256;
		wchar_t szExtension[FILE_PATH_MAX_LEN] = { 0, };

		errno_t err = _wsplitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, FILE_PATH_MAX_LEN);
		(void)(err);

		Assert(!err, L"error file path");

		return szExtension;
	}

	std::wstring String::SWPrintf(const wchar_t* const format, ...)
	{
		constexpr UINT STRING_MAX_LEN = 512;

		wchar_t szBuffer[STRING_MAX_LEN] = { 0, };

		va_list args;
		va_start(args, format);
		swprintf_s(szBuffer, STRING_MAX_LEN, format, args);
		va_end(args);

		return szBuffer;
	}
}