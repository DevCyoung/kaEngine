#include "pch.h"
#include "TitleController.h"
#include "Components.h"
#include "GameManager.h"

TitleController::TitleController()
    : ScriptComponent(eScriptComponentType::TitleController)
    , mSpeed(100.f)
    , mTitleState(eTitleState::Start)
    , mCursorState(eCursorState::Start)
{
}

TitleController::~TitleController()
{
}

void TitleController::initialize()
{
}

void TitleController::update()
{
    cursorMove();
    cursorSelect();
}

void TitleController::lateUpdate()
{
}


void TitleController::cursorMove()
{
    Transform* transform = GetOwner()->GetComponent<Transform>();

    if (gInput->GetKeyDown(eKeyCode::DOWN))
    {
        mCursorState = eCursorState::Exit;
        transform->SetPosition(0.f, 62.f, 0.f);
        gSoundManager->Play(eResAudioClip::Title_Skip, 0.1f);
    }

    if (gInput->GetKeyDown(eKeyCode::UP))
    {
        mCursorState = eCursorState::Start;
        transform->SetPosition(0.f, 112.f, 0.f);
        gSoundManager->Play(eResAudioClip::Title_Skip, 0.1f);
    }

    if (mTitleState == eTitleState::NextScene)
    {
        Camera* mainCamera = GetOwner()->GetGameSystem()->
            GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);

        Transform* cameraTransform = mainCamera->GetOwner()->GetComponent<Transform>();
        Vector3 position = cameraTransform->GetPosition();
        mSpeed +=  600.f * gDeltaTime;
        position.y -= gDeltaTime * mSpeed;
        cameraTransform->SetPosition(position);
	}
}

void TitleController::cursorSelect()
{
    if (gInput->GetKeyDown(eKeyCode::SPACE))
    {
        switch (mCursorState)
        {
        case eCursorState::Start:
            mTitleState = eTitleState::NextScene;
            gSoundManager->Play(eResAudioClip::Title_promptGo, 0.5f);
            gSoundManager->Play(eResAudioClip::Title_goScene, 0.5f);
            gSoundManager->SetVolume(eResAudioClip::song_rainonbrick, 0.0f);
            break;
        case eCursorState::Exit:
            PostQuitMessage(0);
            break;
        default:
            break;
        }
    }
}
