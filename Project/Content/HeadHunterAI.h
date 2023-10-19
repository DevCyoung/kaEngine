#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "MonsterFSM.h"

REGISTER_SCRIPTCOMPONENT_TYPE(HeadHunterAI);

class HeadHunterAI : public ScriptComponent
{
public:
	enum eState
	{
		Idle,
		Sweep,
		Roll,
		Hurt,
		Chase,
		TelportShotGround,
		TelportShot,
		WallJump,
		Attack,
		Aim,
		BoomShot,
		LandDash,
		PreJump,
		Dead,
	};

public:
	HeadHunterAI();
	virtual ~HeadHunterAI();
	HeadHunterAI(const HeadHunterAI&) = delete;
	HeadHunterAI& operator=(const HeadHunterAI&) = delete;

	void CreateAnimation();

	GameObject* CreateHand();
	GameObject* CreateLazer();
	GameObject* CreateBullet();

	void SetHand(GameObject* hand) { mHand = hand; }
	GameObject* GetHand() const { return mHand; }	

	virtual void onCollisionEnter(Collider2D* other) override final;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

private:
	MonsterFSM* mFSM;
	GameObject* mHand;
};
