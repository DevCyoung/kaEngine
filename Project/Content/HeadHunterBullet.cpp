#include "pch.h"
#include "HeadHunterBullet.h"
#include "Components.h"
#include "GameObjectBuilder.h"
#include <Engine/Scene.h>
#include <Engine/EngineMath.h>
#include "GameManager.h"
#include "MonsterAttack.h"
HeadHunterBullet::HeadHunterBullet()
    : ScriptComponent(eScriptComponentType::HeadHunterBullet)
    , mCircle(nullptr)
    , mState(eHeadHunterBulletState::Idle)
    , mBoomTime(0.f)
{
    
    
}

HeadHunterBullet::~HeadHunterBullet()
{
}

void HeadHunterBullet::initialize()
{
    mCircle->GetComponent<Transform>()->SetScale(0.f, 0.f, 1.f);
}

void HeadHunterBullet::update()
{


    int rand = helper::rand::RandInt(0, 100) % 2;

    if (rand == 0)
    {
        mCircle->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();
    }
    else
    {
        mCircle->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();
    }


    switch (mState)
    {
    case eHeadHunterBulletState::Idle:
    {
        Vector3 scale = mCircle->GetComponent<Transform>()->GetScale();
        scale.x += gDeltaTime * 2.f;
        scale.y += gDeltaTime * 2.f;

        Vector3 rot = GetOwner()->GetComponent<Transform>()->GetRotation();
        rot.z += gDeltaTime * 360.f;

        if (scale.x >= 2.f)
        {     
            mState = eHeadHunterBulletState::Boom;
            gSoundManager->Play(eResAudioClip::HeadHunter_arlam);            
        }

        mCircle->GetComponent<Transform>()->SetScale(scale);
        GetOwner()->GetComponent<Transform>()->SetRotation(rot);
    }        
        break;
    case eHeadHunterBulletState::Shot:
    {
        GetOwner()->GetGameSystem()->GetScene()->RegisterEventSetDestroy(mCircle);
        GetOwner()->GetGameSystem()->GetScene()->RegisterEventSetDestroy(GetOwner());
    }
        break;
    case eHeadHunterBulletState::Boom:
    {
        mBoomTime += gDeltaTime;

       /* Vector3 scale = mCircle->GetComponent<Transform>()->GetScale();
        scale.x -= gDeltaTime * 2.f;
        scale.y -= gDeltaTime * 2.f;
        mCircle->GetComponent<Transform>()->SetScale(scale);*/

        if (mBoomTime >= 0.5f)
        {
            mState = eHeadHunterBulletState::Shot;
            gSoundManager->Play(eResAudioClip::HeadHunter_explo1, 1.f);

            Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

            for (int i = 0; i < 15; i++)
            {                
                int offsetX = helper::rand::RandInt(-75, 75);
                int offsetY = helper::rand::RandInt(-75, 75);

                Vector3 nextPos = pos;
                nextPos.x += offsetX;
                nextPos.y += offsetY;

                gEffectManager->Shot(L"Explosion1", nextPos);

            }

            GameObject* const monsterAttack = new GameObject();
            monsterAttack->AddComponent<RectCollider2D>();
            monsterAttack->AddComponent<MonsterAttack>();

            monsterAttack->GetComponent<MonsterAttack>()->Shot(0.2f, pos, Vector2(150.f, 150.f));
            GetOwner()->GetGameSystem()->GetScene()->RegisterEventAddGameObject(monsterAttack, eLayerType::MonsterAttack);            
        }
    }
        
        break;
    default:
        break;
    }
        


 

    
}

void HeadHunterBullet::lateUpdate()
{
}
