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
	CameraWall,
	ChildTest,
	Chinatown04Controller,
	CopAI,
	CursorMovement,
	DoorController,
	Effect2D,
	FolowPlayer,
	GalssWindow,
	GlassParticle,
	GridPainter,
	HeadMovement,
	InputMovementTest,
	KissyfaceAI,
	LerpTest,
	MonsterAttack,
	ParentTest,
	PathNode,
	PickPixelTest,
	PlayerController,
	PlayerMovementTest,
	Rect2DInterpolation,
	RewindComponent,
	ShieldCop,
	ShiftController,
	ShotGunAI,
	SimpleDrawPoint,
	SimpleEditorCollider2D,
	SlashComponent,
	TestScript,
	UIEffect,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

