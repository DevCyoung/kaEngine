#include "pch.h"
#include "EnumScriptComponent.h"

#include "A.h"
#include "B.h"
#include "C.h"
#include "CameraInputMove.h"
#include "D.h"
#include "E.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptComponentType::End)]
{
	L"A",
	L"B",
	L"C",
	L"CameraInputMove",
	L"D",
	L"E",
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eScriptComponentType::End));
	return ScriptComponentNames[static_cast<UINT>(type)];
}

ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName)
{
	ScriptComponent* scriptcomponent = nullptr;

	if (L"A" == scriptcomponentName)
		scriptcomponent = new A;
	else if (L"B" == scriptcomponentName)
		scriptcomponent = new B;
	else if (L"C" == scriptcomponentName)
		scriptcomponent = new C;
	else if (L"CameraInputMove" == scriptcomponentName)
		scriptcomponent = new CameraInputMove;
	else if (L"D" == scriptcomponentName)
		scriptcomponent = new D;
	else if (L"E" == scriptcomponentName)
		scriptcomponent = new E;
	else
		assert(false);
	return scriptcomponent;
}

ScriptComponent* CreateScriptComponentByEnum(const eScriptComponentType type)
{
	ScriptComponent* scriptcomponent = nullptr;

	switch (type)
	{
	case eScriptComponentType::A:
		scriptcomponent = new A;
		break;
	case eScriptComponentType::B:
		scriptcomponent = new B;
		break;
	case eScriptComponentType::C:
		scriptcomponent = new C;
		break;
	case eScriptComponentType::CameraInputMove:
		scriptcomponent = new CameraInputMove;
		break;
	case eScriptComponentType::D:
		scriptcomponent = new D;
		break;
	case eScriptComponentType::E:
		scriptcomponent = new E;
		break;
	default:
		assert(false);
		break;
	}
	return scriptcomponent;
}

