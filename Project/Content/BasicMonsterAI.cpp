#include "pch.h"
#include "BasicMonsterAI.h"
#include "Rect2DInterpolation.h"
#include  <Engine/Color.h>
#include <Engine/EngineMath.h>
#include "BulletMovement.h"
#include <Engine/SceneManager.h>
#include "ResourceManager.h"
#include "RewindComponent.h"
#include "FolowPlayer.h"
#include "DoorController.h"

#include "KatanaZeroSystem.h"

BasicMonsterAI::BasicMonsterAI(const eScriptComponentType scriptComponentType)
	: ScriptComponent(scriptComponentType)
	, mPrePlayerPathNode(nullptr)
	, mNextElevatorNode(nullptr)
	, mHandObject(nullptr)
	, mGunObject(nullptr)
	, mTransform(nullptr)
	, mAnimator2D(nullptr)
	, mRigidbody2D(nullptr)
	, mRunSpeed(450.f)
	, mPatrolDitance(100.f)
	, mCurIdleTime(0.f)
	, mCurWalkTime(0.f)
	, mShotDelayTime(1.5f)
	, mElevatorTime(0.f)
	, mBlockTime(0.f)
	, mEffectTime(0.f)
	, mState(eMonsterState::Idle)
	, mTraceState(eTraceState::None)
	, mAttackState(eAttackState::None)
	, mMonsterType(eMonsterType::Ganster)
	, mEmotionState(eEmotionState::None)
	, mbDead(false)
	, mbShield(false)
	, mAimAttackableDistance(350.f)
{
}

BasicMonsterAI::~BasicMonsterAI()
{
}

void BasicMonsterAI::ChangeState(eMonsterState state)
{
	(void)state;
}

void BasicMonsterAI::initialize()
{
	mTransform = GetOwner()->GetComponent<Transform>();
	mAnimator2D = GetOwner()->GetComponent<Animator2D>();
	mRigidbody2D = GetOwner()->GetComponent<Rigidbody2D>();

	if (mGunObject)
	{
		mGunObject->GetComponent<Animator2D>()->TurnOffVisiblelity();
	}

	mAnimator2D->Play(L"Idle", true);

	liveEnter();
}

void BasicMonsterAI::update()
{
	if (GameManager::GetInstance()->GetRewindManager()->GetRewindState() != eRewindState::Record)
	{
		return;
	}



	if (mGunObject)
	{
		if (mState == eMonsterState::Aim)
		{
			mGunObject->GetComponent<Animator2D>()->TurnOnVisiblelity();
		}
		else
		{
			mGunObject->GetComponent<Animator2D>()->TurnOffVisiblelity();
		}
	}

	if (mbDead)
	{
		bleed();
	}

	stateUpdate();


	if (mState == eMonsterState::Whip ||
		mState == eMonsterState::Aim)
	{
		Vector2 velocity = mRigidbody2D->GetVelocity();
		velocity.x = 0.f;
		mRigidbody2D->SetVelocity(velocity);
	}
}

void BasicMonsterAI::onCollisionEnter(Collider2D* other)
{

	float blockSpeed = 180.f;
	Vector2 blockDirection = Vector2::Left;
	GameObject* player = GameManager::GetInstance()->GetPlayer();
	if (GetOwner()->GetComponent<Transform>()->GetFlipX())
	{
		blockDirection = Vector2::Right;
	}

	if (other->GetOwner()->GetLayer() == eLayerType::PlayerAttack && 
		eMonsterType::Shield == mMonsterType &&
		GetOwner()->GetComponent<Transform>()->GetFlipX() != player->GetComponent<Transform>()->GetFlipX())
	{
		
		mRigidbody2D->SetVelocity(blockDirection * blockSpeed);
		mAnimator2D->Play(L"Idle", true);
		mState = eMonsterState::Block;
		gSoundManager->Play(eResAudioClip::block, 1.f);
		Vector2 playerBlockDirection = helper::math::GetDirection2D(GetOwner(), player);
		Vector2 playerBlockSpeed = Vector2(300.f, 400.f);

		if (playerBlockDirection.x < 0.f)
		{
			playerBlockSpeed.x *= -1.f;
		}
		player->GetComponent<Rigidbody2D>()->SetVelocity(playerBlockSpeed);
	}
	else
	{
		damaged(other, Vector2(900.f, 1000.f));
	}	
}

