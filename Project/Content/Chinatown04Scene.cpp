#include "pch.h"
#include "Chinatown04Scene.h"
#include "Components.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>
#include "SimpleEditorCollider2D.h"
#include "GameManager.h"
#include "PathNode.h"
#include <Engine/Color.h>
#include "GameManager.h"
#include <Engine/SceneManager.h>
#include "Chinatown05Scene.h"
#include "CameraWall.h"
#include <Engine/Engine.h>
#include <Engine/GraphicDeviceDx11.h>
#include <Engine/ConstantBuffer.h>
#include "KissyfaceScene.h"
Chinatown04Scene::Chinatown04Scene()
	: KatanaScene(eKatanaSceneType::ChinaTown04)
{
}

Chinatown04Scene::~Chinatown04Scene()
{
}

void Chinatown04Scene::AddMapObject()
{
	GameObject* const tile = GameObjectBuilder::Default2D(L"Chanatown04TileMap");
	AddGameObject(tile, eLayerType::TileMap);		
}

void Chinatown04Scene::AddWallObject()
{
	//Wall
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(192, 48, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-128, 336, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-512, 688, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 288));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(192, 688, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 288));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0, 672, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2304, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1056, 496, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(192, 672));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-960, 256, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(384, 320));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-384, 384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(448, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(256, 384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(448, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-656, 80, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(224, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(384, -224, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1280, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(400, 96, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(352, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(944, 384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(1056, 544, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(192, 384));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-64, 96, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(192, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(800, 96, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(448, 64));
		AddGameObject(wall, eLayerType::Wall);
	}




	//Slope
	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-544, 128, -256, -160);
		AddGameObject(wall, eLayerType::LeftSlope);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(864, 416, 576, 128);

		AddGameObject(wall, eLayerType::RightSlope);
	}




	//Platform
	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(-544, 128, -160, 128);
		AddGameObject(platform, eLayerType::Platform);
	}

	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(-768, 416, -608, 416);
		AddGameObject(platform, eLayerType::Platform);
	}

	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(-96, 416, 32, 416);
		AddGameObject(platform, eLayerType::Platform);
	}

	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(32, 128, 160, 128);
		AddGameObject(platform, eLayerType::Platform);
	}

	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(480, 416, 864, 416);
		AddGameObject(platform, eLayerType::Platform);
	}

	//Small Triangle
	{
		//4pixel interpolate
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//wall->GetComponent<LineCollider2D>()->SetPoints(-224, 64, -160, 128); original
		wall->GetComponent<LineCollider2D>()->SetPoints(-220, 68, -160, 128);
		AddGameObject(wall, eLayerType::RightSlope);
	}
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-192, 66.5, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 5));
		AddGameObject(wall, eLayerType::Wall);
	}


	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//wall->GetComponent<LineCollider2D>()->SetPoints(480, 416, 544, 352); original
		wall->GetComponent<LineCollider2D>()->SetPoints(480, 416, 540, 356);
		AddGameObject(wall, eLayerType::LeftSlope);
	}
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(512, 354.5, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 5));
		AddGameObject(wall, eLayerType::Wall);
	}
}

void Chinatown04Scene::AddDoorObject()
{
	{
		GameObject* door = GameObjectBuilder::InstantiateClubDoor(this);
		door->GetComponent<Transform>()->SetPosition(-508, 480, 0);
	}

	{
		GameObject* door = GameObjectBuilder::InstantiateClubDoor(this);
		door->GetComponent<Transform>()->SetPosition(196, 480, 0);
	}

	{
		GameObject* door = GameObjectBuilder::InstantiateClubDoor(this);
		door->GetComponent<Transform>()->SetPosition(-124, 192, 0);
	}

	{
		GameObject* door = GameObjectBuilder::InstantiateClubDoor(this);
		door->GetComponent<Transform>()->SetPosition(196, -96, 0);
	}
}

void Chinatown04Scene::AddMonsterObject()
{
	/*{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Ganster, this);
		monster->GetComponent<Transform>()->SetPosition(-80, 150, 0);
	}*/

	{
		//GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Ganster, this);
		//monster->GetComponent<Transform>()->SetPosition(-500, 150, 0);

		//3Ãþ
		InstantiateMonster(eMonsterType::Shield, Vector2(-250, 453), true);
		InstantiateMonster(eMonsterType::Cop, Vector2(-50, 453), true);
		InstantiateMonster(eMonsterType::Shotgun, Vector2(500, 453), true);

		//2Ãþ
		InstantiateMonster(eMonsterType::Cop, Vector2(-600, 165), false);
		InstantiateMonster(eMonsterType::Shotgun, Vector2(-400, 165), false);
		InstantiateMonster(eMonsterType::Shield, Vector2(50, 165), false);

		//1Ãþ
		//InstantiateMonster(eMonsterType::Cop, Vector2(-600, 165), true);
		InstantiateMonster(eMonsterType::Cop, Vector2(0, -100), true);
		InstantiateMonster(eMonsterType::Shield, Vector2(400, -100), true);

	}
}

