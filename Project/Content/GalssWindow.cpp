#include "pch.h"
#include "GalssWindow.h"
#include "Components.h"
#include "GlassParticle.h"
#include "GameManager.h"
#include "Rect2DInterpolation.h"
#include "RewindComponent.h"
#include <Engine/EngineMath.h>


GalssWindow::GalssWindow()
    : ScriptComponent(eScriptComponentType::GalssWindow)
{
}

GalssWindow::~GalssWindow()
{
}

void GalssWindow::initialize()
{
}

void GalssWindow::update()
{
}

void GalssWindow::lateUpdate()
{
}

GameObject* GalssWindow::InstantiateGlass()
{
    GameObject* glassParticle = new GameObject();
    glassParticle->AddComponent<Animator2D>();

    glassParticle->AddComponent<Rigidbody2D>();
    glassParticle->AddComponent<GlassParticle>();
    glassParticle->AddComponent<RectCollider2D>();
    glassParticle->AddComponent<RewindComponent>();


    glassParticle->GetComponent<RectCollider2D>()->SetSize(20.f, 20.f);


    Animator2D* anim = glassParticle->GetComponent<Animator2D>();
    Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Particle_particle);


    glassParticle->GetComponent<Rigidbody2D>()->TurnOnGravity();
    glassParticle->GetComponent<Rigidbody2D>()->SetGravityAccel(1800.f);

    anim->CreateAnimation(L"spr_glassshard_1_0", atlas, 1, XMUINT2(5, 161), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_1", atlas, 1, XMUINT2(5, 207), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_2", atlas, 1, XMUINT2(5, 253), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_3", atlas, 1, XMUINT2(5, 299), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_4", atlas, 1, XMUINT2(5, 345), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);

    anim->CreateAnimation(L"spr_glassshard_1_ground_0", atlas, 1, XMUINT2(5, 391), XMUINT2(5, 4), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_ground_1", atlas, 1, XMUINT2(5, 434), XMUINT2(5, 4), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_ground_2", atlas, 1, XMUINT2(5, 477), XMUINT2(5, 4), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_ground_3", atlas, 1, XMUINT2(5, 520), XMUINT2(5, 4), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_white_0", atlas, 1, XMUINT2(5, 563), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_white_1", atlas, 1, XMUINT2(5, 609), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_white_2", atlas, 1, XMUINT2(5, 655), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_white_3", atlas, 1, XMUINT2(5, 701), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->CreateAnimation(L"spr_glassshard_1_white_4", atlas, 1, XMUINT2(5, 747), XMUINT2(5, 7), XMUINT2(10, 10), XMINT2(0, 0), 0.125f);
    anim->Play(L"spr_glassshard_1_0", true);

    glassParticle->GetComponent<Rigidbody2D>()->SetVelocity(Vector2(300.f, 100.f));
    Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

    glassParticle->GetComponent<Transform>()->SetPosition(pos);
    glassParticle->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
    GetOwner()->GetGameSystem()->GetScene()->RegisterEventAddGameObject(glassParticle, eLayerType::Object);

    return glassParticle;
}

void GalssWindow::onCollisionEnter(Collider2D* other)
{
    if (other->GetOwner()->GetLayer() == eLayerType::PlayerAttack)
    {
        gSoundManager->Play(eResAudioClip::glassbreak, 1.f);

        for (int i = 0; i < 10; ++i)
        {            
            int offsetX = helper::rand::RandInt(-1, 30);
            int offsetY = helper::rand::RandInt(-4, 30);

            GameObject* glassParticle = InstantiateGlass();
            glassParticle->GetComponent<Rigidbody2D>()->SetVelocity(Vector2(200.f * offsetX, -200.f + i * 30 * offsetY));

            Vector3 pos = glassParticle->GetComponent<Transform>()->GetPosition();
            pos.x += offsetX - 20;
            pos.y += offsetY - 20;
        }
        GetOwner()->GetComponent<Transform>()->SetPosition(1000000.f, 1000000.f, 1.f);
    }
}
