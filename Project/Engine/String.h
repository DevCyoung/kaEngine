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
		static std::wstring StrToWStr(const std::string& STR);
		static std::string WStrToStr(const std::wstring& WSTR);
		static std::wstring SplitFilePathExtension(const std::wstring& FILE_PATH);
	};
}