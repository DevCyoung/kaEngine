#include "pch.h"
#include "Animation2D.h"
#include "Textrue.h"
#include "TimeManager.h"

Animation2D::Animation2D(const std::wstring& animName,
	Texture* const atlas,
	const UINT frameCount,
	const XMUINT2 startLeft,
	const XMUINT2 frameSize,	
	const XMUINT2 framePad,
	const XMINT2 frameoffset,
	const float duration)
	: mKey(animName)
	, mAtlas(atlas)
	, mbFinished(false)
	, mCurFramePlayTime(0.f)
	, mCurFrameIdx(0)
	, mFrames()
{
	mFrames.reserve(20);

	XMUINT2 cursorPos = startLeft;
	const UINT FRAME_COUNT = frameCount;
	const UINT MAX_FRAME_COUNT_X = static_cast<UINT>(mAtlas->GetWidth()) / (framePad.x + frameSize.x);



	Vector2 atlasUVPerPixel = {};
	atlasUVPerPixel.x = 1.f / (mAtlas->GetWidth());
	atlasUVPerPixel.y = 1.f / (mAtlas->GetHeight());	

	tFrame frame = {};

	frame.UVSize.x = static_cast<float>(frameSize.x) * atlasUVPerPixel.x;
	frame.UVSize.y = static_cast<float>(frameSize.y) * atlasUVPerPixel.y;

	frame.UVOffset.x = static_cast<float>(frameoffset.x) * atlasUVPerPixel.x;
	frame.UVOffset.y = static_cast<float>(frameoffset.y) * atlasUVPerPixel.y;

	frame.duration = duration;

	for (UINT i = 0; i < FRAME_COUNT; ++i)
	{
		frame.UVLeftTop.x = static_cast<float>(cursorPos.x) * atlasUVPerPixel.x;
		frame.UVLeftTop.y = static_cast<float>(cursorPos.y) * atlasUVPerPixel.y;

		frame.center.x = cursorPos.x + (frameSize.x / 2);
		frame.center.y = cursorPos.y + (frameSize.y / 2);

		mFrames.push_back(frame);

		cursorPos.x += frameSize.x + framePad.x;

		if ((i + 1) % MAX_FRAME_COUNT_X == 0)
		{
			cursorPos.x  = startLeft.x;
			cursorPos.y += frameSize.y + framePad.y;
		}
	}
}

Animation2D::~Animation2D()
{
}

void Animation2D::lateUpdate()
{
	if (mbFinished)
	{
		return;
	}

	//Animation Event;	

	mCurFramePlayTime += gDeltaTime;

	if (mFrames[mCurFrameIdx].duration < mCurFramePlayTime)
	{
		mCurFramePlayTime -= mFrames[mCurFrameIdx].duration;
		++mCurFrameIdx;

		if (mFrames.size() <= mCurFrameIdx)
		{
			mbFinished = true;
			mCurFrameIdx = static_cast<int>(mFrames.size()) - 1;
		}

		if (mFrames[mCurFrameIdx].bEvent)
		{
			mFrames[mCurFrameIdx].endEvent();
		}
	}
}

void Animation2D::reset()
{
	mCurFrameIdx = 0;
	mCurFramePlayTime = 0.f;
	mbFinished = false;
}

void Animation2D::reset(const UINT frameIdx)
{
	Assert(mFrames.size() > mCurFrameIdx, WCHAR_IS_INVALID_TYPE);

	mCurFrameIdx = frameIdx;
	mCurFramePlayTime = 0.f;
	mbFinished = false;
}
