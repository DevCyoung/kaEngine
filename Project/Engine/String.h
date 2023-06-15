#pragma once

namespace engine
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
	};
}
