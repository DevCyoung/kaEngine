#include "pch.h"
#include "GangsterAI.h"
#include "Components.h"
#include "Rect2DInterpolation.h"
#include  <Engine/Color.h>
#include <Engine/EngineMath.h>
#include "BulletMovement.h"
#include <Engine/SceneManager.h>
#include "ResourceManager.h"
#include "RewindComponent.h"
#include "FolowPlayer.h"
#include <Engine/SceneManager.h>

GangsterAI::GangsterAI()
	: BasicMonsterAI(eScriptComponentType::GangsterAI)
{
}

GangsterAI::~GangsterAI()
{
}

void GangsterAI::CreateAnimation(Scene* scene)
{
	Animator2D* const anim = GetOwner()->GetComponent<Animator2D>();
	Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Gangster_gangster);

	anim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));	
	anim->CreateAnimation(L"Fall", atlas, 12, XMUINT2(5, 34), XMUINT2(42, 41), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"HurtFly", atlas, 2, XMUINT2(5, 114), XMUINT2(38, 34), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"HurtGround", atlas, 14, XMUINT2(5, 187), XMUINT2(44, 34), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"Idle", atlas, 8, XMUINT2(5, 304), XMUINT2(49, 50), XMUINT2(10, 10), XMINT2(0, 7), 0.08f);
	anim->CreateAnimation(L"Run", atlas, 10, XMUINT2(5, 393), XMUINT2(45, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.08f);
	anim->CreateAnimation(L"Turn", atlas, 6, XMUINT2(5, 472), XMUINT2(48, 42), XMUINT2(10, 10), XMINT2(0, 3), 0.08f);
	anim->CreateAnimation(L"Walk", atlas, 8, XMUINT2(5, 553), XMUINT2(34, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.08f);
	anim->CreateAnimation(L"Whip", atlas, 6, XMUINT2(5, 632), XMUINT2(48, 35), XMUINT2(10, 10), XMINT2(2, 0), 0.08f);
	anim->CreateAnimation(L"Aim", atlas, 1, XMUINT2(5, 754), XMUINT2(42, 50), XMUINT2(10, 10), XMINT2(0, 7), 0.08f);
	anim->Play(L"Idle", true);

	(void)scene;
}

void GangsterAI::CreateGun(Scene* scene)
{
	GameObject* const hand = new GameObject();
	hand->GetComponent<Transform>()->SetPosition(-4.f, 3.f, 0.f);
	hand->AddComponent<RewindComponent>();	
	hand->SetName(L"hand");
	hand->SetParent(GetOwner());

	SetHandObject(hand);
	scene->AddGameObject(hand, eLayerType::Monster);
	{
		GameObject* const gun = new GameObject();
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Gangster_gangster);

		gun->GetComponent<Transform>()->SetPosition(13.f, 0.f, 0.f);
		gun->AddComponent<RewindComponent>();

		gun->AddComponent<Animator2D>();
		gun->SetName(L"gun");
		gun->SetParent(hand);

		Animator2D* const gunAnim = gun->GetComponent<Animator2D>();
		gunAnim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));

		gunAnim->CreateAnimation(L"Gun", atlas, 1, XMUINT2(5, 706), XMUINT2(33, 9), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
		gunAnim->Play(L"Gun", true);

		SetGunObject(gun);
		scene->AddGameObject(gun, eLayerType::Monster);
	}
}
