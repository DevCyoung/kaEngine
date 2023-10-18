#pragma once
#include "KatanaScene.h"

class Chinatown05Scene : public KatanaScene
{
public:
	Chinatown05Scene();
	virtual ~Chinatown05Scene();
	Chinatown05Scene(const Chinatown05Scene&) = delete;
	Chinatown05Scene& operator=(const Chinatown05Scene&) = delete;

	// KatanaScene을(를) 통해 상속됨
	virtual void AddMapObject() override;
	virtual void AddWallObject() override;
	virtual void AddDoorObject() override;
	virtual void AddMonsterObject() override;
	virtual void AddObject() override;
	virtual void AddLightObject() override;
	virtual void AddCameraObject() override;
	virtual void AddUIObject() override;
	virtual void AddPlayerObject() override;
	virtual Scene* Clone() override;
	virtual KatanaScene* GetNextScene() override;
};

