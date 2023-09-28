#include "pch.h"
#include "AxeMovement.h"
#include "Components.h"
#include <Engine/EngineMath.h>

AxeMovement::AxeMovement()
    : ScriptComponent(eScriptComponentType::AxeMovement)
    , mbStoop(false)
    , mState(eAxeMovementState::None)
    , mKissyface(nullptr)
    , mRotationDistance(0.f)
    , mRotationCount(1)
{
}

AxeMovement::~AxeMovement()
{
}

void AxeMovement::initialize()
{
    mRotationDistance = 100.f;
}

void AxeMovement::update()
{
    if (mbStoop)
    {
        return;
    }

    

    
    switch (mState)
    {
    case eAxeMovementState::None:
        break;
    case eAxeMovementState::Idle:
        break;
    case eAxeMovementState::Throw:
    {
        Vector3 angle = GetOwner()->GetComponent<Transform>()->GetRotation();
        angle.z -= gDeltaTime * 360.f * 3.f;
        GetOwner()->GetComponent<Transform>()->SetRotation(angle);

        Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();
        position.x += gDeltaTime * 1000.f;
        GetOwner()->GetComponent<Transform>()->SetPosition(position);
    }
        break;
    case eAxeMovementState::Return:
    {
        Vector3 angle = GetOwner()->GetComponent<Transform>()->GetRotation();
        angle.z += gDeltaTime * 360.f * 3.f;
        GetOwner()->GetComponent<Transform>()->SetRotation(angle);

        Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();
        position.x -= gDeltaTime * 1000.f;
        GetOwner()->GetComponent<Transform>()->SetPosition(position);
    }
        break;
    case eAxeMovementState::Rotation:
    {
        float axeRotationSpeed = 2.f;

        Vector3 angle = GetOwner()->GetParentOrNull()->GetComponent<Transform>()->GetRotation();
        angle.z += gDeltaTime * 360.f * axeRotationSpeed;
        GetOwner()->GetParentOrNull()->GetComponent<Transform>()->SetRotation(angle);

        Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();
        //position.y -= gDeltaTime * 170.f;

        if (angle.z >= 360 * mRotationCount)
        {            
            mbStoop = true;
		}

        GetOwner()->GetComponent<Transform>()->SetPosition(position);
    }
    default:
        break;
    }
}

void AxeMovement::lateUpdate()
{
}

void AxeMovement::onCollisionEnter(Collider2D* other)
{
    if (other->GetOwner()->GetLayer() == eLayerType::Wall && mState == eAxeMovementState::Throw)
    {
        mbStoop = true;
		//GetOwner()->SetEnable(false);

        Vector3 angle = GetOwner()->GetComponent<Transform>()->GetRotation();
        angle.z = 60.f;
        GetOwner()->GetComponent<Transform>()->SetRotation(angle);
	}
}
