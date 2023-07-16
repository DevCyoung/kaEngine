#include "pch.h"
#include "Collide2DTestScene.h"
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


Collide2DTestScene::Collide2DTestScene()
	: Scene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Bullet);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Mouse);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Satellite);	
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Mouse, eLayerType::Satellite);
	
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
		
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
		
		obj->GetComponent<Transform>()->SetPosition(-500.f, 200.f, 1.f);
		obj->GetComponent<RectCollider2D>()->SetScale(Vector2(200.f, 100.f));
		obj->GetComponent<PlayerMovementTest>()->mbRight = false;
		
		AddGameObject(obj, eLayerType::Default);

		{
			GameObject* const child = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
		
			child->AddComponent<RectCollider2D>();
			child->AddComponent<PlayerMovementTest>();
		
			child->GetComponent<PlayerMovementTest>()->mbRight = false;
			child->GetComponent<Transform>()->SetPosition(300.f, 0.f, 1.f);
			child->GetComponent<RectCollider2D>()->SetScale(Vector2(100.f, 100.f));
		
			child->SetParent(obj);
			AddGameObject(child, eLayerType::Default);
		
			{
				GameObject* const child2 = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
		
				child2->AddComponent<RectCollider2D>();
				child2->AddComponent<PlayerMovementTest>();
		
				child2->GetComponent<PlayerMovementTest>()->mbRight = false;
				child2->GetComponent<Transform>()->SetPosition(300.f, 0.f, 1.f);
				child2->GetComponent<RectCollider2D>()->SetScale(Vector2(100.f, 100.f));
		
				child2->SetParent(child);
				AddGameObject(child2, eLayerType::Default);
		
				{
					GameObject* const child3 = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
		
					child3->AddComponent<CircleCollider2D>();
					child3->AddComponent<PlayerMovementTest>();
		
					child3->GetComponent<Transform>()->SetPosition(-300.f, 0.f, 1.f);
					child3->GetComponent<CircleCollider2D>()->SetRdius(30.f);
					child3->GetComponent<PlayerMovementTest>()->mbRight = false;
		
					child3->SetParent(child2);
					AddGameObject(child3, eLayerType::Satellite);
				}
		
				{
					GameObject* const child3 = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
		
					child3->AddComponent<CircleCollider2D>();
					child3->AddComponent<PlayerMovementTest>();
		
					child3->GetComponent<Transform>()->SetPosition(300.f, 0.f, 1.f);
					child3->GetComponent<CircleCollider2D>()->SetRdius(30.f);
					child3->GetComponent<PlayerMovementTest>()->mbRight = false;
		
					child3->SetParent(child2);
					AddGameObject(child3, eLayerType::Satellite);
				}
		
				{
					GameObject* const child3 = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
		
					child3->AddComponent<CircleCollider2D>();
					child3->AddComponent<PlayerMovementTest>();
		
					child3->GetComponent<Transform>()->SetPosition(0.f, 300.f, 1.f);
					child3->GetComponent<CircleCollider2D>()->SetRdius(30.f);
					child3->GetComponent<PlayerMovementTest>()->mbRight = false;
		
					child3->SetParent(child2);
					AddGameObject(child3, eLayerType::Satellite);
				}
		
				{
					GameObject* const child3 = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
		
					child3->AddComponent<CircleCollider2D>();
					child3->AddComponent<PlayerMovementTest>();
		
					child3->GetComponent<Transform>()->SetPosition(0.f, -300.f, 1.f);
					child3->GetComponent<CircleCollider2D>()->SetRdius(30.f);
					child3->GetComponent<PlayerMovementTest>()->mbRight = false;
		
					child3->SetParent(child2);
					AddGameObject(child3, eLayerType::Satellite);
		
					{
						GameObject* const child4 = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
		
						child4->AddComponent<RectCollider2D>();
						child4->AddComponent<PlayerMovementTest>();
		
						child4->GetComponent<Transform>()->SetPosition(500.f, 0.f, 1.f);
						child4->GetComponent<RectCollider2D>()->SetScale(Vector2(300.f, 200.f));
						child4->GetComponent<PlayerMovementTest>()->mbRight = false;
		
						child4->SetParent(child3);
						AddGameObject(child4, eLayerType::Default);
					}
				}
		
			}
		
		
		}
	}

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(300.f, 0.f, 1.f);
		obj->GetComponent<RectCollider2D>()->SetScale(Vector2(500.f, 100.f));
		obj->GetComponent<PlayerMovementTest>()->mbRight = false;
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(-300.f, -300.f, 1.f);
		obj->GetComponent<RectCollider2D>()->SetScale(Vector2(500.f, 20.f));
		obj->GetComponent<PlayerMovementTest>()->mbRight = false;
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(-100.f, -500.f, 1.f);
		obj->GetComponent<RectCollider2D>()->SetScale(Vector2(1000.f, 100.f));
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(150, 150, 1.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, 10.f);
		obj->GetComponent<RectCollider2D>()->SetScale(Vector2(500, 20));
		obj->GetComponent<PlayerMovementTest>()->mbRight = true;
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");
	
		obj->AddComponent<RectCollider2D>();
		obj->AddComponent<PlayerMovementTest>();
	
		obj->GetComponent<Transform>()->SetPosition(450, -350, 1.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, 10.f);
		obj->GetComponent<RectCollider2D>()->SetScale(Vector2(400, 20));
		obj->GetComponent<PlayerMovementTest>()->mbRight = false;
	
		AddGameObject(obj, eLayerType::Default);
	}



	//UI
	const Vector2 screenSize = gEngine->GetRenderTargetSize();
	const float hudPosY = gEngine->GetRenderTargetSize().y / 2.f - 23.f;

	//UI UP Hud
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHud");
	
		const Vector2 pos = helper::RenderTargetToWorldUI(Vector2(screenSize.x / 2.f, 23.f), screenSize);
	
		obj->GetComponent<Transform>()->SetPosition(Vector3(pos.x, pos.y, 10.f));
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	constexpr float timerPosX = -8.f;
	
	//UI HudTimer
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHudTimer");
	
		obj->GetComponent<Transform>()->SetPosition(timerPosX, hudPosY + 2.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Timer
	{
	
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UITimer");
	
		obj->AddComponent<UIEffect>();
	
		obj->GetComponent<Transform>()->SetPosition(timerPosX + 16.f, hudPosY + 6.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UIShift
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIShift00");
	
		obj->AddComponent<ShiftController>();
	
		obj->GetComponent<Transform>()->SetPosition(-455.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Battery
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIBattery");
	
		obj->GetComponent<Transform>()->SetPosition(-561.f, hudPosY - 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Hud Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHudItem");
	
		obj->GetComponent<Transform>()->SetPosition(+560.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Left Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UILeftItem");
	
		obj->GetComponent<Transform>()->SetPosition(528.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Right Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIRightItem");
	
		obj->GetComponent<Transform>()->SetPosition(592.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Left Click
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UILeftClick");
	
		obj->GetComponent<Transform>()->SetPosition(550.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}
	
	//UI Right Click
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIRightClick");
	
		obj->GetComponent<Transform>()->SetPosition(610.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
	
		AddGameObject(obj, eLayerType::UI);
	}

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");

		obj->AddComponent<CircleCollider2D>();
		obj->AddComponent<CursorMovement>();

		obj->GetComponent<CircleCollider2D>()->SetRdius(50.f);

		AddGameObject(obj, eLayerType::Mouse);
	}	

	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();

		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();

		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		mainCamera->GetComponent<Camera>()->SetProjectionType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);

		AddGameObject(mainCamera, eLayerType::Default);
	}

	//UI Camera
	{
		GameObject* const uiCamera = new GameObject();

		uiCamera->AddComponent<Camera>();

		uiCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		uiCamera->GetComponent<Camera>()->SetProjectionType(eCameraPriorityType::UI);
		uiCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		uiCamera->GetComponent<Camera>()->TurnOffAllLayer();
		uiCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);

		AddGameObject(uiCamera, eLayerType::Default);
	}
}

Collide2DTestScene::~Collide2DTestScene()
{
}
