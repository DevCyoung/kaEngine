#include "pch.h"
#include "EnumScriptComponent.h"

#include "Bugiman.h"
#include "BulletMovement.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "PlayerMovementTest.h"
#include "ShiftController.h"
#include "TestScript.h"
#include "UIEffect.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptComponentType::End)]
{
	L"Bugiman",
	L"BulletMovement",
	L"CameraInputMoveMent",
	L"CursorMovement",
	L"PlayerMovementTest",
	L"ShiftController",
	L"TestScript",
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
	else if (L"BulletMovement" == scriptcomponentName)
		scriptcomponent = new BulletMovement;
	else if (L"CameraInputMoveMent" == scriptcomponentName)
		scriptcomponent = new CameraInputMoveMent;
	else if (L"CursorMovement" == scriptcomponentName)
		scriptcomponent = new CursorMovement;
	else if (L"PlayerMovementTest" == scriptcomponentName)
		scriptcomponent = new PlayerMovementTest;
	else if (L"ShiftController" == scriptcomponentName)
		scriptcomponent = new ShiftController;
	else if (L"TestScript" == scriptcomponentName)
		scriptcomponent = new TestScript;
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
	case eScriptComponentType::BulletMovement:
		scriptcomponent = new BulletMovement;
		break;
	case eScriptComponentType::CameraInputMoveMent:
		scriptcomponent = new CameraInputMoveMent;
		break;
	case eScriptComponentType::CursorMovement:
		scriptcomponent = new CursorMovement;
		break;
	case eScriptComponentType::PlayerMovementTest:
		scriptcomponent = new PlayerMovementTest;
		break;
	case eScriptComponentType::ShiftController:
		scriptcomponent = new ShiftController;
		break;
	case eScriptComponentType::TestScript:
		scriptcomponent = new TestScript;
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

