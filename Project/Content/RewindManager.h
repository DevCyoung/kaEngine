#pragma once

//1Ка 3600
#define MAX_REWIND_FRAME 3600 * 2
#define REWIND_FRAME_TIME 0.0166666f / 2.f

class GameObject;

struct RewindObjectData
{
	GameObject* Obj;

	bool bVisible;

	//pos, rot, scale
	Matrix WorldMatrix;

	//animkey, idx
	std::wstring AnimKey;
	UINT FrameIdx;
};

enum class eRewindState
{
	None,
	Record,
	Play,	
	Pause,
	Rewind,
};

class RewindManager
{
public:
	RewindManager();
	virtual ~RewindManager();
	RewindManager(const RewindManager&) = delete;
	RewindManager& operator=(const RewindManager&) = delete;

	void LateUpdate();
	//void AddFrameData(const RewindObjectData& data);

	void Record();
	void Play();
	void Pause();
	void Rewind();

	void RegisterRewindObject(GameObject* const obj) { Assert(obj, WCHAR_IS_NULLPTR), mRewindObjects.push_back(obj); };

	void SetRewindState(const eRewindState state) { mState = state; }
	eRewindState GetRewindState() const { return mState; }


private:
	eRewindState mState;
	float mCurTime;
	float mTimeScale;
	UINT mCurFrameIdx;
	//1Ка 3600
	std::vector<GameObject*> mRewindObjects;
	std::vector<RewindObjectData> mRewindFrameDatasArray[MAX_REWIND_FRAME];
};

