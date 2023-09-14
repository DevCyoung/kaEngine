#include "pch.h"
#include "GameObjectBuilder.h"
#include "Components.h"
#include "ResourceManager.h"
#include <Engine/Engine.h>
#include "PlayerController.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "ShiftController.h"
#include "UIEffect.h"
#include <Engine/Scene.h>
#include <Engine/EngineMath.h>
#include "FolowPlayer.h"
#include <Engine/AfterImage.h>
#include "SimpleDrawPoint.h"
#include "GangsterAI.h"
#include "PlayerPath.h"

GameObject* GameObjectBuilder::Default2D(const std::wstring& materialName)
{
	GameObject* const obj = new GameObject();
	obj->AddComponent<SpriteRenderer>();

	SpriteRenderer* const spriteRenderer = obj->GetComponent<SpriteRenderer>();
	spriteRenderer->SetMesh(gResourceManager->FindOrNull<Mesh>(L"FillRect2D"));
	spriteRenderer->SetMaterial(gResourceManager->FindOrNull<Material>(materialName));

	return obj;
}

GameObject* GameObjectBuilder::Player()
{
	GameObject* const player = new GameObject();
	player->SetName(L"Player");

	
	player->AddComponent<Rigidbody2D>();
	player->AddComponent<AfterImage>();
	player->AddComponent<Rect2DInterpolation>();
	player->AddComponent<RectCollider2D>();
	player->AddComponent<PlayerPath>();

	//Animation
	{
		player->GetComponent<Transform>()->SetPosition(0.f, 160.f, -1.f);

		player->AddComponent<Animator2D>();
		player->AddComponent<PlayerController>();

		player->GetComponent<PlayerController>()->SetFSM(new PlayerFSM(player));

		Animator2D* const anim = player->GetComponent<Animator2D>();
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Player_zero);

		anim->CreateAnimation(L"Attack", atlas, 7,
			XMUINT2(5, 34), XMUINT2(62, 42), XMUINT2(10, 10), XMINT2(0, 3), 0.0325f);

		anim->CreateAnimation(L"Roll", atlas, 7,
			XMUINT2(5, 1718), XMUINT2(48, 33), XMUINT2(10, 10), XMINT2(0, -1), 0.06f);

		anim->CreateAnimation(L"DoorBreakFull", atlas, 10,
			XMUINT2(5, 198), XMUINT2(50, 44), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);

		anim->CreateAnimation(L"Fall", atlas, 4,
			XMUINT2(5, 281), XMUINT2(42, 48), XMUINT2(10, 10), XMINT2(-3, 6), 0.06f);

		anim->CreateAnimation(L"Jump", atlas, 4,
			XMUINT2(5, 826), XMUINT2(32, 42), XMUINT2(10, 10), XMINT2(-3, 3), 0.08f);

		anim->CreateAnimation(L"Idle", atlas, 11,
			XMUINT2(5, 681), XMUINT2(36, 35), XMUINT2(10, 10), XMINT2(0, 0), 0.1f);

		anim->CreateAnimation(L"IdleToRun", atlas, 4,
			XMUINT2(5, 755), XMUINT2(44, 32), XMUINT2(10, 10), XMINT2(0, -2), 0.08f);

		anim->CreateAnimation(L"Run", atlas, 10,
			XMUINT2(5, 1790), XMUINT2(44, 32), XMUINT2(10, 10), XMINT2(0, -2), 0.07f);

		anim->CreateAnimation(L"RunToIdle", atlas, 5,
			XMUINT2(5, 1861), XMUINT2(52, 36), XMUINT2(10, 10), XMINT2(0, 0), 0.085f);

		anim->CreateAnimation(L"Flip", atlas, 11,
			XMUINT2(5, 1137), XMUINT2(50, 45), XMUINT2(10, 10), XMINT2(0, 0), 0.065f);

		anim->CreateAnimation(L"PlaySong", atlas, 31,
			XMUINT2(5, 1221), XMUINT2(36, 39), XMUINT2(10, 10), XMINT2(0, 0), 0.09f);

		anim->CreateAnimation(L"PostCrouch", atlas, 2,
			XMUINT2(5, 1560), XMUINT2(36, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.09f);

		anim->CreateAnimation(L"PreCrouch", atlas, 2,
			XMUINT2(5, 1639), XMUINT2(36, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.09f);

		/*anim->CreateAnimation(L"Crouch", atlas, 1,
			XMUINT2(5, 2005), XMUINT2(36, 40), XMUINT2(10, 10), XMINT2(0, 5800), 0.09f);*/

		anim->CreateAnimation(L"WallSlide", atlas, 1,
			XMUINT2(5, 2250), XMUINT2(46, 42), XMUINT2(10, 10), XMINT2(3, 0), 0.09f);

		anim->CreateAnimation(L"HurtGround", atlas, 6,
			XMUINT2(5, 532), XMUINT2(57, 25), XMUINT2(10, 10), XMINT2(0, -5), 0.09f);

		anim->CreateAnimation(L"HurtRecover", atlas, 9,
			XMUINT2(5, 596), XMUINT2(56, 46), XMUINT2(10, 10), XMINT2(1, 5), 0.09f);


		player->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);
	}

	//Collider
	{
		player->GetComponent<RectCollider2D>()->SetSize(22.f, 44.f);
		player->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 4.f));
	}

	player->GetComponent<Animator2D>()->Play(L"Idle", true);

	//Rigidbody
	player->GetComponent<Rigidbody2D>()->TurnOnGravity();
	player->GetComponent<Rigidbody2D>()->SetGravityAccel(1800.f);

	//Collider
	//player->GetComponent<RectCollider2D>()->SetSize(22.f, 44.f);
	//player->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 4.f));


	return player;
}

