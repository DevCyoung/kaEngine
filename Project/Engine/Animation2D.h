#pragma once

class Texture;

class Animation2D
{
	friend class Animator2D;

public:
	struct Event
	{
		void operator=(std::function<void()> func)
		{
			mEvent = std::move(func);
		}
		void operator()()
		{
			if (mEvent)
				mEvent();
		}

		std::function<void()> mEvent;
	};

	struct Events
	{
		Event startEvent;		
		Event endEvent;
	};

	struct tFrame
	{
		Vector2 UVLeftTop;
		Vector2 UVSize;
		Vector2	UVOffset;
		XMINT2	center;
		float duration;
		Event endEvent;
		bool bEvent;
	};


public:
	Animation2D(const std::wstring& animName,
		Texture* const atlas,
		const UINT frameCount,
		const XMUINT2 startLeft,
		const XMUINT2 frameSize,		
		const XMUINT2 framePad,
		const XMINT2 frameoffset,
		const float duration);

	virtual ~Animation2D();
	Animation2D(const Animation2D&) = delete;
	Animation2D& operator=(const Animation2D&) = delete;

	const tFrame& GetCurFrame() const { return mFrames[mCurFrameIdx]; }
	Texture* GetAtlas() const { Assert(mAtlas, WCHAR_IS_NULLPTR); return mAtlas; }

	void SetFrameEndEvent(UINT frameIDX, std::function<void()> func)
	{
		Assert(frameIDX < mFrames.size(), WCHAR_IS_INVALID_TYPE);

		mFrames[frameIDX].endEvent = std::move(func);
		mFrames[frameIDX].bEvent = true;
	}

	void SetFirstFrameEndEvent(std::function<void()> func)
	{
		Assert(!mFrames.empty(), WCHAR_IS_INVALID_TYPE);

		SetFrameEndEvent(0, std::move(func));
	}

	void SetLastFrameEndEvent(std::function<void()> func)
	{
		Assert(!mFrames.empty(), WCHAR_IS_INVALID_TYPE);

		SetFrameEndEvent(static_cast<int>(mFrames.size()) - 1, std::move(func));
	}

private:
	void lateUpdate();
	void reset();

private:
	std::wstring mKey;
	Texture* mAtlas;
	bool mbFinished;
	float mCurFramePlayTime;
	int mCurFrameIdx;

	std::vector<tFrame> mFrames;	
};