void BasicMonsterAI::onCollisionExit(Collider2D* other)
{

	(void)other;

}

void BasicMonsterAI::stateUpdate()
{
	mShotDelayTime += gDeltaTime;




	switch (mState)
	{
	case eMonsterState::Idle:
		idle();
		break;
	case eMonsterState::Walk:
		walk();
		break;
	case eMonsterState::Turn:
		turn();
		break;
	case eMonsterState::Aim:
		aim();
		break;
	case eMonsterState::Whip:
		whip();
		break;
	case eMonsterState::Fall:
		break;
	case eMonsterState::HurtFly:
		break;
	case eMonsterState::HurtGround:
		break;
	case eMonsterState::Dead:
		break;
	case eMonsterState::Block:
		block();
		break;
	case eMonsterState::Trace:
		trace();



		if (isAttackable(mAimAttackableDistance))
		{
			mState = eMonsterState::Aim;
			mAttackState = eAttackState::None;
			mShotDelayTime = 0.f;
			mAnimator2D->Play(L"Aim", true);
		}
		break;
	default:
		break;
	}

	if (mState == eMonsterState::Idle ||
		mState == eMonsterState::Walk ||
		mState == eMonsterState::Turn)
	{
		if (mState != eMonsterState::Trace)
		{
			search();
		}
	}
}

