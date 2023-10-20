#include "pch.h"
#include "KissyfaceAI.h"
#include "Components.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>

#include "AxeMovement.h"
#include <Engine/AfterImage.h>

#include "MonsterAttack.h"

#include <Engine/Scene.h>


#include "HeadMovement.h"
#include "SoundManager.h"

KissyfaceAI::KissyfaceAI()
	: ScriptComponent(eScriptComponentType::KissyfaceAI)
	, mMonsterAttack(nullptr)
	, mBrokenAxe(nullptr)
	, mAnimator2D(nullptr)
	, mRigidbody2D(nullptr)
	, mState(eKissyfaceAIState::None)
	, mDirection(Vector2::Zero)
	, mAxe(nullptr)
	, mLife(0)
	, mHurtTime(0.f)
	, mStruggleTime(0.f)
{	
}

KissyfaceAI::~KissyfaceAI()
{
}

void KissyfaceAI::initialize()
{	
	mMonsterAttack = new GameObject();

	mMonsterAttack->AddComponent<MonsterAttack>();
	mMonsterAttack->AddComponent<RectCollider2D>();

	mMonsterAttack->GetComponent<RectCollider2D>()->SetSize(Vector2(30.f, 50.f));

	mMonsterAttack->SetParent(GetOwner());
	GetOwner()->GetGameSystem()->GetScene()->AddGameObject(mMonsterAttack, eLayerType::MonsterAttack);


	mAnimator2D = GetOwner()->GetComponent<Animator2D>();
	mRigidbody2D = GetOwner()->GetComponent<Rigidbody2D>();

	mState = eKissyfaceAIState::Idle;

	mRigidbody2D->SetVelocityLimit(2000.f);

	mDirection = Vector2::One;

	mDirection.x = 1.f;

	turnOffVisibleAxe();
	turnOffMonsterAttack();

	{
		Animation2D* animation = GetOwner()->GetComponent<Animator2D>()->FindAnimationOrNull(L"Throw");
		std::function<void()> func = std::bind(&KissyfaceAI::throwAxe, this);
		animation->SetFrameEndEvent(6, func);
	}

	{
		Animation2D* animation = GetOwner()->GetComponent<Animator2D>()->FindAnimationOrNull(L"Slash");

		{
			std::function<void()> func = std::bind(&KissyfaceAI::turnOnMonsterAttack, this);
			animation->SetFrameEndEvent(6, func);
		}		

		{
			std::function<void()> func = std::bind(&KissyfaceAI::turnOffMonsterAttack, this);
			animation->SetFrameEndEvent(10, func);
		}
	}

	{
		//spr_kissyface_lungeattack
		Animation2D* animation = GetOwner()->GetComponent<Animator2D>()->FindAnimationOrNull(L"spr_kissyface_lungeattack");

		{
			std::function<void()> func = std::bind(&KissyfaceAI::turnOnMonsterAttack, this);
			animation->SetFrameEndEvent(1, func);
		}

		{
			std::function<void()> func = std::bind(&KissyfaceAI::turnOffMonsterAttack, this);
			animation->SetFrameEndEvent(6, func);
		}
	}
}

