#include "pch.h"
#include "EnumScriptComponent.h"

#include "Bugiman.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "ShiftController.h"
#include "UIEffect.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptComponentType::End)]
{
	L"Bugiman",
	L"CameraInputMoveMent",
	L"CursorMovement",
	L"ShiftController",
	L"UIEffect",
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eScriptComponentType::End));
	return ScriptComponentNames[static_cast<UINT>(type)];
}

ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName)
{
	ScriptComponent* scriptcomponent = nullptr;

	if (L"Bugiman" == scriptcomponentName)
		scriptcomponent = new Bugiman;
	else if (L"CameraInputMoveMent" == scriptcomponentName)
		scriptcomponent = new CameraInputMoveMent;
	else if (L"CursorMovement" == scriptcomponentName)
		scriptcomponent = new CursorMovement;
	else if (L"ShiftController" == scriptcomponentName)
		scriptcomponent = new ShiftController;
	else if (L"UIEffect" == scriptcomponentName)
		scriptcomponent = new UIEffect;
	else
		assert(false);
	return scriptcomponent;
}

ScriptComponent* CreateScriptComponentByEnum(const eScriptComponentType type)
{
	ScriptComponent* scriptcomponent = nullptr;

	switch (type)
	{
	case eScriptComponentType::Bugiman:
		scriptcomponent = new Bugiman;
		break;
	case eScriptComponentType::CameraInputMoveMent:
		scriptcomponent = new CameraInputMoveMent;
		break;
	case eScriptComponentType::CursorMovement:
		scriptcomponent = new CursorMovement;
		break;
	case eScriptComponentType::ShiftController:
		scriptcomponent = new ShiftController;
		break;
	case eScriptComponentType::UIEffect:
		scriptcomponent = new UIEffect;
		break;
	default:
		assert(false);
		break;
	}
	return scriptcomponent;
}

