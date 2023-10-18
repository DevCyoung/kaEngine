#include "pch.h"
#include "RewindManager.h"
#include "Components.h"
#include <Engine/TimeManager.h>
#include "GameManager.h"

#include <Engine/ConstantBuffer.h>
#include <Engine/Engine.h>
#include <Engine/GraphicDeviceDx11.h>

#include <Engine/SceneManager.h>
#include "Chinatown01Scene.h"
#include "KatanaZeroSystem.h"

#include <Engine/String.h>
#include <Engine/Scene.h>
#include "DieController.h"

int cctvSpeeds[9] = { -8, -4, -2, -1, 1, 2, 4, 8, 0};

RewindManager::RewindManager()
	: mState(eRewindState::None)
	, mCurTime(0.f)
	, mFrameTime(0.f)
	, mMAXFrameIdx(0)
	, mCurFrameIdx(0)
	, mTVThumTime(0.f)
	, mTimeScale(1.f)
	, mRewindFrameDatasArray{}
	, mTimerUI(nullptr)
	, mRewindEvent(eRewindEvent::None)
	, mCCTVSpeedIdx(4)
{
	for (auto& data : mRewindFrameDatasArray)
	{
		data.clear();
		data.reserve(100);
	}
}

RewindManager::~RewindManager()
{
}

void RewindManager::Initialize(Scene* Scene)
{
	mTimerUI = Scene->GetGameSystem()->FindGameObjectOrNull(L"UITimer");
}

//PlayerDeath

void RewindManager::LateUpdate()
{
	if (nullptr == mTimerUI)
	{
		return;
	}

	//GameManager::GetInstance()->GetEventManager()->

	switch (mState)
	{
	case eRewindState::None:
		break;
	case eRewindState::Record:
	{
		mCurTime += gDeltaTime;
		float uvX = 1.f - (mCurTime / static_cast<float>(MAX_REWIND_SECOND));
		mTimerUI->GetComponent<SpriteRenderer>()->SetUvOffsetX(uvX);
	}
	record();
	break;
	case eRewindState::PlayBack:
		playBack();
		break;
	case eRewindState::CCTV:
		play();
		break;
	case eRewindState::Pause:
		pause();
		break;
	case eRewindState::Rewind:
		rewind();
		break;
	case eRewindState::BlackOut:
		blackOut();
		break;
	default:
		break;
	}

	if (gInput->GetKeyDown(eKeyCode::NUM5))
	{
		mTimeScale -= 0.2f;
	}

	if (gInput->GetKeyDown(eKeyCode::NUM6))
	{
		mTimeScale += 0.2f;
	}

	if (mTimeScale <= 0.2f)
	{
		mTimeScale = 0.2f;
	}
	else if (mTimeScale >= 8.f)
	{
		mTimeScale = 8.f;
	}

	//button
	if (gInput->GetKeyDown(eKeyCode::R))
	{
		Rewind();
	}

	if (gInput->GetKeyDown(eKeyCode::T))
	{			

		//CCTVPlay();
		GameObject* dieControler = SceneManager::GetInstance()->GetCurrentScene()->GetGameSystem()->FindGameObjectOrNull(L"DieController");
		dieControler->GetComponent<DieController>()->TurnOffDieText();
		recordSave();
		mState = eRewindState::BlackOut;
	}

	if (gInput->GetKeyDown(eKeyCode::LEFT))
	{
		--mCCTVSpeedIdx;
		mState = eRewindState::CCTV;
	}
	else if (gInput->GetKeyDown(eKeyCode::RIGHT))
	{
		++mCCTVSpeedIdx;
		mState = eRewindState::CCTV;
	}

	if (mCCTVSpeedIdx <= 0)
	{
		mCCTVSpeedIdx = 0;
	}
	else if (mCCTVSpeedIdx >= 7)
	{
		mCCTVSpeedIdx = 7;
	}

	if (mState == eRewindState::CCTV ||
		mState == eRewindState::Pause)
	{		
		if (gInput->GetKeyDown(eKeyCode::LBTN))
		{
			gKatanaZeroSystem->LoadNextScene();
		}		
	}
}

void RewindManager::Rewind()
{
	if (mState == eRewindState::Rewind)
	{
		return;
	}

	if (mCurFrameIdx <= 60)
	{
		return;
	}
	recordSave();

	mRewindEvent = eRewindEvent::RewindStart;
	SetRewindState(eRewindState::Rewind);

	gSoundManager->TurnOffSound();

	gSoundManager->PlayInForce(eResAudioClip::rewind, 1.f);
	tWaveInfo waveInfo = {};
	waveInfo.WaveXPower = 200.f;
	waveInfo.WaveYPower = 0.f;
	waveInfo.WaveSpeed = 50.f;

	gGraphicDevice->PassCB(eCBType::Wave, sizeof(waveInfo), &waveInfo);
	gGraphicDevice->BindCB(eCBType::Wave, eShaderBindType::PS);


	GameObject* dieControler = SceneManager::GetInstance()->GetCurrentScene()->GetGameSystem()->FindGameObjectOrNull(L"DieController");
	dieControler->GetComponent<DieController>()->TurnOffDieText();
}

