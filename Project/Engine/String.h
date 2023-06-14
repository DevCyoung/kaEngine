#pragma once

#include <string>

namespace engine
{
	class String
	{
	private:
		String();
		virtual ~String();

	public:		
		static std::wstring StrToWStr(const std::string& str);
		static std::string WStrToStr(const std::wstring& wstr);
	};
}

