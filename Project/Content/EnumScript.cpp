#include "pch.h"
#include "EnumScript.h"

#include "CameraScript.h"
#include "Findingin.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptType::End)]
{
	L"CameraScript",
	L"Findingin",
};

const wchar_t* GetComponentName(const eScriptType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eScriptType::End));
	return ScriptComponentNames[static_cast<UINT>(type)];
}

Script* CreateScriptByName(const std::wstring& scriptName)
{
	Script* script = nullptr;

	if (L"CameraScript" == scriptName)
		script = new CameraScript;
	else if (L"Findingin" == scriptName)
		script = new Findingin;
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
	case eScriptType::Findingin:
		script = new Findingin;
		break;
	default:
		assert(false);
		break;
	}
	return script;
}

