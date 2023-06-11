#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "String.h"
#include <codecvt>
#include <locale>



namespace engine
{
	String::String()
	{
	}
	String::~String()
	{
	}

	std::wstring String::StrToWStr(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return std::wstring(converter.from_bytes(str));
	}

	std::string String::WStrToStr(const std::wstring& wstr)
	{		
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
		return std::string(converter.to_bytes(wstr));
	}
}