void KissyfaceAI::update()
{
	/*GameObject* const player = GameManager::GetInstance()->GetPlayer();
	Transform* const transform = GetOwner()->GetComponent<Transform>();*/


	/*Vector2 direction =  helper::math::GetDirection2D(GetOwner(), player);

	if (direction.x < 0)
	{
		transform->SetFlipx(true);
	}
	else
	{
		transform->SetFlipx(false);
	}*/

	//transform->SetFlipx



	//Change state

	if (mState != eKissyfaceAIState::Slash &&
		mState != eKissyfaceAIState::LungeAttack &&
		mState != eKissyfaceAIState::Struggle)
	{
		turnOffMonsterAttack();
	}

	switch (mState)
	{
	case eKissyfaceAIState::None:
		break;
	case eKissyfaceAIState::Ready:
		break;
	case eKissyfaceAIState::ToBattle:
		break;
	case eKissyfaceAIState::Block:
		block();
		break;
	case eKissyfaceAIState::Idle:
		Idle();
		break;
	case eKissyfaceAIState::Hurt:
		hurt();
		break;
	case eKissyfaceAIState::Recover:
		recover();
		break;
	case eKissyfaceAIState::Slash:
		slash();
		break;
	case eKissyfaceAIState::PreJump:
		preJump();
		break;
	case eKissyfaceAIState::Jump:
		jump();
		break;
	case eKissyfaceAIState::JumpSwing:
		jumpSwing();
		break;
	case eKissyfaceAIState::LandAttack:
		landAttack();
		break;
	case eKissyfaceAIState::PreLunge:
		preLunge();
		break;
	case eKissyfaceAIState::Lunge:
		lunge();
		break;
	case eKissyfaceAIState::LungeAttack:
		lungeAttack();
		break;
	case eKissyfaceAIState::Throw:
		_throw();
		break;
	case eKissyfaceAIState::Tug:
		tug();
		break;
	case eKissyfaceAIState::ReturnAxe:
		returnAxe();
		break;	
	case eKissyfaceAIState::Slice:
		slice();
		break;
	case eKissyfaceAIState::Struggle:
		struggle();
		break;
	case eKissyfaceAIState::Dead:
		break;
	default:
		break;
	}



	if (gInput->GetKeyDown(eKeyCode::Y))
	{
		mAnimator2D->Play(L"Recover", false);
	}
	else if (gInput->GetKeyDown(eKeyCode::NUM3))
	{
		mAnimator2D->Play(L"Hurt", false);
	}
	else if (gInput->GetKeyDown(eKeyCode::NUM4))
	{
		mAnimator2D->Play(L"Idle", false);
	}
	else if (gInput->GetKeyDown(eKeyCode::NUM5))
	{
		mAnimator2D->Play(L"Slash", false);
		mState = eKissyfaceAIState::Slash;		
	}
	else if (gInput->GetKeyDown(eKeyCode::NUM6))
	{
		turnOnVisibleAxe();
		mAnimator2D->Play(L"Throw", false);
		mState = eKissyfaceAIState::Throw;
	}
	else if (gInput->GetKeyDown(eKeyCode::NUM7))
	{
		//mAnimator2D->Play(L"spr_kissyface_returnaxe", false);
		mState = eKissyfaceAIState::Tug;
		mAxe->GetComponent<AxeMovement>()->SetState(eAxeMovementState::Return);
		mAxe->GetComponent<AxeMovement>()->SetStoop(false);
	}
	else if (gInput->GetKeyDown(eKeyCode::NUM8))
	{
		mAnimator2D->Play(L"PreJump", false);
		mState = eKissyfaceAIState::PreJump;

		/*mState = eKissyfaceAIState::JumpSwing;
		mAxe->GetParentOrNull()->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);
		mAxe->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);
		mAxe->GetComponent<Transform>()->SetPosition(0.f, 250.f, 0.f);
		mAxe->GetComponent<AxeMovement>()->SetState(eAxeMovementState::Rotation);        */
	}
	else if (gInput->GetKeyDown(eKeyCode::NUM9))
	{
		mAnimator2D->Play(L"spr_kissyface_prelunge", true);
		mState = eKissyfaceAIState::PreLunge;
	}
	else if (gInput->GetKeyDown(eKeyCode::NUM0))
	{
		mRigidbody2D->SetVelocity(Vector2::Left * 80.f);

		mAnimator2D->Play(L"Block", true);
		mState = eKissyfaceAIState::Block;
	}



}

void KissyfaceAI::lateUpdate()
{
}

void KissyfaceAI::hurt()
{
	mHurtTime += gDeltaTime;

	if (mHurtTime >= 2.f)
	{
		mAnimator2D->Play(L"Recover", false);
		mState = eKissyfaceAIState::Recover;		
	}
}

void KissyfaceAI::recover()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Idle", false);
		mState = eKissyfaceAIState::Idle;
	}
}

