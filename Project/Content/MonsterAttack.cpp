#include "pch.h"
#include "MonsterAttack.h"
#include "Components.h"
#include <Engine/Scene.h>
MonsterAttack::MonsterAttack()
    : ScriptComponent(eScriptComponentType::MonsterAttack)
    , mAttackDirection(Vector2::Zero)
    , mbAttackAble(true)
    , mbShot(false)
    , mbBack(false)
    , mShotTime(0.f)
{
}

MonsterAttack::~MonsterAttack()
{
}

void MonsterAttack::initialize()
{
}

void MonsterAttack::update()
{
    if (mbShot)
    {
        mShotTime -= gDeltaTime;

        if (mShotTime <= 0.f)
        {
            GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(100000,-100000,1.f));
            GetOwner()->GetComponent<RectCollider2D>()->SetSize(1.f, 1.f);
            GetOwner()->GetGameSystem()->GetScene()->RegisterEventSetDestroy(GetOwner());
            mbShot = false;
        }        
    }
}

void MonsterAttack::lateUpdate()
{
}

void MonsterAttack::Shot(float time, Vector3 position, Vector2 scale)
{
    GetOwner()->GetComponent<Transform>()->SetPosition(position);
    GetOwner()->GetComponent<RectCollider2D>()->SetSize(scale.x, scale.y);


    mbShot = true;
    mShotTime = time;
}
