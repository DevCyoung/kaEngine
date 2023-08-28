#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(Rect2DInterpolation);

class Rect2DInterpolation : public ScriptComponent
{
private:
	enum class eWallType
	{
		Left,
		Right,
		Ceiling,
		Floor,
		Slope,
		Platform,
		End,
	};

public:
	Rect2DInterpolation();
	virtual ~Rect2DInterpolation();
	Rect2DInterpolation(const Rect2DInterpolation&) = delete;
	Rect2DInterpolation& operator=(const Rect2DInterpolation&) = delete;

public:
	bool IsCollisionWallFloor()   const { return mbCollisionDir[static_cast<UINT>(eWallType::Floor)]; }
	bool IsCollisionWallLeft()    const { return mbCollisionDir[static_cast<UINT>(eWallType::Left)]; }
	bool IsCollisionWallRight()   const { return mbCollisionDir[static_cast<UINT>(eWallType::Right)]; }
	bool IsCollisionWallCeiling() const { return mbCollisionDir[static_cast<UINT>(eWallType::Ceiling)]; }
	bool IsCollisionWallSlop()    const { return mbCollisionDir[static_cast<UINT>(eWallType::Slope)]; }
	bool IsCollisionWalPlatform() const { return mbCollisionDir[static_cast<UINT>(eWallType::Platform)]; }

	bool IsPlatform() const { return mbPlatform; }

	void TurnOnPlatform()   { mbPlatform = true; }
	void TurnOffPlatform()  { mbPlatform = false; }


	

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void lastUpdate() override final;

	virtual void onCollisionEnter(Collider2D* other) override;
	virtual void onCollisionStay(Collider2D* other) override;
	virtual void onCollisionExit(Collider2D* other) override;

	void onCollisionLeftWall(Collider2D* other, Vector2 width);
	void onCollisionRightWall(Collider2D* other, Vector2 width);
	void onCollisionDownWall(Collider2D* other, Vector2 width);
	void onCollisionUpWall(Collider2D* other, Vector2 width);

	void onCollisionInterpolation(Collider2D* const other);

	bool mbPlatform;
	bool mbCollisionDir[static_cast<UINT>(eWallType::End)];
	Vector2 mInterpolationPos[static_cast<UINT>(eWallType::End)];
};
