#include "pch.h"
#include "EnumScript.h"

#include "CameraScript.h"

static constexpr const wchar_t* const ScriptNames[static_cast<UINT>(eScriptType::End)]
{
	L"CameraScript",
};

const wchar_t* GetScriptName(const eScriptType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eScriptType::End));
	return ScriptNames[static_cast<UINT>(type)];
}

Script* CreateScriptByName(const std::wstring& scriptName)
{
	Script* script = nullptr;

	if (L"CameraScript" == scriptName)
		script = new CameraScript;
	else
		assert(false);
	return script;
}

Script* CreateScriptByEnum(const eScriptType type)
{
	Script* script = nullptr;

	switch (type)
	{
	case eScriptType::CameraScript:
		script = new CameraScript;
		break;
	default:
		assert(false);
		break;
	}
	return script;
}

