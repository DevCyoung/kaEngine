#pragma once
#include <string>

namespace helper
{
	class String
	{
	private:
		String();
		virtual ~String();
		String(const String&) = delete;
		String& operator=(const String&) = delete;

	public:
		static std::wstring StrToWStr(const std::string& str);
		static std::string WStrToStr(const std::wstring& wstr);
		static std::wstring SplitFilePathExtension(const std::wstring& filePath);
		static std::wstring SWPrintf(const wchar_t* const format, ...);
	};
}