bool BasicMonsterAI::isAttackable(const float attackDistacne)
{
	if (eTraceState::ElevatorEnter == mTraceState || 
		eTraceState::ElevatorExit == mTraceState ||
		eTraceState::Turn == mTraceState)
	{
		return false;
	}

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


	//°¢µµ
	/*Vector2 baseDirection = Vector2::Left;

	if (direction.x > 0.f)
	{
		baseDirection = Vector2::Right;		
	}

	if (baseDirection.Dot(direction) < cosf(Deg2Rad(45.f)))
	{
		return false;
	}	*/

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

void BasicMonsterAI::trace()
{
	const GameObject* const PLAYER_OBJECT = GameManager::GetInstance()->GetPlayer();
	const Transform* const PLAYER_TRANSFORM = PLAYER_OBJECT->GetComponent<Transform>();
	const Vector3 PLAYER_POS = PLAYER_TRANSFORM->GetPosition();
	const Vector3 POSITION = mTransform->GetPosition();

	float elevatorEnterTime = 1.f;
	float enterSpeed = gDeltaTime * 1.85f;
	if (mTraceState == eTraceState::ElevatorEnter)
	{
		mRigidbody2D->SetVelocity(Vector2::Zero);
		mElevatorTime += enterSpeed;

		float mulColor = 1.f - mElevatorTime;
		mAnimator2D->MulColor(mulColor, mulColor, mulColor, mulColor);

		if (mElevatorTime >= 1.f)
		{
			mElevatorTime = 0.f;
			mTraceState = eTraceState::ElevatorExit;
			Vector2 nextElevatorPos = mNextElevatorNode->GetPosition();
			mTransform->SetPosition(Vector3(nextElevatorPos.x, nextElevatorPos.y - 10.f, mTransform->GetPosition().z));	
		}
	}
	else if (mTraceState == eTraceState::ElevatorExit)
	{
		mRigidbody2D->SetVelocity(Vector2::Zero);
		mElevatorTime += enterSpeed;

		float mulColor = mElevatorTime;

		mAnimator2D->MulColor(mulColor, mulColor, mulColor, mulColor);

		if (mElevatorTime >= elevatorEnterTime)
		{
			mAnimator2D->MulColorReset();

			mElevatorTime = 0.f;
			mTraceState = eTraceState::Run;
			mAnimator2D->Play(L"Run", true);
			//mPath.pop_back();
		}
	}
	else if (mTraceState == eTraceState::Turn)
	{
		mRigidbody2D->SetVelocity(Vector2::Zero);

		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mTraceState = eTraceState::Run;
			mAnimator2D->Play(L"Run", true);
		}
	}
	else
	{
		PathNode* const curStandNode = GetOwner()->GetComponent<PlayerPath>()->GetCurPathNodeOrNull();


		if (nullptr == curStandNode)
		{
			return;
		}

		if (nullptr == mPrePlayerPathNode)
		{
			mPrePlayerPathNode = PLAYER_OBJECT->GetComponent<PlayerPath>()->GetCurPathNodeOrNull();
		}
		else if (mPrePlayerPathNode == nullptr ||
			mPrePlayerPathNode != PLAYER_OBJECT->GetComponent<PlayerPath>()->GetCurPathNodeOrNull()) // player node changed
		{
			mPrePlayerPathNode = PLAYER_OBJECT->GetComponent<PlayerPath>()->GetCurPathNodeOrNull();
			PathInfo* const pathInfo = GameManager::GetInstance()->GetPathInfo();
			mPath = pathInfo->Dijikstra(curStandNode->GetIdx(), mPrePlayerPathNode->GetIdx());
		}

		Vector2 velocity = mRigidbody2D->GetVelocity();
		Vector2 direction = Vector2::Zero;


		if (PLAYER_POS.x < mTransform->GetPosition().x)
		{
			direction.x = -1.f;
		}
		else
		{
			direction.x = 1.f;
		}

		if (false == mPath.empty())
		{
			PathNode* nextNode = mPath.back();

			if (nextNode == curStandNode && nextNode->GetType() != eLayerType::Elevator)
			{				
				mPath.pop_back();
				return;
			}

			Vector2 nextNodePos = nextNode->GetPosition();
			Rect2DInterpolation* const rect2DInterpolation = GetOwner()->GetComponent<Rect2DInterpolation>();

			if (nextNodePos.x < mTransform->GetPosition().x)
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
				float elevatorPosX = nextNode->GetLineStartPosition().x;

				if (abs(POSITION.x - elevatorPosX) < 2.f)
				{
					mPath.pop_back();

					if (mPath.size() > 1)
					{
						PathNode* const nextNextNode = mPath[mPath.size() - 1];
						if (nextNextNode->GetType() == eLayerType::Elevator)
						{
							mTraceState = eTraceState::ElevatorEnter;							
							mNextElevatorNode = nextNextNode;
							//z
							mAnimator2D->Play(L"Idle", true);
						}
					}

					return;								
				}

			}
			break;

			case eLayerType::LeftSlope: // up down ?
			{
				if (nextNodePos.y < mTransform->GetPosition().y) //down
				{
					rect2DInterpolation->TurnOffPlatform();
					velocity.y = -mRunSpeed;
				}
				else // up
				{
					rect2DInterpolation->TurnOnPlatform();
				}
			}
			break;

			case eLayerType::RightSlope: // up down ?
			{
				if (nextNodePos.y < mTransform->GetPosition().y) //down
				{
					rect2DInterpolation->TurnOffPlatform();
					velocity.y = -mRunSpeed;
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

		Vector2 prevVelocity = mRigidbody2D->GetVelocity();
		velocity.x = direction.x * mRunSpeed;

		if (direction.x < 0.f)
		{
			mTransform->SetRotation(0.f, 180.f, 0.f);
		}
		else
		{
			mTransform->SetRotation(0.f, 0.f, 0.f);
		}

		mRigidbody2D->SetVelocity(velocity);

		Vector3 prevDirection = mTransform->GetRight();		

		if ( (prevDirection.x < 0.f && direction.x > 0.f) ||
			 (prevDirection.x > 0.f && direction.x < 0.f))
		{
			//mAnimator2D->Play(L"Turn", false);
			//mTraceState = eTraceState::Turn;
		}
	}
}

void BasicMonsterAI::idle()
{
	/*Vector2 velocity = mRigidbody2D->GetVelocity();
	velocity.x = 0.f;
	mRigidbody2D->SetVelocity(velocity);

	mCurIdleTime += gDeltaTime;

	if (mCurIdleTime > 2.f)
	{
		mCurIdleTime = 0.f;
		mTransform->SetFlipx(!mTransform->GetFlipX());
		mAnimator2D->Play(L"Turn", false);
		mState = eMonsterState::Turn;
	}*/
}

void BasicMonsterAI::walk()
{
	mCurWalkTime += gDeltaTime;

	Vector2 velocity = mRigidbody2D->GetVelocity();

	if (mCurWalkTime > 3.f)
	{
		mCurWalkTime = 0.f;

		mAnimator2D->Play(L"Idle", false);
		mState = eMonsterState::Idle;
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

void BasicMonsterAI::turn()
{
	Vector2 velocity = mRigidbody2D->GetVelocity();
	velocity.x = 0.f;
	mRigidbody2D->SetVelocity(velocity);

	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Walk", true);
		mState = eMonsterState::Walk;
	}
}

void BasicMonsterAI::aim()
{
	GameObject* player = GameManager::GetInstance()->GetPlayer();
	Vector2 direction = helper::math::GetDirection2D(mHandObject, player);

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



	if (isAttackable(100.f) && mAnimator2D->FindAnimationOrNull(L"Whip"))
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
		Scene* scene = GetOwner()->GetGameSystem()->GetScene();
		Vector3 bulletPosition = mHandObject->GetComponent<Transform>()->GetWorldMatrix().Translation();
		bulletPosition += mHandObject->GetComponent<Transform>()->GetRight() * 80.f;
		bool bFlip = mTransform->GetFlipX();

		if (mAttackState == eAttackState::Shot)
		{
			GameObject* spark = gEffectManager->GetShotEffect(L"GunSmoke1");

			spark->GetComponent<Transform>()->SetRotation(handRotation);
			spark->GetComponent<Transform>()->SetFlipx(bFlip);
			spark->GetComponent<Transform>()->SetPosition(bulletPosition);

			mAttackState = eAttackState::Smog;
		}
		else if (mShotDelayTime > 0.95f)
		{
			mShotDelayTime = 0.f;			
			gSoundManager->Play(eResAudioClip::ShieldCopShot, 0.5f);


			GameObject* bullet = createBullet(Vector3(direction.x, direction.y, 0.f), bulletPosition);			
			
			GameObject* spark = gEffectManager->GetShotEffect(L"GunSpark1");
			spark->GetComponent<Transform>()->SetRotation(handRotation);
			spark->GetComponent<Transform>()->SetFlipx(bFlip);			
			spark->GetComponent<Transform>()->SetPosition(bulletPosition);

			scene->RegisterEventAddGameObject(bullet, eLayerType::Bullet);

			mAttackState = eAttackState::Shot;
		}
		else
		{
			if (abs(handRotation.z - deg) > 0.5f)
			{
				mHandObject->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, deg));
			}
		}
	}
}

