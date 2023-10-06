#include "pch.h"
#include "Chinatown01Scene.h"
#include "TItleScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "UIEffect.h"
#include "Bugiman.h"
#include "PlayerMovementTest.h"
#include "ShiftController.h"
#include <Engine/Engine.h>
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include "LerpTest.h"
#include <Engine/CollisionManagement2D.h>
#include "InputMovementTest.h"
#include "ChildTest.h"
#include "ParentTest.h"
#include "NoiseTest.h"
#include "PlayerController.h"
#include "PlayerFSM.h"
#include "GridPainter.h"
#include <Engine/Color.h>
#include "PickPixelTest.h"
#include "Rect2DInterpolation.h"
#include "SimpleEditorCollider2D.h"
#include "GameManager.h"
#include "PathNode.h"
#include "Chinatown04Scene.h"
#include "CameraWall.h"
#include "RewindComponent.h"



#include <Engine/ConstantBuffer.h>
#include <Engine/Engine.h>
#include <Engine/GraphicDeviceDx11.h>

#include "GalssWindow.h"

Chinatown01Scene::Chinatown01Scene()
{
	SetBackgroundColor(Vector4(0.5294f, 0.5254f, 0.7843f, 1.f));

	mCollisionManagement2D->TurnOffAllCollisionLayer();

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Platform);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Platform);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Door);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Door);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Door, eLayerType::PlayerAttack);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::PlayerAttack);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::PlayerAttack);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::PlayerAttack);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Camera, eLayerType::CameraWall);


	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Wall, eLayerType::PlayerAttack);


	{
		tWaveInfo waveInfo = {};

		waveInfo.WaveXPower = 0.f;
		waveInfo.WaveYPower = 0.f;
		waveInfo.WaveSpeed = 0.f;

		gGraphicDevice->PassCB(eCBType::Wave, sizeof(waveInfo), &waveInfo);
		gGraphicDevice->BindCB(eCBType::Wave, eShaderBindType::PS);
	}

//#pragma region Material
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_1);
//		gResourceManager->Insert(L"Chanatown05BackGround01", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_2);
//		gResourceManager->Insert(L"Chanatown05BackGround02", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_3);
//		gResourceManager->Insert(L"Chanatown05BackGround03", material);
//	}
//
//	{
//		Material* const material =
//			MaterialBuilder::Sprite2D(
//				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_Tilemap);
//		gResourceManager->Insert(L"Chanatown01TileMap", material);
//	}
//#pragma endregion

#pragma region MapObj
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"Chanatown05BackGround01");
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-580, 560.f, 500.f);

		AddGameObject(obj, eLayerType::BackGround);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"Chanatown05BackGround02");

		obj->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-640, 560.f, 600.f);


		AddGameObject(obj, eLayerType::BackGround);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"Chanatown05BackGround03");

		obj->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-640, 560.f, 700.f);

		AddGameObject(obj, eLayerType::BackGround);
	}
#pragma endregion

#pragma region Editor
	//{
	//	GameObject* const testObj = new GameObject();
	//	testObj->AddComponent<SimpleEditorCollider2D>();
	//	AddGameObject(testObj, eLayerType::Default);
	//}
#pragma endregion

#pragma region WallObj
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-2224, 496, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(96, 416));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1888, 352, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(768, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1632, 656, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1280, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1024, 816, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 544));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1856, 800, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 512));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-160, 80, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2112, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(48, 624, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(544, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-64, 368, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(320, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(560, 368, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(672, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(560, 736, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 768));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(176, 1104, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(800, 352));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-192, 1056, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 448));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-224, 976, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 224));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-256, 1024, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-192, 496, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 288));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-240, 624, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(32, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1056, 384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(128, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1024, 336, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-192, 352, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 192));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(256, 320, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-1504.000000, 416.000000, -1216.000000, 128.000000);
		AddGameObject(wall, eLayerType::LeftSlope);
	}

	//³ªÁß¿¡Ãß°¡µÊ
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1152, 353.5f, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 3));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-1182, 354, -1120, 416);
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		AddGameObject(wall, eLayerType::RightSlope);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-1504, 416, -1120, 416);
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		AddGameObject(wall, eLayerType::Platform);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(96, 416, 224, 416);
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		AddGameObject(wall, eLayerType::Platform);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(320, 672, 480, 672);
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		AddGameObject(wall, eLayerType::Platform);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-416, 384, -224, 384);
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		AddGameObject(wall, eLayerType::Platform);
	}



