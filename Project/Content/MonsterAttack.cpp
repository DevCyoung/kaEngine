#include "pch.h"
#include "MonsterAttack.h"
#include "Components.h"

MonsterAttack::MonsterAttack()
    : ScriptComponent(eScriptComponentType::MonsterAttack)
    , mAttackDirection(Vector2::Zero)
    , mbAttackAble(true)
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
}

void MonsterAttack::lateUpdate()
{
}