void BasicMonsterAI::whip()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Run", true);
		mState = eMonsterState::Trace;
	}
}

void BasicMonsterAI::partrol()
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

void BasicMonsterAI::search()
{
	Physics2D* const physics2D = GetOwner()->GetGameSystem()->GetPhysics2D();
	DebugRenderer2D* const debugRenderer2D = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetDebugRenderer2D();
	RayCast2DHitInfo hitInfo = {};
	Vector3 pos = mTransform->GetPosition();

	float rayDistance = 300.f;
	GameObject* player = GameManager::GetInstance()->GetPlayer();
	Vector2 rayDirection = helper::math::GetDirection2D(GetOwner(), player);

	debugRenderer2D->DrawLine2D2(pos, rayDirection, rayDistance, 0.f, helper::Color::MAGENTA);

	if (physics2D->RayCastHit2D(Vector2(pos.x, pos.y), rayDirection, rayDistance, eLayerType::Player, &hitInfo))
	{
		Vector3 playerPos = GameManager::GetInstance()->GetPlayer()->GetComponent<Transform>()->GetPosition();

		if (physics2D->RayCastHit2D(Vector2(pos.x, pos.y), Vector2(playerPos.x, playerPos.y), 
			rayDistance, eLayerType::Door, &hitInfo))
		{
			if (false == hitInfo.collider->GetOwner()->GetComponent<DoorController>()->IsOpen())
			{
				return;
			}
		}

		
		rayDistance = Vector2::Distance(Vector2(playerPos.x, playerPos.y), Vector2(pos.x, pos.y));

		if (physics2D->RayCastHit2D(Vector2(pos.x, pos.y), rayDirection, rayDistance, eLayerType::Wall, &hitInfo))
		{		
			return;
		}
		if (physics2D->RayCastHit2D(Vector2(pos.x, pos.y), rayDirection, rayDistance, eLayerType::LeftSlope, &hitInfo))
		{
			return;
		}
		if (physics2D->RayCastHit2D(Vector2(pos.x, pos.y), rayDirection, rayDistance, eLayerType::RightSlope, &hitInfo))
		{
			return;
		}

		mAnimator2D->Play(L"Run", true);
		mState = eMonsterState::Trace;

		if (mEmotionState == eEmotionState::None)
		{
			mEmotionState = eEmotionState::Follow;
			mEmotion->GetComponent<Animator2D>()->Play(L"Follow", false);			
		}

	}
}

