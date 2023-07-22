#pragma once
#include <string>

class ScriptComponent;

enum class eScriptComponentType 
{
	Bugiman,
	BulletMovement,
	CameraInputMoveMent,
	ChildTest,
	Chinatown04Controller,
	CursorMovement,
	InputMovementTest,
	LerpTest,
	NoiseTest,
	ParentTest,
	PickPixelTest,
	PlayerController,
	PlayerMovementTest,
	ShiftController,
	TestScript,
	UIEffect,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

