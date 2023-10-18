#include "pch.h"
#include "EnumScriptComponent.h"

#include "NoiseTest.h"
#include "PlayerPath.h"
#include "GangsterAI.h"
#include "AfterImage.h"
#include "AxeMovement.h"
#include "Bugiman.h"
#include "BulletMovement.h"
#include "CameraInputMoveMent.h"
#include "CameraWall.h"
#include "CCTVTextDrawer.h"
#include "ChildTest.h"
#include "Chinatown04Controller.h"
#include "ClearController.h"
#include "CopAI.h"
#include "CursorMovement.h"
#include "DieController.h"
#include "DoorController.h"
#include "Effect2D.h"
#include "Emotion.h"
#include "FolowPlayer.h"
#include "GalssWindow.h"
#include "GlassParticle.h"
#include "GridPainter.h"
#include "HeadHunterAI.h"
#include "HeadHunterBullet.h"
#include "HeadHunterLazer.h"
#include "HeadMovement.h"
#include "InputMovementTest.h"
#include "KissyfaceAI.h"
#include "LerpTest.h"
#include "MonsterAttack.h"
#include "NexeScene.h"
#include "ParentTest.h"
#include "PathNode.h"
#include "PickPixelTest.h"
#include "PlayerController.h"
#include "PlayerMovementTest.h"
#include "Rect2DInterpolation.h"
#include "RewindComponent.h"
#include "ShieldCop.h"
#include "ShiftController.h"
#include "ShotGunAI.h"
#include "SimpleDrawPoint.h"
#include "SimpleEditorCollider2D.h"
#include "SlashComponent.h"
#include "TestScript.h"
#include "TitleController.h"
#include "UIEffect.h"

