#pragma once
#include <string>

class ScriptComponent;

enum class eScriptComponentType 
{
	NoiseTest,
	PlayerPath,
	GangsterAI,
	AfterImage,
	AxeMovement,
	Bugiman,
	BulletMovement,
	CameraInputMoveMent,
	ChildTest,
	Chinatown04Controller,
	CursorMovement,
	FolowPlayer,
	GridPainter,
	InputMovementTest,
	KissyfaceAI,
	LerpTest,
	ParentTest,
	PathNode,
	PickPixelTest,
	PlayerController,
	PlayerMovementTest,
	Rect2DInterpolation,
	RewindComponent,
	ShiftController,
	SimpleDrawPoint,
	SimpleEditorCollider2D,
	TestScript,
	UIEffect,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

