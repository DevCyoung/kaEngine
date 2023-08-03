#pragma once
#include <string>

class ScriptComponent;

enum class eScriptComponentType 
{
	NoiseTest,
	Bugiman,
	BulletMovement,
	CameraInputMoveMent,
	ChildTest,
	Chinatown04Controller,
	CursorMovement,
	GridPainter,
	InputMovementTest,
	LerpTest,
	ParentTest,
	PickPixelTest,
	PlayerController,
	PlayerMovementTest,
	Rect2DInterpolation,
	ShiftController,
	SimpleEditorCollider2D,
	TestScript,
	UIEffect,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