static constexpr const wchar_t* const ScriptComponentNames[static_cast<UINT>(eScriptComponentType::End)]
{
	L"NoiseTest",
	L"PlayerPath",
	L"GangsterAI",
	L"AfterImage",
	L"AxeMovement",
	L"Bugiman",
	L"BulletMovement",
	L"CameraInputMoveMent",
	L"CameraWall",
	L"CCTVTextDrawer",
	L"ChildTest",
	L"Chinatown04Controller",
	L"ClearController",
	L"CopAI",
	L"CursorMovement",
	L"DieController",
	L"DoorController",
	L"Effect2D",
	L"Emotion",
	L"FolowPlayer",
	L"GalssWindow",
	L"GlassParticle",
	L"GridPainter",
	L"HeadHunterAI",
	L"HeadHunterBullet",
	L"HeadHunterLazer",
	L"HeadMovement",
	L"InputMovementTest",
	L"KissyfaceAI",
	L"LerpTest",
	L"MonsterAttack",
	L"NexeScene",
	L"ParentTest",
	L"PathNode",
	L"PickPixelTest",
	L"PlayerController",
	L"PlayerMovementTest",
	L"Rect2DInterpolation",
	L"RewindComponent",
	L"ShieldCop",
	L"ShiftController",
	L"ShotGunAI",
	L"SimpleDrawPoint",
	L"SimpleEditorCollider2D",
	L"SlashComponent",
	L"TestScript",
	L"TitleController",
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

	if (L"NoiseTest" == scriptcomponentName)
		scriptcomponent = new NoiseTest;
	else if (L"PlayerPath" == scriptcomponentName)
		scriptcomponent = new PlayerPath;
	else if (L"GangsterAI" == scriptcomponentName)
		scriptcomponent = new GangsterAI;
	else if (L"AfterImage" == scriptcomponentName)
		scriptcomponent = new AfterImage;
	else if (L"AxeMovement" == scriptcomponentName)
		scriptcomponent = new AxeMovement;
	else if (L"Bugiman" == scriptcomponentName)
		scriptcomponent = new Bugiman;
	else if (L"BulletMovement" == scriptcomponentName)
		scriptcomponent = new BulletMovement;
	else if (L"CameraInputMoveMent" == scriptcomponentName)
		scriptcomponent = new CameraInputMoveMent;
	else if (L"CameraWall" == scriptcomponentName)
		scriptcomponent = new CameraWall;
	else if (L"CCTVTextDrawer" == scriptcomponentName)
		scriptcomponent = new CCTVTextDrawer;
	else if (L"ChildTest" == scriptcomponentName)
		scriptcomponent = new ChildTest;
	else if (L"Chinatown04Controller" == scriptcomponentName)
		scriptcomponent = new Chinatown04Controller;
	else if (L"ClearController" == scriptcomponentName)
		scriptcomponent = new ClearController;
	else if (L"CopAI" == scriptcomponentName)
		scriptcomponent = new CopAI;
	else if (L"CursorMovement" == scriptcomponentName)
		scriptcomponent = new CursorMovement;
	else if (L"DieController" == scriptcomponentName)
		scriptcomponent = new DieController;
	else if (L"DoorController" == scriptcomponentName)
		scriptcomponent = new DoorController;
	else if (L"Effect2D" == scriptcomponentName)
		scriptcomponent = new Effect2D;
	else if (L"Emotion" == scriptcomponentName)
		scriptcomponent = new Emotion;
	else if (L"FolowPlayer" == scriptcomponentName)
		scriptcomponent = new FolowPlayer;
	else if (L"GalssWindow" == scriptcomponentName)
		scriptcomponent = new GalssWindow;
	else if (L"GlassParticle" == scriptcomponentName)
		scriptcomponent = new GlassParticle;
	else if (L"GridPainter" == scriptcomponentName)
		scriptcomponent = new GridPainter;
	else if (L"HeadHunterAI" == scriptcomponentName)
		scriptcomponent = new HeadHunterAI;
	else if (L"HeadHunterBullet" == scriptcomponentName)
		scriptcomponent = new HeadHunterBullet;
	else if (L"HeadHunterLazer" == scriptcomponentName)
		scriptcomponent = new HeadHunterLazer;
	else if (L"HeadMovement" == scriptcomponentName)
		scriptcomponent = new HeadMovement;
	else if (L"InputMovementTest" == scriptcomponentName)
		scriptcomponent = new InputMovementTest;
	else if (L"KissyfaceAI" == scriptcomponentName)
		scriptcomponent = new KissyfaceAI;
	else if (L"LerpTest" == scriptcomponentName)
		scriptcomponent = new LerpTest;
	else if (L"MonsterAttack" == scriptcomponentName)
		scriptcomponent = new MonsterAttack;
	else if (L"NexeScene" == scriptcomponentName)
		scriptcomponent = new NexeScene;
	else if (L"ParentTest" == scriptcomponentName)
		scriptcomponent = new ParentTest;
	else if (L"PathNode" == scriptcomponentName)
		scriptcomponent = new PathNode;
	else if (L"PickPixelTest" == scriptcomponentName)
		scriptcomponent = new PickPixelTest;
	else if (L"PlayerController" == scriptcomponentName)
		scriptcomponent = new PlayerController;
	else if (L"PlayerMovementTest" == scriptcomponentName)
		scriptcomponent = new PlayerMovementTest;
	else if (L"Rect2DInterpolation" == scriptcomponentName)
		scriptcomponent = new Rect2DInterpolation;
	else if (L"RewindComponent" == scriptcomponentName)
		scriptcomponent = new RewindComponent;
	else if (L"ShieldCop" == scriptcomponentName)
		scriptcomponent = new ShieldCop;
	else if (L"ShiftController" == scriptcomponentName)
		scriptcomponent = new ShiftController;
	else if (L"ShotGunAI" == scriptcomponentName)
		scriptcomponent = new ShotGunAI;
	else if (L"SimpleDrawPoint" == scriptcomponentName)
		scriptcomponent = new SimpleDrawPoint;
	else if (L"SimpleEditorCollider2D" == scriptcomponentName)
		scriptcomponent = new SimpleEditorCollider2D;
	else if (L"SlashComponent" == scriptcomponentName)
		scriptcomponent = new SlashComponent;
	else if (L"TestScript" == scriptcomponentName)
		scriptcomponent = new TestScript;
	else if (L"TitleController" == scriptcomponentName)
		scriptcomponent = new TitleController;
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
	case eScriptComponentType::NoiseTest:
		scriptcomponent = new NoiseTest;
		break;
	case eScriptComponentType::PlayerPath:
		scriptcomponent = new PlayerPath;
		break;
	case eScriptComponentType::GangsterAI:
		scriptcomponent = new GangsterAI;
		break;
	case eScriptComponentType::AfterImage:
		scriptcomponent = new AfterImage;
		break;
	case eScriptComponentType::AxeMovement:
		scriptcomponent = new AxeMovement;
		break;
	case eScriptComponentType::Bugiman:
		scriptcomponent = new Bugiman;
		break;
	case eScriptComponentType::BulletMovement:
		scriptcomponent = new BulletMovement;
		break;
	case eScriptComponentType::CameraInputMoveMent:
		scriptcomponent = new CameraInputMoveMent;
		break;
	case eScriptComponentType::CameraWall:
		scriptcomponent = new CameraWall;
		break;
	case eScriptComponentType::CCTVTextDrawer:
		scriptcomponent = new CCTVTextDrawer;
		break;
	case eScriptComponentType::ChildTest:
		scriptcomponent = new ChildTest;
		break;
	case eScriptComponentType::Chinatown04Controller:
		scriptcomponent = new Chinatown04Controller;
		break;
	case eScriptComponentType::ClearController:
		scriptcomponent = new ClearController;
		break;
	case eScriptComponentType::CopAI:
		scriptcomponent = new CopAI;
		break;
	case eScriptComponentType::CursorMovement:
		scriptcomponent = new CursorMovement;
		break;
	case eScriptComponentType::DieController:
		scriptcomponent = new DieController;
		break;
	case eScriptComponentType::DoorController:
		scriptcomponent = new DoorController;
		break;
	case eScriptComponentType::Effect2D:
		scriptcomponent = new Effect2D;
		break;
	case eScriptComponentType::Emotion:
		scriptcomponent = new Emotion;
		break;
	case eScriptComponentType::FolowPlayer:
		scriptcomponent = new FolowPlayer;
		break;
	case eScriptComponentType::GalssWindow:
		scriptcomponent = new GalssWindow;
		break;
	case eScriptComponentType::GlassParticle:
		scriptcomponent = new GlassParticle;
		break;
	case eScriptComponentType::GridPainter:
		scriptcomponent = new GridPainter;
		break;
	case eScriptComponentType::HeadHunterAI:
		scriptcomponent = new HeadHunterAI;
		break;
	case eScriptComponentType::HeadHunterBullet:
		scriptcomponent = new HeadHunterBullet;
		break;
	case eScriptComponentType::HeadHunterLazer:
		scriptcomponent = new HeadHunterLazer;
		break;
	case eScriptComponentType::HeadMovement:
		scriptcomponent = new HeadMovement;
		break;
	case eScriptComponentType::InputMovementTest:
		scriptcomponent = new InputMovementTest;
		break;
	case eScriptComponentType::KissyfaceAI:
		scriptcomponent = new KissyfaceAI;
		break;
	case eScriptComponentType::LerpTest:
		scriptcomponent = new LerpTest;
		break;
	case eScriptComponentType::MonsterAttack:
		scriptcomponent = new MonsterAttack;
		break;
	case eScriptComponentType::NexeScene:
		scriptcomponent = new NexeScene;
		break;
	case eScriptComponentType::ParentTest:
		scriptcomponent = new ParentTest;
		break;
	case eScriptComponentType::PathNode:
		scriptcomponent = new PathNode;
		break;
	case eScriptComponentType::PickPixelTest:
		scriptcomponent = new PickPixelTest;
		break;
	case eScriptComponentType::PlayerController:
		scriptcomponent = new PlayerController;
		break;
	case eScriptComponentType::PlayerMovementTest:
		scriptcomponent = new PlayerMovementTest;
		break;
	case eScriptComponentType::Rect2DInterpolation:
		scriptcomponent = new Rect2DInterpolation;
		break;
	case eScriptComponentType::RewindComponent:
		scriptcomponent = new RewindComponent;
		break;
	case eScriptComponentType::ShieldCop:
		scriptcomponent = new ShieldCop;
		break;
	case eScriptComponentType::ShiftController:
		scriptcomponent = new ShiftController;
		break;
	case eScriptComponentType::ShotGunAI:
		scriptcomponent = new ShotGunAI;
		break;
	case eScriptComponentType::SimpleDrawPoint:
		scriptcomponent = new SimpleDrawPoint;
		break;
	case eScriptComponentType::SimpleEditorCollider2D:
		scriptcomponent = new SimpleEditorCollider2D;
		break;
	case eScriptComponentType::SlashComponent:
		scriptcomponent = new SlashComponent;
		break;
	case eScriptComponentType::TestScript:
		scriptcomponent = new TestScript;
		break;
	case eScriptComponentType::TitleController:
		scriptcomponent = new TitleController;
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

