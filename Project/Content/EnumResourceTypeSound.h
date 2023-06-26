#pragma once


enum class eResSound
{
	Die,
	End
};

const wchar_t* EnumResourcePath(eResSound type);
