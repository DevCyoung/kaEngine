#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

#include "PathNode.h"
#include "GameManager.h"
#include "PlayerPath.h"

REGISTER_SCRIPTCOMPONENT_TYPE(GangsterAI);

class GangsterAI : public ScriptComponent
{
public:
	GangsterAI();
	virtual ~GangsterAI();
	GangsterAI(const GangsterAI&) = delete;
	GangsterAI& operator=(const GangsterAI&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;


private:
	PathNode* prevPlayerPathNode;	
	std::queue<PathNode*> mPath;
};
