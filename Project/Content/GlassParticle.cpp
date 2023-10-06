#include "pch.h"
#include "GlassParticle.h"
#include "Components.h"
#include "ResourceManager.h"

GlassParticle::GlassParticle()
    : ScriptComponent(eScriptComponentType::GlassParticle)
    , mbRotation(true)
{
}

GlassParticle::~GlassParticle()
{
}

void GlassParticle::Shot(const std::wstring& animName, Vector2 velocity)
{
    Animator2D* anim = GetOwner()->GetComponent<Animator2D>();
	anim->Play(animName, true);
	GetOwner()->GetComponent<Rigidbody2D>()->SetVelocity(velocity);
}

void GlassParticle::initialize()
{
}

void GlassParticle::update()
{
    if (mbRotation)
    {
        Transform* transform = GetOwner()->GetComponent<Transform>();
        Vector3 rotation = transform->GetRotation();
        rotation.z += gDeltaTime * 720.f;
        transform->SetRotation(rotation);
    }  
}

void GlassParticle::lateUpdate()
{
}

void GlassParticle::onCollisionEnter(Collider2D* other)
{
    (void)other;
}