GameObject* GameObjectBuilder::InstantiateMonster(const eMonsterType type, Scene* const scene)
{
	(void)type;
	GameObject* const monster = new GameObject();	
	monster->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);	

	monster->SetName(L"Monster");	
	monster->AddComponent<Rigidbody2D>();	
	monster->AddComponent<Rect2DInterpolation>();
	monster->AddComponent<RectCollider2D>();
	monster->AddComponent<Animator2D>();
	monster->AddComponent<GangsterAI>();
	monster->AddComponent<PlayerPath>();

	//Collider
	{
		monster->GetComponent<RectCollider2D>()->SetSize(22.f, 44.f);
		monster->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 4.f));
	}

	//Rigidbody
	{
		monster->GetComponent<Rigidbody2D>()->TurnOnGravity();
		monster->GetComponent<Rigidbody2D>()->SetGravityAccel(1800.f);
	}


	scene->AddGameObject(monster, eLayerType::Monster);

#pragma region GansterAnimation

	//Animation
	{				
		Animator2D* const anim = monster->GetComponent<Animator2D>();
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Gangster_gangster);

		anim->CreateAnimation(L"Fall", atlas, 12, XMUINT2(5, 34), XMUINT2(42, 41), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"HurtFly", atlas, 2, XMUINT2(5, 114), XMUINT2(38, 34), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"HurtGround", atlas, 14, XMUINT2(5, 187), XMUINT2(44, 34), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"Idle", atlas, 8, XMUINT2(5, 304), XMUINT2(49, 50), XMUINT2(10, 10), XMINT2(0, 7), 0.125f);

		anim->CreateAnimation(L"Run", atlas, 10, XMUINT2(5, 393), XMUINT2(45, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.07f);

		anim->CreateAnimation(L"Turn", atlas, 6, XMUINT2(5, 472), XMUINT2(48, 42), XMUINT2(10, 10), XMINT2(0, 3), 0.0825f);

		anim->CreateAnimation(L"Walk", atlas, 8, XMUINT2(5, 553), XMUINT2(34, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.0825f);

		anim->CreateAnimation(L"Whip", atlas, 6, XMUINT2(5, 632), XMUINT2(48, 35), XMUINT2(10, 10), XMINT2(2, 0), 0.0825f);

		anim->CreateAnimation(L"Aim", atlas, 1, XMUINT2(5, 754), XMUINT2(42, 50), XMUINT2(10, 10), XMINT2(0, 7), 0.125f);

		//Gun objs		
		{
			GameObject* const hand = new GameObject();			
			hand->GetComponent<Transform>()->SetPosition(-4.f, 3.f, 0.f);
			//hand->AddComponent<SimpleDrawPoint>();
			//hand->GetComponent<SimpleDrawPoint>()->origin = monster;

			hand->SetName(L"hand");
			hand->SetParent(monster);

			monster->GetComponent<GangsterAI>()->SetHandObject(hand);

			scene->AddGameObject(hand, eLayerType::Monster);

			{
				GameObject* const gun = new GameObject();
				gun->GetComponent<Transform>()->SetPosition(13.f, 0.f, 0.f);
				gun->AddComponent<Animator2D>();
				gun->SetName(L"gun");
				gun->SetParent(hand);

				Animator2D* const gunAnim = gun->GetComponent<Animator2D>();
				gunAnim->CreateAnimation(L"Gun", atlas, 1, XMUINT2(5, 706), XMUINT2(33, 9), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
				gunAnim->Play(L"Gun", true);

				monster->GetComponent<GangsterAI>()->SetGunObject(gun);

				scene->AddGameObject(gun, eLayerType::Monster);
			}
		}


		anim->Play(L"HurtGround", true);
	}

#pragma endregion



	
	return monster;
}

GameObject* GameObjectBuilder::Slash()
{
	GameObject* const Slash = new GameObject();

	Slash->AddComponent<Animator2D>();
	Slash->AddComponent<CircleCollider2D>();

	Slash->GetComponent<CircleCollider2D>()->SetRadius(50.f);

	Animator2D* const animator = Slash->GetComponent<Animator2D>();

	animator->GetMaterial()->SetShader(
		gResourceManager->FindOrNull<Shader>(L"LightAnimation2D"));

	Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Player_slash);

	animator->CreateAnimation(L"Slash", atlas, 6, XMUINT2(5, 34), XMUINT2(106, 32), XMUINT2(10, 10), XMINT2(0, 0), 0.04f);

	//Slash->SetParent(player);
	//player->GetComponent<PlayerController>()->SetSlash(Slash);

	Slash->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);

	return Slash;
}


