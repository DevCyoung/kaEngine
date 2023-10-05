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

GangsterAI::GangsterAI()
	: ScriptComponent(eScriptComponentType::GangsterAI)
	, mPrePlayerPathNode(nullptr)
	, mHandObject(nullptr)
	, mGunObject(nullptr)
	, mTransform(nullptr)
	, mAnimator2D(nullptr)
	, mRigidbody2D(nullptr)
	, mRunSpeed(300.f)
	, mPatrolDitance(100.f)
	, mCurIdleTime(0.f)
	, mCurWalkTime(0.f)
	, mShotDelayTime(0.f)
	, mElevatorTime(0.f)
	, mEffectTime(0.f)
	, mState(eGangsterState::Idle)
	, mbDead(false)
{
}

GangsterAI::~GangsterAI()
{
}

void GangsterAI::trace()
{
	const GameObject* const PLAYER_OBJECT = GameManager::GetInstance()->GetPlayer();
	const Transform* const PLAYER_TRANSFORM = PLAYER_OBJECT->GetComponent<Transform>();
	const Vector3 PLAYER_POS = PLAYER_TRANSFORM->GetPosition();

	Transform* const transform = GetOwner()->GetComponent<Transform>();
	PathNode* const curStandNode = GetOwner()->GetComponent<PlayerPath>()->GetCurPathNodeOrNull();

	if (nullptr == curStandNode)
	{
		return;
	}

	Rigidbody2D* const rigidbody2D = GetOwner()->GetComponent<Rigidbody2D>();
	Vector2 velocity = rigidbody2D->GetVelocity();
	Vector2 direction = Vector2::Zero;

	if (PLAYER_POS.x < transform->GetPosition().x)
	{
		direction.x = -1.f;
	}
	else
	{
		direction.x = 1.f;
	}

	if (nullptr == mPrePlayerPathNode)
	{
		mPrePlayerPathNode = PLAYER_OBJECT->GetComponent<PlayerPath>()->GetCurPathNodeOrNull();
	}
	else if (mPrePlayerPathNode == nullptr || mPrePlayerPathNode != PLAYER_OBJECT->GetComponent<PlayerPath>()->GetCurPathNodeOrNull()) // player node changed
	{
		mPrePlayerPathNode = PLAYER_OBJECT->GetComponent<PlayerPath>()->GetCurPathNodeOrNull();
		PathInfo* const pathInfo = GameManager::GetInstance()->GetPathInfo();
		mPath = pathInfo->Dijikstra(curStandNode->GetIdx(), mPrePlayerPathNode->GetIdx());
	}

	if (false == mPath.empty())
	{
		PathNode* nextNode = mPath.front();

		if (nextNode == curStandNode && nextNode->GetType() != eLayerType::Elevator)
		{
			mPath.pop();
			return;
		}

		Vector2 nextNodePos = nextNode->GetPosition();
		Rect2DInterpolation* const rect2DInterpolation = GetOwner()->GetComponent<Rect2DInterpolation>();

		if (nextNodePos.x < transform->GetPosition().x)
		{
			direction.x = -1.f;
		}
		else
		{
			direction.x = 1.f;
		}

		switch (nextNode->GetType())
		{
		case eLayerType::Wall: //just move direction...
		{
			rect2DInterpolation->TurnOnPlatform();
		}
		break;

		case eLayerType::Elevator: //elevator
		{			
			rect2DInterpolation->TurnOnPlatform();

			Vector3 elevatorPos = Vector3(nextNode->GetPosition().x, nextNode->GetPosition().y, 0.);
			elevatorPos.z = 0.f;
			Vector3 pos = transform->GetPosition();
			pos.z = 0.f;

			if (Vector3::Distance(elevatorPos, pos) < 40.f)
			{
				mElevatorTime += gDeltaTime;

				if (mElevatorTime >= 0.5f)
				{
					mElevatorTime = 0.f;
					mPath.pop();
					nextNode = mPath.front();

					if (!mPath.empty() && nextNode->GetType() == eLayerType::Elevator)
					{
						nextNodePos = nextNode->GetPosition();
						transform->SetPosition(Vector3(nextNodePos.x, nextNodePos.y - 10.f, transform->GetPosition().z));						
					}
				}

				return;
			}

		}
		break;

		case eLayerType::LeftSlope: // up down ?
		{
			if (nextNodePos.y < transform->GetPosition().y) //down
			{
				rect2DInterpolation->TurnOffPlatform();
			}
			else // up
			{
				rect2DInterpolation->TurnOnPlatform();
			}
		}
		break;

		case eLayerType::RightSlope: // up down ?
		{
			if (nextNodePos.y < transform->GetPosition().y) //down
			{
				rect2DInterpolation->TurnOffPlatform();
			}
			else // up
			{
				rect2DInterpolation->TurnOnPlatform();
			}
		}
		break;

		default:
		{

		}
		break;
		}
	}
	else
	{

	}


	if (direction.x < 0.f)
	{
		transform->SetRotation(0.f, 180.f, 0.f);
	}
	else
	{
		transform->SetRotation(0.f, 0.f, 0.f);
	}

	velocity.x = direction.x * mRunSpeed;
	rigidbody2D->SetVelocity(velocity);
}

