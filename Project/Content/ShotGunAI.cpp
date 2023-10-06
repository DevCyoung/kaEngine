#include "pch.h"
#include "ShotGunAI.h"
#include "Components.h"

ShotGunAI::ShotGunAI()
    : BasicMonsterAI(eScriptComponentType::ShotGunAI)
{
}

ShotGunAI::~ShotGunAI()
{
}

void ShotGunAI::CreateAnimation(Scene* scene)
{
	Animator2D* const anim = GetOwner()->GetComponent<Animator2D>();
	Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_ShotgunMan_shotgun);

	anim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));
	anim->CreateAnimation(L"Fall", atlas, 12, XMUINT2(5, 806), XMUINT2(37, 40), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"HurtFly", atlas, 2, XMUINT2(5, 167), XMUINT2(35, 36), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"HurtGround", atlas, 14, XMUINT2(5, 242), XMUINT2(39, 33), XMUINT2(10, 10), XMINT2(0, -1), 0.08f);
	anim->CreateAnimation(L"Idle", atlas, 6, XMUINT2(5, 314), XMUINT2(48, 50), XMUINT2(10, 10), XMINT2(0, 7), 0.08f);
	anim->CreateAnimation(L"Run", atlas, 10, XMUINT2(5, 639), XMUINT2(33, 39), XMUINT2(10, 10), XMINT2(0, 2), 0.08f);
	anim->CreateAnimation(L"Turn", atlas, 8, XMUINT2(5, 1421), XMUINT2(52, 40), XMUINT2(10, 10), XMINT2(1, 2), 0.08f);
	anim->CreateAnimation(L"Walk", atlas, 10, XMUINT2(5, 1500), XMUINT2(48, 41), XMUINT2(10, 10), XMINT2(1, 3), 0.08f);
	anim->CreateAnimation(L"Aim", atlas, 1, XMUINT2(5, 1580), XMUINT2(42, 50), XMUINT2(10, 10), XMINT2(0, 7), 0.08f);

	anim->Play(L"Idle", true);

	(void)scene;
}

void ShotGunAI::CreateGun(Scene* scene)
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
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_ShotgunMan_shotgun);

		gun->GetComponent<Transform>()->SetPosition(13.f, 0.f, 0.f);
		gun->AddComponent<RewindComponent>();

		gun->AddComponent<Animator2D>();
		gun->SetName(L"gun");
		gun->SetParent(hand);

		Animator2D* const gunAnim = gun->GetComponent<Animator2D>();
		gunAnim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));

		gunAnim->CreateAnimation(L"Gun", atlas, 1, XMUINT2(5, 1669), XMUINT2(34, 10), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
		gunAnim->Play(L"Gun", true);

		SetGunObject(gun);
		scene->AddGameObject(gun, eLayerType::Monster);
	}
}