void KissyfaceAI::block()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Idle", false);
		mState = eKissyfaceAIState::Idle;
	}
}

void KissyfaceAI::preJump()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Jump", false);
		mState = eKissyfaceAIState::Jump;

		mRigidbody2D->SetVelocity(Vector2::Up * 1000.f);
	}
}


void KissyfaceAI::jump()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"JumpSwing", false);
		mState = eKissyfaceAIState::JumpSwing;

		turnOnVisibleAxe();
		mAxe->GetParentOrNull()->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);
		mAxe->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);
		mAxe->GetComponent<Transform>()->SetPosition(0.f, 100.f, 0.f);
		mAxe->GetComponent<AxeMovement>()->SetState(eAxeMovementState::Rotation);
	}

	//mRigidbody2D->TurnOffGravity();   
}

void KissyfaceAI::jumpSwing()
{
	Physics2D* physics2D = GetOwner()->GetGameSystem()->GetPhysics2D();

	RayCast2DHitInfo hitInfo = {};

	Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();
	Vector2 position2D = Vector2(position.x, position.y);

	//distance 
	float distance = GetOwner()->GetComponent<RectCollider2D>()->GetSize().y / 2.f + 50.f;

	if (physics2D->RayCastHit2D(position2D, Vector2::Down, distance, eLayerType::Wall, &hitInfo))
	{
		turnOffVisibleAxe();
		mAnimator2D->Play(L"LandAttack", false);
		mState = eKissyfaceAIState::LandAttack;
	}
}

void KissyfaceAI::landAttack()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Idle", false);
		mState = eKissyfaceAIState::Idle;
	}
}

void KissyfaceAI::slash()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Idle", false);
		mState = eKissyfaceAIState::Idle;
	}
}

void KissyfaceAI::Idle()
{
	//Slash
	/*mAnimator2D->Play(L"spr_kissyface_slash", true);
	mState = eKissyfaceAIState::Slash;*/

	//Lunge
	if (false == mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		return;
		/*mAnimator2D->Play(L"spr_kissyface_prelunge", true);
		mState = eKissyfaceAIState::PreLunge;*/

		//mAnimator2D->Play(L"Throw", true);
		//mState = eKissyfaceAIState::Throw;


		//mDirection.x *= -1;

	   /* if (mDirection.x < 0.f)
		{
			GetOwner()->GetComponent<Transform>()->SetFlipx(true);
		}
		else
		{
			GetOwner()->GetComponent<Transform>()->SetFlipx(false);
		}*/
	}

	GameObject* player = GameManager::GetInstance()->GetPlayer();


	Vector2 direction = helper::math::GetDirection2D(GetOwner(), player);

	//const float LAND_DISTANCE = 750.f;

	float distance = helper::math::GetDistance2D(GetOwner(), player);


	if (direction.x < 0.f)
	{
		GetOwner()->GetComponent<Transform>()->SetFlipx(true);
		mAxe->GetComponent<MonsterAttack>()->SetAttackDirection(Vector2::Left);
	}
	else
	{
		GetOwner()->GetComponent<Transform>()->SetFlipx(false);
		mAxe->GetComponent<MonsterAttack>()->SetAttackDirection(Vector2::Right);
	}

	

	if (distance >= 350.f)
	{
		
		mAnimator2D->Play(L"spr_kissyface_prelunge", true);
		mState = eKissyfaceAIState::PreLunge;

		if (helper::rand::RandInt(0, 10000) % 2 == 0)
		{
			
		}
		else
		{
			/*turnOnVisibleAxe();

			mAnimator2D->Play(L"Throw", false);
			mState = eKissyfaceAIState::Throw;*/
		}		
	}
	else if (distance >= 300.f)
	{
		turnOnVisibleAxe();

		mAnimator2D->Play(L"Throw", false);
		mState = eKissyfaceAIState::Throw;
	}
	else if (distance >= 200.f)
	{
		mAnimator2D->Play(L"PreJump", false);
		mState = eKissyfaceAIState::PreJump;
	}
	else if (distance >= 150.f)
	{
		mAnimator2D->Play(L"Slash", false);
		mState = eKissyfaceAIState::Slash;
	}
	else 
	{
		if (helper::rand::RandInt(0, 10000) % 2 == 0)
		{
			mAnimator2D->Play(L"Slash", false);
			mState = eKissyfaceAIState::Slash;
		}
		else
		{
			/*mAnimator2D->Play(L"PreJump", false);
			mState = eKissyfaceAIState::PreJump;*/
		}
	}


	(void)distance;



}

