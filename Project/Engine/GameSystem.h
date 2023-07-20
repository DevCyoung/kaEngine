#pragma once

class Collider2D;
class Scene;

class RenderTargetRenderer;
class Physics2D;

class GameSystem
{
public:
	GameSystem(Scene* const scene);
	virtual ~GameSystem();
	GameSystem(const GameSystem&) = delete;
	GameSystem& operator=(const GameSystem&) = delete;

public:
	Physics2D*  GetPhysics2D() { return mPhysics2D; }
	RenderTargetRenderer* GetRenderTargetRenderer() { return mRenderTargetRenderer; }

private:
	Scene* mScene;
	Physics2D* mPhysics2D;
	RenderTargetRenderer* mRenderTargetRenderer;
};

