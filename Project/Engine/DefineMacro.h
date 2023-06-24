#pragma once
#define WCHAR_SWITCH_DEFAULT (L"switch default")
#define WCHAR_IS_NULLPTR (L"is nullptr")
#define WCHAR_IS_NOT_NULLPTR (L"is not nullptr")
#define WCHAR_IS_INVALID_TYPE (L"is invalid type")

#define Assert(expression, message) assert(expression && message)
#define Static_Assert(expression, message) static_assert(expression, message)

//#define FIXME(message, filenameHint) MessageBox(nullptr, message, L"FIXME", MB_OK | MB_ICONWARNING)