void BasicMonsterAI::block()
{
	mBlockTime += gDeltaTime;

	if (mBlockTime >= 0.5f)
	{
		mBlockTime = 0.f;
		mAnimator2D->Play(L"Idle", true);
		mState = eMonsterState::Idle;
	}
}

void BasicMonsterAI::damaged(Collider2D* other, Vector2 pushOutPower)
{
	eLayerType otherLayerType = other->GetOwner()->GetLayer();

	if (false == mbDead)
	{
		//bool bPlayerBullet = other->GetOwner()->GetComponent<BulletMovement>()->IsPlayerBullet();
		if (otherLayerType == eLayerType::PlayerAttack ||
			(otherLayerType == eLayerType::Bullet && other->GetOwner()->GetComponent<BulletMovement>()->IsPlayerBullet()))
		{
			mbDead = true;
			dieEnter();
			mAnimator2D->MulColorReset();

			gSoundManager->Play(eResAudioClip::enemySlice, 1.f);
			Vector3 dir = other->GetOwner()->GetComponent<Transform>()->GetRight();
			if (otherLayerType == eLayerType::PlayerAttack)
			{

				dir.x *= pushOutPower.x;
				dir.y *= pushOutPower.y;
				mRigidbody2D->SetVelocity(Vector2(dir.x, dir.y));
			}
			else
			{
				dir = other->GetOwner()->GetComponent<BulletMovement>()->mDir;
				dir.z = 0.f;
				dir.Normalize();

				dir.x *= pushOutPower.x;
				dir.y *= pushOutPower.y;
				mRigidbody2D->SetVelocity(Vector2(dir.x, dir.y));
			}
			

			if (dir.y > 0.f)
			{
				mAnimator2D->Play(L"Fall", false);
				mState = eMonsterState::HurtFly;
			}
			else
			{
				mAnimator2D->Play(L"HurtGround", false);
				mState = eMonsterState::HurtGround;
			}

			Camera* const mainCamera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);

			mainCamera->GetOwner()->GetComponent<FolowPlayer>()->ShakeCamera();
			GameManager::GetInstance()->GetEventManager()->ShotTimeEffect(0.1f, 0.2f);		
		}		
	}
	else if (otherLayerType == eLayerType::Wall || 
			 otherLayerType == eLayerType::LeftSlope ||
			 otherLayerType == eLayerType::RightSlope)
	{
		if (mState == eMonsterState::HurtFly)
		{
			mAnimator2D->Play(L"HurtGround", false);
			mState = eMonsterState::HurtGround;
		}
	}

}

GameObject* BasicMonsterAI::createBullet(Vector3 direction, Vector3 position)
{
	GameObject* bullet = new GameObject();
	Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Particle_particle);

	bullet->AddComponent<BulletMovement>();
	bullet->AddComponent<Animator2D>();
	bullet->AddComponent<RewindComponent>();
	bullet->AddComponent<RectCollider2D>();

	bullet->GetComponent<RectCollider2D>()->SetSize(20.f, 20.f);
	bullet->GetComponent<Animator2D>()->CreateAnimation(L"Bullet", atlas, 1, XMUINT2(5, 79), XMUINT2(34, 2), XMUINT2(10, 10)
		, XMINT2(0, 0), 0.1f);
	bullet->GetComponent<Animator2D>()->Play(L"Bullet", false);
	bullet->GetComponent<BulletMovement>()->mDir = Vector3(direction.x, direction.y, 0.f);
	bullet->GetComponent<Transform>()->SetPosition(position);

	return bullet;
}

void BasicMonsterAI::bleed()
{
	mEffectTime += gDeltaTime;

	if (mEffectTime > 0.03f && false == mRigidbody2D->IsStop())
	{
		mEffectTime = 0.f;

		Vector3 position = mTransform->GetPosition();
		position.y -= 25.f;

		for (int i = 0; i < 4; i++)
		{
			int rand = helper::rand::RandInt(0, 10000) % 20;

			position.x += rand - 10.f;
			position.y += rand - 10.f;

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
}

void BasicMonsterAI::dieEnter()
{	
	KatanaScene* katanaScene = gKatanaZeroSystem->GetCurrentScene();	
	katanaScene->SubEnemyCount();
}

void BasicMonsterAI::liveEnter()
{
	KatanaScene* katanaScene = gKatanaZeroSystem->GetCurrentScene();
	katanaScene->AddEnemyCount();
}
