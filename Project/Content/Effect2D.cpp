#include "pch.h"
#include "Effect2D.h"
#include "Components.h"

Effect2D::Effect2D()
    : ScriptComponent(eScriptComponentType::Effect2D)
    , mDirection(Vector2::Zero)
    , mSpeed(0.f)
{

}

Effect2D::~Effect2D()
{
}

void Effect2D::initialize()
{
}

void Effect2D::update()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();
    Animation2D* const animation = animator->GetCurAnimationOrNull();

    if (animation && animation->IsFinished())
    {
        animator->TurnOffVisiblelity();
	}

    Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();

    position.x += mDirection.x * mSpeed * gDeltaTime;
    position.y += mDirection.y * mSpeed * gDeltaTime;

    GetOwner()->GetComponent<Transform>()->SetPosition(position);
}

void Effect2D::lateUpdate()
{
}
