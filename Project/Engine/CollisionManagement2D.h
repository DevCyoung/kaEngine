#pragma once
#include "EnumLayer.h"

class Scene;
class Collider2D;
class GameObject;
class RenderTargetRenderer;

class CollisionManagement2D
{
	friend class Scene;
public:
	CollisionManagement2D();
	virtual ~CollisionManagement2D();
	CollisionManagement2D(const CollisionManagement2D&) = delete;
	CollisionManagement2D& operator=(const CollisionManagement2D&) = delete;

	void TurnOnAllCollisionLayer();
	void TurnOffAllCollisionLayer();
	void TurnOnCollisionLayer(const eLayerType left, const eLayerType right);
	void TurnOffCollisionLayer(const eLayerType left, const eLayerType right);

private:
	void phisicsUpdate(Scene* const scene);
	void collisionGameObject(const GameObject* const left, const GameObject* const right);

	bool collisionBoxCollider2D(const Collider2D* left, const Collider2D* right);
	bool collisionCircleCollider2D(const Collider2D* left, const Collider2D* right);
	bool collisionBoxAndCircleCollider2D(const Collider2D* box, const Collider2D* circle);

private:
	union CollisionID
	{
		struct tagLayerID
		{
			UINT LeftID;
			UINT RightID;
		} entityID;		

		UINT_PTR id;
	};

	UINT	mCollisionMatrix[static_cast<UINT>(eLayerType::End)];
	std::unordered_map<UINT_PTR, bool>	mCollisionCheckMap;
	RenderTargetRenderer* mRenderTargetRenderer;
};

