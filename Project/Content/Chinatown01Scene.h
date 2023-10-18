#pragma once
#include "KatanaScene.h"

class Chinatown01Scene : public KatanaScene
{
public:
	Chinatown01Scene();
	virtual ~Chinatown01Scene();
	Chinatown01Scene(const Chinatown01Scene&) = delete;
	Chinatown01Scene& operator=(const Chinatown01Scene&) = delete;

	virtual void AddMapObject() override final;
	virtual void AddWallObject() override final;
	virtual void AddDoorObject() override final;
	virtual void AddMonsterObject() override final;
	virtual void AddObject() override final;
	virtual void AddLightObject() override final;
	virtual void AddCameraObject() override final;
	virtual void AddUIObject() override final;
	virtual void AddPlayerObject() override final;

	// Scene을(를) 통해 상속됨
	virtual Scene* Clone() override;

	// KatanaScene을(를) 통해 상속됨
	virtual KatanaScene* GetNextScene() override;
};