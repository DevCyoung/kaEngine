#pragma once

class FSMState
{
public:
	FSMState();
	virtual ~FSMState();
	
	virtual void InputUpdate() = 0;
	virtual void Update() = 0;
	virtual void Enter() {};
	virtual void Exit() {};


};

