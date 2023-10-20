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
    , mPrevBackgorundColor(Vector4::One)
    , mSlomoGage(121.f)
    , mSlomoState(eSlomoState::None)
{
    gSoundManager->SetSoundPitch(1.0f);
}

ShiftController::~ShiftController()
{
}

void ShiftController::EnterSlomo()
{
    Scene* const scene = GetOwner()->GetGameSystem()->GetScene();

    mPrevBackgorundColor = scene->GetBackgroundColor();

    Vector4 backgroundColor = mPrevBackgorundColor;
    float colorScale = 0.3f;
    backgroundColor.x *= colorScale;
    backgroundColor.y *= colorScale;
    backgroundColor.z *= colorScale;

    mLight->SetLightDiffuse(Vector3::One * colorScale);

    GetOwner()->GetGameSystem()->GetScene()->SetBackgroundColor(backgroundColor);



    gSoundManager->SetSoundPitch(0.5f);
    gSoundManager->SetPitch(eResAudioClip::slomoEngage, 1.0f);
    gSoundManager->Play(eResAudioClip::slomoEngage, 1.f);
    mPlayer->GetComponent<AfterImage>()->TurnOffVisiblelity();




    /*  for (GameObject* light : mLights)
      {
          light->GetComponent<Light2D>()->TurnOffLight();
      }*/
    GameManager::GetInstance()->GetEventManager()->SetSlomo(true);
    TimeManager::GetInstance()->SetTileScale(0.25f);
    

    tCBColorInfo colorInfo = {};
    colorInfo.bUseColor = 1;
    mPlayer->GetComponent<Animator2D>()->SetColorInfo(colorInfo);
}

void ShiftController::ExitSlomo()
{
    gSoundManager->Stop(eResAudioClip::slomoEngage);
    gSoundManager->SetSoundPitch(1.f);
    gSoundManager->Play(eResAudioClip::slomoDisengage, 1.f);



    mLight->SetLightDiffuse(Vector3::One);
    GetOwner()->GetGameSystem()->GetScene()->SetBackgroundColor(mPrevBackgorundColor);

    //gSoundManager->SetPitch(eResAudioClip::song_chinatown, 1.f);



    mPlayer->GetComponent<AfterImage>()->TurnOnVisiblelity();




    /*for (GameObject* light : mLights)
    {
        light->GetComponent<Light2D>()->TurnOnLight();
    }*/
    GameManager::GetInstance()->GetEventManager()->SetSlomo(false);
    TimeManager::GetInstance()->SetTileScale(1.f);

    tCBColorInfo colorInfo = {};
    colorInfo.bUseColor = 0;
    mPlayer->GetComponent<Animator2D>()->SetColorInfo(colorInfo);
}

void ShiftController::initialize()
{
    mLight = GetOwner()->GetGameSystem()->FindGameObject(L"GlobalLight2D")->GetComponent<Light2D>();
    //mLights =  GetOwner()->GetGameSystem()->FindGameObjects(L"DefuseLight");
    mPlayer = GetOwner()->GetGameSystem()->FindGameObject(L"Player");

    for (int i = 0; i < BATTERY_COUNT; ++i)
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

    if (gInput->GetKeyDown(eKeyCode::LSHIFT) && mSlomoGage >= 15.f)
    {                    
        EnterSlomo();
        mSlomoState = eSlomoState::Slomo;
    }
    else if (gInput->GetKeyUp(eKeyCode::LSHIFT) && mSlomoState == eSlomoState::Slomo)
    {
        mSlomoState = eSlomoState::None;
        ExitSlomo();
    }    
    else if (gInput->GetKey(eKeyCode::LSHIFT) && mSlomoState == eSlomoState::Slomo)
    {    
        float dstTimeScale = 0.15f;
        GetOwner()->GetComponent<SpriteRenderer>()->SetMaterial(gResourceManager->FindOrNull<Material>(L"UIShift01"));

        mTimeScale -= gDeltaTime * 4.f;

        material->SetShader(gResourceManager->Find<Shader>(L"Animation2D"));

        if (mTimeScale <= dstTimeScale)
        {
            mTimeScale = dstTimeScale;
        }        


        mSlomoGage -= gRealDeltaTime * 15.f;

        if (mSlomoGage <= 0.f)
        {
            mSlomoState = eSlomoState::None;
            ExitSlomo();
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


        mSlomoGage += gRealDeltaTime * 10.f;

        if (mSlomoGage >= 121.f)
        {
            mSlomoGage= 121.f;
        }
        
    }

    int idx = static_cast<int>(mSlomoGage / BATTERY_COUNT);

    if (idx <= 0.f)
    {
        idx = 0;
    }

    for (int i = 0; i < idx; ++i)
    {
        SpriteRenderer* const spriteRenderer = mBattery[i]->GetComponent<SpriteRenderer>();
        spriteRenderer->SetColorReset();
        spriteRenderer->MulColorReset();
    }

    for (int i = idx; i < BATTERY_COUNT; ++i)
    {        
        SpriteRenderer* const spriteRenderer = mBattery[i]->GetComponent<SpriteRenderer>();

        spriteRenderer->SetColorR(1.f);
        spriteRenderer->MulColorG(0.5f);
        spriteRenderer->MulColorB(0.5f);
    }    

    //TimeManager::GetInstance()->SetTileScale(mTimeScale);
    //mLight->SetLightDiffuse(Vector3::One * mTimeScale);
}

void ShiftController::lateUpdate()
{
}