int RewindManager::GetCCTVSpeed() const
{
	return cctvSpeeds[mCCTVSpeedIdx];
}

void RewindManager::record()
{
	mFrameTime += gDeltaTime;

	if (mCurFrameIdx >= MAX_REWIND_FRAME - 1)
	{
		recordSave();
		return;
	}

	if (mFrameTime >= REWIND_FRAME_TIME)
	{
		for (GameObject* obj : mRewindObjects)
		{
			RewindObjectData data = {};

			data.Obj = obj;
			data.WorldMatrix = obj->GetComponent<Transform>()->GetWorldMatrix();	

			Animator2D* const animator =  obj->GetComponentOrNull<Animator2D>();

			if (animator)
			{
				data.bVisible = animator->IsVisible();

				Animation2D* const anim = animator->GetCurAnimationOrNull();				

				if (anim)
				{
					data.AnimKey = anim->GetKey();
					data.FrameIdx = anim->GetFrameIdx();					
				}				
			}

			mRewindFrameDatasArray[mCurFrameIdx].push_back(data);
		}

		mFrameTime = 0.f;		
		++mCurFrameIdx;
	}
}

void RewindManager::recordSave()
{
	mMAXFrameIdx = mCurFrameIdx;
	mState = eRewindState::RecordSave;

}

void RewindManager::play()
{
	mFrameTime += gDeltaTime;

	if (mFrameTime >= REWIND_FRAME_TIME)
	{
		mFrameTime = 0.f;
		mCurFrameIdx += cctvSpeeds[mCCTVSpeedIdx];
	}

	if (mCurFrameIdx < 0)
	{
		mCurFrameIdx = 0;		
	}
	else if (mCurFrameIdx > mMAXFrameIdx)
	{
		mCurFrameIdx = mMAXFrameIdx;
	}

	if (cctvSpeeds[mCCTVSpeedIdx] < 0 && mCurFrameIdx <= 0)
	{
		mCCTVSpeedIdx = 3;
		mState = eRewindState::Pause;
	}
	else if (cctvSpeeds[mCCTVSpeedIdx] > 0 && mCurFrameIdx >= mMAXFrameIdx)
	{
		mCCTVSpeedIdx = 4;
		mState = eRewindState::Pause;
	}

	DrawFrame(mCurFrameIdx);

	wchar_t text[256] = {};
	int cctvSpeed = cctvSpeeds[mCCTVSpeedIdx];

	if (cctvSpeed < -1)
	{
		swprintf_s(text, 256, L"REWIND X %d", abs(cctvSpeeds[mCCTVSpeedIdx]));
	}
	else if (cctvSpeed == -1)
	{
		swprintf_s(text, 256, L"REWIND");		
	}
	else if (cctvSpeed == 1)
	{
		swprintf_s(text, 256, L"PLAY");	
	}	
	else
	{
		swprintf_s(text, 256, L"PLAY X %d", cctvSpeeds[mCCTVSpeedIdx]);
	}

	gKatanaZeroSystem->SetCRTText(text);


	if (cctvSpeeds[mCCTVSpeedIdx]  > 0)
	{
		gKatanaZeroSystem->PlayCRT();
	}
	else if (cctvSpeeds[mCCTVSpeedIdx] < 0)
	{
		gKatanaZeroSystem->RewindCRT();
	}
	else
	{


	}

	float playTime = (mCurFrameIdx * REWIND_FRAME_TIME);

	int min = static_cast<int>(playTime) / 60;
	int sec = static_cast<int>(playTime) % 60;
	int other = static_cast<int>((playTime - static_cast<int>(playTime)) * 100);

	if (other <= 1)
	{
		other = 0;
	}

	wchar_t text2[256] = {};
	swprintf_s(text2, 256, L"TIME - %02d:%02d:%02d", min, sec, other);
	gKatanaZeroSystem->SetCRTTextTime(text2);

	float timeline = static_cast<float>(mCurFrameIdx) / static_cast<float>(mMAXFrameIdx);
	gKatanaZeroSystem->SetCRTTimeLine(timeline);
}

void RewindManager::playBack()
{
	mFrameTime += gDeltaTime;

	if (mFrameTime >= REWIND_FRAME_TIME)
	{
		mFrameTime = 0.f;
		--mCurFrameIdx;
	}	

	if (mCurFrameIdx <= 1)
	{
		mCurFrameIdx = 1;
	}
	else if (mCurFrameIdx >= mMAXFrameIdx - 1)
	{
		mCurFrameIdx = mCurFrameIdx - 1;
	}

	DrawFrame(mCurFrameIdx);
}

void RewindManager::pause()
{
	if (mCurFrameIdx <= 0)
	{
		mCurFrameIdx = 0;
	}
	else if (mCurFrameIdx >= mMAXFrameIdx)
	{
		mCurFrameIdx = mMAXFrameIdx;
	}

	DrawFrame(mCurFrameIdx);

	wchar_t text[256] = {};	
	swprintf_s(text, 256, L"PAUSE");

	gKatanaZeroSystem->SetCRTText(text);

	float timeline = static_cast<float>(mCurFrameIdx) / static_cast<float>(mMAXFrameIdx);
	gKatanaZeroSystem->SetCRTTimeLine(timeline);
	gKatanaZeroSystem->PauseCRT();
}