void KissyfaceAI::preLunge()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"spr_kissyface_lunge", true);
		mState = eKissyfaceAIState::Lunge;

		Vector2 velocity = Vector2(1100.f, 400.f);

		if (GetOwner()->GetComponent<Transform>()->GetFlipX())
		{
			velocity = Vector2(-1100.f, 400.f);
		}

		mRigidbody2D->SetVelocity(velocity);
	}
}

void KissyfaceAI::lunge()
{

	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"spr_kissyface_lungeattack", true);
		mState = eKissyfaceAIState::LungeAttack;

		Vector2 velocity = mRigidbody2D->GetVelocity();
		velocity.x = 0.f;
		mRigidbody2D->SetVelocity(velocity);
	}

	//mRigidbody2D->AddForce(Vector2(100.f, 200.f));
}

void KissyfaceAI::lungeAttack()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Idle", true);
		mState = eKissyfaceAIState::Idle;
	}
}

void KissyfaceAI::_throw()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		//mAnimator2D->Play(L"spr_kissyface_tug", true);
		//mState = eKissyfaceAIState::Tug;
		if (mAxe->GetComponent<AxeMovement>()->IsStoop())
		{
			mState = eKissyfaceAIState::Tug;
			mAxe->GetComponent<AxeMovement>()->SetState(eAxeMovementState::Return);
			mAxe->GetComponent<AxeMovement>()->SetStoop(false);
		}
		

	}
}

void KissyfaceAI::tug()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		//mAnimator2D->Play(L"spr_kissyface_returnaxe", true);
		//mState = eKissyfaceAIState::ReturnAxe;        

	}

	float distance = helper::math::GetDistance2D(GetOwner(), mAxe);

	if (distance < 100.f)
	{
		mAnimator2D->Play(L"spr_kissyface_returnaxe", true);
		mState = eKissyfaceAIState::ReturnAxe;

		turnOffVisibleAxe();
	}


}

void KissyfaceAI::returnAxe()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"Idle", true);
		mState = eKissyfaceAIState::Idle;
	}
}

void KissyfaceAI::slice()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{	
		mAnimator2D->Play(L"Dead", true);
		mState = eKissyfaceAIState::Dead;

		GameObject* player = GetOwner()->GetGameSystem()->FindGameObject(L"Player");

		player->GetComponent<Animator2D>()->TurnOnVisiblelity();
		//player->GetComponent<AfterImage>()->TurnOnVisiblelity();

		Vector3 playerPosition = player->GetComponent<Transform>()->GetPosition();

		if (GetOwner()->GetComponent<Transform>()->GetFlipX())
		{			
			playerPosition.x = GetOwner()->GetComponent<Transform>()->GetPosition().x - 40.f;
			player->GetComponent<Transform>()->SetFlipx(false);
		}
		else
		{			
			playerPosition.x = GetOwner()->GetComponent<Transform>()->GetPosition().x + 40.f;
			player->GetComponent<Transform>()->SetFlipx(true);
		}

		player->GetComponent<Transform>()->SetPosition(playerPosition);

		mBrokenAxe->GetComponent<Animator2D>()->TurnOnVisiblelity();
	}
}

