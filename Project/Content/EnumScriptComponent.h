#pragma once
#include <string>

class ScriptComponent;

enum class eScriptComponentType 
{
	Bugiman,
	BulletMovement,
	CameraInputMoveMent,
	ChildTest,
	CursorMovement,
	InputMovementTest,
	LerpTest,
	NoiseTest,
	ParentTest,
	PlayerMovementTest,
	ShiftController,
	TestScript,
	UIEffect,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

