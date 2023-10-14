#include "pch.h"
#include "MonsterFSM.h"

MonsterFSM::MonsterFSM(GameObject* owner)
	: mMonsterStates{}
	, mRegisterEnterState(nullptr)
	, mCurrentState(nullptr)
	, mOwner(owner)
{
}

MonsterFSM::~MonsterFSM()
{
	for (MonsterState* state : mMonsterStates)
	{
		DELETE_POINTER(state);
	}
}

void MonsterFSM::Initialize(int idx)
{
	Assert(idx < MAX_MONSTER_STATES, WCHAR_IS_INVALID_TYPE);
	Assert(mMonsterStates[idx], WCHAR_IS_NULLPTR);

	for (MonsterState* state : mMonsterStates)
	{
		if (state)
		{
			state->Initialize();
		}
	}

	mCurrentState = mMonsterStates[idx];
	mCurrentState->Enter();
}

void MonsterFSM::GlobalUpdate()
{
	if (mRegisterEnterState)
	{
		mCurrentState->Exit();
		mCurrentState = mRegisterEnterState;
		mCurrentState->Enter();
		mRegisterEnterState = nullptr;
	}
}

void MonsterFSM::Update()
{
	Assert(mCurrentState, WCHAR_IS_NULLPTR);

	mCurrentState->Update();
}

void MonsterFSM::AddState(int idx, MonsterState* state)
{
	Assert(state, WCHAR_IS_NULLPTR);
	Assert(idx < MAX_MONSTER_STATES, WCHAR_IS_INVALID_TYPE);
	Assert(!mMonsterStates[idx], WCHAR_IS_NOT_NULLPTR);

	state->mMonsterFSM = this;
	state->mGameObject = mOwner;

	mMonsterStates[idx] = state;
}

void MonsterFSM::ChangeState(int idx)
{
	Assert(mCurrentState, WCHAR_IS_NULLPTR);
	Assert(idx < MAX_MONSTER_STATES, WCHAR_IS_INVALID_TYPE);
	Assert(mMonsterStates[idx], WCHAR_IS_NULLPTR);
	Assert(!mRegisterEnterState, WCHAR_IS_NOT_NULLPTR);

	mRegisterEnterState = mMonsterStates[idx];

	/*mCurrentState->Exit();
	mCurrentState = mMonsterStates[idx];
	mCurrentState->Enter();*/
}
