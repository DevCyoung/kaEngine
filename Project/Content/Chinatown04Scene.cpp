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

Chinatown04Scene::Chinatown04Scene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Platform);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Platform);

	//PathNode

	GameManager::initialize();

	GameManager::GetInstance()->GetRewindManager()->SetRewindState(eRewindState::Record);

#pragma region Material
	{
		Material* const tileMaterial =
			MaterialBuilder::LightSprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown04_Tilemap);
		gResourceManager->Insert(L"Chanatown04TileMap", tileMaterial);
	}
#pragma endregion

#pragma region MapObj
	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"Chanatown04TileMap");

		tile->GetComponent<Transform>()->SetPosition(0, 0, 100);
		//tile->AddComponent<Chinatown04Controller>();

		AddGameObject(tile, eLayerType::TileMap);
	}
#pragma endregion

#pragma region Editor
	/*{
		GameObject* const testObj = new GameObject();
		testObj->AddComponent<SimpleEditorCollider2D>();
		AddGameObject(testObj, eLayerType::Default);
	}*/
#pragma endregion

#pragma region ColliderObj



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



	//CameraWall
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1072, 224, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(224, 1664));
		AddGameObject(wall, eLayerType::CamearaWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-16, 848, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2336, 416));
		AddGameObject(wall, eLayerType::CamearaWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(1072, 224, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 1664));
		AddGameObject(wall, eLayerType::CamearaWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-16, -416, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2336, 384));
		AddGameObject(wall, eLayerType::CamearaWall);
	}





#pragma endregion

#pragma region PathNode

	PathInfo* const pathInfo =  GameManager::GetInstance()->GetPathInfo();

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
		wall->GetComponent<LineCollider2D>()->SetPoints(64, 128, 64, 256);

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
		wall->GetComponent<LineCollider2D>()->SetPoints(64, -160, 64, -32);

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

#pragma endregion


#pragma region Light

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
#pragma endregion

	{
		GameObject* lgiht = GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);
		lgiht->GetComponent<Light2D>()->SetLightDiffuse(Vector3::One);
	}

#pragma region Monster

	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Ganster, this);
		monster->GetComponent<Transform>()->SetPosition(-80, 150, -30);
	}

	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Ganster, this);
		monster->GetComponent<Transform>()->SetPosition(-460, 250, -30);
	}

	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Ganster, this);
		monster->GetComponent<Transform>()->SetPosition(600, 450, -30);
	}

	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Ganster, this);
		monster->GetComponent<Transform>()->SetPosition(-100, -150, -30);
	}

#pragma endregion


	{
		GameObject* player = GameObjectBuilder::InstantiatePlayer(this);
		player->GetComponent<Transform>()->SetPosition(0, 0, -30);

		GameManager::GetInstance()->SetPlayer(player);
	}

	{
		GameObjectBuilder::AddUI(this);
		GameObjectBuilder::AddCamera(this);
	}
}

Chinatown04Scene::~Chinatown04Scene()
{
	GameManager::deleteInstance();
}

void Chinatown04Scene::lateUpdate()
{
	Scene::lateUpdate();

	GameManager::GetInstance()->GetRewindManager()->LateUpdate();
}