void GangsterAI::initialize()
{
	mTransform = GetOwner()->GetComponent<Transform>();
	mAnimator2D = GetOwner()->GetComponent<Animator2D>();
	mRigidbody2D = GetOwner()->GetComponent<Rigidbody2D>();

	mGunObject->GetComponent<Animator2D>()->TurnOffVisiblelity();

	mAnimator2D->Play(L"Idle", true);

	//GameManager::GetInstance()->GetRewindManager()->RegisterRewindObject(GetOwner());
}

void GangsterAI::update()
{

	if (GameManager::GetInstance()->GetRewindManager()->GetRewindState() != eRewindState::Record)
	{
		return;
	}

	mEffectTime += gDeltaTime;
	
	if (mbDead  && mEffectTime > 0.03f && mRigidbody2D->GetVelocity().x != 0.f)
	{
		mEffectTime = 0.f;

		Vector3 position = mTransform->GetPosition();

		position.y -= 25.f;

		for (int i = 0; i < 4; i++)
		{
			int rand = helper::rand::RandInt(0, 10000) % 20;

			position.x += rand - 10.f;
			position.y += rand - 10.f;

			//position.y
			
			if (mTransform->GetFlipX())
			{
				gEffectManager->Shot(L"Blood1", position, Vector2(0.7f, 0.3f), 350.f);
			}
			else
			{
				gEffectManager->Shot(L"Blood3", position, Vector2(-0.7f, 0.3f), 350.f);
			}
		}
	}



	mShotDelayTime += gDeltaTime;

	if (mState == eGangsterState::Aim)
	{
		mGunObject->GetComponent<Animator2D>()->TurnOnVisiblelity();
	}
	else
	{
		mGunObject->GetComponent<Animator2D>()->TurnOffVisiblelity();
	}

	//search
	
	

	switch (mState)
	{
	case eGangsterState::Idle:
		idle();
		break;
	case eGangsterState::Walk:
		walk();
		break;
	case eGangsterState::Turn:
		turn();
		break;
	case eGangsterState::Aim:
		aim();
		break;
	case eGangsterState::Whip:
		whip();
		break;
	case eGangsterState::Fall:
		break;
	case eGangsterState::HurtFly:
		break;
	case eGangsterState::HurtGround:
		break;
	case eGangsterState::Dead:
		break;
	case eGangsterState::Trace:
		trace();


		
		if (isAttackable(300.f))
		{
			mState = eGangsterState::Aim;
			mShotDelayTime = 0.f;
			mAnimator2D->Play(L"Aim", true);
		}

		break;
	default:
		break;
	}

	if (mState == eGangsterState::Idle ||
		mState == eGangsterState::Walk ||
		mState == eGangsterState::Turn)
	{
		if (mState != eGangsterState::Trace)
		{
			search();
		}		
	}
}

void GangsterAI::lateUpdate()
{
}

