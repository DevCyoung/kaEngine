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

    mDirection.x = -1.f;


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
    case eKissyfaceAIState::Idle:
        Idle();
        break;
    case eKissyfaceAIState::Block:
        break;
    case eKissyfaceAIState::Hurt:
        break;
    case eKissyfaceAIState::Slash:
        slash();
        break;
    case eKissyfaceAIState::Jump:
        break;
    case eKissyfaceAIState::JumpSwing:
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
    case eKissyfaceAIState::Recover:
        break;
    case eKissyfaceAIState::Dead:
        break;
    default:
        break;
    }


    if (gInput->GetKeyDown(eKeyCode::NUM5))
    {
        mAnimator2D->Play(L"spr_kissyface_idle", false);
    }
    else if (gInput->GetKeyDown(eKeyCode::NUM6))
    {
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
        mAxe->GetComponent<AfterImage>()->TurnOnVisiblelity();
        mAxe->GetComponent<Animator2D>()->TurnOnVisiblelity();
        mAxe->GetComponent<AxeMovement>()->SetState(eAxeMovementState::Rotation);

        mAxe->GetComponent<Transform>()->SetPosition(0.f, 150.f, 0.f);        
    }



}

void KissyfaceAI::lateUpdate()
{
}

void KissyfaceAI::slash()
{
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
        mRigidbody2D->SetVelocity(Vector2(1100.f, 400.f) * mDirection);
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
        mAnimator2D->Play(L"spr_kissyface_idle", true);
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

    float distance =  helper::math::GetDistance2D(GetOwner(), mAxe);

    if (distance < 100.f)
    {
        mAnimator2D->Play(L"spr_kissyface_returnaxe", true);
        mState = eKissyfaceAIState::ReturnAxe;

        mAxe->GetComponent<Animator2D>()->TurnOffVisiblelity();        
        mAxe->GetComponent<AfterImage>()->TurnOffVisiblelity();
        mAxe->GetComponent<AxeMovement>()->SetStoop(true);

    }


}

void KissyfaceAI::returnAxe()
{
    if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
    {
        mAnimator2D->Play(L"spr_kissyface_idle", true);
        mState = eKissyfaceAIState::Idle;
        
    }
}

void KissyfaceAI::throwAxe()
{
    mAxe->GetComponent<AxeMovement>()->SetState(eAxeMovementState::Throw);

    mAxe->GetComponent<Animator2D>()->TurnOnVisiblelity();
    mAxe->GetComponent<AfterImage>()->TurnOnVisiblelity();
    mAxe->GetComponent<AxeMovement>()->SetStoop(false);

    Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();
    position.x += 100.f;
    mAxe->GetComponent<Transform>()->SetPosition(position);
}