GameObject* GameObjectBuilder::InstantiatePlayer(Scene* const scene)
{
	GameObject* const player = GameObjectBuilder::Player();
	
	player->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
	player->GetComponent<Animator2D>()->GetMaterial()->SetShader(
		gResourceManager->FindOrNull<Shader>(L"LightAnimation2D"));

	scene->AddGameObject(player, eLayerType::Player);

	//Add Slash
	{
		GameObject* const Slash = new GameObject();

		Slash->AddComponent<Animator2D>();
		Slash->AddComponent<CircleCollider2D>();

		Slash->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		Slash->GetComponent<CircleCollider2D>()->SetRadius(50.f);

		Animator2D* const animator = Slash->GetComponent<Animator2D>();
		animator->GetMaterial()->SetShader(
			gResourceManager->FindOrNull<Shader>(L"LightAnimation2D"));
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Player_slash);
		animator->CreateAnimation(L"Slash", atlas, 6, XMUINT2(5, 34), XMUINT2(106, 32), XMUINT2(10, 10), XMINT2(0, 0), 0.04f);

		Slash->SetParent(player);
		player->GetComponent<PlayerController>()->SetSlash(Slash);	
		scene->AddGameObject(Slash, eLayerType::Default);
	}	

	return player;

}

GameObject* GameObjectBuilder::InstantiateGlobalLight2D(Scene* const scene, const eLayerType type)
{
	GameObject* const light = new GameObject();
	light->SetName(L"GlobalLight2D");
	light->AddComponent<Light2D>();

	light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::DIRECTIONAL);
	light->GetComponent<Light2D>()->SetRadius(300.f);	
	light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(1.f, 1.f, 1.f));

	light->GetComponent<Transform>()->SetPosition(100, 0.f, 0.f);

	scene->AddGameObject(light, type);

	return light;
}

