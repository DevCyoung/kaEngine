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

	mCurTime += gDeltaTime;
	float uvX = 1.f - (mCurTime / static_cast<float>(MAX_REWIND_SECOND));	
	mTimerUI->GetComponent<SpriteRenderer>()->SetUvOffsetX(uvX);

	//GameManager::GetInstance()->GetEventManager()->

	switch (mState)
	{
	case eRewindState::None:
		break;
	case eRewindState::Record:
		Record();
		break;
	case eRewindState::PlayBack:
		BackPlay();
		break;
	case eRewindState::Play:
		Play();
		break;
	case eRewindState::Pause:
		Pause();
		break;
	case eRewindState::Rewind:
		Rewind();
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
		if (mCurFrameIdx <= 60)
		{
			return;
		}		
		RecordSave();

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

	}

	if (gInput->GetKeyDown(eKeyCode::T))
	{
		if (mCurFrameIdx <= 60)
		{
			return;
		}

		RecordSave();
		mState = eRewindState::Pause;		
	}

	if (gInput->GetKeyDown(eKeyCode::NUM8))
	{
		SetRewindState(eRewindState::PlayBack);
	}

	if (gInput->GetKeyDown(eKeyCode::NUM9))
	{
		SetRewindState(eRewindState::Play);
	}
}

void RewindManager::Record()
{
	mFrameTime += gDeltaTime;

	if (mCurFrameIdx >= MAX_REWIND_FRAME - 1)
	{
		RecordSave();
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

void RewindManager::RecordSave()
{
	mMAXFrameIdx = mCurFrameIdx;
	mState = eRewindState::RecordSave;

}

void RewindManager::Play()
{
	mFrameTime += gDeltaTime;

	if (mFrameTime >= REWIND_FRAME_TIME)
	{
		mFrameTime = 0.f;
		++mCurFrameIdx;
	}

	DrawFrame(mCurFrameIdx);
}

void RewindManager::BackPlay()
{
	mFrameTime += gDeltaTime;

	if (mFrameTime >= REWIND_FRAME_TIME)
	{
		mFrameTime = 0.f;
		--mCurFrameIdx;
	}

	DrawFrame(mCurFrameIdx);
}

void RewindManager::Pause()
{
	DrawFrame(mCurFrameIdx - 1);	
}

void RewindManager::Rewind()
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

void RewindManager::DrawFrame(int frameIdx)
{

	if (frameIdx <= 1)
	{
		frameIdx = 1;
	}
	else if (frameIdx >= mMAXFrameIdx - 1)
	{
		frameIdx = mMAXFrameIdx - 1;
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
