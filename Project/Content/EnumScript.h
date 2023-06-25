#pragma once

enum class eScriptType 
{
	CameraScript,
	End
};

const wchar_t* GetScriptName(const eScriptType type);
Script* CreateScriptByName(const std::wstring& scriptName);
Script * CreateScriptByEnum(const eScriptType type);

