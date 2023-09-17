#include "pch.h"
#include "RewindManager.h"
#include "Components.h"
#include <Engine/TimeManager.h>

RewindManager::RewindManager()
	: mState(eRewindState::None)
	, mCurTime(0.f)
	, mCurFrameIdx(0)
	, mTimeScale(1.f)
	, mRewindFrameDatasArray{}
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

void RewindManager::LateUpdate()
{
	if (mCurFrameIdx >= MAX_REWIND_FRAME - 1 || mCurFrameIdx < 0)
	{
		return;
	}

	switch (mState)
	{
	case eRewindState::None:
		break;
	case eRewindState::Record:
		Record();
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


	if (gInput->GetKeyDown(eKeyCode::NUM7))
	{
		SetRewindState(eRewindState::Rewind);
	}

	if (gInput->GetKeyDown(eKeyCode::NUM8))
	{
		SetRewindState(eRewindState::Play);
	}

	if (gInput->GetKeyDown(eKeyCode::NUM9))
	{
		SetRewindState(eRewindState::Pause);
	}
}

void RewindManager::Record()
{
	mCurTime += gDeltaTime;
	if (mCurTime >= REWIND_FRAME_TIME)
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

		mCurTime = 0.f;
		++mCurFrameIdx;
	}


	if (gInput->GetKeyDown(eKeyCode::SPACE))
	{
		
	}
}

void RewindManager::Play()
{
	mCurTime += gDeltaTime;

	if (mCurTime >= REWIND_FRAME_TIME * mTimeScale && mCurFrameIdx < MAX_REWIND_FRAME - 1)
	{
		mCurTime = 0.f;
		++mCurFrameIdx;
	}

	const std::vector<RewindObjectData>& datas = mRewindFrameDatasArray[mCurFrameIdx];
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

void RewindManager::Pause()
{
	const std::vector<RewindObjectData>& datas = mRewindFrameDatasArray[mCurFrameIdx];
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

void RewindManager::Rewind()
{
	mCurTime += gDeltaTime;

	if (mCurTime >= REWIND_FRAME_TIME  * mTimeScale && mCurFrameIdx >= 1)
	{
		mCurTime = 0.f;
		--mCurFrameIdx;
	}

	const std::vector<RewindObjectData>& datas = mRewindFrameDatasArray[mCurFrameIdx];
	std::vector<RewindObjectData>::const_reverse_iterator riter = datas.rbegin();

	for (; riter != datas.rend(); ++riter)
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
