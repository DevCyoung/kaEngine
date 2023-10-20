#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(DieController);

class DieController : public ScriptComponent
{
public:
	DieController();
	virtual ~DieController();
	DieController(const DieController&) = delete;
	DieController& operator=(const DieController&) = delete;


	std::vector<GameObject*> mBlackImages;
	std::vector<GameObject*> mTexts;

	void TurnOnDieText();
	void TurnOffDieText();

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	
};