void GangsterAI::onCollisionEnter(Collider2D* other)
{	
	if (false == mbDead && other->GetOwner()->GetLayer() == eLayerType::PlayerAttack)
	{
		//Vector2 direction = helper::math::GetDirection2D(other->GetOwner(), GetOwner());
		Vector3 dir = other->GetOwner()->GetComponent<Transform>()->GetRight();

		if (dir.y > 0.f)
		{
			mAnimator2D->Play(L"Fall", false);
			mState = eGangsterState::HurtFly;
		}
		else
		{
			mAnimator2D->Play(L"HurtGround", false);
			mState = eGangsterState::HurtGround;
		}

		dir.x *= 900.f;
		dir.y *= 1000.f;

		//Matrix mat = mTransform->GetWorldMatrix();
		//mat._42 += 10.f;
		//mTransform->SetWorldMatrix(mat);

		//mTransform->SetPosition(position);

		mRigidbody2D->SetVelocity(Vector2(dir.x, dir.y));
		

		Camera* const camera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);
		camera->GetOwner()->GetComponent<FolowPlayer>()->ShakeCamera();


		GameManager::GetInstance()->GetEventManager()->ShotTimeEffect(0.1f, 0.2f);

		gSoundManager->Play(eResAudioClip::enemySlice, 1.f);

		mbDead = true;
	}	
	else if (other->GetOwner()->GetLayer() == eLayerType::Wall)
	{
		if (mState == eGangsterState::HurtFly)
		{
			mAnimator2D->Play(L"HurtGround", false);
			mState = eGangsterState::HurtGround;
		}
	}
}

bool GangsterAI::isAttackable(const float attackDistacne)
{
	RenderTargetRenderer* const renderTargetRenderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
	DebugRenderer2D* const debugRender2D = renderTargetRenderer->GetDebugRenderer2D();

	Vector3 pos = mHandObject->GetComponent<Transform>()->GetWorldMatrix().Translation();
	debugRender2D->DrawFillCircle2D(pos, 2.5f, 0.f, helper::Color::YELLOW);

	//Raycast
	RayCast2DHitInfo hitInfo;

	GameObject* player = GameManager::GetInstance()->GetPlayer();
	Vector2 direction = helper::math::GetDirection2D(mHandObject, player);
	float distance = helper::math::GetDistance2D(mHandObject, player);

	Vector2 pos2D = Vector2(pos.x, pos.y);

	Physics2D* const physics2D = GetOwner()->GetGameSystem()->GetPhysics2D();
	
	if (false == physics2D->RayCastHit2D(pos2D, direction, distance, eLayerType::Wall, &hitInfo) &&
		false == physics2D->RayCastHit2D(pos2D, direction, distance, eLayerType::LeftSlope, &hitInfo) &&
		false == physics2D->RayCastHit2D(pos2D, direction, distance, eLayerType::RightSlope, &hitInfo) &&
		distance <= attackDistacne)
	{
		debugRender2D->DrawLine2D2(pos, direction, distance, 0.f, helper::Color::MAGENTA);
		return true;
	}
	else
	{
		debugRender2D->DrawLine2D2(pos, direction, distance, 0.f, helper::Color::YELLOW);		
	}

	return false;
}

void GangsterAI::idle()
{
	Vector2 velocity = mRigidbody2D->GetVelocity();
	velocity.x = 0.f;
	mRigidbody2D->SetVelocity(velocity);

	mCurIdleTime += gDeltaTime;

	if (mCurIdleTime > 2.f)
	{
		mCurIdleTime = 0.f;
		mTransform->SetFlipx(!mTransform->GetFlipX());
		mAnimator2D->Play(L"Turn", false);
		mState = eGangsterState::Turn;
	}
}

void GangsterAI::walk()
{	
	mCurWalkTime += gDeltaTime;

	Vector2 velocity = mRigidbody2D->GetVelocity();

	if (mCurWalkTime > 3.f)
	{
		mCurWalkTime = 0.f;

		mAnimator2D->Play(L"Idle", false);
		mState = eGangsterState::Idle;
		return;
	}

	Vector2 direction = Vector2::Right;

	if (mTransform->GetRotation().y != 0.f)
	{
		direction = Vector2::Left;
	}

	velocity.x = direction.x * mRunSpeed * 0.2f;
	mRigidbody2D->SetVelocity(velocity);
}

