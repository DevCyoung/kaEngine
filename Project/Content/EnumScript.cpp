#include "pch.h"
#include "EnumScript.h"

const wchar_t* ComponentNames[static_cast<UINT>(eScriptType::End)]
{
	L"CameraScript",
	L"SampleScript",
	L"TestScript",
};

const wchar_t* GetComponentWstrByEnum(const eScriptType type)
{
	return ComponentNames[static_cast<UINT>(type)];
}