void Chinatown04Scene::AddObject()
{
	{
		GameObject* clear = new GameObject();

		clear->AddComponent<RectCollider2D>();
		clear->AddComponent<ClearController>();

		clear->GetComponent<RectCollider2D>()->SetSize(100.f, 100.f);

		clear->GetComponent<Transform>()->SetPosition(1000, -144, 0);

		AddGameObject(clear, eLayerType::Event);
	}
}

void Chinatown04Scene::AddLightObject()
{
	//Global Light
	{
		GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);
	}

	Vector3 difuse = Vector3(0.5f, 1.f, 1.f) * 2.4f;
	//float radius = 120.f;
	float radius = 140.f;

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-912, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-784, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-656, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}




	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-368, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-240, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-112, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(16, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(336, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(464, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(720, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(848, 528, 0);
		AddGameObject(light, eLayerType::Light);
	}

	//2

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-560, 272, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-432, 272, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-304, 272, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(80, 272, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(208, 272, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(336, 272, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(464, 272, 0);
		AddGameObject(light, eLayerType::Light);
	}



	//3
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-144, -16, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-16, -16, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(304, -16, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(432, -16, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(592, -16, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(720, -16, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(880, -16, 0);
		AddGameObject(light, eLayerType::Light);
	}
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(976, -16, 0);
		AddGameObject(light, eLayerType::Light);
	}
}

void Chinatown04Scene::AddCameraObject()
{
	{
		GameObject* mainCamera = GameObjectBuilder::AddCamera(this);
		Vector3 pos = mainCamera->GetComponent<Transform>()->GetPosition();
		mainCamera->GetComponent<Transform>()->SetPosition(-800, 450, pos.z);
	}

	//CameraWall
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->AddComponent<CameraWall>();

		wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Left);
		wall->GetComponent<Transform>()->SetPosition(-1072, 224, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(224, 1664));
		AddGameObject(wall, eLayerType::CameraWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->AddComponent<CameraWall>();

		wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Up);
		wall->GetComponent<Transform>()->SetPosition(-16, 848, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2336, 416));
		AddGameObject(wall, eLayerType::CameraWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->AddComponent<CameraWall>();

		wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Right);
		wall->GetComponent<Transform>()->SetPosition(1072, 224, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 1664));
		AddGameObject(wall, eLayerType::CameraWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->AddComponent<CameraWall>();

		wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Down);
		wall->GetComponent<Transform>()->SetPosition(-16, -416, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2336, 384));
		AddGameObject(wall, eLayerType::CameraWall);
	}
}

void Chinatown04Scene::AddUIObject()
{
#pragma region UI
	GameObjectBuilder::AddUI(this);
#pragma endregion
}

void Chinatown04Scene::AddPlayerObject()
{
	{
		GameObject* player = GameObjectBuilder::InstantiatePlayer(this);
		player->GetComponent<Transform>()->SetPosition(-800, 450, 0);

		GameManager::GetInstance()->SetPlayer(player);
	}

	PathInfo* const pathInfo = GameManager::GetInstance()->GetPathInfo();
	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);

		wall->GetComponent<LineCollider2D>()->SetPoints(-960, 416, 864, 416);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::BLUE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(864, 416, 960, 416);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}


	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(864, 416, 576, 128);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::YELLOW);
		wall->GetComponent<PathNode>()->SetType(eLayerType::RightSlope);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(64, 128, 576, 128);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::BLUE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(64, 128, 64, 224);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::WHITE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Elevator);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-544, 128, 64, 128);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-768, 128, -544, 128);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::BLUE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-544, 128, -256, -160);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::WHITE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::LeftSlope);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-256, -160, 64, -160);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::BLUE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(64, -160, 64, -64);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::WHITE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Elevator);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(64, -160, 1024, -160);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	//connect edge

	//0
	pathInfo->InsertEdge(0, 1, 1);

	//1
	pathInfo->InsertEdge(1, 0, 1);
	pathInfo->InsertEdge(1, 2, 1);

	//2 right slope
	pathInfo->InsertEdge(2, 1, 1);
	pathInfo->InsertEdge(2, 3, 1);

	//3
	pathInfo->InsertEdge(3, 2, 1);
	pathInfo->InsertEdge(3, 4, 1);

	//4 elevator
	pathInfo->InsertEdge(4, 3, 1);
	pathInfo->InsertEdge(4, 5, 1);
	pathInfo->InsertEdge(4, 9, 0);

	//5
	pathInfo->InsertEdge(5, 4, 1);
	pathInfo->InsertEdge(5, 6, 1);

	//6
	pathInfo->InsertEdge(6, 5, 1);
	pathInfo->InsertEdge(6, 7, 1);

	//7 left slope
	pathInfo->InsertEdge(7, 6, 1);
	pathInfo->InsertEdge(7, 8, 1);

	//8
	pathInfo->InsertEdge(8, 7, 1);
	pathInfo->InsertEdge(8, 9, 1);

	//9 elevator
	pathInfo->InsertEdge(9, 8, 1);
	pathInfo->InsertEdge(9, 10, 1);
	pathInfo->InsertEdge(9, 4, 0);

	//10
	pathInfo->InsertEdge(10, 9, 1);

	pathInfo->Dijikstra(1, 10);
}

Scene* Chinatown04Scene::Clone()
{
	return new Chinatown04Scene();
}

KatanaScene* Chinatown04Scene::GetNextScene()
{
	return nullptr;
}