void GangsterAI::turn()
{
	Vector2 velocity = mRigidbody2D->GetVelocity();
	velocity.x = 0.f;
	mRigidbody2D->SetVelocity(velocity);

	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Walk", true);
		mState = eGangsterState::Walk;
	}	
}

void GangsterAI::aim()
{
	GameObject* player = GameManager::GetInstance()->GetPlayer();
	Vector2 direction = helper::math::GetDirection2D(mHandObject, player);
	//float distance = helper::math::GetDistance2D(mHandObject, player);

	float deg = Rad2Deg(atan2(direction.y, direction.x));

	if (direction.x < 0.f)
	{
		deg = 180 - deg;

		mTransform->SetRotation(Vector3(0.f, 180.f, 0.f));

	}
	else
	{
		mTransform->SetRotation(Vector3(0.f, 0.f, 0.f));
	}

	Vector3 handRotation = mHandObject->GetComponent<Transform>()->GetRotation();

	if (abs(handRotation.z - deg) > 0.5f)
	{
		mHandObject->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, deg));
	}

	if (isAttackable(80.f))
	{
		mAnimator2D->Play(L"Whip", false);
		mState = eGangsterState::Whip;
	}
	else if (false == isAttackable(500.f))
	{
		mAnimator2D->Play(L"Run", true);
		mState = eGangsterState::Trace;
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

void GangsterAI::whip()
{
	mRigidbody2D->SetVelocity(Vector2::Zero);

	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{		
		mAnimator2D->Play(L"Run", true);
		mState = eGangsterState::Trace;
	}
}

void GangsterAI::search()
{
	Physics2D* const physics2D = GetOwner()->GetGameSystem()->GetPhysics2D();
	DebugRenderer2D* const debugRenderer2D = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetDebugRenderer2D();
	RayCast2DHitInfo hitInfo = {};
	Vector3 pos = mTransform->GetPosition();

	float rayDistance = 70.f;

	Vector2 rayDirection = Vector2::Right;

	if (mTransform->GetRotation().y != 0.f)
	{
		rayDirection = Vector2::Left;
	}

	debugRenderer2D->DrawLine2D2(pos, rayDirection, rayDistance, 0.f, helper::Color::MAGENTA);

	/*if (physics2D->RayCastHit2D(Vector2(pos.x, pos.y), rayDirection, rayDistance, eLayerType::Wall, &hitInfo) ||
		physics2D->RayCastHit2D(Vector2(pos.x, pos.y), rayDirection, rayDistance, eLayerType::Door, &hitInfo))
	{
	}
	else */if (physics2D->RayCastHit2D(Vector2(pos.x, pos.y), rayDirection, rayDistance, eLayerType::Player, &hitInfo))
	{
		rayDirection = Vector2::Left;
		mAnimator2D->Play(L"Run", true);
		mState = eGangsterState::Trace;
	}
}

void GangsterAI::ChangeState(eGangsterState state)
{
	if (mState != state)
	{

	}

}

void GangsterAI::partrol()
{
	Physics2D* const physics2D = GetOwner()->GetGameSystem()->GetPhysics2D();
	DebugRenderer2D* const debugRenderer2D = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetDebugRenderer2D();
	RayCast2DHitInfo hitInfo = {};
	Vector3 pos = mTransform->GetPosition();

	float rayDistance = 40.f;

	Vector2 direction = Vector2::Right;

	if (mTransform->GetRotation().y != 0.f)
	{
		direction = Vector2::Left;
	}

	debugRenderer2D->DrawLine2D2(pos, direction, rayDistance, 0.f, helper::Color::MAGENTA);

	if (physics2D->RayCastHit2D(Vector2(pos.x, pos.y), direction, rayDistance, eLayerType::Wall, &hitInfo) ||
		physics2D->RayCastHit2D(Vector2(pos.x, pos.y), direction, rayDistance, eLayerType::Door, &hitInfo))
	{
	}
}