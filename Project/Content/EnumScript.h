#pragma once

enum class eScriptType
{
	CameraScript,
	diffTest,
	Findingin,
	End
};

const wchar_t* GetComponentName(const eScriptType type);
Script* CreateScriptByName(const std::wstring& scriptName);
Script* CreateScriptByEnum(const eScriptType type);

