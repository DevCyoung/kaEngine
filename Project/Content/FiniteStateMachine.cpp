#include "pch.h"
#include "FSMState.h"
#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine()
	: mCurState(nullptr)
	, mPrevState(nullptr)
{
}

FiniteStateMachine::~FiniteStateMachine()
{
}

void FiniteStateMachine::ChangeState(FSMState* const state)
{
	Assert(state, WCHAR_IS_NULLPTR);
	
	mPrevState = state;

	mCurState->Exit();
	mCurState = state;
	mCurState->Enter();
}
