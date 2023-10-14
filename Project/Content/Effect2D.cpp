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
        GetOwner()->GetComponent<Transform>()->SetPosition(100000.f, 0.f, 0.f);

        Transform* transform = GetOwner()->GetComponent<Transform>();

        transform->SetPosition(10000000.f, 10000000.f, 1.f);
        transform->SetRotation(Vector3::Zero);
        transform->SetScale(2.f, 2.f, 1.f);
        GetOwner()->SetParent(nullptr);
	}

    Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();

    position.x += mDirection.x * mSpeed * gDeltaTime;
    position.y += mDirection.y * mSpeed * gDeltaTime;

    GetOwner()->GetComponent<Transform>()->SetPosition(position);
}

void Effect2D::lateUpdate()
{
}
