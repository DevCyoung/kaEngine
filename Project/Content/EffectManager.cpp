#include "pch.h"
#include "EffectManager.h"
#include "Components.h"
#include "ResourceManager.h"
#include "Effect2D.h"
#include "RewindComponent.h"


EffectManager::EffectManager()
	: mEffects{}
	, mEffectIdx(0)
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize(Scene* scene)
{
	for (int i = 0; i < MAX_EFFECT_COUNT; ++i)
	{
		GameObject* const effectObject = new GameObject();

		effectObject->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		{
			Texture* const atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Effect_effect1);

			effectObject->AddComponent<Animator2D>();
			effectObject->AddComponent<Effect2D>();
			effectObject->AddComponent<RewindComponent>();

			Animator2D* const anim = effectObject->GetComponent<Animator2D>();
			anim->TurnOffVisiblelity();

			anim->CreateAnimation(L"Blood1", atlas, 6, XMUINT2(5, 34), XMUINT2(30, 30), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"Blood2", atlas, 6, XMUINT2(5, 103), XMUINT2(30, 30), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"Blood3", atlas, 6, XMUINT2(5, 172), XMUINT2(30, 30), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"BulletReflect", atlas, 5, XMUINT2(5, 241), XMUINT2(70, 64), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"DustCloud", atlas, 7, XMUINT2(5, 344), XMUINT2(19, 19), XMUINT2(10, 10), XMINT2(0, 0), 0.05f);
			anim->CreateAnimation(L"JumpCloud", atlas, 4, XMUINT2(5, 402), XMUINT2(32, 51), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"LandCloud", atlas, 7, XMUINT2(5, 492), XMUINT2(50, 14), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"SpinerBullet", atlas, 5, XMUINT2(5, 545), XMUINT2(70, 64), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"StomperCloud", atlas, 10, XMUINT2(5, 648), XMUINT2(56, 23), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);
			anim->CreateAnimation(L"StomperCloud2", atlas, 10, XMUINT2(5, 710), XMUINT2(56, 23), XMUINT2(10, 10), XMINT2(0, 0), 0.06f);
		}		

		{

		}

		mEffects[i] = effectObject;
		scene->RegisterEventAddGameObject(effectObject, eLayerType::Effect);
	}
}

void EffectManager::Shot(const std::wstring& str, Vector3 pos)
{
	GameObject* const effect = mEffects[mEffectIdx];

	effect->GetComponent<Effect2D>()->SetSpeed(0.f);
	effect->GetComponent<Effect2D>()->SetVelocity(Vector2::Zero);

	effect->GetComponent<Animator2D>()->TurnOnVisiblelity();
	effect->GetComponent<Animator2D>()->Play(str, false);

	pos.z = 0.f;

	effect->GetComponent<Transform>()->SetPosition(pos);	

	mEffectIdx = (mEffectIdx + 1) % MAX_EFFECT_COUNT;
}

void EffectManager::Shot(const std::wstring& str, Vector3 pos, bool bFlip)
{
	GameObject* const effect = mEffects[mEffectIdx];

	effect->GetComponent<Animator2D>()->SetFlipX(bFlip);

	Shot(str, pos);
}

void EffectManager::Shot(const std::wstring& str, Vector3 pos, Vector2 direction, float speed)
{
	GameObject* const effect = mEffects[mEffectIdx];

	Shot(str, pos);

	effect->GetComponent<Effect2D>()->SetSpeed(speed);
	effect->GetComponent<Effect2D>()->SetVelocity(direction);	
}
