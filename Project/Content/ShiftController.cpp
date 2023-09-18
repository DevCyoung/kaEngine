#include "pch.h"
#include "ShiftController.h"
#include "Components.h"
#include "ResourceManager.h"
#include <Engine/InputManager.h>

ShiftController::ShiftController()
    : ScriptComponent(eScriptComponentType::ShiftController)
    , mTimeScale(1.f)
    , mPlayer(nullptr)
{
}

ShiftController::~ShiftController()
{
}

void ShiftController::initialize()
{
    mLight = GetOwner()->GetGameSystem()->FindGameObject(L"GlobalLight2D")->GetComponent<Light2D>();
    //mPlayer = GetOwner()->GetGameSystem()->FindGameObject(L"Player");
}

void ShiftController::update()
{     
    if (nullptr == mPlayer)
    {
        return;
    }

    Material* const material = mPlayer->GetComponent<Animator2D>()->GetMaterial();
    
    if (gInput->GetKey(eKeyCode::LSHIFT))
    {
        GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(gResourceManager->FindOrNull<Material>(L"UIShift01"));

        mTimeScale -= gDeltaTime * 4.f;

        material->SetShader(gResourceManager->Find<Shader>(L"Animation2D"));

        if (mTimeScale <= 0.15f)
        {
            mTimeScale = 0.15f;
        }

        
    }
    else
    {
        GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(gResourceManager->FindOrNull<Material>(L"UIShift00"));

        mTimeScale += gDeltaTime * 10.f;

        material->SetShader(gResourceManager->Find<Shader>(L"LightAnimation2D"));

        //Animation2D
        if (mTimeScale >= 1.f)
        {
            mTimeScale = 1.f;
        }


        
    }

    TimeManager::GetInstance()->SetTileScale(mTimeScale);
    mLight->SetLightDiffuse(Vector3::One * mTimeScale);
}

void ShiftController::lateUpdate()
{
}

