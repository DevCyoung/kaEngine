#pragma once
#include <string>

class ScriptComponent;

enum class eScriptComponentType 
{
	A,
	B,
	C,
	D,
	E,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

