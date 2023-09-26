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
#include "RewindComponent.h"

#include "KissyfaceAI.h"
#include "AxeMovement.h"

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
	player->AddComponent<RewindComponent>();


	player->GetComponent<AfterImage>()->SetCreateDeltaTime(0.02f);
	player->GetComponent<AfterImage>()->SetAlphaTime(1.2f);
	player->GetComponent<AfterImage>()->SetAlphaMaxTime(2.0f);


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
	monster->AddComponent <RewindComponent>();


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
			hand->AddComponent<RewindComponent>();
			//hand->AddComponent<SimpleDrawPoint>();
			//hand->GetComponent<SimpleDrawPoint>()->origin = monster;

			hand->SetName(L"hand");
			hand->SetParent(monster);

			monster->GetComponent<GangsterAI>()->SetHandObject(hand);

			scene->AddGameObject(hand, eLayerType::Monster);

			{
				GameObject* const gun = new GameObject();
				gun->GetComponent<Transform>()->SetPosition(13.f, 0.f, 0.f);
				gun->AddComponent<RewindComponent>();

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

GameObject* GameObjectBuilder::InstantiateKissyface(Scene* const scene)
{	
	GameObject* const kissyface = new GameObject();

	kissyface->GetComponent<Transform>()->SetPosition(-200.f, 0.f, 0.f);
	kissyface->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);

	kissyface->SetName(L"Monster");
	kissyface->AddComponent<Rigidbody2D>();
	kissyface->AddComponent<Rect2DInterpolation>();
	kissyface->AddComponent<RectCollider2D>();
	kissyface->AddComponent<Animator2D>();
	kissyface->AddComponent<KissyfaceAI>();

	//Collider
	{
		kissyface->GetComponent<RectCollider2D>()->SetSize(22.f, 58.f);
		kissyface->GetComponent<RectCollider2D>()->SetOffset(Vector2(0.f, 4.f));
	}

	//Rigidbody
	{
		kissyface->GetComponent<Rigidbody2D>()->TurnOnGravity();
		kissyface->GetComponent<Rigidbody2D>()->SetGravityAccel(1800.f);
	}

	//Animation
	{
		Animator2D* const anim = kissyface->GetComponent<Animator2D>();
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Kissyface_kissyface);

		anim->CreateAnimation(L"spr_kissyface_block", atlas, 5, XMUINT2(5, 34), XMUINT2(53, 48), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_dead", atlas, 12, XMUINT2(5, 121), XMUINT2(49, 26), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_die", atlas, 14, XMUINT2(5, 222), XMUINT2(106, 56), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_headfly", atlas, 6, XMUINT2(5, 449), XMUINT2(17, 14), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_headfly_loop", atlas, 6, XMUINT2(5, 502), XMUINT2(17, 12), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_headland", atlas, 8, XMUINT2(5, 553), XMUINT2(46, 15), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_hit_grenade", atlas, 6, XMUINT2(5, 607), XMUINT2(72, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_hurt", atlas, 6, XMUINT2(5, 696), XMUINT2(71, 58), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_jump", atlas, 2, XMUINT2(5, 793), XMUINT2(38, 73), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_jump_swing", atlas, 3, XMUINT2(5, 905), XMUINT2(31, 54), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_landattack", atlas, 6, XMUINT2(5, 998), XMUINT2(44, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_lunge", atlas, 5, XMUINT2(5, 1087), XMUINT2(83, 68), XMUINT2(10, 10), XMINT2(20, 9), 0.08f);

		anim->CreateAnimation(L"spr_kissyface_lungeattack", atlas, 9, XMUINT2(5, 1194), XMUINT2(104, 54), XMUINT2(10, 10), XMINT2(35, 2), 0.08f);

		anim->CreateAnimation(L"spr_kissyface_prelunge", atlas, 4, XMUINT2(5, 1498), XMUINT2(41, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);

		anim->CreateAnimation(L"spr_kissyface_nohead", atlas, 7, XMUINT2(5, 1351), XMUINT2(53, 20), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_prejump", atlas, 4, XMUINT2(5, 1410), XMUINT2(44, 49), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_recover", atlas, 7, XMUINT2(5, 1587), XMUINT2(69, 45), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		

		anim->CreateAnimation(L"spr_kissyface_sharpenaxe", atlas, 16, XMUINT2(5, 1752), XMUINT2(31, 49), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_slash", atlas, 12, XMUINT2(5, 1840), XMUINT2(122, 52), XMUINT2(10, 10), XMINT2(0, 2), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_struggle", atlas, 2, XMUINT2(5, 2055), XMUINT2(58, 36), XMUINT2(10, 10), XMINT2(0, -7), 0.125f);

		anim->CreateAnimation(L"Throw", atlas, 9, XMUINT2(5, 2130), XMUINT2(106, 55), XMUINT2(10, 10), XMINT2(6, 3), 0.08f);
		anim->CreateAnimation(L"spr_kissyface_returnaxe", atlas, 5, XMUINT2(5, 1671), XMUINT2(69, 42), XMUINT2(10, 10), XMINT2(0, -4), 0.08f);

		anim->CreateAnimation(L"spr_kissyface_tug", atlas, 6, XMUINT2(5, 2391), XMUINT2(58, 41), XMUINT2(10, 10), XMINT2(5, -4), 0.125f);



		anim->CreateAnimation(L"spr_kissyface_tobattle", atlas, 9, XMUINT2(5, 2289), XMUINT2(52, 63), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);


		anim->CreateAnimation(L"spr_kissyface_walk", atlas, 10, XMUINT2(5, 2471), XMUINT2(39, 49), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_axe", atlas, 1, XMUINT2(5, 2559), XMUINT2(26, 80), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_broken_axe", atlas, 1, XMUINT2(5, 2678), XMUINT2(106, 5), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_casual_idle", atlas, 1, XMUINT2(5, 2722), XMUINT2(40, 49), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_chain", atlas, 1, XMUINT2(5, 2810), XMUINT2(11, 4), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_hitgrenade_idle", atlas, 1, XMUINT2(5, 2853), XMUINT2(37, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

		anim->CreateAnimation(L"spr_kissyface_idle", atlas, 1, XMUINT2(5, 2942), XMUINT2(37, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
	}

	{
		GameObject* const parent = new GameObject();
		parent->GetComponent<Transform>()->SetScale(0.5f, 0.5f, 1.f);


		parent->SetParent(kissyface);
		scene->AddGameObject(parent, eLayerType::Monster);

		{
			GameObject* const axe = new GameObject();

			axe->SetName(L"Axe");
			axe->GetComponent<Transform>()->SetFlipx(true);
			axe->AddComponent<Animator2D>();
			axe->AddComponent<RectCollider2D>();
			axe->AddComponent<AxeMovement>();
			axe->AddComponent<AfterImage>();

			//axe->AddComponent<Rigidbody2D>();

			axe->GetComponent<RectCollider2D>()->SetSize(22.f, 58.f);
			axe->GetComponent<Animator2D>()->TurnOffVisiblelity();
			axe->GetComponent<AxeMovement>()->SetKissyfaace(kissyface);

			Animator2D* const anim = axe->GetComponent<Animator2D>();
			Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Kissyface_kissyface);

			anim->CreateAnimation(L"spr_kissyface_axe", atlas, 1, XMUINT2(5, 2559), XMUINT2(26, 80), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

			anim->Play(L"spr_kissyface_axe", true);


			kissyface->GetComponent<KissyfaceAI>()->SetAxe(axe);
			scene->AddGameObject(axe, eLayerType::Monster);
			axe->SetParent(parent);
		}		
	}	




	kissyface->GetComponent<Animator2D>()->Play(L"spr_kissyface_walk", true);
	scene->AddGameObject(kissyface, eLayerType::Monster);
	return kissyface;
}

GameObject* GameObjectBuilder::Slash()
{
	GameObject* const Slash = new GameObject();

	Slash->AddComponent<Animator2D>();
	Slash->AddComponent<CircleCollider2D>();
	//Slash->AddComponent<RewindComponent>();

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
		Slash->AddComponent<RewindComponent>();

		Slash->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		Slash->GetComponent<CircleCollider2D>()->SetRadius(50.f);

		Animator2D* const animator = Slash->GetComponent<Animator2D>();
		animator->GetMaterial()->SetShader(gResourceManager->FindOrNull<Shader>(L"LightAnimation2D"));
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Player_slash);
		animator->CreateAnimation(L"Slash", atlas, 6, 
			XMUINT2(5, 34), XMUINT2(106, 32), XMUINT2(10, 10), XMINT2(0, 0), 0.04f);

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

GameObject* GameObjectBuilder::AddCamera(Scene* const scene)
{
	//UI
	const Vector2 screenSize = gEngine->GetRenderTargetSize();	
	GameObject* result = nullptr;

	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();
		result = mainCamera;
		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();
		mainCamera->AddComponent<FolowPlayer>();
		mainCamera->AddComponent<RewindComponent>();

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
			backgroundCamera->AddComponent<RewindComponent>();


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

	return result;
}
