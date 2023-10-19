#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(FolowPlayer);

class Transform;

class FolowPlayer : public ScriptComponent
{
public:
	FolowPlayer();
	virtual ~FolowPlayer();
	FolowPlayer(const FolowPlayer&) = delete;
	FolowPlayer& operator=(const FolowPlayer&) = delete;

	void ShakeCamera();
	void SetFolow(bool bFolow) { mbFolow = bFolow; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void fixedUpdate() override final;
	virtual void lateUpdate() override final;
	virtual void lastUpdate() override final;

	virtual void onCollisionEnter(Collider2D* other) override;	
	virtual void onCollisionStay(Collider2D* other) override;
	virtual void onCollisionExit(Collider2D* other) override;
	
	bool mbCollideWall[4];

	Transform* mPlayerTransform;
	float mShakeTime;
	float mShakeInterverTime;
	Vector3 mPrevPosition;
	int mShakeCount;
	bool mbShake;
	bool mbFolow;
};
