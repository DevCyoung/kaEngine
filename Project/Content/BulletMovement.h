#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "GameObjectBuilder.h"

REGISTER_SCRIPTCOMPONENT_TYPE(BulletMovement);

class BulletMovement : public ScriptComponent
{
public:
	BulletMovement();
	virtual ~BulletMovement();
	BulletMovement(const BulletMovement&) = delete;
	BulletMovement& operator=(const BulletMovement&) = delete;

	Vector3 mDir;

	bool IsPlayerBullet() const { return mbPlayerBullet; }
	void SetIsPlayerBullet(const bool value) { mbPlayerBullet = value; }
	void SetIsScaleMode(const bool value) { mbScaleMode = value; }
	void SetIsRotationMode(const bool value) { mbRotationMode = value; }
	void SetBulletType(const eBulletType value) { mBulletType = value; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	virtual void onCollisionEnter(Collider2D* other) override;
	virtual void onCollisionStay(Collider2D* other) override;
	virtual void onCollisionExit(Collider2D* other) override;



private:
	float mDelay;
	float mSpeed;
	bool mbPlayerBullet;
	bool mbScaleMode;
	bool mbRotationMode;
	eBulletType mBulletType;
};
