#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(TitleController);

enum class eTitleState
{
	Start,
	Option,
	NextScene,
	exit,
};

enum class eCursorState
{
	Start,
	Exit,
};

class TitleController : public ScriptComponent
{
public:
	TitleController();
	virtual ~TitleController();
	TitleController(const TitleController&) = delete;
	TitleController& operator=(const TitleController&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	void cursorMove();
	void cursorSelect();

	float mSpeed;

	eTitleState mTitleState;
	eCursorState mCursorState;
};
