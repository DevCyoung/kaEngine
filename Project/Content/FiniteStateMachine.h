#pragma once
class FSMState;

class FiniteStateMachine
{
public:
	FiniteStateMachine();
	virtual ~FiniteStateMachine();

	virtual void GlobalUpdate() = 0;
	virtual void InputUpdate() = 0;
	virtual void Update() = 0;

	void ChangeState(FSMState* const state);
	FSMState* GetCurState() const { return mCurState; }


protected:
	FSMState* mCurState;
	FSMState* mPrevState;
};