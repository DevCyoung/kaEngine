#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(CCTVTextDrawer);

class CCTVTextDrawer : public ScriptComponent
{
public:
	CCTVTextDrawer();
	virtual ~CCTVTextDrawer();
	CCTVTextDrawer(const CCTVTextDrawer&) = delete;
	CCTVTextDrawer& operator=(const CCTVTextDrawer&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