#pragma endregion

#pragma region Monster	

	//1Ãþ
	//monster
	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Cop, this);
		monster->GetComponent<Transform>()->SetPosition(-500, 150, 0);
		monster->GetComponent<Transform>()->SetFlipx(true);
	}

	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Shotgun, this);
		monster->GetComponent<Transform>()->SetPosition(-600, 150, 0);
		monster->GetComponent<Transform>()->SetFlipx(true);
	}

	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Shotgun, this);
		monster->GetComponent<Transform>()->SetPosition(-700, 150, 0);
		monster->GetComponent<Transform>()->SetFlipx(true);
	}

	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Shield, this);
		monster->GetComponent<Transform>()->SetPosition(-850, 150, 0);
		monster->GetComponent<Transform>()->SetFlipx(true);
	}

	//monster
	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Cop, this);
		monster->GetComponent<Transform>()->SetPosition(100, 150, 0);
		monster->GetComponent<Transform>()->SetFlipx(true);
	}

	//monster
	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Shield, this);
		monster->GetComponent<Transform>()->SetPosition(550, 150, 0);
		monster->GetComponent<Transform>()->SetFlipx(true);
	}


	//2Ãþ ¿ÞÂÊ
	//monster
	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Shield, this);
		monster->GetComponent<Transform>()->SetPosition(-1700, 450, 0);
		monster->GetComponent<Transform>()->SetFlipx(true);
	}

	//2Ãþ ¿À¸¥ÂÊ
	//monster
	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Cop, this);
		monster->GetComponent<Transform>()->SetPosition(0, 450, 0);
	}

	//monster
	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Shotgun, this);
		monster->GetComponent<Transform>()->SetPosition(350, 450, 0);
		monster->GetComponent<Transform>()->SetFlipx(true);
	}

	//3Ãþ
	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Cop, this);
		monster->GetComponent<Transform>()->SetPosition(200, 700, 0);
	}

#pragma endregion	

#pragma region Tile Map
	//tile map
	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"Chanatown01TileMap");
		/*tile->AddComponent<GridPainter>();

		tile->GetComponent<GridPainter>()->SetCellSize(32);
		tile->GetComponent<GridPainter>()->SetCellCount(XMUINT2(200, 200));
		tile->GetComponent<GridPainter>()->SetColor(helper::Color::YELLOW);
		tile->GetComponent<GridPainter>()->TurnOffDraw();*/

		AddGameObject(tile, eLayerType::TileMap);
	}
#pragma endregion

#pragma region Light
	{
		GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);
	}
	Vector3 difuse = Vector3(0.5f, 1.35f, 0.8f) * 1.4f;
	//float radius = 120.f;
	float radius = 140.f;

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-2000, 520, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-1650, 520, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-1400, 520, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-1150, 520, 0);
		AddGameObject(light, eLayerType::Light);
	}

	difuse = Vector3(1.5f, 1.15f, 0.4f) * 1.4f;
	radius = 400.f;

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-550, 650, 0);
		AddGameObject(light, eLayerType::Light);
	}

	difuse = Vector3(1.5f, 1.15f, 0.4f) * 1.4f;
	radius = 240.f;
	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(100, 250, 0);
		AddGameObject(light, eLayerType::Light);
	}
#pragma endregion

#pragma region Camera
	{
		//GameObjectBuilder::AddUI(this);
		GameObject* mainCamera = GameObjectBuilder::AddCamera(this);

		//mainCamera->AddComponent<AudioListener>();

		Vector3 pos = mainCamera->GetComponent<Transform>()->GetPosition();
		mainCamera->GetComponent<Transform>()->SetPosition(-1568, 452, pos.z);		
	}


	//Camera Wall
	{
		{
			GameObject* const wall = new GameObject();
			//[RectCollider]
			wall->AddComponent<RectCollider2D>();
			wall->AddComponent<CameraWall>();

			wall->GetComponent<Transform>()->SetPosition(-720, -64, 0);
			wall->GetComponent<RectCollider2D>()->SetSize(Vector2(3232, 192));
			wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Down);
			

			AddGameObject(wall, eLayerType::CameraWall);
		}

		{
			GameObject* const wall = new GameObject();
			//[RectCollider]
			wall->AddComponent<RectCollider2D>();
			wall->AddComponent<CameraWall>();

			wall->GetComponent<Transform>()->SetPosition(-2272, 624, 0);
			wall->GetComponent<RectCollider2D>()->SetSize(Vector2(128, 1632));
			wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Left);

			AddGameObject(wall, eLayerType::CameraWall);
		}

		{
			GameObject* const wall = new GameObject();
			//[RectCollider]
			wall->AddComponent<RectCollider2D>();
			wall->AddComponent<CameraWall>();

			wall->GetComponent<Transform>()->SetPosition(864, 624, 0);
			wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 1568));
			wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Right);
			AddGameObject(wall, eLayerType::CameraWall);
		}


	}

	