void KissyfaceAI::struggle()
{
	mStruggleTime += gDeltaTime;	

	if (gInput->GetKey(eKeyCode::LBTN) && mStruggleTime >= 2.f)
	{
		--mLife;

		GameObject* player = GetOwner()->GetGameSystem()->FindGameObject(L"Player");

		if (mLife < 0)
		{
			mAnimator2D->Play(L"Slice", false);
			mState = eKissyfaceAIState::Slice;

			player->GetComponent<Animator2D>()->TurnOffVisiblelity();
			player->GetComponent<AfterImage>()->TurnOffVisiblelity();

		}
		else
		{
			mAnimator2D->Play(L"Recover", false);
			mState = eKissyfaceAIState::Recover;

			

			player->GetComponent<Animator2D>()->TurnOnVisiblelity();
			player->GetComponent<AfterImage>()->TurnOnVisiblelity();

			Vector3 playerPosition = player->GetComponent<Transform>()->GetPosition();

			if (GetOwner()->GetComponent<Transform>()->GetFlipX())
			{
				mAxe->GetComponent<MonsterAttack>()->SetAttackDirection(Vector2::Left);
				playerPosition.x = GetOwner()->GetComponent<Transform>()->GetPosition().x - 50.f;
			}
			else
			{
				mAxe->GetComponent<MonsterAttack>()->SetAttackDirection(Vector2::Right);
				playerPosition.x = GetOwner()->GetComponent<Transform>()->GetPosition().x + 50.f;
			}

			turnOnMonsterAttack();
			player->GetComponent<Transform>()->SetPosition(playerPosition);
		}

		

	}
	else if (false == gInput->GetKey(eKeyCode::LBTN))
	{
		mAnimator2D->Play(L"Recover", false);
		mState = eKissyfaceAIState::Recover;

		GameObject* player = GetOwner()->GetGameSystem()->FindGameObject(L"Player");

		player->GetComponent<Animator2D>()->TurnOnVisiblelity();
		player->GetComponent<AfterImage>()->TurnOnVisiblelity();

		Vector3 playerPosition = player->GetComponent<Transform>()->GetPosition();

		if (GetOwner()->GetComponent<Transform>()->GetFlipX())
		{
			mAxe->GetComponent<MonsterAttack>()->SetAttackDirection(Vector2::Left);
			playerPosition.x = GetOwner()->GetComponent<Transform>()->GetPosition().x - 50.f;
		}
		else
		{
			mAxe->GetComponent<MonsterAttack>()->SetAttackDirection(Vector2::Right);
			playerPosition.x = GetOwner()->GetComponent<Transform>()->GetPosition().x + 50.f;
		}

		turnOnMonsterAttack();
		player->GetComponent<Transform>()->SetPosition(playerPosition);
	}
}

void KissyfaceAI::throwAxe()
{
	mAxe->GetComponent<AxeMovement>()->SetState(eAxeMovementState::Throw);

	turnOnVisibleAxe();

	Vector3 position = mAxe->GetComponent<Transform>()->GetPosition();
	position.y = 0.f;
	position.x = 100.f;
	mAxe->GetComponent<Transform>()->SetPosition(position);
}

void KissyfaceAI::turnOnVisibleAxe()
{
	mAxe->GetComponent<Animator2D>()->TurnOnVisiblelity();
	mAxe->GetComponent<AfterImage>()->TurnOnVisiblelity();
	mAxe->GetComponent<AxeMovement>()->SetStoop(false);
}

void KissyfaceAI::turnOffVisibleAxe()
{
	mAxe->GetComponent<Animator2D>()->TurnOffVisiblelity();
	mAxe->GetComponent<AfterImage>()->TurnOffVisiblelity();
	mAxe->GetComponent<AxeMovement>()->SetStoop(true);

	Vector3 position = mAxe->GetComponent<Transform>()->GetPosition();
	position.y = 100000.f;
	position.x = 100000.f;
	mAxe->GetComponent<Transform>()->SetPosition(position);
}

void KissyfaceAI::turnOnMonsterAttack()
{
	//(void)offset;
	Vector3 position = Vector3::Right * 50.f;
	mMonsterAttack->GetComponent<Transform>()->SetPosition(position);

	if (GetOwner()->GetComponent<Transform>()->GetFlipX())
	{
		mMonsterAttack->GetComponent<MonsterAttack>()->SetAttackDirection(Vector2::Left);
	}
	else
	{
		mMonsterAttack->GetComponent<MonsterAttack>()->SetAttackDirection(Vector2::Right);
	}
}

