#include "pch.h"
#include "KissyfaceAI.h"
#include "Components.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>

#include "AxeMovement.h"
#include <Engine/AfterImage.h>

KissyfaceAI::KissyfaceAI()
	: ScriptComponent(eScriptComponentType::KissyfaceAI)
	, mAnimator2D(nullptr)
	, mRigidbody2D(nullptr)
	, mState(eKissyfaceAIState::None)
	, mDirection(Vector2::Zero)
	, mAxe(nullptr)
	, mLife(3)
	, mHurtTime(0.f)
{
}

KissyfaceAI::~KissyfaceAI()
{
}

void KissyfaceAI::initialize()
{
	mAnimator2D = GetOwner()->GetComponent<Animator2D>();
	mRigidbody2D = GetOwner()->GetComponent<Rigidbody2D>();

	mState = eKissyfaceAIState::Idle;

	mRigidbody2D->SetVelocityLimit(2000.f);

	mDirection = Vector2::One;

	mDirection.x = 1.f;

	turnOffVisibleAxe();

	Animation2D* animation = GetOwner()->GetComponent<Animator2D>()->FindAnimationOrNull(L"Throw");

	{
		std::function<void()> func = std::bind(&KissyfaceAI::throwAxe, this);
		animation->SetFrameEndEvent(6, func);
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
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
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

}

void KissyfaceAI::preLunge()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator2D->Play(L"spr_kissyface_lunge", true);
		mState = eKissyfaceAIState::Lunge;

		if (mDirection.x > 0.f)
		{
			GetOwner()->GetComponent<Transform>()->SetFlipx(false);
		}
		else
		{
			GetOwner()->GetComponent<Transform>()->SetFlipx(true);
		}

		mRigidbody2D->SetVelocity(Vector2(1100.f, 400.f) * mDirection);
		mDirection.x *= -1.f;
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

void KissyfaceAI::onCollisionEnter(Collider2D* other)
{
	if (other->GetOwner()->GetLayer() == eLayerType::Default)
	{
		GameObject* player = GetOwner()->GetGameSystem()->FindGameObject(L"Player");

		if (isAttackable())
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
