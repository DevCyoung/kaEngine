#include "pch.h"
#include "EnumScriptComponent.h"

#include "BlaBLa.h"
#include "Bugiman.h"
#include "CameraInputMove.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptComponentType::End)]
{
	L"BlaBLa",
	L"Bugiman",
	L"CameraInputMove",
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eScriptComponentType::End));
	return ScriptComponentNames[static_cast<UINT>(type)];
}

ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName)
{
	ScriptComponent* scriptcomponent = nullptr;

	if (L"BlaBLa" == scriptcomponentName)
		scriptcomponent = new BlaBLa;
	else if (L"Bugiman" == scriptcomponentName)
		scriptcomponent = new Bugiman;
	else if (L"CameraInputMove" == scriptcomponentName)
		scriptcomponent = new CameraInputMove;
	else
		assert(false);
	return scriptcomponent;
}

ScriptComponent* CreateScriptComponentByEnum(const eScriptComponentType type)
{
	ScriptComponent* scriptcomponent = nullptr;

	switch (type)
	{
	case eScriptComponentType::BlaBLa:
		scriptcomponent = new BlaBLa;
		break;
	case eScriptComponentType::Bugiman:
		scriptcomponent = new Bugiman;
		break;
	case eScriptComponentType::CameraInputMove:
		scriptcomponent = new CameraInputMove;
		break;
	default:
		assert(false);
		break;
	}
	return scriptcomponent;
}

