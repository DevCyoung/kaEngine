#include "pch.h"
#include "DieController.h"
#include "Components.h"
#include <Engine/EngineMath.h>

DieController::DieController()
    : ScriptComponent(eScriptComponentType::DieController)
{
}

DieController::~DieController()
{
}

void DieController::TurnOnDieText()
{
    for (GameObject* const obj : mBlackImages)
    {
        obj->GetComponentOrNull<RenderComponent>()->TurnOnVisiblelity();
	}

    for (GameObject* const obj : mTexts)
    {
        obj->GetComponentOrNull<RenderComponent>()->TurnOnVisiblelity();
	}
}

void DieController::TurnOffDieText()
{
    for (GameObject* const obj : mBlackImages)
    {
        obj->GetComponentOrNull<RenderComponent>()->TurnOffVisiblelity();
    }

    for (GameObject* const obj : mTexts)
    {
        obj->GetComponentOrNull<RenderComponent>()->TurnOffVisiblelity();
    }
}

void DieController::initialize()
{
}

void DieController::update()
{

    XMUINT4 color = XMUINT4(109, 178, 255, 200);

    int rand = helper::rand::RandInt(-100, 100) % 2;

    

    if (rand == 0)
    {
        color = XMUINT4(255, 255, 255, 200);
    }

    for (GameObject* const obj : mTexts)
    {		                
        obj->GetComponent<EngineText>()->SetColor(color);
	}
}

void DieController::lateUpdate()
{
}