void GameObjectBuilder::AddUI(Scene* const scene)
{

#pragma region UIGameOBject
	//UI
	const Vector2 screenSize = gEngine->GetRenderTargetSize();
	const float hudPosY = gEngine->GetRenderTargetSize().y / 2.f - 23.f;

	//UI Cursur
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UICursor");

		obj->AddComponent<CursorMovement>();

		obj->GetComponent<Transform>()->SetPosition(610.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::Mouse);
	}

	//UI UP Hud
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHud");

		const Vector2 pos = helper::RenderTargetToWorldUI(Vector2(screenSize.x / 2.f, 23.f), screenSize);

		obj->GetComponent<Transform>()->SetPosition(Vector3(pos.x, pos.y, 10.f));
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	constexpr float timerPosX = -8.f;

	//UI HudTimer
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHudTimer");

		obj->GetComponent<Transform>()->SetPosition(timerPosX, hudPosY + 2.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Timer
	{

		GameObject* const obj = GameObjectBuilder::Default2D(L"UITimer");

		obj->AddComponent<UIEffect>();

		obj->GetComponent<Transform>()->SetPosition(timerPosX + 16.f, hudPosY + 6.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UIShift
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIShift00");

		obj->AddComponent<ShiftController>();

		obj->GetComponent<Transform>()->SetPosition(-455.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Battery
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIBattery");

		obj->GetComponent<Transform>()->SetPosition(-561.f, hudPosY - 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);

		for (UINT i = 0; i < 11; ++i)
		{
			//UI BatteryPart
			{
				GameObject* const part = GameObjectBuilder::Default2D(L"UIBatteryPart");

				part->GetComponent<Transform>()->SetPosition(-25.5f + i * 5.f, 0.5f, 0.f);
				part->SetParent(obj);
				scene->AddGameObject(part, eLayerType::UI);
			}
		}

	}

	//UI Hud Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIHudItem");

		obj->GetComponent<Transform>()->SetPosition(+560.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UILeftItem");

		obj->GetComponent<Transform>()->SetPosition(528.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Item
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIRightItem");

		obj->GetComponent<Transform>()->SetPosition(592.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Click
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UILeftClick");

		obj->GetComponent<Transform>()->SetPosition(550.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Click
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"UIRightClick");

		obj->GetComponent<Transform>()->SetPosition(610.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		scene->AddGameObject(obj, eLayerType::UI);
	}



#pragma endregion

}

void GameObjectBuilder::AddCamera(Scene* const scene)
{
	//UI
	const Vector2 screenSize = gEngine->GetRenderTargetSize();	

	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();

		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();
		mainCamera->AddComponent<FolowPlayer>();

		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::BackGround);

		scene->AddGameObject(mainCamera, eLayerType::Default);

		//backGorund Camera
		{
			GameObject* const backgroundCamera = new GameObject();

			backgroundCamera->AddComponent<Camera>();			

			backgroundCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -110.f);
			backgroundCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::BackGround);
			backgroundCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
			backgroundCamera->GetComponent<Camera>()->SetProjectionType(eCameraProjectionType::Perspective);

			backgroundCamera->GetComponent<Camera>()->TurnOffAllLayer();
			backgroundCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::BackGround);

			backgroundCamera->SetParent(mainCamera);
			scene->AddGameObject(backgroundCamera, eLayerType::Default);
		}
	}

	//UI Camera
	{
		GameObject* const uiCamera = new GameObject();

		uiCamera->AddComponent<Camera>();

		uiCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		uiCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::UI);
		uiCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		uiCamera->GetComponent<Camera>()->TurnOffAllLayer();
		uiCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);

		scene->AddGameObject(uiCamera, eLayerType::Default);
	}	
}
