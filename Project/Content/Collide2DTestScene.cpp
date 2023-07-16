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

		obj->GetComponent<Transform>()->SetPosition(300.f, 0.f, 1.f);
		obj->GetComponent<RectCollider2D>()->SetScale(Vector2(500.f, 100.f));
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

	const Vector2 screenSize = gEngine->GetRenderTargetSize();

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
