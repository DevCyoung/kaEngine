#include "pch.h"
#include "CopAI.h"
#include "Components.h"

CopAI::CopAI()
    : BasicMonsterAI(eScriptComponentType::CopAI)
{
}

CopAI::~CopAI()
{
}

void CopAI::CreateAnimation(Scene* scene)
{
	Animator2D* const anim = GetOwner()->GetComponent<Animator2D>();
	Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Cop_cop);

	anim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));

	anim->CreateAnimation(L"Fall", atlas, 12, XMUINT2(5, 118), XMUINT2(42, 41), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"HurtFly", atlas, 2, XMUINT2(5, 198), XMUINT2(30, 34), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"HurtGround", atlas, 14, XMUINT2(5, 271), XMUINT2(41, 34), XMUINT2(10, 10), XMINT2(0, -1), 0.08f);
	anim->CreateAnimation(L"Idle", atlas, 8, XMUINT2(5, 388), XMUINT2(49, 50), XMUINT2(10, 10), XMINT2(0, 7), 0.08f);
	anim->CreateAnimation(L"Run", atlas, 10, XMUINT2(5, 561), XMUINT2(45, 40), XMUINT2(10, 10), XMINT2(0, 2), 0.08f);
	anim->CreateAnimation(L"Turn", atlas, 6, XMUINT2(5, 640), XMUINT2(52, 39), XMUINT2(10, 10), XMINT2(0, 2), 0.08f);
	anim->CreateAnimation(L"Walk", atlas, 8, XMUINT2(5, 718), XMUINT2(27, 38), XMUINT2(10, 10), XMINT2(1, 1), 0.08f);
	anim->CreateAnimation(L"Aim", atlas, 1, XMUINT2(5, 844), XMUINT2(49, 50), XMUINT2(10, 10), XMINT2(0, 7), 0.08f);
	
	anim->Play(L"Idle", true);
	(void)scene;
}

void CopAI::CreateGun(Scene* scene)
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
		Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Cop_cop);

		gun->GetComponent<Transform>()->SetPosition(13.f, 0.f, 0.f);
		gun->AddComponent<RewindComponent>();

		gun->AddComponent<Animator2D>();
		gun->SetName(L"gun");
		gun->SetParent(hand);

		Animator2D* const gunAnim = gun->GetComponent<Animator2D>();
		gunAnim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));

		gunAnim->CreateAnimation(L"Gun", atlas, 1, XMUINT2(5, 795), XMUINT2(32, 10), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
		gunAnim->Play(L"Gun", true);

		SetGunObject(gun);
		scene->AddGameObject(gun, eLayerType::Monster);
	}
    (void)scene;
}