#pragma endregion

#pragma region UI
	{
		GameObjectBuilder::AddUI(this);
	}
#pragma endregion

#pragma region Door

	{
		GameObject* door = GameObjectBuilder::InstantiateDoor(this);
		door->GetComponent<Transform>()->SetPosition(-1854, 480, 0);
	}

	{
		GameObject* door = GameObjectBuilder::InstantiateDoor(this);
		door->GetComponent<Transform>()->SetPosition(-1024, 192, 0);
	}

	{
		GameObject* door = GameObjectBuilder::InstantiateDoor(this);
		door->GetComponent<Transform>()->SetPosition(-192, 192, 0);
	}

	{
		GameObject* door = GameObjectBuilder::InstantiateDoor(this);
		door->GetComponent<Transform>()->SetPosition(258, 192, 0);
	}
	

#pragma endregion

#pragma region Glass

	GameObject* glass = new GameObject();
	glass->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	glass->GetComponent<Transform>()->SetPosition(-1000, 480, 0);
	

	glass->AddComponent<RectCollider2D>();
	glass->AddComponent<Animator2D>();		
	glass->AddComponent<GalssWindow>();
	glass->AddComponent<RewindComponent>();

	glass->GetComponent<RectCollider2D>()->SetSize(5.f, 70.f);

	Animator2D* anim = glass->GetComponent<Animator2D>();
	Texture* atlas = gResourceManager->FindOrNullByEnum<Texture>(eResTexture::Atlas_Particle_particle);
	anim->CreateAnimation(L"GlassWindow", atlas, 1, XMUINT2(5, 793), XMUINT2(2, 64), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
	anim->Play(L"GlassWindow", true);

	AddGameObject(glass, eLayerType::Wall);
#pragma endregion


#pragma region PostProcess
	{
		GameObject* const postProcess = new GameObject();

		postProcess->AddComponent<SpriteRenderer>();

		postProcess->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"GrayPostProcess"));

		postProcess->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();

		AddGameObject(postProcess, eLayerType::Default);
	}

	{
		GameObject* const postProcess = new GameObject();

		postProcess->AddComponent<SpriteRenderer>();
		postProcess->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"WavePostProcess"));

		AddGameObject(postProcess, eLayerType::Default);
	}
#pragma endregion

}

Chinatown01Scene::~Chinatown01Scene()
{
	GameManager::deleteInstance();
}

