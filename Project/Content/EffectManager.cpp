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
		effectObject->GetComponent<Transform>()->SetPosition(100000.f, 0.f, 0.f);

		{
			Texture* const atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Effect_effect1);
			Material* const mat = gResourceManager->FindOrNull<Material>(L"Animation2D");


			effectObject->AddComponent<Animator2D>();
			effectObject->AddComponent<Effect2D>();
			effectObject->AddComponent<RewindComponent>();

			Animator2D* const anim = effectObject->GetComponent<Animator2D>();

			anim->SetMaterial(mat);
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
			Animator2D* const anim = effectObject->GetComponent<Animator2D>();
			Texture* const atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Effect_gunEffect);

			anim->CreateAnimation(L"GunSmoke1", atlas, 10, XMUINT2(5, 34), XMUINT2(26, 22), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"GunSmoke2", atlas, 12, XMUINT2(5, 95), XMUINT2(39, 21), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"GunSmoke3", atlas, 11, XMUINT2(5, 155), XMUINT2(27, 21), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"GunSpark1", atlas, 8, XMUINT2(5, 215), XMUINT2(42, 42), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"GunSpark2", atlas, 8, XMUINT2(5, 296), XMUINT2(50, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"GunSpark3", atlas, 8, XMUINT2(5, 385), XMUINT2(50, 50), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"ShotGunFloor", atlas, 7, XMUINT2(5, 474), XMUINT2(15, 6), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
			anim->CreateAnimation(L"ShotGunFly", atlas, 6, XMUINT2(5, 519), XMUINT2(5, 5), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
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

GameObject* EffectManager::GetShotEffect(const std::wstring& str)
{
	GameObject* const effect = mEffects[mEffectIdx];

	effect->GetComponent<Effect2D>()->SetSpeed(0.f);
	effect->GetComponent<Effect2D>()->SetVelocity(Vector2::Zero);

	effect->GetComponent<Animator2D>()->TurnOnVisiblelity();
	effect->GetComponent<Animator2D>()->Play(str, false);

	mEffectIdx = (mEffectIdx + 1) % MAX_EFFECT_COUNT;

	return effect;
}

void EffectManager::Shot(const std::wstring& str, Vector3 pos, bool bFlip)
{
	GameObject* const effect = mEffects[mEffectIdx];

	effect->GetComponent<Animator2D>()->SetFlipX(bFlip);

	Shot(str, pos);
}

void EffectManager::Shot(const std::wstring& str, Vector3 pos, GameObject* parent)
{
	GameObject* const effect = mEffects[mEffectIdx];

	effect->SetParent(parent);

	Shot(str, pos);
}

void EffectManager::Shot(const std::wstring& str, Vector3 pos, Vector3 rotation, bool bFlip)
{
	GameObject* const effect = mEffects[mEffectIdx];

	effect->GetComponent<Transform>()->SetRotation(rotation);
	Shot(str, pos, bFlip);
}

void EffectManager::Shot(const std::wstring& str, Vector3 pos, Vector2 direction, float speed)
{
	GameObject* const effect = mEffects[mEffectIdx];

	Shot(str, pos);

	effect->GetComponent<Effect2D>()->SetSpeed(speed);
	effect->GetComponent<Effect2D>()->SetVelocity(direction);	
}