void RewindManager::rewind()
{
	mFrameTime += gRealDeltaTime;

	//1분짜리가있을때 5초안에 리와인드 되야한다면?	
	//300프레임만 사용가능함
	if (mFrameTime >= REWIND_FRAME_TIME)
	{	
		mFrameTime = 0.f;		

		if (mMAXFrameIdx <= REWIND_TIME * 60 + 1)
		{
			--mCurFrameIdx;
		}
		else
		{
			mRewindFrame += mMAXFrameIdx / (REWIND_TIME * 60);
			mCurFrameIdx = mMAXFrameIdx - static_cast<int>(mRewindFrame);
		}				
	}

	if (mRewindEvent == eRewindEvent::RewindStart)
	{
		if (mCurFrameIdx <= 50)
		{
			mRewindEvent = eRewindEvent::RewindTVThumb;

			tWaveInfo waveInfo = {};

			waveInfo.WaveXPower = 450.f;
			waveInfo.WaveYPower = 10.f;
			waveInfo.WaveSpeed = 1.f;

			gGraphicDevice->PassCB(eCBType::Wave, sizeof(waveInfo), &waveInfo);
			gGraphicDevice->BindCB(eCBType::Wave, eShaderBindType::PS);
		}
	}
	else if (mRewindEvent == eRewindEvent::RewindTVThumb)
	{
		mTVThumTime += gRealDeltaTime;

		if (mTVThumTime > 0.28f)
		{
			mRewindEvent = eRewindEvent::RewindEnd;
			gSoundManager->PlayInForce(eResAudioClip::tvThump, 1.f);
			gSoundManager->TurnOnSound();


			tWaveInfo waveInfo = {};

			waveInfo.WaveXPower = 0.f;
			waveInfo.WaveYPower = 0.f;
			waveInfo.WaveSpeed = 0.f;

			gGraphicDevice->PassCB(eCBType::Wave, sizeof(waveInfo), &waveInfo);
			gGraphicDevice->BindCB(eCBType::Wave, eShaderBindType::PS);

			SceneManager::GetInstance()->RegisterLoadScene(SceneManager::GetInstance()->GetCurrentScene()->Clone());
		}
	}

	if (mCurFrameIdx <= 1)
	{
		mCurFrameIdx = 1;
	}
	
	DrawFrame(mCurFrameIdx);
}

void RewindManager::blackOut()
{
	GameObject* blackOut = gKatanaZeroSystem->GetBlackOut();
	GameObject* readyText = gKatanaZeroSystem->GetReadyText();

	float a = blackOut->GetComponent<SpriteRenderer>()->GetSprite2DInfo().A;
	a += gRealDeltaTime * 2.f	;

	readyText->GetComponent<EngineText>()->TurnOnVisiblelity();
	blackOut->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();

	if (a >= 5.f)
	{				
		readyText->GetComponent<EngineText>()->TurnOffVisiblelity();
		blackOut->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();
		CCTVPlay();
	}	

	float na = a;
	if (na >= 1.f)
	{
		na = 1.f;
	}
	
	
	readyText->GetComponent<EngineText>()->SetColor(XMUINT4(255, 255, 255, static_cast<int>(na * 255)));
	blackOut->GetComponent<SpriteRenderer>()->SetColorA(a);
}

void RewindManager::DrawFrame(int frameIdx)
{

	if (frameIdx <= 0)
	{
		frameIdx = 0;
	}
	else if (frameIdx >= mMAXFrameIdx)
	{
		frameIdx = mMAXFrameIdx;
	}
		

	const std::vector<RewindObjectData>& datas = mRewindFrameDatasArray[frameIdx];
	std::vector<RewindObjectData>::const_iterator riter = datas.begin();

	for (; riter != datas.end(); ++riter)
	{
		GameObject* const obj = riter->Obj;

		obj->GetComponent<Transform>()->SetWorldMatrix(riter->WorldMatrix);

		Animator2D* const anim = obj->GetComponentOrNull<Animator2D>();

		if (anim && riter->AnimKey != L"")
		{
			anim->PlayFrame(riter->AnimKey, riter->FrameIdx, false);

			if (riter->bVisible)
			{
				obj->GetComponent<Animator2D>()->TurnOnVisiblelity();
			}
			else
			{
				obj->GetComponent<Animator2D>()->TurnOffVisiblelity();
			}

		}

		if (obj->GetComponentOrNull<Camera>())
		{
			obj->GetComponent<Camera>()->CalculateCamera();
		}

	}
}

void RewindManager::CCTVPlay()
{
	if (mCurFrameIdx <= 60)
	{
		return;
	}

	recordSave();
	gKatanaZeroSystem->TurnOnCRT();
	gSoundManager->TurnOffSound();
	mState = eRewindState::CCTV;
	mCurFrameIdx = 1;	


	Camera* uiCamera =  gKatanaZeroSystem->GetCurrentScene()->
		GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::UI);

	uiCamera->TurnOffAllLayer();
}