void KissyfaceAI::turnOffMonsterAttack()
{
	mMonsterAttack->GetComponent<Transform>()->SetPosition(100000.f, 100000.f, 100000.f);
}


void KissyfaceAI::onCollisionEnter(Collider2D* other)
{
	if (other->GetOwner()->GetLayer() == eLayerType::PlayerAttack)
	{
		GameObject* player = GetOwner()->GetGameSystem()->FindGameObject(L"Player");

		if (mState == eKissyfaceAIState::Hurt)
		{
			mAnimator2D->Play(L"Struggle", true);
			mState = eKissyfaceAIState::Struggle;
			mStruggleTime = 0.f;
			player->GetComponent<Animator2D>()->TurnOffVisiblelity();
			player->GetComponent<AfterImage>()->TurnOffVisiblelity();

			Vector2 direction = helper::math::GetDirection2D(player, GetOwner());

			if (direction.x < 0.f)
			{
				GetOwner()->GetComponent<Transform>()->SetFlipx(false);
			}
			else
			{
				GetOwner()->GetComponent<Transform>()->SetFlipx(true);
			}

		}
		else if (mState == eKissyfaceAIState::Dead)
		{
			mAnimator2D->Play(L"NoHead", false);
			mState = eKissyfaceAIState::NoHead;

			Vector2 direction = helper::math::GetDirection2D(player, mHead);

			mHead->GetComponent<HeadMovement>()->TurnOnHead(direction);
		}
		else if (mState == eKissyfaceAIState::NoHead)
		{

		}
		else if (isAttackable())
		{

			mHurtTime = 0.f;
			mAnimator2D->Play(L"Hurt", false);
			mState = eKissyfaceAIState::Hurt;

			Vector2 damagedScale = Vector2(550.f, 400.f);

			if (helper::math::GetDirection2D(player, GetOwner()).x > 0.f)
			{
				GetOwner()->GetComponent<Transform>()->SetFlipx(true);
			}
			else
			{
				GetOwner()->GetComponent<Transform>()->SetFlipx(false);
				damagedScale.x *= -1.f;
			}

			gSoundManager->Play(eResAudioClip::enemySlice, 1.f);

			mRigidbody2D->SetVelocity(damagedScale);			
		}
		else
		{			
			float blockSpeed = 130.f;
			Vector2 blockDirection = Vector2::Left;

			if (GetOwner()->GetComponent<Transform>()->GetFlipX())
			{
				blockDirection = Vector2::Right;
			}

			mRigidbody2D->SetVelocity(blockDirection * blockSpeed);
			mAnimator2D->Play(L"Block", true);
			mState = eKissyfaceAIState::Block;

			gSoundManager->Play(eResAudioClip::block, 1.f);

			Vector2 playerBlockDirection = helper::math::GetDirection2D(GetOwner(), player);
			Vector2 playerBlockSpeed = Vector2(300.f, 100.f);

			if (playerBlockDirection.x < 0.f)
			{
				playerBlockSpeed.x *= -1.f;
			}

			player->GetComponent<Rigidbody2D>()->SetVelocity(playerBlockSpeed);
		}		
	}
}

bool KissyfaceAI::isAxeInHand()
{
	return false;
}

bool KissyfaceAI::isAttackable()
{
	GameObject* player = GetOwner()->GetGameSystem()->FindGameObject(L"Player");
	Vector2 direction = helper::math::GetDirection2D(player, GetOwner());

	if (GetOwner()->GetComponent<Transform>()->GetFlipX() && direction.x > 0.f)
	{
		return false;
	}
	else if (false == GetOwner()->GetComponent<Transform>()->GetFlipX() && direction.x < 0.f)
	{
		return false;
	}

	return true;

	//return GetOwner()->GetComponent<Transform>()->GetFlipX();

	////front
	//if (/*front*/)
	//{		
	//	return true;
	//}

	////back

	//return false;
}
