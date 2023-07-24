#include "pch.h"
#include "Rect2DInterpolation.h"
#include "Components.h"

Rect2DInterpolation::Rect2DInterpolation()
    : ScriptComponent(eScriptComponentType::Rect2DInterpolation)
{
}

Rect2DInterpolation::~Rect2DInterpolation()
{
}

void Rect2DInterpolation::initialize()
{
}

void Rect2DInterpolation::update()
{
}

void Rect2DInterpolation::lateUpdate()
{
}

void Rect2DInterpolation::onCollisionEnter(Collider2D* other)
{
    Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

    rigidbody->TurnOnGround();
    rigidbody->TurnOffGravity();
    rigidbody->SetVelocity(Vector2::Zero);

    (void)other;
}

void Rect2DInterpolation::onCollisionStay(Collider2D* other)
{
    

    (void)other;
}

void Rect2DInterpolation::onCollisionExit(Collider2D* other)
{
    Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

    rigidbody->TurnOffGround();
    rigidbody->TurnOnGravity();

    (void)other;
}
