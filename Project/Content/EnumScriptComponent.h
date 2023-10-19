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
	CCTVTextDrawer,
	ChildTest,
	Chinatown04Controller,
	ClearController,
	CopAI,
	CursorMovement,
	DieController,
	DoorController,
	Effect2D,
	Emotion,
	FolowPlayer,
	GalssWindow,
	GlassParticle,
	GridPainter,
	HeadHunterAI,
	HeadHunterBullet,
	HeadHunterLazer,
	HeadMovement,
	InputMovementTest,
	KissyfaceAI,
	LerpTest,
	MonsterAttack,
	NexeScene,
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
	SlashEffectMovement,
	TestScript,
	TitleController,
	UIEffect,
	End
};

const wchar_t* GetScriptComponentName(const eScriptComponentType type);
ScriptComponent* CreateScriptComponentByName(const std::wstring& scriptcomponentName);
ScriptComponent * CreateScriptComponentByEnum(const eScriptComponentType type);

