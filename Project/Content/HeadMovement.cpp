#include "pch.h"
#include "HeadMovement.h"
#include "Components.h"

HeadMovement::HeadMovement()
    : ScriptComponent(eScriptComponentType::HeadMovement)
    , mbTurnOnHead(false)
    , mState(eHeadState::None)
{
}

HeadMovement::~HeadMovement()
{
}

void HeadMovement::TurnOnHead(Vector2 direction)
{
    GetOwner()->GetComponent<Animator2D>()->Play(L"HeadFly", true);
    GetOwner()->GetComponent<Animator2D>()->TurnOnVisiblelity();

    Vector3 position = GetOwner()->GetComponent<Transform>()->GetWorldMatrix().Translation();
    GetOwner()->SetParent(nullptr);
    GetOwner()->GetComponent<Transform>()->SetPosition(position);

    GetOwner()->GetComponent<Rigidbody2D>()->TurnOnGravity();
    GetOwner()->GetComponent<Rigidbody2D>()->SetVelocityLimit(3000.f);

    if (direction.x < 0.f)
    {
        GetOwner()->GetComponent<Rigidbody2D>()->SetVelocity(Vector2(-1300.f, 700.f));
    }   
    else
    {
        GetOwner()->GetComponent<Rigidbody2D>()->SetVelocity(Vector2(1300.f, 700.f));
    }

    mState = eHeadState::Fly;

    mbTurnOnHead = true;
}

void HeadMovement::initialize()
{
}

void HeadMovement::update()
{
    if (false == mbTurnOnHead)
    {
        return;
    }

    switch (mState)
    {
    case eHeadState::None:
        break;
    case eHeadState::Fly:
    {
        if (GetOwner()->GetComponent<Animator2D>()->GetCurAnimationOrNull()->IsFinished())
        {
            mState = eHeadState::FlyLoop;
            GetOwner()->GetComponent<Animator2D>()->Play(L"HeadFlyLoop", true);
        }
    }
        break;
    case eHeadState::FlyLoop:
        break;
    case eHeadState::Land:
        break;
    default:
        break;
    }
}

void HeadMovement::lateUpdate()
{
}

void HeadMovement::onCollisionEnter(Collider2D* other)
{
    if (other->GetOwner()->GetLayer() == eLayerType::Wall)
    {
        if (other->GetSize().y > other->GetSize().x)
        {
            Vector2 velocity = GetOwner()->GetComponent<Rigidbody2D>()->GetVelocity();			
            velocity.x *= -0.3f;

            /*if (velocity.x < 0.f)
            {
                
            }
            else
            {
                velocity.x = -300.f;
            }*/
            

            Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();
            position.x -= 10.f;
            GetOwner()->GetComponent<Transform>()->SetPosition(position);

            GetOwner()->GetComponent<Rigidbody2D>()->SetVelocity(velocity);

		}
        else
        {
            if (GetOwner()->GetComponent<Rigidbody2D>()->GetVelocity().x < 0.f)
            {
                GetOwner()->GetComponent<Transform>()->SetFlipx(true);
			}
            else
            {
                GetOwner()->GetComponent<Transform>()->SetFlipx(false);
            }

            GetOwner()->GetComponent<Animator2D>()->Play(L"HeadLand", false);
            mState = eHeadState::Land;
        }
    }
}
