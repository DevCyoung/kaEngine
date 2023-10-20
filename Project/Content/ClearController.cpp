#include "pch.h"
#include "ClearController.h"
#include "Components.h"
#include "KatanaZeroSystem.h"

ClearController::ClearController()
    : ScriptComponent(eScriptComponentType::ClearController)
{
}

ClearController::~ClearController()
{
}

void ClearController::initialize()
{
}

void ClearController::update()
{
}

void ClearController::lateUpdate()
{
}

void ClearController::onCollisionEnter(Collider2D* other)
{
    eLayerType layerType = other->GetOwner()->GetLayer();

    if (layerType == eLayerType::Player)
    {
        KatanaScene* scene = gKatanaZeroSystem->GetCurrentScene();

        if (scene->IsClear())
        {
            gKatanaZeroSystem->GameClear();
        }        
	}
}
