#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(Rect2DInterpolation);

class Rect2DInterpolation : public ScriptComponent
{
private:
	enum class Dir
	{
		Left,
		Right,
		Up,
		Down,
		Slop,
		End,
	};

public:
	Rect2DInterpolation();
	virtual ~Rect2DInterpolation();
	Rect2DInterpolation(const Rect2DInterpolation&) = delete;
	Rect2DInterpolation& operator=(const Rect2DInterpolation&) = delete;

public:
	bool IsCollisionWallLeft() { return mbCollisionDir[static_cast<UINT>(Dir::Left)]; }
	bool IsCollisionWallRight() { return mbCollisionDir[static_cast<UINT>(Dir::Right)]; }
	bool IsCollisionWallDown() { return mbCollisionDir[static_cast<UINT>(Dir::Down)]; }
	bool IsCollisionWallUp() { return mbCollisionDir[static_cast<UINT>(Dir::Up)]; }
	bool IsCollisionSlop() { return mbCollisionDir[static_cast<UINT>(Dir::Slop)]; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	virtual void onCollisionEnter(Collider2D* other) override;
	virtual void onCollisionStay(Collider2D* other) override;
	virtual void onCollisionExit(Collider2D* other) override;

	void onCollisionLeftWall(Collider2D* other, Vector2 width);
	void onCollisionRightWall(Collider2D* other, Vector2 width);
	void onCollisionDownWall(Collider2D* other, Vector2 width);
	void onCollisionUpWall(Collider2D* other, Vector2 width);	


	bool mbCollisionDir[5];
};