void Chinatown01Scene::initialize()
{
	GameManager::initialize();
	GameManager::GetInstance()->GetRewindManager()->SetRewindState(eRewindState::Record);
	GameManager::GetInstance()->GetRewindManager()->Initialize(this);
	GameManager::GetInstance()->GetEffectManager()->Initialize(this);

#pragma region Player
	{
		GameObject* player = GameObjectBuilder::InstantiatePlayer(this);
		player->GetComponent<Transform>()->SetPosition(-2000, 450, 0);

		GameManager::GetInstance()->SetPlayer(player);
	}
#pragma endregion
#pragma region PathNode
		PathInfo* const pathInfo = GameManager::GetInstance()->GetPathInfo();

		{
			GameObject* const wall = new GameObject();
			//[LineCollider]
			wall->AddComponent<LineCollider2D>();
			wall->AddComponent<PathNode>();

			pathInfo->AddPathNode(wall->GetComponent<PathNode>());

			wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
			wall->GetComponent<LineCollider2D>()->SetPoints(-2176, 416, -1504, 416);

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
			wall->GetComponent<LineCollider2D>()->SetPoints(-1504, 416, -992, 416);

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
			wall->GetComponent<LineCollider2D>()->SetPoints(-1504, 416, -1216, 128);


			wall->GetComponent<LineCollider2D>()->TurnOnVisible();
			wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::YELLOW);
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
			wall->GetComponent<LineCollider2D>()->SetPoints(-1216, 128, 96, 128);

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
			wall->GetComponent<LineCollider2D>()->SetPoints(96, 128, 96, 224);

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
			wall->GetComponent<LineCollider2D>()->SetPoints(96, 128, 864, 128);

			wall->GetComponent<LineCollider2D>()->TurnOnVisible();
			wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
			wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

			AddGameObject(wall, eLayerType::PathNode);
		}

		//2Ãþ
		{
			GameObject* const wall = new GameObject();

			//[LineCollider]
			wall->AddComponent<LineCollider2D>();
			wall->AddComponent<PathNode>();

			pathInfo->AddPathNode(wall->GetComponent<PathNode>());

			wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
			wall->GetComponent<LineCollider2D>()->SetPoints(-160, 416, 96, 416);


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
			wall->GetComponent<LineCollider2D>()->SetPoints(96, 416, 96, 512);

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
			wall->GetComponent<LineCollider2D>()->SetPoints(96, 416, 480, 416);


			wall->GetComponent<LineCollider2D>()->TurnOnVisible();
			wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::BLUE);
			wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

			AddGameObject(wall, eLayerType::PathNode);
		}

		//3Ãþ
		{
			GameObject* const wall = new GameObject();

			//[LineCollider]
			wall->AddComponent<LineCollider2D>();
			wall->AddComponent<PathNode>();

			pathInfo->AddPathNode(wall->GetComponent<PathNode>());

			wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
			wall->GetComponent<LineCollider2D>()->SetPoints(-224, 672, 96, 672);

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
			wall->GetComponent<LineCollider2D>()->SetPoints(96, 672, 96, 768);

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
			wall->GetComponent<LineCollider2D>()->SetPoints(96, 672, 480, 672);

			wall->GetComponent<LineCollider2D>()->TurnOnVisible();
			wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
			wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

			AddGameObject(wall, eLayerType::PathNode);
		}





		//connect Edge
		//0
		pathInfo->InsertEdge(0, 1, 1);
		pathInfo->InsertEdge(0, 2, 1);

		//1
		pathInfo->InsertEdge(1, 0, 1);

		//2
		pathInfo->InsertEdge(2, 0, 1);
		pathInfo->InsertEdge(2, 3, 1);

		//3
		pathInfo->InsertEdge(3, 2, 1);
		pathInfo->InsertEdge(3, 4, 1);

		//4 elevator
		pathInfo->InsertEdge(4, 3, 1);
		pathInfo->InsertEdge(4, 5, 1);
		pathInfo->InsertEdge(4, 7, 1);

		//5 
		pathInfo->InsertEdge(5, 4, 1);

		//6
		pathInfo->InsertEdge(6, 7, 1);

		//7 elevator
		pathInfo->InsertEdge(7, 6, 1);
		pathInfo->InsertEdge(7, 8, 1);
		pathInfo->InsertEdge(7, 4, 1);
		pathInfo->InsertEdge(7, 10, 1);

		//8
		pathInfo->InsertEdge(8, 7, 1);

		//9 
		pathInfo->InsertEdge(9, 10, 1);

		//10 elevator
		pathInfo->InsertEdge(10, 9, 1);
		pathInfo->InsertEdge(10, 11, 1);
		pathInfo->InsertEdge(10, 7, 1);

		//11 
		pathInfo->InsertEdge(11, 10, 1);



	#pragma endregion	
	Scene::initialize();
	TimeManager::GetInstance()->ResetTime();
	//TimeManager::GetInstance()->ResetTime();
}

void Chinatown01Scene::update()
{
	Scene::update();

	if (gInput->GetKeyDown(eKeyCode::P))
	{
		SceneManager::GetInstance()->RegisterLoadScene(new Chinatown04Scene);
	}
}

void Chinatown01Scene::lateUpdate()
{
	Scene::lateUpdate();

	GameManager::GetInstance()->GetRewindManager()->LateUpdate();
	GameManager::GetInstance()->GetEventManager()->LateUpdate();
}

