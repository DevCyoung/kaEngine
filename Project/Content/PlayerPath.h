#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "PathNode.h"

REGISTER_SCRIPTCOMPONENT_TYPE(PlayerPath);

class PlayerPath : public ScriptComponent
{
public:
	PlayerPath();
	virtual ~PlayerPath();
	PlayerPath(const PlayerPath&) = delete;
	PlayerPath& operator=(const PlayerPath&) = delete;

	PathNode* const GetCurPathNodeOrNull() const { return mCurPathNode; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	PathNode* mCurPathNode;
};
