#include "pch.h"
#include "ShiftController.h"
#include "Components.h"
#include "ResourceManager.h"
#include <Engine/InputManager.h>
#include "GameManager.h"
#include  <Engine/AfterImage.h>

ShiftController::ShiftController()
    : ScriptComponent(eScriptComponentType::ShiftController)
    , mLight(nullptr)    
    , mPlayer(nullptr)
    , mBattery{}
    , mTimeScale(1.f)    
{
}

ShiftController::~ShiftController()
{
}

void ShiftController::initialize()
{
    mLight = GetOwner()->GetGameSystem()->FindGameObject(L"GlobalLight2D")->GetComponent<Light2D>();
    mPlayer = GetOwner()->GetGameSystem()->FindGameObject(L"Player");

    for (int i = 0; i < 11; ++i)
    {
        mBattery[i] = GetOwner()->GetGameSystem()->FindGameObject(L"UIBatteryPart" + std::to_wstring(i));
    }
}

void ShiftController::update()
{     
    if (nullptr == mPlayer)
    {
        assert(false);
        return;
    }

    //Player Material
    Material* const material = mPlayer->GetComponent<Animator2D>()->GetMaterial();

    if (gInput->GetKeyDown(eKeyCode::LSHIFT))
    {
        gSoundManager->Play(eResAudioClip::slomoEngage, 1.f);
        mLight->SetLightDiffuse(Vector3::One * 0.1f);
        GetOwner()->GetGameSystem()->GetScene()->SetBackgroundColor(Vector4(0.5294f * 0.1f, 0.5254f * 0.1f, 0.7843f * 0.1f, 1.f));
        gSoundManager->SetPitch(eResAudioClip::song_chinatown, 0.5f); 
        mPlayer->GetComponent<AfterImage>()->TurnOffVisiblelity();


        for (int i = 0; i < 11; ++i)
        {
            SpriteRenderer* const spriteRenderer = mBattery[i]->GetComponent<SpriteRenderer>();            
            spriteRenderer->SetColorR(1.f);
            spriteRenderer->MulColorG(0.5f);
            spriteRenderer->MulColorB(0.5f);
        }

        TimeManager::GetInstance()->SetTileScale(0.25f);

        tCBColorInfo colorInfo = {};
        colorInfo.bUseColor = 1;
        mPlayer->GetComponent<Animator2D>()->SetColorInfo(colorInfo);

    }
    else if (gInput->GetKeyUp(eKeyCode::LSHIFT))
    {
        gSoundManager->Stop(eResAudioClip::slomoEngage);
        gSoundManager->Play(eResAudioClip::slomoDisengage, 1.f);
        mLight->SetLightDiffuse(Vector3::One);
        GetOwner()->GetGameSystem()->GetScene()->SetBackgroundColor(Vector4(0.5294f, 0.5254f, 0.7843f, 1.f));
        gSoundManager->SetPitch(eResAudioClip::song_chinatown, 1.f);
        mPlayer->GetComponent<AfterImage>()->TurnOnVisiblelity();


        for (int i = 0; i < 11; ++i)
        {
            SpriteRenderer* const spriteRenderer = mBattery[i]->GetComponent<SpriteRenderer>();
            spriteRenderer->SetColorReset();            
            spriteRenderer->MulColorReset();
        }

        TimeManager::GetInstance()->SetTileScale(1.f);

        tCBColorInfo colorInfo = {};
        colorInfo.bUseColor = 0;
        mPlayer->GetComponent<Animator2D>()->SetColorInfo(colorInfo);
    }
    
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

    //TimeManager::GetInstance()->SetTileScale(mTimeScale);
    //mLight->SetLightDiffuse(Vector3::One * mTimeScale);
}

void ShiftController::lateUpdate()
{
}

