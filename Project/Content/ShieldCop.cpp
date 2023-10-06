#include "pch.h"
#include "ShieldCop.h"
#include "Components.h"
#include <Engine/EngineMath.h>
#include "BulletMovement.h"

ShieldCop::ShieldCop()
    : BasicMonsterAI(eScriptComponentType::ShieldCop)
{
}

ShieldCop::~ShieldCop()
{
}

void ShieldCop::aim()
{
	GameObject* player = GameManager::GetInstance()->GetPlayer();
	Vector2 direction = helper::math::GetDirection2D(mHandObject, player);
	//float distance = helper::math::GetDistance2D(mHandObject, player);

	float deg = Rad2Deg(atan2(direction.y, direction.x));

	//arm Rotation
	float armDeg = deg < 0.f ? 360.f + deg : deg;
	(void)armDeg;

	if (direction.x < 0.f)
	{
		deg = 180 - deg;

		mTransform->SetRotation(Vector3(0.f, 180.f, 0.f));

		if (armDeg < 180)
		{
			armDeg = 180.f - armDeg;
		}
		else
		{
			armDeg = 270 + 270 - armDeg;
		}

	}
	else
	{
		mTransform->SetRotation(Vector3(0.f, 0.f, 0.f));
	}

	if (armDeg < 90)
	{
		armDeg += 90.f;
	}
	else
	{
		armDeg -= 270.f;
	}
	UINT frameIdx = static_cast<UINT>(armDeg / 9.f);
	if (frameIdx >= 18)
	{
		frameIdx = 18;
	}
	mAnimator2D->PlayFrame(L"Aim", frameIdx, false);

	Vector3 handRotation = mHandObject->GetComponent<Transform>()->GetRotation();

	if (abs(handRotation.z - deg) > 0.5f)
	{
		mHandObject->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, deg));
	}

	if (isAttackable(80.f) && mAnimator2D->FindAnimationOrNull(L"Whip"))
	{
		mAnimator2D->Play(L"Whip", false);
		mState = eMonsterState::Whip;
	}
	else if (false == isAttackable(500.f))
	{
		mAnimator2D->Play(L"Run", true);
		mState = eMonsterState::Trace;
	}
	else
	{
		if (mShotDelayTime > 0.5f)
		{
			mShotDelayTime = 0.f;

			//Shot
			Scene* scene = GetOwner()->GetGameSystem()->GetScene();
			GameObject* bullet = new GameObject();

			bullet->AddComponent<BulletMovement>();
			bullet->AddComponent<SpriteRenderer>();
			bullet->AddComponent<RewindComponent>();
			bullet->AddComponent<RectCollider2D>();

			bullet->GetComponent<RectCollider2D>()->SetSize(20.f, 20.f);

			bullet->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.3f, 1.f));

			bullet->GetComponent<SpriteRenderer>()->SetMaterial(gResourceManager->FindOrNull<Material>(L"UITimer"));
			bullet->GetComponent<SpriteRenderer>()->SetMesh(gResourceManager->FindOrNull<Mesh>(L"FillRect2D"));
			bullet->GetComponent<BulletMovement>()->mDir = Vector3(direction.x, direction.y, 0.f);



			bullet->GetComponent<Transform>()->SetPosition(mHandObject->GetComponent<Transform>()->GetWorldMatrix().Translation());

			scene->RegisterEventAddGameObject(bullet, eLayerType::Bullet);
		}
	}

	mRigidbody2D->SetVelocity(Vector2::Zero);
}

void ShieldCop::CreateAnimation(Scene* scene)
{
	Animator2D* const anim = GetOwner()->GetComponent<Animator2D>();
	Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_ShieldCop_shieldcop);
	Texture* atlas2 = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_ShotgunMan_shotgun);

	anim->SetMaterial(gResourceManager->FindOrNull<Material>(L"LightAnimation2D"));	
	anim->CreateAnimation(L"Fall", atlas, 12, XMUINT2(5, 737), XMUINT2(37, 40), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"HurtFly", atlas, 2, XMUINT2(5, 350), XMUINT2(35, 36), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);
	anim->CreateAnimation(L"HurtGround", atlas2, 14, XMUINT2(5, 242), XMUINT2(39, 33), XMUINT2(10, 10), XMINT2(0, -1), 0.08f);
	anim->CreateAnimation(L"Idle", atlas, 6, XMUINT2(5, 425), XMUINT2(32, 38), XMUINT2(10, 10), XMINT2(0, 1), 0.08f);
	anim->CreateAnimation(L"Run", atlas, 10, XMUINT2(5, 658), XMUINT2(39, 40), XMUINT2(10, 10), XMINT2(0, 3), 0.08f);
	anim->CreateAnimation(L"Turn", atlas, 8, XMUINT2(5, 1104), XMUINT2(35, 42), XMUINT2(10, 10), XMINT2(2, 3), 0.08f);
	anim->CreateAnimation(L"Walk", atlas, 10, XMUINT2(5, 1185), XMUINT2(29, 41), XMUINT2(10, 10), XMINT2(1, 3), 0.08f);
	anim->CreateAnimation(L"Aim", atlas, 19, XMUINT2(5, 34), XMUINT2(50, 52), XMUINT2(10, 10), XMINT2(0, 8), 0.08f);
	anim->CreateAnimation(L"Whip", atlas, 6, XMUINT2(5, 187), XMUINT2(65, 43), XMUINT2(10, 10), XMINT2(0, 4), 0.07f);
		
	anim->Play(L"Idle", true);
	(void)scene;
}

void ShieldCop::CreateGun(Scene* scene)
{
	GameObject* const hand = new GameObject();
	hand->GetComponent<Transform>()->SetPosition(-4.f, 3.f, 0.f);
	hand->AddComponent<RewindComponent>();
	hand->SetName(L"hand");
	hand->SetParent(GetOwner());

	SetHandObject(hand);
	scene->AddGameObject(hand, eLayerType::Monster);    
}